import serial
import time

SERIAL_PORT = 'COM4'
BAUD_RATE = 115200

def main():
    print(f"Connecting to {SERIAL_PORT} at {BAUD_RATE} baud...")
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print("Connected!")
        
        time.sleep(2)
        
        ser.flushInput()
        ser.flushOutput()
        
        print("\nWaiting for xv6 boot message...")
        start_time = time.time()
        timeout = 30
        
        output = ""
        while time.time() - start_time < timeout:
            if ser.in_waiting > 0:
                data = ser.read(ser.in_waiting).decode('ascii', errors='replace')
                output += data
                print(data, end='')
                if 'xv6' in output.lower() or 'panic' in output.lower():
                    break
        
        print(f"\n\nTotal output:\n{output}")
        ser.close()
        
    except serial.SerialException as e:
        print(f"Error: {e}")
        print("Please check if the FPGA is connected and the serial port is correct.")

if __name__ == '__main__':
    main()