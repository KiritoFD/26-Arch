"""Diagnose current EEPROM state and compare with backup."""
import ctypes
import struct

ft = ctypes.WinDLL('ftd2xx.dll')
ft.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ft.FT_Open.restype = ctypes.c_uint32
ft.FT_ReadEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint16)]
ft.FT_ReadEE.restype = ctypes.c_uint32
ft.FT_Close.argtypes = [ctypes.c_void_p]
ft.FT_Close.restype = ctypes.c_uint32
ft.FT_GetDeviceInfo.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_uint32),
                                 ctypes.POINTER(ctypes.c_uint32), ctypes.c_char_p,
                                 ctypes.c_char_p, ctypes.c_void_p]
ft.FT_GetDeviceInfo.restype = ctypes.c_uint32

# List devices first
ft.FT_CreateDeviceInfoList.argtypes = [ctypes.POINTER(ctypes.c_uint32)]
ft.FT_CreateDeviceInfoList.restype = ctypes.c_uint32
num = ctypes.c_uint32()
ft.FT_CreateDeviceInfoList(ctypes.byref(num))
print(f"D2XX devices found: {num.value}")

if num.value == 0:
    print("No D2XX devices! EEPROM may be corrupt or VID wrong.")
    exit(1)

handle = ctypes.c_void_p()
if ft.FT_Open(0, ctypes.byref(handle)) != 0:
    print("FT_Open failed")
    exit(1)

dev_type = ctypes.c_uint32()
dev_id = ctypes.c_uint32()
sn = ctypes.create_string_buffer(64)
desc = ctypes.create_string_buffer(256)
ft.FT_GetDeviceInfo(handle, ctypes.byref(dev_type), ctypes.byref(dev_id), sn, desc, None)
print(f"D2XX: desc='{desc.value.decode()}' sn='{sn.value.decode()}' type={dev_type.value}")

# Read 256 words
words = []
for i in range(256):
    w = ctypes.c_uint16()
    ft.FT_ReadEE(handle, i, ctypes.byref(w))
    words.append(w.value)
ft.FT_Close(handle)

# Load backup
with open('sim/eeprom_backups/eeprom_backup_20260627_072124.bin', 'rb') as f:
    orig_data = f.read()
orig = list(struct.unpack('<' + 'H'*(len(orig_data)//2), orig_data))

# Compare
diffs = []
for i in range(256):
    if words[i] != orig[i]:
        diffs.append(i)
print(f"\nDiffs vs backup: {len(diffs)}")
for i in diffs:
    print(f"  word {i:3d}: cur=0x{words[i]:04x} orig=0x{orig[i]:04x}")

# Check checksum
cs127 = 0
for w in words[:127]:
    cs127 ^= w
cs255 = 0
for w in words[128:255]:
    cs255 ^= w
print(f"\nChecksum 127: stored=0x{words[127]:04x} computed=0x{cs127:04x} {'OK' if words[127]==cs127 else 'FAIL'}")
print(f"Checksum 255: stored=0x{words[255]:04x} computed=0x{cs255:04x} {'OK' if words[255]==cs255 else 'FAIL'}")

# Key fields
print(f"\nWord 0 (PID): 0x{words[0]:04x}")
print(f"Word 1 (VID): 0x{words[1]:04x}")
print(f"Word 3 (cfg): 0x{words[3]:04x}")
print(f"Word 4 (cfgB): 0x{words[4]:04x}")
print(f"Word 5 (misc): 0x{words[5]:04x}")
print(f"Word 9: 0x{words[9]:04x} (bit11={1 if words[9]&0x800 else 0})")
