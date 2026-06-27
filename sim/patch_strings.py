"""Patch current board EEPROM: copy string area from original board.

The current board (Vivado FAIL) is missing data at offset 0x1c-0x42:
  - 0x1c-0x23: c7 92 6a 35 51 01 70 01 (unknown config, maybe checksum or ID)
  - 0x24-0x29: "Basys3" (6 bytes)
  - 0x2a-0x34: zeros (padding)
  - 0x35-0x42: "Digilent Basys3" (15 bytes)

This script:
1. Reads current EEPROM
2. Copies bytes 0x1c-0x4f from original backup (keeping 0x50-0x52 unchanged)
3. Keeps current SN (word 116-118 = 210183A8AC3D)
4. Recalculates checksum
5. Writes only changed words
6. Verifies

Run this with the CURRENT (failing) board connected.
"""
import ctypes
import struct
import sys

ftd2xx = ctypes.windll.FTD2XX
ftd2xx.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ftd2xx.FT_Open.restype = ctypes.c_uint32
ftd2xx.FT_Close.argtypes = [ctypes.c_void_p]
ftd2xx.FT_Close.restype = ctypes.c_uint32
ftd2xx.FT_ReadEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint16)]
ftd2xx.FT_ReadEE.restype = ctypes.c_uint32
ftd2xx.FT_WriteEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.c_uint16]
ftd2xx.FT_WriteEE.restype = ctypes.c_uint32


def calc_checksum(words_256):
    cs = 0
    for w in words_256[:255]:
        cs ^= w
    return cs


# Load original (Vivado OK) EEPROM as reference
orig_path = 'sim/eeprom_backups/eeprom_backup_20260627_072124.bin'
with open(orig_path, 'rb') as f:
    orig_data = f.read()
orig_words = list(struct.unpack('<' + 'H'*(len(orig_data)//2), orig_data))

# The bytes to copy: offset 0x1c to 0x4f (words 14 to 39 inclusive)
# This is the area that differs between boards
COPY_START_WORD = 14   # offset 0x1c
COPY_END_WORD = 39     # offset 0x4e (inclusive)

# Open current device
handle = ctypes.c_void_p()
status = ftd2xx.FT_Open(0, ctypes.byref(handle))
if status != 0:
    print(f"FT_Open(0) failed: {status}")
    print("Make sure Vivado is closed and the CURRENT (failing) board is connected.")
    sys.exit(1)
print("FT_Open(0) OK")

# Read current EEPROM
words = []
for i in range(256):
    w = ctypes.c_uint16()
    s = ftd2xx.FT_ReadEE(handle, i, ctypes.byref(w))
    if s != 0:
        print(f"Read failed at {i}")
        sys.exit(1)
    words.append(w.value)

# Verify checksum
calc_cs = calc_checksum(words)
print(f"Current checksum: stored=0x{words[255]:04x} calc=0x{calc_cs:04x} match={words[255]==calc_cs}")

# Show what we'll change
print(f"\n=== Words to copy (word {COPY_START_WORD}-{COPY_END_WORD}) ===")
changes = []
for i in range(COPY_START_WORD, COPY_END_WORD + 1):
    if words[i] != orig_words[i]:
        changes.append((i, words[i], orig_words[i]))
        print(f"  Word {i:3d} (0x{i*2:04x}): 0x{words[i]:04x} -> 0x{orig_words[i]:04x}")

if not changes:
    print("  No changes needed - already matches!")
    ftd2xx.FT_Close(handle)
    sys.exit(0)

print(f"\nTotal words to change: {len(changes)}")

# Apply changes
for i, old, new in changes:
    words[i] = new

# Recalculate checksum
new_checksum = calc_checksum(words)
old_checksum = words[255]
words[255] = new_checksum

print(f"\nChecksum: 0x{old_checksum:04x} -> 0x{new_checksum:04x}")

# Confirm
print()
if '--yes' not in sys.argv:
    resp = input(f"Write {len(changes)} words + checksum? Type YES: ")
    if resp != 'YES':
        print("Aborted")
        ftd2xx.FT_Close(handle)
        sys.exit(0)
else:
    print("Auto-confirmed via --yes")

# Write changed words
print("\nWriting...")
for i, old, new in changes:
    status = ftd2xx.FT_WriteEE(handle, i, ctypes.c_uint16(new))
    if status != 0:
        print(f"  FAILED at word {i}: {status}")
        sys.exit(1)
    print(f"  Word {i}: 0x{new:04x} OK")

# Write checksum
status = ftd2xx.FT_WriteEE(handle, 255, ctypes.c_uint16(new_checksum))
if status != 0:
    print(f"  FAILED checksum: {status}")
    sys.exit(1)
print(f"  Word 255 (checksum): 0x{new_checksum:04x} OK")

# Verify
print("\nVerifying...")
for i, old, new in changes:
    w = ctypes.c_uint16()
    ftd2xx.FT_ReadEE(handle, i, ctypes.byref(w))
    if w.value != new:
        print(f"  MISMATCH word {i}: expected 0x{new:04x} got 0x{w.value:04x}")
    else:
        print(f"  Word {i}: 0x{w.value:04x} OK")

w = ctypes.c_uint16()
ftd2xx.FT_ReadEE(handle, 255, ctypes.byref(w))
print(f"  Checksum: 0x{w.value:04x} {'OK' if w.value == new_checksum else 'MISMATCH'}")

ftd2xx.FT_Close(handle)

print("\n=== Patch complete! ===")
print("Next: unplug USB, wait 3s, re-plug, test Vivado")
print("If fails, restore: python sim\\restore_eeprom_full.py sim\\eeprom_backups\\eeprom_backup_20260627_065956.bin")
