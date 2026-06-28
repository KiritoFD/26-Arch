#!/usr/bin/env python3
"""Identify which D2XX index is Channel A vs B by serial number suffix."""
import sys
sys.path.insert(0, 'tools')
from uart_monitor import ftd2xx, FTDeviceInfo, FT_OK
import ctypes
from ctypes import wintypes

num = wintypes.DWORD(0)
ftd2xx.FT_CreateDeviceInfoList(ctypes.byref(num))
infos = (FTDeviceInfo * num.value)()
ftd2xx.FT_GetDeviceInfoList.argtypes = [ctypes.POINTER(FTDeviceInfo), ctypes.POINTER(wintypes.DWORD)]
ftd2xx.FT_GetDeviceInfoList(infos, ctypes.byref(num))

ftd2xx.FT_GetBitMode.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_ubyte)]
ftd2xx.FT_GetBitMode.restype = wintypes.DWORD

for i in range(num.value):
    info = infos[i]
    desc = info.description.decode('ascii', errors='replace')
    serial = info.serialNumber.decode('ascii', errors='replace')
    print(f"[{i}] desc='{desc}' serial='{serial}' flags=0x{info.flags:x} locId=0x{info.locId:x}", flush=True)

    # Try open to read bitmode
    handle = ctypes.c_void_p(0)
    st = ftd2xx.FT_Open(i, ctypes.byref(handle))
    if st != FT_OK:
        print(f"    FT_Open failed: {st} (likely busy = VCP driver owns it)", flush=True)
        # If busy, it's likely the VCP-managed channel!
        continue

    mode = ctypes.c_ubyte(0)
    st = ftd2xx.FT_GetBitMode(handle, ctypes.byref(mode))
    print(f"    BitMode=0x{mode.value:02x} (0x00=UART, 0x40=FIFO, 0x20=MPSSE, 0xff=bitbang)", flush=True)
    ftd2xx.FT_Close(handle)
print("DONE", flush=True)
