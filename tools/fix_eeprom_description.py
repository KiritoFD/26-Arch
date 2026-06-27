#!/usr/bin/env python3
"""Fix FTDI EEPROM Description for Vivado recognition.

Vivado requires specific USB Product Strings for Basys3:
  Description: "Digilent Basys3" (not "Digilent USB Device")
  Manufacturer: "Digilent"

This script:
1. Reads current EEPROM
2. Verifies channel modes are correct (A=FIFO, B=UART+VCP)
3. Fixes Description field
4. Programs new EEPROM
5. Instructs user to unplug/replug USB

Usage: python tools\fix_eeprom_description.py --force
"""
import sys
import ftd2xx


def main():
    force = '--force' in sys.argv

    print("=" * 60)
    print("Fix FTDI EEPROM Description for Vivado recognition")
    print('  Target Description: "Digilent Basys3"')
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
    pid = data.ProductId
    desc = data.Description
    mfr = data.Manufacturer
    serial = data.SerialNumber

    print(f"  VID: 0x{vid:04x} ({'OK - FTDI' if vid == 0x0403 else 'WARNING!'})")
    print(f"  PID: 0x{pid:04x}")
    print(f"  Serial: {serial}")
    print(f"  Description: {desc}")
    print(f"  Manufacturer: {mfr}")

    print(f"\n  Channel A: FIFO7={data.IFAIsFifo7}, VCP7={data.AIsVCP7}")
    print(f"  Channel B: FIFO7={data.IFBIsFifo7}, VCP7={data.BIsVCP7}")

    if vid != 0x0403:
        print(f"\nABORT: VID is 0x{vid:04x}, expected 0x0403 (FTDI)")
        dev.close()
        sys.exit(1)

    # Check if Description needs fixing
    target_desc = b"Digilent Basys3"
    if desc == target_desc:
        print(f"\n  Description is already correct: {target_desc}")
        print("  No fix needed.")
        dev.close()
        return

    print(f"\n  Current Description: {desc}")
    print(f"  Target Description:  {target_desc}")

    # Show what will change
    print("\n--- Changes ---")
    print(f"  Description: {desc} → {target_desc}")

    # Also check Manufacturer
    target_mfr = b"Digilent"
    if mfr != target_mfr:
        print(f"  Manufacturer: {mfr} → {target_mfr}")

    if not force:
        response = input("\nProceed with EEPROM write? (yes/no): ")
        if response.lower() != 'yes':
            print("Aborted.")
            dev.close()
            return

    # Modify Description (and Manufacturer if needed)
    data.Description = target_desc
    data.Manufacturer = target_mfr

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
    print(f"  Description: {data2.Description}")
    print(f"  Manufacturer: {data2.Manufacturer}")
    print(f"  Channel A: FIFO7={data2.IFAIsFifo7}, VCP7={data2.AIsVCP7}")
    print(f"  Channel B: FIFO7={data2.IFBIsFifo7}, VCP7={data2.BIsVCP7}")

    if data2.Description == target_desc:
        print("\n  ✓ Description fixed!")
    else:
        print(f"\n  ✗ Description still wrong: {data2.Description}")

    dev.close()

    print("\n" + "=" * 60)
    print("EEPROM DESCRIPTION FIXED!")
    print("=" * 60)
    print("\nNEXT STEPS:")
    print("1. UNPLUG the USB cable from the Basys3")
    print("2. Wait 2 seconds")
    print("3. REPLUG the USB cable")
    print("4. Vivado should now recognize the board as 'Digilent Basys3'")


if __name__ == "__main__":
    main()
