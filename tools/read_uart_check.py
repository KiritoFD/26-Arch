#!/usr/bin/env python3
"""Read UART from Channel B (device 1) WITHOUT Vivado programming.

First reads any buffered data (from previous power-on), then
waits for new data. If we see boot messages, FPGA is alive.

Usage: python tools\read_uart_check.py [duration_sec]
"""
import sys
import time
import ftd2xx


def main():
    duration = float(sys.argv[1]) if len(sys.argv) > 1 else 5.0

    print("=" * 60)
    print("Read UART from Channel B (device 1) — NO Vivado")
    print("=" * 60)

    num = ftd2xx.createDeviceInfoList()
    print(f"Found {num} FTDI device(s)")
    for i in range(num):
        info = ftd2xx.getDeviceInfoDetail(i)
        print(f"  [{i}] {info.get('description', b'?')} serial={info.get('serial', b'?')}")

    if num < 2:
        print("ERROR: Need 2 devices (Channel A + B)")
        sys.exit(1)

    # Open device 1 (Channel B = UART)
    print("\nOpening device 1 (Channel B)...")
    try:
        dev = ftd2xx.open(1)
    except Exception as e:
        print(f"ERROR opening device 1: {e}")
        sys.exit(1)

    # Configure UART
    dev.resetDevice()
    dev.setBaudRate(115200)
    dev.setDataCharacteristics(
        ftd2xx.defines.BITS_8,
        ftd2xx.defines.STOP_BITS_1,
        ftd2xx.defines.PARITY_NONE
    )
    dev.setFlowControl(ftd2xx.defines.FLOW_NONE, 0, 0)
    dev.setTimeouts(200, 200)
    # DON'T purge RX — keep buffered boot messages

    # Check if there's already buffered data
    queued = dev.getQueueStatus()
    print(f"RX buffer (boot messages): {queued} bytes")

    if queued > 0:
        data = dev.read(queued)
        if data:
            text = data.decode('ascii', errors='replace')
            print("\n--- BUFFERED DATA (boot messages) ---")
            print(text)
            print(f"--- END ({len(data)} bytes) ---")

    # Now wait for new data
    print(f"\nWaiting for new data ({duration}s)...")
    received = bytearray()
    start = time.time()

    while (time.time() - start) < duration:
        try:
            rx_bytes = dev.getQueueStatus()
            if rx_bytes > 0:
                data = dev.read(rx_bytes)
                if data:
                    received.extend(data)
                    elapsed = time.time() - start
                    text = data.decode('ascii', errors='replace')
                    print(f"  [{elapsed:.1f}s] +{len(data)} bytes: {repr(text[:80])}")
        except Exception as e:
            print(f"  read error: {e}")
        time.sleep(0.1)

    print(f"\nTotal new bytes: {len(received)}")

    if len(received) > 0:
        print("\n--- NEW DATA ---")
        print(received.decode('ascii', errors='replace'))

    dev.close()

    # Conclusion
    print("\n" + "=" * 60)
    print("CONCLUSION")
    print("=" * 60)
    if queued > 0 or len(received) > 0:
        print("✓ FPGA IS ALIVE — UART data received!")
        print("  The FPGA bitstream is running and xv6 is outputting.")
    else:
        print("✗ No UART data received.")
        print("  Possible causes:")
        print("  1. FPGA not programmed (no bitstream loaded)")
        print("  2. UART not connected (check physical pins)")
        print("  3. Baud rate mismatch")


if __name__ == "__main__":
    main()
