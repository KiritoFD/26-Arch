"""Try reading COM4 using Windows API directly via ctypes."""
import ctypes
import time

kernel32 = ctypes.windll.kernel32

# Open COM4
port_name = "\\\\.\\COM4"
handle = kernel32.CreateFileW(
    port_name,
    0x80000000,  # GENERIC_READ
    0,           # no sharing
    None,
    3,           # OPEN_EXISTING
    0,
    None
)

if handle == -1:
    error = ctypes.GetLastError()
    print(f"Failed to open COM4: error {error}")
else:
    print(f"COM4 handle: {handle}")
    
    # Set up DCB (Device Control Block)
    dcb = ctypes.create_string_buffer(28)
    dcb_bytes = dcb.raw
    dcb_bytes = b'\x1c\x00\x00\x00' + b'\x00\xc2\x01\x00'  # DCBlength=28, BaudRate=115200
    # ... this is getting too complex
    
    # Just try reading
    buf = ctypes.create_string_buffer(256)
    bytes_read = ctypes.c_ulong(0)
    
    # Set timeouts
    timeouts = ctypes.create_string_buffer(20)
    # ReadIntervalTimeout=MAXDWORD, ReadTotalTimeoutMultiplier=0, 
    # ReadTotalTimeoutConstant=5000
    import struct
    struct.pack_into('IIIII', timeouts, 0, 0xFFFFFFFF, 0, 0, 5000, 0)
    kernel32.SetCommTimeouts(handle, timeouts)
    
    print("Reading for 10 seconds...")
    start = time.time()
    total = 0
    while time.time() - start < 10:
        result = kernel32.ReadFile(handle, buf, 256, ctypes.byref(bytes_read), None)
        n = bytes_read.value
        if n > 0:
            total += n
            data = buf.raw[:n]
            print(f"  Got {n} bytes: {data[:50].hex()}")
    
    print(f"Total: {total} bytes")
    kernel32.CloseHandle(handle)
