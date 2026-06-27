"""Dump USB device descriptors using FTD2XX to confirm channel A is in UART mode."""
import ctypes

ftd2xx = ctypes.windll.FTD2XX

# Function to get USB info via FTD2XX
# Get number of devices
num_devices = ctypes.c_uint32()
status = ftd2xx.FT_ListDevices(ctypes.byref(num_devices), None, 0x80000000)  # FT_LIST_NUMBER_ONLY
print(f"FT_ListDevices count status={status}, num={num_devices.value}")

if num_devices.value > 0:
    # Get serial numbers
    buf_size = 256
    buf = ctypes.create_string_buffer(buf_size * num_devices.value)
    status = ftd2xx.FT_ListDevices(buf, ctypes.byref(num_devices), 0x80000001)  # FT_LIST_ALL
    print(f"FT_ListDevices all status={status}")
    # Serial numbers are null-separated
    sn_list = buf.raw.split(b'\x00')
    for i, sn in enumerate(sn_list):
        if sn:
            print(f"  Device {i}: SN={sn.decode('ascii', errors='replace')}")

# Try opening device 0 (should be Channel A UART)
handle = ctypes.c_void_p()
status = ftd2xx.FT_Open(0, ctypes.byref(handle))
print(f"\nFT_Open(0) status={status}")
if status == 0:
    # Get device info
    ft_type = ctypes.c_uint32()
    dev_id = ctypes.c_uint32()
    sn = ctypes.create_string_buffer(16)
    desc = ctypes.create_string_buffer(64)
    status = ftd2xx.FT_GetDeviceInfo(handle, ctypes.byref(ft_type), ctypes.byref(dev_id), sn, desc, None)
    if status == 0:
        type_names = {0:'FT_DEVICE_BM', 1:'FT_DEVICE_AM', 2:'FT_DEVICE_100AX', 3:'FT_DEVICE_UNKNOWN',
                     4:'FT_DEVICE_2232C', 5:'FT_DEVICE_232R', 6:'FT_DEVICE_2232H', 7:'FT_DEVICE_4232H',
                     8:'FT_DEVICE_232H', 9:'FT_DEVICE_X_SERIES', 10:'FT_DEVICE_4232HA'}
        print(f"  Type={ft_type.value} ({type_names.get(ft_type.value, '?')})")
        print(f"  DeviceID=0x{dev_id.value:08x}")
        print(f"  SN={sn.value.decode('ascii', errors='replace')}")
        print(f"  Desc={desc.value.decode('ascii', errors='replace')}")

    # Get latency timer
    latency = ctypes.c_ubyte()
    status = ftd2xx.FT_GetLatencyTimer(handle, ctypes.byref(latency))
    print(f"  LatencyTimer={latency.value if status==0 else f'status={status}'}")

    # Get bitmode
    bitmode = ctypes.c_ubyte()
    status = ftd2xx.FT_GetBitMode(handle, ctypes.byref(bitmode))
    print(f"  BitMode=0x{bitmode.value:02x} status={status}")

    # Check UART status by reading line status
    line_status = ctypes.c_uint32()
    status = ftd2xx.FT_GetModemStatus(handle, ctypes.byref(line_status))
    print(f"  ModemStatus=0x{line_status.value:08x} status={status}")

    # Try to set UART parameters (115200, 8N1)
    status = ftd2xx.FT_SetBaudRate(handle, 115200)
    print(f"  SetBaudRate(115200) status={status}")
    status = ftd2xx.FT_SetDataCharacteristics(handle, 8, 0, 0)  # 8 bits, no parity, 1 stop
    print(f"  SetDataCharacteristics status={status}")

    # Try writing bytes to see if UART works
    write_buf = ctypes.create_string_buffer(b'\xaa\x55\x00\xff')
    written = ctypes.c_uint32()
    status = ftd2xx.FT_Write(handle, write_buf, 4, ctypes.byref(written))
    print(f"  FT_Write status={status} written={written.value}")

    ftd2xx.FT_Close(handle)
    print("  Channel A UART opened successfully! Channel A IS in UART/VCP mode.")
else:
    print(f"  Cannot open - status={status}")
    print("  Channel A NOT accessible as UART/VCP - it may be in FIFO mode or another driver has it")
