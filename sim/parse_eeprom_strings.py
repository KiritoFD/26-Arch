"""Parse FT2232H EEPROM strings (full layout)."""
import struct

with open('eeprom_dump_current.bin', 'rb') as f:
    data = f.read()

words = struct.unpack('<' + 'H'*(len(data)//2), data)
print(f"Total words: {len(words)}")
print()
print("Raw hex dump (first 0x80 bytes):")
for i in range(0, 0x80, 16):
    hex_part = ' '.join(f'{b:02x}' for b in data[i:i+16])
    ascii_part = ''.join(chr(b) if 32 <= b < 127 else '.' for b in data[i:i+16])
    print(f"  {i:04x}: {hex_part}  |{ascii_part}|")

print()
print("Strings area (offset 0x14 = word 10 onwards):")
# FT2232H string descriptor format:
# Each string: 2 bytes (length+type header) + ascii chars (UTF-16LE)
# Word 9: Manufacturer string offset
# Word 10: Manufacturer string (chars, 2 per word)
# Word 11: Product string offset
# Word 12: Product string
# Word 13: Serial string offset
# Word 14: Serial string

# Actually FT2232H uses raw bytes starting at word 9 (0x12 offset)
# Format: first byte = string length (in bytes incl header), 0x03 = UTF-16 type
# Then UTF-16LE chars

# Look at offsets 0x14+ for strings
str_data = data[0x14:]
print(f"String area (from 0x14, {len(str_data)} bytes):")
for i in range(0, min(len(str_data), 64), 16):
    hex_part = ' '.join(f'{b:02x}' for b in str_data[i:i+16])
    ascii_part = ''.join(chr(b) if 32 <= b < 127 else '.' for b in str_data[i:i+16])
    print(f"  +{i:02x}: {hex_part}  |{ascii_part}|")

# Try to extract UTF-16 strings
print()
print("=== Extracted UTF-16LE strings ===")
# Skip first 2 bytes (length+type header), then UTF-16LE
# Typical format: LL 03 <utf16 chars>
i = 0
strs = []
while i < len(str_data) - 2:
    if str_data[i+1] == 0x03 and str_data[i] > 2:  # 0x03 = string descriptor type, length > 2
        length = str_data[i]
        end = i + length
        if end <= len(str_data):
            s = str_data[i+2:end].decode('utf-16-le', errors='replace')
            print(f"  Offset +0x{i:02x}: '{s}' (len={length})")
            strs.append((i, s))
        i = end
    else:
        i += 1

# Check channel type word (word 3, offset 0x06)
print()
print(f"Word 3 (channel types): 0x{words[3]:04x}")
print(f"  Channel A type: {words[3] & 0xFF} (0=UART, 1=FIFO, 2=CPUFIFO, 4=OPTO, 0x40=1284)")
print(f"  Channel B type: {(words[3] >> 8) & 0xFF}")
