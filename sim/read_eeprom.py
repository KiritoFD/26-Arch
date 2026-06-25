"""Read FT2232 EEPROM using ftd2xx library (FTDI D2XX driver)."""
import sys

try:
    import ftd2xx
except ImportError:
    print("Installing ftd2xx...")
    import subprocess
    subprocess.check_call([sys.executable, "-m", "pip", "install", "ftd2xx"])
    import ftd2xx

# List all FTDI devices
devices = ftd2xx.listDevices()
print(f"Found {len(devices)} FTDI device(s)")
for i, dev in enumerate(devices):
    print(f"  Device {i}: {dev}")

# Open each device and read EEPROM
for i in range(len(devices)):
    try:
        d = ftd2xx.open(i)
        print(f"\n=== Device {i} ===")
        print(f"  Description: {d.getDeviceInfo()['description']}")
        print(f"  Serial: {d.getDeviceInfo()['serial']}")
        print(f"  Type: {d.getDeviceInfo()['type']}")
        print(f"  ID: {d.getDeviceInfo()['id']}")
        print(f"  Location: {d.getDeviceInfo()['loc_id']}")
        
        # Read EEPROM
        try:
            eeprom_data = d.readEEProm()
            print(f"  EEPROM size: {len(eeprom_data)} bytes")
            # Print first 64 bytes as hex dump
            for offset in range(0, min(128, len(eeprom_data)), 16):
                hex_str = ' '.join(f'{b:02x}' for b in eeprom_data[offset:offset+16])
                ascii_str = ''.join(chr(b) if 32 <= b < 127 else '.' for b in eeprom_data[offset:offset+16])
                print(f"  {offset:04x}: {hex_str}  {ascii_str}")
        except Exception as e2:
            print(f"  EEPROM read error: {e2}")
        
        d.close()
    except Exception as e:
        print(f"  Device {i} error: {e}")
