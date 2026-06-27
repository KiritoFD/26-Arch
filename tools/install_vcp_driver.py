#!/usr/bin/env python3
"""Force-load FTDI VCP (ftdiport) driver for Channel A.

After EEPROM swap, Windows D2XX driver still binds to Channel A.
We need to install the ftdiport driver to create a COM port.

Strategy:
1. Find FTDI VCP driver INF (oem*.inf or ftdiport.inf)
2. Use pnputil to install/add the driver package
3. Use pnputil to bind the driver to the FTDI device

Alternative: Use DevCon to restart the device
"""
import sys
import subprocess
import os
import glob


def find_ftdi_driver_inf():
    """Find FTDI VCP driver INF files in Windows DriverStore."""
    print("=" * 60)
    print("Searching for FTDI VCP driver INF files...")
    print("=" * 60)

    # Check Windows DriverStore
    driver_store = r"C:\Windows\System32\DriverStore\FileRepository"

    # Search for ftdiport.inf (VCP port driver) and ftdibus.inf (bus driver)
    ftdi_infs = []
    for root, dirs, files in os.walk(driver_store):
        for f in files:
            if f.lower() in ('ftdiport.inf', 'ftdibus.inf'):
                full_path = os.path.join(root, f)
                ftdi_infs.append(full_path)
                print(f"  Found: {full_path}")

    if not ftdi_infs:
        # Search common FTDI driver install locations
        for path in [r"C:\FTDI", r"C:\FT2232", os.path.expanduser("~/Downloads")]:
            if os.path.exists(path):
                for root, dirs, files in os.walk(path):
                    for f in files:
                        if f.lower().endswith('.inf') and 'ftdi' in f.lower():
                            full_path = os.path.join(root, f)
                            ftdi_infs.append(full_path)
                            print(f"  Found: {full_path}")

    return ftdi_infs


def list_ftdi_oem_inf():
    """List FTDI OEM INF files via pnputil."""
    print("\n" + "=" * 60)
    print("Listing installed FTDI driver packages (pnputil)...")
    print("=" * 60)

    try:
        result = subprocess.run(['pnputil', '/enum-drivers'],
                                capture_output=True, text=True, timeout=30)
        output = result.stdout

        # Parse the output — find FTDI entries
        lines = output.split('\n')
        ftdi_entries = []
        current_entry = {}
        for line in lines:
            line = line.strip()
            if line.startswith('Published Name:'):
                if current_entry and 'FTDI' in str(current_entry):
                    ftdi_entries.append(current_entry)
                current_entry = {'published': line.split(':', 1)[1].strip()}
            elif line.startswith('Original Name:'):
                current_entry['original'] = line.split(':', 1)[1].strip()
            elif line.startswith('Provider Name:'):
                current_entry['provider'] = line.split(':', 1)[1].strip()
            elif line.startswith('Class Name:'):
                current_entry['class'] = line.split(':', 1)[1].strip()
            elif line.startswith('Driver INF:'):
                current_entry['inf'] = line.split(':', 1)[1].strip()
                # Check if FTDI-related
                if 'ftdi' in current_entry.get('inf', '').lower() or \
                   'ftdi' in current_entry.get('provider', '').lower():
                    ftdi_entries.append(current_entry)
                    current_entry = {}

        # Also catch any trailing entry
        if current_entry and 'FTDI' in str(current_entry):
            ftdi_entries.append(current_entry)

        print(f"Found {len(ftdi_entries)} FTDI driver package(s):")
        for entry in ftdi_entries:
            print(f"  Published: {entry.get('published', '?')}")
            print(f"  Original:  {entry.get('original', '?')}")
            print(f"  Provider:  {entry.get('provider', '?')}")
            print(f"  Class:     {entry.get('class', '?')}")
            print(f"  INF:       {entry.get('inf', '?')}")
            print()

        return ftdi_entries
    except Exception as e:
        print(f"  Error: {e}")
        return []


def find_ftdi_device_hwids():
    """Find FTDI device hardware IDs."""
    print("\n" + "=" * 60)
    print("Finding FTDI device hardware IDs...")
    print("=" * 60)

    try:
        # Use PowerShell Get-PnpDevice
        result = subprocess.run(
            ['powershell', '-Command',
             'Get-PnpDevice | Where-Object { $_.FriendlyName -match "FTDI|Digilent|USB Serial" } | Select-Object FriendlyName, InstanceId, Status, Class | Format-List'],
            capture_output=True, text=True, timeout=30
        )
        print(result.stdout)
        if result.stderr:
            print(f"  STDERR: {result.stderr[:500]}")
    except Exception as e:
        print(f"  Error: {e}")

    try:
        # Also try Get-WmiObject
        result = subprocess.run(
            ['powershell', '-Command',
             'Get-WmiObject Win32_PnPEntity | Where-Object { $_.Name -match "FTDI|Digilent|USB Serial" } | Select-Object Name, DeviceID, Status | Format-List'],
            capture_output=True, text=True, timeout=30
        )
        print("WMI devices:")
        print(result.stdout)
    except Exception as e:
        print(f"  WMI error: {e}")


def main():
    # Find installed FTDI drivers
    oem_infs = list_ftdi_oem_inf()
    hwids = find_ftdi_device_hwids()

    # Try to install FTDI VCP driver
    print("\n" + "=" * 60)
    print("Attempting to install FTDI VCP driver...")
    print("=" * 60)

    # Find ftdiport.inf (the port driver, not the bus driver)
    ftdiport_inf = None
    for entry in oem_infs:
        inf = entry.get('inf', '').lower()
        if 'ftdiport' in inf:
            ftdiport_inf = entry.get('inf')
            break

    if not ftdiport_inf:
        print("  ftdiport.inf not found in DriverStore")
        print("  Trying to find it elsewhere...")
        found_infs = find_ftdi_driver_inf()
        for inf in found_infs:
            if 'ftdiport' in inf.lower():
                ftdiport_inf = inf
                break

    if ftdiport_inf:
        print(f"\n  Found ftdiport INF: {ftdiport_inf}")
        print("\n  To install, run as Administrator:")
        print(f"    pnputil /add-driver {ftdiport_inf} /install")
    else:
        print("\n  ftdiport.inf NOT FOUND on this system!")
        print("\n  To get VCP driver:")
        print("  1. Download from https://ftdichip.com/drivers/vcp-drivers/")
        print("  2. Extract the ZIP")
        print("  3. Run the installer (CDM v2.12.36.4 or later)")
        print("  4. Replug the USB cable")

    # Alternative: try to force re-enumeration
    print("\n" + "=" * 60)
    print("Alternative: Force device re-enumeration")
    print("=" * 60)
    print("  Try running as Administrator:")
    print("    pnputil /scan-devices")
    print("  This may trigger Windows to load the VCP driver for Channel A")


if __name__ == "__main__":
    main()
