#!/usr/bin/env python3
"""Swap FTDI FT2232H Channel A/B modes in EEPROM.

CURRENT (WRONG):
  Channel A (FPGA UART pins): FIFO mode, no VCP  → used for JTAG
  Channel B (FPGA JTAG pins): UART mode, VCP      → not used for JTAG

TARGET (CORRECT):
  Channel A (FPGA UART pins): UART mode, VCP       → COM port for serial
  Channel B (FPGA JTAG pins): FIFO mode, no VCP    → JTAG for Vivado

This script:
1. Reads current EEPROM
2. Verifies the current state matches expected (A=FIFO, B=VCP)
3. Swaps: A→UART+VCP, B→FIFO
4. Programs new EEPROM
5. Instructs user to unplug/replug USB

SAFETY:
- Only modifies channel mode fields (IFAIsFifo7, AIsVCP7, IFBIsFifo7, BIsVCP7)
- All other fields preserved
- Verifies VID=0x0403 (FTDI) before writing
- Shows before/after comparison
"""
import sys
import ftd2xx


def main():
    force = '--force' in sys.argv

    print("=" * 60)
    print("FTDI EEPROM Channel Swap")
    print("  A: FIFO  → UART + VCP (for COM port)")
    print("  B: UART+VCP → FIFO (for JTAG)")
    print("=" * 60)

    # Open device 0 (Channel A — currently in FIFO/D2XX mode)
    num = ftd2xx.createDeviceInfoList()
    print(f"\nFound {num} FTDI device(s)")
    for i in range(num):
        info = ftd2xx.getDeviceInfoDetail(i)
        print(f"  [{i}] {info.get('description', b'?')} (serial: {info.get('serial', b'?')})")

    if num == 0:
        print("ERROR: No FTDI devices found")
        sys.exit(1)

    print("\nOpening device 0 (Channel A)...")
    dev = ftd2xx.open(0)

    # Read current EEPROM
    print("\n--- Reading current EEPROM ---")
    data = dev.eeRead()

    # Verify critical fields
    vid = data.VendorId
    pid = data.ProductId
    print(f"  VID: 0x{vid:04x} ({'OK - FTDI' if vid == 0x0403 else 'WARNING!'})")
    print(f"  PID: 0x{pid:04x}")
    print(f"  Serial: {data.SerialNumber}")
    print(f"  Description: {data.Description}")

    if vid != 0x0403:
        print(f"\nABORT: VID is 0x{vid:04x}, expected 0x0403 (FTDI)")
        print("  Writing with wrong VID can brick the board!")
        dev.close()
        sys.exit(1)

    # Current channel mode
    print("\n--- Current Channel Modes ---")
    a_fifo = data.IFAIsFifo7
    a_vcp = data.AIsVCP7
    b_fifo = data.IFBIsFifo7
    b_vcp = data.BIsVCP7

    def mode_str(fifo, vcp):
        if fifo:
            return f"FIFO (FIFO7={fifo}, VCP7={vcp})"
        elif vcp:
            return f"UART+VCP (FIFO7={fifo}, VCP7={vcp})"
        else:
            return f"UART/D2XX (FIFO7={fifo}, VCP7={vcp})"

    print(f"  Channel A: {mode_str(a_fifo, a_vcp)}")
    print(f"  Channel B: {mode_str(b_fifo, b_vcp)}")

    # Verify current state matches expected (A=FIFO, B=VCP)
    if not (a_fifo == 1 and a_vcp == 0):
        print("\nWARNING: Channel A is NOT in expected FIFO mode!")
        print(f"  Expected: FIFO7=1, VCP7=0")
        print(f"  Got: FIFO7={a_fifo}, VCP7={a_vcp}")
        if not force:
            response = input("  Continue anyway? (yes/no): ")
            if response.lower() != 'yes':
                print("Aborted.")
                dev.close()
                sys.exit(1)

    # Show the swap
    print("\n--- Target Channel Modes (after swap) ---")
    print(f"  Channel A: {mode_str(0, 1)} (UART + VCP → COM port)")
    print(f"  Channel B: {mode_str(1, 0)} (FIFO → JTAG)")

    # Confirm
    print("\n" + "=" * 60)
    print("This will WRITE to the FTDI EEPROM.")
    print("After writing, you MUST unplug and replug the USB cable")
    print("for the changes to take effect.")
    print("=" * 60)
    if not force:
        response = input("\nProceed with EEPROM write? (yes/no): ")
        if response.lower() != 'yes':
            print("Aborted. No changes made.")
            dev.close()
            sys.exit(0)

    # Modify only the channel mode fields
    data.IFAIsFifo7 = 0    # Channel A: leave FIFO → UART mode
    data.AIsVCP7 = 1       # Channel A: enable VCP → COM port
    data.IFBIsFifo7 = 1    # Channel B: enter FIFO → JTAG mode
    data.BIsVCP7 = 0       # Channel B: disable VCP → D2XX only

    print("\n--- Writing EEPROM ---")
    try:
        dev.eeProgram(data)
        print("EEPROM written successfully!")
    except Exception as e:
        print(f"ERROR writing EEPROM: {e}")
        dev.close()
        sys.exit(1)

    # Verify by re-reading
    print("\n--- Verifying EEPROM ---")
    data2 = dev.eeRead()
    print(f"  Channel A: {mode_str(data2.IFAIsFifo7, data2.AIsVCP7)}")
    print(f"  Channel B: {mode_str(data2.IFBIsFifo7, data2.BIsVCP7)}")

    if data2.IFAIsFifo7 == 0 and data2.AIsVCP7 == 1 and \
       data2.IFBIsFifo7 == 1 and data2.BIsVCP7 == 0:
        print("\n  ✓ EEPROM swap verified!")
    else:
        print("\n  ✗ WARNING: Verification failed! EEPROM may be in unexpected state.")
        print("  Check with FT_Prog before unplugging.")

    dev.close()

    print("\n" + "=" * 60)
    print("EEPROM RECONFIGURATION COMPLETE!")
    print("=" * 60)
    print("\nNEXT STEPS:")
    print("1. UNPLUG the USB cable from the Basys3")
    print("2. Wait 2 seconds")
    print("3. REPLUG the USB cable")
    print("4. Wait for Windows to recognize the device and load drivers")
    print("5. Check Device Manager for a new COM port (Channel A)")
    print("6. Vivado should now use Channel B for JTAG (serial ...B)")
    print("\nAfter replug, run:")
    print("  python tools/check_com_ports.py")
    print("  to verify the COM port appears")


if __name__ == "__main__":
    main()
