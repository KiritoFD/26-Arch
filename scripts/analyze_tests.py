#!/usr/bin/env python3
"""Analyze the lab+4 test failures."""
import struct

# Read the binary
with open('ready-to-run/lab+/4/all-test-privfull.bin', 'rb') as f:
    data = f.read()

regnames = {0:'zero',1:'ra',2:'sp',3:'gp',4:'tp',5:'t0',6:'t1',7:'t2',
            8:'s0',9:'s1',10:'a0',11:'a1',12:'a2',13:'a3',14:'a4',15:'a5',
            16:'a6',17:'a7',28:'t3',29:'t4',30:'t5',31:'t6'}

def decode_jalr(val):
    opcode = val & 0x7f
    rd = (val >> 7) & 0x1f
    funct3 = (val >> 12) & 0x7
    rs1 = (val >> 15) & 0x1f
    imm = (val >> 20) & 0xfff
    if imm & 0x800: imm -= 0x1000
    return opcode, rd, funct3, rs1, imm

print("=" * 60)
print("Analysis of lab+4 instr_misalign test")
print("=" * 60)

# Check instruction at 0x80006028 (offset 0x6028)
offset = 0x6028
word = struct.unpack_from('<I', data, offset)[0]
opcode, rd, funct3, rs1, imm = decode_jalr(word)
print(f"\nAt 0x8000{offset:04x}: 0x{word:08x}")
print(f"  jalr {regnames.get(rd,'x'+str(rd))}, {regnames.get(rs1,'x'+str(rs1))}, {imm}")

# Trace the test flow
print("\n--- Test flow ---")
print("Before instr_misalign:")
print("  setup_test: a7=-1+1=0, ecall -> test_state=0, a0=0")
print()
print("instr_misalign test code:")
print("  80006018: jal ra, setup_test  # sets a7=0, ecall -> test_state=0")
print("  8000601c: auipc a1, 0        # a1 = 0x8000601c")
print("  80006020: addi a1, a1, 16    # a1 = 0x8000602c")
print("  80006024: addi t0, a1, 1     # t0 = 0x8000602d (misaligned!)")
print(f"  80006028: jalr {regnames.get(rd,'x'+str(rd))}, {regnames.get(rs1,'x'+str(rs1))}, {imm}")

if rs1 == 5:  # t0
    target_raw = 0x8000602d + imm
    target = target_raw & ~1
    print(f"\n  JALR with rs1=t0: target = (0x8000602d + {imm}) & ~1 = 0x{target:08x}")
    print(f"  0x{target:08x} is 4-byte aligned -> NO misalign exception (RISC-V spec)")
    print(f"  But test expects misalign exception -> test assumes pre-mask check")
elif rs1 == 10:  # a0
    print(f"\n  JALR with rs1=a0=0: target = (0 + {imm}) & ~1 = 0")
    print(f"  0x0 is 4-byte aligned -> NO misalign exception")
else:
    print(f"\n  JALR with rs1=x{rs1}: unexpected register")

# Check breakpoint test - look for any ebreak instruction
print("\n" + "=" * 60)
print("Analysis of lab+4 breakpoint test")
print("=" * 60)
ebreak_count = 0
for i in range(0, len(data)-3, 4):
    word = struct.unpack_from('<I', data, i)[0]
    if word == 0x00100073:  # ebreak
        print(f"  Found ebreak at offset 0x{i:x} (addr 0x8000{i:04x})")
        ebreak_count += 1
print(f"\nTotal ebreak instructions in binary: {ebreak_count}")

# Understand the test dispatch mechanism
print("\n" + "=" * 60)
print("Test dispatch analysis")
print("=" * 60)
print("Test framework: each test calls setup_test which does ecall")
print("setup_test: a7++ -> ecall -> handler sets test_state=a7")
print("After ecall returns, test code runs and should cause specific exception")
print("Handler checks: test_state == mcause -> PASS")
print()
print("For breakpoint (test_state=3):")
print("  setup_test sets test_state=3, then test code should cause breakpoint (mcause=3)")
print("  But there's no ebreak in the binary, so no breakpoint exception is raised")
print("  The test continues to the next setup_test, but test_state=3 was already set")
print("  When the next test's ecall comes, handler sees test_state=3 (not -1),")
print("  and the syscall handler auto-sets test_state to the new a7 value")
print("  This effectively skips the breakpoint test")

# Look at the trap handler to understand test dispatch
print("\n" + "=" * 60)
print("Trap handler test_state flow for breakpoint")
print("=" * 60)
# The breakpoint test at test_state=3:
# After illegal_instr (test_state=2) passes, test_state=-1
# setup_test for breakpoint: a7=3, ecall
# Handler syscall: test_state was -1 (from previous pass), so it prints "already done" and sets test_state=3
# Wait, let me re-read the syscall function
print("After illegal_instr PASS: test_state = -1")
print("Breakpoint setup_test: a7=3, ecall")
print("In syscall handler:")
print("  test_state=-1 (< 0) -> skip 'already done' check")
print("  test_state = a7 = 3")
print("  Returns to breakpoint test code")
print("  Test code should cause breakpoint (mcause=3)")
print("  But no breakpoint mechanism exists in this binary")
print("  Test falls through to next code, eventually hits load_misalign")
print("  load_misalign does ecall with a7=4, handler sets test_state=4")
print("  This overwrites test_state=3, so breakpoint test is lost")
print("  -> Test framework prints 'Test breakpoint [X]'")

# Check the m_trap_test function - breakpoint might come from there
print("\n" + "=" * 60)
print("Checking m_trap_test for breakpoint handling")
print("=" * 60)
# Search for the trap handler dispatch logic
for i in range(0x5470, 0x5490, 4):
    if i < len(data):
        word = struct.unpack_from('<I', data, i)[0]
        print(f"  0x8000{i:04x}: 0x{word:08x}")

# Check if the test framework has a breakpoint test that
# uses the trap handler differently
# The test names array is at 0x8000d8a0
# Let's look at the test_state -> expected_mcause mapping
print("\n" + "=" * 60)
print("Test state -> expected cause mapping")
print("=" * 60)
tests = [
    (0, "instr_misalign", 0),
    (1, "instr_access_fault", 1),
    (2, "illegal_instr", 2),
    (3, "breakpoint", 3),
    (4, "load_misalign", 4),
    (5, "load_fault", 5),
    (6, "store_misalign", 6),
    (7, "store_fault", 7),
]
for ts, name, expected in tests:
    print(f"  test_state={ts}: {name} -> expects mcause={expected}")

print("\nFor breakpoint: test_state=3 expects mcause=3 (breakpoint)")
print("A breakpoint exception can be caused by ebreak instruction (mcause=3)")
print("Since no ebreak exists in binary, the test cannot trigger this exception")
