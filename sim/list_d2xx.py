"""List D2XX devices and try to open each."""
import ctypes
ftd2xx = ctypes.windll.FTD2XX

# FT_ListDevices
ftd2xx.FT_ListDevices.argtypes = [ctypes.POINTER(ctypes.c_uint32), ctypes.c_void_p, ctypes.c_uint32]
ftd2xx.FT_ListDevices.restype = ctypes.c_uint32

# Get num devices
num = ctypes.c_uint32(0)
status = ftd2xx.FT_ListDevices(ctypes.byref(num), None, 0x80000000)
print(f"FT_ListDevices num status={status}, num={num.value}")

# Get serial numbers
buf = ctypes.create_string_buffer(4096)
status = ftd2xx.FT_ListDevices(None, buf, 0x20000000)
print(f"FT_ListDevices all status={status}")
if status == 0:
    s = buf.value.decode('ascii', errors='replace')
    print(f"  Devices: {s}")

# Try opening device 0, 1, 2
ftd2xx.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ftd2xx.FT_Open.restype = ctypes.c_uint32

for idx in range(num.value + 2):
    handle = ctypes.c_void_p()
    status = ftd2xx.FT_Open(idx, ctypes.byref(handle))
    if status == 0:
        print(f"  FT_Open({idx}) OK - device available")
        ftd2xx.FT_Close(handle)
    else:
        print(f"  FT_Open({idx}) failed: {status}")

# Check if COM ports are using FTDI (which would block D2XX access)
import subprocess
print("\n=== COM ports ===")
result = subprocess.run(['powershell', '-Command', 'Get-WmiObject Win32_SerialPort | Select-Object DeviceID, Caption, PNPDeviceID | Format-List'], capture_output=True, text=True)
print(result.stdout)
if result.returncode != 0:
    # Try another way
    result = subprocess.run(['powershell', '-Command', 'Get-WmiObject Win32_PnPEntity | Where-Object {$_.Name -match "COM"} | Select-Object Name, DeviceID | Format-List'], capture_output=True, text=True)
    print(result.stdout)
