"""Force restore ALL 256 words from original backup, including serial number and checksums.
No preservation - exact copy of the working board's EEPROM.
"""
import ctypes
import struct
import time

ORIG_PATH = 'sim/eeprom_backups/eeprom_backup_20260627_072124.bin'
with open(ORIG_PATH, 'rb') as f:
    orig_data = f.read()
orig = list(struct.unpack('<' + 'H'*(len(orig_data)//2), orig_data))

ft = ctypes.WinDLL('ftd2xx.dll')
ft.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ft.FT_Open.restype = ctypes.c_uint32
ft.FT_WriteEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.c_uint16]
ft.FT_WriteEE.restype = ctypes.c_uint32
ft.FT_ReadEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint16)]
ft.FT_ReadEE.restype = ctypes.c_uint32
ft.FT_Close.argtypes = [ctypes.c_void_p]
ft.FT_Close.restype = ctypes.c_uint32

handle = ctypes.c_void_p()
if ft.FT_Open(0, ctypes.byref(handle)) != 0:
    print("FT_Open failed")
    exit(1)

# Read current
cur = []
for i in range(256):
    w = ctypes.c_uint16()
    ft.FT_ReadEE(handle, i, ctypes.byref(w))
    cur.append(w.value)

# Find differences
changes = [(i, cur[i], orig[i]) for i in range(256) if cur[i] != orig[i]]
print(f"=== Writing {len(changes)} words (full restore) ===")
for i, old, new in changes:
    print(f"  Word {i:3d}: 0x{old:04x} -> 0x{new:04x}")

# Write all
for i, old, new in changes:
    ft.FT_WriteEE(handle, i, ctypes.c_uint16(new))
    time.sleep(0.05)

# Verify
print("\n=== Verifying ===")
all_ok = True
for i in range(256):
    w = ctypes.c_uint16()
    ft.FT_ReadEE(handle, i, ctypes.byref(w))
    if w.value != orig[i]:
        print(f"  MISMATCH word {i}: expected 0x{orig[i]:04x} got 0x{w.value:04x}")
        all_ok = False

if all_ok:
    print("  All 256 words match original backup!")
else:
    print("  Some words failed")

ft.FT_Close(handle)
print("\nDone! Unplug USB, wait 3s, replug.")
