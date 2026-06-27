#!/usr/bin/env python3
"""Check Windows device driver bindings for FTDI devices.

Lists all FTDI/Digilent devices with their bound driver INF.
"""
import subprocess

def main():
    print("=" * 60)
    print("Windows FTDI Device Driver Bindings")
    print("=" * 60)

    # Method 1: Get-WmiObject Win32_PnPSignedDriver
    print("\n--- Method 1: Win32_PnPSignedDriver ---")
    ps_cmd = """
    Get-WmiObject Win32_PnPSignedDriver | Where-Object {
        $_.DeviceID -match 'VID_0403' -or $_.DeviceID -match 'VID_1443'
    } | Select-Object DeviceName, DriverProviderName, DriverVersion, InfName, DeviceID, Status | Format-List
    """
    result = subprocess.run(['powershell', '-Command', ps_cmd],
                            capture_output=True, text=True, timeout=30)
    print(result.stdout)
    if result.stderr:
        print(f"STDERR: {result.stderr[:500]}")

    # Method 2: Get-PnpDevice
    print("\n--- Method 2: Get-PnpDevice ---")
    ps_cmd2 = """
    Get-PnpDevice | Where-Object {
        $_.InstanceId -match 'VID_0403' -or $_.InstanceId -match 'VID_1443'
    } | Select-Object FriendlyName, Class, Status, InstanceId | Format-List
    """
    result2 = subprocess.run(['powershell', '-Command', ps_cmd2],
                             capture_output=True, text=True, timeout=30)
    print(result2.stdout)
    if result2.stderr:
        print(f"STDERR: {result2.stderr[:500]}")

    # Method 3: pnputil /enum-devices
    print("\n--- Method 3: pnputil /enum-devices /class USB ---")
    result3 = subprocess.run(['pnputil', '/enum-devices', '/class', 'USB'],
                             capture_output=True, text=True, timeout=30)
    output = result3.stdout
    # Filter for FTDI/Digilent entries
    lines = output.split('\n')
    relevant = []
    capture = False
    for line in lines:
        if 'VID_0403' in line or 'VID_1443' in line or 'FTDI' in line or 'Digilent' in line:
            relevant.append(line)
            capture = True
        elif capture and (line.strip() == '' or line.startswith('Instance ID')):
            if line.strip() == '':
                relevant.append('')
            capture = False
        elif capture:
            relevant.append(line)
    print('\n'.join(relevant[:50]) if relevant else "No FTDI/Digilent entries found in USB class")

    # Also list COM ports
    print("\n--- COM Ports ---")
    ps_cmd3 = """
    Get-WmiObject Win32_PnPEntity | Where-Object { $_.Name -match 'COM\\d+' } | Select-Object Name, DeviceID | Format-List
    """
    result4 = subprocess.run(['powershell', '-Command', ps_cmd3],
                            capture_output=True, text=True, timeout=30)
    print(result4.stdout if result4.stdout else "No COM ports found")


if __name__ == "__main__":
    main()
