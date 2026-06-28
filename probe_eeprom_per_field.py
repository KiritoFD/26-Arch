"""
逐字段探测：单独修改一个字段为 1，dump 前后对比，精确定位每个字段对应的 raw bit。
测试字段：AIsVCP, BIsVCP, SelfPowered, RemoteWakeup, IFAIsFifo, IFBIsFifo,
         IFAIsFifoTar, IFBIsFifoTar, IFAIsFastSer, IFBIsFastSer,
         PullDownEnable, SerNumEnable, AIsHighCurrent, BIsHighCurrent,
         USBVersionEnable, USBVersion
每次修改后立即恢复。
"""
import sys
import time
import ftd2xx
from ftd2xx._ftd2xx import FT_ReadEE, FT_WriteEE, DWORD, WORD
import ctypes
import json


def open_dev():
    devices = ftd2xx.listDevices()
    print(f"[INFO] Found {len(devices) if devices else 0} FTDI device(s)")
    if not devices:
        return None
    for idx in range(len(devices)):
        try:
            d = ftd2xx.open(idx)
            print(f"[INFO] Opened channel index {idx}")
            return d
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


def diff(before, after):
    diffs = []
    for i, (b, a) in enumerate(zip(before, after)):
        if b != a:
            diffs.append((i, b, a, b ^ a))
    return diffs


# 测试字段列表
TEST_FIELDS = [
    'AIsVCP', 'BIsVCP',
    'SelfPowered', 'RemoteWakeup',
    'IFAIsFifo', 'IFBIsFifo',
    'IFAIsFifoTar', 'IFBIsFifoTar',
    'IFAIsFastSer', 'IFBIsFastSer',
    'PullDownEnable', 'SerNumEnable',
    'AIsHighCurrent', 'BIsHighCurrent',
    'USBVersionEnable',
]


def main():
    dev = open_dev()
    if dev is None:
        print("[ERROR] Cannot open device")
        return 1

    handle = dev.handle
    print(f"[INFO] handle = {handle}")

    # baseline
    print("\n[BASELINE] Dump current EEPROM")
    baseline = dump_all(handle)
    print(f"[INFO] baseline word 0..7: {[f'0x{w:04x}' for w in baseline[:8]]}")
    print(f"[INFO] baseline word 4 = 0x{baseline[4]:04x}")

    # 读 pdata
    pdata_orig = dev.eeRead()
    print(f"[INFO] Original AIsVCP={pdata_orig.AIsVCP} BIsVCP={pdata_orig.BIsVCP}")

    results = {}

    for field in TEST_FIELDS:
        print(f"\n[TEST] Set {field}=1 (only this field)")
        # 复制原 pdata
        pdata = dev.eeRead()
        # 设置当前字段为 1 (其他保持原值)
        setattr(pdata, field, 1)

        # dump before
        before = dump_all(handle)

        # eeProgram
        try:
            dev.eeProgram(pdata)
        except Exception as e:
            print(f"  [ERROR] eeProgram failed: {e}")
            results[field] = ('error', str(e))
            continue

        # dump after
        after = dump_all(handle)
        diffs = diff(before, after)
        if not diffs:
            print(f"  [NO CHANGE] eeProgram had no effect on raw bits")
            results[field] = ('no_change', None)
        else:
            summary = []
            for idx, b, a, fl in diffs:
                if idx == 127 or idx == 255:
                    continue  # 校验和
                summary.append(f"word{idx}:0x{b:04x}->0x{a:04x}(flipped=0x{fl:04x})")
                # 列出翻转的 bit
                for bit in range(16):
                    if fl & (1 << bit):
                        bb = (b >> bit) & 1
                        aa = (a >> bit) & 1
                        print(f"    word {idx} bit {bit:2d}: {bb} -> {aa}")
            print(f"  [CHANGED] {summary}")
            results[field] = ('changed', summary)

        # 立即恢复
        restore_all(handle, baseline)
        # 验证恢复
        restored = dump_all(handle)
        if restored != baseline:
            print(f"  [ERROR] restore failed!")
            mismatch = sum(1 for b, r in zip(baseline, restored) if b != r)
            print(f"  {mismatch} words mismatch")

    # 恢复 pdata 读回验证
    print("\n[FINAL] Re-read pdata after all tests")
    pdata_final = dev.eeRead()
    print(f"[INFO] AIsVCP={pdata_final.AIsVCP} BIsVCP={pdata_final.BIsVCP}")

    dev.close()

    # 汇总
    print("\n" + "=" * 70)
    print("字段 -> raw bit 位置 汇总")
    print("=" * 70)
    for field, (status, info) in results.items():
        if status == 'changed':
            print(f"  {field:20s} -> {info}")
        elif status == 'no_change':
            print(f"  {field:20s} -> [NO CHANGE] (eeProgram ignored this field)")
        else:
            print(f"  {field:20s} -> [ERROR] {info}")

    print("\n[DONE]")
    return 0


if __name__ == '__main__':
    sys.exit(main())
