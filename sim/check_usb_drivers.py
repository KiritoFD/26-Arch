"""Check installed USB/serial drivers."""
import subprocess

cmd = [
    'powershell', '-NoProfile', '-Command',
    "Get-WmiObject Win32_PnPSignedDriver | Where-Object { "
    "$_.DeviceName -like '*WinUSB*' -or "
    "$_.DeviceName -like '*libusb*' -or "
    "$_.DeviceName -like '*USB Serial*' -or "
    "$_.DeviceName -like '*FTDI*' -or "
    "$_.DeviceName -like '*Digilent*' } | "
    "Select-Object DeviceName, DriverVersion, InfName | Format-List"
]
r = subprocess.run(cmd, capture_output=True, text=True)
print("=== USB/Serial Drivers ===")
print(r.stdout)
if r.stderr:
    print("STDERR:", r.stderr)
