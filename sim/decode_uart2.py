#!/usr/bin/env python3
import sys, re
logfile = sys.argv[1] if len(sys.argv) > 1 else '/mnt/g/GitHub/26-Arch/sim/build_fpga/sim_output2.log'
chars = []
with open(logfile, 'r', errors='replace') as f:
    for line in f:
        m = re.search(r'DEV_W.*addr=0x0000000010000000.*wdata=0x00000000000000(..).*wstrobe=0x01', line)
        if m:
            chars.append(chr(int(m.group(1), 16)))
print(''.join(chars))
