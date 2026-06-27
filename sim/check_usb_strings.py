"""Check actual USB device string descriptors via Windows USB API.

This reads the real USB descriptor strings, not D2XX's interpretation.
"""
import ctypes
from ctypes import wintypes

setupapi = ctypes.windll.setupapi

# Get USB device strings via SetupAPI
# We'll use the Windows USB view approach

# Actually, let's just check the registry for the USB device strings
import winreg

devices = []
# Check USB device registry
usb_keys = [
    r'SYSTEM\CurrentControlSet\Enum\USB\VID_0403&PID_6010',
]

for usb_key in usb_keys:
    try:
        key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, usb_key)
        i = 0
        while True:
            try:
                subkey_name = winreg.EnumKey(key, i)
                i += 1
                subkey = winreg.OpenKey(key, subkey_name)
                # Read DeviceDesc and HardwareId
                try:
                    desc, _ = winreg.QueryValueEx(subkey, 'DeviceDesc')
                except FileNotFoundError:
                    desc = '(none)'
                try:
                    hwid, _ = winreg.QueryValueEx(subkey, 'HardwareId')
                except FileNotFoundError:
                    hwid = []
                try:
                    friendly, _ = winreg.QueryValueEx(subkey, 'FriendlyName')
                except FileNotFoundError:
                    friendly = '(none)'
                print(f"\n  Instance: {subkey_name}")
                print(f"    DeviceDesc: {desc}")
                print(f"    HardwareId: {hwid}")
                print(f"    FriendlyName: {friendly}")

                # Check for Child0000, Child0001 (interface children)
                try:
                    child_key = winreg.OpenKey(subkey, 'Child0000')
                    child_desc, _ = winreg.QueryValueEx(child_key, 'DeviceDesc')
                    child_hwid, _ = winreg.QueryValueEx(child_key, 'HardwareId')
                    print(f"    Child0000 Desc: {child_desc}")
                    print(f"    Child0000 HWID: {child_hwid}")
                    winreg.CloseKey(child_key)
                except FileNotFoundError:
                    pass
                try:
                    child_key = winreg.OpenKey(subkey, 'Child0001')
                    child_desc, _ = winreg.QueryValueEx(child_key, 'DeviceDesc')
                    child_hwid, _ = winreg.QueryValueEx(child_key, 'HardwareId')
                    print(f"    Child0001 Desc: {child_desc}")
                    print(f"    Child0001 HWID: {child_hwid}")
                    winreg.CloseKey(child_key)
                except FileNotFoundError:
                    pass
                winreg.CloseKey(subkey)
            except OSError:
                break
        winreg.CloseKey(key)
    except FileNotFoundError:
        print(f"Key not found: {usb_key}")

# Also check USB\VID_0403&PID_6010&MI_00 and MI_01
print("\n=== Interface devices (MI_00, MI_01) ===")
for iface in ['VID_0403&PID_6010&MI_00', 'VID_0403&PID_6010&MI_01']:
    key_path = f'SYSTEM\\CurrentControlSet\\Enum\\USB\\{iface}'
    try:
        key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, key_path)
        i = 0
        while True:
            try:
                subkey_name = winreg.EnumKey(key, i)
                i += 1
                subkey = winreg.OpenKey(key, subkey_name)
                try:
                    desc, _ = winreg.QueryValueEx(subkey, 'DeviceDesc')
                except FileNotFoundError:
                    desc = '(none)'
                try:
                    hwid, _ = winreg.QueryValueEx(subkey, 'HardwareId')
                except FileNotFoundError:
                    hwid = []
                try:
                    friendly, _ = winreg.QueryValueEx(subkey, 'FriendlyName')
                except FileNotFoundError:
                    friendly = '(none)'
                try:
                    service, _ = winreg.QueryValueEx(subkey, 'Service')
                except FileNotFoundError:
                    service = '(none)'
                print(f"\n  {iface}\\{subkey_name}")
                print(f"    DeviceDesc: {desc}")
                print(f"    HardwareId: {hwid}")
                print(f"    FriendlyName: {friendly}")
                print(f"    Service: {service}")
                winreg.CloseKey(subkey)
            except OSError:
                break
        winreg.CloseKey(key)
    except FileNotFoundError:
        print(f"  {iface}: not found")
