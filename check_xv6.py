import struct
f = open('third_party/xv6-riscv/fs.img', 'rb')
d = f.read()
f.close()
print('fs.img size:', len(d), 'bytes =', len(d)//1024, 'KB')
sb = d[1024:1024+32]
magic, size, nblocks, ninodes, nlog, logstart, inodestart, bmapstart = struct.unpack('<IIIIIIII', sb)
print(f'magic=0x{magic:08x} size={size} blocks total={size*1024} bytes nblocks={nblocks} ninodes={ninodes}')
print(f'nlog={nlog} logstart={logstart} inodestart={inodestart} bmapstart={bmapstart}')
# count non-zero blocks at the tail
last_nonzero = 0
for i in range(len(d)//1024):
    blk = d[i*1024:(i+1)*1024]
    if any(b != 0 for b in blk):
        last_nonzero = i+1
print(f'last non-zero block: {last_nonzero} -> {last_nonzero*1024} bytes = {last_nonzero*1024/1024} KB')
