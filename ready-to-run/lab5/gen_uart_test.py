# Simple UART test: write 'A' to UART THR then loop forever
# RISC-V assembly, assembled manually

# UART THR address = 0x10000000
# LUI a0, 0x10000      -> a0 = 0x10000000
# ADDI a1, zero, 0x41  -> a1 = 'A'
# SW a1, 0(a0)         -> write 'A' to UART THR
# J .                  -> loop forever

# Encoding:
# LUI a0, 0x10000     = 0x10000537
# ADDI a1, zero, 0x41 = 0x04100593
# SW a1, 0(a0)        = 0x00B52023
# J . (offset=0)      = 0x0000006F

# As 64-bit little-endian words (byte-swapped per 32-bit half):
# Word 0: [0x04100593, 0x10000537] -> little-endian: 9305100041 3705001000 -> COE: 37050010009305100041
# Wait, let me recalculate

# 32-bit instructions in order:
# 0x10000537  LUI a0, 0x10000
# 0x04100593  ADDI a1, zero, 0x41
# 0x00B52023  SW a1, 0(a0)
# 0x0000006F  J .

# 64-bit word 0 (addr 0x80000000): instructions 0 and 1
#   low 32-bit = 0x10000537, high 32-bit = 0x04100593
#   little-endian byte-swap per 32-bit:
#     0x10000537 -> bytes 37 05 00 10 -> reversed: 10 00 05 37
#     0x04100593 -> bytes 93 05 10 04 -> reversed: 04 10 05 93
#   COE format (high word first, each word byte-reversed):
#     high 32-bit reversed: 04100593 -> wait, COE format is:
#     For 64-bit wide BRAM, COE stores data as hex strings
#     gen_xv6_coe.py does: hex1 = chunk[4:8][::-1], hex2 = chunk[0:4][::-1]
#     So for bytes [37,05,00,10,93,05,10,04]:
#       chunk[4:8] = [93,05,10,04] -> reversed = [04,10,05,93] -> hex "04100593"
#       chunk[0:4] = [37,05,00,10] -> reversed = [10,00,05,37] -> hex "10000537"
#       COE line = "0410059310000537"

# Let me just use the Python script to generate this properly

import struct
import sys

def create_test_coe():
    # Simple RISC-V program: write 'A' to UART, then loop
    instructions = [
        0x10000537,  # LUI a0, 0x10000
        0x04100593,  # ADDI a1, zero, 0x41
        0x00B52023,  # SW a1, 0(a0)
        0x0000006F,  # J .
    ]

    # Pack as little-endian bytes
    data = b''
    for inst in instructions:
        data += struct.pack('<I', inst)

    # Pad to 8 bytes (one 64-bit word)
    while len(data) < 8:
        data += b'\x00'

    # Generate COE
    lines = []
    for i in range(0, len(data), 8):
        chunk = data[i:i+8]
        # Same byte-swap as gen_xv6_coe.py
        hex1 = ''.join(f'{b:02x}' for b in chunk[4:8][::-1])
        hex2 = ''.join(f'{b:02x}' for b in chunk[0:4][::-1])
        lines.append(hex1 + hex2)

    # Pad to 21000 entries
    while len(lines) < 21000:
        lines.append("0000000000000000")

    coe_path = r"g:\GitHub\26-Arch\ready-to-run\lab5\uart-test.coe"
    with open(coe_path, "w") as f:
        f.write("memory_initialization_radix = 16;\n")
        f.write("memory_initialization_vector =\n")
        for i, line in enumerate(lines):
            if i == len(lines) - 1:
                f.write(line + ";\n")
            else:
                f.write(line + "\n")

    print(f"Generated {coe_path} with {len(lines)} entries")
    print(f"First COE line: {lines[0]}")

if __name__ == "__main__":
    create_test_coe()
