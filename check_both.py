#!/usr/bin/env python3
"""Check BOTH Channel A (idx 0) and Channel B (idx 1) bitmode."""
import sys
sys.path.insert(0, 'tools')
from uart_monitor import ftd2xx, FT_OK
import ctypes
from ctypes import wintypes

ftd2xx.FT_GetBitMode.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_ubyte)]
ftd2xx.FT_GetBitMode.restype = wintypes.DWORD

for idx in [0, 1]:
    handle = ctypes.c_void_p(0)
    status = ftd2xx.FT_Open(idx, ctypes.byref(handle))
    print(f"=== Channel [{idx}] ===", flush=True)
    if status != FT_OK:
        print(f"  FT_Open = {status} (busy)", flush=True)
        continue

    mode = ctypes.c_ubyte(0)
    s = ftd2xx.FT_GetBitMode(handle, ctypes.byref(mode))
    print(f"  BitMode = 0x{mode.value:02x} (status={s})", flush=True)

    # Try set UART mode and read
    ftd2xx.FT_ResetDevice(handle)
    ftd2xx.FT_SetBaudRate(handle, 115200)
    ftd2xx.FT_SetDataCharacteristics(handle, 8, 0, 0)
    ftd2xx.FT_SetTimeouts(handle, 500, 500)
    ftd2xx.FT_Purge(handle, 3)

    buf = (ctypes.c_ubyte * 256)()
    got = wintypes.DWORD(0)
    s = ftd2xx.FT_Read(handle, buf, 256, ctypes.byref(got))
    print(f"  Read: status={s} got={got.value}", flush=True)
    if got.value > 0:
        print(f"  data: {bytes(buf[:min(got.value,64)]).hex(' ')}", flush=True)
        try:
            print(f"  ascii: {bytes(buf[:min(got.value,64)]).decode('ascii', errors='replace')}", flush=True)
        except: pass

    ftd2xx.FT_Close(handle)
print("DONE", flush=True)
