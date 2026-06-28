"""Check device status and EEPROM quickly."""
import ctypes
import struct

ft = ctypes.WinDLL('ftd2xx.dll')
ft.FT_CreateDeviceInfoList.argtypes = [ctypes.POINTER(ctypes.c_uint32)]
ft.FT_CreateDeviceInfoList.restype = ctypes.c_uint32
ft.FT_GetDeviceInfoDetail.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_uint32), ctypes.c_char_p, ctypes.c_char_p, ctypes.POINTER(ctypes.c_void_p)]
ft.FT_GetDeviceInfoDetail.restype = ctypes.c_uint32
ft.FT_Open.argtypes = [ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p)]
ft.FT_Open.restype = ctypes.c_uint32
ft.FT_ReadEE.argtypes = [ctypes.c_void_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint16)]
ft.FT_ReadEE.restype = ctypes.c_uint32
ft.FT_Close.argtypes = [ctypes.c_void_p]
ft.FT_Close.restype = ctypes.c_uint32
ft.FT_GetDeviceInfo.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_uint32), ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p]
ft.FT_GetDeviceInfo.restype = ctypes.c_uint32

# List devices
num = ctypes.c_uint32()
ft.FT_CreateDeviceInfoList(ctypes.byref(num))
print(f"D2XX devices found: {num.value}")

for i in range(num.value):
    flags = ctypes.c_uint32()
    typ = ctypes.c_uint32()
    vid = ctypes.c_uint32()
    pid = ctypes.c_uint32()
    serial = ctypes.create_string_buffer(32)
    desc = ctypes.create_string_buffer(128)
    handle = ctypes.c_void_p()
    ft.FT_GetDeviceInfoDetail(i, ctypes.byref(flags), ctypes.byref(typ), ctypes.byref(vid), ctypes.byref(pid), serial, desc, ctypes.byref(handle))
    print(f"  [{i}] flags=0x{flags.value:04x} VID=0x{vid.value:04x} PID=0x{pid.value:04x}")
    print(f"       serial='{serial.value.decode('ascii', errors='replace')}' desc='{desc.value.decode('ascii', errors='replace')}'")

# Try to open device 0 and read key EEPROM words
print("\n--- EEPROM Check ---")
handle = ctypes.c_void_p()
ret = ft.FT_Open(0, ctypes.byref(handle))
if ret != 0:
    print(f"FT_Open failed: {ret}")
    print("-> Device is likely occupied by Vivado/hw_server")
    print("-> This is NORMAL if Vivado is running. EEPROM check skipped.")
else:
    key_words = [0, 1, 3, 5, 9, 127, 128, 133, 255]
    for idx in key_words:
        w = ctypes.c_uint16()
        ft.FT_ReadEE(handle, idx, ctypes.byref(w))
        print(f"  word {idx:3d} = 0x{w.value:04x}")
    
    # Verify checksum
    words = []
    for i in range(256):
        w = ctypes.c_uint16()
        ft.FT_ReadEE(handle, i, ctypes.byref(w))
        words.append(w.value)
    
    cs127 = 0
    for w in words[:127]:
        cs127 ^= w
    cs255 = 0
    for w in words[128:255]:
        cs255 ^= w
    
    print(f"\n  Expected word 127 = 0x{cs127:04x}, actual = 0x{words[127]:04x} {'OK' if cs127 == words[127] else 'MISMATCH'}")
    print(f"  Expected word 255 = 0x{cs255:04x}, actual = 0x{words[255]:04x} {'OK' if cs255 == words[255] else 'MISMATCH'}")
    
    # Check string area
    s = bytes(words[9*16:9*16+16]) + bytes(words[10*16:10*16+16])
    print(f"  String area (words 144-175): {bytes(words[144:176])[:40]}...")
    
    ft.FT_Close(handle)
