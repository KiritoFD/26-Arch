#!/usr/bin/env python3
"""Convert fs.img to disk_hex.txt for Verilator simulation.

Each line is a 32-bit hex word (little-endian), matching sim_disk_mem layout.
sim_disk_mem has 256000 entries (1000KB = 2000 blocks of 512 bytes).
"""
import sys
import struct

DISK_ENTRIES = 256000  # 1000KB / 4 bytes per word

def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <fs.img> <disk_hex.txt>")
        sys.exit(1)

    input_path = sys.argv[1]
    output_path = sys.argv[2]

    with open(input_path, 'rb') as f:
        data = f.read()

    print(f"fs.img size: {len(data)} bytes = {len(data) // 512} blocks")

    # Convert to 32-bit little-endian words
    num_words = len(data) // 4
    words = []
    for i in range(num_words):
        word = struct.unpack_from('<I', data, i * 4)[0]
        words.append(word)

    # Pad to DISK_ENTRIES
    if len(words) > DISK_ENTRIES:
        print(f"ERROR: fs.img too large ({len(words)} words > {DISK_ENTRIES} entries)")
        sys.exit(1)

    print(f"Writing {len(words)} words + {DISK_ENTRIES - len(words)} padding to {output_path}")

    with open(output_path, 'w') as f:
        for i in range(DISK_ENTRIES):
            if i < len(words):
                f.write(f"{words[i]:08x}\n")
            else:
                f.write("00000000\n")

if __name__ == '__main__':
    main()
