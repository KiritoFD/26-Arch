"""Compare two FT2232H EEPROM backups and show config differences.

Original board (SN 210183A8A984, Vivado works, no COM):
  sim\eeprom_backups\eeprom_backup_20260627_064416.bin

New board (SN 210183A8AC3D, has COM8, Vivado doesn't recognize):
  sim\eeprom_backups\eeprom_backup_20260627_065210.bin
"""
import struct
import os

orig_path = 'sim/eeprom_backups/eeprom_backup_20260627_064416.bin'  # original
new_path = 'sim/eeprom_backups/eeprom_backup_20260627_065210.bin'     # new board

with open(orig_path, 'rb') as f:
    orig_data = f.read()
with open(new_path, 'rb') as f:
    new_data = f.read()

orig_words = list(struct.unpack('<' + 'H'*(len(orig_data)//2), orig_data))
new_words = list(struct.unpack('<' + 'H'*(len(new_data)//2), new_data))

print(f"Original board (SN 210183A8A984): {len(orig_words)} words, checksum=0x{orig_words[255]:04x}")
print(f"New board      (SN 210183A8AC3D): {len(new_words)} words, checksum=0x{new_words[255]:04x}")

# Compare configuration words (0-9, the meaningful area)
print("\n=== Configuration word comparison (words 0-9) ===")
for i in range(10):
    o = orig_words[i]
    n = new_words[i]
    diff = " *** DIFFERENT ***" if o != n else ""
    print(f"  Word {i} (0x{i*2:02x}): orig=0x{o:04x}  new=0x{n:04x}{diff}")

# Detailed interpretation of key words
print("\n=== Detailed interpretation ===")

def interpret_word3(w):
    """Word 3 = Channel A type (low byte) | Channel B type (high byte)"""
    a_type = w & 0xFF
    b_type = (w >> 8) & 0xFF
    type_names = {0: 'UART', 1: '245FIFO', 2: 'CPUFIFO', 3: 'OPTO', 4: '1284'}
    return f"Channel A type=0x{a_type:02x}({type_names.get(a_type,'?')}), Channel B type=0x{b_type:02x}({type_names.get(b_type,'?')})"

def interpret_word5_ft2232h(w):
    """Word 5 in FT2232H contains VCP/FIFO flags.

    FT2232H word 5 (from FTDI AN_135, "Driver / Hardware I/O options"):
    bit 0   = AIsHighCurrent
    bit 1   = BIsHighCurrent
    bit 2   = IFAIsFifo        (Channel A interface is FIFO)
    bit 3   = IFAIsFifoTar
    bit 4   = IFAIsFastSer
    bit 5   = AIsVCP           <-- Channel A VCP enable
    bit 6   = IFBIsFifo        (Channel B interface is FIFO)
    bit 7   = IFBIsFifoTar
    bit 8   = IFBIsFastSer
    bit 9   = BIsVCP           <-- Channel B VCP enable
    bit 10  = PullDownEnable5
    bit 11  = SerNumEnable5
    bit 12  = USBVersionEnable5
    bit 13-15 = IsoInA/IsoInB/IsoOutA/IsoOutB (varies)

    NOTE: bit positions vary by source. We'll show all bit values.
    """
    bits = []
    for bit in range(16):
        if w & (1 << bit):
            bits.append(bit)
    names = {
        0: 'AIsHighCurrent',
        1: 'BIsHighCurrent',
        2: 'IFAIsFifo (A=FIFO)',
        3: 'IFAIsFifoTar',
        4: 'IFAIsFastSer',
        5: 'AIsVCP (A=VCP/COM)',  # KEY
        6: 'IFBIsFifo (B=FIFO)',
        7: 'IFBIsFifoTar',
        8: 'IFBIsFastSer',
        9: 'BIsVCP (B=VCP/COM)',  # KEY
        10: 'PullDownEnable5',
        11: 'SerNumEnable5',
        12: 'USBVersionEnable5',
        13: 'IsoInA',
        14: 'IsoInB',
        15: 'IsoOut',
    }
    return bits, names

print("\nWord 3 (channel types):")
print(f"  Original: 0x{orig_words[3]:04x} = {interpret_word3(orig_words[3])}")
print(f"  New:      0x{new_words[3]:04x} = {interpret_word3(new_words[3])}")

print("\nWord 5 (VCP/FIFO flags) - THE KEY DIFFERENCE:")
for label, w in [('Original', orig_words[5]), ('New', new_words[5])]:
    bits, names = interpret_word5_ft2232h(w)
    print(f"  {label}: 0x{w:04x} = binary {w:016b}")
    print(f"    Set bits: {bits}")
    for b in bits:
        print(f"      bit {b}: {names.get(b, '?')}")

# Also check word 6, 7 (channel-specific FIFO options)
print("\nWord 6 (Channel A FIFO options):")
print(f"  Original: 0x{orig_words[6]:04x}")
print(f"  New:      0x{new_words[6]:04x}")

print("\nWord 7 (Channel B FIFO options):")
print(f"  Original: 0x{orig_words[7]:04x}")
print(f"  New:      0x{new_words[7]:04x}")

# Show all differing words
print("\n=== All differing words ===")
diff_count = 0
for i in range(256):
    if orig_words[i] != new_words[i]:
        diff_count += 1
        if i < 16 or diff_count < 20:
            print(f"  Word {i:3d} (0x{i*2:04x}): orig=0x{orig_words[i]:04x}  new=0x{new_words[i]:04x}")
print(f"\nTotal differing words: {diff_count}")

# Look for "Basys3" and "Digilent" strings in both
print("\n=== Strings comparison ===")
for label, data in [('Original', orig_data), ('New', new_data)]:
    print(f"\n{label} board strings:")
    # Search for UTF-16LE "Digilent" or "Basys3"
    for needle_str in ['Digilent', 'Basys3', '210183A8']:
        needle = needle_str.encode('utf-16-le')
        idx = data.find(needle)
        if idx >= 0:
            # Get the full string (find length byte before)
            if idx > 0:
                length = data[idx-1]
                full = data[idx:idx+length-2].decode('utf-16-le', errors='replace')
                print(f"  '{needle_str}' at offset 0x{idx-1:02x}, length={length}: '{full}'")
            else:
                print(f"  '{needle_str}' at offset 0x{idx:02x} (no length byte before)")

# Print non-zero region
print("\n=== Non-zero data summary ===")
for label, words_list in [('Original', orig_words), ('New', new_words)]:
    last_nz = 0
    for i, w in enumerate(words_list):
        if w != 0:
            last_nz = i
    print(f"  {label}: last non-zero word = {last_nz} (offset 0x{last_nz*2:04x})")
