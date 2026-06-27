"""Fix FT2232H EEPROM: restore string area from original backup + recalc checksums.

Root cause: FTDI proprietary strings (words 14-33) and enable flags (words 13, 41)
are all zero on current board. Both image checksums (word 127, 255) are wrong.
FTDI chip ignores EEPROM config → falls back to default VID/PID but NO strings.
Vivado Digilent plugin can't identify board without "Basys3"/"Digilent Basys3" strings.

Fix:
1. Copy string data + flags from original backup (keeping current serial number)
2. Recalculate both image checksums
3. Write via D2XX
"""
import ctypes
import struct
import sys
import time

# Load original (Vivado OK) EEPROM
ORIG_PATH = 'sim/eeprom_backups/eeprom_backup_20260627_072124.bin'
with open(ORIG_PATH, 'rb') as f:
    orig_data = f.read()
orig = list(struct.unpack('<' + 'H'*(len(orig_data)//2), orig_data))

# Load current EEPROM (just saved)
CUR_PATH = 'sim/eeprom_backups/eeprom_current_after_vid_fix.bin'
with open(CUR_PATH, 'rb') as f:
    cur_data = f.read()
cur = list(struct.unpack('<' + 'H'*(len(cur_data)//2), cur_data))

print("=== Before fix ===")
print(f"  Current serial: {cur[106]:04x} {cur[107]:04x}... (bLength at word 106)")
print(f"  Original serial: {orig[106]:04x} {orig[107]:04x}... (bLength at word 106)")

# Words to copy from original (string area + enable flags)
# Image 1 (words 0-127)
words_to_copy_img1 = list(range(13, 34)) + [41]
# Image 2 (words 128-255) = mirror
words_to_copy_img2 = [w + 128 for w in words_to_copy_img1]

# Do NOT copy: word 9/137 (serial length differs per board), words 106-119/234-247 (serial number)
all_words_to_copy = words_to_copy_img1 + words_to_copy_img2

print(f"\n=== Words to copy from original ({len(all_words_to_copy)} words) ===")
changes = []
for i in all_words_to_copy:
    if cur[i] != orig[i]:
        changes.append((i, cur[i], orig[i]))
        label = "string/flag"
        print(f"  Word {i:3d}: 0x{cur[i]:04x} -> 0x{orig[i]:04x}  ({label})")

if not changes:
    print("  No string changes needed!")
else:
    print(f"  Total: {len(changes)} words to change")

# Apply string changes
for i, old, new in changes:
    cur[i] = new

# Recalculate checksums
# Image 1: word 127 = XOR of words 0-126
# Image 2: word 255 = XOR of words 128-254
cs_127 = 0
for w in cur[:127]:
    cs_127 ^= w
cs_255 = 0
for w in cur[128:255]:
    cs_255 ^= w

print(f"\n=== Checksum recalculation ===")
print(f"  Word 127: stored=0x{cur[127]:04x}, computed=0x{cs_127:04x}, {'OK' if cur[127]==cs_127 else 'MISMATCH'}")
print(f"  Word 255: stored=0x{cur[255]:04x}, computed=0x{cs_255:04x}, {'OK' if cur[255]==cs_255 else 'MISMATCH'}")

# Add checksum changes
if cur[127] != cs_127:
    changes.append((127, cur[127], cs_127))
    cur[127] = cs_127
if cur[255] != cs_255:
    changes.append((255, cur[255], cs_255))
    cur[255] = cs_255

print(f"\n=== Total changes: {len(changes)} words ===")
for i, old, new in changes:
    print(f"  Word {i:3d}: 0x{old:04x} -> 0x{new:04x}")

if not changes:
    print("\nNothing to fix!")
    sys.exit(0)

# Save the fixed EEPROM for backup
FIXED_PATH = 'sim/eeprom_backups/eeprom_fixed_strings.bin'
with open(FIXED_PATH, 'wb') as f:
    f.write(struct.pack('<' + 'H'*256, *cur))
print(f"\nSaved fixed EEPROM to {FIXED_PATH}")

# Confirm before writing
if '--yes' not in sys.argv:
    resp = input(f"\nWrite {len(changes)} words to EEPROM? Type YES: ")
    if resp != 'YES':
        print("Aborted")
        sys.exit(0)
else:
    print("\nAuto-confirmed via --yes")

# Write via D2XX
print(f"\n=== Writing {len(changes)} words via D2XX ===")
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
status = ft.FT_Open(0, ctypes.byref(handle))
if status != 0:
    print(f"FT_Open failed: {status}")
    print("Close Vivado/hw_server if running")
    sys.exit(1)
print(f"  FT_Open OK")

for i, old, new in changes:
    status = ft.FT_WriteEE(handle, i, ctypes.c_uint16(new))
    if status != 0:
        print(f"  FAILED word {i}: status={status}")
        ft.FT_Close(handle)
        sys.exit(1)
    print(f"  Word {i:3d}: 0x{new:04x} OK")
    time.sleep(0.05)

# Verify
print(f"\n=== Verifying ===")
all_ok = True
for i, old, new in changes:
    w = ctypes.c_uint16()
    ft.FT_ReadEE(handle, i, ctypes.byref(w))
    if w.value != new:
        print(f"  MISMATCH word {i}: expected 0x{new:04x} got 0x{w.value:04x}")
        all_ok = False
    else:
        print(f"  Word {i:3d}: 0x{w.value:04x} OK")

ft.FT_Close(handle)

if all_ok:
    print(f"\n=== SUCCESS! All {len(changes)} words written and verified ===")
    print("Next: unplug USB, wait 3s, replug")
    print("Then check: Vivado Hardware Manager should detect Basys3")
else:
    print("\n=== Some verification failed ===")
    print("Try unplugging and replugging USB")
