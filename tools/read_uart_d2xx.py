#!/usr/bin/env python3
"""Read UART data from Basys3 FTDI Port A via D2XX API.

The Basys3 FTDI Port A is in UART mode but the VCP driver is not loaded,
so there is no COM port. This script uses the D2XX API directly to read
UART data from Port A.

Usage: python read_uart_d2xx.py [baud_rate] [duration_sec]
  baud_rate: default 115200
  duration_sec: default 10 (0 = run forever until Ctrl+C)
"""
import sys
import time
import ftd2xx

def main():
    baud = int(sys.argv[1]) if len(sys.argv) > 1 else 115200
    duration = float(sys.argv[2]) if len(sys.argv) > 2 else 10.0

    # List devices
    num_devices = ftd2xx.createDeviceInfoList()
    print(f"Found {num_devices} FTDI device(s):")
    for i in range(num_devices):
        info = ftd2xx.getDeviceInfoDetail(i)
        print(f"  [{i}] {info}")

    if num_devices == 0:
        print("ERROR: No FTDI devices found")
        sys.exit(1)

    # Open Port A (index 0)
    print(f"\nOpening device 0 (Port A)...")
    try:
        dev = ftd2xx.open(0)
    except Exception as e:
        print(f"ERROR: Cannot open device 0: {e}")
        print("Trying device 1...")
        try:
            dev = ftd2xx.open(1)
        except Exception as e2:
            print(f"ERROR: Cannot open device 1 either: {e2}")
            sys.exit(1)

    print(f"Opened: {dev}")

    # Reset device
    dev.resetDevice()

    # Configure UART parameters
    # baud = 25MHz / 217 ≈ 115207 ≈ 115200
    dev.setBaudRate(baud)
    dev.setDataCharacteristics(
        ftd2xx.defines.BITS_8,    # 8 data bits
        ftd2xx.defines.STOP_BITS_1, # 1 stop bit
        ftd2xx.defines.PARITY_NONE  # no parity
    )

    # Set flow control: none
    dev.setFlowControl(ftd2xx.defines.FLOW_NONE, 0, 0)

    # Set timeouts: read timeout 1000ms
    dev.setTimeouts(1000, 1000)

    # Purge buffers
    dev.purge(ftd2xx.defines.PURGE_RX | ftd2xx.defines.PURGE_TX)

    print(f"\nUART configured: {baud} baud, 8N1")
    print("Reading UART data (press Ctrl+C to stop)...")
    print("=" * 60)

    start = time.time()
    total_bytes = 0
    try:
        while duration == 0 or (time.time() - start) < duration:
            # Read available data
            try:
                rx_bytes = dev.getQueueStatus()
            except Exception:
                rx_bytes = 0

            if rx_bytes > 0:
                data = dev.read(rx_bytes)
                if data:
                    if isinstance(data, bytes):
                        text = data.decode('ascii', errors='replace')
                    else:
                        text = str(data)
                    sys.stdout.write(text)
                    sys.stdout.flush()
                    total_bytes += len(data)

            time.sleep(0.01)  # 10ms polling

    except KeyboardInterrupt:
        print("\n\nStopped by user")

    elapsed = time.time() - start
    print(f"\n{'=' * 60}")
    print(f"Total bytes read: {total_bytes} in {elapsed:.1f}s")
    if total_bytes == 0:
        print("WARNING: No UART data received. Try pressing btnC (reset) on the Basys3.")

    dev.close()

if __name__ == "__main__":
    main()
