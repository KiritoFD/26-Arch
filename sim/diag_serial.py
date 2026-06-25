"""Detailed COM port diagnostic."""
import serial, time

for port_name in ['COM4', 'COM20']:
    print(f"\n=== Testing {port_name} ===")
    try:
        ser = serial.Serial(port=port_name)
        print(f"  Opened: {ser.name}")
        print(f"  Port: {ser.port}")
        print(f"  Baudrate: {ser.baudrate}")
        print(f"  Bytesize: {ser.bytesize}")
        print(f"  Parity: {ser.parity}")
        print(f"  Stopbits: {ser.stopbits}")
        
        # Set RTS/DTR
        ser.rts = True
        ser.dtr = True
        time.sleep(0.5)
        
        # Read for 10 seconds
        start = time.time()
        total_bytes = 0
        while time.time() - start < 8:
            if ser.in_waiting > 0:
                chunk = ser.read(ser.in_waiting)
                total_bytes += len(chunk)
                print(f"  [{time.time()-start:.1f}s] Got {len(chunk)} bytes: {chunk[:32].hex()}")
            else:
                time.sleep(0.05)
        
        print(f"  Total: {total_bytes} bytes received")
        
        # Check line states
        print(f"  CTS: {ser.cts}, DSR: {ser.dsr}, RI: {ser.ri}, CD: {ser.cd}")
        
        ser.close()
    except Exception as e:
        print(f"  Error: {e}")

# Also list all USB devices via WMI
print("\n\n=== USB Devices ===")
import subprocess
result = subprocess.run(['powershell', '-Command',
    'Get-WmiObject Win32_USBControllerDevice | Select-Object Name, DeviceID | Format-List'],
    capture_output=True, text=True)
print(result.stdout[:2000])
