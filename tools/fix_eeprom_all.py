#!/usr/bin/env python3
"""Fix FTDI EEPROM: set correct channel modes AND Description.

This script fixes all fields in one operation:
  Channel A: FIFO7=1, VCP7=0 (FIFO → Vivado JTAG)
  Channel B: FIFO7=0, VCP7=1 (UART+VCP → COM port)
  Description: "Digilent Basys3"
  Manufacturer: "Digilent"
  VID: 0x0403, PID: 0x6010

IMPORTANT: eeRead/eeProgram in ftd2xx Python library may not reliably
read/write all fields. This script explicitly sets all required fields.
"""
import sys
import ftd2xx


def main():
    force = '--force' in sys.argv

    print("=" * 60)
    print("Fix FTDI EEPROM: Channel Modes + Description")
    print("=" * 60)

    num = ftd2xx.createDeviceInfoList()
    print(f"\nFound {num} FTDI device(s)")

    dev = ftd2xx.open(0)

    # Read current EEPROM
    print("\n--- Reading current EEPROM ---")
    data = dev.eeRead()

    print(f"  VID: 0x{data.VendorId:04x}")
    print(f"  PID: 0x{data.ProductId:04x}")
    print(f"  Serial: {data.SerialNumber}")
    print(f"  Description: {data.Description}")
    print(f"  Manufacturer: {data.Manufacturer}")
    print(f"  Channel A: FIFO7={data.IFAIsFifo7}, VCP7={data.AIsVCP7}")
    print(f"  Channel B: FIFO7={data.IFBIsFifo7}, VCP7={data.BIsVCP7}")

    # Target values
    print("\n--- Target values ---")
    print("  Channel A: FIFO7=1, VCP7=0 (FIFO → Vivado JTAG)")
    print("  Channel B: FIFO7=0, VCP7=1 (UART+VCP → COM port)")
    print('  Description: "Digilent Basys3"')
    print('  Manufacturer: "Digilent"')

    if not force:
        response = input("\nProceed? (yes/no): ")
        if response.lower() != 'yes':
            dev.close()
            return

    # Set ALL required fields explicitly
    # VID/PID
    data.VendorId = 0x0403   # FTDI
    data.ProductId = 0x6010  # FT2232H

    # Description and Manufacturer (for Vivado recognition)
    data.Description = b"Digilent Basys3"
    data.Manufacturer = b"Digilent"

    # Serial number (preserve existing)
    # data.SerialNumber = b"210183A8A984"  # already read

    # Channel A: FIFO mode (for Vivado JTAG)
    data.IFAIsFifo7 = 1     # Channel A: FIFO245 mode
    data.AIsVCP7 = 0        # Channel A: no VCP (D2XX only)

    # Channel B: UART mode (for COM port)
    data.IFBIsFifo7 = 0     # Channel B: UART mode
    data.BIsVCP7 = 1        # Channel B: VCP enabled

    # Also set non-7 versions for compatibility
    data.IFAIsFifo = 0      # Channel A: not FIFO (legacy)
    data.IFAIsFastSer = 0   # Channel A: not fast serial
    data.IFAIsFastSer7 = 0  # Channel A: not fast serial (7)
    data.IFBIsFifo = 0      # Channel B: not FIFO (legacy)
    data.IFBIsFastSer = 0   # Channel B: not fast serial
    data.IFBIsFastSer7 = 0  # Channel B: not fast serial (7)

    # Serial number enable
    data.SerNumEnable = 1
    data.SerNumEnable7 = 1

    print("\n--- Writing EEPROM ---")
    try:
        dev.eeProgram(data)
        print("EEPROM written successfully!")
    except Exception as e:
        print(f"ERROR: {e}")
        dev.close()
        sys.exit(1)

    # Verify
    print("\n--- Verifying ---")
    data2 = dev.eeRead()
    print(f"  VID: 0x{data2.VendorId:04x}")
    print(f"  PID: 0x{data2.ProductId:04x}")
    print(f"  Description: {data2.Description}")
    print(f"  Manufacturer: {data2.Manufacturer}")
    print(f"  Channel A: FIFO7={data2.IFAIsFifo7}, VCP7={data2.AIsVCP7}")
    print(f"  Channel B: FIFO7={data2.IFBIsFifo7}, VCP7={data2.BIsVCP7}")

    a_ok = (data2.IFAIsFifo7 == 1 and data2.AIsVCP7 == 0)
    b_ok = (data2.IFBIsFifo7 == 0 and data2.BIsVCP7 == 1)
    desc_ok = (data2.Description == b"Digilent Basys3")

    print(f"\n  Channel A (FIFO/JTAG): {'✓' if a_ok else '✗'}")
    print(f"  Channel B (UART+VCP):  {'✓' if b_ok else '✗'}")
    print(f"  Description:           {'✓' if desc_ok else '✗'}")

    dev.close()

    print("\n" + "=" * 60)
    print("EEPROM FIX COMPLETE!")
    print("=" * 60)
    print("\nNEXT STEPS:")
    print("1. UNPLUG USB cable")
    print("2. Wait 2 seconds")
    print("3. REPLUG USB cable")
    print("4. Test Vivado JTAG connection")


if __name__ == "__main__":
    main()
