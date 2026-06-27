"""Deep comparison of header words 0-13 between original and current."""
import struct

with open('sim/eeprom_backups/eeprom_backup_20260627_072124.bin', 'rb') as f:
    orig_data = f.read()
orig = list(struct.unpack('<' + 'H'*(len(orig_data)//2), orig_data))

with open('sim/eeprom_backups/eeprom_current_after_vid_fix.bin', 'rb') as f:
    cur_data = f.read()
cur = list(struct.unpack('<' + 'H'*(len(cur_data)//2), cur_data))

print("=== Header words 0-13 ===")
print(f"{'Word':<6} {'Orig':<8} {'Cur':<8} {'Match':<8}")
for i in range(14):
    match = "SAME" if orig[i] == cur[i] else "*** DIFF"
    print(f"{i:<6} 0x{orig[i]:04x}   0x{cur[i]:04x}   {match}")

# Word 9 is critical - it contains string offsets
print(f"\n=== Word 9 decode (string offsets) ===")
print(f"  orig=0x{orig[9]:04x} = {orig[9]:016b}")
print(f"  cur =0x{cur[9]:04x} = {cur[9]:016b}")
print(f"  orig high byte: 0x{(orig[9]>>8)&0xff:02x} = {(orig[9]>>8)&0xff}")
print(f"  orig low byte:  0x{orig[9]&0xff:02x} = {orig[9]&0xff}")

# Word 12 also - 0x0056
print(f"\n=== Word 12 decode ===")
print(f"  orig=0x{orig[12]:04x}")
print(f"  cur =0x{cur[12]:04x}")

# Check full string table in original (words 77-120)
print(f"\n=== Original string table (words 77-120) ===")
for i in range(77, 120):
    lo = orig[i] & 0xff
    hi = (orig[i] >> 8) & 0xff
    c_lo = chr(lo) if 0x20 <= lo < 0x7f else '.'
    c_hi = chr(hi) if 0x20 <= hi < 0x7f else '.'
    diff = " ***" if cur[i] != orig[i] else ""
    print(f"  word {i:3d}: orig=0x{orig[i]:04x} cur=0x{cur[i]:04x}  '{c_lo}{c_hi}'{diff}")

# Check what string index points to
print(f"\n=== Word 7 (string descriptor indices) ===")
print(f"  orig=0x{orig[7]:04x} = {orig[7]:016b}")
print(f"  cur =0x{cur[7]:04x} = {cur[7]:016b}")
sn_idx = orig[7] & 0x1f
prod_idx = (orig[7] >> 5) & 0x1f
manu_idx = (orig[7] >> 10) & 0x1f
print(f"  Serial string index: {sn_idx}")
print(f"  Product string index: {prod_idx}")
print(f"  Manufacturer string index: {manu_idx}")

# Check word 9 (0x1ad4 orig vs 0x12d4 cur) - this differs!
print(f"\n=== Word 9 decode (differs!) ===")
print(f"  orig=0x{orig[9]:04x}  cur=0x{cur[9]:04x}  diff=0x{orig[9]^cur[9]:04x}")
# Word 9 in FT2232H contains "USB Power" / string table offset / max power
# Bits 0-7: MaxPower (in 2mA units)
# Bits 8-15: PollingTimeout / USBVersion
print(f"  orig low byte (MaxPower?): {orig[9]&0xff} = {(orig[9]&0xff)*2}mA")
print(f"  cur low byte (MaxPower?): {cur[9]&0xff} = {(cur[9]&0xff)*2}mA")
print(f"  orig high byte: 0x{(orig[9]>>8)&0xff:02x}")
print(f"  cur high byte:  0x{(cur[9]>>8)&0xff:02x}")

# Word 137 is the mirror in image 2
print(f"\n=== Word 137 (image 2 mirror of word 9) ===")
print(f"  orig=0x{orig[137]:04x}  cur=0x{cur[137]:04x}")
