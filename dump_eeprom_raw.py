"""
Dump FT2232H EEPROM raw words (256 words = 512 bytes)
用 FT_ReadEE 直接读，绕过 FT_PROGRAM_DATA 结构体
"""
import ftd2xx
from ftd2xx._ftd2xx import FT_ReadEE, FT_WriteEE, FT_HANDLE, DWORD, WORD, LPWORD
import ctypes

# 枚举
devices = ftd2xx.listDevices()
print(f"[INFO] Found {len(devices)} FTDI device(s)")

# 打开 channel 1
dev = None
for idx in range(len(devices)):
    try:
        dev = ftd2xx.open(idx)
        print(f"[INFO] Opened channel index {idx}")
        break
    except ftd2xx.DeviceError as e:
        print(f"[INFO] open({idx}) failed: {e}")

if dev is None:
    print("[ERROR] Cannot open any FTDI channel")
    exit(1)

# dev.handle 是 FT_HANDLE
handle = dev.handle
print(f"[INFO] handle = {handle}")

# 读 256 words
print("\n" + "=" * 60)
print("EEPROM raw dump (256 words)")
print("=" * 60)
words = []
for i in range(256):
    val = WORD(0)
    status = FT_ReadEE(handle, DWORD(i), ctypes.byref(val))
    if status != 0:
        print(f"[ERROR] FT_ReadEE({i}) failed: {status}")
        dev.close()
        exit(1)
    words.append(val.value)

# 打印
for i in range(0, 256, 8):
    line = f"{i:3d}: "
    for j in range(8):
        line += f"{words[i+j]:04x} "
    # ASCII
    ascii_str = ""
    for j in range(8):
        w = words[i+j]
        ascii_str += chr(w & 0xff) if 32 <= (w & 0xff) < 127 else "."
        ascii_str += chr((w >> 8) & 0xff) if 32 <= ((w >> 8) & 0xff) < 127 else "."
    line += f" |{ascii_str}|"
    print(line)

# 校验和验证 (word 0..254 XOR = word 255)
checksum_calc = 0
for i in range(255):
    checksum_calc ^= words[i]
print(f"\n[CHECKSUM] word 255 stored = 0x{words[255]:04x}")
print(f"[CHECKSUM] word 255 calc   = 0x{checksum_calc:04x}")
if checksum_calc == words[255]:
    print("[CHECKSUM] OK")
else:
    print("[CHECKSUM] MISMATCH!")

# 关键 word 解析
print("\n" + "=" * 60)
print("关键字段解析")
print("=" * 60)
print(f"Word 0 (VID)        : 0x{words[0]:04x}")
print(f"Word 1 (PID)        : 0x{words[1]:04x}")
print(f"Word 2              : 0x{words[2]:04x}")
print(f"Word 3 (Config)     : 0x{words[3]:04x}")
print(f"  AIsFifo    (bit 8)  = {(words[3] >> 8) & 1}")
print(f"  AIsFifoTar (bit 9)  = {(words[3] >> 9) & 1}")
print(f"  AIsFastSer (bit 10) = {(words[3] >> 10) & 1}")
print(f"  BIsFifo    (bit 11) = {(words[3] >> 11) & 1}")
print(f"  BIsFifoTar (bit 12) = {(words[3] >> 12) & 1}")
print(f"  BIsFastSer (bit 13) = {(words[3] >> 13) & 1}")
print(f"Word 4              : 0x{words[4]:04x}")
print(f"Word 5              : 0x{words[5]:04x}")
# 尝试找 DriverType
# FT2232H DriverType 可能在 word 4 的低字节
# ADriverType: 0=D2XX, 1=VCP
print(f"\nWord 4 low byte  = 0x{words[4] & 0xff:02x}")
print(f"Word 4 high byte = 0x{(words[4] >> 8) & 0xff:02x}")

dev.close()
print(f"\n[DONE] Dump complete")
