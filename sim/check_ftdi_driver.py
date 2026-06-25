"""Reinstall FTDI driver for Channel B using pnputil."""
import subprocess

# List all FTDI drivers
result = subprocess.run(['powershell', '-Command',
    'Get-WmiObject Win32_PnPSignedDriver | Where-Object { $_.DeviceName -match "FTDI" } | Select-Object DeviceName, DriverVersion, InfName'],
    capture_output=True, text=True)
print("=== FTDI Drivers ===")
print(result.stdout[:2000])

# Check FTDI device details
result2 = subprocess.run(['powershell', '-Command',
    'Get-PnpDevice -PresentOnly | Where-Object { $_.InstanceId -match "FTDI" } | Select-Object Status, Class, FriendlyName, InstanceId | Format-List'],
    capture_output=True, text=True)
print("\n=== FTDI Devices ===")
print(result2.stdout[:2000])

# Try to reset COM4 device
result3 = subprocess.run(['powershell', '-Command',
    'Get-PnpDevice -PresentOnly | Where-Object { $_.FriendlyName -match "COM4" } | Select-Object Status, InstanceId'],
    capture_output=True, text=True)
print("\n=== COM4 Device ===")
print(result3.stdout[:1000])
