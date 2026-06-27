"""Compare EEPROM of original board (Vivado OK) vs current board (Vivado FAIL).

Original board (Vivado OK):    sim/eeprom_backups/eeprom_backup_20260627_072124.bin (SN 210183A8A984)
Current board (Vivado FAIL):   sim/eeprom_backups/eeprom_backup_20260627_065956.bin (SN 210183A8AC3D)
"""
import struct

orig_path = 'sim/eeprom_backups/eeprom_backup_20260627_072124.bin'  # Vivado OK
fail_path = 'sim/eeprom_backups/eeprom_backup_20260627_065956.bin'  # Vivado FAIL

with open(orig_path, 'rb') as f:
    orig_data = f.read()
with open(fail_path, 'rb') as f:
    fail_data = f.read()

orig = list(struct.unpack('<' + 'H'*(len(orig_data)//2), orig_data))
fail = list(struct.unpack('<' + 'H'*(len(fail_data)//2), fail_data))

print(f"Original (Vivado OK, SN 210183A8A984): checksum=0x{orig[255]:04x}")
print(f"Current  (Vivado FAIL, SN 210183A8AC3D): checksum=0x{fail[255]:04x}")

# Show ALL differing words (not just first 10)
print("\n=== ALL differing words ===")
diffs = []
for i in range(256):
    if orig[i] != fail[i]:
        diffs.append((i, orig[i], fail[i]))

for i, o, f in diffs:
    print(f"  Word {i:3d} (0x{i*2:04x}): orig=0x{o:04x}  fail=0x{f:04x}  diff_bits={bin(o^f)}")

print(f"\nTotal differing words: {len(diffs)}")

# Focus on config words (0-9)
print("\n=== Config words (0-9) ===")
for i in range(10):
    o = orig[i]
    f = fail[i]
    same = "SAME" if o == f else "*** DIFFERENT ***"
    print(f"  Word {i} (0x{i*2:02x}): orig=0x{o:04x}  fail=0x{f:04x}  {same}")

# Decode word 3, 4, 5, 6, 7 with bit-level detail
print("\n=== Bit-level decode of config words ===")
bit_names_w3 = {
    0: 'ChanA type bit0', 1: 'ChanA type bit1', 2: 'ChanA type bit2', 3: 'ChanA type bit3',
    4: 'ChanA type bit4', 5: 'ChanA type bit5', 6: 'ChanA type bit6', 7: 'ChanA type bit7',
    8: 'ChanB type bit0', 9: 'ChanB type bit1', 10: 'ChanB type bit2', 11: 'ChanB type bit3',
    12: 'ChanB type bit4', 13: 'ChanB type bit5', 14: 'ChanB type bit6', 15: 'ChanB type bit7',
}
bit_names_w5 = {
    0: 'AIsHighCurrent', 1: 'BIsHighCurrent', 2: 'IFAIsFifo', 3: 'IFAIsFifoTar',
    4: 'IFAIsFastSer', 5: 'AIsVCP', 6: 'IFBIsFifo', 7: 'IFBIsFifoTar',
    8: 'IFBIsFastSer', 9: 'BIsVCP', 10: 'PullDownEnable', 11: 'SerNumEnable',
    12: 'USBVersionEnable',
}

for word_idx, names in [(3, bit_names_w3), (5, bit_names_w5), (7, None)]:
    o = orig[word_idx]
    f = fail[word_idx]
    if o == f:
        print(f"\nWord {word_idx} = 0x{o:04x} (SAME in both)")
        if names:
            for bit in range(16):
                if o & (1 << bit):
                    print(f"  bit {bit}: {names.get(bit, '?')} = SET")
    else:
        print(f"\nWord {word_idx}: orig=0x{o:04x}  fail=0x{f:04x} *** DIFFERENT ***")
        if names:
            for bit in range(16):
                o_set = bool(o & (1 << bit))
                f_set = bool(f & (1 << bit))
                if o_set != f_set:
                    print(f"  bit {bit}: {names.get(bit, '?')}: orig={'SET' if o_set else 'CLR'} fail={'SET' if f_set else 'CLR'} ***")

# Also check word 7 in detail (it had 0x129a)
print(f"\nWord 7 detail:")
print(f"  orig=0x{orig[7]:04x} = {orig[7]:016b}")
print(f"  fail=0x{fail[7]:04x} = {fail[7]:016b}")
