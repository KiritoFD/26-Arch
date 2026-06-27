#!/usr/bin/env python3
"""Diagnose FTDI Channel A configuration and check for UART data.

This script:
1. Lists all COM ports (VCP mode check)
2. Opens FTDI Port A via D2XX
3. Reads and decodes the FTDI EEPROM (word 0-15)
4. Checks Channel A mode and VCP settings
5. Programs FPGA and reads UART data
"""
import sys
import time
import subprocess
import struct
import ftd2xx

VIVADO = r"C:\Xilinx\Vivado\2019.2\bin\vivado.bat"
TCL_SCRIPT = r"g:\GitHub\26-Arch\vivado\program_only.tcl"


def check_com_ports():
    """Check for available COM ports via pyserial."""
    print("=" * 60)
    print("Checking COM ports (VCP mode)...")
    print("=" * 60)
    try:
        import serial.tools.list_ports
        ports = list(serial.tools.list_ports.comports())
        if not ports:
            print("  No COM ports found (Channel A is NOT in VCP mode)")
        else:
            for p in ports:
                print(f"  COM{p.device}: {p.description} ({p.manufacturer})")
    except ImportError:
        print("  pyserial not installed, trying Windows registry...")
        try:
            import winreg
            key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE,
                r"SOFTWARE\Microsoft\Windows NT\CurrentVersion\Ports")
            i = 0
            while True:
                try:
                    name, value, _ = winreg.EnumValue(key, i)
                    if 'COM' in name or 'Serial' in name.lower():
                        print(f"  {name}: {value}")
                    i += 1
                except OSError:
                    break
        except Exception as e:
            print(f"  Registry check failed: {e}")


def read_ftdi_eeprom(dev):
    """Read FTDI EEPROM words 0-15 and decode configuration."""
    print("\n" + "=" * 60)
    print("Reading FTDI EEPROM (first 16 words)...")
    print("=" * 60)

    words = []
    for addr in range(16):
        try:
            # FT_ReadEE(handle, word_offset, &value)
            val = dev.readEE(addr)
            words.append(val)
            print(f"  Word {addr:2d}: 0x{val:04x} ({val})")
        except Exception as e:
            print(f"  Word {addr:2d}: ERROR: {e}")
            words.append(None)

    if all(w is not None for w in words):
        print("\n--- EEPROM Decode ---")
        vid = words[0]
        pid = words[1]
        print(f"  VID: 0x{vid:04x} ({'FTDI' if vid == 0x0403 else 'Xilinx' if vid == 0x1443 else 'Unknown'})")
        print(f"  PID: 0x{pid:04x}")

        word3 = words[3]
        type_a = word3 & 0xFF
        type_b = (word3 >> 8) & 0xFF
        type_names = {0: "UART", 1: "FIFO", 2: "CPUFIFO", 4: "OPTO", 7: "FIFO245"}
        print(f"  Word 3: 0x{word3:04x}")
        print(f"    Channel A: 0x{type_a:02x} = {type_names.get(type_a, 'Unknown')}")
        print(f"    Channel B: 0x{type_b:02x} = {type_names.get(type_b, 'Unknown')}")

        word5 = words[5]
        print(f"  Word 5: 0x{word5:04x}")
        # Check VCP/D2XX settings
        # Bit 0 of high byte: Channel A D2XX only (not VCP)
        # Bit 1 of high byte: Channel B D2XX only (not VCP)
        a_d2xx_only = (word5 >> 8) & 0x01
        b_d2xx_only = (word5 >> 9) & 0x01
        print(f"    Channel A D2XX only (no VCP): {a_d2xx_only}")
        print(f"    Channel B D2XX only (no VCP): {b_d2xx_only}")

        # Also check Drive bits
        drive_a = word5 & 0xFF
        drive_b = (word5 >> 8) & 0xFF
        print(f"    Drive_A: 0x{drive_a:02x}")
        print(f"    Drive_B: 0x{drive_b:02x}")

    return words


def program_fpga():
    """Reprogram FPGA via Vivado Tcl."""
    print("\n" + "=" * 60)
    print("Programming FPGA (restarts xv6)...")
    print("=" * 60)
    proc = subprocess.run(
        [VIVADO, "-mode", "batch", "-source", TCL_SCRIPT],
        capture_output=True, text=True, timeout=120
    )
    print(f"Exit code: {proc.returncode}")
    return proc.returncode == 0


def read_uart(dev, duration):
    """Read UART data for specified duration."""
    print(f"\nReading UART for {duration}s...")
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
        except Exception:
            pass
        time.sleep(0.05)

    return received


def main():
    # Step 1: Check COM ports
    check_com_ports()

    # Step 2: Open D2XX and read EEPROM
    print("\n" + "=" * 60)
    print("Opening D2XX device 0 (Port A)...")
    print("=" * 60)

    num_devices = ftd2xx.createDeviceInfoList()
    print(f"Found {num_devices} FTDI device(s)")
    for i in range(num_devices):
        info = ftd2xx.getDeviceInfoDetail(i)
        print(f"  [{i}] {info.get('description', b'?')} (serial: {info.get('serial', b'?')})")

    dev = ftd2xx.open(0)
    print(f"Opened device 0")

    # Read EEPROM
    eeprom_words = read_ftdi_eeprom(dev)

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
    dev.purge(ftd2xx.defines.PURGE_RX | ftd2xx.defines.PURGE_TX)
    print("\nUART configured: 115200 baud, 8N1, RX purged")

    dev.close()
    print("Closed D2XX device (to allow Vivado JTAG access)")

    # Step 3: Program FPGA
    program_fpga()

    # Step 4: Re-open D2XX and read UART
    print("\n" + "=" * 60)
    print("Re-opening D2XX to read UART...")
    print("=" * 60)

    dev = ftd2xx.open(0)
    dev.resetDevice()
    dev.setBaudRate(115200)
    dev.setDataCharacteristics(
        ftd2xx.defines.BITS_8,
        ftd2xx.defines.STOP_BITS_1,
        ftd2xx.defines.PARITY_NONE
    )
    dev.setFlowControl(ftd2xx.defines.FLOW_NONE, 0, 0)
    dev.setTimeouts(500, 500)
    # DON'T purge RX — keep buffered boot messages!

    # Check buffer
    try:
        queued = dev.getQueueStatus()
        print(f"FTDI RX buffer: {queued} bytes queued")
    except:
        print("Cannot check queue status")

    # Read for 10 seconds
    received = read_uart(dev, 10.0)

    # Summary
    print("\n" + "=" * 60)
    print("RESULT")
    print("=" * 60)
    print(f"Total bytes received: {len(received)}")

    if len(received) > 0:
        print("\n--- ASCII ---")
        print(received.decode('ascii', errors='replace'))
        print("\n--- Hex (first 128 bytes) ---")
        for i in range(0, min(128, len(received)), 16):
            chunk = received[i:i+16]
            hex_str = ' '.join(f'{b:02x}' for b in chunk)
            ascii_str = ''.join(chr(b) if 32 <= b < 127 else '.' for b in chunk)
            print(f"  {i:04x}: {hex_str:<48s} {ascii_str}")
    else:
        print("\nNo UART data received!")
        print("\nDiagnostic summary:")
        if eeprom_words:
            word3 = eeprom_words[3]
            type_a = word3 & 0xFF
            if type_a != 0:
                print(f"  ROOT CAUSE: Channel A is NOT in UART mode (type=0x{type_a:02x})")
                print("  FIX: Use FT_Prog to set Channel A to UART mode")
            else:
                print("  Channel A IS in UART mode")
                print("  Possible issue: hardware connection or baud rate")

    dev.close()


if __name__ == "__main__":
    main()
