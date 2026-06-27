"""Compare EEPROM of original board (Vivado works) vs current board (COM7, Vivado fails).

Original board: sim/eeprom_backups/eeprom_backup_20260627_064416.bin (SN 210183A8A984)
  - Vivado works, no COM port
  - Desc = "Digilent USB Device A"

Current board: sim/eeprom_backups/eeprom_backup_20260627_065956.bin (SN 7&150BDE91)
  - COM7 exists (Channel A VCP)
  - Vivado fails
  - Desc = "Dual RS232-HS A"

Key question: what makes Vivado recognize a Basys3?
"""
import struct

boards = [
    ('Original (Vivado OK, no COM)', 'sim/eeprom_backups/eeprom_backup_20260627_064416.bin'),
    ('Current  (COM7, Vivado FAIL)',  'sim/eeprom_backups/eeprom_backup_20260627_065956.bin'),
]

print(f"{'Word':<6} {'Offset':<8} {'Original':<10} {'Current':<10} {'Diff':<6}")
print("-" * 50)

orig_words = None
curr_words = None
for name, path in boards:
    with open(path, 'rb') as f:
        data = f.read()
    words = list(struct.unpack('<' + 'H'*(len(data)//2), data))
    if 'Original' in name:
        orig_words = words
    else:
        curr_words = words

# Compare config words (0-9)
for i in range(10):
    o = orig_words[i]
    c = curr_words[i]
    diff = "***" if o != c else ""
    print(f"{i:<6} 0x{i*2:04x}   0x{o:04x}     0x{c:04x}     {diff}")

# Detailed interpretation
print("\n=== Config interpretation ===")
print(f"Word 0 (VID):      orig=0x{orig_words[0]:04x}  curr=0x{curr_words[0]:04x}")
print(f"Word 1 (PID):      orig=0x{orig_words[1]:04x}  curr=0x{curr_words[1]:04x}")
print(f"Word 2 (bcdDev):   orig=0x{orig_words[2]:04x}  curr=0x{curr_words[2]:04x}")
print(f"Word 3 (ChanType): orig=0x{orig_words[3]:04x}  curr=0x{curr_words[3]:04x}")
print(f"Word 4 (USB power): orig=0x{orig_words[4]:04x}  curr=0x{curr_words[4]:04x}")
print(f"Word 5 (VCP/FIFO): orig=0x{orig_words[5]:04x}  curr=0x{curr_words[5]:04x}")
print(f"Word 6 (ChanA opt): orig=0x{orig_words[6]:04x}  curr=0x{curr_words[6]:04x}")
print(f"Word 7 (ChanB opt): orig=0x{orig_words[7]:04x}  curr=0x{curr_words[7]:04x}")

# Word 5 bit interpretation (FT2232H)
print("\n=== Word 5 bit analysis (FT2232H VCP/FIFO flags) ===")
names = {
    0: 'AIsHighCurrent',
    1: 'BIsHighCurrent',
    2: 'IFAIsFifo',
    3: 'IFAIsFifoTar',
    4: 'IFAIsFastSer',
    5: 'AIsVCP (A=COM port)',
    6: 'IFBIsFifo',
    7: 'IFBIsFifoTar',
    8: 'IFBIsFastSer',
    9: 'BIsVCP (B=COM port)',
    10: 'PullDownEnable',
    11: 'SerNumEnable',
    12: 'USBVersionEnable',
}
for label, w in [('Original', orig_words[5]), ('Current', curr_words[5])]:
    print(f"\n  {label} word 5 = 0x{w:04x} = {w:016b}")
    for bit in range(13):
        if w & (1 << bit):
            print(f"    bit {bit}: {names.get(bit, '?')} = SET")

# Find USB string descriptors
print("\n=== USB String Descriptors ===")
for label, data in [('Original', bytes())]:
    pass  # will fill below

for name, path in boards:
    with open(path, 'rb') as f:
        data = f.read()
    print(f"\n{name}:")
    # Find string descriptors (format: length, 0x03, UTF-16LE)
    i = 0x14  # start of string area
    while i < len(data) - 2:
        if data[i+1] == 0x03 and data[i] > 2 and data[i] < 60:
            length = data[i]
            if i + length <= len(data):
                s = data[i+2:i+length].decode('utf-16-le', errors='replace')
                print(f"  @0x{i:02x}: '{s}' (len={length})")
                i += length
                continue
        i += 1
