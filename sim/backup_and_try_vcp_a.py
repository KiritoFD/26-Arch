"""Backup current EEPROM, then try word 5 = 0x0009 (enable VCP on Channel A only).

Current: word 5 = 0x0008 (no VCP on either channel)
Target:  word 5 = 0x0009 (bit 0=1 -> Channel A VCP, bit 3=1 preserved)

Basys3 wiring:
  Channel A -> FPGA UART  -> VCP -> COM port
  Channel B -> FPGA JTAG   -> D2XX -> Vivado
"""
import ctypes
import struct
import time
import shutil
import datetime

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

# 1. Backup current EEPROM
words = []
for i in range(256):
    w = ctypes.c_uint16()
    ft.FT_ReadEE(handle, i, ctypes.byref(w))
    words.append(w.value)

ts = datetime.datetime.now().strftime('%Y%m%d_%H%M%S')
backup_path = f'sim/eeprom_backups/eeprom_backup_before_vcp_a_{ts}.bin'
with open(backup_path, 'wb') as f:
    f.write(struct.pack('<' + 'H'*256, *words))
print(f"Backup saved: {backup_path}")
print(f"  Word 5 = 0x{words[5]:04x}")

# 2. Compute new word 5 and checksums
old_w5 = words[5]
new_w5 = 0x0009  # bit 0=1 (AIsVCP), bit 3=1 (preserved)
print(f"\nChange: word 5 = 0x{old_w5:04x} -> 0x{new_w5:04x}")
print(f"  bit 0 (AIsVCP): {old_w5&1} -> {new_w5&1}  (Channel A -> VCP -> COM)")
print(f"  bit 1 (BIsVCP): {(old_w5>>1)&1} -> {(new_w5>>1)&1}  (Channel B -> D2XX -> Vivado)")

# Update both images
words[5] = new_w5
words[133] = new_w5  # image 2 mirror

# Recalc checksums
cs127 = 0
for w in words[:127]:
    cs127 ^= w
words[127] = cs127

cs255 = 0
for w in words[128:255]:
    cs255 ^= w
words[255] = cs255

# 3. Write changed words
changes = [(5, old_w5, new_w5), (133, words[133], new_w5)]
# Only write if different from backup
cur133 = words[133]
print(f"\nWriting word 5 and 133 (and checksums if changed)...")

# Read current 133
w = ctypes.c_uint16()
ft.FT_ReadEE(handle, 133, ctypes.byref(w))
cur133 = w.value

to_write = []
if old_w5 != new_w5:
    to_write.append((5, new_w5))
if cur133 != new_w5:
    to_write.append((133, new_w5))

# Check if checksums changed
w = ctypes.c_uint16()
ft.FT_ReadEE(handle, 127, ctypes.byref(w))
if w.value != cs127:
    to_write.append((127, cs127))
    print(f"  word 127: 0x{w.value:04x} -> 0x{cs127:04x}")

w = ctypes.c_uint16()
ft.FT_ReadEE(handle, 255, ctypes.byref(w))
if w.value != cs255:
    to_write.append((255, cs255))
    print(f"  word 255: 0x{w.value:04x} -> 0x{cs255:04x}")

print(f"\nWriting {len(to_write)} words:")
for idx, val in to_write:
    print(f"  word {idx}: -> 0x{val:04x}")
    ft.FT_WriteEE(handle, idx, ctypes.c_uint16(val))
    time.sleep(0.1)

# 4. Verify
print("\n=== Verifying ===")
for idx, val in to_write:
    w = ctypes.c_uint16()
    ft.FT_ReadEE(handle, idx, ctypes.byref(w))
    ok = "OK" if w.value == val else "FAIL"
    print(f"  word {idx}: 0x{w.value:04x} {ok}")

ft.FT_Close(handle)
print(f"\nDone! Word 5 = 0x{new_w5:04x}")
print("Unplug USB, wait 3s, replug.")
print("Expected: Vivado OK (ChB D2XX) + COM port (ChA VCP)")
