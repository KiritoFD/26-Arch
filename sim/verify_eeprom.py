"""Re-read EEPROM and compare with original in detail, byte by byte."""
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

handle = ctypes.c_void_p()
if ft.FT_Open(0, ctypes.byref(handle)) != 0:
    print("FT_Open failed")
    exit(1)

# Get device info
dev_type = ctypes.c_uint32()
dev_id = ctypes.c_uint32()
sn = ctypes.create_string_buffer(64)
desc = ctypes.create_string_buffer(256)
ft.FT_GetDeviceInfo(handle, ctypes.byref(dev_type), ctypes.byref(dev_id), sn, desc, None)
print(f"D2XX reports: desc='{desc.value.decode()}' sn='{sn.value.decode()}' type={dev_type.value} id=0x{dev_id.value:08x}")

# Read 256 words
words = []
for i in range(256):
    w = ctypes.c_uint16()
    ft.FT_ReadEE(handle, i, ctypes.byref(w))
    words.append(w.value)
ft.FT_Close(handle)

# Compare with original
with open('sim/eeprom_backups/eeprom_backup_20260627_072124.bin', 'rb') as f:
    orig_data = f.read()
orig = list(struct.unpack('<' + 'H'*(len(orig_data)//2), orig_data))

print(f"\n=== Full comparison (current vs original) ===")
diffs = []
for i in range(256):
    if words[i] != orig[i]:
        diffs.append(i)

print(f"Total diffs: {len(diffs)}")
if diffs:
    # Group: serial area vs non-serial
    serial_area = set(range(106, 120)) | set(range(234, 248))
    serial_diffs = [i for i in diffs if i in serial_area]
    non_serial_diffs = [i for i in diffs if i not in serial_area]
    print(f"  Serial area diffs (expected): {len(serial_diffs)}")
    print(f"  Non-serial diffs: {len(non_serial_diffs)}")
    if non_serial_diffs:
        print("\n  *** UNEXPECTED DIFFS ***")
        for i in non_serial_diffs:
            print(f"    Word {i:3d}: cur=0x{words[i]:04x} orig=0x{orig[i]:04x}")

# Verify checksum
cs_127 = 0
for w in words[:127]:
    cs_127 ^= w
cs_255 = 0
for w in words[128:255]:
    cs_255 ^= w
print(f"\nChecksum word 127: stored=0x{words[127]:04x} computed=0x{cs_127:04x} {'OK' if words[127]==cs_127 else 'FAIL'}")
print(f"Checksum word 255: stored=0x{words[255]:04x} computed=0x{cs_255:04x} {'OK' if words[255]==cs_255 else 'FAIL'}")

# Show all non-zero words
print(f"\n=== All non-zero words in current EEPROM ===")
for i in range(256):
    if words[i] != 0:
        lo = words[i] & 0xff
        hi = (words[i] >> 8) & 0xff
        c_lo = chr(lo) if 0x20 <= lo < 0x7f else '.'
        c_hi = chr(hi) if 0x20 <= hi < 0x7f else '.'
        print(f"  word {i:3d}: 0x{words[i]:04x}  '{c_lo}{c_hi}'")

# The D2XX desc comes from USB descriptor, not EEPROM directly
# FTDI chip reads EEPROM at USB enumeration time
# If desc='Dual RS232-HS' it means FTDI is NOT using EEPROM config
# This happens when checksum fails OR when config bits are invalid
print(f"\n=== Config analysis ===")
print(f"Word 3 (ChanA config): 0x{words[3]:04x}")
print(f"Word 4 (ChanB config): 0x{words[4]:04x}")
print(f"Word 5 (Misc config):  0x{words[5]:04x}")
print(f"Word 9: 0x{words[9]:04x} (orig=0x{orig[9]:04x})")
