#!/usr/bin/env python3
"""Check FT2232H Channel A bitmode and try to read data."""
import sys
sys.path.insert(0, 'tools')
from uart_monitor import ftd2xx, FTDeviceInfo, FT_OK
import ctypes
from ctypes import wintypes

# Get device info
num = wintypes.DWORD(0)
ftd2xx.FT_CreateDeviceInfoList(ctypes.byref(num))
infos = (FTDeviceInfo * num.value)()
ftd2xx.FT_GetDeviceInfoList.argtypes = [ctypes.POINTER(FTDeviceInfo), ctypes.POINTER(wintypes.DWORD)]
ftd2xx.FT_GetDeviceInfoList(infos, ctypes.byref(num))
print(f"Device [0]: desc='{infos[0].description.decode()}' flags=0x{infos[0].flags:x}")

# Open device 0
handle = ctypes.c_void_p(0)
status = ftd2xx.FT_Open(0, ctypes.byref(handle))
print(f"FT_Open(0) = {status}")
if status != FT_OK:
    sys.exit(1)

# Check current bitmode
ftd2xx.FT_GetBitMode.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_ubyte)]
ftd2xx.FT_GetBitMode.restype = wintypes.DWORD
mode = ctypes.c_ubyte(0)
status = ftd2xx.FT_GetBitMode(handle, ctypes.byref(mode))
print(f"FT_GetBitMode: status={status} mode=0x{mode.value:02x}")
print("  (0x00=UART/Reset, 0x20=MPSSE, 0x40=FIFO, 0x80=CBUS)")

# Try resetting to UART mode
print("\nTrying FT_SetBitMode(0, 0) to force UART mode...")
status = ftd2xx.FT_SetBitMode(handle, 0, 0)
print(f"  FT_SetBitMode = {status}")

# Re-check
status = ftd2xx.FT_GetBitMode(handle, ctypes.byref(mode))
print(f"  After reset: mode=0x{mode.value:02x}")

# Configure UART
ftd2xx.FT_ResetDevice(handle)
ftd2xx.FT_SetBaudRate(handle, 115200)
ftd2xx.FT_SetDataCharacteristics(handle, 8, 0, 0)
ftd2xx.FT_SetTimeouts(handle, 500, 500)
ftd2xx.FT_Purge(handle, 3)

# Read for 3 seconds
import time
print("\nReading 3 seconds at 115200...")
total = 0
start = time.time()
while time.time() - start < 3:
    buf = (ctypes.c_ubyte * 4096)()
    got = wintypes.DWORD(0)
    ftd2xx.FT_Read(handle, buf, 4096, ctypes.byref(got))
    if got.value > 0:
        data = bytes(buf[:got.value])
        total += got.value
        print(f"  Got {got.value} bytes: {data[:60].hex(' ')}")
        try:
            print(f"    ASCII: {data[:60].decode('ascii', errors='replace')}")
        except:
            pass
print(f"Total: {total} bytes")

# Also check queue status
rxBytes = wintypes.DWORD(0)
ftd2xx.FT_GetQueueStatus(handle, ctypes.byref(rxBytes))
print(f"RX queue: {rxBytes.value} bytes pending")

ftd2xx.FT_Close(handle)
