"""Backup full FT2232H EEPROM to a timestamped file.

The Basys3 FT2232H EEPROM is 256 words = 512 bytes.
We also save it in multiple formats for safety:
- Binary (raw bytes, little-endian words)
- Hex (human readable)
- JSON (with metadata for restoration)
"""
import ctypes
import struct
import json
import datetime
import os

ftd2xx = ctypes.windll.FTD2XX
ftd2xx.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ftd2xx.FT_Open.restype = ctypes.c_uint32
ftd2xx.FT_Close.argtypes = [ctypes.c_void_p]
ftd2xx.FT_Close.restype = ctypes.c_uint32
ftd2xx.FT_ReadEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint16)]
ftd2xx.FT_ReadEE.restype = ctypes.c_uint32

# Open Channel A
handle = ctypes.c_void_p()
status = ftd2xx.FT_Open(0, ctypes.byref(handle))
if status != 0:
    print(f"FT_Open(0) failed: {status}")
    print("Make sure Vivado/hw_server is closed.")
    exit(1)

# Read all 256 words
words = []
for i in range(256):
    w = ctypes.c_uint16()
    s = ftd2xx.FT_ReadEE(handle, i, ctypes.byref(w))
    if s != 0:
        print(f"FT_ReadEE failed at word {i}: {s}")
        ftd2xx.FT_Close(handle)
        exit(1)
    words.append(w.value)

ftd2xx.FT_Close(handle)

# Verify checksum (FT2232H: XOR of words 0..254, stored in word 255)
calc_cs = 0
for w in words[:255]:
    calc_cs ^= w
print(f"Read {len(words)} words ({len(words)*2} bytes)")
print(f"Stored checksum (word 255): 0x{words[255]:04x}")
print(f"Calculated checksum (XOR 0..254): 0x{calc_cs:04x}")
print(f"Match: {words[255] == calc_cs}")

# Generate timestamp
ts = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
backup_dir = os.path.join('sim', 'eeprom_backups')
os.makedirs(backup_dir, exist_ok=True)

# Save binary
bin_path = os.path.join(backup_dir, f'eeprom_backup_{ts}.bin')
with open(bin_path, 'wb') as f:
    for w in words:
        f.write(struct.pack('<H', w))
print(f"\nSaved binary: {bin_path}")

# Save hex (word-level)
hex_path = os.path.join(backup_dir, f'eeprom_backup_{ts}.hex')
with open(hex_path, 'w') as f:
    f.write(f"# FT2232H EEPROM backup - {ts}\n")
    f.write(f"# Basys3 S/N: 210183A8A984\n")
    f.write(f"# 256 words = 512 bytes\n")
    f.write(f"# Format: word_index: value (hex)\n")
    for i, w in enumerate(words):
        f.write(f"{i:3d} (0x{i*2:04x}): 0x{w:04x}\n")
print(f"Saved hex: {hex_path}")

# Save JSON with metadata
json_path = os.path.join(backup_dir, f'eeprom_backup_{ts}.json')
backup_data = {
    'timestamp': ts,
    'device': 'FT2232H on Basys3',
    'serial_number': '210183A8A984',
    'vid': f'0x{words[0]:04x}',
    'pid': f'0x{words[1]:04x}',
    'bcd_device': f'0x{words[2]:04x}',
    'config_word_3': f'0x{words[3]:04x}',
    'config_word_4': f'0x{words[4]:04x}',
    'config_word_5': f'0x{words[5]:04x}',
    'config_word_6': f'0x{words[6]:04x}',
    'config_word_7': f'0x{words[7]:04x}',
    'stored_checksum': f'0x{words[255]:04x}',
    'calculated_checksum': f'0x{calc_cs:04x}',
    'checksum_algorithm': 'XOR of words 0..254',
    'num_words': len(words),
    'words_hex': [f'0x{w:04x}' for w in words],
}
with open(json_path, 'w') as f:
    json.dump(backup_data, f, indent=2)
print(f"Saved JSON: {json_path}")

# Also create a "latest" symlink/copy for easy restoration
latest_bin = os.path.join(backup_dir, 'eeprom_backup_latest.bin')
with open(latest_bin, 'wb') as f:
    for w in words:
        f.write(struct.pack('<H', w))
print(f"Saved latest: {latest_bin}")

# Also save in the old location for compatibility
with open('eeprom_dump_current.bin', 'wb') as f:
    for w in words:
        f.write(struct.pack('<H', w))
print(f"Updated: eeprom_dump_current.bin")

print("\n=== Backup complete! ===")
print(f"To restore: python sim\\restore_eeprom_full.py {bin_path}")
