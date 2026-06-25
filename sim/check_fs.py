#!/usr/bin/env python3
import struct
import sys

with open("/mnt/g/GitHub/26-Arch/third_party/xv6-riscv/fs.img", "rb") as f:
    data = f.read()

for i in range(len(data)):
    if data[i] != 0:
        print(f"First non-zero at offset {i} (0x{i:x}), block {i//512}")
        start = max(0, i - 16)
        for j in range(start, min(len(data), i + 32), 4):
            word = struct.unpack_from('<I', data, j)[0]
            print(f"  offset {j} (0x{j:x}): {word:08x}")
        break
else:
    print("All zeros!")
