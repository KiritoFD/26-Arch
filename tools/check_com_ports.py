#!/usr/bin/env python3
"""Check FTDI devices and COM ports after EEPROM reconfiguration.

After unplugging and replugging USB:
1. Verify D2XX devices are present (Channel B should be FIFO/D2XX)
2. Check for COM ports (Channel A should now have VCP/COM port)
3. If COM port found, test UART reading

Usage: python tools/check_com_ports.py
"""
import sys
import time

def check_d2xx():
    """Check D2XX devices."""
    print("=" * 60)
    print("D2XX Devices:")
    print("=" * 60)
    try:
        import ftd2xx
        num = ftd2xx.createDeviceInfoList()
        print(f"  Found {num} D2XX device(s):")
        for i in range(num):
            info = ftd2xx.getDeviceInfoDetail(i)
            desc = info.get('description', b'?')
            serial = info.get('serial', b'?')
            print(f"    [{i}] {desc} (serial: {serial})")

        if num > 0:
            print("\n  EEPROM verification:")
            dev = ftd2xx.open(0)
            data = dev.eeRead()
            print(f"    Channel A: FIFO7={data.IFAIsFifo7}, VCP7={data.AIsVCP7} "
                  f"→ {'UART+VCP ✓' if data.IFAIsFifo7 == 0 and data.AIsVCP7 == 1 else 'UNEXPECTED'}")
            print(f"    Channel B: FIFO7={data.IFBIsFifo7}, VCP7={data.BIsVCP7} "
                  f"→ {'FIFO ✓' if data.IFBIsFifo7 == 1 and data.BIsVCP7 == 0 else 'UNEXPECTED'}")
            dev.close()
        return num
    except Exception as e:
        print(f"  D2XX error: {e}")
        return 0


def check_com_ports():
    """Check for COM ports via pyserial."""
    print("\n" + "=" * 60)
    print("COM Ports (VCP):")
    print("=" * 60)
    try:
        import serial.tools.list_ports
        ports = list(serial.tools.list_ports.comports())
        ftdi_ports = [p for p in ports if 'ftdi' in (p.manufacturer or '').lower()
                      or 'ftdi' in (p.description or '').lower()
                      or 'digilent' in (p.manufacturer or '').lower()
                      or 'digilent' in (p.description or '').lower()
                      or 'usb serial' in (p.description or '').lower()]

        if not ftdi_ports:
            print("  No FTDI COM ports found")
            print("  (Only non-FTDI ports may be present)")
            all_ports = [p for p in ports if 'bluetooth' not in (p.description or '').lower()]
            for p in all_ports:
                print(f"    {p.device}: {p.description} ({p.manufacturer})")
            return []

        print(f"  Found {len(ftdi_ports)} FTDI COM port(s):")
        for p in ftdi_ports:
            print(f"    {p.device}: {p.description}")
            print(f"      Manufacturer: {p.manufacturer}")
            print(f"      Serial: {p.serial_number}")
            print(f"      VID:PID: {p.vid:#06x}:{p.pid:#06x}")
        return ftdi_ports
    except ImportError:
        print("  pyserial not installed, trying registry...")
        return []


def test_uart(com_port):
    """Test UART reading on the given COM port."""
    print("\n" + "=" * 60)
    print(f"Testing UART on {com_port}...")
    print("=" * 60)
    try:
        import serial
        ser = serial.Serial(com_port, 115200, timeout=1)
        print(f"  Opened {com_port} at 115200 baud")
        print(f"  Reading for 5 seconds (press btnC on Basys3 to reset xv6)...")

        data = bytearray()
        start = time.time()
        while (time.time() - start) < 5:
            chunk = ser.read(64)
            if chunk:
                data.extend(chunk)
                text = chunk.decode('ascii', errors='replace')
                print(f"  [{time.time()-start:.1f}s] +{len(chunk)} bytes: {repr(text[:80])}")

        ser.close()
        print(f"\n  Total: {len(data)} bytes")
        if len(data) > 0:
            print("  --- Full data ---")
            print(data.decode('ascii', errors='replace'))
        return len(data) > 0
    except Exception as e:
        print(f"  Error: {e}")
        return False


def main():
    num_d2xx = check_d2xx()
    com_ports = check_com_ports()

    if com_ports:
        port = com_ports[0].device
        print(f"\n  Will test UART on {port}")
        response = input("  Test UART now? (yes/no): ")
        if response.lower() == 'yes':
            test_uart(port)
    else:
        print("\n" + "=" * 60)
        print("No FTDI COM port found!")
        print("=" * 60)
        if num_d2xx > 0:
            print("D2XX devices are present but no COM port.")
            print("The VCP driver may not be loaded.")
            print("\nTo fix:")
            print("  1. Open Device Manager")
            print("  2. Find 'USB Serial Converter A' (under Universal Serial Bus controllers)")
            print("  3. Right-click → Update Driver → Browse → Let me pick")
            print("  4. Select 'USB Serial Port' (VCP driver)")
            print("  5. Replug USB")
        else:
            print("No FTDI devices detected at all!")
            print("Try replugging the USB cable.")


if __name__ == "__main__":
    main()
