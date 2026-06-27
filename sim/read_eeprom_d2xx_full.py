"""Read full EEPROM (256 words) via D2XX and decode all fields including strings."""
import ctypes
import struct
import sys

ft = ctypes.WinDLL('ftd2xx.dll')

ft.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ft.FT_Open.restype = ctypes.c_uint32
ft.FT_ReadEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint16)]
ft.FT_ReadEE.restype = ctypes.c_uint32
ft.FT_Close.argtypes = [ctypes.c_void_p]
ft.FT_Close.restype = ctypes.c_uint32
ft.FT_GetDeviceInfo.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_uint32),
                                 ctypes.POINTER(ctypes.c_uint32), ctypes.c_char_p,
                                 ctypes.c_char_p, ctypes.c_void_p]
ft.FT_GetDeviceInfo.restype = ctypes.c_uint32

handle = ctypes.c_void_p()
status = ft.FT_Open(0, ctypes.byref(handle))
if status != 0:
    print(f'FT_Open(0) failed: {status}')
    print('Try: close Vivado/hw_server first')
    sys.exit(1)

# Get device info
dev_type = ctypes.c_uint32()
dev_id = ctypes.c_uint32()
sn_buf = ctypes.create_string_buffer(64)
desc_buf = ctypes.create_string_buffer(256)
status = ft.FT_GetDeviceInfo(handle, ctypes.byref(dev_type), ctypes.byref(dev_id),
                             sn_buf, desc_buf, None)
if status == 0:
    print(f"Device: type={dev_type.value}, id=0x{dev_id.value:08x}")
    print(f"  Serial: {sn_buf.value.decode('ascii', errors='replace')}")
    print(f"  Description: {desc_buf.value.decode('ascii', errors='replace')}")

# Read 256 words
words = []
for i in range(256):
    w = ctypes.c_uint16()
    s = ft.FT_ReadEE(handle, i, ctypes.byref(w))
    if s != 0:
        print(f'Read failed at word {i}: {s}')
        break
    words.append(w.value)

ft.FT_Close(handle)

if len(words) < 128:
    print('Failed to read EEPROM')
    sys.exit(1)

print(f"\nRead {len(words)} words")
print(f"\n=== Header ===")
print(f"Word 0  (PID):        0x{words[0]:04x}")
print(f"Word 1  (VID):        0x{words[1]:04x}")
print(f"Word 2  (Release):    0x{words[2]:04x}")
print(f"Word 3  (Config):     0x{words[3]:04x}")
print(f"Word 4  (Config):     0x{words[4]:04x}")
print(f"Word 5  (Config2):     0x{words[5]:04x}")

# Decode word 3 (Channel A config)
w3 = words[3]
print(f"\n=== Channel A Config (word 3 = 0x{w3:04x}) ===")
# Bit fields for FT2232H config word
# Bits 0-7: various
# Common interpretation:
print(f"  Channel A Driver: {'VCP' if (w3 & 0x01) == 0 else 'D2XX only'} (bit0={w3&1})")
print(f"  bit1 (self_pwrd): {bool(w3 & 0x02)}")
print(f"  bit2 (remote_wkup): {bool(w3 & 0x04)}")
print(f"  bit3 (ISet): {(w3 >> 3) & 0x07}")
print(f"  bit6 (USB_pull_en): {bool(w3 & 0x40)}")
print(f"  bit7 (ext_osc): {bool(w3 & 0x80)}")
print(f"  HighByte (Channel A type): 0x{(w3 >> 8) & 0xff:02x}")
chA_type = (w3 >> 8) & 0xff
ch_types = {0: 'UART', 0x10: 'FIFO', 0x20: 'OPTO', 0x30: 'CBUS', 0x40: 'SYNC_FIFO'}
print(f"    -> {ch_types.get(chA_type & 0xf0, f'unknown 0x{chA_type:02x}')}")

# Decode word 4 (Channel B config)
w4 = words[4]
print(f"\n=== Channel B Config (word 4 = 0x{w4:04x}) ===")
print(f"  Channel B Driver: {'VCP' if (w4 & 0x01) == 0 else 'D2XX only'} (bit0={w4&1})")
chB_type = (w4 >> 8) & 0xff
print(f"  HighByte (Channel B type): 0x{chB_type:02x}")
print(f"    -> {ch_types.get(chB_type & 0xf0, f'unknown 0x{chB_type:02x}')}")

print(f"\n=== USB Strings (word 6=ManuStrIndex, 7=ProdStrIndex, 8=SerStrIndex) ===")
# For FT2232H, the string descriptor indices are embedded differently.
# Word 3/4 have string index bits; the actual strings are in a string table.
# Try standard string decode from the string descriptors seen by USB stack.
print(f"  Word 6: 0x{words[6]:04x}")
print(f"  Word 7: 0x{words[7]:04x}")
print(f"  Word 8: 0x{words[8]:04x}")

# Check checksums
cs_127 = 0
for w in words[:127]:
    cs_127 ^= w
cs_255 = 0
for w in words[:255]:
    cs_255 ^= w
print(f"\n=== Checksums ===")
print(f"  Word 127: stored=0x{words[127]:04x}, computed=0x{cs_127:04x}, {'OK' if words[127]==cs_127 else 'MISMATCH'}")
print(f"  Word 255: stored=0x{words[255]:04x}, computed=0x{cs_255:04x}, {'OK' if words[255]==cs_255 else 'MISMATCH'}")

# Dump first 40 words for reference
print(f"\n=== Full dump words 0-39 ===")
for i in range(0, 40, 8):
    line = ' '.join(f'{words[j]:04x}' for j in range(i, min(i+8, len(words))))
    print(f'  {i:3d}: {line}')

# Save raw
with open('sim/eeprom_backups/eeprom_current_after_vid_fix.bin', 'wb') as f:
    f.write(struct.pack('<' + 'H'*len(words), *words))
print(f'\nSaved to sim/eeprom_backups/eeprom_current_after_vid_fix.bin')
