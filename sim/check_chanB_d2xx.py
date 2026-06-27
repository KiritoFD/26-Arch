"""Test if D2XX can open Channel B (Device 1) - this is what Vivado hw_server needs."""
import ctypes

ftd2xx = ctypes.windll.FTD2XX
ftd2xx.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ftd2xx.FT_Open.restype = ctypes.c_uint32
ftd2xx.FT_Close.argtypes = [ctypes.c_void_p]
ftd2xx.FT_Close.restype = ctypes.c_uint32
ftd2xx.FT_GetDeviceInfo.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_uint32), ctypes.c_char_p, ctypes.c_char_p, ctypes.c_void_p]
ftd2xx.FT_GetDeviceInfo.restype = ctypes.c_uint32
ftd2xx.FT_GetQueueStatus.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_uint32)]
ftd2xx.FT_GetQueueStatus.restype = ctypes.c_uint32

# List devices first
num = ctypes.c_uint32()
ftd2xx.FT_ListDevices(ctypes.byref(num), None, 0x80000000)
print(f"Number of D2XX devices: {num.value}")

# Get serial numbers of all devices
if num.value > 0:
    buf = ctypes.create_string_buffer(256 * num.value)
    n = ctypes.c_uint32(num.value)
    ftd2xx.FT_ListDevices(buf, ctypes.byref(n), 0x80000001)
    sns = buf.raw.split(b'\x00')
    for i, sn in enumerate(sns):
        if sn:
            print(f"  Device {i}: SN={sn.decode('ascii', errors='replace')}")

# Try to open Channel B (device index 1)
print("\n=== Trying FT_Open(1) - Channel B ===")
handle = ctypes.c_void_p()
status = ftd2xx.FT_Open(1, ctypes.byref(handle))
print(f"FT_Open(1) status={status}")
if status == 0:
    ft_type = ctypes.c_uint32()
    dev_id = ctypes.c_uint32()
    sn = ctypes.create_string_buffer(16)
    desc = ctypes.create_string_buffer(64)
    s = ftd2xx.FT_GetDeviceInfo(handle, ctypes.byref(ft_type), ctypes.byref(dev_id), sn, desc, None)
    if s == 0:
        print(f"  Type={ft_type.value} (6=FT2232H)")
        print(f"  DeviceID=0x{dev_id.value:08x}")
        print(f"  SN={sn.value.decode('ascii','replace')}")
        print(f"  Desc={desc.value.decode('ascii','replace')}")
        print()
        if 'B' in desc.value.decode('ascii','replace'):
            print("  -> Channel B accessible via D2XX! Vivado hw_server should work.")
        else:
            print("  -> WARNING: This might not be Channel B")
    ftd2xx.FT_Close(handle)
else:
    print(f"  FAILED - Vivado cannot access Channel B for JTAG!")
    print(f"  Possible causes:")
    print(f"  - Channel B is in VCP mode (COM port locks it)")
    print(f"  - Another process (Vivado/hw_server) holds Channel B")

# Also try Channel A
print("\n=== Trying FT_Open(0) - Channel A ===")
handle2 = ctypes.c_void_p()
status2 = ftd2xx.FT_Open(0, ctypes.byref(handle2))
print(f"FT_Open(0) status={status2}")
if status2 == 0:
    ft_type2 = ctypes.c_uint32()
    dev_id2 = ctypes.c_uint32()
    sn2 = ctypes.create_string_buffer(16)
    desc2 = ctypes.create_string_buffer(64)
    s2 = ftd2xx.FT_GetDeviceInfo(handle2, ctypes.byref(ft_type2), ctypes.byref(dev_id2), sn2, desc2, None)
    if s2 == 0:
        print(f"  Desc={desc2.value.decode('ascii','replace')}")
    ftd2xx.FT_Close(handle2)
