"""Check Windows device tree for FTDI devices."""
import subprocess

cmd = 'Get-WmiObject Win32_PnPEntity | Where-Object { $_.DeviceID -match "VID_0403" } | Select-Object Name, DeviceID, Status | Format-List'
r = subprocess.run(['powershell', '-NoProfile', '-Command', cmd], capture_output=True, text=True)
print(r.stdout)
if r.stderr:
    print("STDERR:", r.stderr[:500])
