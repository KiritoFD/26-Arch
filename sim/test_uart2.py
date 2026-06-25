"""Test: can we SEND data to COM4 and see it loop back?
Also test: try reading from COM20 with 115200 baud.
"""
import serial, time

# Test 1: Send data to COM4 and see if it echoes
print("=== Test 1: Send to COM4, check TX/RX ===")
try:
    ser = serial.Serial('COM4', 115200, timeout=1)
    print(f"COM4 opened. CTS={ser.cts}, DSR={ser.dsr}")
    
    # Send a byte
    ser.write(b'U')  # 'U' = 0x55 = 01010101, good for scope
    time.sleep(0.5)
    
    # Check if anything came back
    n = ser.in_waiting
    if n > 0:
        data = ser.read(n)
        print(f"  Received {n} bytes: {data.hex()}")
    else:
        print("  No echo (expected - no loopback)")
    ser.close()
except Exception as e:
    print(f"  Error: {e}")

# Test 2: Try COM20 as UART
print("\n=== Test 2: Read from COM20 @ 115200 ===")
try:
    ser = serial.Serial('COM20', 115200, timeout=1)
    print(f"COM20 opened. CTS={ser.cts}, DSR={ser.dsr}")
    start = time.time()
    total = 0
    while time.time() - start < 5:
        n = ser.in_waiting
        if n > 0:
            data = ser.read(n)
            total += len(data)
            print(f"  [{time.time()-start:.1f}s] {len(data)} bytes: {data[:30].hex()}")
        else:
            time.sleep(0.05)
    print(f"  Total: {total} bytes")
    ser.close()
except Exception as e:
    print(f"  Error: {e}")

# Test 3: Check if FTDI Channel B is in VCP mode
print("\n=== Test 3: FTDI driver info ===")
import subprocess
result = subprocess.run(['powershell', '-Command',
    'Get-PnpDevice -PresentOnly | Where-Object { $_.InstanceId -match "FTDIBUS" } | Select-Object Status, Class, FriendlyName, InstanceId'],
    capture_output=True, text=True)
print(result.stdout[:2000])
