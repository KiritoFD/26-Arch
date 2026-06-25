"""Serial port test - try both COM ports and read continuously."""
import serial
import time
import sys

def test_port(port_name, baud=115200, timeout=5):
    print(f"\n=== Testing {port_name} at {baud} baud ===")
    try:
        ser = serial.Serial(port_name, baud, timeout=0.1)
        ser.flushInput()
        ser.flushOutput()
        
        start = time.time()
        output = ""
        while time.time() - start < timeout:
            if ser.in_waiting > 0:
                data = ser.read(ser.in_waiting).decode('ascii', errors='replace')
                output += data
                print(data, end='', flush=True)
            time.sleep(0.01)
        
        ser.close()
        if output:
            print(f"\n[Received {len(output)} bytes from {port_name}]")
        else:
            print(f"[No data from {port_name}]")
        return output
    except serial.SerialException as e:
        print(f"Error: {e}")
        return ""

# Test both COM ports
for port in ['COM4', 'COM20']:
    test_port(port, timeout=5)

# Also try with SW0=ON (standalone test sends 'A')
print("\n\nIf SW0=ON, should see 'A' characters...")
print("If SW0=OFF, should see xv6 boot message...")
print("\nTrying longer read on COM4...")
test_port('COM4', timeout=10)
