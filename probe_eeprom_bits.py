"""
探测 FT2232H EEPROM 字段对应的 raw word/bit 位置。
策略：
  1. dump 当前所有 256 words (baseline)
  2. eeProgram 修改若干字段为 1 (AIsVCP, BIsVCP, SelfPowered, RemoteWakeup, IFAIsFifo, IFBIsFifo)
  3. dump 所有 words，对比哪些 bit 翻转
  4. 立即用备份恢复 (写回 baseline)
  5. dump 验证恢复成功

每次 eeProgram 调用前都会备份。
所有操作都在 channel 1 (Port B, D2XX) 上做（已知能打开）。
"""
import sys
import time
import ftd2xx
from ftd2xx._ftd2xx import FT_ReadEE, FT_WriteEE, FT_HANDLE, DWORD, WORD, LPWORD
import ctypes
import json
import os


def list_channels():
    devices = ftd2xx.listDevices()
    if not devices:
        return []
    return list(devices)


def open_channel(idx):
    try:
        return ftd2xx.open(idx)
    except ftd2xx.DeviceError as e:
        return None


def dump_all_words(handle):
    words = []
    for i in range(256):
        val = WORD(0)
        status = FT_ReadEE(handle, DWORD(i), ctypes.byref(val))
        if status != 0:
            raise RuntimeError(f"FT_ReadEE({i}) failed: {status}")
        words.append(val.value)
    return words


def calc_checksum(words_0_254):
    c = 0
    for w in words_0_254:
        c ^= w
    return c & 0xFFFF


def diff_words(before, after):
    """返回 [(idx, before_val, after_val, flipped_bits)]"""
    diffs = []
    for i, (b, a) in enumerate(zip(before, after)):
        if b != a:
            flipped = b ^ a
            diffs.append((i, b, a, flipped))
    return diffs


def main():
    devices = list_channels()
    print(f"[INFO] Found {len(devices) if devices else 0} FTDI device(s)")
    if not devices:
        print("[ERROR] No FTDI devices")
        return 1

    dev = None
    chosen_idx = None
    for idx in range(len(devices)):
        d = open_channel(idx)
        if d is not None:
            dev = d
            chosen_idx = idx
            print(f"[INFO] Opened channel index {idx}")
            break
    if dev is None:
        print("[ERROR] Cannot open any channel")
        return 1

    handle = dev.handle
    print(f"[INFO] handle = {handle}")

    # Step 1: dump baseline
    print("\n[STEP 1] Dump baseline (current EEPROM)")
    baseline = dump_all_words(handle)
    cs = calc_checksum(baseline[:255])
    print(f"[INFO] Baseline checksum: stored=0x{baseline[255]:04x} calc=0x{cs:04x} {'OK' if cs==baseline[255] else 'MISMATCH'}")

    # 备份到文件
    backup_path = f"eeprom_probe_backup_{time.strftime('%Y%m%d_%H%M%S')}.bin"
    with open(backup_path, 'wb') as f:
        for w in baseline:
            f.write(bytes([w & 0xFF, (w >> 8) & 0xFF]))
    print(f"[INFO] Baseline saved to {backup_path}")

    # Step 2: 读 ft_program_data
    print("\n[STEP 2] Read ft_program_data")
    pdata = dev.eeRead()
    pd_dict = {
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
        'MaxPower': pdata.MaxPower,
        'PullDownEnable': pdata.PullDownEnable,
        'SerNumEnable': pdata.SerNumEnable,
        'AIsHighCurrent': pdata.AIsHighCurrent,
        'BIsHighCurrent': pdata.BIsHighCurrent,
    }
    print(f"[INFO] Original pdata: {json.dumps(pd_dict, indent=2)}")

    # Step 3: eeProgram — 翻转若干字段为 1
    print("\n[STEP 3] eeProgram with AIsVCP=1, BIsVCP=1, SelfPowered=1, RemoteWakeup=1, IFAIsFifo=1, IFBIsFifo=1")
    # 复制 pdata, 修改若干字段
    pdata.AIsVCP = 1
    pdata.BIsVCP = 1
    pdata.SelfPowered = 1
    pdata.RemoteWakeup = 1
    pdata.IFAIsFifo = 1
    pdata.IFBIsFifo = 1

    try:
        dev.eeProgram(pdata)
        print("[INFO] eeProgram OK")
    except Exception as e:
        print(f"[ERROR] eeProgram failed: {e}")
        dev.close()
        return 1

    # Step 4: dump after
    print("\n[STEP 4] Dump after eeProgram")
    after = dump_all_words(handle)
    diffs = diff_words(baseline, after)
    if not diffs:
        print("[WARN] No words changed — eeProgram had NO effect on raw EEPROM")
        print("[INFO] This means eeProgram is broken for FT2232H — need raw bit manipulation")
    else:
        print(f"[INFO] {len(diffs)} word(s) changed:")
        for idx, b, a, fl in diffs:
            print(f"  Word {idx:3d}: 0x{b:04x} -> 0x{a:04x}  (flipped bits = 0x{fl:04x})")
            # 列出每个翻转的 bit
            for bit in range(16):
                if fl & (1 << bit):
                    before_bit = (b >> bit) & 1
                    after_bit = (a >> bit) & 1
                    print(f"      bit {bit:2d}: {before_bit} -> {after_bit}")

    # Step 5: 立即恢复（用 baseline raw 直接 FT_WriteEE）
    print("\n[STEP 5] Restore baseline by FT_WriteEE")
    for i in range(256):
        status = FT_WriteEE(handle, DWORD(i), WORD(baseline[i]))
        if status != 0:
            print(f"[ERROR] FT_WriteEE({i}) failed: {status}")
            dev.close()
            return 1
    print("[INFO] All 256 words restored")

    # Step 6: 验证恢复
    print("\n[STEP 6] Verify restore")
    restored = dump_all_words(handle)
    mismatch_count = 0
    for i, (b, r) in enumerate(zip(baseline, restored)):
        if b != r:
            mismatch_count += 1
            if mismatch_count <= 5:
                print(f"  [MISMATCH] word {i}: baseline=0x{b:04x} restored=0x{r:04x}")
    if mismatch_count == 0:
        print(f"[OK] Restore successful — all 256 words match baseline")
    else:
        print(f"[ERROR] Restore failed — {mismatch_count} words mismatch")

    # Step 7: 再读 pdata 验证字段
    print("\n[STEP 7] Re-read ft_program_data after restore")
    pdata2 = dev.eeRead()
    pd_dict2 = {
        'AIsVCP': pdata2.AIsVCP,
        'BIsVCP': pdata2.BIsVCP,
        'SelfPowered': pdata2.SelfPowered,
        'RemoteWakeup': pdata2.RemoteWakeup,
        'IFAIsFifo': pdata2.IFAIsFifo,
        'IFBIsFifo': pdata2.IFBIsFifo,
    }
    print(f"[INFO] After restore pdata: {json.dumps(pd_dict2, indent=2)}")

    dev.close()
    print(f"\n[DONE] Probe complete. Backup at: {backup_path}")
    return 0


if __name__ == '__main__':
    sys.exit(main())
