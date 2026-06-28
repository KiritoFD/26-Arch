"""Full EEPROM restore from known-good backup.
Completely overwrite all 256 words, then verify.
"""
import ctypes
import struct
import time

ft = ctypes.WinDLL('ftd2xx.dll')
ft.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ft.FT_Open.restype = ctypes.c_uint32
ft.FT_WriteEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.c_uint16]
ft.FT_WriteEE.restype = ctypes.c_uint32
ft.FT_ReadEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint16)]
ft.FT_ReadEE.restype = ctypes.c_uint32
ft.FT_Close.argtypes = [ctypes.c_void_p]
ft.FT_Close.restype = ctypes.c_uint32

# Read backup
backup_path = 'sim/eeprom_backups/eeprom_restore_target.bin'
with open(backup_path, 'rb') as f:
    data = f.read()
backup_words = list(struct.unpack('<' + 'H'*(len(data)//2), data))
print(f"Loaded backup: {backup_path}")
print(f"  {len(backup_words)} words")
print(f"  word 0   = 0x{backup_words[0]:04x}")
print(f"  word 1   = 0x{backup_words[1]:04x} (VID)")
print(f"  word 3   = 0x{backup_words[3]:04x}")
print(f"  word 5   = 0x{backup_words[5]:04x}")
print(f"  word 9   = 0x{backup_words[9]:04x}")
print(f"  word 127 = 0x{backup_words[127]:04x} (checksum)")
print(f"  word 255 = 0x{backup_words[255]:04x} (checksum)")

# Verify backup checksums
cs127 = 0
for w in backup_words[:127]:
    cs127 ^= w
cs255 = 0
for w in backup_words[128:255]:
    cs255 ^= w
print(f"\nBackup checksum verification:")
print(f"  word 127: expected 0x{cs127:04x}, actual 0x{backup_words[127]:04x} {'OK' if cs127 == backup_words[127] else 'FAIL'}")
print(f"  word 255: expected 0x{cs255:04x}, actual 0x{backup_words[255]:04x} {'OK' if cs255 == backup_words[255] else 'FAIL'}")

if cs127 != backup_words[127] or cs255 != backup_words[255]:
    print("Backup checksum mismatch! Aborting.")
    exit(1)

# Open device
handle = ctypes.c_void_p()
if ft.FT_Open(0, ctypes.byref(handle)) != 0:
    print("FT_Open failed - close Vivado/hw_server first")
    exit(1)

# Read current EEPROM
print("\n=== Current EEPROM (diff from backup) ===")
cur_words = []
for i in range(256):
    w = ctypes.c_uint16()
    ft.FT_ReadEE(handle, i, ctypes.byref(w))
    cur_words.append(w.value)

diffs = []
for i in range(256):
    if cur_words[i] != backup_words[i]:
        diffs.append(i)
print(f"  {len(diffs)} words differ")
if diffs:
    for i in diffs[:20]:
        print(f"    word {i:3d}: current=0x{cur_words[i]:04x} backup=0x{backup_words[i]:04x}")

# Write all 256 words
print(f"\n=== Writing all 256 words from backup ===")
written = 0
for i in range(256):
    ft.FT_WriteEE(handle, i, ctypes.c_uint16(backup_words[i]))
    written += 1
    if written % 32 == 0:
        print(f"  {written}/256...")
    time.sleep(0.05)

print(f"  Written: {written}/256")

# Verify
print("\n=== Verifying ===")
fail_count = 0
for i in range(256):
    w = ctypes.c_uint16()
    ft.FT_ReadEE(handle, i, ctypes.byref(w))
    if w.value != backup_words[i]:
        print(f"  FAIL word {i}: written=0x{backup_words[i]:04x} read=0x{w.value:04x}")
        fail_count += 1

if fail_count == 0:
    print(f"  All 256 words verified OK!")
else:
    print(f"  {fail_count} words failed verification!")

ft.FT_Close(handle)
print("\nDone! Unplug USB, wait 3s, replug.")
print("Expected: Vivado OK + COM port (if Load VCP enabled in device manager)")
