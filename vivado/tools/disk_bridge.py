#!/usr/bin/env python3
"""
disk_bridge.py - PC-side serial disk bridge + UART console for xv6 on Basys3 FPGA.

The FPGA UART TX line carries both:
  - Console output (xv6 printf characters)
  - Disk requests: [0xAA, 0xBB, blockno_3, blockno_2, blockno_1, blockno_0]

This script reads the serial port, prints console output to stdout,
detects disk requests, and sends back disk data:
  PC -> FPGA: [0xCC, 0xDD, data_byte0, ..., data_byte1023]

Usage:
  python disk_bridge.py --port COM4 --image fs.img
  python disk_bridge.py --port /dev/ttyUSB0 --image fs.img
"""

import argparse
import struct
import sys
import threading

try:
    import serial
except ImportError:
    print("Error: pyserial not installed. Run: pip install pyserial")
    sys.exit(1)


def main():
    parser = argparse.ArgumentParser(description="Serial disk bridge + UART console for xv6 on FPGA")
    parser.add_argument("--port", required=True, help="Serial port (e.g. COM4 or /dev/ttyUSB0)")
    parser.add_argument("--image", required=True, help="Path to fs.img disk image")
    parser.add_argument("--baud", type=int, default=115200, help="Baud rate (default: 115200)")
    parser.add_argument("--verbose", action="store_true", help="Print disk request debug info")
    args = parser.parse_args()

    # Load disk image
    with open(args.image, "rb") as f:
        disk_data = f.read()

    disk_size = len(disk_data)
    num_blocks = disk_size // 1024
    print(f"Loaded disk image: {args.image} ({disk_size} bytes, {num_blocks} blocks)", flush=True)

    # Open serial port
    ser = serial.Serial(args.port, args.baud, timeout=1)
    print(f"Opened serial port: {args.port} @ {args.baud}bps", flush=True)
    print("Waiting for UART output and disk requests from FPGA...", flush=True)

    request_count = 0
    buf = bytearray()  # RX byte buffer

    try:
        while True:
            # Read available bytes
            data = ser.read(256)
            if not data:
                continue

            buf.extend(data)

            # Process buffer: look for disk request pattern [0xAA, 0xBB, ...]
            # and print everything else as console output
            i = 0
            while i < len(buf):
                # Check for disk request header
                if buf[i] == 0xAA and i + 5 < len(buf) and buf[i+1] == 0xBB:
                    # Found disk request: [0xAA, 0xBB, blockno_3:0]
                    blockno_bytes = bytes(buf[i+2:i+6])
                    blockno = struct.unpack(">I", blockno_bytes)[0]
                    request_count += 1

                    if args.verbose:
                        print(f"\n  [DISK] Request #{request_count}: block {blockno}", end="", flush=True)

                    # Read 1024 bytes from disk image
                    offset = blockno * 1024
                    if offset + 1024 <= disk_size:
                        block_data = disk_data[offset:offset + 1024]
                    else:
                        block_data = b"\x00" * 1024
                        if args.verbose:
                            print(f" (out of range, zeros)", end="", flush=True)

                    # Send response: [0xCC, 0xDD, data_0..data_1023]
                    response = b"\xCC\xDD" + block_data
                    ser.write(response)
                    ser.flush()

                    if args.verbose:
                        print(f" -> sent 1026 bytes", flush=True)

                    if request_count % 50 == 0:
                        print(f"\n  [DISK] Served {request_count} requests total", flush=True)

                    i += 6  # Skip past the request header
                else:
                    # Console output byte - print as character
                    b = buf[i]
                    if 0x20 <= b <= 0x7e or b in (0x0a, 0x0d, 0x09):
                        sys.stdout.write(chr(b))
                    else:
                        # Non-printable: show hex for debug
                        sys.stdout.write(f"\\x{b:02x}")
                    sys.stdout.flush()
                    i += 1

            # Clear processed bytes
            buf.clear()

    except KeyboardInterrupt:
        print(f"\n\nShutting down. Served {request_count} disk requests total.", flush=True)
    finally:
        ser.close()


if __name__ == "__main__":
    main()
