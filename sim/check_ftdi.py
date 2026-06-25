"""Check FTDI driver status using Windows registry and device manager."""
import subprocess, re

# Check FTDI devices in device manager
result = subprocess.run(['powershell', '-Command',
    'Get-PnpDevice | Where-Object { $_.FriendlyName -match "FTDI|USB Serial" } | Select-Object Status, Class, FriendlyName, InstanceId | Format-List'],
    capture_output=True, text=True)
print("=== FTDI Devices ===")
print(result.stdout[:3000])

# Check COM port details
result2 = subprocess.run(['powershell', '-Command',
    'Get-WmiObject Win32_SerialPort | Select-Object DeviceID, Description, ProviderType, Status, StatusInfo | Format-List'],
    capture_output=True, text=True)
print("\n=== Serial Port Details ===")
print(result2.stdout[:3000])
