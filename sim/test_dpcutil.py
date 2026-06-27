"""Test Digilent Adept dpcutil to see if it can discover Basys3."""
import ctypes

try:
    dpcutil = ctypes.windll.dpcutil
    print("dpcutil.dll loaded OK")
except Exception as e:
    print(f"Cannot load dpcutil.dll: {e}")
    exit(1)

# DpcInit - initialize the library
init = dpcutil.DpcInit
init.restype = ctypes.c_int
init.argtypes = []
result = init()
print(f"DpcInit() = {result} (0=success)")

# DpcIdFirst - get first device ID
id_first = dpcutil.DpcIdFirst
id_first.restype = ctypes.c_int
id_first.argtypes = [ctypes.POINTER(ctypes.c_uint)]

dev_id = ctypes.c_uint(0)
result = id_first(ctypes.byref(dev_id))
print(f"DpcIdFirst() = {result}, dev_id = {dev_id.value}")
if result == 0:
    print("  -> No Digilent devices found by dpcutil!")

    # This is the problem - dpcutil doesn't see the board
    # The board needs to be registered with Digilent Adept
    print("\n  Digilent Adept cannot see the Basys3.")
    print("  Need to install Vivado's cable drivers (install_digilent.exe)")
else:
    print(f"  -> Found device! ID = {dev_id.value}")

    # Try to get name
    get_name = dpcutil.DpcGetName
    get_name.restype = ctypes.c_int
    get_name.argtypes = [ctypes.c_uint, ctypes.c_char_p, ctypes.c_uint]
    name_buf = ctypes.create_string_buffer(256)
    result = get_name(dev_id, name_buf, 256)
    if result:
        print(f"  Name: {name_buf.value.decode('ascii', errors='replace')}")

# Also check FT2232H cable detection via xilinx hw_server's mechanism
# hw_server uses its own Digilent plugin, let's check the plugin DLL
import os
vivado_plugins = "C:\\Xilinx\\Vivado\\2019.2\\lib\\win64.o"
print(f"\n=== Vivado plugins ({vivado_plugins}) ===")
if os.path.isdir(vivado_plugins):
    for f in os.listdir(vivado_plugins):
        if 'digilent' in f.lower() or 'diligent' in f.lower() or 'cable' in f.lower():
            print(f"  {f}")
