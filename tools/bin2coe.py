#!/usr/bin/env python3
"""Convert a flat binary (little-endian) to a Vivado BRAM COE file.

Usage: python bin2coe.py <input.bin> <output.coe>
Each COE entry is a 64-bit hex word (8 bytes, little-endian from the binary).
"""
import sys
import struct

def main():
    if len(sys.argv) != 3:
        print("Usage: python bin2coe.py <input.bin> <output.coe>")
        sys.exit(1)

    in_path, out_path = sys.argv[1], sys.argv[2]

    with open(in_path, "rb") as f:
        data = f.read()

    # Pad to 8-byte alignment
    while len(data) % 8 != 0:
        data += b"\x00"

    with open(out_path, "w") as f:
        f.write("memory_initialization_radix = 16;\n")
        f.write("memory_initialization_vector =\n")
        for i in range(0, len(data), 8):
            word = struct.unpack_from("<Q", data, i)[0]
            f.write(f"{word:016x}\n")

    print(f"Converted {len(data)} bytes ({len(data)//8} words) -> {out_path}")

if __name__ == "__main__":
    main()
