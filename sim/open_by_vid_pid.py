"""Find and open FTDI device by VID/PID via USB enumeration, bypassing D2XX FT_ListDevices.

When VID is changed from 0x0403 (FTDI default) to something else like 0x1443 (Xilinx),
the FTDI VCP/D2XX drivers no longer claim the device, so FT_ListDevices returns 0.
We need to open it directly to fix the EEPROM.

Strategy: use FT_OpenEx with device description "Digilent USB Device" which is still
reported by the OS even when VID changed. If that fails, we need to find another way.
"""
import ctypes
import sys

ftd2xx = ctypes.windll.FTD2XX

# FT_OpenEx with description
ftd2xx.FT_OpenEx.argtypes = [ctypes.c_char_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ftd2xx.FT_OpenEx.restype = ctypes.c_uint32

# Try opening by description "Digilent USB Device"
descriptions = [
    b"Digilent USB Device",
    b"Digilent USB Device A",
    b"Digilent USB Device B",
    b"Dual RS232-HS",
    b"Dual RS232",
    b"USB Serial Converter A",
    b"USB Serial Converter B",
]

print("=== Trying FT_OpenEx by description ===")
for desc in descriptions:
    handle = ctypes.c_void_p()
    status = ftd2xx.FT_OpenEx(desc, 1, ctypes.byref(handle))  # FT_OPEN_BY_DESCRIPTION = 1
    if status == 0:
        print(f"  SUCCESS with description: {desc}")
        ftd2xx.FT_Close(handle)
    else:
        print(f"  failed ({status}) with: {desc}")

# Try opening by serial number
print("\n=== Trying FT_OpenEx by serial number ===")
serials = [
    b"210183A8AC3D",
    b"210183A8AC3DA",
    b"210183A8AC3DB",
    b"A",
    b"B",
]
for sn in serials:
    handle = ctypes.c_void_p()
    status = ftd2xx.FT_OpenEx(sn, 2, ctypes.byref(handle))  # FT_OPEN_BY_SERIAL_NUMBER = 2
    if status == 0:
        print(f"  SUCCESS with SN: {sn}")
        ftd2xx.FT_Close(handle)
    else:
        print(f"  failed ({status}) with SN: {sn}")

# Also try the standard FT_Open with indices 0-3
print("\n=== Trying FT_Open by index ===")
ftd2xx.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ftd2xx.FT_Open.restype = ctypes.c_uint32
for idx in range(4):
    handle = ctypes.c_void_p()
    status = ftd2xx.FT_Open(idx, ctypes.byref(handle))
    if status == 0:
        print(f"  FT_Open({idx}) OK")
        ftd2xx.FT_Close(handle)
    else:
        print(f"  FT_Open({idx}) failed: {status}")
