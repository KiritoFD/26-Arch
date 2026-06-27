#!/usr/bin/env python3
"""Read ASCII output from FPGA UART via FTDI Channel B."""
import sys
import time
import ftd2xx

def main():
    duration = int(sys.argv[1]) if len(sys.argv) > 1 else 15
    print(f"=== FPGA ASCII Reader ===")
    print(f"Duration: {duration}s, Baud: 115200, 8N1")
    print(f"Listening for ASCII output...\n")

    n = ftd2xx.createDeviceInfoList()
    dev = ftd2xx.open(1)
    dev.resetDevice()
    dev.setBaudRate(115200)
    dev.setDataCharacteristics(8, 0, 0)
    dev.setFlowControl(0x0000, 0, 0)
    dev.setTimeouts(100, 100)
    dev.setLatencyTimer(2)
    dev.purge(1 | 2)

    buf = bytearray()
    t0 = time.time()
    while time.time() - t0 < duration:
        try:
            n = dev.getQueueStatus()
            if n and n > 0:
                data = dev.read(n)
                for b in data:
                    byte = b if isinstance(b, int) else ord(b)
                    buf.append(byte)
                # Print as ASCII (replace non-printable with .)
                text = ''.join(chr(b) if 32 <= b < 127 or b in (10, 13, 9) else f'[{b:02x}]' for b in buf)
                print(f"\r[{time.time()-t0:.1f}s] {text}", end='', flush=True)
                buf.clear()
            else:
                time.sleep(0.01)
        except KeyboardInterrupt:
            break
        except Exception as e:
            print(f"\n[Error: {e}]")
            time.sleep(0.5)

    dev.close()
    print(f"\n\n=== Done ===")

if __name__ == '__main__':
    main()
