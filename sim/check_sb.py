#!/usr/bin/env python3
import struct
with open("/mnt/g/GitHub/26-Arch/third_party/xv6-riscv/fs.img", "rb") as f:
    f.seek(1024)
    data = f.read(16)
    print("Raw bytes at offset 1024:", data.hex())
    for i in range(4):
        w = struct.unpack_from('<I', data, i*4)[0]
        print(f"  word[{256+i}] = {w:08x}")
