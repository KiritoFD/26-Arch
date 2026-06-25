import serial, time, sys

# Test all combinations of COM ports and baud rates
ports = ['COM4', 'COM20']
bauds = [115200, 9600, 57600, 38400]

for port in ports:
    for baud in bauds:
        try:
            ser = serial.Serial(port, baud, timeout=1)
            start = time.time()
            data = bytearray()
            while time.time() - start < 3:
                chunk = ser.read(256)
                if chunk:
                    data.extend(chunk)
            ser.close()
            if data:
                print(f"[OK] {port} @ {baud}: {len(data)} bytes - {data[:50].hex()} - {data[:50].decode('utf-8', errors='replace')}")
            else:
                print(f"[--] {port} @ {baud}: no data")
        except Exception as e:
            print(f"[ERR] {port} @ {baud}: {e}")
