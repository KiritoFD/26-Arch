"""Read FTDI FT2232 EEPROM configuration using pyftdi."""
import sys

try:
    from pyftdi.ftdi import Ftdi
    from pyftdi.eeprom import FtdiEeprom
except ImportError:
    print("pyftdi not available, trying alternative approach")
    sys.exit(1)

# List devices
ftdi = Ftdi()
devices = ftdi.find_all([(0x0403, 0x6010)])
print(f"Found {len(devices)} FT2232 devices")
for i, dev in enumerate(devices):
    print(f"  Device {i}: bus={dev[0]}, addr={dev[1]}, SN={dev[2]}, desc={dev[3]}")

# Try to read EEPROM from each device
for i in range(len(devices)):
    for iface in [0, 1]:
        try:
            f = Ftdi()
            url = f'ftdi://ftdi:2232/{i}/{iface}'
            f.open_from_url(url)
            print(f"\nDevice {i} Interface {iface}:")
            print(f"  Chip: {f.chip_name}")
            
            # Try to read EEPROM
            try:
                eeprom = FtdiEeprom()
                eeprom.open(f'ftdi://ftdi:2232/{i}/')
                print(f"  EEPROM loaded")
                print(f"  Manufacturer: {eeprom.manufacturer_name}")
                print(f"  Product: {eeprom.product_name}")
                print(f"  Serial: {eeprom.serial_number}")
                print(f"  Channel A type: {eeprom.channel_a_type}")
                print(f"  Channel B type: {eeprom.channel_b_type}")
            except Exception as e2:
                print(f"  EEPROM read error: {e2}")
            
            f.close()
        except Exception as e:
            print(f"  Device {i} Interface {iface} error: {e}")
