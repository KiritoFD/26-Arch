"""Check FTD2XX.dll exports and find the one being loaded."""
import ctypes
import os
import subprocess

# Find which FTD2XX.dll is being loaded
print("=== Finding FTD2XX.dll locations ===")
for search_path in ['C:\\Windows\\System32', 'C:\\Windows\\SysWOW64']:
    dll = os.path.join(search_path, 'FTD2XX.dll')
    if os.path.exists(dll):
        import ctypes.wintypes
        # Get file version
        info = subprocess.run(['powershell', '-Command',
            f'(Get-Item "{dll}").VersionInfo | Select-Object FileVersion, ProductVersion, FileDescription, CompanyName | Format-List'],
            capture_output=True, text=True)
        print(f"{dll}:")
        print(info.stdout)

# Try loading from System32
print("\n=== Loading FTD2XX.dll ===")
ftd2xx = ctypes.windll.FTD2XX

# Try different function names for VID/PID
functions_to_try = [
    'FT_SetVIDPID',
    'FT_GetVIDPID',
    'FT_CreateDeviceInfoList',
    'FT_GetDeviceInfoList',
    'FT_GetDeviceInfoDetail',
    'FT_ListDevices',
    'FT_Open',
    'FT_OpenEx',
    'FT_ReadEE',
    'FT_WriteEE',
    'FT_Close',
    'FT_GetDeviceInfo',
    'FT_SetTimeouts',
]

print("\n=== Checking exported functions ===")
for func_name in functions_to_try:
    try:
        func = getattr(ftd2xx, func_name)
        print(f"  {func_name}: AVAILABLE")
    except AttributeError:
        print(f"  {func_name}: NOT FOUND")

# Try FT_CreateDeviceInfoList - this might see all devices
print("\n=== Trying FT_CreateDeviceInfoList ===")
try:
    ftd2xx.FT_CreateDeviceInfoList.argtypes = [ctypes.POINTER(ctypes.c_uint32)]
    ftd2xx.FT_CreateDeviceInfoList.restype = ctypes.c_uint32

    num_devices = ctypes.c_uint32(0)
    status = ftd2xx.FT_CreateDeviceInfoList(ctypes.byref(num_devices))
    print(f"  FT_CreateDeviceInfoList: status={status}, num={num_devices.value}")

    if num_devices.value > 0:
        print(f"  Found {num_devices.value} device(s)")
except Exception as e:
    print(f"  Error: {e}")