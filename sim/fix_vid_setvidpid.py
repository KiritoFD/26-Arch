"""Fix FT2232H EEPROM by registering custom VID/PID with FTD2XX driver.

When VID was changed from 0x0403 to 0x1443, the FTDI D2XX driver no longer
recognizes the device. We use FT_SetVIDPID to register the custom VID/PID,
then FT_ListDevices and FT_Open will work.

After fixing the VID back to 0x0403, the device will work normally again.
"""
import ctypes
import struct
import sys
import time

ftd2xx = ctypes.windll.FTD2XX

# Function signatures
ftd2xx.FT_SetVIDPID.argtypes = [ctypes.c_uint32, ctypes.c_uint32]
ftd2xx.FT_SetVIDPID.restype = ctypes.c_uint32
ftd2xx.FT_GetVIDPID.argtypes = [ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_uint32)]
ftd2xx.FT_GetVIDPID.restype = ctypes.c_uint32
ftd2xx.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ftd2xx.FT_Open.restype = ctypes.c_uint32
ftd2xx.FT_Close.argtypes = [ctypes.c_void_p]
ftd2xx.FT_Close.restype = ctypes.c_uint32
ftd2xx.FT_ListDevices.argtypes = [ctypes.POINTER(ctypes.c_uint32), ctypes.c_void_p, ctypes.c_uint32]
ftd2xx.FT_ListDevices.restype = ctypes.c_uint32
ftd2xx.FT_ReadEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint16)]
ftd2xx.FT_ReadEE.restype = ctypes.c_uint32
ftd2xx.FT_WriteEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.c_uint16]
ftd2xx.FT_WriteEE.restype = ctypes.c_uint32
ftd2xx.FT_GetDeviceInfo.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_uint32),
                                     ctypes.c_char_p, ctypes.c_char_p, ctypes.c_void_p]
ftd2xx.FT_GetDeviceInfo.restype = ctypes.c_uint32


def calc_checksum(words_256):
    cs = 0
    for w in words_256[:255]:
        cs ^= w
    return cs


# Load original (Vivado OK) EEPROM as reference for string area
orig_path = 'sim/eeprom_backups/eeprom_backup_20260627_072124.bin'
with open(orig_path, 'rb') as f:
    orig_data = f.read()
orig_words = list(struct.unpack('<' + 'H'*(len(orig_data)//2), orig_data))

CUSTOM_VID = 0x1443
CUSTOM_PID = 0x6010

print("=== Step 1: Register custom VID/PID with FTD2XX driver ===")
status = ftd2xx.FT_SetVIDPID(CUSTOM_VID, CUSTOM_PID)
print(f"  FT_SetVIDPID(0x{CUSTOM_VID:04x}, 0x{CUSTOM_PID:04x}) = {status} (0=OK)")

# Verify
vid = ctypes.c_uint32()
pid = ctypes.c_uint32()
status = ftd2xx.FT_GetVIDPID(ctypes.byref(vid), ctypes.byref(pid))
print(f"  FT_GetVIDPID: VID=0x{vid.value:04x} PID=0x{pid.value:04x} status={status}")

print("\n=== Step 2: List devices ===")
num = ctypes.c_uint32(0)
status = ftd2xx.FT_ListDevices(ctypes.byref(num), None, 0x80000000)
print(f"  FT_ListDevices: status={status}, num={num.value}")

if status != 0 or num.value == 0:
    print("  No devices found even after SetVIDPID!")
    print("  Trying to open by index anyway...")

# Try opening device 0
print("\n=== Step 3: Open device ===")
handle = ctypes.c_void_p()
for idx in range(4):
    status = ftd2xx.FT_Open(idx, ctypes.byref(handle))
    if status == 0:
        print(f"  FT_Open({idx}) OK!")
        break
    else:
        print(f"  FT_Open({idx}) failed: {status}")

if status != 0:
    print("\nERROR: Cannot open device even with custom VID/PID registered.")
    print("The FTDI driver may need to be reinstalled, or use Zadig+libusb approach.")
    sys.exit(1)

# Get device info
dev_type = ctypes.c_uint32()
dev_id = ctypes.c_uint32()
sn_buf = ctypes.create_string_buffer(64)
desc_buf = ctypes.create_string_buffer(256)
status = ftd2xx.FT_GetDeviceInfo(handle, ctypes.byref(dev_type), ctypes.byref(dev_id),
                                  sn_buf, desc_buf, None)
if status == 0:
    print(f"  Type: {dev_type.value}")
    print(f"  ID: 0x{dev_id.value:08x}")
    print(f"  SN: {sn_buf.value.decode('ascii', errors='replace')}")
    print(f"  Desc: {desc_buf.value.decode('ascii', errors='replace')}")
else:
    print(f"  GetDeviceInfo failed: {status}")

# Read current EEPROM
print("\n=== Step 4: Read current EEPROM ===")
words = []
for i in range(256):
    w = ctypes.c_uint16()
    s = ftd2xx.FT_ReadEE(handle, i, ctypes.byref(w))
    if s != 0:
        print(f"  Read failed at word {i}: {s}")
        ftd2xx.FT_Close(handle)
        sys.exit(1)
    words.append(w.value)
print(f"  Read {len(words)} words OK")

print(f"\n  Word 0 (PID): 0x{words[0]:04x}")
print(f"  Word 1 (VID): 0x{words[1]:04x}  (target: 0x0403)")
print(f"  Word 3 (config): 0x{words[3]:04x}")
print(f"  Word 5 (config2): 0x{words[5]:04x}")

# Show string area differences
print(f"\n  String area (word 14-39):")
for i in range(14, 40):
    if words[i] != orig_words[i]:
        print(f"    word {i}: current=0x{words[i]:04x} orig=0x{orig_words[i]:04x} *** NEEDS FIX")
    elif orig_words[i] != 0:
        print(f"    word {i}: current=0x{words[i]:04x} orig=0x{orig_words[i]:04x} (OK)")

# Determine changes
changes = []

# 1. Fix VID (word 1) - THE CRITICAL FIX
if words[1] != 0x0403:
    changes.append((1, words[1], 0x0403, "VID (0x1443 -> 0x0403)"))

# 2. Fix PID (word 0) if needed
if words[0] != 0x6010:
    changes.append((0, words[0], 0x6010, "PID"))

# 3. Copy string area (word 14-39) from original backup
for i in range(14, 40):
    if words[i] != orig_words[i]:
        changes.append((i, words[i], orig_words[i], "string data"))

if not changes:
    print("\n  No changes needed!")
    ftd2xx.FT_Close(handle)
    sys.exit(0)

print(f"\n=== {len(changes)} words to change ===")
for i, old, new, label in changes:
    print(f"  Word {i:3d}: 0x{old:04x} -> 0x{new:04x}  ({label})")

# Apply changes (for checksum calculation)
for i, old, new, label in changes:
    words[i] = new

# Recalculate checksums
cs_127 = 0
for w in words[:127]:
    cs_127 ^= w
cs_255 = 0
for w in words[:255]:
    cs_255 ^= w

print(f"\n  Checksum word 127: 0x{words[127]:04x} -> 0x{cs_127:04x}")
print(f"  Checksum word 255: 0x{words[255]:04x} -> 0x{cs_255:04x}")

if words[127] != cs_127:
    changes.append((127, words[127], cs_127, "checksum127"))
if words[255] != cs_255:
    changes.append((255, words[255], cs_255, "checksum255"))

# Confirm
if '--yes' not in sys.argv:
    resp = input(f"\nWrite {len(changes)} words? Type YES: ")
    if resp != 'YES':
        print("Aborted")
        ftd2xx.FT_Close(handle)
        sys.exit(0)
else:
    print("\nAuto-confirmed via --yes")

# Write
print(f"\n=== Step 5: Writing {len(changes)} words ===")
for i, old, new, label in changes:
    status = ftd2xx.FT_WriteEE(handle, i, ctypes.c_uint16(new))
    if status != 0:
        print(f"  FAILED word {i}: {status}")
        ftd2xx.FT_Close(handle)
        sys.exit(1)
    print(f"  Word {i:3d}: 0x{new:04x} OK ({label})")
    time.sleep(0.05)

# Verify
print("\n=== Step 6: Verifying ===")
all_ok = True
for i, old, new, label in changes:
    w = ctypes.c_uint16()
    ftd2xx.FT_ReadEE(handle, i, ctypes.byref(w))
    if w.value != new:
        print(f"  MISMATCH word {i}: expected 0x{new:04x} got 0x{w.value:04x}")
        all_ok = False
    else:
        print(f"  Word {i:3d}: 0x{w.value:04x} OK ({label})")

ftd2xx.FT_Close(handle)

# Clear custom VID/PID registration
ftd2xx.FT_SetVIDPID(0, 0)
print("\n  Cleared custom VID/PID registration")

if all_ok:
    print("\n=== SUCCESS! EEPROM fixed ===")
    print("VID restored to 0x0403, string area restored.")
    print("Next: unplug USB, wait 3s, replug")
    print("Then: FT_Prog should see device, Vivado should detect board")
else:
    print("\n=== Some verification failed ===")
    print("Try unplugging and replugging USB anyway")
