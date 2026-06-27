"""Find the FT2232H EEPROM checksum algorithm.

Looking at the data:
- 0x0095-0x00fe: USB string descriptors (3 strings: Mfr, Product, Serial)
- 0x00fe: 0x2947 (checksum word)

The string descriptor table is at offset 0x96 onwards.
Before that (words 0-0x47 = 0x00-0x8f), we have the FT2232H config area.

The checksum is in the last word (word 0x7F = offset 0xFE).

FTDI's FT2232H uses a 16-bit checksum. Let me try several algorithms.
"""
import struct

with open('eeprom_dump_current.bin', 'rb') as f:
    data = f.read()

words = struct.unpack('<' + 'H'*(len(data)//2), data)
print(f"Total words: {len(words)} (expected 128, got {len(words)})")

# If we got 128 words but file has 256 bytes, that's correct
# Wait, file is 128 words = 256 bytes. But our backup_eeprom.py read 128 words too.
# Let me check actual data length

# Find non-zero region
last_nonzero = 0
for i, w in enumerate(words):
    if w != 0:
        last_nonzero = i
print(f"Last non-zero word: {last_nonzero} (offset 0x{last_nonzero*2:02x})")
print(f"Checksum word (last): 0x{words[-1]:04x}")

# Try various checksum algorithms
target = words[-1]  # 0x2947

# Algo 1: 16-bit XOR of all words except last
cs = 0
for w in words[:-1]:
    cs ^= w
print(f"\nAlgo 1 (XOR all): 0x{cs:04x} match={cs==target}")

# Algo 2: 16-bit sum of all words except last
cs = 0
for w in words[:-1]:
    cs = (cs + w) & 0xFFFF
print(f"Algo 2 (sum all): 0x{cs:04x} match={cs==target}")

# Algo 3: 0x10000 - sum (two's complement)
cs = (0x10000 - sum(words[:-1])) & 0xFFFF
print(f"Algo 3 (0x10000-sum): 0x{cs:04x} match={cs==target}")

# Algo 4: sum of bytes (not words)
cs = 0
for w in words[:-1]:
    cs = (cs + (w & 0xFF) + ((w >> 8) & 0xFF)) & 0xFFFF
print(f"Algo 4 (sum bytes): 0x{cs:04x} match={cs==target}")

# Algo 5: two's complement of sum of bytes
cs = (0x10000 - sum((w & 0xFF) + ((w >> 8) & 0xFF) for w in words[:-1])) & 0xFFFF
print(f"Algo 5 (~sum bytes): 0x{cs:04x} match={cs==target}")

# Algo 6: FTDI algorithm from FT2232H reference (subtractive)
# checksum = 0xFFFF - sum(bytes) + 1 (for first byte)
cs = 0xFFFF
for w in words[:-1]:
    lo = w & 0xFF
    hi = (w >> 8) & 0xFF
    cs = (cs - lo - hi) & 0xFFFF
print(f"Algo 6 (subtract bytes from 0xFFFF): 0x{cs:04x} match={cs==target}")

# Algo 7: FTDI algorithm from libftdi source (XOR with carry)
# checksum = XOR of all bytes, with carry propagation
cs = 0
for w in words[:-1]:
    lo = w & 0xFF
    hi = (w >> 8) & 0xFF
    cs = (cs + lo + hi) & 0xFFFF
# Inverse
cs_inv = (~cs + 1) & 0xFFFF
print(f"Algo 7 (~sum bytes +1): 0x{cs_inv:04x} match={cs_inv==target}")
print(f"  (raw sum: 0x{cs:04x})")

# Algo 8: 0xAAAA - sum (FTDI's algorithm for some chips)
cs = (0xAAAA - sum(words[:-1])) & 0xFFFF
print(f"Algo 8 (0xAAAA - sum): 0x{cs:04x} match={cs==target}")

# Algo 9: Just last word is XOR of all preceding (16-bit)
# Already algo 1.

# Algo 10: Sum of all preceding bytes
all_bytes = []
for w in words[:-1]:
    all_bytes.append(w & 0xFF)
    all_bytes.append((w >> 8) & 0xFF)
cs_byte_sum = sum(all_bytes) & 0xFF
print(f"\nAlgo 10 (byte sum low 8 bits): 0x{cs_byte_sum:02x}")
print(f"  target low byte: 0x{target & 0xFF:02x}")
print(f"  target high byte: 0x{(target >> 8) & 0xFF:02x}")

# Try with 16-bit byte sum
cs = sum(all_bytes) & 0xFFFF
print(f"Algo 10b (16-bit byte sum): 0x{cs:04x} match={cs==target}")
cs = (~sum(all_bytes)) & 0xFFFF
print(f"Algo 10c (~byte sum): 0x{cs:04x} match={cs==target}")
cs = (~sum(all_bytes) + 1) & 0xFFFF
print(f"Algo 10d (~byte sum +1): 0x{cs:04x} match={cs==target}")

# Let me also check: maybe the checksum is over a subset of words, not all
# For example, maybe it's just the string descriptor area (0x96-0xfd)
print("\n--- Trying checksums over different ranges ---")
for start_w, end_w in [(0, 127), (0, 0x47), (0x48, 0x7E), (0x96//2, 0x7E)]:
    sub = words[start_w:end_w+1]
    cs_xor = 0
    for w in sub:
        cs_xor ^= w
    cs_sum = sum(sub) & 0xFFFF
    cs_sub = (0x10000 - sum(sub)) & 0xFFFF
    print(f"  words[{start_w}..{end_w}]: XOR=0x{cs_xor:04x}  sum=0x{cs_sum:04x}  -sum=0x{cs_sub:04x}")
