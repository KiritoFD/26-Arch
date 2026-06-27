"""Read the FULL FT2232H EEPROM (could be 128 or 256 words depending on chip)."""
import ctypes
import struct

ftd2xx = ctypes.windll.FTD2XX
ftd2xx.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ftd2xx.FT_Open.restype = ctypes.c_uint32
ftd2xx.FT_Close.argtypes = [ctypes.c_void_p]
ftd2xx.FT_Close.restype = ctypes.c_uint32
ftd2xx.FT_ReadEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint16)]
ftd2xx.FT_ReadEE.restype = ctypes.c_uint32

handle = ctypes.c_void_p()
status = ftd2xx.FT_Open(0, ctypes.byref(handle))
if status != 0:
    print(f"FT_Open failed: {status}")
    exit(1)

# Read up to 256 words (FT2232H EEPROM is typically 4Kbits = 256 words = 512 bytes)
words = []
for i in range(256):
    w = ctypes.c_uint16()
    s = ftd2xx.FT_ReadEE(handle, i, ctypes.byref(w))
    if s != 0:
        print(f"FT_ReadEE failed at word {i}: {s}")
        break
    words.append(w.value)

ftd2xx.FT_Close(handle)

print(f"Read {len(words)} words")

# Find non-zero region
last_nz = 0
for i, w in enumerate(words):
    if w != 0:
        last_nz = i
print(f"Last non-zero word: {last_nz} (offset 0x{last_nz*2:04x})")

# Print all non-zero parts
print("\nFull dump:")
for i in range(0, len(words), 8):
    if i > last_nz + 7:
        break
    hex_str = ' '.join(f'{words[j]:04x}' for j in range(i, min(i+8, len(words))))
    print(f"  {i*2:04x}: {hex_str}")

# Save full dump
with open('eeprom_full.bin', 'wb') as f:
    for w in words:
        f.write(struct.pack('<H', w))
print(f"\nSaved {len(words)*2} bytes to eeprom_full.bin")

# Now try checksums on full data
target_full = words[-1] if len(words) >= 256 else words[127]
print(f"\nChecksum candidate (last word): 0x{target_full:04x}")

# Try various lengths and algorithms
target_word_127 = words[127] if len(words) > 127 else 0
target_word_255 = words[255] if len(words) > 255 else 0
print(f"Word 127 (offset 0xFE): 0x{target_word_127:04x}")
print(f"Word 255 (offset 0x1FE): 0x{target_word_255:04x}")

# For each potential end word, try XOR and sum-based checksums
for end_word in [127, 191, 255]:
    if end_word >= len(words):
        continue
    target = words[end_word]
    print(f"\n--- Trying with checksum at word {end_word} (target=0x{target:04x}) ---")
    # XOR
    cs = 0
    for w in words[:end_word]:
        cs ^= w
    print(f"  XOR of words 0..{end_word-1}: 0x{cs:04x} match={cs==target}")
    # Sum
    cs_sum = sum(words[:end_word]) & 0xFFFF
    print(f"  Sum of words 0..{end_word-1}: 0x{cs_sum:04x} match={cs_sum==target}")
    cs_neg = (0x10000 - cs_sum) & 0xFFFF
    print(f"  -Sum: 0x{cs_neg:04x} match={cs_neg==target}")
    # Byte-level
    all_bytes = []
    for w in words[:end_word]:
        all_bytes.append(w & 0xFF)
        all_bytes.append((w >> 8) & 0xFF)
    cs_b = sum(all_bytes) & 0xFFFF
    print(f"  Sum of bytes: 0x{cs_b:04x} match={cs_b==target}")
    cs_b_neg = (~sum(all_bytes) + 1) & 0xFFFF
    print(f"  -bytes (two's complement): 0x{cs_b_neg:04x} match={cs_b_neg==target}")
