import serial, time, sys, threading

def read_port(port, results, timeout=10):
    try:
        ser = serial.Serial(port, 115200, timeout=1)
        start = time.time()
        data = bytearray()
        while time.time() - start < timeout:
            chunk = ser.read(1024)
            if chunk:
                data.extend(chunk)
        ser.close()
        results[port] = data
    except Exception as e:
        results[port] = f"Error: {e}"

results = {}
threads = []
for port in ['COM4', 'COM20']:
    t = threading.Thread(target=read_port, args=(port, results))
    t.start()
    threads.append(t)

for t in threads:
    t.join()

for port, data in results.items():
    if isinstance(data, bytearray):
        if data:
            print(f"{port}: {len(data)} bytes - {data[:100].hex()}")
            print(f"  Text: {data[:200].decode('utf-8', errors='replace')}")
        else:
            print(f"{port}: No data")
    else:
        print(f"{port}: {data}")
