#!/usr/bin/env python3
"""Restore Basys3 FTDI EEPROM to default D2XX/JTAG + VCP UART mode.

Word3 = 0x0700:
  Channel A type = 0x00 (UART/VCP)
  Channel B type = 0x07 (FIFO/D2XX) <- used by Digilent JTAG
"""
import sys
import ctypes
from ctypes import wintypes

FTD2XX_DLL = "ftd2xx.dll"

try:
    ft = ctypes.WinDLL(FTD2XX_DLL)
except OSError as e:
    print(f"ERROR: Cannot load {FTD2XX_DLL}: {e}")
    sys.exit(1)

# FT_Open
ft_open = ft.FT_Open
ft_open.argtypes = [ctypes.c_int, ctypes.POINTER(wintypes.HANDLE)]
ft_open.restype = wintypes.DWORD

# FT_Close
ft_close = ft.FT_Close
ft_close.argtypes = [wintypes.HANDLE]
ft_close.restype = wintypes.DWORD

# FT_ReadEE
ft_read_ee = ft.FT_ReadEE
ft_read_ee.argtypes = [wintypes.HANDLE, wintypes.DWORD, ctypes.POINTER(wintypes.WORD)]
ft_read_ee.restype = wintypes.DWORD

# FT_WriteEE
ft_write_ee = ft.FT_WriteEE
ft_write_ee.argtypes = [wintypes.HANDLE, wintypes.DWORD, wintypes.WORD]
ft_write_ee.restype = wintypes.DWORD

handle = wintypes.HANDLE()
status = ft_open(0, ctypes.byref(handle))
if status != 0:
    print(f"ERROR: FT_Open failed with status {status}")
    sys.exit(1)

# Read word 3
word3 = wintypes.WORD()
status = ft_read_ee(handle, 3, ctypes.byref(word3))
if status != 0:
    print(f"ERROR: FT_ReadEE failed with status {status}")
    ft_close(handle)
    sys.exit(1)

print(f"Current word 3: 0x{word3.value:04x}")
print(f"  Channel A type: {word3.value & 0xff}")
print(f"  Channel B type: {(word3.value >> 8) & 0xff}")

# Restore default Basys3 value
TARGET_WORD3 = 0x0700
if word3.value == TARGET_WORD3:
    print("Already at default Basys3 value. No change.")
    ft_close(handle)
    sys.exit(0)

# Backup current EEPROM first
import struct
eeprom_words = []
for i in range(128):
    w = wintypes.WORD()
    ft_read_ee(handle, i, ctypes.byref(w))
    eeprom_words.append(w.value)
with open('eeprom_backup_before_restore.bin', 'wb') as f:
    f.write(struct.pack('<' + 'H'*128, *eeprom_words))
print("Backup saved to eeprom_backup_before_restore.bin")

# Write word 3
status = ft_write_ee(handle, 3, TARGET_WORD3)
if status != 0:
    print(f"ERROR: FT_WriteEE failed with status {status}")
    ft_close(handle)
    sys.exit(1)

print(f"\nWrote word 3 = 0x{TARGET_WORD3:04x}")
print("  Channel A type: 0 (UART/VCP)")
print("  Channel B type: 7 (FIFO/D2XX - JTAG)")
print("\nPlease unplug and replug the Basys3 USB cable for the change to take effect.")

ft_close(handle)
