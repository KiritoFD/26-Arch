"""Fix FT2232H EEPROM via libusb1 (usb1 module), bypassing FTDI D2XX driver.

Uses usb1 module which bundles its own libusb-1.0.dll.
"""
import usb1
import struct
import sys
import time

# Load original (Vivado OK) EEPROM as reference for string area
orig_path = 'sim/eeprom_backups/eeprom_backup_20260627_072124.bin'
with open(orig_path, 'rb') as f:
    orig_data = f.read()
orig_words = list(struct.unpack('<' + 'H'*(len(orig_data)//2), orig_data))


def calc_checksum(words_256):
    cs = 0
    for w in words_256[:255]:
        cs ^= w
    return cs


def main():
    print("=== Finding FT2232H device via libusb1 ===")
    context = usb1.USBContext()
    if not context:
        print("ERROR: Could not create USB context")
        sys.exit(1)

    combos = [
        (0x0403, 0x6010),  # Original FTDI
        (0x1443, 0x6010),  # Xilinx (current broken)
    ]

    dev = None
    found_vid = found_pid = None
    for vid, pid in combos:
        for d in context.getDeviceList():
            if d.getVendorID() == vid and d.getProductID() == pid:
                dev = d
                found_vid = vid
                found_pid = pid
                break
        if dev:
            break

    if dev is None:
        print("ERROR: Could not find FT2232H device!")
        print("Try: unplug USB, wait 3s, replug, run again")
        sys.exit(1)

    print(f"  FOUND! VID=0x{found_vid:04x} PID=0x{found_pid:04x}")

    # Open device
    handle = dev.open()

    # Get strings
    try:
        manufacturer = handle.getManufacturer()
        print(f"  Manufacturer: {manufacturer}")
    except Exception as e:
        print(f"  Manufacturer: <error: {e}>")
    try:
        product = handle.getProduct()
        print(f"  Product: {product}")
    except Exception as e:
        print(f"  Product: <error: {e}>")
    try:
        serial = handle.getSerial()
        print(f"  Serial: {serial}")
    except Exception as e:
        print(f"  Serial: <error: {e}>")

    # Detach kernel driver if active
    try:
        if handle.kernelDriverActive(0):
            print("  Detaching kernel driver from interface 0")
            handle.detachKernelDriver(0)
    except Exception as e:
        print(f"  (kernel driver check: {e})")

    # Claim interface 0
    try:
        handle.claimInterface(0)
        print("  Interface 0 claimed")
    except Exception as e:
        print(f"  Claim interface 0 failed: {e}")
        try:
            handle.claimInterface(1)
            print("  Interface 1 claimed instead")
        except Exception as e2:
            print(f"  Claim interface 1 also failed: {e2}")

    # Read current EEPROM (256 words)
    print("\n=== Reading current EEPROM (256 words) ===")
    words = []
    for i in range(256):
        try:
            # bmRequestType=0xC0 (IN, vendor, device), bRequest=0x90 (read EEPROM), wIndex=addr, wLength=2
            data = handle.controlRead(0xC0, 0x90, 0x0000, i, 2)
            w = struct.unpack('<H', bytes(data))[0]
            words.append(w)
        except Exception as e:
            print(f"  Read failed at word {i}: {e}")
            sys.exit(1)

    print(f"  Read {len(words)} words OK")

    # Show current config
    print(f"\n  Word 0 (PID): 0x{words[0]:04x} (should be 0x6010)")
    print(f"  Word 1 (VID): 0x{words[1]:04x} (should be 0x0403)")
    print(f"  Word 2 (release): 0x{words[2]:04x}")
    print(f"  Word 3 (config): 0x{words[3]:04x}")
    print(f"  Word 5 (config2): 0x{words[5]:04x}")
    print(f"  Word 127 (chksum): 0x{words[127]:04x}")
    print(f"  Word 255 (chksum): 0x{words[255]:04x}")

    # Show string area
    print(f"\n  String area (word 14-39):")
    for i in range(14, 40):
        if words[i] != 0 or orig_words[i] != 0:
            marker = " *** NEEDS FIX" if words[i] != orig_words[i] else ""
            print(f"    word {i}: current=0x{words[i]:04x} orig=0x{orig_words[i]:04x}{marker}")

    # Determine what to patch
    changes = []

    # 1. Fix VID (word 1)
    if words[1] != 0x0403:
        changes.append((1, words[1], 0x0403, "VID"))
    # 2. Fix PID (word 0) - in case it's wrong
    if words[0] != 0x6010:
        changes.append((0, words[0], 0x6010, "PID"))

    # 3. Copy string area (word 14-39) from original backup
    for i in range(14, 40):
        if words[i] != orig_words[i]:
            changes.append((i, words[i], orig_words[i], "string"))

    if not changes:
        print("\n  No changes needed - EEPROM already matches!")
        handle.releaseInterface(0)
        sys.exit(0)

    print(f"\n=== {len(changes)} words to change ===")
    for i, old, new, label in changes:
        print(f"  Word {i:3d}: 0x{old:04x} -> 0x{new:04x}  ({label})")

    # Apply changes
    for i, old, new, label in changes:
        words[i] = new

    # Recalculate checksums
    cs_127 = 0
    for w in words[:127]:
        cs_127 ^= w
    cs_255 = 0
    for w in words[:255]:
        cs_255 ^= w

    print(f"\n  New checksum word 127: 0x{words[127]:04x} -> 0x{cs_127:04x}")
    print(f"  New checksum word 255: 0x{words[255]:04x} -> 0x{cs_255:04x}")

    if words[127] != cs_127:
        changes.append((127, words[127], cs_127, "checksum127"))
    if words[255] != cs_255:
        changes.append((255, words[255], cs_255, "checksum255"))

    # Confirm
    if '--yes' not in sys.argv:
        resp = input(f"\nWrite {len(changes)} words? Type YES: ")
        if resp != 'YES':
            print("Aborted")
            handle.releaseInterface(0)
            sys.exit(0)
    else:
        print("\nAuto-confirmed via --yes")

    # Write
    print(f"\n=== Writing {len(changes)} words ===")
    for i, old, new, label in changes:
        try:
            # bmRequestType=0x40 (OUT, vendor, device), bRequest=0x91 (write EEPROM)
            # wValue = value, wIndex = addr
            handle.controlWrite(0x40, 0x91, new, i, b'')
            print(f"  Word {i:3d}: 0x{new:04x} OK ({label})")
            time.sleep(0.05)
        except Exception as e:
            print(f"  FAILED word {i}: {e}")
            sys.exit(1)

    # Verify
    print("\n=== Verifying ===")
    all_ok = True
    for i, old, new, label in changes:
        data = handle.controlRead(0xC0, 0x90, 0x0000, i, 2)
        readback = struct.unpack('<H', bytes(data))[0]
        if readback != new:
            print(f"  MISMATCH word {i}: expected 0x{new:04x} got 0x{readback:04x}")
            all_ok = False
        else:
            print(f"  Word {i:3d}: 0x{readback:04x} OK ({label})")

    try:
        handle.releaseInterface(0)
    except:
        pass

    if all_ok:
        print("\n=== SUCCESS! All words written and verified ===")
        print("Next: unplug USB, wait 3s, replug")
        print("The device should re-enumerate with VID=0x0403, and Vivado should detect it")
    else:
        print("\n=== Some verification failed ===")
        print("Try unplugging and replugging USB")


if __name__ == '__main__':
    main()
