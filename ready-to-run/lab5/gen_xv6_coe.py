#!/usr/bin/env python3
"""Convert xv6 kernel binary to BRAM COE file for Vivado."""

import sys

def bin_to_coe(bin_path, coe_path, depth=21000):
    with open(bin_path, "rb") as f:
        content = f.read()

    # Pad to 8-byte alignment
    while len(content) % 8 != 0:
        content += b'\x00'

    lines = []
    for i in range(0, len(content), 8):
        chunk = content[i:i+8]
        # Little-endian: swap 4-byte halves, reverse each half
        hex1 = ''.join(f'{b:02x}' for b in chunk[4:8][::-1])
        hex2 = ''.join(f'{b:02x}' for b in chunk[0:4][::-1])
        lines.append(hex1 + hex2)

    # Pad to BRAM depth with zeros
    while len(lines) < depth:
        lines.append("0000000000000000")

    with open(coe_path, "w") as f:
        f.write("memory_initialization_radix = 16;\n")
        f.write("memory_initialization_vector =\n")
        for i, line in enumerate(lines):
            if i == len(lines) - 1:
                f.write(line + ";\n")
            else:
                f.write(line + "\n")

    print(f"Generated {coe_path} with {len(lines)} entries ({len(content)} bytes)")

if __name__ == "__main__":
    bin_path = sys.argv[1] if len(sys.argv) > 1 else "kernel.bin"
    coe_path = sys.argv[2] if len(sys.argv) > 2 else "xv6-kernel.coe"
    depth = int(sys.argv[3]) if len(sys.argv) > 3 else 21000
    bin_to_coe(bin_path, coe_path, depth)
