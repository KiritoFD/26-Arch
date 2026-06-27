"""Interactive D2XX serial console for Basys3 Channel A.

Usage:
  python sim\d2xx_serial.py                 # default 115200 8N1
  python sim\d2xx_serial.py 9600            # custom baud
  python sim\d2xx_serial.py 115200 --hex    # hex mode (printable ASCII + hex)

No COM port needed. Uses FTD2XX.dll directly to talk to the FT2232H Channel A.
Vivado/hw_server must be closed first so the device is free.

Keys:
  Ctrl+C  : quit
  Ctrl+R  : toggle hex display
  Enter   : send newline (\n)
  Any other printable key: send as byte
"""
import ctypes
import sys
import threading
import time
import argparse

ftd2xx = ctypes.windll.FTD2XX

# Argument parsing
parser = argparse.ArgumentParser(description='D2XX serial console for Basys3 Channel A')
parser.add_argument('baud', type=int, nargs='?', default=115200, help='Baud rate (default 115200)')
parser.add_argument('--hex', action='store_true', help='Show received bytes in hex')
parser.add_argument('--device', type=int, default=0, help='D2XX device index (0=Channel A, 1=Channel B)')
parser.add_argument('--latency', type=int, default=16, help='Latency timer in ms (default 16)')
args = parser.parse_args()

# Open device
handle = ctypes.c_void_p()
status = ftd2xx.FT_Open(args.device, ctypes.byref(handle))
if status != 0:
    print(f"FT_Open({args.device}) failed: status={status}")
    print("Make sure Vivado/hw_server is closed (it locks the FTDI device).")
    sys.exit(1)

# Get device info to confirm
ft_type = ctypes.c_uint32()
dev_id = ctypes.c_uint32()
sn = ctypes.create_string_buffer(16)
desc = ctypes.create_string_buffer(64)
ftd2xx.FT_GetDeviceInfo(handle, ctypes.byref(ft_type), ctypes.byref(dev_id), sn, desc, None)
print(f"Opened: type={ft_type.value}, SN={sn.value.decode('ascii','replace')}, Desc={desc.value.decode('ascii','replace')}")

# Configure UART
ftd2xx.FT_SetBaudRate(handle, args.baud)
ftd2xx.FT_SetDataCharacteristics(handle, 8, 0, 0)  # 8 bits, no parity, 1 stop
ftd2xx.FT_SetFlowControl(handle, 0, 0, 0)
ftd2xx.FT_SetLatencyTimer(handle, args.latency)
ftd2xx.FT_SetTimeouts(handle, 50, 50)  # short timeouts for interactive
ftd2xx.FT_Purge(handle, 1)
ftd2xx.FT_Purge(handle, 2)

print(f"UART configured: {args.baud} 8N1, latency={args.latency}ms")
print("Type characters to send, Enter=\\n, Ctrl+R=toggle hex, Ctrl+C=quit")
print("---")

hex_mode = args.hex
running = True
lock = threading.Lock()


def reader_thread():
    """Background thread that reads and prints incoming UART data."""
    global hex_mode
    buf = ctypes.create_string_buffer(8192)
    while running:
        available = ctypes.c_uint32()
        status = ftd2xx.FT_GetQueueStatus(handle, ctypes.byref(available))
        if status != 0 or available.value == 0:
            time.sleep(0.01)
            continue
        to_read = min(available.value, 8192)
        read_bytes = ctypes.c_uint32()
        status = ftd2xx.FT_Read(handle, buf, to_read, ctypes.byref(read_bytes))
        if status != 0:
            print(f"\n[FT_Read error: {status}]", file=sys.stderr)
            break
        if read_bytes.value > 0:
            data = buf.raw[:read_bytes.value]
            with lock:
                if hex_mode:
                    # Show printable ASCII + hex for non-printable
                    out = []
                    for b in data:
                        if 32 <= b < 127 or b in (10, 13, 9):
                            out.append(chr(b))
                        else:
                            out.append(f'[{b:02x}]')
                    print(''.join(out), end='', flush=True)
                else:
                    try:
                        print(data.decode('utf-8', errors='replace'), end='', flush=True)
                    except:
                        print(data.decode('latin-1', errors='replace'), end='', flush=True)


def input_thread():
    """Background thread that reads keyboard input and sends to UART."""
    global hex_mode, running
    try:
        while running:
            ch = sys.stdin.read(1)
            if not ch:
                continue
            if ch == '\x03':  # Ctrl+C
                running = False
                break
            if ch == '\x12':  # Ctrl+R
                with lock:
                    hex_mode = not hex_mode
                    print(f"\n[hex_mode={'on' if hex_mode else 'off'}]", flush=True)
                continue
            # Map Enter to \n
            if ch == '\r':
                send = b'\n'
            else:
                send = ch.encode('latin-1', errors='replace')
            written = ctypes.c_uint32()
            ftd2xx.FT_Write(handle, ctypes.create_string_buffer(send), len(send), ctypes.byref(written))
    except KeyboardInterrupt:
        running = False


t1 = threading.Thread(target=reader_thread, daemon=True)
t2 = threading.Thread(target=input_thread, daemon=True)
t1.start()
t2.start()

try:
    while running:
        time.sleep(0.1)
except KeyboardInterrupt:
    running = False

ftd2xx.FT_Close(handle)
print("\n[Closed]")
