"""Check original VID/PID from backup files."""
import struct
import os

backups = [
    'sim/eeprom_backups/eeprom_backup_20260627_072124.bin',  # Original board (Vivado OK)
    'sim/eeprom_backups/eeprom_backup_20260627_065956.bin',  # Current board (broken)
    'sim/eeprom_backups/eeprom_backup_20260627_064416.bin',  # Earlier backup
]

for path in backups:
    if not os.path.exists(path):
        continue
    with open(path, 'rb') as f:
        data = f.read()
    words = list(struct.unpack('<' + 'H'*(len(data)//2), data))
    print(f"\n{path}:")
    print(f"  Word 0 (PID):     0x{words[0]:04x}")
    print(f"  Word 1 (VID):     0x{words[1]:04x}")
    print(f"  Word 2 (release): 0x{words[2]:04x}")
    # Decode as bytes (little-endian)
    pid_bytes = struct.pack('<H', words[0])
    vid_bytes = struct.pack('<H', words[1])
    print(f"  PID bytes: {pid_bytes.hex()} -> USB PID = 0x{words[0]:04x}")
    print(f"  VID bytes: {vid_bytes.hex()} -> USB VID = 0x{words[1]:04x}")
