"""Restore FT2232H EEPROM from a backup file.

Usage:
  python sim\\restore_eeprom_full.py <backup_file.bin>

This will:
1. Read the backup file (256 words = 512 bytes)
2. Verify the checksum matches the stored one
3. Open the FTDI device (Channel A)
4. Erase the EEPROM
5. Write all 256 words from the backup
6. Verify by reading back

WARNING: This overwrites the entire EEPROM. Make sure Vivado is closed.
"""
import ctypes
import struct
import sys
import os

ftd2xx = ctypes.windll.FTD2XX
ftd2xx.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ftd2xx.FT_Open.restype = ctypes.c_uint32
ftd2xx.FT_Close.argtypes = [ctypes.c_void_p]
ftd2xx.FT_Close.restype = ctypes.c_uint32
ftd2xx.FT_ReadEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint16)]
ftd2xx.FT_ReadEE.restype = ctypes.c_uint32
ftd2xx.FT_WriteEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.c_uint16]
ftd2xx.FT_WriteEE.restype = ctypes.c_uint32
ftd2xx.FT_EraseEE.argtypes = [ctypes.c_void_p]
ftd2xx.FT_EraseEE.restype = ctypes.c_uint32


def calc_checksum(words_256):
    """XOR of words 0..254."""
    cs = 0
    for w in words_256[:255]:
        cs ^= w
    return cs


auto_confirm = False
if len(sys.argv) < 2:
    print("Usage: python sim\\restore_eeprom_full.py [-y] <backup_file.bin>")
    print("  -y: Auto-confirm (no interactive prompt)")
    print("Available backups:")
    backup_dir = os.path.join('sim', 'eeprom_backups')
    if os.path.isdir(backup_dir):
        for f in sorted(os.listdir(backup_dir)):
            if f.endswith('.bin'):
                print(f"  {os.path.join(backup_dir, f)}")
    sys.exit(1)

args = sys.argv[1:]
if args[0] == '-y':
    auto_confirm = True
    args = args[1:]

if len(args) < 1:
    print("Error: No backup file specified")
    sys.exit(1)

backup_file = args[0]
if not os.path.exists(backup_file):
    print(f"Backup file not found: {backup_file}")
    sys.exit(1)

# Read backup file
with open(backup_file, 'rb') as f:
    data = f.read()

if len(data) != 512:
    print(f"WARNING: Backup file is {len(data)} bytes, expected 512. Proceeding anyway...")

words = list(struct.unpack('<' + 'H'*(len(data)//2), data))
print(f"Loaded {len(words)} words from {backup_file}")

# Verify checksum
stored_cs = words[255] if len(words) > 255 else 0
calc_cs = calc_checksum(words)
print(f"Stored checksum: 0x{stored_cs:04x}")
print(f"Calculated checksum: 0x{calc_cs:04x}")
if stored_cs != calc_cs:
    print("WARNING: Checksum mismatch! Backup may be corrupted.")
    resp = input("Continue anyway? (y/N): ")
    if resp.lower() != 'y':
        sys.exit(1)
    # Recalculate checksum
    words[255] = calc_cs
    print(f"Recalculated checksum: 0x{calc_cs:04x}")

# Confirm with user
print(f"\nAbout to write {len(words)} words to FT2232H EEPROM")
print("This will OVERWRITE the current EEPROM!")
if auto_confirm:
    print("Auto-confirm enabled (-y).")
else:
    resp = input("Type 'YES' to proceed: ")
    if resp != 'YES':
        print("Aborted.")
        sys.exit(0)

# Open device
handle = ctypes.c_void_p()
status = ftd2xx.FT_Open(0, ctypes.byref(handle))
if status != 0:
    print(f"FT_Open(0) failed: {status}")
    print("Make sure Vivado/hw_server is closed.")
    sys.exit(1)
print(f"FT_Open OK")

# Erase EEPROM
print("Erasing EEPROM...")
status = ftd2xx.FT_EraseEE(handle)
if status != 0:
    print(f"FT_EraseEE failed: {status}")
    ftd2xx.FT_Close(handle)
    sys.exit(1)
print("Erase complete.")

# Write all words
print("Writing 256 words...")
for i, w in enumerate(words):
    status = ftd2xx.FT_WriteEE(handle, i, ctypes.c_uint16(w))
    if status != 0:
        print(f"FT_WriteEE failed at word {i}: {status}")
        ftd2xx.FT_Close(handle)
        sys.exit(1)
    if (i + 1) % 32 == 0:
        print(f"  Wrote {i+1}/256 words...")

print("Write complete.")

# Verify by reading back
print("Verifying...")
mismatch = False
for i, expected in enumerate(words):
    w = ctypes.c_uint16()
    status = ftd2xx.FT_ReadEE(handle, i, ctypes.byref(w))
    if status != 0:
        print(f"FT_ReadEE failed at word {i}: {status}")
        mismatch = True
        break
    if w.value != expected:
        print(f"MISMATCH at word {i}: expected 0x{expected:04x}, got 0x{w.value:04x}")
        mismatch = True

ftd2xx.FT_Close(handle)

if mismatch:
    print("\nVERIFICATION FAILED! Please re-run backup and try again.")
    sys.exit(1)
else:
    print("\n=== Restore complete and verified! ===")
    print("Please unplug and re-plug the USB cable to apply changes.")
