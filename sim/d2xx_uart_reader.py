"""Test reading UART data from Basys3 Channel A via FTD2XX (D2XX mode, no COM port needed)."""
import ctypes
import time

ftd2xx = ctypes.windll.FTD2XX

handle = ctypes.c_void_p()
status = ftd2xx.FT_Open(0, ctypes.byref(handle))
print(f"FT_Open(0) status={status}")
if status != 0:
    print("Cannot open Channel A. Make sure Vivado is closed.")
    exit(1)

# Configure UART: 115200 baud, 8N1
ftd2xx.FT_SetBaudRate(handle, 115200)
ftd2xx.FT_SetDataCharacteristics(handle, 8, 0, 0)  # 8 bits, no parity, 1 stop
ftd2xx.FT_SetFlowControl(handle, 0, 0, 0)  # no flow control
ftd2xx.FT_SetLatencyTimer(handle, 16)  # 16ms latency
ftd2xx.FT_SetTimeouts(handle, 1000, 1000)  # 1s read/write timeout
ftd2xx.FT_Purge(handle, 1)  # purge RX
ftd2xx.FT_Purge(handle, 2)  # purge TX

print("UART configured: 115200 8N1, latency=16ms, timeout=1s")
print("Reading 5 seconds of UART data from Basys3 Channel A...")
print("(If xv6 is running, you should see boot messages)")

# Read for 5 seconds
total_rx = 0
start = time.time()
buf = ctypes.create_string_buffer(4096)
rx_all = bytearray()

while time.time() - start < 5:
    available = ctypes.c_uint32()
    status = ftd2xx.FT_GetQueueStatus(handle, ctypes.byref(available))
    if status != 0:
        print(f"FT_GetQueueStatus failed: {status}")
        break
    if available.value > 0:
        read_bytes = ctypes.c_uint32()
        to_read = min(available.value, 4096)
        status = ftd2xx.FT_Read(handle, buf, to_read, ctypes.byref(read_bytes))
        if status != 0:
            print(f"FT_Read failed: {status}")
            break
        if read_bytes.value > 0:
            data = buf.raw[:read_bytes.value]
            rx_all.extend(data)
            total_rx += read_bytes.value
            # Print as ASCII where possible
            try:
                text = data.decode('ascii', errors='replace')
                print(text, end='', flush=True)
            except:
                print(f"[hex: {data.hex()}]")
    time.sleep(0.05)

print()
print(f"\n=== Done. Total RX bytes: {total_rx} ===")
ftd2xx.FT_Close(handle)
