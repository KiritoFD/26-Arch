#!/usr/bin/env python3
"""Test Channel B (idx 1) — might be the UART channel if EEPROM has A=FIFO/B=UART."""
import sys
sys.path.insert(0, 'tools')
from uart_monitor import ftd2xx, FT_OK
import ctypes
from ctypes import wintypes
import time

ftd2xx.FT_GetBitMode.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_ubyte)]
ftd2xx.FT_GetBitMode.restype = wintypes.DWORD

handle = ctypes.c_void_p(0)
st = ftd2xx.FT_Open(1, ctypes.byref(handle))  # Channel B
print(f"FT_Open(1) = {st}", flush=True)
if st != FT_OK:
    sys.exit(1)

mode = ctypes.c_ubyte(0)
st = ftd2xx.FT_GetBitMode(handle, ctypes.byref(mode))
print(f"Channel B BitMode=0x{mode.value:02x} (st={st})", flush=True)

# Configure as UART
ftd2xx.FT_ResetDevice(handle)
ftd2xx.FT_SetBitMode(handle, 0, 0)  # Force UART mode
ftd2xx.FT_SetBaudRate(handle, 115200)
ftd2xx.FT_SetDataCharacteristics(handle, 8, 0, 0)
ftd2xx.FT_SetFlowControl(handle, 0, 0, 0)
ftd2xx.FT_SetTimeouts(handle, 300, 300)
ftd2xx.FT_SetLatencyTimer(handle, 2)
ftd2xx.FT_Purge(handle, 3)

st = ftd2xx.FT_GetBitMode(handle, ctypes.byref(mode))
print(f"After config BitMode=0x{mode.value:02x}", flush=True)

# Read 3 seconds
print("Reading 3s at 115200...", flush=True)
total = 0
start = time.time()
samples = []
while time.time() - start < 3:
    buf = (ctypes.c_ubyte * 4096)()
    got = wintypes.DWORD(0)
    ftd2xx.FT_Read(handle, buf, 4096, ctypes.byref(got))
    if got.value > 0:
        data = bytes(buf[:got.value])
        total += got.value
        samples.append(data)

print(f"Total bytes: {total}", flush=True)
if samples:
    all_data = b''.join(samples)
    print(f"First 200 hex: {all_data[:200].hex(' ')}", flush=True)
    try:
        print(f"First 200 ascii: {all_data[:200].decode('ascii', errors='replace')!r}", flush=True)
    except: pass

ftd2xx.FT_Close(handle)
print("DONE", flush=True)
