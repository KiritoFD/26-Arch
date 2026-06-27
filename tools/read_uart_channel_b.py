#!/usr/bin/env python3
"""Read UART data from Basys3 FTDI Channel B (device index 1).

Basys3 hardware connection:
  Channel A (device 0): FPGA JTAG → FIFO mode → Vivado
  Channel B (device 1): FPGA UART → UART mode → COM port

This script:
1. Programs FPGA (restarts xv6)
2. Opens D2XX device 1 (Channel B)
3. Reads UART data for boot messages

Usage: python tools\read_uart_channel_b.py [duration_sec]
"""
import sys
import time
import subprocess
import ftd2xx

VIVADO = r"C:\Xilinx\Vivado\2019.2\bin\vivado.bat"
TCL_SCRIPT = r"g:\GitHub\26-Arch\vivado\program_only.tcl"


def program_fpga():
    """Reprogram FPGA via Vivado Tcl."""
    print("[Vivado] Programming FPGA...")
    proc = subprocess.run(
        [VIVADO, "-mode", "batch", "-source", TCL_SCRIPT],
        capture_output=True, text=True, timeout=120
    )
    print(f"[Vivado] Exit code: {proc.returncode}")
    if proc.returncode != 0:
        print(f"[Vivado] STDOUT (last 500 chars):")
        print(proc.stdout[-500:])
    return proc.returncode == 0


def main():
    duration = float(sys.argv[1]) if len(sys.argv) > 1 else 10.0

    # Step 1: Program FPGA
    print("=" * 60)
    print("Step 1: Programming FPGA (restarts xv6)...")
    print("=" * 60)
    ok = program_fpga()

    # Step 2: Open D2XX device 1 (Channel B - UART)
    print("\n" + "=" * 60)
    print("Step 2: Opening D2XX device 1 (Channel B - UART)...")
    print("=" * 60)

    num_devices = ftd2xx.createDeviceInfoList()
    print(f"Found {num_devices} FTDI device(s)")
    for i in range(num_devices):
        info = ftd2xx.getDeviceInfoDetail(i)
        print(f"  [{i}] {info.get('description', b'?')} (serial: {info.get('serial', b'?')})")

    if num_devices < 2:
        print("ERROR: Need at least 2 FTDI devices (Channel A + B)")
        sys.exit(1)

    # Open device 1 (Channel B)
    print("\nOpening device 1 (Channel B)...")
    try:
        dev = ftd2xx.open(1)
    except Exception as e:
        print(f"ERROR: Cannot open device 1: {e}")
        print("Trying device 0...")
        try:
            dev = ftd2xx.open(0)
        except Exception as e2:
            print(f"ERROR: Cannot open device 0 either: {e2}")
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
    dev.setTimeouts(500, 500)
    # DON'T purge RX — keep buffered boot messages

    print("UART configured: 115200 baud, 8N1")
    try:
        queued = dev.getQueueStatus()
        print(f"RX buffer: {queued} bytes queued")
    except:
        pass

    # Step 3: Read UART data
    print(f"\nReading UART for {duration}s...")
    received = bytearray()
    start = time.time()
    last_len = 0

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
                    last_len = len(received)
        except Exception as e:
            print(f"  read error: {e}")
        time.sleep(0.05)

    # Summary
    print("\n" + "=" * 60)
    print("RESULT")
    print("=" * 60)
    print(f"Total bytes: {len(received)}")

    if len(received) > 0:
        print("\n--- ASCII ---")
        print(received.decode('ascii', errors='replace'))
        print("\n--- Hex (first 128) ---")
        for i in range(0, min(128, len(received)), 16):
            chunk = received[i:i+16]
            hex_str = ' '.join(f'{b:02x}' for b in chunk)
            ascii_str = ''.join(chr(b) if 32 <= b < 127 else '.' for b in chunk)
            print(f"  {i:04x}: {hex_str:<48s} {ascii_str}")
    else:
        print("\nNo UART data received on Channel B")
        print("Possible causes:")
        print("  1. Channel B EEPROM not yet in UART mode (replug USB)")
        print("  2. FPGA not sending UART data")
        print("  3. Wrong baud rate")

    dev.close()


if __name__ == "__main__":
    main()
