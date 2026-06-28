#!/usr/bin/env python3
import re
import sys

with open(sys.argv[1] if len(sys.argv) > 1 else 'sim_test_full.log') as f:
    data = f.read()

# Match lines where CPU writes to UART_RHR_THR (0x10000000) with wstrobe=0x01
# Format: "[x][DEV_W] cyc=8340 #10 addr=0x10000000 wdata=0x78 wstrobe=0x01"
# The leading char before [DEV_W] is the actual $write output from device.sv
# We want to reconstruct the user-visible TX stream.

# Method 1: Extract chars from leading bytes before "[DEV_" markers
# Each line that starts with a non-'[' char + '[DEV_W]' is a TX byte
chars = []
for line in data.split('\n'):
    if 'DEV_W' in line and 'addr=0x10000000' in line and 'wstrobe=0x01' in line:
        # The TX char is whatever appears BEFORE [DEV_W] on the same line
        idx = line.find('[DEV_W]')
        prefix = line[:idx]
        # Also extract wdata as fallback
        m = re.search(r'wdata=0x([0-9a-f]+)', line)
        if m:
            byte_val = int(m.group(1), 16) & 0xFF
            chars.append(chr(byte_val))

print("---TX bytes from wdata---")
print(''.join(chars))
print()
print("---Repr---")
print(repr(''.join(chars)))
