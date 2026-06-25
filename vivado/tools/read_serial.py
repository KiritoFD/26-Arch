import serial, time
s = serial.Serial('COM20', 115200, timeout=2)
print('Reading COM20 for 10s...', flush=True)
t0 = time.time()
while time.time() - t0 < 10:
    d = s.read(256)
    for b in d:
        if 32 <= b <= 126 or b in (10, 13):
            print(chr(b), end='', flush=True)
        else:
            print(f'[{b:02x}]', end='', flush=True)
s.close()
print('\nDone')
