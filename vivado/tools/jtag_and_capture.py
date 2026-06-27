#!/usr/bin/env python3
"""Open FTDI first, then JTAG program FPGA, capture all boot output."""
import sys
import time
import threading
import ftd2xx
import subprocess

def ftdi_listener(dev, stop_event, output_list):
    """Background thread that continuously reads from FTDI."""
    buf = bytearray()
    while not stop_event.is_set():
        try:
            n = dev.getQueueStatus()
            if n and n > 0:
                data = dev.read(n)
                for b in data:
                    byte = b if isinstance(b, int) else ord(b)
                    buf.append(byte)
                    if 32 <= byte < 127 or byte in (10, 13, 9):
                        sys.stdout.write(chr(byte))
                    else:
                        sys.stdout.write(f'[{byte:02x}]')
                sys.stdout.flush()
            else:
                time.sleep(0.001)
        except Exception as e:
            print(f"\n[FTDI error: {e}]")
            time.sleep(0.1)
    output_list.extend(buf)

def main():
    duration = int(sys.argv[1]) if len(sys.argv) > 1 else 30
    print(f"=== JTAG Program + Boot Capture ===")

    # Step 1: Open FTDI first
    print("Opening FTDI Channel B...")
    n = ftd2xx.createDeviceInfoList()
    dev = ftd2xx.open(1)
    dev.resetDevice()
    dev.setBaudRate(115200)
    dev.setDataCharacteristics(8, 0, 0)
    dev.setFlowControl(0x0000, 0, 0)
    dev.setTimeouts(10, 10)
    dev.setLatencyTimer(1)
    dev.purge(1 | 2)  # Clear old buffer
    print("FTDI ready and listening.")

    # Step 2: Start background listener
    stop_event = threading.Event()
    output_list = []
    listener = threading.Thread(target=ftdi_listener, args=(dev, stop_event, output_list))
    listener.daemon = True
    listener.start()

    # Step 3: JTAG program FPGA (this resets CPU)
    print("JTAG programming FPGA (CPU will reset)...")
    result = subprocess.run(
        [r'C:\Xilinx\Vivado\2019.2\bin\vivado.bat', '-mode', 'batch',
         '-source', r'g:\GitHub\26-Arch\vivado\program_jtag.tcl'],
        capture_output=True, text=True, timeout=60,
        cwd=r'g:\GitHub\26-Arch'
    )
    print(f"JTAG done (exit code {result.returncode})")
    print(f"Capturing for {duration}s after JTAG...\n")

    # Step 4: Wait for capture duration
    time.sleep(duration)

    # Step 5: Stop and report
    stop_event.set()
    listener.join(timeout=2)
    dev.close()

    print(f"\n\n=== Done. Total bytes captured: {len(output_list)} ===")
    print(f"Hex: {' '.join(f'{b:02x}' for b in output_list)}")

if __name__ == '__main__':
    main()
