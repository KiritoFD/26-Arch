#!/usr/bin/env python3
"""Reprogram FPGA (restart xv6 boot) and immediately read UART via D2XX.

This script:
1. Opens D2XX device 0 (Port A) and configures UART
2. Calls Vivado Tcl to reprogram the FPGA (restarts xv6 boot)
3. Reads UART data for the specified duration
4. Prints received data (boot messages)

Usage: python reprogram_and_read.py [duration_sec]
"""
import sys
import time
import subprocess
import threading
import ftd2xx

VIVADO = r"C:\Xilinx\Vivado\2019.2\bin\vivado.bat"
TCL_SCRIPT = r"g:\GitHub\26-Arch\vivado\program_only.tcl"

def program_fpga():
    """Reprogram FPGA via Vivado Tcl (restarts xv6 boot)."""
    print("[Vivado] Programming FPGA (restarts xv6)...")
    proc = subprocess.run(
        [VIVADO, "-mode", "batch", "-source", TCL_SCRIPT],
        capture_output=True, text=True, timeout=120
    )
    print(f"[Vivado] Exit code: {proc.returncode}")
    if proc.returncode != 0:
        print(f"[Vivado] STDERR: {proc.stderr[:500]}")
    return proc.returncode == 0


def main():
    duration = float(sys.argv[1]) if len(sys.argv) > 1 else 15.0

    # Step 1: Open D2XX and configure UART BEFORE programming
    print("=" * 60)
    print("Step 1: Opening D2XX device (Port A)...")
    print("=" * 60)

    num_devices = ftd2xx.createDeviceInfoList()
    print(f"Found {num_devices} FTDI device(s)")
    for i in range(num_devices):
        info = ftd2xx.getDeviceInfoDetail(i)
        desc = info.get('description', b'?')
        print(f"  [{i}] {desc}")

    if num_devices == 0:
        print("ERROR: No FTDI devices found")
        sys.exit(1)

    # Open Port A (device 0)
    print("\nOpening device 0 (Port A)...")
    dev = ftd2xx.open(0)
    print(f"Opened: {dev}")

    # Reset and configure UART
    dev.resetDevice()
    dev.setBaudRate(115200)
    dev.setDataCharacteristics(
        ftd2xx.defines.BITS_8,
        ftd2xx.defines.STOP_BITS_1,
        ftd2xx.defines.PARITY_NONE
    )
    dev.setFlowControl(ftd2xx.defines.FLOW_NONE, 0, 0)
    dev.setTimeouts(500, 500)  # 500ms read timeout
    dev.purge(ftd2xx.defines.PURGE_RX | ftd2xx.defines.PURGE_TX)

    print("UART configured: 115200 baud, 8N1")
    print("Purged RX/TX buffers")

    # Step 2: Reprogram FPGA (restarts xv6 boot)
    print("\n" + "=" * 60)
    print("Step 2: Reprogramming FPGA (xv6 will restart)...")
    print("=" * 60)

    # Start reading in background thread BEFORE programming
    received_data = bytearray()
    reading = True

    def reader_thread():
        """Background thread that continuously reads UART data."""
        while reading:
            try:
                rx_bytes = dev.getQueueStatus()
                if rx_bytes > 0:
                    data = dev.read(rx_bytes)
                    if data:
                        received_data.extend(data)
            except Exception:
                pass
            time.sleep(0.005)  # 5ms polling

    reader = threading.Thread(target=reader_thread, daemon=True)
    reader.start()
    print("Background UART reader started")

    # Program FPGA (this restarts xv6)
    ok = program_fpga()
    if not ok:
        print("WARNING: FPGA programming may have failed")

    # Step 3: Read UART data for the specified duration
    print("\n" + "=" * 60)
    print(f"Step 3: Reading UART for {duration} seconds...")
    print("=" * 60)

    start = time.time()
    last_len = 0
    while (time.time() - start) < duration:
        time.sleep(0.5)
        elapsed = time.time() - start
        current_len = len(received_data)
        if current_len > last_len:
            # Print new data
            new_data = received_data[last_len:]
            text = new_data.decode('ascii', errors='replace')
            print(f"[{elapsed:.1f}s] +{len(new_data)} bytes: {repr(text[:80])}")
            last_len = current_len
        else:
            print(f"[{elapsed:.1f}s] waiting... ({current_len} bytes total)")

    # Stop reader thread
    reading = False
    reader.join(timeout=2)

    # Step 4: Print summary
    print("\n" + "=" * 60)
    print("CAPTURE COMPLETE")
    print("=" * 60)
    print(f"Total bytes received: {len(received_data)}")

    if len(received_data) > 0:
        print("\n--- Received UART data (ASCII) ---")
        text = received_data.decode('ascii', errors='replace')
        print(text)
        print("--- End of data ---")

        # Also print hex dump for first 64 bytes
        print("\n--- Hex dump (first 64 bytes) ---")
        for i in range(0, min(64, len(received_data)), 16):
            chunk = received_data[i:i+16]
            hex_str = ' '.join(f'{b:02x}' for b in chunk)
            ascii_str = ''.join(chr(b) if 32 <= b < 127 else '.' for b in chunk)
            print(f"  {i:04x}: {hex_str:<48s} {ascii_str}")
    else:
        print("\nWARNING: No UART data received!")
        print("Possible causes:")
        print("  1. FTDI Channel A not connected to FPGA pin A18")
        print("  2. Baud rate mismatch (FPGA: ~115207, expected: 115200)")
        print("  3. xv6 crashed before writing to UART")
        print("  4. FTDI RX not receiving (hardware issue)")

    dev.close()


if __name__ == "__main__":
    main()
