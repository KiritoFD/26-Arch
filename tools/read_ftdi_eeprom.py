#!/usr/bin/env python3
"""Read FT2232H EEPROM User Area to check Digilent OEM ID."""
import ctypes
from ctypes import wintypes

# Load FTD2XX
try:
    ftd2xx = ctypes.WinDLL("ftd2xx.dll")
except OSError:
    # Try absolute path
    ftd2xx = ctypes.WinDLL(r"C:\Windows\System32\ftd2xx.dll")

# Function prototypes
ftd2xx.FT_CreateDeviceInfoList.restype = ctypes.c_uint
ftd2xx.FT_CreateDeviceInfoList.argtypes = [ctypes.POINTER(ctypes.c_uint)]

ftd2xx.FT_GetDeviceInfoDetail.restype = ctypes.c_uint
ftd2xx.FT_GetDeviceInfoDetail.argtypes = [
    ctypes.c_uint,  # index
    ctypes.POINTER(ctypes.c_uint),  # Flags
    ctypes.POINTER(ctypes.c_uint),  # Type
    ctypes.POINTER(ctypes.c_uint),  # ID
    ctypes.POINTER(ctypes.c_uint),  # LocId
    ctypes.c_char * 16,  # SerialNumber
    ctypes.c_char * 64,  # Description
    ctypes.POINTER(ctypes.c_void_p)  # ftHandle
]

ftd2xx.FT_OpenEx.restype = ctypes.c_uint
ftd2xx.FT_OpenEx.argtypes = [ctypes.c_void_p, ctypes.c_uint, ctypes.POINTER(ctypes.c_void_p)]

ftd2xx.FT_Close.restype = ctypes.c_uint
ftd2xx.FT_Close.argtypes = [ctypes.c_void_p]

ftd2xx.FT_EE_UASize.restype = ctypes.c_uint
ftd2xx.FT_EE_UASize.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_uint)]

ftd2xx.FT_EE_UARead.restype = ctypes.c_uint
ftd2xx.FT_EE_UARead.argtypes = [
    ctypes.c_void_p,
    ctypes.POINTER(ctypes.c_ubyte),
    ctypes.c_uint,
    ctypes.POINTER(ctypes.c_uint)
]

ftd2xx.FT_EE_Read.restype = ctypes.c_uint
fttd2xx_EE_Read = ftd2xx.FT_EE_Read

# FT_PROGRAM_DATA structure
# Note: Manufacturer, ManufacturerId, Description, SerialNumber are char* (pointers)
# User must allocate buffers and set the pointers before calling FT_EE_Read
class FT_PROGRAM_DATA(ctypes.Structure):
    _fields_ = [
        ("Signature1", ctypes.c_uint),
        ("Signature2", ctypes.c_uint),
        ("Version", ctypes.c_uint),
        ("VendorId", ctypes.c_ushort),
        ("ProductId", ctypes.c_ushort),
        ("Manufacturer", ctypes.c_char_p),
        ("ManufacturerId", ctypes.c_char_p),
        ("Description", ctypes.c_char_p),
        ("SerialNumber", ctypes.c_char_p),
        ("MaxPower", ctypes.c_ushort),
        ("PnP", ctypes.c_ushort),
        ("SelfPowered", ctypes.c_ushort),
        ("RemoteWakeup", ctypes.c_ushort),
        # Rev4 (1 byte) - on Windows CDM driver, used as USB power type
        ("Rev4", ctypes.c_ubyte * 1),
        ("IsoIn", ctypes.c_ubyte),
        ("IsoOut", ctypes.c_ubyte),
        ("PullDownEnable", ctypes.c_ubyte),
        ("SerNumEnable", ctypes.c_ubyte),
        ("USBVersionEnable", ctypes.c_ubyte),
        ("USBVersion", ctypes.c_ushort),
        ("Rev5", ctypes.c_ubyte * 1),
        ("I2CSlaveAddress", ctypes.c_ushort),
        ("Rev6", ctypes.c_ubyte * 2),
        ("Rev7", ctypes.c_ubyte * 1),
        ("Rev8", ctypes.c_ubyte * 1),
    ]

ftd2xx.FT_EE_Read.restype = ctypes.c_uint
ftd2xx.FT_EE_Read.argtypes = [ctypes.c_void_p, ctypes.POINTER(FT_PROGRAM_DATA)]

# Open by serial number
FT_OPEN_BY_SERIAL_NUMBER = 1

print("=== Step 1: Enumerate FTDI devices ===")
num_devices = ctypes.c_uint(0)
ret = ftd2xx.FT_CreateDeviceInfoList(ctypes.byref(num_devices))
print(f"FT_CreateDeviceInfoList ret={ret}, numDevices={num_devices.value}")

if num_devices.value == 0:
    print("No FTDI devices found!")
    exit(1)

for i in range(num_devices.value):
    print(f"\n--- Device {i} ---")
    flags = ctypes.c_uint(0)
    dev_type = ctypes.c_uint(0)
    dev_id = ctypes.c_uint(0)
    loc_id = ctypes.c_uint(0)
    serial = (ctypes.c_char * 16)()
    desc = (ctypes.c_char * 64)()
    handle = ctypes.c_void_p()
    
    ret = ftd2xx.FT_GetDeviceInfoDetail(
        i, ctypes.byref(flags), ctypes.byref(dev_type),
        ctypes.byref(dev_id), ctypes.byref(loc_id),
        serial, desc, ctypes.byref(handle)
    )
    print(f"  ret={ret}")
    print(f"  flags={flags.value:#x}")
    print(f"  type={dev_type.value:#x}  (4=FT2232H, 6=FT2232H-variant)")
    print(f"  id={dev_id.value:#x}")
    print(f"  locId={loc_id.value:#x}")
    print(f"  serial={serial.value.decode('ascii', errors='replace')}")
    print(f"  description={desc.value.decode('ascii', errors='replace')}")

# Try opening device 0 by serial number
print("\n=== Step 2: Open device and read EEPROM ===")
# Get serial of device 0
flags = ctypes.c_uint(0)
dev_type = ctypes.c_uint(0)
dev_id = ctypes.c_uint(0)
loc_id = ctypes.c_uint(0)
serial0 = (ctypes.c_char * 16)()
desc0 = (ctypes.c_char * 64)()
handle0 = ctypes.c_void_p()
ftd2xx.FT_GetDeviceInfoDetail(
    0, ctypes.byref(flags), ctypes.byref(dev_type),
    ctypes.byref(dev_id), ctypes.byref(loc_id),
    serial0, desc0, ctypes.byref(handle0)
)

# Open by serial
handle = ctypes.c_void_p()
serial_str = serial0.value.decode('ascii').rstrip('\x00')
print(f"Opening device with serial '{serial_str}'")
ret = ftd2xx.FT_OpenEx(serial0, FT_OPEN_BY_SERIAL_NUMBER, ctypes.byref(handle))
print(f"FT_OpenEx ret={ret}")
if ret != 0:
    print("Failed to open device!")
    exit(1)

print(f"Handle: {handle.value:#x}")

# Read FT_PROGRAM_DATA
print("\n--- FT_PROGRAM_DATA (EEPROM) ---")
program_data = FT_PROGRAM_DATA()
mfg_buf = ctypes.create_string_buffer(32)
mfg_id_buf = ctypes.create_string_buffer(16)
desc_buf = ctypes.create_string_buffer(64)
sn_buf = ctypes.create_string_buffer(16)
program_data.Manufacturer = ctypes.cast(mfg_buf, ctypes.c_char_p)
program_data.ManufacturerId = ctypes.cast(mfg_id_buf, ctypes.c_char_p)
program_data.Description = ctypes.cast(desc_buf, ctypes.c_char_p)
program_data.SerialNumber = ctypes.cast(sn_buf, ctypes.c_char_p)

ret = ftd2xx.FT_EE_Read(handle, ctypes.byref(program_data))
print(f"FT_EE_Read ret={ret}")
print(f"  VendorId={program_data.VendorId:#06x}")
print(f"  ProductId={program_data.ProductId:#06x}")
print(f"  Manufacturer={mfg_buf.value.decode('ascii', errors='replace')}")
print(f"  ManufacturerId={mfg_id_buf.value.decode('ascii', errors='replace')}")
print(f"  Description={desc_buf.value.decode('ascii', errors='replace')}")
print(f"  SerialNumber={sn_buf.value.decode('ascii', errors='replace')}")
print(f"  MaxPower={program_data.MaxPower}")
print(f"  SelfPowered={program_data.SelfPowered}")
print(f"  RemoteWakeup={program_data.RemoteWakeup}")
print(f"  PnP={program_data.PnP}")
print(f"  SerNumEnable={program_data.SerNumEnable}")

# Read User Area
print("\n--- EEPROM User Area ---")
ua_size = ctypes.c_uint(0)
ret = ftd2xx.FT_EE_UASize(handle, ctypes.byref(ua_size))
print(f"FT_EE_UASize ret={ret}, size={ua_size.value}")

if ua_size.value > 0:
    buf_size = min(ua_size.value, 256)
    buf = (ctypes.c_ubyte * buf_size)()
    bytes_read = ctypes.c_uint(0)
    ret = ftd2xx.FT_EE_UARead(handle, buf, buf_size, ctypes.byref(bytes_read))
    print(f"FT_EE_UARead ret={ret}, bytesRead={bytes_read.value}")
    
    data = bytes(buf[:bytes_read.value])
    print(f"  Raw bytes: {data.hex()}")
    print(f"  ASCII: {data.decode('ascii', errors='replace')}")
    
    # Look for Digilent signature (usually 'D' 'i' 'g' 'i' at start, or similar)
    print("\n  --- Interpretation ---")
    if len(data) >= 4:
        # First 2 bytes usually: OEM ID (0x01 for Digilent)
        oem_id = data[0]
        print(f"  First byte (OEM ID?): 0x{oem_id:02x} ({oem_id})")
        if oem_id == 1:
            print("  -> Digilent OEM ID (1) detected!")
        elif oem_id == 0:
            print("  -> OEM ID is 0 (NOT Digilent)")
    
    # Print as hex+ASCII
    print("\n  Hex dump:")
    for i in range(0, min(len(data), 96), 16):
        chunk = data[i:i+16]
        hex_str = ' '.join(f'{b:02x}' for b in chunk)
        ascii_str = ''.join(chr(b) if 32 <= b <= 126 else '.' for b in chunk)
        print(f"    {i:04x}: {hex_str:<48s}  {ascii_str}")

ftd2xx.FT_Close(handle)
print("\n=== Done ===")
