"""Read FT2232 EEPROM using ftd2xx - simplified version."""
import sys
import ftd2xx

# List all FTDI devices
devices = ftd2xx.listDevices()
print(f"Found {len(devices)} FTDI device(s)")

for i in range(len(devices)):
    try:
        d = ftd2xx.open(i)
        info = d.getDeviceInfo()
        print(f"\n=== Device {i}: {info['description']} ===")
        print(f"  Serial: {info['serial']}")
        print(f"  Type: {info['type']}")  # Type 6 = FT2232H
        print(f"  Vendor ID: 0x{(info['id'] >> 16) & 0xFFFF:04x}")
        print(f"  Product ID: 0x{info['id'] & 0xFFFF:04x}")
        
        # Read EEPROM raw
        try:
            eeprom = d.readEEProm()
            print(f"  EEPROM: {len(eeprom)} bytes")
            # Hex dump first 128 bytes
            for offset in range(0, min(128, len(eeprom)), 16):
                hex_str = ' '.join(f'{b:02x}' for b in eeprom[offset:offset+16])
                ascii_str = ''.join(chr(b) if 32 <= b < 127 else '.' for b in eeprom[offset:offset+16])
                print(f"  {offset:04x}: {hex_str}  {ascii_str}")
            
            # Parse FT2232H EEPROM structure
            # Offset 0x00: Vendor ID (little-endian)
            # Offset 0x02: Product ID (little-endian)
            # Offset 0x04: Device release
            # Offset 0x06: Config descriptor (byte 0 = Channel A type, byte 1 = Channel B type)
            # Channel type: 0=UART, 1=FT245 FIFO, 2=CPU FIFO, 4=opto-isolate
            if len(eeprom) >= 8:
                vid = eeprom[0] | (eeprom[1] << 8)
                pid = eeprom[2] | (eeprom[3] << 8)
                ch_a_type = eeprom[6]
                ch_b_type = eeprom[7]
                print(f"\n  Parsed EEPROM:")
                print(f"  VID: 0x{vid:04x}, PID: 0x{pid:04x}")
                type_names = {0: 'UART', 1: 'FT245 FIFO', 2: 'CPU FIFO', 3: 'OPTO', 4: 'FT2232H'}
                print(f"  Channel A type: {ch_a_type} ({type_names.get(ch_a_type, 'Unknown')})")
                print(f"  Channel B type: {ch_b_type} ({type_names.get(ch_b_type, 'Unknown')})")
        except Exception as e2:
            print(f"  EEPROM read error: {e2}")
        
        d.close()
    except Exception as e:
        print(f"  Device {i} error: {e}")
