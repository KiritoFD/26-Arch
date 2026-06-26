#!/usr/bin/env python3
"""
Program FPGA via Vivado, then immediately read UART output.
Captures xv6 boot messages from the very first cycle.

Usage: python prog_and_read.py [read_duration_seconds]
"""
import sys
import time
import threading
import subprocess
import ftd2xx

def program_fpga():
    """Program FPGA via Vivado batch mode."""
    tcl = r"g:\GitHub\26-Arch\vivado\program_fpga_new_bit.tcl"
    vivado = r"C:\Xilinx\Vivado\2019.2\bin\vivado.bat"
    cmd = [vivado, "-mode", "batch", "-source", tcl,
           "-log", r"g:\GitHub\26-Arch\vivado\prog_capture.log",
           "-journal", r"g:\GitHub\26-Arch\vivado\prog_capture.jou"]
    print(f"[Vivado] Programming FPGA...")
    r = subprocess.run(cmd, capture_output=True, text=True, timeout=120)
    print(f"[Vivado] Exit code: {r.returncode}")
    if "End of startup status: HIGH" in r.stdout:
        print("[Vivado] FPGA programmed OK!")
        return True
    else:
        print(f"[Vivado] stdout tail: {r.stdout[-500:]}")
        return False

def read_uart_thread(dev, stop_event, output_list):
    """Background thread to read UART continuously."""
    total = 0
    while not stop_event.is_set():
        try:
            n = dev.getQueueStatus()
            if n and n > 0:
                data = dev.read(n)
                total += len(data)
                for b in data:
                    byte = b if isinstance(b, int) else ord(b)
                    if 32 <= byte <= 126 or byte in (10, 13):
                        output_list.append(chr(byte))
                    else:
                        output_list.append(f'[{byte:02x}]')
            else:
                time.sleep(0.005)
        except Exception as e:
            output_list.append(f'\n[Read error: {e}]\n')
            time.sleep(0.5)
    return total

def main():
    read_dur = int(sys.argv[1]) if len(sys.argv) > 1 else 30
    print(f"=== Combined FPGA Program + UART Read ===")
    print(f"Read duration after programming: {read_dur}s")

    # Step 1: Open FTDI Channel B FIRST (before programming FPGA)
    print("\n[FTDI] Opening Channel B...")
    n = ftd2xx.createDeviceInfoList()
    print(f"[FTDI] Devices found: {n}")
    dev = ftd2xx.open(1)
    dev.resetDevice()
    dev.setBaudRate(115200)
    dev.setDataCharacteristics(8, 0, 0)
    dev.setFlowControl(0x0000, 0, 0)
    dev.setTimeouts(100, 100)
    dev.setLatencyTimer(2)
    dev.purge(1 | 2)
    print("[FTDI] Channel B ready: 115200 8N1")

    # Step 2: Start UART reader thread
    output_list = []
    stop_event = threading.Event()
    reader = threading.Thread(target=read_uart_thread, args=(dev, stop_event, output_list))
    reader.start()
    print("[UART] Reader thread started, listening for data...")

    # Step 3: Program FPGA (this triggers xv6 boot)
    print("\n[Vivado] Programming FPGA now (xv6 will boot immediately)...")
    ok = program_fpga()

    if ok:
        print(f"\n[UART] Reading for {read_dur}s to capture xv6 output...")
        time.sleep(read_dur)
    else:
        print("[Vivado] Programming failed, reading 5s anyway...")
        time.sleep(5)

    # Step 4: Stop reader and collect output
    stop_event.set()
    reader.join(timeout=3)
    dev.close()

    # Step 5: Print captured output
    print(f"\n{'='*60}")
    print("CAPTURED UART OUTPUT:")
    print(f"{'='*60}")
    text = ''.join(output_list)
    print(text)
    print(f"{'='*60}")
    print(f"Total characters: {len(text)}")

if __name__ == '__main__':
    main()
