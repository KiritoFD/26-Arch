"""Scan full 256-word EEPROM for string data and find 'program_ftdi' garbage."""
import struct

# Current EEPROM (just read via D2XX)
with open('sim/eeprom_backups/eeprom_current_after_vid_fix.bin', 'rb') as f:
    cur_data = f.read()
cur = list(struct.unpack('<' + 'H'*(len(cur_data)//2), cur_data))

# Original (working) EEPROM
with open('sim/eeprom_backups/eeprom_backup_20260627_072124.bin', 'rb') as f:
    orig_data = f.read()
orig = list(struct.unpack('<' + 'H'*(len(orig_data)//2), orig_data))

print("=== Non-zero words in CURRENT EEPROM (beyond word 9) ===")
for i in range(10, 256):
    if cur[i] != 0:
        print(f"  Word {i:3d} (0x{i*2:04x}): 0x{cur[i]:04x}  orig=0x{orig[i]:04x} {'*** DIFF' if cur[i]!=orig[i] else ''}")

print("\n=== Non-zero words in ORIGINAL EEPROM (beyond word 9) ===")
for i in range(10, 256):
    if orig[i] != 0:
        # Try to decode as UTF-16LE chars
        lo = orig[i] & 0xff
        hi = (orig[i] >> 8) & 0xff
        chars = ''
        if 0x20 <= lo < 0x7f and hi == 0:
            chars = f"  '{chr(lo)}'"
        if 0x20 <= hi < 0x7f and lo == 0:
            chars = f"  '{chr(hi)}'"
        print(f"  Word {i:3d} (0x{i*2:04x}): 0x{orig[i]:04x}  cur=0x{cur[i]:04x}{chars}{'*** DIFF' if cur[i]!=orig[i] else ''}")

# Try to find "program_ftdi" in current EEPROM as UTF-16LE
print("\n=== Searching for 'program_ftdi' in current EEPROM (UTF-16LE) ===")
target = "program_ftdi"
target_words = [ord(c) for c in target]
for start in range(256 - len(target_words)):
    match = True
    for j, tw in enumerate(target_words):
        if cur[start + j] != tw:
            match = False
            break
    if match:
        print(f"  FOUND at word {start} (0x{start*2:04x})!")
        # Show the full string
        s = ''
        for k in range(start, min(start + 40, 256)):
            if cur[k] == 0:
                break
            if 0x20 <= cur[k] < 0x7f:
                s += chr(cur[k])
            else:
                s += f'[{cur[k]:04x}]'
        print(f"  String: '{s}'")

# Also search in original
print("\n=== Searching for 'Basys3' in original EEPROM (UTF-16LE) ===")
target2 = "Basys3"
target_words2 = [ord(c) for c in target2]
for start in range(256 - len(target_words2)):
    match = True
    for j, tw in enumerate(target_words2):
        if orig[start + j] != tw:
            match = False
            break
    if match:
        print(f"  FOUND at word {start} (0x{start*2:04x})!")
        s = ''
        for k in range(max(0, start-2), min(start + 20, 256)):
            if orig[k] == 0 and k > start:
                break
            if 0x20 <= orig[k] < 0x7f:
                s += chr(orig[k])
            else:
                s += f'[{orig[k]:04x}]'
        print(f"  Context: '{s}'")

print("\n=== Searching for 'Digilent' in original EEPROM (UTF-16LE) ===")
target3 = "Digilent"
target_words3 = [ord(c) for c in target3]
for start in range(256 - len(target_words3)):
    match = True
    for j, tw in enumerate(target_words3):
        if orig[start + j] != tw:
            match = False
            break
    if match:
        print(f"  FOUND at word {start} (0x{start*2:04x})!")
        s = ''
        for k in range(max(0, start-2), min(start + 20, 256)):
            if orig[k] == 0 and k > start:
                break
            if 0x20 <= orig[k] < 0x7f:
                s += chr(orig[k])
            else:
                s += f'[{orig[k]:04x}]'
        print(f"  Context: '{s}'")
