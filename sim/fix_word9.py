"""Fix word 9 and 137 (and recalc checksums).

Word 9 differs: orig=0x1ad4, cur=0x12d4. Diff is bit 11.
This bit likely controls USB string descriptor table reading.
Mirror in word 137 also needs fixing.
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

# Read current 256 words
handle = ctypes.c_void_p()
if ft.FT_Open(0, ctypes.byref(handle)) != 0:
    print("FT_Open failed")
    exit(1)

words = []
for i in range(256):
    w = ctypes.c_uint16()
    ft.FT_ReadEE(handle, i, ctypes.byref(w))
    words.append(w.value)

print(f"Current word 9:   0x{words[9]:04x} (should be 0x1ad4)")
print(f"Current word 137: 0x{words[137]:04x} (should be 0x1ad4)")

changes = []
if words[9] != 0x1ad4:
    changes.append((9, words[9], 0x1ad4))
    words[9] = 0x1ad4
if words[137] != 0x1ad4:
    changes.append((137, words[137], 0x1ad4))
    words[137] = 0x1ad4

# Recalc checksums
cs_127 = 0
for w in words[:127]:
    cs_127 ^= w
cs_255 = 0
for w in words[128:255]:
    cs_255 ^= w

if words[127] != cs_127:
    changes.append((127, words[127], cs_127))
    words[127] = cs_127
if words[255] != cs_255:
    changes.append((255, words[255], cs_255))
    words[255] = cs_255

print(f"\nChanges ({len(changes)}):")
for i, old, new in changes:
    print(f"  Word {i:3d}: 0x{old:04x} -> 0x{new:04x}")

# Write
for i, old, new in changes:
    ft.FT_WriteEE(handle, i, ctypes.c_uint16(new))
    print(f"  Wrote word {i}: 0x{new:04x} OK")
    time.sleep(0.05)

# Verify
print("\nVerifying:")
for i, old, new in changes:
    w = ctypes.c_uint16()
    ft.FT_ReadEE(handle, i, ctypes.byref(w))
    print(f"  Word {i}: 0x{w.value:04x} {'OK' if w.value==new else 'FAIL'}")

ft.FT_Close(handle)
print("\nDone! Unplug USB, wait 3s, replug.")
