"""Modify FT2232 EEPROM: Change Channel B from FIFO (type 7) to UART (type 0).

WARNING: This modifies the FTDI EEPROM. If done incorrectly, the board may 
not be recognized. We backup the EEPROM first and only change the Channel B type byte.

The FT2232H EEPROM word 3 (offset 0x06) contains:
  - Low byte (offset 0x06): Channel A driver type
  - High byte (offset 0x07): Channel B driver type

Current: Channel A=0 (UART), Channel B=7 (FIFO)
Target:  Channel A=0 (UART), Channel B=0 (UART)
"""
import ctypes
import sys

# Load FTD2XX DLL
ftd2xx_dll = ctypes.windll.FTD2XX

FT_OK = 0

ft_open = ftd2xx_dll.FT_Open
ft_open.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_void_p)]
ft_open.restype = ctypes.c_ulong

ft_close = ftd2xx_dll.FT_Close
ft_close.argtypes = [ctypes.c_void_p]
ft_close.restype = ctypes.c_ulong

ft_read_ee = ftd2xx_dll.FT_ReadEE
ft_read_ee.argtypes = [ctypes.c_void_p, ctypes.c_ulong, ctypes.POINTER(ctypes.c_ushort)]
ft_read_ee.restype = ctypes.c_ulong

ft_write_ee = ftd2xx_dll.FT_WriteEE
ft_write_ee.argtypes = [ctypes.c_void_p, ctypes.c_ulong, ctypes.c_ushort]
ft_write_ee.restype = ctypes.c_ulong

ft_ee_program = ftd2xx_dll.FT_EE_Program
ft_ee_program.restype = ctypes.c_ulong

# First, backup the entire EEPROM
print("=== Step 1: Backup EEPROM ===")
handle = ctypes.c_void_p()
status = ft_open(0, ctypes.byref(handle))  # Open device 0 (either channel works)
if status != FT_OK:
    print(f"FT_Open failed: {status}")
    sys.exit(1)

# Read all EEPROM words
eeprom_backup = []
for addr in range(128):  # FT2232H has up to 256 words
    val = ctypes.c_ushort()
    status = ft_read_ee(handle, addr, ctypes.byref(val))
    if status != FT_OK:
        break
    eeprom_backup.append(val.value)

print(f"Read {len(eeprom_backup)} words")

# Save backup
with open("G:\\GitHub\\26-Arch\\sim\\eeprom_backup.bin", "wb") as f:
    for w in eeprom_backup:
        f.write(w.to_bytes(2, 'little'))
print("Backup saved to eeprom_backup.bin")

# Show current word 3
word3 = eeprom_backup[3]
ch_a = word3 & 0xFF
ch_b = (word3 >> 8) & 0xFF
print(f"\nCurrent word 3: 0x{word3:04x}")
print(f"  Channel A type: {ch_a}")
print(f"  Channel B type: {ch_b}")

if ch_b == 0:
    print("\nChannel B is already UART mode! No change needed.")
    ft_close(handle)
    sys.exit(0)

# Modify word 3: Change Channel B type from 7 to 0
new_word3 = (word3 & 0x00FF) | (0 << 8)  # Set Channel B type = 0 (UART)
print(f"\nNew word 3: 0x{new_word3:04x}")
print(f"  Channel A type: {new_word3 & 0xFF}")
print(f"  Channel B type: {(new_word3 >> 8) & 0xFF}")

# Ask for confirmation
confirm = input("\nType 'YES' to write new EEPROM value: ")
if confirm != 'YES':
    print("Aborted.")
    ft_close(handle)
    sys.exit(0)

# Write new word 3
print("\nWriting new EEPROM word 3...")
status = ft_write_ee(handle, 3, new_word3)
if status != FT_OK:
    print(f"FT_WriteEE failed: {status}")
else:
    print("EEPROM write successful!")

# Verify
val = ctypes.c_ushort()
ft_read_ee(handle, 3, ctypes.byref(val))
print(f"Verification - word 3: 0x{val.value:04x}")
print(f"  Channel A type: {val.value & 0xFF}")
print(f"  Channel B type: {(val.value >> 8) & 0xFF}")

ft_close(handle)
print("\nDone! Please unplug and replug the Basys3 USB cable for changes to take effect.")
