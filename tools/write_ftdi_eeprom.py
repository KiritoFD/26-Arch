#!/usr/bin/env python3
"""
Write FT2232H EEPROM for Basys3 (Digilent configuration).

CRITICAL: This script rewrites the EEPROM. If interrupted or wrong, device may
become unrecognizable. Recovery requires EEPROM programmer (FT_PROG) or
swapping the chip.

Basys3 standard EEPROM layout:
  VendorId       = 0x0403
  ProductId      = 0x6010
  Manufacturer   = "Digilent"
  ManufacturerId = " Digilent"
  Description    = "Digilent USB Device"
  SerialNumber   = "210183A8AC3D"  (preserved from internal ROM, hard-coded)
  MaxPower       = 90  (180 mA)
  SelfPowered    = 0
  RemoteWakeup   = 0
  SerNumEnable   = 1
  USBVersion     = 0x0200

EEPROM User Area (Digilent format):
  Bytes 0-1: OEM ID = 0x0001 (Digilent)
  Remaining: padding (zeros)

Reads current state first, asks for confirmation before writing.
"""
import ctypes
import sys

ftd2xx = ctypes.WinDLL("ftd2xx.dll")

ftd2xx.FT_CreateDeviceInfoList.restype = ctypes.c_uint
ftd2xx.FT_CreateDeviceInfoList.argtypes = [ctypes.POINTER(ctypes.c_uint)]

ftd2xx.FT_GetDeviceInfoDetail.restype = ctypes.c_uint
ftd2xx.FT_GetDeviceInfoDetail.argtypes = [
    ctypes.c_uint, ctypes.POINTER(ctypes.c_uint), ctypes.POINTER(ctypes.c_uint),
    ctypes.POINTER(ctypes.c_uint), ctypes.POINTER(ctypes.c_uint),
    ctypes.c_char * 16, ctypes.c_char * 64, ctypes.POINTER(ctypes.c_void_p)
]

ftd2xx.FT_OpenEx.restype = ctypes.c_uint
ftd2xx.FT_OpenEx.argtypes = [ctypes.c_char_p, ctypes.c_uint, ctypes.POINTER(ctypes.c_void_p)]

ftd2xx.FT_Close.restype = ctypes.c_uint
ftd2xx.FT_Close.argtypes = [ctypes.c_void_p]

ftd2xx.FT_EE_UASize.restype = ctypes.c_uint
ftd2xx.FT_EE_UASize.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_uint)]

ftd2xx.FT_EE_UARead.restype = ctypes.c_uint
ftd2xx.FT_EE_UARead.argtypes = [
    ctypes.c_void_p, ctypes.POINTER(ctypes.c_ubyte), ctypes.c_uint, ctypes.POINTER(ctypes.c_uint)
]

ftd2xx.FT_EE_UAWrite.restype = ctypes.c_uint
ftd2xx.FT_EE_UAWrite.argtypes = [
    ctypes.c_void_p, ctypes.POINTER(ctypes.c_ubyte), ctypes.c_uint
]

ftd2xx.FT_EE_Program.restype = ctypes.c_uint
ftd2xx.FT_EE_Program.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_void_p)]

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

FT_OPEN_BY_SERIAL_NUMBER = 1

# Basys3 standard EEPROM values
# Hard-coded serial from device descriptor (preserved)
BASYS3_SERIAL = "210183A8AC3D"

def read_eeprom(handle, label=""):
    """Read FT_PROGRAM_DATA and UA, return both."""
    if label:
        print(f"\n--- {label} ---")
    pd = FT_PROGRAM_DATA()
    mfg_buf = ctypes.create_string_buffer(256)
    mid_buf = ctypes.create_string_buffer(256)
    desc_buf = ctypes.create_string_buffer(256)
    sn_buf = ctypes.create_string_buffer(256)
    pd.Manufacturer = ctypes.cast(mfg_buf, ctypes.c_char_p)
    pd.ManufacturerId = ctypes.cast(mid_buf, ctypes.c_char_p)
    pd.Description = ctypes.cast(desc_buf, ctypes.c_char_p)
    pd.SerialNumber = ctypes.cast(sn_buf, ctypes.c_char_p)
    ret = ftd2xx.FT_EE_Read(handle, ctypes.byref(pd))
    print(f"FT_EE_Read ret={ret}")
    print(f"  Signature1={pd.Signature1:#x}, Signature2={pd.Signature2:#x}, Version={pd.Version:#x}")
    print(f"  VendorId={pd.VendorId:#06x}, ProductId={pd.ProductId:#06x}")
    print(f"  Manufacturer='{mfg_buf.value.decode('ascii', errors='replace')}'")
    print(f"  ManufacturerId='{mid_buf.value.decode('ascii', errors='replace')}'")
    print(f"  Description='{desc_buf.value.decode('ascii', errors='replace')}'")
    print(f"  SerialNumber='{sn_buf.value.decode('ascii', errors='replace')}'")
    print(f"  MaxPower={pd.MaxPower}, SelfPowered={pd.SelfPowered}")
    print(f"  RemoteWakeup={pd.RemoteWakeup}, SerNumEnable={pd.SerNumEnable}")
    print(f"  USBVersion={pd.USBVersion:#06x}")

    ua_size = ctypes.c_uint(0)
    ftd2xx.FT_EE_UASize(handle, ctypes.byref(ua_size))
    print(f"  UA size: {ua_size.value}")
    if ua_size.value > 0:
        buf_size = ua_size.value
        buf = (ctypes.c_ubyte * buf_size)()
        bytes_read = ctypes.c_uint(0)
        ftd2xx.FT_EE_UARead(handle, buf, buf_size, ctypes.byref(bytes_read))
        data = bytes(buf[:bytes_read.value])
        print(f"  UA ({bytes_read.value}B): {data[:32].hex()}")
    return pd, mfg_buf.value, mid_buf.value, desc_buf.value, sn_buf.value


def write_eeprom_ua_only(handle):
    """Write ONLY the EEPROM User Area, leaving the FT_PROGRAM_DATA intact.
    This is safer than rewriting the full EEPROM."""
    print("\n=== Writing Digilent OEM ID to EEPROM User Area ===")
    ua_size = ctypes.c_uint(0)
    ftd2xx.FT_EE_UASize(handle, ctypes.byref(ua_size))
    print(f"UA size: {ua_size.value} bytes")

    # Construct Digilent UA: bytes 0-1 = OEM ID = 0x0001, rest = 0
    # Reference: Digilent Adept SDK spec
    ua_data = bytearray(ua_size.value)
    ua_data[0] = 0x01  # OEM ID low byte = 1 (Digilent)
    ua_data[1] = 0x00  # OEM ID high byte = 0

    print(f"Will write: {bytes(ua_data[:16]).hex()} ... (first 16 bytes)")
    print(f"OEM ID = 0x{(ua_data[1] << 8) | ua_data[0]:04x}")

    buf = (ctypes.c_ubyte * ua_size.value)(*ua_data)
    ret = ftd2xx.FT_EE_UAWrite(handle, buf, ua_size.value)
    print(f"FT_EE_UAWrite ret={ret}")
    return ret == 0


def write_full_eeprom(handle):
    """Rewrite the entire FT2232H EEPROM with Basys3 standard values."""
    print("\n=== Writing FULL FT2232H EEPROM (Basys3 config) ===")
    pd = FT_PROGRAM_DATA()
    pd.Signature1 = 0xdeadbeef
    pd.Signature2 = 0x00000000
    pd.Version = 0x00000005  # rev 5 (FT2232H)

    mfg_buf = ctypes.create_string_buffer(b"Digilent")
    mid_buf = ctypes.create_string_buffer(b" Digilent")
    desc_buf = ctypes.create_string_buffer(b"Digilent USB Device")
    sn_buf = ctypes.create_string_buffer(BASYS3_SERIAL.encode('ascii'))

    pd.Manufacturer = ctypes.cast(mfg_buf, ctypes.c_char_p)
    pd.ManufacturerId = ctypes.cast(mid_buf, ctypes.c_char_p)
    pd.Description = ctypes.cast(desc_buf, ctypes.c_char_p)
    pd.SerialNumber = ctypes.cast(sn_buf, ctypes.c_char_p)

    pd.VendorId = 0x0403
    pd.ProductId = 0x6010
    pd.MaxPower = 90  # 180 mA (90 * 2mA units)
    pd.PnP = 1
    pd.SelfPowered = 0
    pd.RemoteWakeup = 0
    pd.SerNumEnable = 1
    pd.USBVersionEnable = 1
    pd.USBVersion = 0x0200
    pd.PullDownEnable = 0
    # Channel-specific bits in IsoIn/IsoOut (rev 4 fields)
    pd.IsoIn = 0
    pd.IsoOut = 0

    ret = ftd2xx.FT_EE_Program(handle, ctypes.byref(pd))
    print(f"FT_EE_Program ret={ret}")
    return ret == 0


def main():
    # Enumerate
    num = ctypes.c_uint(0)
    ftd2xx.FT_CreateDeviceInfoList(ctypes.byref(num))
    print(f"FTDI devices: {num.value}")

    if num.value == 0:
        print("No FTDI devices found!")
        return

    # Use channel A (JTAG)
    # Channel A: serial ends with 'A', Channel B: serial ends with 'B'
    print("\n=== Available devices ===")
    target_idx = -1
    target_serial = None
    for i in range(num.value):
        flags = ctypes.c_uint(0)
        dev_type = ctypes.c_uint(0)
        dev_id = ctypes.c_uint(0)
        loc_id = ctypes.c_uint(0)
        serial = (ctypes.c_char * 16)()
        desc = (ctypes.c_char * 64)()
        handle_dummy = ctypes.c_void_p()
        ftd2xx.FT_GetDeviceInfoDetail(
            i, ctypes.byref(flags), ctypes.byref(dev_type),
            ctypes.byref(dev_id), ctypes.byref(loc_id),
            serial, desc, ctypes.byref(handle_dummy)
        )
        sn = serial.value.decode('ascii', errors='replace')
        print(f"  [{i}] serial={sn}, desc={desc.value.decode('ascii', errors='replace')}")
        # Pick channel A (JTAG) - serial ends with 'A'
        if sn.endswith('A'):
            target_idx = i
            target_serial = serial

    if target_idx < 0:
        print("No channel A device found, using device 0")
        target_idx = 0

    # Open channel A
    print(f"\n=== Opening device {target_idx} ===")
    handle = ctypes.c_void_p()
    ret = ftd2xx.FT_OpenEx(target_serial, FT_OPEN_BY_SERIAL_NUMBER, ctypes.byref(handle))
    print(f"FT_OpenEx ret={ret}")
    if ret != 0:
        print("Failed to open!")
        return

    # Read BEFORE
    read_eeprom(handle, "BEFORE write")

    # Ask for confirmation
    print("\n" + "=" * 60)
    print("EEPROM will be rewritten with Basys3 standard Digilent config.")
    print("This is a HIGH-RISK operation.")
    print("=" * 60)

    if '--force' not in sys.argv:
        choice = input("\nChoose action:\n  [1] Write ONLY Digilent OEM ID to UA (safer)\n  [2] Write FULL EEPROM (Basys3 config)\n  [q] Quit\n> ")
    else:
        choice = '1'

    if choice == '1':
        ok = write_eeprom_ua_only(handle)
    elif choice == '2':
        ok = write_full_eeprom(handle)
        if ok:
            # Also write OEM ID to UA after full EEPROM write
            print("\nNow also writing Digilent OEM ID to UA...")
            write_eeprom_ua_only(handle)
    else:
        print("Aborted.")
        ftd2xx.FT_Close(handle)
        return

    if not ok:
        print("Write failed!")
        ftd2xx.FT_Close(handle)
        return

    # Read AFTER
    read_eeprom(handle, "AFTER write")

    ftd2xx.FT_Close(handle)
    print("\n=== DONE ===")
    print("Now unplug Basys3 USB cable, wait 5 seconds, replug.")
    print("Then re-run verify_adept.ps1 to test.")


if __name__ == "__main__":
    main()
