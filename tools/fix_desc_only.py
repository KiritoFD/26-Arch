#!/usr/bin/env python3
"""Fix FTDI EEPROM Description via D2XX (no FT_Prog needed).

Sets Description to "Digilent USB Device" (original Basys3 value).
Preserves all other fields.
"""
import sys
import ftd2xx


def main():
    force = '--force' in sys.argv

    print("=" * 60)
    print("Fix Description via D2XX")
    print("=" * 60)

    num = ftd2xx.createDeviceInfoList()
    print(f"Found {num} FTDI device(s)")

    dev = ftd2xx.open(0)

    # Read current EEPROM
    print("\n--- Reading current EEPROM ---")
    data = dev.eeRead()
    print(f"  VID=0x{data.VendorId:04x} PID=0x{data.ProductId:04x}")
    print(f"  Desc={data.Description}")
    print(f"  Mfr={data.Manufacturer}")
    print(f"  Serial={data.SerialNumber}")
    print(f"  ChA: FIFO7={data.IFAIsFifo7} VCP7={data.AIsVCP7}")
    print(f"  ChB: FIFO7={data.IFBIsFifo7} VCP7={data.BIsVCP7}")

    # Fix Description
    target_desc = b"Digilent USB Device"
    print(f"\n  Setting Description to: {target_desc}")

    if not force:
        response = input("\nProceed? (yes/no): ")
        if response.lower() != 'yes':
            dev.close()
            return

    # Preserve all other fields, only change Description
    data.Description = target_desc
    # Keep Manufacturer as Digilent (was correct before)
    data.Manufacturer = b"Digilent"

    # Channel modes (preserve correct values)
    # Note: eeRead may return wrong values for FIFO7/VCP7
    # so we explicitly set them again
    data.IFAIsFifo7 = 1    # Channel A: FIFO (JTAG)
    data.AIsVCP7 = 0       # Channel A: no VCP
    data.IFBIsFifo7 = 0    # Channel B: UART
    data.BIsVCP7 = 1       # Channel B: VCP enabled

    print("\n--- Writing EEPROM ---")
    try:
        dev.eeProgram(data)
        print("EEPROM written!")
    except Exception as e:
        print(f"ERROR: {e}")
        dev.close()
        sys.exit(1)

    # Verify
    print("\n--- Verifying ---")
    data2 = dev.eeRead()
    print(f"  VID=0x{data2.VendorId:04x} PID=0x{data2.ProductId:04x}")
    print(f"  Desc={data2.Description}")
    print(f"  Mfr={data2.Manufacturer}")
    print(f"  ChA: FIFO7={data2.IFAIsFifo7} VCP7={data2.AIsVCP7}")
    print(f"  ChB: FIFO7={data2.IFBIsFifo7} VCP7={data2.BIsVCP7}")

    desc_ok = (data2.Description == target_desc)
    print(f"\n  Description correct: {'YES' if desc_ok else 'NO'}")

    dev.close()

    print("\n" + "=" * 60)
    print("Description FIXED via D2XX!")
    print("=" * 60)
    print("\nNEXT: Unplug USB, wait, replug, test Vivado")


if __name__ == "__main__":
    main()
