"""Query PnP devices for FTDI/Basys3 via WMI."""
import subprocess
import re

cmd = [
    'powershell', '-NoProfile', '-Command',
    "Get-WmiObject Win32_PnPEntity | Where-Object { $_.DeviceID -like '*VID_1443*' -or $_.DeviceID -like '*VID_0403*' } | Select-Object Name, Status, DeviceID | Format-List"
]
r = subprocess.run(cmd, capture_output=True, text=True)
print("=== PnP Devices (VID 0403/1443) ===")
print(r.stdout)
if r.stderr:
    print("STDERR:", r.stderr)
