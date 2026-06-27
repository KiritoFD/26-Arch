#!/usr/bin/env python3
"""Restore FTDI EEPROM to correct Basys3 configuration.

CORRECT config (Basys3 hardware):
  Channel A (ADBUS → FPGA JTAG):  FIFO mode (FIFO7=1, VCP7=0) → Vivado JTAG
  Channel B (BDBUS → FPGA UART): UART mode (FIFO7=0, VCP7=1) → COM port

WRONG config (current, after bad swap):
  Channel A: UART+VCP (FIFO7=0, VCP7=1)  ← WRONG, A is JTAG
  Channel B: FIFO (FIFO7=1, VCP7=0)      ← WRONG, B is UART

This script restores the correct configuration.
"""
import sys
import ftd2xx


def main():
    force = '--force' in sys.argv

    print("=" * 60)
    print("FTDI EEPROM RESTORE (correct Basys3 config)")
    print("  A (JTAG pins): UART+VCP → FIFO  (for Vivado JTAG)")
    print("  B (UART pins): FIFO     → UART+VCP (for COM port)")
    print("=" * 60)

    num = ftd2xx.createDeviceInfoList()
    print(f"\nFound {num} FTDI device(s)")
    for i in range(num):
        info = ftd2xx.getDeviceInfoDetail(i)
        print(f"  [{i}] {info.get('description', b'?')} (serial: {info.get('serial', b'?')})")

    if num == 0:
        print("ERROR: No FTDI devices found")
        sys.exit(1)

    # Open device 0 (Channel A)
    print("\nOpening device 0 (Channel A)...")
    dev = ftd2xx.open(0)

    # Read current EEPROM
    print("\n--- Reading current EEPROM ---")
    data = dev.eeRead()

    vid = data.VendorId
    print(f"  VID: 0x{vid:04x} ({'OK - FTDI' if vid == 0x0403 else 'WARNING!'})")

    if vid != 0x0403:
        print(f"\nABORT: VID is 0x{vid:04x}, expected 0x0403 (FTDI)")
        dev.close()
        sys.exit(1)

    # Current channel mode
    print("\n--- Current Channel Modes (WRONG) ---")
    print(f"  Channel A: FIFO7={data.IFAIsFifo7}, VCP7={data.AIsVCP7}")
    print(f"  Channel B: FIFO7={data.IFBIsFifo7}, VCP7={data.BIsVCP7}")

    # Target: restore correct config
    print("\n--- Target Channel Modes (CORRECT) ---")
    print(f"  Channel A: FIFO7=1, VCP7=0 (FIFO → Vivado JTAG)")
    print(f"  Channel B: FIFO7=0, VCP7=1 (UART+VCP → COM port)")

    if not force:
        response = input("\nProceed with EEPROM restore? (yes/no): ")
        if response.lower() != 'yes':
            print("Aborted.")
            dev.close()
            sys.exit(0)

    # Restore correct config
    data.IFAIsFifo7 = 1    # Channel A: FIFO → JTAG
    data.AIsVCP7 = 0       # Channel A: no VCP
    data.IFBIsFifo7 = 0    # Channel B: UART → COM port
    data.BIsVCP7 = 1       # Channel B: VCP enabled

    print("\n--- Writing EEPROM ---")
    try:
        dev.eeProgram(data)
        print("EEPROM written successfully!")
    except Exception as e:
        print(f"ERROR writing EEPROM: {e}")
        dev.close()
        sys.exit(1)

    # Verify
    print("\n--- Verifying EEPROM ---")
    data2 = dev.eeRead()
    print(f"  Channel A: FIFO7={data2.IFAIsFifo7}, VCP7={data2.AIsVCP7} "
          f"→ {'FIFO ✓' if data2.IFAIsFifo7 == 1 and data2.AIsVCP7 == 0 else 'WRONG'}")
    print(f"  Channel B: FIFO7={data2.IFBIsFifo7}, VCP7={data2.BIsVCP7} "
          f"→ {'UART+VCP ✓' if data2.IFBIsFifo7 == 0 and data2.BIsVCP7 == 1 else 'WRONG'}")

    dev.close()

    print("\n" + "=" * 60)
    print("EEPROM RESTORED to correct Basys3 configuration!")
    print("=" * 60)
    print("\nNEXT STEPS:")
    print("1. UNPLUG the USB cable from the Basys3")
    print("2. Wait 2 seconds")
    print("3. REPLUG the USB cable")
    print("4. Vivado JTAG should work again (Channel A = FIFO)")
    print("5. UART data will be on Channel B (read device 1 via D2XX)")


if __name__ == "__main__":
    main()
