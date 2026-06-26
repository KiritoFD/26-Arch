#!/usr/bin/env python3
"""
Read xv6 UART output via FTDI Channel B (D2XX direct, no COM port needed).
Basys3 FT2232H: Channel A=JTAG (index 0, locked by Digilent), Channel B=UART (index 1).

Usage: python read_uart_ftd2xx.py [duration_seconds]
"""
import sys
import time
import ftd2xx

def main():
    duration = int(sys.argv[1]) if len(sys.argv) > 1 else 30
    print(f"=== FTDI D2XX UART Reader (Basys3 Channel B) ===")
    print(f"Duration: {duration}s, Baud: 115200, 8N1")

    n = ftd2xx.createDeviceInfoList()
    print(f"FTDI devices found: {n}")

    # Channel B is at index 1 (Channel A at index 0 is locked by Digilent JTAG)
    dev = ftd2xx.open(1)
    info = dev.getDeviceInfo()
    desc = info.get('description', b'?')
    if isinstance(desc, bytes):
        desc = desc.decode('ascii', errors='ignore')
    serial = info.get('serial', b'?')
    if isinstance(serial, bytes):
        serial = serial.decode('ascii', errors='ignore')
    print(f"Opened device 1: desc={desc}, serial={serial}")

    # Reset and configure UART
    # FTDI D2XX constants (raw values):
    #   Stop bits: 0=1bit, 2=2bits
    #   Parity: 0=none, 1=odd, 2=even, 3=mark, 4=space
    #   Flow: 0x0000=none, 0x0100=RTS_CTS, 0x0200=DTR_DSR, 0x0400=XON_XOFF
    #   Purge: 1=RX, 2=TX
    dev.resetDevice()
    dev.setBaudRate(115200)
    dev.setDataCharacteristics(8, 0, 0)  # 8 data, 1 stop, no parity
    dev.setFlowControl(0x0000, 0, 0)     # No flow control
    dev.setTimeouts(1000, 1000)
    dev.setLatencyTimer(2)
    dev.purge(1 | 2)                     # Purge RX + TX

    print(f"FTDI Channel B configured: 115200 baud, 8N1")
    print(f"Waiting for UART data... (Ctrl+C to stop)")
    print(f"{'='*60}")
    sys.stdout.flush()

    t0 = time.time()
    total_bytes = 0
    while time.time() - t0 < duration:
        try:
            rx_bytes = dev.getQueueStatus()
            if rx_bytes and rx_bytes > 0:
                data = dev.read(rx_bytes)
                total_bytes += len(data)
                for b in data:
                    if isinstance(b, int):
                        byte = b
                    else:
                        byte = ord(b)
                    if 32 <= byte <= 126 or byte in (10, 13):
                        sys.stdout.write(chr(byte))
                    else:
                        sys.stdout.write(f'[{byte:02x}]')
                sys.stdout.flush()
            else:
                time.sleep(0.01)
        except KeyboardInterrupt:
            print("\n[Interrupted by user]")
            break
        except Exception as e:
            print(f"\n[Read error: {e}]")
            time.sleep(0.5)

    print(f"\n{'='*60}")
    print(f"Total bytes received: {total_bytes}")
    dev.close()
    print("FTDI device closed.")

if __name__ == '__main__':
    main()
