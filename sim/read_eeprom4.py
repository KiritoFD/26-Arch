"""Read FT2232 EEPROM using direct FTD2XX DLL calls via ctypes."""
import ctypes
import ctypes.wintypes

# Load FTD2XX DLL
try:
    ftd2xx_dll = ctypes.windll.FTD2XX
except:
    try:
        ftd2xx_dll = ctypes.windll.LoadLibrary("C:\\Windows\\System32\\FTD2XX.dll")
    except:
        print("Cannot load FTD2XX.dll")
        exit(1)

print("FTD2XX.dll loaded")

# FT_STATUS codes
FT_OK = 0

# Function prototypes
ft_open = ftd2xx_dll.FT_Open
ft_open.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_void_p)]
ft_open.restype = ctypes.c_ulong

ft_close = ftd2xx_dll.FT_Close
ft_close.argtypes = [ctypes.c_void_p]
ft_close.restype = ctypes.c_ulong

ft_read_ee = ftd2xx_dll.FT_ReadEE
ft_read_ee.argtypes = [ctypes.c_void_p, ctypes.c_ulong, ctypes.POINTER(ctypes.c_ushort)]
ft_read_ee.restype = ctypes.c_ulong

ft_get_device_info = ftd2xx_dll.FT_GetDeviceInfo
ft_get_device_info.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_ulong), 
                                ctypes.POINTER(ctypes.c_ulong), ctypes.c_char_p,
                                ctypes.c_char_p, ctypes.POINTER(ctypes.c_ulong)]
ft_get_device_info.restype = ctypes.c_ulong

# Open device by index
for idx in range(2):
    handle = ctypes.c_void_p()
    status = ft_open(idx, ctypes.byref(handle))
    if status != FT_OK:
        print(f"Device {idx}: FT_Open failed with status {status}")
        continue
    
    print(f"\n=== Device {idx} ===")
    
    # Read EEPROM words
    words = []
    for addr in range(64):
        val = ctypes.c_ushort()
        status = ft_read_ee(handle, addr, ctypes.byref(val))
        if status != FT_OK:
            print(f"  FT_ReadEE failed at addr {addr}: status {status}")
            break
        words.append(val.value)
    
    if words:
        print(f"  Read {len(words)} EEPROM words:")
        for j in range(0, len(words), 8):
            hex_str = ' '.join(f'{words[j+k]:04x}' for k in range(min(8, len(words)-j)))
            print(f"  {j*2:04x}: {hex_str}")
        
        # Parse FT2232H EEPROM
        # Word 0: VID (low byte first)
        vid = words[0]
        pid = words[1]
        print(f"  VID: 0x{vid:04x}, PID: 0x{pid:04x}")
        
        # Word 3 contains config: low byte = Channel A driver, high byte = Channel B driver
        # But FT2232H EEPROM layout is different
        # Actually for FT2232H:
        # Offset 0x00: VID
        # Offset 0x02: PID
        # Offset 0x04: Device release
        # Offset 0x06: Config byte 0 = Channel A type
        #              Config byte 1 = Channel B type
        # Type values: 0=UART, 1=FT245 FIFO, 2=CPU FIFO
        
        # Words are 16-bit little-endian
        # Word 3 = bytes [6, 7]
        config_word = words[3]
        ch_a_type = config_word & 0xFF
        ch_b_type = (config_word >> 8) & 0xFF
        type_names = {0: 'UART', 1: 'FT245 FIFO', 2: 'CPU FIFO', 4: 'OPTO'}
        print(f"  Channel A type: {ch_a_type} ({type_names.get(ch_a_type, 'Unknown')})")
        print(f"  Channel B type: {ch_b_type} ({type_names.get(ch_b_type, 'Unknown')})")
    
    ft_close(handle)
