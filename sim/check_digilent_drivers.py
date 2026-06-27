"""Check Digilent Adept driver installation."""
import subprocess

cmd = [
    'powershell', '-NoProfile', '-Command',
    "Get-WmiObject Win32_PnPSignedDriver | Where-Object { "
    "$_.DeviceName -like '*Digilent*' -or "
    "$_.DeviceName -like '*dpg*' -or "
    "$_.DeviceName -like '*Adept*' } | "
    "Select-Object DeviceName, DriverVersion, InfName, DeviceID | Format-List"
]
r = subprocess.run(cmd, capture_output=True, text=True)
print("=== Digilent Drivers ===")
print(r.stdout if r.stdout else "(none found)")

# Check for dpgdp / dpcutil
cmd2 = [
    'powershell', '-NoProfile', '-Command',
    "Get-ChildItem 'C:\\Windows\\System32\\drivers' -Filter 'dpg*' -ErrorAction SilentlyContinue | Select-Object Name; "
    "Get-ChildItem 'C:\\Windows\\System32' -Filter 'dpcutil*' -ErrorAction SilentlyContinue | Select-Object Name"
]
r2 = subprocess.run(cmd2, capture_output=True, text=True)
print("=== Digilent Driver Files ===")
print(r2.stdout if r2.stdout else "(none found)")
