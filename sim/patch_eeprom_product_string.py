"""Parse the FT2232H EEPROM USB string descriptors and plan modification.

String descriptor format (USB standard):
  byte 0: bLength (length in bytes, including header)
  byte 1: bDescriptorType = 0x03 (string)
  bytes 2..N: UTF-16LE characters

The string descriptors start after the FT2232H config area.
From the dump:
  0x0095: 0312 0044 0069 0067 0069 006c 0065 006e 0074
          ^^ length=0x12=18 bytes, type=0x03
          UTF-16: "Digilent" (8 chars × 2 + 2 header = 18 ✓)
          ... ends at 0x0095 + 18 = 0x00A7

  0x00A7: 0328 0044 0069 0067 0069 006c 0065 006e 0074 0020
          0055 0053 0042 0020 0044 0065 0076 0069 0063 0065
          ^^ length=0x28=40 bytes, type=0x03
          UTF-16: "Digilent USB Device" (19 chars × 2 + 2 header = 40 ✓)
          ... ends at 0x00A7 + 40 = 0x00CF

  0x00CF: 031a 0032 0031 0030 0031 0038 0033 0041 0038 0041
          0039 0038 0034
          ^^ length=0x1a=26 bytes, type=0x03
          UTF-16: "210183A8A984" (12 chars × 2 + 2 header = 26 ✓)
          ... ends at 0x00CF + 26 = 0x00E9

After that:
  0x00E9-0x00FD: 03 02 00 00 ... (some extra descriptor + padding)
  0x00FE: checksum word (0x2947)

So:
- Manufacturer string at byte offset 0x95-0xA6 (18 bytes)
- Product string at byte offset 0xA7-0xCE (40 bytes)
- Serial string at byte offset 0xCF-0xE8 (26 bytes)

We want to change Product string from "Digilent USB Device" to something
FTDI-standard like "Dual RS232-HS" (15 chars).

New string: "Dual RS232-HS" = 15 chars
New descriptor length: 15 × 2 + 2 = 32 bytes (vs old 40 bytes, 8 bytes shorter)

The 8 bytes difference will be padding. The total area remains the same size
(we just zero out the extra bytes).

Plan:
1. Read current EEPROM (256 words)
2. Replace the product string bytes at 0xA7-0xCE with new descriptor
3. Zero out the freed bytes (if new string is shorter)
4. If new string is longer, we need to shift other strings - more complex
5. Recalculate checksum as XOR of words 0..254
6. Write modified words back to EEPROM
"""
import ctypes
import struct

ftd2xx = ctypes.windll.FTD2XX
ftd2xx.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ftd2xx.FT_Open.restype = ctypes.c_uint32
ftd2xx.FT_Close.argtypes = [ctypes.c_void_p]
ftd2xx.FT_Close.restype = ctypes.c_uint32
ftd2xx.FT_ReadEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint16)]
ftd2xx.FT_ReadEE.restype = ctypes.c_uint32
ftd2xx.FT_WriteEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.c_uint16]
ftd2xx.FT_WriteEE.restype = ctypes.c_uint32


def calc_checksum(words_256):
    """XOR of all words 0..254, store result in word 255."""
    cs = 0
    for w in words_256[:255]:
        cs ^= w
    return cs


def make_string_descriptor(s):
    """Build a USB string descriptor (bytes) from an ASCII string."""
    utf16 = s.encode('utf-16-le')
    length = len(utf16) + 2  # +2 for header
    return bytes([length, 0x03]) + utf16


# === Read current EEPROM ===
handle = ctypes.c_void_p()
status = ftd2xx.FT_Open(0, ctypes.byref(handle))
if status != 0:
    print(f"FT_Open failed: {status}. Make sure Vivado is closed.")
    exit(1)

words = []
for i in range(256):
    w = ctypes.c_uint16()
    s = ftd2xx.FT_ReadEE(handle, i, ctypes.byref(w))
    if s != 0:
        print(f"Read failed at {i}")
        exit(1)
    words.append(w.value)

print(f"Read {len(words)} words")
print(f"Current checksum (word 255): 0x{words[255]:04x}")
print(f"Verify (XOR 0..254): 0x{calc_checksum(words):04x}")

# Convert to byte array for easier string manipulation
data = bytearray()
for w in words:
    data += struct.pack('<H', w)

# Find current string descriptors
print("\n=== Current string descriptors ===")
i = 0x95
for n, name in enumerate(['Manufacturer', 'Product', 'Serial']):
    if i >= len(data) - 1:
        break
    length = data[i]
    desc_type = data[i+1]
    if desc_type != 0x03:
        print(f"  {name} @0x{i:02x}: bad desc type 0x{desc_type:02x}")
        break
    s = data[i+2:i+length].decode('utf-16-le', errors='replace')
    print(f"  {name} @0x{i:02x}-0x{i+length-1:02x}: '{s}' (len={length})")
    i += length

# Print the bytes after the strings
print(f"\nAfter strings (offset 0x{i:02x}):")
print(' '.join(f'{b:02x}' for b in data[i:i+32]))

# === Plan modification ===
# Product string is at offset 0xA7-0xCE (40 bytes, "Digilent USB Device")
# We want to change it to "Dual RS232-HS" (15 chars = 32 bytes descriptor)
# But wait - if we change the length, the serial string offset will shift.
# Better to keep the SAME length (40 bytes) by padding the string.

# Approach 1: Keep total descriptor length = 40 bytes (pad with spaces or shorten)
# "Dual RS232-HS" is 14 chars, descriptor = 30 bytes
# To keep 40 bytes, we'd need 19 chars -> pad to "Dual RS232-HS      " (19 chars)
# That's ugly. Let's use the descriptor length change approach instead.

# Approach 2: Change the length byte and shift the serial string
# This is cleaner but requires shifting all subsequent data.

# Approach 3 (SIMPLEST): Just modify the ASCII bytes of the product string
# Keep the SAME length (19 UTF-16 chars = 40 bytes), just change the content
# to "FT2232H Dual UART  " (19 chars, padded with spaces)
# Or better: "USB Serial Port A  " - but that's a description, not matching
# Actually FTDI's ftdiport.inf matches Hardware IDs (FTDIBUS\COMPORT&VID_0403&PID_6010)
# NOT the string. The string is just for display.

# Wait - the original problem was that the string "Digilent USB Device"
# caused ftdiport.inf to NOT match. But that's not true based on INF analysis.
# ftdiport.inf matches the FTDIBUS\COMPORT sub-device hardware ID, which is
# generated by ftdibus when it loads.

# So the string itself isn't the issue. Let me reconsider...

# Actually the issue might be the AIsVCP / BIsVCP flags in the EEPROM.
# These flags tell ftdibus whether to expose the channel as VCP (COM port)
# or as D2XX device.

# Looking at word 3 = 0x0700:
#   - Channel A type = 0x00 (UART)
#   - Channel B type = 0x07 (?)
# But the AIsVCP/BIsVCP flags are SEPARATE bits in the Rev5 area.

# Let me check the structured data more carefully.
# Word 4 (0x08) = 0xfa80
# Word 5 (0x0a) = 0x0008
# Word 6 (0x0c) = 0x0000
# Word 7 (0x0e) = 0x129a

# FT2232H EEPROM layout (from FTDI docs):
# Word 0: VID
# Word 1: PID
# Word 2: bcdDevice
# Word 3: Config1 (A type, B type)
# Word 4: Config2 (USB attributes, MaxPower)
# Word 5: Config3 (misc options)
# Word 6: Config4 (channel A FIFO options)
# Word 7: Config5 (channel B FIFO options)

# Wait, the config bytes AIsVCP/BIsVCP are in the HIGH BYTE of word 3!
# Word 3 = 0x0700
# Low byte (Channel A type) = 0x00 = UART
# High byte (Channel B type) = 0x07
# For FT2232H, the high byte of word 3 is actually:
#   bits 0-2: Channel B type (0=UART, 1=FIFO, etc)
#   bit 3: SerNumEnable (use serial number from EEPROM)
#   ... actually I'm getting confused.

# Let me look at the actual FT2232H config word layout from FTDI AN_135:
# Word 3 (Config1):
#   bits 7:0   - Channel A type (0=UART/FIFO, 1=245FIFO, 2=CPUFIFO, 3=OPTO, 4=1284)
#   bits 15:8  - Channel B type (same encoding)
# But also bits in word 5:
# Word 5 (Config3, "Device options"):
#   bit 0: UseExtOsc (0=use internal 48MHz, 1=use external)
#   bit 1: HighDriveIOs
#   bit 2-3: Endpoint size
#   bit 4: PullDownEnable
#   bit 5: SerNumEnable (channel A)
#   bit 6: USBVersionEnable
#   bit 7: AIsVCP (1=channel A is VCP/COM port, 0=D2XX)
#   bit 8-15: same for channel B (BIsVCP at bit 15)

# Wait, that's for FT232R. FT2232H has different bit layout.

# FT2232H Word 3 layout:
#   bits 7:0   - Channel A type (0=UART, 1=245FIFO, 2=CPUFIFO, 4=OPTO)
#   bits 15:8  - Channel B type

# Word 4 layout:
#   bit 0-6   - MaxPower (units of 2mA)
#   bit 7     - SelfPowered
#   bit 8     - RemoteWakeup
#   bit 9     - PullDownEnable
#   ...

# Word 5 (FT2232H) layout:
#   bit 0-3   - IsoInA, IsoInB, IsoOutA, IsoOutB
#   bit 4     - PullDownEnable5
#   bit 5     - SerNumEnable5
#   bit 6     - USBVersionEnable5
#   bit 7     - AIsHighCurrent
#   bit 8     - BIsHighCurrent
#   bit 9     - IFAIsFifo
#   bit 10    - IFAIsFifoTar
#   bit 11    - IFAIsFastSer
#   bit 12    - AIsVCP   <-- THIS IS THE KEY!
#   bit 13    - IFBIsFifo
#   bit 14    - IFBIsFifoTar
#   bit 15    - IFBIsFastSer
#   bit 16    - BIsVCP

# So AIsVCP is bit 12 of word 5.
# Word 5 = 0x0008 = binary 0000 0000 0000 1000
# Bit 3 is set. That's IFAIsFifo (bit 9 in my numbering... wait)

# Let me recompute. 0x0008 = bit 3 set.
# If bits are numbered from LSB:
# bit 3 = IsoOutB (or similar)

# I need to consult the FTDI AN_135 documentation for the exact bit positions.
# But the key insight is: AIsVCP must be set (1) for ftdibus to create a VCP/COM
# sub-device. If it's 0, the channel is exposed only as D2XX.

# Current word 5 = 0x0008 -> bit 3 set
# This doesn't match the typical AIsVCP position (bit 12).

# Let me just try SETTING bit 12 of word 5 and see if that fixes it.
# But we need to know the correct bit position.

# Actually, let me look at the EEPROM data differently.
# Word 5 = 0x0008 (binary: 00000000 00001000)
# Word 6 = 0x0000
# Word 7 = 0x129a (binary: 00010010 10011010)

# Hmm, word 7 = 0x129a has more bits set. Let me see if AIsVCP/BIsVCP is in word 7.
# Word 7 (0x129a):
#   bit 1 = 1 (0x02)
#   bit 3 = 1 (0x08)
#   bit 4 = 1 (0x10)
#   bit 7 = 1 (0x80)
#   bit 8 = 1 (0x100, but that's high byte bit 0... wait)

# Let me decode 0x129a as 16 bits:
# High byte 0x12 = 00010010
# Low byte 0x9a = 10011010
# So bits 1, 3, 4, 7, 12 are set

# This is getting complicated. Let me just dump the FT_PROGRAM_DATA structure
# properly. The issue before was struct size mismatch.
# I'll use a shorter struct that doesn't include Rev6/Rev7 extensions.

print("\n=== Aborting EEPROM patch - need to verify AIsVCP/BIsVCP bit position first ===")
ftd2xx.FT_Close(handle)
