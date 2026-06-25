"""Test COM4 with many different baud rates."""
import serial, time

bauds = [300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600]

for baud in bauds:
    try:
        ser = serial.Serial('COM4', baud, timeout=0.5)
        start = time.time()
        data = bytearray()
        while time.time() - start < 2:
            chunk = ser.read(256)
            if chunk:
                data.extend(chunk)
        ser.close()
        if data:
            print(f"[OK] {baud}: {len(data)} bytes - {data[:30].hex()}")
        else:
            print(f"[--] {baud}: no data")
    except Exception as e:
        print(f"[ERR] {baud}: {e}")
