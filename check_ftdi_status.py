"""
检查 FTDI 设备状态：channel A/B 的 driver type, COM port, 设备管理器状态
"""
import ftd2xx
import ctypes
from ftd2xx._ftd2xx import FT_OpenEx, FT_ListDevices, FT_GetDeviceInfoDetail
import ctypes

# 列出所有 FTDI 设备详细信息
print("=" * 70)
print("FTDI 设备详细列表")
print("=" * 70)

devices = ftd2xx.listDevices()
if not devices:
    print("[ERROR] No FTDI devices found")
    exit(1)

print(f"Total devices: {len(devices)}")
for i, d in enumerate(devices):
    print(f"  [{i}] {d}")

# 尝试打开每个 channel 看 driver type
print("\n" + "=" * 70)
print("逐个 channel 打开测试")
print("=" * 70)

for idx in range(len(devices)):
    print(f"\n--- Channel {idx} ---")
    try:
        dev = ftd2xx.open(idx)
        print(f"  Opened OK")
        try:
            print(f"  Description: {dev.getDescription()}")
        except Exception as e:
            print(f"  getDescription failed: {e}")
        try:
            info = dev.getDeviceInfo()
            print(f"  Info: {info}")
        except Exception as e:
            print(f"  getDeviceInfo failed: {e}")
        try:
            baud = dev.getBaudRate()
            print(f"  BaudRate: {baud}")
        except Exception as e:
            print(f"  getBaudRate failed: {e}")
        try:
            print(f"  DriverType: {dev.DriverType}")
        except Exception as e:
            print(f"  DriverType attr failed: {e}")
        try:
            # ftd2xx 1.3.x
            print(f"  ftHandle: {dev.handle}")
            print(f"  type: {dev.type}")
            print(f"  id: {dev.id}")
            print(f"  description: {dev.description}")
            print(f"  serial: {dev.serial}")
        except Exception as e:
            print(f"  attr access failed: {e}")
        dev.close()
    except ftd2xx.DeviceError as e:
        print(f"  Open FAILED: {e}")
    except Exception as e:
        print(f"  Error: {e}")

# 读 EEPROM 看 channel A/B 配置
print("\n" + "=" * 70)
print("EEPROM 当前配置")
print("=" * 70)

from ftd2xx._ftd2xx import FT_ReadEE, DWORD, WORD

dev = None
for idx in range(len(devices)):
    try:
        dev = ftd2xx.open(idx)
        print(f"Opened channel {idx} for EEPROM read")
        break
    except ftd2xx.DeviceError:
        continue

if dev:
    handle = dev.handle
    words = []
    for i in range(8):
        val = WORD(0)
        FT_ReadEE(handle, DWORD(i), ctypes.byref(val))
        words.append(val.value)
    print(f"word 0..7: {[f'0x{w:04x}' for w in words]}")
    print(f"word 4 = 0x{words[4]:04x} (bit 7 = {(words[4] >> 7) & 1})")
    print(f"word 5 = 0x{words[5]:04x}")
    dev.close()
