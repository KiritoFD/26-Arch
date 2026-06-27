#!/usr/bin/env python3
import re
import sys

with open(sys.argv[1]) as f:
    txt = f.read()

chars = re.findall(r"ch='(.)'", txt)
print(''.join(chars))
