#!/usr/bin/env python3
import sys, re
chars = []
with open('/mnt/g/GitHub/26-Arch/sim/build_fpga/sim_output.log', 'r', errors='replace') as f:
    for line in f:
        m = re.search(r'DEV_W.*addr=0x0000000010000000.*wdata=0x00000000000000(..).*wstrobe=0x01', line)
        if m:
            chars.append(chr(int(m.group(1), 16)))
print(''.join(chars))
