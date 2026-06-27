"""Patch FT2232H EEPROM: change word 41 to switch Channel B from VCP to FIFO/JTAG.

This is a MINIMAL patch:
- Only modifies word 41 (offset 0x52) from 0x0000 to 0x0001
- Recalculates checksum (word 255 = XOR of words 0..254)
- Writes only the changed words (word 41 and word 255)
- Verifies by reading back

Before running:
- Close Vivado/hw_server
- Backup exists at sim/eeprom_backups/eeprom_backup_20260627_065210.bin

After running:
- Unplug and re-plug USB
- Vivado should recognize the board (Channel B = FIFO/JTAG)
- COM8 will disappear (Channel B no longer VCP)
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
    """XOR of words 0..254."""
    cs = 0
    for w in words_256[:255]:
        cs ^= w
    return cs


# The word to patch and its new value
PATCH_WORD_ADDR = 41        # word index (offset 0x52)
PATCH_WORD_NEW_VALUE = 0x0001  # value that makes Channel B = FIFO/JTAG (from original board)

# Open device (Channel A, which is D2XX mode - accessible via FT_Open)
handle = ctypes.c_void_p()
status = ftd2xx.FT_Open(0, ctypes.byref(handle))
if status != 0:
    print(f"FT_Open(0) failed: {status}")
    print("Make sure Vivado/hw_server is closed.")
    sys.exit(1)
print("FT_Open(0) OK")

# Read current EEPROM
words = []
for i in range(256):
    w = ctypes.c_uint16()
    s = ftd2xx.FT_ReadEE(handle, i, ctypes.byref(w))
    if s != 0:
        print(f"FT_ReadEE failed at word {i}: {s}")
        ftd2xx.FT_Close(handle)
        sys.exit(1)
    words.append(w.value)

print(f"Read {len(words)} words")
print(f"Current word 41 (0x52): 0x{words[PATCH_WORD_ADDR]:04x}")
print(f"Current checksum (word 255): 0x{words[255]:04x}")

# Verify current checksum matches
calc_cs = calc_checksum(words)
if calc_cs != words[255]:
    print(f"WARNING: Current checksum mismatch! stored=0x{words[255]:04x} calc=0x{calc_cs:04x}")
    print("Aborting - EEPROM may be corrupted.")
    ftd2xx.FT_Close(handle)
    sys.exit(1)
print(f"Checksum verified OK (0x{calc_cs:04x})")

# Check if word 41 is already the target value
if words[PATCH_WORD_ADDR] == PATCH_WORD_NEW_VALUE:
    print(f"\nWord 41 is already 0x{PATCH_WORD_NEW_VALUE:04x} - no change needed!")
    ftd2xx.FT_Close(handle)
    sys.exit(0)

# Apply patch
old_value = words[PATCH_WORD_ADDR]
words[PATCH_WORD_ADDR] = PATCH_WORD_NEW_VALUE

# Recalculate checksum
new_checksum = calc_checksum(words)
words[255] = new_checksum

print(f"\n=== Patch plan ===")
print(f"  Word 41 (0x52): 0x{old_value:04x} -> 0x{PATCH_WORD_NEW_VALUE:04x}")
print(f"  Word 255 (checksum): 0x{words[255] ^ (old_value ^ PATCH_WORD_NEW_VALUE):04x} -> 0x{new_checksum:04x}")
print(f"  (checksum = old_checksum XOR old_word41 XOR new_word41)")

# Confirm
print()
if '--yes' in sys.argv:
    print("Auto-confirmed via --yes flag")
else:
    resp = input("Type 'YES' to write these 2 words to EEPROM: ")
    if resp != 'YES':
        print("Aborted.")
        ftd2xx.FT_Close(handle)
        sys.exit(0)

# Write word 41
print(f"\nWriting word 41 = 0x{PATCH_WORD_NEW_VALUE:04x}...")
status = ftd2xx.FT_WriteEE(handle, PATCH_WORD_ADDR, ctypes.c_uint16(PATCH_WORD_NEW_VALUE))
if status != 0:
    print(f"FT_WriteEE failed for word 41: {status}")
    ftd2xx.FT_Close(handle)
    sys.exit(1)
print("  OK")

# Write new checksum
print(f"Writing word 255 (checksum) = 0x{new_checksum:04x}...")
status = ftd2xx.FT_WriteEE(handle, 255, ctypes.c_uint16(new_checksum))
if status != 0:
    print(f"FT_WriteEE failed for checksum: {status}")
    ftd2xx.FT_Close(handle)
    sys.exit(1)
print("  OK")

# Verify by reading back
print("\n=== Verifying ===")
for addr, expected in [(PATCH_WORD_ADDR, PATCH_WORD_NEW_VALUE), (255, new_checksum)]:
    w = ctypes.c_uint16()
    s = ftd2xx.FT_ReadEE(handle, addr, ctypes.byref(w))
    if s != 0 or w.value != expected:
        print(f"  MISMATCH at word {addr}: expected 0x{expected:04x}, got 0x{w.value:04x}")
    else:
        print(f"  Word {addr}: 0x{w.value:04x} OK")

ftd2xx.FT_Close(handle)

print("\n=== Patch complete! ===")
print("Next steps:")
print("  1. Unplug the USB cable")
print("  2. Wait 3 seconds")
print("  3. Re-plug the USB cable")
print("  4. Open Vivado and check if the board is recognized")
print("  5. COM8 should be gone (Channel B is now FIFO/JTAG)")
print()
print("If Vivado still doesn't recognize the board, restore the backup:")
print("  python sim\\restore_eeprom_full.py sim\\eeprom_backups\\eeprom_backup_20260627_065210.bin")
