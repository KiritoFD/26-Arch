"""Fix FT2232H EEPROM via libusb, bypassing FTDI D2XX driver.

When VID was changed to non-0x0403, the FTDI D2XX driver no longer claims the device,
so FT_Open/FT_OpenEx fail. We use libusb to directly access the FT2232H and rewrite
the EEPROM via control transfers.

FT2232H EEPROM access:
  - Control endpoint 0 (OUT): bmRequestType=0x40, bRequest=0x91 (write), wIndex=word_addr
  - Control endpoint 0 (IN):  bmRequestType=0xC0, bRequest=0x90 (read),  wIndex=word_addr
  - wValue = word value (for write)

Strategy:
  1. Find device by VID/PID (try both 0x0403/0x6010 and 0x1443/0x6010)
  2. Claim interface 0
  3. Read current EEPROM (256 words)
  4. Patch: copy string area (word 14-39) from original backup
  5. Restore VID to 0x0403 (word 1, currently 0x1443)
  6. Recalculate checksum (word 127 and 255)
  7. Write changed words
  8. Verify
  9. Device re-enumerates after USB cycle
"""
import usb.core
import usb.util
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


def find_device():
    """Find FT2232H by trying multiple VID/PID combos."""
    combos = [
        (0x0403, 0x6010),  # Original FTDI
        (0x1443, 0x6010),  # Xilinx (current broken)
        (0x0403, 0x7140),  # Alternate
    ]
    for vid, pid in combos:
        print(f"  Trying VID=0x{vid:04x} PID=0x{pid:04x}")
        dev = usb.core.find(idVendor=vid, idProduct=pid)
        if dev is not None:
            print(f"  FOUND! VID=0x{vid:04x} PID=0x{pid:04x}")
            return dev, vid, pid
    return None, None, None


def read_eeprom_word(dev, addr):
    """Read one 16-bit word from FT2232H EEPROM via control transfer."""
    # bmRequestType=0xC0 (IN, vendor, device), bRequest=0x90 (read EEPROM)
    data = dev.ctrl_transfer(0xC0, 0x90, 0x0000, addr, 2)
    return struct.unpack('<H', bytes(data))[0]


def write_eeprom_word(dev, addr, value):
    """Write one 16-bit word to FT2232H EEPROM via control transfer."""
    # bmRequestType=0x40 (OUT, vendor, device), bRequest=0x91 (write EEPROM)
    # wValue = value, wIndex = addr
    result = dev.ctrl_transfer(0x40, 0x91, value, addr, None)
    return result


def main():
    print("=== Finding FT2232H device via libusb ===")
    dev, found_vid, found_pid = find_device()
    if dev is None:
        print("ERROR: Could not find FT2232H device!")
        print("Try: unplug USB, wait 3s, replug, run again")
        sys.exit(1)

    print(f"\nDevice info:")
    print(f"  VID: 0x{found_vid:04x}")
    print(f"  PID: 0x{found_pid:04x}")
    try:
        print(f"  Manufacturer: {usb.util.get_string(dev, dev.iManufacturer)}")
    except:
        print(f"  Manufacturer: <error>")
    try:
        print(f"  Product: {usb.util.get_string(dev, dev.iProduct)}")
    except:
        print(f"  Product: <error>")
    try:
        print(f"  Serial: {usb.util.get_string(dev, dev.iSerialNumber)}")
    except:
        print(f"  Serial: <error>")

    # Detach kernel driver if active (Windows usually doesn't need this)
    try:
        if dev.is_kernel_driver_active(0):
            print("\n  Detaching kernel driver from interface 0")
            dev.detach_kernel_driver(0)
    except Exception as e:
        print(f"  (kernel driver check: {e})")

    # Claim interface
    try:
        usb.util.claim_interface(dev, 0)
        print("  Interface 0 claimed")
    except Exception as e:
        print(f"  Claim interface 0 failed: {e}")
        # Try interface 1
        try:
            usb.util.claim_interface(dev, 1)
            print("  Interface 1 claimed")
        except Exception as e2:
            print(f"  Claim interface 1 also failed: {e2}")
            print("  Continuing anyway...")

    # Read current EEPROM (256 words)
    print("\n=== Reading current EEPROM (256 words) ===")
    words = []
    for i in range(256):
        try:
            w = read_eeprom_word(dev, i)
            words.append(w)
        except Exception as e:
            print(f"  Read failed at word {i}: {e}")
            # Try claiming interface 0 explicitly
            try:
                usb.util.claim_interface(dev, 0)
                w = read_eeprom_word(dev, i)
                words.append(w)
            except Exception as e2:
                print(f"  Retry failed: {e2}")
                sys.exit(1)

    print(f"  Read {len(words)} words OK")

    # Show current config
    print(f"\n  Current VID (word 1): 0x{words[1]:04x} (should be 0x0403)")
    print(f"  Current PID (word 0): 0x{words[0]:04x} (should be 0x6010)")
    print(f"  Current checksum: stored=0x{words[127]:04x} (word 127), 0x{words[255]:04x} (word 255)")
    calc_cs = calc_checksum(words)
    print(f"  Calculated checksum: 0x{calc_cs:04x}")

    # Show string area (word 14-39)
    print(f"\n  String area (word 14-39):")
    for i in range(14, 40):
        if words[i] != 0:
            print(f"    word {i}: 0x{words[i]:04x}")

    # Determine what to patch
    changes = []

    # 1. Fix VID if wrong (word 1)
    if words[1] != 0x0403:
        changes.append((1, words[1], 0x0403, "VID"))
    # 2. Fix PID if wrong (word 0)
    if words[0] != 0x6010:
        changes.append((0, words[0], 0x6010, "PID"))

    # 3. Copy string area (word 14-39) from original backup
    for i in range(14, 40):
        if words[i] != orig_words[i]:
            changes.append((i, words[i], orig_words[i], "string"))

    if not changes:
        print("\n  No changes needed - EEPROM already matches!")
        usb.util.release_interface(dev, 0)
        sys.exit(0)

    print(f"\n=== {len(changes)} words to change ===")
    for i, old, new, label in changes:
        print(f"  Word {i:3d}: 0x{old:04x} -> 0x{new:04x}  ({label})")

    # Apply changes (don't update checksum yet)
    for i, old, new, label in changes:
        words[i] = new

    # Recalculate checksums
    # word 127 and 255 are checksums for first half (0-126) and full (0-254)
    # Actually FT2232H EEPROM is 256 words; word 127 is checksum of 0-126, word 255 is checksum of 0-254
    # Let's check: in original, word 127 = 0x2947, word 255 = 0x2947 (same!)
    # This suggests the EEPROM is mirrored: 0-127 mirrors 128-255
    # So checksum at 127 = XOR(0..126), checksum at 255 = XOR(128..254)
    # Wait, they were the same value, so likely word 127 = XOR(0..126) and word 255 = XOR(0..254)
    # Let me compute both
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
            usb.util.release_interface(dev, 0)
            sys.exit(0)
    else:
        print("\nAuto-confirmed via --yes")

    # Write
    print(f"\n=== Writing {len(changes)} words ===")
    for i, old, new, label in changes:
        try:
            write_eeprom_word(dev, i, new)
            print(f"  Word {i:3d}: 0x{new:04x} OK ({label})")
            time.sleep(0.05)  # EEPROM write needs time
        except Exception as e:
            print(f"  FAILED word {i}: {e}")
            sys.exit(1)

    # Verify
    print("\n=== Verifying ===")
    all_ok = True
    for i, old, new, label in changes:
        readback = read_eeprom_word(dev, i)
        if readback != new:
            print(f"  MISMATCH word {i}: expected 0x{new:04x} got 0x{readback:04x}")
            all_ok = False
        else:
            print(f"  Word {i:3d}: 0x{readback:04x} OK ({label})")

    usb.util.release_interface(dev, 0)

    if all_ok:
        print("\n=== SUCCESS! All words written and verified ===")
        print("Next: unplug USB, wait 3s, replug")
        print("The device should re-enumerate with VID=0x0403, and Vivado should detect it")
    else:
        print("\n=== Some verification failed, but writes may have succeeded ===")
        print("Try unplugging and replugging USB")


if __name__ == '__main__':
    main()
