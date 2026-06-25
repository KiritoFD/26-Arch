#!/usr/bin/env python3
"""Convert Xilinx .coe file to hex format for $readmemh"""

import sys
import re

def coe2hex(input_file, output_file):
    with open(input_file, 'r') as f:
        lines = f.readlines()

    # Find the start of data (after memory_initialization_vector =)
    data_started = False
    hex_values = []

    for line in lines:
        line = line.strip()
        if not line:
            continue
        if line.startswith('memory_initialization_radix'):
            continue
        if line.startswith('memory_initialization_vector'):
            data_started = True
            # Check if there's data on the same line after '='
            parts = line.split('=', 1)
            if len(parts) > 1:
                val = parts[1].strip().rstrip(';').strip()
                if val:
                    hex_values.append(val)
            continue
        if data_started:
            # Remove trailing semicolons and commas
            val = line.rstrip(';').rstrip(',').strip()
            if val:
                hex_values.append(val)

    with open(output_file, 'w') as f:
        for val in hex_values:
            f.write(val + '\n')

    print(f"Converted {len(hex_values)} entries from {input_file} to {output_file}")

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <input.coe> <output.hex>")
        sys.exit(1)
    coe2hex(sys.argv[1], sys.argv[2])
