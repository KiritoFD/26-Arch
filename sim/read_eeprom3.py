"""Read FT2232 EEPROM using ftd2xx low-level API."""
import sys
import ctypes
import ftd2xx

devices = ftd2xx.listDevices()
print(f"Found {len(devices)} FTDI device(s)")

for i in range(len(devices)):
    try:
        d = ftd2xx.open(i)
        info = d.getDeviceInfo()
        print(f"\n=== Device {i}: {info['description']} ===")
        
        # Read EEPROM using ftd2xx function
        # ftd2xx uses ctypes to call FTD2XX DLL
        # Try to read EEPROM data
        try:
            # Method 1: Use ftd2xx's internal _ft function
            eeprom_data = (ctypes.c_ubyte * 256)()
            size = ctypes.c_ulong(256)
            result = d._ft.FT_EE_Read(d._handle, ctypes.byref(eeprom_data), ctypes.byref(size))
            print(f"  FT_EE_Read result: {result}")
            if result == 0:
                for offset in range(0, min(128, size.value), 16):
                    hex_str = ' '.join(f'{eeprom_data[offset+j]:02x}' for j in range(16))
                    print(f"  {offset:04x}: {hex_str}")
        except Exception as e2:
            print(f"  Method 1 error: {e2}")
        
        # Method 2: Try reading via FT_ReadEE
        try:
            # Read individual EEPROM words (16-bit)
            print("  Trying FT_ReadEE...")
            words = []
            for addr in range(0, 64):
                val = ctypes.c_ushort()
                result = d._ft.FT_ReadEE(d._handle, addr, ctypes.byref(val))
                if result != 0:
                    print(f"  FT_ReadEE failed at addr {addr}: {result}")
                    break
                words.append(val.value)
            
            if words:
                print(f"  Read {len(words)} EEPROM words:")
                for j in range(0, len(words), 8):
                    hex_str = ' '.join(f'{words[j+k]:04x}' for k in range(min(8, len(words)-j)))
                    print(f"  {j*2:04x}: {hex_str}")
                
                # Parse Channel A/B type from EEPROM word 3 (offset 0x06)
                # Word 3 = bytes 6-7
                if len(words) >= 4:
                    config_word = words[3]
                    ch_a_type = config_word & 0xFF
                    ch_b_type = (config_word >> 8) & 0xFF
                    type_names = {0: 'UART', 1: 'FT245 FIFO', 2: 'CPU FIFO', 4: 'OPTO'}
                    print(f"\n  Channel A type byte: {ch_a_type} ({type_names.get(ch_a_type, 'Unknown')})")
                    print(f"  Channel B type byte: {ch_b_type} ({type_names.get(ch_b_type, 'Unknown')})")
        except Exception as e3:
            print(f"  Method 2 error: {e3}")
        
        d.close()
    except Exception as e:
        print(f"  Device {i} error: {e}")
