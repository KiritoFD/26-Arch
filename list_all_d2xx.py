#!/usr/bin/env python3
"""List ALL FTDI devices including busy ones. Try opening by description."""
import sys
sys.path.insert(0, 'tools')
from uart_monitor import ftd2xx, FTDeviceInfo, FT_OK
import ctypes
from ctypes import wintypes

num = wintypes.DWORD(0)
ftd2xx.FT_CreateDeviceInfoList(ctypes.byref(num))
print(f"Total FTDI devices: {num.value}", flush=True)

infos = (FTDeviceInfo * num.value)()
ftd2xx.FT_GetDeviceInfoList.argtypes = [ctypes.POINTER(FTDeviceInfo), ctypes.POINTER(wintypes.DWORD)]
ftd2xx.FT_GetDeviceInfoList(infos, ctypes.byref(num))

for i in range(num.value):
    info = infos[i]
    desc = info.description.decode('ascii', errors='replace')
    serial = info.serialNumber.decode('ascii', errors='replace')
    opened = bool(info.flags & 1)
    print(f"[{i}] desc='{desc}' serial='{serial}' flags=0x{info.flags:x} opened={opened}", flush=True)

# Also try FT_ListDevices with different modes
print("\n=== FT_ListDevices (mode=0) ===", flush=True)
ftd2xx.FT_ListDevices.argtypes = [ctypes.POINTER(wintypes.DWORD), ctypes.c_void_p, wintypes.DWORD]
ftd2xx.FT_ListDevices.restype = wintypes.DWORD
cnt = wintypes.DWORD(0)
st = ftd2xx.FT_ListDevices(ctypes.byref(cnt), None, 0)  # FT_LIST_NUMBER_ONLY
print(f"  Count: {cnt.value} (status={st})", flush=True)
