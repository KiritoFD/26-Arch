#!/usr/bin/env python3

import serial
import time

SERIAL_PORT = 'COM4'
BAUD_RATE = 115200

def main():
    print(f"Connecting to {SERIAL_PORT} at {BAUD_RATE} baud...")
    
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print("Connected!")
    
    time.sleep(2)
    
    fs_img_path = r'G:\GitHub\26-Arch\third_party\xv6-riscv\fs.img'
    print(f"Loading {fs_img_path}...")
    
    with open(fs_img_path, 'rb') as f:
        fs_data = f.read()
    
    print(f"fs.img size: {len(fs_data)} bytes")
    
    ser.flushInput()
    ser.flushOutput()
    
    print("\nSending file system image...")
    print("Press reset on FPGA now!")
    time.sleep(3)
    
    header = f"FSLOAD:{len(fs_data):08X}\n"
    print(f"Sending header: {header.strip()}")
    ser.write(header.encode('ascii'))
    
    chunk_size = 256
    total_sent = 0
    
    for i in range(0, len(fs_data), chunk_size):
        chunk = fs_data[i:i+chunk_size]
        ser.write(chunk)
        total_sent += len(chunk)
        progress = (total_sent / len(fs_data)) * 100
        print(f"  Sent {total_sent}/{len(fs_data)} bytes ({progress:.1f}%)...", end='\r')
        time.sleep(0.005)
    
    print()
    print("\nWaiting for confirmation...")
    
    response = b''
    timeout = 30
    start_time = time.time()
    
    while time.time() - start_time < timeout:
        if ser.in_waiting > 0:
            data = ser.read(ser.in_waiting)
            response += data
            print(data.decode('ascii', errors='replace'), end='')
            if b'FSLOAD_OK' in response:
                print("\nFile system loaded successfully!")
                break
    
    ser.close()

if __name__ == '__main__':
    main()