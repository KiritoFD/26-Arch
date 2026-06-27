#!/usr/bin/env python3
"""Listen to Basys3 UART via FTDI D2XX (no VCP COM port needed).
Tries both FTDI channels, prints readable data."""
import sys
import time
import ftd2xx

DURATION = int(sys.argv[1]) if len(sys.argv) > 1 else 30

for ch in [0, 1]:
    try:
        dev = ftd2xx.open(ch)
        info = dev.getDeviceInfo()
        desc = info.get('description', b'?')
        if isinstance(desc, bytes):
            desc = desc.decode('ascii', errors='ignore')
        print(f"\n=== Channel {ch}: {desc} ===")

        dev.resetDevice()
        dev.setBaudRate(115200)
        dev.setDataCharacteristics(8, 0, 0)
        dev.setFlowControl(0x0000, 0, 0)
        dev.setTimeouts(10, 10)
        dev.setLatencyTimer(2)
        dev.purge(1 | 2)

        t0 = time.time()
        total = 0
        while time.time() - t0 < DURATION:
            n = dev.getQueueStatus()
            if n and n > 0:
                data = dev.read(n)
                total += len(data)
                for b in data:
                    byte = b if isinstance(b, int) else ord(b)
                    if 32 <= byte < 127 or byte in (10, 13, 9):
                        sys.stdout.write(chr(byte))
                    else:
                        sys.stdout.write(f'[{byte:02x}]')
                sys.stdout.flush()
            else:
                time.sleep(0.005)

        dev.close()
        print(f"\n--- Channel {ch} total bytes: {total} ---")
    except Exception as e:
        print(f"\nChannel {ch} failed: {e}")
