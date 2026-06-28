"""
裁剪 fs.img 到指定大小，fit SPI Flash 容量约束。
原 fs.img: 2MB (FSSIZE=2000 blocks × 1KB)
Flash布局: bitstream(2.09MB) @0x0 + fs.img @0x300000(3MB)
Flash总容量: 4MB
可用空间: 4MB - 3MB = 1MB = 1024KB
保留 976KB (999424 bytes = 976 blocks)，留 48KB 余量给 bitstream 增长
"""
import os
import sys

SRC = r"g:\GitHub\26-Arch\third_party\xv6-riscv\fs.img"
DST = r"g:\GitHub\26-Arch\third_party\xv6-riscv\fs_trim.img"

# 976 KB = 999424 bytes = 976 blocks × 1024 bytes
TRIM_SIZE = 976 * 1024

src_size = os.path.getsize(SRC)
print(f"Source fs.img: {src_size} bytes ({src_size//1024} KB)")

if src_size <= TRIM_SIZE:
    print(f"Source already <= {TRIM_SIZE}, no trim needed")
    sys.exit(0)

with open(SRC, "rb") as fsrc, open(DST, "wb") as fdst:
    data = fsrc.read(TRIM_SIZE)
    fdst.write(data)

dst_size = os.path.getsize(DST)
print(f"Trimmed fs_trim.img: {dst_size} bytes ({dst_size//1024} KB)")

# 验证：检查尾部是否全 0（空闲区域）
with open(DST, "rb") as f:
    f.seek(TRIM_SIZE - 1024)
    tail = f.read(1024)
    if all(b == 0 for b in tail):
        print("OK: tail 1KB all zeros (trimmed region was free space)")
    else:
        non_zero = sum(1 for b in tail if b != 0)
        print(f"WARNING: tail 1KB has {non_zero} non-zero bytes")

print(f"DST_PATH={DST}")
