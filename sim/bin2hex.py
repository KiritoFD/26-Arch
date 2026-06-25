#!/usr/bin/env python3
"""Convert kernel.bin to kernel_hex.txt with zero-padding for $readmemh.
Output format: one 64-bit hex word per line, little-endian byte order.
Pads to BRAM_SIZE entries (21000 = 164KB / 8 bytes per entry).
"""
import sys, os

BIN_PATH = sys.argv[1] if len(sys.argv) > 1 else None
OUT_PATH = sys.argv[2] if len(sys.argv) > 2 else None
BRAM_ENTRIES = 21000  # 164KB / 8 = 21000 64-bit words

if not BIN_PATH or not OUT_PATH:
    print(f"Usage: {sys.argv[0]} <kernel.bin> <kernel_hex.txt>")
    sys.exit(1)

with open(BIN_PATH, 'rb') as f:
    content = f.read()

print(f"Kernel binary: {len(content)} bytes ({len(content)/1024:.1f} KB)")

# Pad to 8-byte alignment
if len(content) % 8 != 0:
    content += b'\x00' * (8 - len(content) % 8)

entries = len(content) // 8
print(f"Kernel entries: {entries}")

if entries > BRAM_ENTRIES:
    print(f"ERROR: Kernel too large! {entries} > {BRAM_ENTRIES} BRAM entries")
    sys.exit(1)

with open(OUT_PATH, 'w') as f:
    for i in range(BRAM_ENTRIES):
        if i < entries:
            chunk = content[i*8:(i+1)*8]
            # Little-endian: reverse byte order within each 64-bit word
            # But store as two 32-bit words, each little-endian
            word1 = chunk[4:8][::-1]  # high 32 bits
            word2 = chunk[0:4][::-1]  # low 32 bits
            f.write(''.join(f'{b:02x}' for b in word1) + ''.join(f'{b:02x}' for b in word2) + '\n')
        else:
            f.write('0000000000000000\n')

print(f"Generated {BRAM_ENTRIES} entries -> {OUT_PATH}")
