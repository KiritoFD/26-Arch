"""Analyze the current board's EEPROM in detail - focus on SN and string descriptors.

The current board (7&150bde91 instance) has:
- D2XX Desc = "Dual RS232-HS A" (not "Digilent USB Device A")
- D2XX SN = "A" (only 1 char, not 12-char "210183A8xxxx")
- Windows instance = "7&150bde91&1&3" (parent location ID, not real SN)

This suggests the SN string descriptor is corrupted or SerNumEnable is off.
"""
import struct

with open('sim/eeprom_backups/eeprom_backup_20260627_065956.bin', 'rb') as f:
    data = f.read()

words = list(struct.unpack('<' + 'H'*(len(data)//2), data))

print("=== String descriptor area (0x14 - 0x100) ===")
# Look for USB string descriptors
i = 0x14
strs = []
while i < len(data) - 2:
    if data[i+1] == 0x03 and 2 < data[i] < 60:
        length = data[i]
        if i + length <= len(data):
            s = data[i+2:i+length].decode('utf-16-le', errors='replace')
            strs.append((i, length, s))
            print(f"  @0x{i:02x} (len={length}): '{s}'")
            i += length
            continue
    i += 1

# Check the SN string specifically
print("\n=== Serial Number String ===")
for offset, length, s in strs:
    if '210183A8' in s or len(s) == 12:
        print(f"  Found SN at 0x{offset:02x}: '{s}'")
        # Show raw bytes
        raw = data[offset:offset+length]
        print(f"  Raw bytes: {' '.join(f'{b:02x}' for b in raw)}")

# Compare SN between first half (0x00-0xFF) and second half (0x100-0x1FF)
print("\n=== First half (0x00-0xFF) vs Second half (0x100-0x1FF) ===")
first = data[:0x100]
second = data[0x100:]
if first == second:
    print("  IDENTICAL (mirror copy)")
else:
    print("  DIFFERENT!")
    for i in range(0, 0x100, 2):
        if first[i] != second[i] or first[i+1] != second[i+1]:
            print(f"    @0x{i:02x}/0x{i+0x100:02x}: first=0x{first[i]:02x}{first[i+1]:02x} second=0x{second[i]:02x}{second[i+1]:02x}")

# Check D2XX SN - the Desc "Dual RS232-HS" suggests this is a GENERIC FTDI config
# not Digilent-specific. The EEPROM Product string says "Digilent USB Device"
# but D2XX returns "Dual RS232-HS" - this mismatch is suspicious.

# Let me check if there's a SECOND EEPROM or if the Desc comes from elsewhere
print("\n=== Word 5 and SerNumEnable ===")
print(f"Word 5 = 0x{words[5]:04x}")
# SerNumEnable is bit 11 of word 5 (or word 4 depending on chip)
if words[5] & (1 << 11):
    print("  SerNumEnable (bit 11) = SET")
else:
    print("  SerNumEnable (bit 11) = NOT SET")

# Also check word 4
print(f"Word 4 = 0x{words[4]:04x}")
if words[4] & (1 << 11):
    print("  Word 4 bit 11 = SET")
else:
    print("  Word 4 bit 11 = NOT SET")

# Print the full hex dump of the string area
print("\n=== Hex dump 0x14-0x60 ===")
for i in range(0x14, 0x60, 16):
    hex_str = ' '.join(f'{b:02x}' for b in data[i:i+16])
    ascii_str = ''.join(chr(b) if 32 <= b < 127 else '.' for b in data[i:i+16])
    print(f"  {i:04x}: {hex_str}  |{ascii_str}|")
