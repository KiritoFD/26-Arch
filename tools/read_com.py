#!/usr/bin/env python3
"""Read UART via COM port (pyserial).

Reads from COM port for a specified duration.
Can be used with FPGA reset to capture boot messages.

Usage: python tools\read_com.py [COM_PORT] [duration_sec]
"""
import sys
import time
import serial
import serial.tools.list_ports


def find_basys3_com():
    """Find FTDI COM port (Channel B)."""
    ports = serial.tools.list_ports.comports()
    for p in ports:
        if p.vid == 0x0403 and p.pid == 0x6010:
            return p.device
    return None


def main():
    # Find COM port
    com_port = sys.argv[1] if len(sys.argv) > 1 else find_basys3_com()
    duration = float(sys.argv[2]) if len(sys.argv) > 2 else 10.0

    if not com_port:
        print("ERROR: No FTDI COM port found")
        sys.exit(1)

    print("=" * 60)
    print(f"Read UART from {com_port} ({duration}s)")
    print("=" * 60)
    print("\n>>> PRESS THE RESET BUTTON ON BASYS3 NOW <<<")
    print(">>> (btnC or red button) to restart xv6 boot <<<\n")

    try:
        ser = serial.Serial(
            port=com_port,
            baudrate=115200,
            bytesize=serial.EIGHTBITS,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            timeout=0.1
        )
    except Exception as e:
        print(f"ERROR opening {com_port}: {e}")
        sys.exit(1)

    print(f"Opened {com_port} @ 115200 baud")
    print(f"Reading for {duration}s...\n")

    received = bytearray()
    start = time.time()

    while (time.time() - start) < duration:
        try:
            data = ser.read(1024)
            if data:
                received.extend(data)
                elapsed = time.time() - start
                text = data.decode('ascii', errors='replace')
                print(f"[{elapsed:.1f}s] +{len(data)}B: {repr(text[:80])}")
        except Exception as e:
            print(f"  read error: {e}")
            break

    ser.close()

    print(f"\n{'='*60}")
    print(f"TOTAL: {len(received)} bytes")
    print(f"{'='*60}")

    if len(received) > 0:
        print("\n--- ASCII ---")
        print(received.decode('ascii', errors='replace'))
        print("\n--- HEX (first 256) ---")
        for i in range(0, min(256, len(received)), 16):
            chunk = received[i:i+16]
            hex_str = ' '.join(f'{b:02x}' for b in chunk)
            ascii_str = ''.join(chr(b) if 32 <= b < 127 else '.' for b in chunk)
            print(f"  {i:04x}: {hex_str:<48s} {ascii_str}")
    else:
        print("\nNo data received.")
        print("Possible causes:")
        print("  1. FPGA not programmed (no bitstream)")
        print("  2. UART not outputting (xv6 not running)")
        print("  3. Wrong COM port / baud rate")


if __name__ == "__main__":
    main()
