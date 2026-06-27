"""Fix checksum words to match actual data."""
import ctypes
import struct
import time

ft = ctypes.WinDLL('ftd2xx.dll')
ft.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ft.FT_Open.restype = ctypes.c_uint32
ft.FT_WriteEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.c_uint16]
ft.FT_WriteEE.restype = ctypes.c_uint32
ft.FT_ReadEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint16)]
ft.FT_ReadEE.restype = ctypes.c_uint32
ft.FT_Close.argtypes = [ctypes.c_void_p]
ft.FT_Close.restype = ctypes.c_uint32
ft.FT_GetDeviceInfo.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_uint32),
                                 ctypes.POINTER(ctypes.c_uint32), ctypes.c_char_p,
                                 ctypes.c_char_p, ctypes.c_void_p]
ft.FT_GetDeviceInfo.restype = ctypes.c_uint32

handle = ctypes.c_void_p()
if ft.FT_Open(0, ctypes.byref(handle)) != 0:
    print("FT_Open failed")
    exit(1)

# Read all 256 words
words = []
for i in range(256):
    w = ctypes.c_uint16()
    ft.FT_ReadEE(handle, i, ctypes.byref(w))
    words.append(w.value)

# Compute correct checksums
cs_127 = 0
for w in words[:127]:
    cs_127 ^= w
cs_255 = 0
for w in words[128:255]:
    cs_255 ^= w

print(f"Word 127: stored=0x{words[127]:04x} computed=0x{cs_127:04x}")
print(f"Word 255: stored=0x{words[255]:04x} computed=0x{cs_255:04x}")

# Write correct checksums
if words[127] != cs_127:
    print(f"\nWriting word 127: 0x{words[127]:04x} -> 0x{cs_127:04x}")
    ft.FT_WriteEE(handle, 127, ctypes.c_uint16(cs_127))
    time.sleep(0.1)

if words[255] != cs_255:
    print(f"Writing word 255: 0x{words[255]:04x} -> 0x{cs_255:04x}")
    ft.FT_WriteEE(handle, 255, ctypes.c_uint16(cs_255))
    time.sleep(0.1)

# Verify
w127 = ctypes.c_uint16()
ft.FT_ReadEE(handle, 127, ctypes.byref(w127))
w255 = ctypes.c_uint16()
ft.FT_ReadEE(handle, 255, ctypes.byref(w255))
print(f"\nVerify word 127: 0x{w127.value:04x} {'OK' if w127.value==cs_127 else 'FAIL'}")
print(f"Verify word 255: 0x{w255.value:04x} {'OK' if w255.value==cs_255 else 'FAIL'}")

# Get device info after fix
dev_type = ctypes.c_uint32()
dev_id = ctypes.c_uint32()
sn = ctypes.create_string_buffer(64)
desc = ctypes.create_string_buffer(256)
ft.FT_GetDeviceInfo(handle, ctypes.byref(dev_type), ctypes.byref(dev_id), sn, desc, None)
print(f"\nD2XX now reports: desc='{desc.value.decode()}' sn='{sn.value.decode()}'")

ft.FT_Close(handle)
print("\nDone! Unplug USB, wait 3s, replug.")
