#!/usr/bin/env python3

import os

BITSTREAM_PATH = r'G:\GitHub\26-Arch\vivado\test-cpu\project\project_3\project_3.runs\impl_1\basys3_top.bit'
FS_IMG_PATH = r'G:\GitHub\26-Arch\third_party\xv6-riscv\fs.img'
OUTPUT_PATH = r'G:\GitHub\26-Arch\vivado\test-cpu\project\project_3\full_flash.bin'

FS_OFFSET = 0x00400000
FLASH_SIZE = 32 * 1024 * 1024

print(f"Creating full flash image...")
print(f"  Bitstream: {BITSTREAM_PATH}")
print(f"  fs.img: {FS_IMG_PATH}")
print(f"  Output: {OUTPUT_PATH}")
print(f"  fs.img offset: 0x{FS_OFFSET:08X}")

with open(BITSTREAM_PATH, 'rb') as f:
    bitstream_data = f.read()

with open(FS_IMG_PATH, 'rb') as f:
    fs_data = f.read()

print(f"  Bitstream size: {len(bitstream_data)} bytes")
print(f"  fs.img size: {len(fs_data)} bytes")

full_flash = bytearray(FLASH_SIZE)

full_flash[:len(bitstream_data)] = bitstream_data

full_flash[FS_OFFSET:FS_OFFSET + len(fs_data)] = fs_data

with open(OUTPUT_PATH, 'wb') as f:
    f.write(full_flash)

print(f"  Full flash image size: {len(full_flash)} bytes")
print(f"  Done!")