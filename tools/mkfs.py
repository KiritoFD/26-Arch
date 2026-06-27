#!/usr/bin/env python3
"""
mkfs.py - Generate xv6 fs.img from user programs (Python port of mkfs.c).

Usage: python mkfs.py <output fs.img> <README> <user_program1> [user_program2 ...]

Disk layout: [ boot | super | log | inode | bitmap | data ]
- BSIZE = 1024
- FSSIZE = 1000 blocks (= 1 MB)
- NINODES = 32
- LOGBLOCKS = 11 (nlog = LOGBLOCKS + 1 = 12)
"""
import sys
import struct
import os

BSIZE = 1024
FSSIZE = 1000
NINODES = 32
LOGBLOCKS = 11
FSMAGIC = 0x10203040
ROOTINO = 1
NDIRECT = 12
NINDIRECT = BSIZE // 4   # 256
MAXFILE = NDIRECT + NINDIRECT
DIRSIZ = 14

# Inode types
T_DIR = 1
T_FILE = 2
T_DEVICE = 3

# struct superblock: 8 * uint32 = 32 bytes
SB_FMT = '<IIIIIIII'

# struct dinode: short type, major, minor, nlink; uint size; uint[13] addrs
# Layout: 4 shorts (8 bytes) + 1 uint (4 bytes) + 13 uints (52 bytes) = 64 bytes
# Format: 4 h/H + 14 I (size + addrs[13])
DINODE_FMT = '<hhhH' + 'I' * 14   # 4 shorts + 14 uints = 8 + 56 = 64 bytes
DINODE_SIZE = struct.calcsize(DINODE_FMT)
assert DINODE_SIZE == 64, f"dinode size = {DINODE_SIZE}"

# struct dirent: ushort inum + char[14] name = 16 bytes
DIRENT_FMT = '<H14s'
DIRENT_SIZE = struct.calcsize(DIRENT_FMT)
assert DIRENT_SIZE == 16

IPB = BSIZE // DINODE_SIZE    # 16
BPB = BSIZE * 8               # 8192

def xshort(x):
    return struct.unpack('<H', struct.pack('<H', x))[0]

def xint(x):
    return struct.unpack('<I', struct.pack('<I', x))[0]

def main():
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} <fs.img> <README> <user_prog1> [user_prog2 ...]")
        sys.exit(1)

    fsimg_path = sys.argv[1]
    readme_path = sys.argv[2]
    user_progs = sys.argv[3:]

    nlog = LOGBLOCKS + 1     # 12 (header + 11 data)
    ninodeblocks = NINODES // IPB + 1   # 32/16 + 1 = 3
    nbitmap = FSSIZE // BPB + 1          # 1000/8192 + 1 = 1
    nmeta = 2 + nlog + ninodeblocks + nbitmap  # 2 + 12 + 3 + 1 = 18
    nblocks = FSSIZE - nmeta             # 982

    sb = struct.pack(SB_FMT,
        FSMAGIC,       # magic
        FSSIZE,        # size
        nblocks,       # nblocks
        NINODES,       # ninodes
        nlog,          # nlog
        2,             # logstart
        2 + nlog,              # inodestart (14)
        2 + nlog + ninodeblocks  # bmapstart (17)
    )

    print(f"nmeta={nmeta} (boot, super, log blocks={nlog}, inode blocks={ninodeblocks}, bitmap blocks={nbitmap}) blocks={nblocks} total={FSSIZE}")
    print(f"sb: magic=0x{FSMAGIC:x} size={FSSIZE} nblocks={nblocks} ninodes={NINODES} nlog={nlog} logstart=2 inodestart={2+nlog} bmapstart={2+nlog+ninodeblocks}")

    # Disk image: list of BSIZE-byte blocks
    disk = [bytearray(BSIZE) for _ in range(FSSIZE)]

    # Block 1: superblock
    disk[1][:len(sb)] = sb

    freeinode = 1
    freeblock = nmeta   # first free data block

    def rsect(sec):
        return bytes(disk[sec])

    def wsect(sec, data):
        assert len(data) == BSIZE, f"wsect: data len = {len(data)}"
        disk[sec] = bytearray(data)

    def winode(inum, ip):
        # ip is a dict with type, major, minor, nlink, size, addrs[13]
        bn = inum // IPB + (2 + nlog)
        buf = bytearray(rsect(bn))
        off = (inum % IPB) * DINODE_SIZE
        # Pack: 4 shorts (type, major, minor, nlink) + 14 uints (size + addrs[13])
        packed = struct.pack(DINODE_FMT,
            ip['type'] & 0xFFFF, ip['major'] & 0xFFFF, ip['minor'] & 0xFFFF, ip['nlink'] & 0xFFFF,
            ip['size'] & 0xFFFFFFFF,
            *[a & 0xFFFFFFFF for a in ip['addrs']])
        buf[off:off+DINODE_SIZE] = packed
        wsect(bn, bytes(buf))

    def rinode(inum):
        bn = inum // IPB + (2 + nlog)
        buf = rsect(bn)
        off = (inum % IPB) * DINODE_SIZE
        fields = struct.unpack(DINODE_FMT, buf[off:off+DINODE_SIZE])
        # fields: (type, major, minor, nlink, size, addrs[0..12])
        return {
            'type': fields[0], 'major': fields[1], 'minor': fields[2], 'nlink': fields[3],
            'size': fields[4],
            'addrs': list(fields[5:18])   # 13 addr entries
        }

    def ialloc(type_):
        nonlocal freeinode
        inum = freeinode
        freeinode += 1
        din = {
            'type': type_, 'major': 0, 'minor': 0, 'nlink': 1, 'size': 0,
            'addrs': [0]*13
        }
        winode(inum, din)
        return inum

    def iappend(inum, data):
        nonlocal freeblock
        din = rinode(inum)
        off = din['size']
        p = 0
        n = len(data)
        while n > 0:
            fbn = off // BSIZE
            assert fbn < MAXFILE, f"fbn={fbn} >= MAXFILE={MAXFILE}"
            if fbn < NDIRECT:
                if din['addrs'][fbn] == 0:
                    din['addrs'][fbn] = freeblock
                    freeblock += 1
                x = din['addrs'][fbn]
            else:
                if din['addrs'][NDIRECT] == 0:
                    din['addrs'][NDIRECT] = freeblock
                    freeblock += 1
                indirect_buf = bytearray(rsect(din['addrs'][NDIRECT]))
                indirect = list(struct.unpack(f'<{NINDIRECT}I', bytes(indirect_buf)))
                if indirect[fbn - NDIRECT] == 0:
                    indirect[fbn - NDIRECT] = freeblock
                    freeblock += 1
                    packed = struct.pack(f'<{NINDIRECT}I', *indirect)
                    indirect_buf = bytearray(packed)
                    wsect(din['addrs'][NDIRECT], bytes(indirect_buf))
                x = indirect[fbn - NDIRECT]
            n1 = min(n, (fbn + 1) * BSIZE - off)
            buf = bytearray(rsect(x))
            buf[off - (fbn * BSIZE):off - (fbn * BSIZE) + n1] = data[p:p+n1]
            wsect(x, bytes(buf))
            n -= n1
            off += n1
            p += n1
        din['size'] = off
        winode(inum, din)

    # Create root directory
    rootino = ialloc(T_DIR)
    assert rootino == ROOTINO, f"rootino={rootino} != ROOTINO={ROOTINO}"

    de = struct.pack(DIRENT_FMT, rootino, b'.' + b'\x00' * 13)
    iappend(rootino, de)

    de = struct.pack(DIRENT_FMT, rootino, b'..' + b'\x00' * 12)
    iappend(rootino, de)

    # Add README and user programs
    for path in [readme_path] + user_progs:
        shortname = os.path.basename(path)
        # Remove .elf suffix if present (xv6 expects raw names like "cat", "sh")
        if shortname.endswith('.elf'):
            shortname = shortname[:-4]
        # Skip leading _ in user program names
        if shortname.startswith('_'):
            shortname = shortname[1:]
        assert len(shortname) <= DIRSIZ, f"name '{shortname}' too long"

        with open(path, 'rb') as f:
            content = f.read()

        inum = ialloc(T_FILE)
        de = struct.pack(DIRENT_FMT, inum, shortname.encode().ljust(DIRSIZ, b'\x00'))
        iappend(rootino, de)
        iappend(inum, content)
        print(f"  added '{shortname}' (inum={inum}, {len(content)} bytes)")

    # Fix size of root inode dir (round up to BSIZE)
    din = rinode(rootino)
    off = din['size']
    off = ((off // BSIZE) + 1) * BSIZE
    din['size'] = off
    winode(rootino, din)

    # balloc: mark first `freeblock` blocks as used
    bmap_buf = bytearray(BSIZE)
    for i in range(freeblock):
        bmap_buf[i // 8] |= (1 << (i % 8))
    bmapstart = 2 + nlog + ninodeblocks
    wsect(bmapstart, bytes(bmap_buf))
    print(f"balloc: first {freeblock} blocks allocated, bitmap at sector {bmapstart}")

    # Write fs.img
    with open(fsimg_path, 'wb') as f:
        for blk in disk:
            f.write(bytes(blk))

    final_size = os.path.getsize(fsimg_path)
    print(f"\nfs.img generated: {fsimg_path} ({final_size} bytes = {final_size // BSIZE} blocks)")

if __name__ == '__main__':
    main()
