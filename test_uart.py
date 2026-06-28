#!/usr/bin/env python3
"""Quick test: read UART for 3 seconds and dump raw bytes."""
import sys
sys.path.insert(0, 'tools')
from uart_monitor import list_devices, find_basys3_uart, open_uart, read_uart, close_uart, ftd2xx, FTDeviceInfo
import ctypes
from ctypes import wintypes
import time

print("=== FTDI devices (detailed) ===")
num = wintypes.DWORD(0)
ftd2xx.FT_CreateDeviceInfoList(ctypes.byref(num))
print(f"Total devices: {num.value}")
if num.value > 0:
    infos = (FTDeviceInfo * num.value)()
    ftd2xx.FT_GetDeviceInfoList.argtypes = [ctypes.POINTER(FTDeviceInfo), ctypes.POINTER(wintypes.DWORD)]
    ftd2xx.FT_GetDeviceInfoList.restype = wintypes.DWORD
    ftd2xx.FT_GetDeviceInfoList(infos, ctypes.byref(num))
    for i, info in enumerate(infos):
        desc = info.description.decode('ascii', errors='replace')
        serial = info.serialNumber.decode('ascii', errors='replace')
        flags_opened = bool(info.flags & 1)
        flags_hispeed = bool(info.flags & 2)
        print(f"  [{i}] desc='{desc}' serial='{serial}' flags=0x{info.flags:x} type={info.type} id=0x{info.id:x} locId=0x{info.locId:x} opened={flags_opened} hispeed={flags_hispeed}")

idx, desc = find_basys3_uart()
print(f"\nSelected: [{idx}] {desc}")

for baud in [115200, 57600, 38400]:
    print(f"\n=== Testing baud={baud} (3s) ===")
    handle, msg = open_uart(idx, baud)
    if handle is None:
        print(f"  Open failed: {msg}")
        continue
    total = 0
    ascii_count = 0
    start = time.time()
    samples = []
    while time.time() - start < 3:
        data, _ = read_uart(handle, 4096)
        if data:
            total += len(data)
            samples.append(data)
            ascii_count += sum(1 for b in data if 32 <= b < 127 or b in (10, 13))
    close_uart(handle)
    print(f"  Total bytes: {total}, ASCII-printable: {ascii_count} ({100*ascii_count/max(total,1):.0f}%)")
    if samples:
        all_data = b''.join(samples)
        print(f"  First 200 bytes (hex): {all_data[:200].hex(' ')}")
        try:
            text = all_data[:200].decode('ascii', errors='replace')
            print(f"  First 200 bytes (ascii): {repr(text)}")
        except:
            pass
    if total > 0 and ascii_count / max(total, 1) > 0.7:
        print(f"  >>> baud={baud} looks correct (high ASCII ratio)")
        break
