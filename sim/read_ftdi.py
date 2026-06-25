"""Use pyftdi to directly read FT2232 UART data, bypassing Windows COM driver."""
import sys
try:
    from pyftdi.ftdi import Ftdi
except ImportError:
    print("pyftdi not installed, trying pip...")
    import subprocess
    subprocess.check_call([sys.executable, "-m", "pip", "install", "pyftdi"])
    from pyftdi.ftdi import Ftdi

ftdi = Ftdi()

# List all connected FT devices
print("Scanning for FT devices...")
devices = ftdi.find_all([(0x0403, 0x6010)])  # FT2232HQ
print(f"Found {len(devices)} device(s)")
for i, dev in enumerate(devices):
    print(f"  Device {i}: {dev}")

# Try to open each device's channel B (UART)
for i in range(len(devices)):
    try:
        f = Ftdi()
        # Open interface 1 (Channel B) - this is the UART port
        f.open_from_url(f'ftdi://?&interface=1')
        print(f"\nDevice {i} Channel B opened:")
        print(f"  Chip: {f.chip_name}")
        print(f"  Baudrate: {f.baudrate}")
        
        # Set baud rate and read
        f.set_baudrate(115200)
        f.set_line_property(8, 1, 'N')  # 8N1
        
        # Read with timeout
        import time
        start = time.time()
        data = bytearray()
        while time.time() - start < 5:
            chunk = f.read(256, 0.1)  # 100ms timeout per read
            if chunk:
                data.extend(chunk)
        
        f.close()
        if data:
            print(f"  Received {len(data)} bytes!")
            print(f"  Hex: {data[:50].hex()}")
            print(f"  Text: {data[:100].decode('utf-8', errors='replace')}")
        else:
            print(f"  No data received")
    except Exception as e:
        print(f"  Device {i} error: {e}")

# Also try Channel A (interface 0) just in case
for i in range(len(devices)):
    try:
        f = Ftdi()
        f.open_from_url(f'ftdi://?&interface=0')
        print(f"\nDevice {i} Channel A (JTAG?):")
        print(f"  Chip: {f.chip_name}")
        f.close()
    except Exception as e:
        pass
