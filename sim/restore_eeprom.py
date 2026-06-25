"""Restore FT2232 EEPROM from backup."""
import ctypes
import sys

# Load FTD2XX DLL
ftd2xx_dll = ctypes.windll.FTD2XX

FT_OK = 0

ft_open = ftd2xx_dll.FT_Open
ft_open.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_void_p)]
ft_open.restype = ctypes.c_ulong

ft_close = ftd2xx_dll.FT_Close
ft_close.argtypes = [ctypes.c_void_p]
ft_close.restype = ctypes.c_ulong

ft_read_ee = ftd2xx_dll.FT_ReadEE
ft_read_ee.argtypes = [ctypes.c_void_p, ctypes.c_ulong, ctypes.POINTER(ctypes.c_ushort)]
ft_read_ee.restype = ctypes.c_ulong

ft_write_ee = ftd2xx_dll.FT_WriteEE
ft_write_ee.argtypes = [ctypes.c_void_p, ctypes.c_ulong, ctypes.c_ushort]
ft_write_ee.restype = ctypes.c_ulong

# Read backup
with open("G:\\GitHub\\26-Arch\\sim\\eeprom_backup.bin", "rb") as f:
    backup_data = f.read()

# Convert to words
backup_words = []
for i in range(0, len(backup_data), 2):
    word = int.from_bytes(backup_data[i:i+2], 'little')
    backup_words.append(word)

print(f"Backup has {len(backup_words)} words")

# Open device
handle = ctypes.c_void_p()
status = ft_open(0, ctypes.byref(handle))
if status != FT_OK:
    print(f"FT_Open failed: {status}")
    print("Cannot restore - device not found!")
    sys.exit(1)

# Read current EEPROM for comparison
current_words = []
for addr in range(len(backup_words)):
    val = ctypes.c_ushort()
    ft_read_ee(handle, addr, ctypes.byref(val))
    current_words.append(val.value)

# Find differences
diffs = []
for i in range(len(backup_words)):
    if backup_words[i] != current_words[i]:
        diffs.append((i, backup_words[i], current_words[i]))

print(f"Found {len(diffs)} differences:")
for addr, backup, current in diffs:
    print(f"  Word {addr}: backup=0x{backup:04x}, current=0x{current:04x}")

# Restore only the changed words
for addr, backup_val, _ in diffs:
    status = ft_write_ee(handle, addr, backup_val)
    if status != FT_OK:
        print(f"  FT_WriteEE failed at word {addr}: {status}")
    else:
        print(f"  Restored word {addr} to 0x{backup_val:04x}")

# Verify
print("\nVerification:")
for addr, backup_val, _ in diffs:
    val = ctypes.c_ushort()
    ft_read_ee(handle, addr, ctypes.byref(val))
    if val.value == backup_val:
        print(f"  Word {addr}: OK (0x{val.value:04x})")
    else:
        print(f"  Word {addr}: MISMATCH (expected 0x{backup_val:04x}, got 0x{val.value:04x})")

ft_close(handle)
print("\nDone! Please unplug and replug the Basys3 USB cable.")
