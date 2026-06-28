"""Fix word 3 back to 0x0700 and recalc checksums.

Problem: word 3 changed from 0x0700 to 0x0000, checksum mismatch,
FTDI discarded EEPROM config -> Vivado can't recognize board.
"""
import ctypes
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

handle = ctypes.c_void_p()
if ft.FT_Open(0, ctypes.byref(handle)) != 0:
    print("FT_Open failed - close Vivado/hw_server first")
    exit(1)

# Read all words
words = []
for i in range(256):
    w = ctypes.c_uint16()
    ft.FT_ReadEE(handle, i, ctypes.byref(w))
    words.append(w.value)

print("=== Before fix ===")
print(f"  word 3   = 0x{words[3]:04x}  (should be 0x0700)")
print(f"  word 131 = 0x{words[131]:04x}  (mirror, should be 0x0700)")

# Fix word 3 and 131 (image 2 mirror)
words[3] = 0x0700
words[131] = 0x0700

# Recalc checksums
cs127 = 0
for w in words[:127]:
    cs127 ^= w
words[127] = cs127

cs255 = 0
for w in words[128:255]:
    cs255 ^= w
words[255] = cs255

print(f"\n=== After fix ===")
print(f"  word 3   = 0x{words[3]:04x}")
print(f"  word 131 = 0x{words[131]:04x}")
print(f"  word 127 = 0x{words[127]:04x} (checksum)")
print(f"  word 255 = 0x{words[255]:04x} (checksum)")

# Write changed words
to_write = []
# Read current values to see what changed
w = ctypes.c_uint16()
ft.FT_ReadEE(handle, 3, ctypes.byref(w))
if w.value != 0x0700:
    to_write.append((3, 0x0700))
    print(f"\n  word 3: 0x{w.value:04x} -> 0x0700")

ft.FT_ReadEE(handle, 131, ctypes.byref(w))
if w.value != 0x0700:
    to_write.append((131, 0x0700))
    print(f"  word 131: 0x{w.value:04x} -> 0x0700")

ft.FT_ReadEE(handle, 127, ctypes.byref(w))
if w.value != cs127:
    to_write.append((127, cs127))
    print(f"  word 127: 0x{w.value:04x} -> 0x{cs127:04x}")

ft.FT_ReadEE(handle, 255, ctypes.byref(w))
if w.value != cs255:
    to_write.append((255, cs255))
    print(f"  word 255: 0x{w.value:04x} -> 0x{cs255:04x}")

print(f"\nWriting {len(to_write)} words...")
for idx, val in to_write:
    ft.FT_WriteEE(handle, idx, ctypes.c_uint16(val))
    time.sleep(0.1)
    print(f"  word {idx}: written 0x{val:04x}")

# Verify
print("\n=== Verify ===")
for idx, val in to_write:
    w = ctypes.c_uint16()
    ft.FT_ReadEE(handle, idx, ctypes.byref(w))
    ok = "OK" if w.value == val else "FAIL"
    print(f"  word {idx}: 0x{w.value:04x} {ok}")

ft.FT_Close(handle)
print("\nDone! Unplug USB, wait 3s, replug.")
