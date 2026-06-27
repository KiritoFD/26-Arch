"""Analyze FT2232H EEPROM string layout - find exact offsets to modify.

FT2232H EEPROM layout (from FTDI AN_232B-01):
- Word 0 (0x00): VID (0x0403)
- Word 1 (0x02): PID (0x6010)
- Word 2 (0x04): Device release (bcdDevice, 0x0700 = rev 7.00)
- Word 3 (0x06): Config: low byte = Channel A type, high byte = Channel B type
- Word 4 (0x08): USB power: bit 0=bus powered, bit 2=remote wakeup, MaxPowerUnit*2 mA
- Word 5 (0x0A): Misc options: bit 0=use ext oscillator, bit 1=high drive I/O, ...
- Word 6 (0x0C): (FT2232H) Channel A/SerNum enable bits (later chips)
- Word 7 (0x0E): (FT2232H) Channel B options
- Then string descriptors starting at word 9 (0x12)

String format (FT2232H style, raw bytes, NOT USB descriptor format):
- Word 9 (0x12): <unused? or length>
- Word 10 (0x14): Manufacturer string (UTF-16LE)
- Word 11 (0x16): ... continuation
- etc.

Looking at the dump:
  0010: ac 28 d4 1a 00 00 00 00 56 00 01 00 c7 92 6a 35
  0020: 51 01 70 01 42 61 73 79 73 33 00 00 00 00 00 00
  0030: 00 00 00 00 00 44 69 67 69 6c 65 6e 74 20 42 61
  0040: 73 79 73 33 00 00 00 00 00 00 00 00 00 00 00 00

Words at 0x14-0x17 (strings area starts here):
word 9  (0x12) = 0x1ad4 ?  (28 ac)
word 10 (0x14) = 0x0000
word 11 (0x16) = 0x0000
word 12 (0x18) = 0x0056  -> 'V' low byte, 0 high
word 13 (0x1a) = 0x0001
word 14 (0x1c) = 0x92c7
word 15 (0x1e) = 0x356a  -> 'j5'
word 16 (0x20) = 0x0151
word 17 (0x22) = 0x0170
word 18 (0x24) = 0x6142  -> 'Ba'  <- "Basys3"
word 19 (0x26) = 0x7973  -> 'sy'
word 20 (0x28) = 0x3373  -> 's3'
...

So "Basys3" is the Manufacturer string (at word 18 = offset 0x24)
And "Digilent Basys3" is the Product string (at word 21 = offset 0x2A? Let's check)

word 21 (0x2A) = 0x0000
word 22 (0x2C) = 0x0000
word 23 (0x2E) = 0x0000
word 24 (0x30) = 0x0000
word 25 (0x32) = 0x4400  -> '.D'   but where's the length?
word 26 (0x34) = 0x6769  -> 'ig'
word 27 (0x36) = 0x6c69  -> 'il'
word 28 (0x38) = 0x6e65  -> 'en'
word 29 (0x3A) = 0x2074  -> 't '
word 30 (0x3C) = 0x6142  -> 'Ba'
word 31 (0x3E) = 0x7973  -> 'ys'
word 32 (0x40) = 0x3373  -> 's3'
...

Hmm, "Digilent Basys3" is at offset 0x33 (byte 0x33='D', 0x34='i', ...)
Actually that's odd-aligned. Let me recheck.

Actually looking again at 0x30 row:
  0030: 00 00 00 00 00 44 69 67 69 6c 65 6e 74 20 42 61

offset 0x35 = 'D', 0x36='i', 0x37='g', ..., 0x43='a' (end "Basys3" at 0x43)

Hmm, but strings in FT2232H EEPROM are typically:
- 1 byte length (in bytes including header)
- 1 byte descriptor type (0x03)
- UTF-16LE chars

So at 0x35: byte 0x35=0x44='D' (not 0x03 type)
That doesn't match USB descriptor format.

Actually FTDI's older EEPROM format uses RAW ASCII (not USB descriptor format).
The format is:
- word N: length of string 1 (1 byte) + 1 byte 0x00 + UTF-16LE chars...

Let me look at the data more carefully.
"""

import struct

with open('eeprom_dump_current.bin', 'rb') as f:
    data = f.read()

words = struct.unpack('<' + 'H'*(len(data)//2), data)

# Look for "Basys3" - found at word 18 (offset 0x24)
# Basys3 = B(0x42) a(0x61) s(0x73) y(0x79) s(0x73) 3(0x33)
# As UTF-16LE: 42 00 61 00 73 00 79 00 73 00 33 00 (12 bytes)
# But we see: 42 61 73 79 73 33 (6 bytes, ASCII packed!)

# So FTDI uses ASCII-packed, NOT UTF-16
# Each word holds 2 ASCII chars (low byte first)

# "Basys3" = 6 chars = 3 words, starting at word 18 (offset 0x24)
# word 18 = 0x6142 = 'a'<<8 | 'B'  -> "Ba"
# word 19 = 0x7973 = 'y'<<8 | 's'  -> "sy"
# word 20 = 0x3373 = '3'<<8 | 's'  -> "s3"

# "Digilent Basys3" = 15 chars, padded to 16 = 8 words, starting at word 25 (offset 0x32)
# word 25 = 0x4400 = 'D'<<8 | 0x00  -> "\0D" - hmm, first byte is 0x00?

# Actually look at offset 0x32:
# 0030: 00 00 00 00 00 44 69 67 69 6c 65 6e 74 20 42 61
# offset 0x32 = 0x00, 0x33 = 0x00, 0x34 = 0x00, 0x35 = 0x44='D' ...
# That's strange. Maybe word 25 (0x32) is 0x0000, word 26 (0x34) is 0x6900 = 'i\0'?

# Wait, let me re-read. Offset 0x32 = word 25 (0x32/2 = 25).
# Bytes at 0x32-0x33: 00 00 -> word 0x0000
# Bytes at 0x34-0x35: 69 67 -> word 0x6769 = 'ig' (i first, g second)
# But that doesn't spell "Digilent"...

# Let me look at the byte-level for the product string:
print("Byte-level view (offsets 0x20-0x50):")
for i in range(0x20, 0x50, 2):
    b0, b1 = data[i], data[i+1]
    c0 = chr(b0) if 32 <= b0 < 127 else '.'
    c1 = chr(b1) if 32 <= b1 < 127 else '.'
    print(f"  0x{i:02x}: {b0:02x} {b1:02x}  ({c0}{c1})")

# The "Digilent Basys3" string as ASCII: D-i-g-i-l-e-n-t-space-B-a-s-y-s-3
# Hex: 44 69 67 69 6c 65 6e 74 20 42 61 73 79 73 33 00

# In EEPROM (ASCII packed, 2 chars per word, low byte first):
# "Di" -> 0x6944
# "gi" -> 0x6967
# "le" -> 0x656c
# "nt" -> 0x746e
# " B" -> 0x4220
# "as" -> 0x7361
# "ys" -> 0x7379
# "s3" -> 0x3333
# That's 8 words = 16 bytes (with trailing \0)

# Looking at the dump, those bytes ARE at offset 0x35-0x44:
# 0x35: 44 69 67 69 6c 65 6e 74 20 42 61 73 79 73 33 00

# But word-aligned would be at 0x34 or 0x36, not 0x35
# This is because FTDI EEPROM string format includes a 1-byte length prefix

# Actually, looking at the older FTDI format (FT_SetEEPROMSize/FT_ProgramEEPROM):
# Format: <length byte> <string chars...>
# So at 0x34 might be: 0x10 (length=16 bytes) then "Digilent Basys3\0"
# Let's check byte 0x34: it's 0x67='g'... no that's not length

# Actually the string table starts at word 9 (0x12) in FT2232H.
# Let me look at the structure:
# Word 9 (0x12): 0x1ad4 - this might be a checksum or string table length

# Let me try interpreting: the FT2232H EEPROM has the following structure
# for strings:
# - Word 9: unused/checksum
# - Words 10-...: string data

# But actually, the format depends on the chip. For FT2232H, the strings
# are stored as ASCII (not UTF-16) starting at word 10 (0x14).

# Let me search for the string boundaries by looking for non-zero runs
print("\nNon-zero regions in string area (0x14+):")
i = 0x14
while i < 0x80:
    if data[i] != 0:
        start = i
        while i < 0x80 and (data[i] != 0 or (i+1 < 0x80 and data[i+1] != 0)):
            i += 1
        end = i
        s = data[start:end].decode('ascii', errors='replace')
        # Also show as UTF-16 if even length
        if (end - start) % 2 == 0:
            try:
                s16 = data[start:end].decode('utf-16-le', errors='replace')
                print(f"  0x{start:02x}-0x{end:02x}: ASCII='{s}' UTF16='{s16}'")
            except:
                print(f"  0x{start:02x}-0x{end:02x}: ASCII='{s}'")
        else:
            print(f"  0x{start:02x}-0x{end:02x}: ASCII='{s}'")
    else:
        i += 1

# Key question: what does word 12 (0x18) = 0x0056 mean?
# 'V' = 0x56. Could be a "VendorID" indicator? Or a string count?
# Let me look at the FTDI FT2232H EEPROM programmer's guide format.
# Word 12 = 0x0056 = 86 decimal. Could be 0x56='V'... probably not.

# Actually for FT2232H, word 12 is the "Manufacturer string offset" (in bytes from start of strings)
# Or it might be a different meaning. Let me check the FTDI docs more carefully.

# From FTDI AN_135 FTDI FT2232H EEPROM:
# Word 0: VID
# Word 1: PID
# Word 2: bcdDevice
# Word 3: Config (A type, B type)
# Word 4: USB power attributes
# Word 5: Misc options
# Word 6: Driver blocks for channel B
# Word 7: Not used in FT2232H (used in FT4232H)
# Word 8: Not used in FT2232H
# Word 9-63: String descriptors

# String format in FT2232H EEPROM (older ASCII format):
# - Byte 0: string length (in bytes, NOT including length byte)
# - Then ASCII chars (1 byte per char, NOT UTF-16)
# - Padded to word boundary

# So strings start at word 9 (0x12):
# Word 9 (0x12) = 0x1ad4... that doesn't look like a length byte

# Let me try: word 9 (0x12) is NOT a string - it's something else
# Maybe the string starts at word 12 (0x18)?
print("\nTrying interpretation: strings start at word 12 (0x18)")
print(f"Word 12 (0x18) = 0x{words[12]:04x} = bytes {data[0x18]:02x} {data[0x19]:02x}")
print(f"Word 13 (0x1a) = 0x{words[13]:04x} = bytes {data[0x1a]:02x} {data[0x1b]:02x}")

# Actually looking at the dump, 0x18 = 0x56 0x00, 0x1a = 0x01 0x00
# 0x56='V', 0x01=^A... probably not a string

# Let me check word 9 onwards more carefully
print("\nWord-by-word from word 9 (0x12):")
for w in range(9, 40):
    offset = w * 2
    if offset < len(data):
        b0 = data[offset]
        b1 = data[offset+1] if offset+1 < len(data) else 0
        c0 = chr(b0) if 32 <= b0 < 127 else '.'
        c1 = chr(b1) if 32 <= b1 < 127 else '.'
        print(f"  word {w:2d} (0x{offset:02x}): 0x{words[w]:04x}  bytes {b0:02x} {b1:02x}  ({c0}{c1})")
