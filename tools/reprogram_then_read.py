#!/usr/bin/env python3
"""Reprogram FPGA, then immediately read UART via D2XX.

Sequence:
1. Program FPGA via Vivado Tcl (xv6 restarts, sends boot messages)
2. Close Vivado (releases JTAG)
3. Open D2XX device 0 (Port A)
4. Check FTDI RX buffer for buffered boot messages
5. Read for specified duration (in case xv6 is in a boot loop)

Usage: python reprogram_then_read.py [duration_sec]
"""
import sys
import time
import subprocess
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
        # Print last 1000 chars of stdout for debugging
        print(f"[Vivado] STDOUT (last 1000 chars):")
        print(proc.stdout[-1000:])
        print(f"[Vivado] STDERR (last 500 chars):")
        print(proc.stderr[-500:])
    return proc.returncode == 0


def main():
    duration = float(sys.argv[1]) if len(sys.argv) > 1 else 10.0

    # Step 1: Program FPGA (xv6 restarts)
    print("=" * 60)
    print("Step 1: Programming FPGA (xv6 will restart)...")
    print("=" * 60)
    ok = program_fpga()
    if not ok:
        print("WARNING: FPGA programming failed — trying to read anyway")

    # Step 2: Immediately open D2XX and read
    print("\n" + "=" * 60)
    print("Step 2: Opening D2XX device (Port A)...")
    print("=" * 60)

    num_devices = ftd2xx.createDeviceInfoList()
    print(f"Found {num_devices} FTDI device(s)")
    for i in range(num_devices):
        info = ftd2xx.getDeviceInfoDetail(i)
        print(f"  [{i}] {info.get('description', b'?')}")

    if num_devices == 0:
        print("ERROR: No FTDI devices found")
        sys.exit(1)

    # Open Port A (device 0)
    print("\nOpening device 0 (Port A)...")
    dev = ftd2xx.open(0)

    # Reset and configure UART
    dev.resetDevice()
    dev.setBaudRate(115200)
    dev.setDataCharacteristics(
        ftd2xx.defines.BITS_8,
        ftd2xx.defines.STOP_BITS_1,
        ftd2xx.defines.PARITY_NONE
    )
    dev.setFlowControl(ftd2xx.defines.FLOW_NONE, 0, 0)
    dev.setTimeouts(500, 500)
    # DO NOT purge RX buffer — we want to read buffered boot messages!

    print("UART configured: 115200 baud, 8N1")
    print("RX buffer NOT purged (to preserve boot messages)")

    # Check FTDI RX buffer for buffered data
    try:
        queued = dev.getQueueStatus()
        print(f"FTDI RX buffer: {queued} bytes queued")
    except Exception as e:
        print(f"getQueueStatus error: {e}")
        queued = 0

    # Step 3: Read UART data
    print("\n" + "=" * 60)
    print(f"Step 3: Reading UART for {duration} seconds...")
    print("=" * 60)

    received_data = bytearray()
    start = time.time()
    last_len = 0

    while (time.time() - start) < duration:
        try:
            rx_bytes = dev.getQueueStatus()
        except Exception:
            rx_bytes = 0

        if rx_bytes > 0:
            data = dev.read(rx_bytes)
            if data:
                received_data.extend(data)
                current_len = len(received_data)
                if current_len > last_len:
                    elapsed = time.time() - start
                    new_data = received_data[last_len:]
                    text = new_data.decode('ascii', errors='replace')
                    print(f"[{elapsed:.1f}s] +{len(new_data)} bytes: {repr(text[:80])}")
                    last_len = current_len
        else:
            time.sleep(0.05)
            elapsed = time.time() - start
            if int(elapsed * 2) % 2 == 0:
                print(f"[{elapsed:.1f}s] waiting... ({len(received_data)} bytes total)")

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

        # Hex dump for first 128 bytes
        print("\n--- Hex dump (first 128 bytes) ---")
        for i in range(0, min(128, len(received_data)), 16):
            chunk = received_data[i:i+16]
            hex_str = ' '.join(f'{b:02x}' for b in chunk)
            ascii_str = ''.join(chr(b) if 32 <= b < 127 else '.' for b in chunk)
            print(f"  {i:04x}: {hex_str:<48s} {ascii_str}")
    else:
        print("\nWARNING: No UART data received!")
        print("Diagnostic checklist:")
        print("  1. Is FTDI Channel A in UART mode? (EEPROM word 3 low byte = 0x00)")
        print("  2. Is FPGA RsTx (pin A18) connected to FTDI ADBUS1 (RXD)?")
        print("  3. Is cpu_clk running? (check LED blink)")
        print("  4. Did xv6 actually write to UART? (ILA shows dbg_ever_thr_write=1)")
        print("  5. Is baud rate correct? (FPGA ~115207, D2XX 115200)")

    dev.close()


if __name__ == "__main__":
    main()
