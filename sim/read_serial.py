import serial, time, sys

port = sys.argv[1] if len(sys.argv) > 1 else 'COM4'
timeout = int(sys.argv[2]) if len(sys.argv) > 2 else 5

try:
    ser = serial.Serial(port, 115200, timeout=1)
    start = time.time()
    data = bytearray()
    while time.time() - start < timeout:
        chunk = ser.read(1024)
        if chunk:
            data.extend(chunk)
    ser.close()
    if data:
        print(f'Received {len(data)} bytes on {port}')
        print(f'Hex: {data[:100].hex()}')
        print(f'Text: {data[:200].decode("utf-8", errors="replace")}')
    else:
        print(f'No data received on {port} in {timeout}s')
except Exception as e:
    print(f'Error on {port}: {e}')
