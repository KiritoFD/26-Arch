"""Check all EEPROM backups for valid checksums."""
import struct
import os
import glob

backups = sorted(glob.glob('sim/eeprom_backups/*.bin'))
# Also check root-level backups
backups += ['eeprom_backup_before_a_b_swap.bin', 'eeprom_backup_before_restore.bin',
            'eeprom_dump_current.bin', 'eeprom_full.bin', 'sim/eeprom_backup.bin',
            'sim/eeprom_full.bin']

for path in backups:
    if not os.path.exists(path):
        continue
    with open(path, 'rb') as f:
        data = f.read()
    if len(data) < 512:
        print(f"{path}: too small ({len(data)} bytes)")
        continue
    words = list(struct.unpack('<' + 'H'*(len(data)//2), data))
    if len(words) < 256:
        print(f"{path}: only {len(words)} words")
        continue

    cs127 = 0
    for w in words[:127]:
        cs127 ^= w
    cs255 = 0
    for w in words[128:255]:
        cs255 ^= w

    ok127 = "OK" if cs127 == words[127] else "FAIL"
    ok255 = "OK" if cs255 == words[255] else "FAIL"

    print(f"{path}")
    print(f"  word 1 (VID) =0x{words[1]:04x}  word 3 =0x{words[3]:04x}  word 5 =0x{words[5]:04x}  word 9 =0x{words[9]:04x}")
    print(f"  word 127: expected=0x{cs127:04x} actual=0x{words[127]:04x} {ok127}")
    print(f"  word 255: expected=0x{cs255:04x} actual=0x{words[255]:04x} {ok255}")

    # Check string area (words 140-170 roughly)
    s_bytes = b''
    for i in range(140, 180):
        s_bytes += struct.pack('<H', words[i])
    has_basys3 = b'Basys3' in s_bytes or b'asys3' in s_bytes
    has_digilent = b'Digilent' in s_bytes or b'igilent' in s_bytes
    print(f"  strings: Basys3={has_basys3} Digilent={has_digilent}")
    print()
