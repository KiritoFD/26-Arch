"""Restore full EEPROM from original (Vivado OK) backup, preserving current board's serial number.

Simplified: copy all 256 words from original backup, except serial area which stays from current.
Then recalc checksums once.
"""
import ctypes
import struct
import time
import sys

ORIG_PATH = 'sim/eeprom_backups/eeprom_backup_20260627_072124.bin'
with open(ORIG_PATH, 'rb') as f:
    orig_data = f.read()
orig = list(struct.unpack('<' + 'H'*(len(orig_data)//2), orig_data))

CUR_PATH = 'sim/eeprom_backups/eeprom_current_after_vid_fix.bin'
with open(CUR_PATH, 'rb') as f:
    cur_data = f.read()
cur = list(struct.unpack('<' + 'H'*(len(cur_data)//2), cur_data))

# Serial number area (keep current board's serial)
SERIAL_RANGE_IMG1 = set(range(106, 120))
SERIAL_RANGE_IMG2 = set(range(234, 248))

# Build target: start from original, override serial area with current
target = list(orig)
for i in SERIAL_RANGE_IMG1:
    target[i] = cur[i]
for i in SERIAL_RANGE_IMG2:
    target[i] = cur[i]

# Recalculate checksums ONCE
cs_127 = 0
for w in target[:127]:
    cs_127 ^= w
target[127] = cs_127

cs_255 = 0
for w in target[128:255]:
    cs_255 ^= w
target[255] = cs_255

# Compute changes (target vs current)
changes = []
for i in range(256):
    if target[i] != cur[i]:
        changes.append((i, cur[i], target[i]))

print(f"=== Total changes: {len(changes)} words ===")
for i, old, new in changes:
    print(f"  Word {i:3d}: 0x{old:04x} -> 0x{new:04x}")

# Save target
with open('sim/eeprom_backups/eeprom_restore_target.bin', 'wb') as f:
    f.write(struct.pack('<' + 'H'*256, *target))

if '--yes' not in sys.argv:
    resp = input(f"\nWrite {len(changes)} words? Type YES: ")
    if resp != 'YES':
        sys.exit(0)

# Write via D2XX
ft = ctypes.WinDLL('ftd2xx.dll')
ft.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ft.FT_Open.restype = ctypes.c_uint32
ft.FT_WriteEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.c_uint16]
ft.FT_WriteEE.restype = ctypes.c_uint32
ft.FT_ReadEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint16)]
ft.FT_ReadEE.restype = ctypes.c_uint32
ft.FT_Close.argtypes = [ctypes.c_void_p]
ft.FT_Close.restype = ctypes.c_uint32
ft.FT_GetDeviceInfo.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_uint32),
                                 ctypes.POINTER(ctypes.c_uint32), ctypes.c_char_p,
                                 ctypes.c_char_p, ctypes.c_void_p]
ft.FT_GetDeviceInfo.restype = ctypes.c_uint32

handle = ctypes.c_void_p()
if ft.FT_Open(0, ctypes.byref(handle)) != 0:
    print("FT_Open failed")
    sys.exit(1)

dev_type = ctypes.c_uint32()
dev_id = ctypes.c_uint32()
sn = ctypes.create_string_buffer(64)
desc = ctypes.create_string_buffer(256)
ft.FT_GetDeviceInfo(handle, ctypes.byref(dev_type), ctypes.byref(dev_id), sn, desc, None)
print(f"\nBefore: desc='{desc.value.decode()}' sn='{sn.value.decode()}'")

print(f"\n=== Writing {len(changes)} words ===")
for idx, (i, old, new) in enumerate(changes):
    status = ft.FT_WriteEE(handle, i, ctypes.c_uint16(new))
    if status != 0:
        print(f"  FAILED word {i}: status={status}")
        ft.FT_Close(handle)
        sys.exit(1)
    print(f"  [{idx+1}/{len(changes)}] Word {i:3d}: 0x{new:04x} OK")
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

if all_ok:
    print("\n  All verified OK")
    ft.FT_GetDeviceInfo(handle, ctypes.byref(dev_type), ctypes.byref(dev_id), sn, desc, None)
    print(f"\nAfter: desc='{desc.value.decode()}' sn='{sn.value.decode()}'")
    print("\n=== SUCCESS! ===")
    print("Unplug USB, wait 3s, replug, then try Vivado")

ft.FT_Close(handle)
