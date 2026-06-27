"""Directly read and modify FT2232H EEPROM using FT_ReadEE/FT_WriteEE (word-level).

This bypasses the FT_PROGRAM_DATA structure entirely and works directly with raw
EEPROM words. We'll:
1. Backup current EEPROM (already done: eeprom_dump_current.bin)
2. Identify the "Digilent Basys3" product string bytes
3. Replace with a FTDI-compatible product string like "Dual RS232-HS"
4. Recompute the FT2232H EEPROM checksum (last word)
5. Write the modified EEPROM
6. Cycle USB to apply changes

WARNING: Writing the wrong checksum can brick the device.
"""
import ctypes
import struct

ftd2xx = ctypes.windll.FTD2XX

# Function prototypes
ftd2xx.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ftd2xx.FT_Open.restype = ctypes.c_uint32
ftd2xx.FT_Close.argtypes = [ctypes.c_void_p]
ftd2xx.FT_Close.restype = ctypes.c_uint32
ftd2xx.FT_ReadEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint16)]
ftd2xx.FT_ReadEE.restype = ctypes.c_uint32
ftd2xx.FT_WriteEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.c_uint16]
ftd2xx.FT_WriteEE.restype = ctypes.c_uint32
ftd2xx.FT_EraseEE.argtypes = [ctypes.c_void_p]
ftd2xx.FT_EraseEE.restype = ctypes.c_uint32
# FT_ProgramEEPROM may not exist; use FT_WriteEE word-by-word instead


def read_eeprom(handle, num_words=128):
    """Read entire EEPROM as list of 16-bit words."""
    words = []
    for i in range(num_words):
        w = ctypes.c_uint16()
        status = ftd2xx.FT_ReadEE(handle, i, ctypes.byref(w))
        if status != 0:
            raise IOError(f"FT_ReadEE failed at word {i}: {status}")
        words.append(w.value)
    return words


def write_eeprom_word(handle, addr, value):
    """Write a single 16-bit word to EEPROM."""
    status = ftd2xx.FT_WriteEE(handle, addr, ctypes.c_uint16(value))
    if status != 0:
        raise IOError(f"FT_WriteEE failed at word {addr}: {status}")
    return True


def calc_ft2232h_checksum(words, num_words=128):
    """Calculate FT2232H EEPROM checksum.

    The checksum is stored in the last word (word 127 = 0x7E).
    Algorithm: XOR of all words except the last, but with a specific FTDI formula.

    FTDI's checksum algorithm for FT2232H (from FTDI AN_135):
    - Checksum covers words 0 to N-2 (where N = total word count, e.g., 128)
    - Each word is broken into bytes
    - Checksum = (sum of bytes + 0x00) & 0xFF  ... no that's not quite right

    Actually FTDI uses a specific algorithm. Let me use the known approach:
    The checksum word (last word) is calculated so that the XOR of all bytes
    in the EEPROM (excluding the checksum itself) equals 0.

    But FTDI's actual algorithm is more nuanced. Let me test with the current
    EEPROM data to verify.
    """
    # FTDI checksum algorithm (from AN_135, the older FTDI parts):
    # checksum is a 16-bit word located at the end
    # sum = 0xFFFF - (sum of all words except last) & 0xFFFF
    # Actually the FT2232H uses a specific formula

    # Method from FTDI's ftape source:
    # Checksum is calculated over all words except the last (checksum word itself)
    # The checksum word is: 0xAAAA - (sum of all previous words) & 0xFFFF
    # ... actually I need to verify with the actual data.

    # Let me use the most commonly documented algorithm:
    # For FT2232H, the checksum is computed as:
    #   checksum = 0x10000 - (sum of words 0 to 126) mod 0x10000
    # ... but FTDI uses different algorithms for different chip families.

    # The reliable approach: read current checksum, then test by computing
    # and verifying it matches.

    # Known FTDI algorithm for FT2232H (from ftd2xx library source):
    # It uses 16-bit XOR of all words except the last
    # checksum = XOR of all words 0..N-2
    cs = 0xFFFF
    for i in range(num_words - 1):  # exclude the checksum word
        # Each word is treated as two bytes
        lo = words[i] & 0xFF
        hi = (words[i] >> 8) & 0xFF
        # FTDI algorithm: keep XOR'ing into the low byte
        cs = (cs - lo) & 0xFFFF
        if cs < 0:
            cs = (cs + 0x10000) & 0xFFFF
        cs = (cs - hi) & 0xFFFF
        if cs < 0:
            cs = (cs + 0x10000) & 0xFFFF
    return cs


def calc_ft2232h_checksum_v2(words, num_words=128):
    """Alternative checksum algorithm: 16-bit XOR of all words except last."""
    cs = 0
    for i in range(num_words - 1):
        cs ^= words[i]
    return cs


# Open device
handle = ctypes.c_void_p()
status = ftd2xx.FT_Open(0, ctypes.byref(handle))
print(f"FT_Open(0) status={status}")
if status != 0:
    print("Cannot open - Vivado may be holding it")
    exit(1)

# Read current EEPROM
words = read_eeprom(handle, 128)

# Check current checksum (last word) vs calculated
current_cs = words[127]
print(f"\nCurrent EEPROM (last word = checksum): 0x{current_cs:04x}")

# Try algorithm 1 (subtract)
cs1 = calc_ft2232h_checksum(words)
print(f"Calc v1 (subtract): 0x{cs1:04x}  match={cs1 == current_cs}")

# Try algorithm 2 (XOR)
cs2 = calc_ft2232h_checksum_v2(words)
print(f"Calc v2 (XOR):      0x{cs2:04x}  match={cs2 == current_cs}")

# Print all words
print("\nFull EEPROM dump:")
for i in range(0, 128, 8):
    hex_str = ' '.join(f'{words[j]:04x}' for j in range(i, min(i+8, 128)))
    print(f"  {i*2:04x}: {hex_str}")

ftd2xx.FT_Close(handle)

# Save current values for reference
with open('eeprom_dump_current.bin', 'wb') as f:
    for w in words:
        f.write(struct.pack('<H', w))
print("\nSaved to eeprom_dump_current.bin")
