#!/usr/bin/env python3
"""Minimal check: open, get bitmode, close. No loops."""
import sys
sys.path.insert(0, 'tools')
from uart_monitor import ftd2xx, FT_OK
import ctypes
from ctypes import wintypes

handle = ctypes.c_void_p(0)
status = ftd2xx.FT_Open(0, ctypes.byref(handle))
print(f"FT_Open(0) = {status}", flush=True)
if status != FT_OK:
    print("Device busy or unavailable. Exit.", flush=True)
    sys.exit(1)

ftd2xx.FT_GetBitMode.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_ubyte)]
ftd2xx.FT_GetBitMode.restype = wintypes.DWORD
mode = ctypes.c_ubyte(0)
status = ftd2xx.FT_GetBitMode(handle, ctypes.byref(mode))
print(f"FT_GetBitMode: status={status} mode=0x{mode.value:02x}", flush=True)

# Single FT_Read attempt (non-blocking)
ftd2xx.FT_SetTimeouts(handle, 100, 100)
buf = (ctypes.c_ubyte * 64)()
got = wintypes.DWORD(0)
status = ftd2xx.FT_Read(handle, buf, 64, ctypes.byref(got))
print(f"FT_Read: status={status} got={got.value}", flush=True)
if got.value > 0:
    print(f"  bytes: {bytes(buf[:got.value]).hex(' ')}", flush=True)

ftd2xx.FT_Close(handle)
print("DONE", flush=True)
