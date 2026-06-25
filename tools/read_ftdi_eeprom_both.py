#!/usr/bin/env python3
"""Read FT2232H EEPROM from BOTH channels to verify state."""
import ctypes

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

num = ctypes.c_uint(0)
ftd2xx.FT_CreateDeviceInfoList(ctypes.byref(num))
print(f"FTDI devices: {num.value}\n")

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
    sn_str = serial.value.decode('ascii', errors='replace')
    print(f"=== Device {i}: serial={sn_str}, desc={desc.value.decode('ascii', errors='replace')} ===")

    handle = ctypes.c_void_p()
    ret = ftd2xx.FT_OpenEx(serial, FT_OPEN_BY_SERIAL_NUMBER, ctypes.byref(handle))
    print(f"FT_OpenEx ret={ret}")
    if ret != 0:
        print("Failed to open\n")
        continue

    # Read EEPROM program data
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
    print(f"  Signature1={pd.Signature1:#x} (expect 0xdeadbeef)")
    print(f"  Signature2={pd.Signature2:#x} (expect 0x00000000)")
    print(f"  VendorId={pd.VendorId:#06x}")
    print(f"  ProductId={pd.ProductId:#06x}")
    print(f"  Manufacturer='{mfg_buf.value.decode('ascii', errors='replace')}'")
    print(f"  ManufacturerId='{mid_buf.value.decode('ascii', errors='replace')}'")
    print(f"  Description='{desc_buf.value.decode('ascii', errors='replace')}'")
    print(f"  SerialNumber='{sn_buf.value.decode('ascii', errors='replace')}'")
    print(f"  MaxPower={pd.MaxPower}")
    print(f"  SelfPowered={pd.SelfPowered}")
    print(f"  RemoteWakeup={pd.RemoteWakeup}")
    print(f"  SerNumEnable={pd.SerNumEnable}")
    print(f"  USBVersion={pd.USBVersion:#06x}")

    # Read UA
    ua_size = ctypes.c_uint(0)
    ret = ftd2xx.FT_EE_UASize(handle, ctypes.byref(ua_size))
    print(f"\n  EEPROM User Area size: {ua_size.value} bytes")

    if ua_size.value > 0:
        buf_size = ua_size.value
        buf = (ctypes.c_ubyte * buf_size)()
        bytes_read = ctypes.c_uint(0)
        ret = ftd2xx.FT_EE_UARead(handle, buf, buf_size, ctypes.byref(bytes_read))
        print(f"  FT_EE_UARead ret={ret}, read={bytes_read.value} bytes")
        data = bytes(buf[:bytes_read.value])
        print(f"  Hex: {data[:64].hex()}")
        ascii_str = ''.join(chr(b) if 32 <= b <= 126 else '.' for b in data[:64])
        print(f"  ASCII: {ascii_str}")
        # Count zero bytes
        zero_count = data.count(0)
        print(f"  Zero bytes: {zero_count}/{len(data)}")
        if zero_count == len(data):
            print("  *** EEPROM UA IS ALL ZEROS! ***")

    ftd2xx.FT_Close(handle)
    print()
