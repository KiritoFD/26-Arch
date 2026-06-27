"""Decode the FT2232H USB string descriptors from EEPROM raw words.

FT2232H EEPROM string format (FTDI proprietary, differs from standard USB):
- String area starts at word 13 (byte 0x1A)
- Each string: 2-byte header [bLength, bType] + UTF-16LE chars (no null term)
- bType=0x03 for USB string descriptor
- bLength = total bytes including header

Layout (from reverse-engineering original EEPROM):
  word 12: 0x0056 -> ?? (V=0x56?)
  word 13: 0x0001 -> string enable flag
  word 14-20: Manufacturer string (Digilent)
  word 21-25: padding?
  word 26-33: Product string (Digilent Basys3)

Actually, FTDI uses a serial-eprom-builder format where strings are stored
contiguously with length prefixes. Let me decode by walking the string area.
"""
import struct

with open('sim/eeprom_backups/eeprom_backup_20260627_072124.bin', 'rb') as f:
    orig_data = f.read()
orig = list(struct.unpack('<' + 'H'*(len(orig_data)//2), orig_data))

with open('sim/eeprom_backups/eeprom_current_after_vid_fix.bin', 'rb') as f:
    cur_data = f.read()
cur = list(struct.unpack('<' + 'H'*(len(cur_data)//2), cur_data))

print("=== Decoding string area of ORIGINAL (Vivado OK) EEPROM ===")
print("Words 12-50 (bytes 0x18-0x64):")
for i in range(12, 50):
    lo = orig[i] & 0xff
    hi = (orig[i] >> 8) & 0xff
    c_lo = chr(lo) if 0x20 <= lo < 0x7f else '.'
    c_hi = chr(hi) if 0x20 <= hi < 0x7f else '.'
    print(f"  word {i:3d} (0x{i*2:04x}): 0x{orig[i]:04x}  lo={lo:02x}({c_lo}) hi={hi:02x}({c_hi})  cur=0x{cur[i]:04x}")

# Walk strings in FTDI format
# In FTDI EEPROM, string descriptors are stored starting after the header
# The header at word 7 contains string indices (manu/prod/ser)
# Word 9 (0x12) is "Manufacturer string offset" or similar

# Try decoding as: bLength(1 byte) + bDescriptorType(1 byte) + UTF-16LE string
print("\n=== Walking FTDI string descriptors (word 12+) ===")
# Get bytes from words 12 onwards
def words_to_bytes(words, start, count):
    bs = b''
    for w in words[start:start+count]:
        bs += struct.pack('<H', w)
    return bs

orig_bytes = words_to_bytes(orig, 12, 100)
cur_bytes = words_to_bytes(cur, 12, 100)

# Try parsing as USB string descriptors
offset = 0
str_idx = 0
while offset < len(orig_bytes) - 2:
    bLength = orig_bytes[offset]
    bType = orig_bytes[offset+1]
    if bLength == 0 or bType != 0x03:
        # Not a string descriptor, try next word
        offset += 2
        continue
    # String descriptor
    str_chars = b''
    for j in range(2, bLength, 2):
        if offset + j + 1 < len(orig_bytes):
            lo = orig_bytes[offset+j]
            hi = orig_bytes[offset+j+1]
            if hi == 0 and 0x20 <= lo < 0x7f:
                str_chars += bytes([lo])
            else:
                str_chars += f'\\x{lo:02x}{hi:02x}'.encode()
    print(f"  Str {str_idx} at byte 0x{offset+12*2:04x} (word {(offset+12*2)//2}): bLength={bLength} bType={bType}")
    print(f"    Value: '{str_chars.decode('ascii', errors='replace')}'")
    str_idx += 1
    offset += bLength

# Compare current
print("\n=== Current EEPROM string area (words 12-50) ===")
for i in range(12, 50):
    lo = cur[i] & 0xff
    hi = (cur[i] >> 8) & 0xff
    c_lo = chr(lo) if 0x20 <= lo < 0x7f else '.'
    c_hi = chr(hi) if 0x20 <= hi < 0x7f else '.'
    diff = " ***" if cur[i] != orig[i] else ""
    print(f"  word {i:3d} (0x{i*2:04x}): 0x{cur[i]:04x}  lo={lo:02x}({c_lo}) hi={hi:02x}({c_hi}){diff}")

# Check what D2XX reports
print("\n=== USB Device Descriptor (via D2XX) ===")
import ctypes
ft = ctypes.WinDLL('ftd2xx.dll')
ft.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ft.FT_Open.restype = ctypes.c_uint32
ft.FT_GetDeviceInfo.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_uint32),
                                 ctypes.POINTER(ctypes.c_uint32), ctypes.c_char_p,
                                 ctypes.c_char_p, ctypes.c_void_p]
ft.FT_GetDeviceInfo.restype = ctypes.c_uint32
ft.FT_Close.argtypes = [ctypes.c_void_p]
ft.FT_Close.restype = ctypes.c_uint32

handle = ctypes.c_void_p()
if ft.FT_Open(0, ctypes.byref(handle)) == 0:
    dev_type = ctypes.c_uint32()
    dev_id = ctypes.c_uint32()
    sn = ctypes.create_string_buffer(64)
    desc = ctypes.create_string_buffer(256)
    if ft.FT_GetDeviceInfo(handle, ctypes.byref(dev_type), ctypes.byref(dev_id),
                          sn, desc, None) == 0:
        print(f"  Type: {dev_type.value}")
        print(f"  ID: 0x{dev_id.value:08x}")
        print(f"  Serial: '{sn.value.decode('ascii', errors='replace')}'")
        print(f"  Description: '{desc.value.decode('ascii', errors='replace')}'")
    ft.FT_Close(handle)

# Compare with original board's USB descriptor
print("\n=== Expected (from original backup, Vivado OK) ===")
print(f"  Expected Product: 'Digilent Basys3'")
print(f"  Got Description: '{desc.value.decode('ascii', errors='replace')}' (above)")
