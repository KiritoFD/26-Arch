#!/usr/bin/env python3
"""
Send a CR to UART then read response — used to poke the xv6 shell
after power cycle (when boot output may already be flushed).
"""
import sys
import time
import ftd2xx

def main():
    duration = int(sys.argv[1]) if len(sys.argv) > 1 else 10
    print(f"=== UART poke (send CR) + read {duration}s ===")
    n = ftd2xx.createDeviceInfoList()
    print(f"FTDI devices found: {n}")
    dev = ftd2xx.open(1)
    dev.resetDevice()
    dev.setBaudRate(115200)
    dev.setDataCharacteristics(8, 0, 0)
    dev.setFlowControl(0x0000, 0, 0)
    dev.setTimeouts(1000, 1000)
    dev.setLatencyTimer(2)
    dev.purge(1 | 2)
    print("Channel B ready. Sending CR...")
    # Send a carriage return to trigger shell prompt
    dev.write(b'\r\n')
    time.sleep(0.2)
    dev.write(b'\r\n')
    print("CR sent. Reading response...")
    sys.stdout.flush()

    t0 = time.time()
    total = 0
    while time.time() - t0 < duration:
        try:
            rxn = dev.getQueueStatus()
            if rxn and rxn > 0:
                data = dev.read(rxn)
                total += len(data)
                for b in data:
                    byte = b if isinstance(b, int) else ord(b)
                    if 32 <= byte <= 126 or byte in (10, 13):
                        sys.stdout.write(chr(byte))
                    else:
                        sys.stdout.write(f'[{byte:02x}]')
                sys.stdout.flush()
            else:
                time.sleep(0.01)
        except KeyboardInterrupt:
            print("\n[Interrupted]")
            break
        except Exception as e:
            print(f"\n[Read error: {e}]")
            time.sleep(0.5)

    print(f"\n{'='*60}")
    print(f"Total bytes: {total}")
    dev.close()

if __name__ == '__main__':
    main()
