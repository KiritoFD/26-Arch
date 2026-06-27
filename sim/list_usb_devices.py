"""List all USB devices and their driver states via libusb1."""
import usb1
import sys

context = usb1.USBContext()
print("=== USB Devices ===")
for d in context.getDeviceList():
    vid = d.getVendorID()
    pid = d.getProductID()
    bus = d.getBusNumber()
    addr = d.getDeviceAddress()
    marker = " <<< TARGET" if (vid, pid) in [(0x0403, 0x6010), (0x1443, 0x6010)] else ""
    print(f"  Bus {bus} Addr {addr}: VID=0x{vid:04x} PID=0x{pid:04x}{marker}")
    try:
        handle = d.open()
        try:
            manu = handle.getManufacturer()
        except Exception as e:
            manu = f"<err: {e}>"
        try:
            prod = handle.getProduct()
        except Exception as e:
            prod = f"<err: {e}>"
        print(f"    Manufacturer: {manu}")
        print(f"    Product:      {prod}")
        try:
            active0 = handle.kernelDriverActive(0)
            active1 = handle.kernelDriverActive(1)
            print(f"    Kernel driver active: if0={active0}, if1={active1}")
        except Exception as e:
            print(f"    Kernel driver check: {e}")
        handle.close()
    except Exception as e:
        print(f"    Open failed: {e}")
