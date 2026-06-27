#!/usr/bin/env python3
"""Read UART data from Basys3 FTDI Port A via D2XX API.
Opens device, waits for user to press btnC (reset), then reads continuously.
"""
import sys
import time
import ftd2xx

def main():
    baud = int(sys.argv[1]) if len(sys.argv) > 1 else 115200
    duration = float(sys.argv[2]) if len(sys.argv) > 2 else 30.0

    num_devices = ftd2xx.createDeviceInfoList()
    print(f"Found {num_devices} FTDI device(s)")
    if num_devices == 0:
        print("ERROR: No FTDI devices found")
        sys.exit(1)

    # Open Port A (device 0)
    print("Opening Port A (device 0)...")
    dev = ftd2xx.open(0)
    dev.resetDevice()
    dev.setBaudRate(baud)
    dev.setDataCharacteristics(
        ftd2xx.defines.BITS_8,
        ftd2xx.defines.STOP_BITS_1,
        ftd2xx.defines.PARITY_NONE
    )
    dev.setFlowControl(ftd2xx.defines.FLOW_NONE, 0, 0)
    dev.setTimeouts(1000, 1000)
    dev.purge(ftd2xx.defines.PURGE_RX | ftd2xx.defines.PURGE_TX)

    print(f"UART ready: {baud} baud, 8N1")
    print("=" * 60)
    print(">>> PRESS btnC (reset) ON THE BASYS3 NOW! <<<")
    print(">>> (or unplug/replug USB to reload bitstream) <<<")
    print("=" * 60)
    print(f"Reading for {duration}s...")

    start = time.time()
    total_bytes = 0
    try:
        while (time.time() - start) < duration:
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

            time.sleep(0.01)

    except KeyboardInterrupt:
        print("\n\nStopped by user")

    elapsed = time.time() - start
    print(f"\n{'=' * 60}")
    print(f"Total bytes read: {total_bytes} in {elapsed:.1f}s")
    if total_bytes == 0:
        print("WARNING: No UART data received.")
        print("Possible causes:")
        print("  1. FTDI Port A not in UART mode (EEPROM config)")
        print("  2. RsTx not connected to FTDI RX (hardware)")
        print("  3. CPU not executing (stuck in reset or disk wait)")
        print("  4. Baud rate mismatch")
    else:
        print(f"SUCCESS: Received {total_bytes} bytes!")

    dev.close()

if __name__ == "__main__":
    main()
