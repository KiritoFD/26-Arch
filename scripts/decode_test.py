val = 0x00028367
opcode = val & 0x7f
rd = (val >> 7) & 0x1f
funct3 = (val >> 12) & 0x7
rs1 = (val >> 15) & 0x1f
imm = (val >> 20) & 0xfff
if imm & 0x800:
    imm = imm - 0x1000
regnames = {0:'x0/zero', 3:'x3/t1', 5:'x5/t0', 10:'x10/a0', 11:'x11/a1'}
print(f"Instruction 0x{val:08x}:")
print(f"  opcode = {opcode:#x} (JALR)")
print(f"  rd     = x{rd} ({regnames.get(rd, '?')})")
print(f"  funct3 = {funct3}")
print(f"  rs1    = x{rs1} ({regnames.get(rs1, '?')})")
print(f"  imm    = {imm}")
print()

# Check what jalr t1,t0,0 would encode to
target_val = (5 << 15) | (3 << 7) | 0x67  # rs1=5(t0), rd=3(t1), opcode=JALR
print(f"jalr t1,t0,0 encodes to: 0x{target_val:08x}")
print(f"  rs1 = x{(target_val>>15)&0x1f} ({regnames.get((target_val>>15)&0x1f, '?')})")
print()

# So if disassembler says jalr t1,t0 but actual encoding has rs1=x10, 
# disassembler is WRONG. Actual instruction is jalr t1, a0, 0.
# After setup_test, a0 = test_state = 0.
# JALR target = (0 + 0) & ~1 = 0
print("After setup_test: a0 = test_state = 0")
print("JALR target = (a0 + 0) & ~1 = 0")
print("Address 0 is 4-byte aligned -> NO misalign exception")
print()
print("This means the test binary has jalr t1,a0 which jumps to address 0")
print("The .s disassembly shows jalr t1,t0 but that's WRONG for this binary")
