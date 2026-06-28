"""
直接用 FT_WriteEE 修改 raw word，绕过 eeProgram，看 ft_program_data 哪个字段变化。
策略：逐个测试 word 4 / word 5 的候选 bit，看 pdata 的 AIsVCP/BIsVCP 是否变化。

候选 bit：
  - word 4 bit 7  (当前 1)
  - word 4 bit 0-4 (当前 0)
  - word 5 bit 2-3 (当前 1, 0x000c)
  - word 5 bit 0,1,4-15
  - word 6 (当前 0xcccc)
  - word 7 (当前 0x129a)
  - word 0 bit 0-7 (header 0x8f09)

每次修改后读 pdata，看 AIsVCP/BIsVCP 哪个变化。立即恢复。
"""
import sys
import time
import ftd2xx
from ftd2xx._ftd2xx import FT_ReadEE, FT_WriteEE, DWORD, WORD
import ctypes
import json


def open_dev():
    devices = ftd2xx.listDevices()
    if not devices:
        return None
    for idx in range(len(devices)):
        try:
            return ftd2xx.open(idx)
        except ftd2xx.DeviceError:
            continue
    return None


def dump_all(handle):
    words = []
    for i in range(256):
        val = WORD(0)
        st = FT_ReadEE(handle, DWORD(i), ctypes.byref(val))
        if st != 0:
            raise RuntimeError(f"FT_ReadEE({i})={st}")
        words.append(val.value)
    return words


def restore_all(handle, baseline):
    for i, v in enumerate(baseline):
        st = FT_WriteEE(handle, DWORD(i), WORD(v))
        if st != 0:
            raise RuntimeError(f"FT_WriteEE({i})={st}")


def write_word(handle, idx, value):
    """写一个 word，并重算校验和写 word 255"""
    # 先读所有 word
    words = dump_all(handle)
    # 修改目标 word
    words[idx] = value & 0xFFFF
    # 如果 idx < 128，也修改镜像 (idx + 128)
    # 注：dump 显示 word 0..126 镜像在 word 128..254，需同步修改
    if idx < 128:
        mirror_idx = idx + 128
        if mirror_idx < 255:
            words[mirror_idx] = value & 0xFFFF
    # 重算校验和
    cs = 0
    for w in words[:255]:
        cs ^= w
    cs &= 0xFFFF
    words[255] = cs
    # 写入 idx, mirror, 255
    st = FT_WriteEE(handle, DWORD(idx), WORD(words[idx]))
    if st != 0:
        raise RuntimeError(f"FT_WriteEE({idx})={st}")
    if idx < 128:
        st = FT_WriteEE(handle, DWORD(idx + 128), WORD(words[idx + 128]))
        if st != 0:
            raise RuntimeError(f"FT_WriteEE({idx + 128})={st}")
    st = FT_WriteEE(handle, DWORD(255), WORD(cs))
    if st != 0:
        raise RuntimeError(f"FT_WriteEE(255)={st}")


def read_pdata_fields(dev):
    pdata = dev.eeRead()
    return {
        'AIsVCP': pdata.AIsVCP,
        'BIsVCP': pdata.BIsVCP,
        'SelfPowered': pdata.SelfPowered,
        'RemoteWakeup': pdata.RemoteWakeup,
        'IFAIsFifo': pdata.IFAIsFifo,
        'IFBIsFifo': pdata.IFBIsFifo,
        'IFAIsFifoTar': pdata.IFAIsFifoTar,
        'IFBIsFifoTar': pdata.IFBIsFifoTar,
        'IFAIsFastSer': pdata.IFAIsFastSer,
        'IFBIsFastSer': pdata.IFBIsFastSer,
        'PullDownEnable': pdata.PullDownEnable,
        'SerNumEnable': pdata.SerNumEnable,
        'AIsHighCurrent': pdata.AIsHighCurrent,
        'BIsHighCurrent': pdata.BIsHighCurrent,
        'MaxPower': pdata.MaxPower,
    }


def main():
    dev = open_dev()
    if dev is None:
        print("[ERROR] Cannot open device")
        return 1
    handle = dev.handle

    print("\n[BASELINE]")
    baseline = dump_all(handle)
    print(f"  word 0..7: {[f'0x{w:04x}' for w in baseline[:8]]}")
    orig_pdata = read_pdata_fields(dev)
    print(f"  pdata: AIsVCP={orig_pdata['AIsVCP']} BIsVCP={orig_pdata['BIsVCP']}")

    # 候选 (word_idx, bit_to_flip, label)
    # 我们要找 AIsVCP 和 BIsVCP 的位置
    # 当前 word 4 = 0xfa80: bit 7 = 1, bit 5/6 = 0
    # word 5 = 0x000c: bit 2 = 1, bit 3 = 1
    # word 6 = 0xcccc
    # word 7 = 0x129a

    candidates = []
    # word 4: bit 0,1,2,3,4 (currently 0), bit 7 (currently 1) — flip each
    for bit in [0, 1, 2, 3, 4, 7]:
        candidates.append((4, bit, f'word4_bit{bit}'))
    # word 5: bit 0,1,4,5,6,7,8,9,10,11,12,13,14,15 (currently 0)
    for bit in [0, 1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]:
        candidates.append((5, bit, f'word5_bit{bit}'))
    # word 5: bit 2,3 (currently 1) — flip to 0
    for bit in [2, 3]:
        candidates.append((5, bit, f'word5_bit{bit}_flip_1_to_0'))
    # word 7: 各种 bit
    for bit in range(16):
        candidates.append((7, bit, f'word7_bit{bit}'))

    print(f"\n[INFO] Testing {len(candidates)} candidate bits")

    findings = []
    for word_idx, bit, label in candidates:
        # 读当前 word 值
        cur = WORD(0)
        FT_ReadEE(handle, DWORD(word_idx), ctypes.byref(cur))
        cur_val = cur.value
        # flip bit
        new_val = cur_val ^ (1 << bit)
        if new_val == cur_val:
            continue  # bit already at desired state, skip

        # 写入
        try:
            write_word(handle, word_idx, new_val)
        except Exception as e:
            print(f"  [{label}] write error: {e}")
            continue

        # 读 pdata
        try:
            pdata = read_pdata_fields(dev)
        except Exception as e:
            print(f"  [{label}] pdata read error: {e}")
            restore_all(handle, baseline)
            continue

        # 找变化的字段
        changed = []
        for k, v in pdata.items():
            if orig_pdata.get(k) != v:
                changed.append(f"{k}:{orig_pdata.get(k)}->{v}")

        if changed:
            print(f"  [{label}] word{word_idx}=0x{cur_val:04x}->0x{new_val:04x}  pdata changed: {changed}")
            findings.append((word_idx, bit, label, changed, cur_val, new_val))

        # 立即恢复
        restore_all(handle, baseline)

    print("\n" + "=" * 70)
    print("找到的字段映射汇总")
    print("=" * 70)
    for word_idx, bit, label, changed, cur_val, new_val in findings:
        print(f"  {label}: word{word_idx}=0x{cur_val:04x}->0x{new_val:04x} -> {changed}")

    if not findings:
        print("  (no candidate bits changed AIsVCP/BIsVCP — they may not be in standard ft_program_data)")

    print("\n[DONE]")
    dev.close()
    return 0


if __name__ == '__main__':
    sys.exit(main())
