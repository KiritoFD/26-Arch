#!/usr/bin/env python3
"""Check FTDI device state via D2XX after EEPROM reconfiguration."""
import ftd2xx

def main():
    n = ftd2xx.createDeviceInfoList()
    print(f"D2XX devices: {n}")
    for i in range(n):
        info = ftd2xx.getDeviceInfoDetail(i)
        print(f"  [{i}] desc={info.get('description', b'?')} serial={info.get('serial', b'?')}")

    if n == 0:
        print("No FTDI devices found via D2XX!")
        return

    dev = ftd2xx.open(0)
    d = dev.eeRead()
    print(f"\nEEPROM:")
    print(f"  VID=0x{d.VendorId:04x} PID=0x{d.ProductId:04x}")
    print(f"  Desc={d.Description}")
    print(f"  Mfr={d.Manufacturer}")
    print(f"  Serial={d.SerialNumber}")
    print(f"  ChA: FIFO7={d.IFAIsFifo7} VCP7={d.AIsVCP7} (should be 1, 0 for JTAG)")
    print(f"  ChB: FIFO7={d.IFBIsFifo7} VCP7={d.BIsVCP7} (should be 0, 1 for UART)")
    dev.close()

if __name__ == "__main__":
    main()
