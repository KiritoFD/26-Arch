"""Restore full EEPROM from original (Vivado OK) backup, preserving current board's serial number.

Original board: SN 210183A8A984 (backup eeprom_backup_20260627_072124.bin)
Current board:  SN 21BE5S1DA (need to keep this)
"""
import ctypes
import struct
import time
import sys

# Original (Vivado OK) backup - 256 words
ORIG_PATH = 'sim/eeprom_backups/eeprom_backup_20260627_072124.bin'
with open(ORIG_PATH, 'rb') as f:
    orig_data = f.read()
orig = list(struct.unpack('<' + 'H'*(len(orig_data)//2), orig_data))

# Current EEPROM (just read)
CUR_PATH = 'sim/eeprom_backups/eeprom_current_after_vid_fix.bin'
with open(CUR_PATH, 'rb') as f:
    cur_data = f.read()
cur = list(struct.unpack('<' + 'H'*(len(cur_data)//2), cur_data))

# The serial number string is at words 106-119 (image 1) and 234-247 (image 2)
# Original serial: "210183A8A984" (12 chars + header)
# Current serial:  "21BE5S1DA" (9 chars + header)
# We must NOT overwrite these - keep current board's serial
SERIAL_RANGE_IMG1 = range(106, 120)  # word 106-119
SERIAL_RANGE_IMG2 = range(234, 248)  # word 234-247

# Build the target: copy everything from original, but keep current serial
target = orig[:]
for i in SERIAL_RANGE_IMG1:
    target[i] = cur[i]
for i in SERIAL_RANGE_IMG2:
    target[i] = cur[i]

# But wait - the serial string length differs (orig=12 chars, cur=9 chars)
# Original word 106 = 0x031a (bLength=26=0x1a), word 119 = 0x0302 (bLength=2)
# Current word 106 = 0x0312 (bLength=18=0x12), word 115 = 0x0302 (bLength=2)
# So orig serial occupies words 106-119 (14 words), cur occupies 106-115 (10 words)
# Words 116-119 are 0x0000 in current but 0x0039/0x0038/0x0034/0x0302 in orig
# Since we keep current serial, words 116-119 should remain 0x0000

# Actually, let's verify by comparing what differs
print("=== Comparing target vs current (excluding serial area) ===")
diffs = []
for i in range(256):
    if target[i] != cur[i]:
        # Skip serial area - those are expected to differ
        if i in SERIAL_RANGE_IMG1 or i in SERIAL_RANGE_IMG2:
            continue
        diffs.append((i, cur[i], target[i]))

print(f"Non-serial differences: {len(diffs)}")
for i, c, t in diffs:
    print(f"  Word {i:3d}: cur=0x{c:04x} -> target=0x{t:04x}")

# Now compute what needs to change (everything from original, minus serial area)
changes = []
for i in range(256):
    if i in SERIAL_RANGE_IMG1 or i in SERIAL_RANGE_IMG2:
        # Keep current serial
        if cur[i] != target[i]:
            # This shouldn't happen since we copied cur->target for serial
            pass
        continue
    if cur[i] != target[i]:
        changes.append((i, cur[i], target[i]))

# Recalculate checksums with the target data
# But we need to recalc considering the serial area is from current
cs_127 = 0
for w in target[:127]:
    cs_127 ^= w
cs_255 = 0
for w in target[128:255]:
    cs_255 ^= w

# Add checksum changes
if target[127] != cs_127:
    changes.append((127, target[127], cs_127))
    target[127] = cs_127
if target[255] != cs_255:
    changes.append((255, target[255], cs_255))
    target[255] = cs_255

# Also fix word 9 if it differs (already fixed but let's be sure)
print(f"\n=== Total changes: {len(changes)} words ===")
for i, old, new in changes:
    print(f"  Word {i:3d}: 0x{old:04x} -> 0x{new:04x}")

# Save target for reference
with open('sim/eeprom_backups/eeprom_restore_target.bin', 'wb') as f:
    f.write(struct.pack('<' + 'H'*256, *target))
print(f"\nSaved target to sim/eeprom_backups/eeprom_restore_target.bin")

if '--yes' not in sys.argv:
    resp = input(f"\nWrite {len(changes)} words? Type YES: ")
    if resp != 'YES':
        print("Aborted")
        sys.exit(0)
else:
    print("\nAuto-confirmed via --yes")

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

# Get before info
dev_type = ctypes.c_uint32()
dev_id = ctypes.c_uint32()
sn = ctypes.create_string_buffer(64)
desc = ctypes.create_string_buffer(256)
ft.FT_GetDeviceInfo(handle, ctypes.byref(dev_type), ctypes.byref(dev_id), sn, desc, None)
print(f"\nBefore: desc='{desc.value.decode()}' sn='{sn.value.decode()}'")

# Write all changed words
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

if all_ok:
    print("  All verified OK")
    # Get after info
    ft.FT_GetDeviceInfo(handle, ctypes.byref(dev_type), ctypes.byref(dev_id), sn, desc, None)
    print(f"\nAfter: desc='{desc.value.decode()}' sn='{sn.value.decode()}'")
    print("\n=== SUCCESS! ===")
    print("Unplug USB, wait 3s, replug, then try Vivado")

ft.FT_Close(handle)
