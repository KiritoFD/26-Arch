#!/usr/bin/env python3
# Regenerate xv6-kernel.coe from kernel.bin (BRAM init, depth=21000 x 64-bit)
import sys

inp = 'third_party/xv6-riscv/kernel/kernel.bin'
outp = 'vivado/xv6_project/xv6-kernel.coe'

with open(inp, 'rb') as f:
    data = f.read()

DEPTH = 21000
# Pad to DEPTH*8 bytes with zeros
need = DEPTH * 8
if len(data) < need:
    data = data + b'\x00' * (need - len(data))
else:
    data = data[:need]

with open(outp, 'w') as f:
    f.write('memory_initialization_radix = 16;\n')
    f.write('memory_initialization_vector =\n')
    for i in range(DEPTH):
        word = data[i*8:(i+1)*8]
        # 64-bit little-endian
        v = int.from_bytes(word, 'little')
        if i == DEPTH - 1:
            f.write(f'{v:016x};\n')  # last line must end with semicolon
        else:
            f.write(f'{v:016x}\n')

import os
print(f'Generated {outp}: {os.path.getsize(outp)} bytes, DEPTH={DEPTH}')
print(f'First word: {int.from_bytes(data[:8], "little"):016x}')
