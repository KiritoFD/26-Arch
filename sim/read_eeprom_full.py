#!/usr/bin/env python3
"""Full EEPROM dump for Basys3 FTDI."""
import ctypes
from ctypes import wintypes
import struct

ft = ctypes.WinDLL('ftd2xx.dll')

handle = wintypes.HANDLE()
status = ft.FT_Open(0, ctypes.byref(handle))
if status != 0:
    print(f'FT_Open failed {status} (Vivado may be holding the device)')
    exit(1)

words = []
for i in range(128):
    w = wintypes.WORD()
    ft.FT_ReadEE(handle, i, ctypes.byref(w))
    words.append(w.value)

ft.FT_Close(handle)

print(f'word3 = 0x{words[3]:04x}')
print(f'  byte0 (bits 7:0)  = 0x{words[3] & 0xff:02x}')
print(f'  byte1 (bits 15:8) = 0x{(words[3] >> 8) & 0xff:02x}')
print()

# Decode common fields
print(f'VID = 0x{words[0]:04x}')
print(f'PID = 0x{words[1]:04x}')
print()

# Dump words 0-31
print('EEPROM words 0-31:')
for i in range(0, 32, 8):
    print('  ' + ' '.join(f'{words[j]:04x}' for j in range(i, i+8)))

# Save raw
with open('eeprom_dump_current.bin', 'wb') as f:
    f.write(struct.pack('<' + 'H'*128, *words))
print('\nSaved to eeprom_dump_current.bin')
