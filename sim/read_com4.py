"""Force set COM4 to 115200 and read with explicit settings."""
import serial, time

# Try COM4 with explicit 115200 settings
ser = serial.Serial(
    port='COM4',
    baudrate=115200,
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    timeout=1,
    xonxoff=False,
    rtscts=False,
    dsrdtr=False
)

print(f"Opened {ser.name} at {ser.baudrate} baud")
print(f"  CTS={ser.cts}, DSR={ser.dsr}, RI={ser.ri}, CD={ser.cd}")
print(f"  RTS={ser.rts}, DTR={ser.dtr}")

# Toggle DTR/RTS to reset any FTDI state
ser.dtr = False
time.sleep(0.1)
ser.dtr = True
time.sleep(0.1)
ser.rts = True

print(f"\nReading for 10 seconds...")
start = time.time()
total = 0
while time.time() - start < 10:
    n = ser.in_waiting
    if n > 0:
        data = ser.read(n)
        total += len(data)
        print(f"  [{time.time()-start:.1f}s] {len(data)} bytes: {data[:50].hex()} = {data[:50].decode('utf-8', errors='replace')}")
    else:
        time.sleep(0.05)

print(f"\nTotal: {total} bytes")
print(f"Final CTS={ser.cts}, DSR={ser.dsr}")
ser.close()
