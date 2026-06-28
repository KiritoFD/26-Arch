"""Full restore from backup + enable VCP on Channel B for COM port.

Basys3 wiring:
  Channel A -> FPGA JTAG   -> FIFO/D2XX (no VCP) -> Vivado
  Channel B -> FPGA UART    -> UART + VCP          -> COM port

Word 5 bit 1 (ALBIsVCP) = 1 enables VCP on Channel B.
"""
import ctypes
import struct
import time

ORIG_PATH = 'sim/eeprom_backups/eeprom_backup_20260627_072124.bin'
with open(ORIG_PATH, 'rb') as f:
    orig_data = f.read()
orig = list(struct.unpack('<' + 'H'*(len(orig_data)//2), orig_data))

# Enable VCP on Channel B: set word 5 bit 1
# Backup has word 5 = 0x0008, we set bit 1 -> 0x000a
orig[5] = orig[5] | 0x0002   # ALBIsVCP = 1
orig[133] = orig[133] | 0x0002  # image 2 mirror

# Recalc checksums
cs127 = 0
for w in orig[:127]:
    cs127 ^= w
orig[127] = cs127

cs255 = 0
for w in orig[128:255]:
    cs255 ^= w
orig[255] = cs255

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

changes = [(i, cur[i], orig[i]) for i in range(256) if cur[i] != orig[i]]
print(f"=== Writing {len(changes)} words (full restore + VCP on ChB) ===")
print(f"Word 5: 0x{cur[5]:04x} -> 0x{orig[5]:04x} (enable ChB VCP)")
print(f"Word 127: 0x{cur[127]:04x} -> 0x{orig[127]:04x} (checksum)")
print(f"Word 255: 0x{cur[255]:04x} -> 0x{orig[255]:04x} (checksum)")

for i, old, new in changes:
    ft.FT_WriteEE(handle, i, ctypes.c_uint16(new))
    time.sleep(0.05)

# Verify
all_ok = True
for i in range(256):
    w = ctypes.c_uint16()
    ft.FT_ReadEE(handle, i, ctypes.byref(w))
    if w.value != orig[i]:
        print(f"  MISMATCH word {i}: expected 0x{orig[i]:04x} got 0x{w.value:04x}")
        all_ok = False

if all_ok:
    print("\nAll 256 words written and verified OK!")
    print(f"\nFinal config:")
    print(f"  Word 3: 0x{orig[3]:04x} (ChA=FIFO, ChB=UART)")
    print(f"  Word 5: 0x{orig[5]:04x} (ChB VCP=1)")
    print(f"  Word 9: 0x{orig[9]:04x} (strings enabled)")
    print(f"  Chksum: 0x{orig[127]:04x} / 0x{orig[255]:04x}")
    print("\nUnplug USB, wait 3s, replug.")
    print("Expected: Vivado sees Basys3 (ChA D2XX) + COM port appears (ChB VCP)")

ft.FT_Close(handle)
