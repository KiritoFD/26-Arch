"""Show the string area (word 10-40) in detail for both boards."""
import struct

orig_path = 'sim/eeprom_backups/eeprom_backup_20260627_072124.bin'  # Vivado OK
fail_path = 'sim/eeprom_backups/eeprom_backup_20260627_065956.bin'  # Vivado FAIL

for label, path in [('Original (Vivado OK)', orig_path), ('Current (Vivado FAIL)', fail_path)]:
    with open(path, 'rb') as f:
        data = f.read()

    print(f"\n=== {label} ===")
    print("String area (word 10-40, offset 0x14-0x50):")
    for i in range(0x14, 0x50, 16):
        hex_str = ' '.join(f'{b:02x}' for b in data[i:i+16])
        ascii_str = ''.join(chr(b) if 32 <= b < 127 else '.' for b in data[i:i+16])
        print(f"  {i:04x}: {hex_str}  |{ascii_str}|")

    # Also show word 40-44 (0x50-0x58) which had the VCP flag difference earlier
    print("Word 40-44 (offset 0x50-0x58):")
    for i in range(0x50, 0x58, 2):
        w = struct.unpack('<H', data[i:i+2])[0]
        print(f"  word {i//2} (0x{i:02x}): 0x{w:04x}")

    # Show the USB descriptor area (0x90-0xF0)
    print("USB descriptor area (offset 0x90-0xF0):")
    for i in range(0x90, 0xF0, 16):
        hex_str = ' '.join(f'{b:02x}' for b in data[i:i+16])
        ascii_str = ''.join(chr(b) if 32 <= b < 127 else '.' for b in data[i:i+16])
        print(f"  {i:04x}: {hex_str}  |{ascii_str}|")
