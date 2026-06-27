#!/usr/bin/env python3
"""Capture boot output - opens FTDI first, then waits for user to press btnC."""
import sys
import time
import ftd2xx

def main():
    duration = int(sys.argv[1]) if len(sys.argv) > 1 else 30
    print(f"=== Boot Capture ===")
    print(f"Opening FTDI Channel B...")

    n = ftd2xx.createDeviceInfoList()
    dev = ftd2xx.open(1)
    dev.resetDevice()
    dev.setBaudRate(115200)
    dev.setDataCharacteristics(8, 0, 0)
    dev.setFlowControl(0x0000, 0, 0)
    dev.setTimeouts(50, 50)
    dev.setLatencyTimer(1)
    # Don't purge - we want to catch any buffered output from before
    # dev.purge(1 | 2)
    # Read any buffered data first
    n = dev.getQueueStatus()
    if n and n > 0:
        old = dev.read(n)
        print(f"Pre-existing buffer ({n} bytes): {list(old)}")
    print(f"FTDI ready. Press btnC on FPGA now to reset CPU. Capturing {duration}s...")
    print(f"(Output appears below)\n")

    all_bytes = bytearray()
    t0 = time.time()
    while time.time() - t0 < duration:
        try:
            n = dev.getQueueStatus()
            if n and n > 0:
                data = dev.read(n)
                for b in data:
                    byte = b if isinstance(b, int) else ord(b)
                    all_bytes.append(byte)
                # Print immediately
                for b in data:
                    byte = b if isinstance(b, int) else ord(b)
                    if 32 <= byte < 127 or byte in (10, 13, 9):
                        sys.stdout.write(chr(byte))
                    else:
                        sys.stdout.write(f'[{byte:02x}]')
                sys.stdout.flush()
            else:
                time.sleep(0.005)
        except KeyboardInterrupt:
            break
        except Exception as e:
            print(f"\n[Error: {e}]")
            time.sleep(0.2)

    dev.close()
    print(f"\n\n=== Done. Total bytes: {len(all_bytes)} ===")
    # Print hex dump of all data
    print(f"Hex: {' '.join(f'{b:02x}' for b in all_bytes)}")

if __name__ == '__main__':
    main()
