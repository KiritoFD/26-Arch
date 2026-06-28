"""
FT2232H EEPROM 读取与备份脚本（CLI，不依赖 FT_Prog）
通过 ftd2xx.dll 直接读 EEPROM 配置，保存为 JSON + raw user area
用法: python read_eeprom_backup.py
"""
import ctypes
import json
import os
import sys
from datetime import datetime

# ============================================================
# 加载 ftd2xx.dll
# ============================================================
ftd2xx = None
for path in ["ftd2xx.dll", r"C:\Windows\System32\ftd2xx.dll", r"C:\Windows\System32\FTD2XX.dll"]:
    try:
        ftd2xx = ctypes.WinDLL(path)
        print(f"[INFO] Loaded ftd2xx.dll from: {path}")
        break
    except OSError:
        continue
if ftd2xx is None:
    print("[ERROR] ftd2xx.dll not found. Install FTDI D2XX driver.")
    sys.exit(1)

FT_OK = 0

# ============================================================
# FT_PROGRAM_DATA 结构（FT2232H/FT4232H）
# 参考 FTDI AN_233 应用笔记
# ============================================================
class FT_PROGRAM_DATA(ctypes.Structure):
    _fields_ = [
        ("Signature1", ctypes.c_uint32),
        ("Signature2", ctypes.c_uint32),
        ("Version", ctypes.c_uint32),
        ("VendorId", ctypes.c_uint16),
        ("ProductId", ctypes.c_uint16),
        ("Manufacturer", ctypes.c_char_p),
        ("ManufacturerId", ctypes.c_char_p),
        ("Description", ctypes.c_char_p),
        ("SerialNumber", ctypes.c_char_p),
        ("MaxPower", ctypes.c_uint16),
        ("PnP", ctypes.c_uint16),
        ("SelfPowered", ctypes.c_uint16),
        ("RemoteWakeup", ctypes.c_uint16),
        # Rev4 fields (FT2232H)
        ("Rev4", ctypes.c_uint8),
        ("IsoIn", ctypes.c_uint8),
        ("IsoOut", ctypes.c_uint8),
        ("PullDownEnable", ctypes.c_uint8),
        ("SerNumEnable", ctypes.c_uint8),
        ("USBVersionEnable", ctypes.c_uint8),
        ("USBVersion", ctypes.c_uint16),
        # Rev5 fields (FT232H) - FT2232H 也填充这些
        ("AHighSpeed", ctypes.c_uint8),
        ("BHighSpeed", ctypes.c_uint8),
        ("CHighSpeed", ctypes.c_uint8),
        ("DHighSpeed", ctypes.c_uint8),
        ("AIsFifo", ctypes.c_uint8),
        ("AIsFifoTar", ctypes.c_uint8),
        ("AIsFastSer", ctypes.c_uint8),
        ("BIsFifo", ctypes.c_uint8),
        ("BIsFifoTar", ctypes.c_uint8),
        ("BIsFastSer", ctypes.c_uint8),
        ("ADriverType", ctypes.c_uint8),
        ("BDriverType", ctypes.c_uint8),
    ]

# ============================================================
# 函数原型
# ============================================================
ftd2xx.FT_Open.restype = ctypes.c_uint32
ftd2xx.FT_Open.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_void_p)]
ftd2xx.FT_Close.restype = ctypes.c_uint32
ftd2xx.FT_Close.argtypes = [ctypes.c_void_p]
ftd2xx.FT_EE_Read.restype = ctypes.c_uint32
ftd2xx.FT_EE_Read.argtypes = [ctypes.c_void_p, ctypes.POINTER(FT_PROGRAM_DATA)]
ftd2xx.FT_EE_UARead.restype = ctypes.c_uint32
ftd2xx.FT_EE_UARead.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_uint32, ctypes.POINTER(ctypes.c_uint32)]
ftd2xx.FT_ListDevices.restype = ctypes.c_uint32
ftd2xx.FT_ListDevices.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_uint32]

# FT_ListDevices flags
FT_LIST_NUMBER_ONLY = 0x80000000

# ============================================================
# 辅助函数
# ============================================================
def mode_str(is_fifo, is_fifo_tar, is_fastser):
    if is_fastser: return "FASTSER"
    if is_fifo: return "FIFO"
    if is_fifo_tar: return "FIFOTAR"
    return "UART"

def driver_str(d):
    if d == 0: return "D2XX"
    if d == 1: return "VCP(COM)"
    return f"UNKNOWN({d})"

def bitmode_val(is_fifo, is_fifo_tar, is_fastser):
    """返回对应的 BitMode 值（用于 FT_SetBitmode）"""
    if is_fifo: return 0x40
    if is_fastser: return 0x10
    return 0x00  # UART

# ============================================================
# 主流程
# ============================================================
# 1. 枚举设备数量
num_devices = ctypes.c_uint32(0)
status = ftd2xx.FT_ListDevices(ctypes.byref(num_devices), None, FT_LIST_NUMBER_ONLY)
if status != FT_OK:
    print(f"[ERROR] FT_ListDevices failed: {status}")
    sys.exit(1)
print(f"[INFO] Found {num_devices.value} FTDI device(s)")
if num_devices.value == 0:
    print("[ERROR] No FTDI devices found")
    sys.exit(1)

# 2. 尝试打开 channel 0 和 1（EEPROM 共享，任一打开即可读 A+B 配置）
handle = ctypes.c_void_p()
opened_idx = -1
for idx in range(int(num_devices.value)):
    status = ftd2xx.FT_Open(idx, ctypes.byref(handle))
    print(f"[INFO] FT_Open({idx}) status={status}")
    if status == FT_OK:
        opened_idx = idx
        print(f"[INFO] Opened channel index {idx}")
        break
    # status=3 表示 DEVICE_NOT_OPENED（端口被占用）

if opened_idx < 0:
    print("[ERROR] Cannot open any FTDI channel")
    print("  可能原因:")
    print("  1. Vivado Hardware Manager 正占用 channel B (JTAG)")
    print("  2. Channel A 被 VCP 驱动占用（COM 口被打开）")
    print("  解决: 关闭 Vivado Hardware Manager，确保没有程序打开 COM 口，再重试")
    sys.exit(1)

# 3. 分配字符串缓冲区
buf_mfr = ctypes.create_string_buffer(256)
buf_mfr_id = ctypes.create_string_buffer(256)
buf_desc = ctypes.create_string_buffer(256)
buf_serial = ctypes.create_string_buffer(256)

# 4. 填充 FT_PROGRAM_DATA
data = FT_PROGRAM_DATA()
data.Signature1 = 0
data.Signature2 = 0xffffffff
data.Version = 2
data.Manufacturer = ctypes.cast(buf_mfr, ctypes.c_char_p)
data.ManufacturerId = ctypes.cast(buf_mfr_id, ctypes.c_char_p)
data.Description = ctypes.cast(buf_desc, ctypes.c_char_p)
data.SerialNumber = ctypes.cast(buf_serial, ctypes.c_char_p)

# 5. FT_EE_Read
status = ftd2xx.FT_EE_Read(handle, ctypes.byref(data))
if status != FT_OK:
    print(f"[ERROR] FT_EE_Read failed: {status}")
    ftd2xx.FT_Close(handle)
    sys.exit(1)
print("[INFO] FT_EE_Read OK")

# 6. 读 User Area (raw bytes)
ua_buf = ctypes.create_string_buffer(256)
ua_read = ctypes.c_uint32(0)
status = ftd2xx.FT_EE_UARead(handle, ua_buf, 256, ctypes.byref(ua_read))
if status != FT_OK:
    print(f"[WARN] FT_EE_UARead failed: {status} (非致命)")
    ua_bytes = b""
else:
    ua_bytes = ua_buf.raw[:ua_read.value]
    print(f"[INFO] User Area: {ua_read.value} bytes")

# 7. 关闭
ftd2xx.FT_Close(handle)
print("[INFO] FT_Close OK")

# ============================================================
# 解析结果
# ============================================================
mfr = buf_mfr.value.decode('ascii', errors='replace')
mfr_id = buf_mfr_id.value.decode('ascii', errors='replace')
desc = buf_desc.value.decode('ascii', errors='replace')
serial = buf_serial.value.decode('ascii', errors='replace')

print("\n" + "=" * 60)
print("EEPROM 配置")
print("=" * 60)
print(f"VID (VendorId)      : 0x{data.VendorId:04x}")
print(f"PID (ProductId)     : 0x{data.ProductId:04x}")
print(f"Manufacturer        : {mfr}")
print(f"ManufacturerId      : {mfr_id}")
print(f"Description         : {desc}")
print(f"SerialNumber        : {serial}")
print(f"MaxPower            : {data.MaxPower} (×2mA = {data.MaxPower*2}mA)")
print(f"SelfPowered         : {data.SelfPowered}")
print(f"RemoteWakeup        : {data.RemoteWakeup}")
print(f"PullDownEnable      : {data.PullDownEnable}")
print(f"SerNumEnable        : {data.SerNumEnable}")
print(f"USBVersionEnable    : {data.USBVersionEnable}")
print(f"USBVersion          : 0x{data.USBVersion:04x} ({(data.USBVersion>>8)&0xff}.{data.USBVersion&0xff})")
print()
print(f"Port A:")
print(f"  Mode              : {mode_str(data.AIsFifo, data.AIsFifoTar, data.AIsFastSer)}")
print(f"  Driver            : {driver_str(data.ADriverType)}")
print(f"  BitMode value     : 0x{bitmode_val(data.AIsFifo, data.AIsFifoTar, data.AIsFastSer):02x}")
print(f"  IsFifo/FifoTar/FastSer : {data.AIsFifo}/{data.AIsFifoTar}/{data.AIsFastSer}")
print(f"  DriverType raw    : {data.ADriverType}")
print(f"  HighSpeed         : {data.AHighSpeed}")
print()
print(f"Port B:")
print(f"  Mode              : {mode_str(data.BIsFifo, data.BIsFifoTar, data.BIsFastSer)}")
print(f"  Driver            : {driver_str(data.BDriverType)}")
print(f"  BitMode value     : 0x{bitmode_val(data.BIsFifo, data.BIsFifoTar, data.BIsFastSer):02x}")
print(f"  IsFifo/FifoTar/FastSer : {data.BIsFifo}/{data.BIsFifoTar}/{data.BIsFastSer}")
print(f"  DriverType raw    : {data.BDriverType}")
print(f"  HighSpeed         : {data.BHighSpeed}")
print("=" * 60)

# ============================================================
# 保存备份
# ============================================================
backup_dir = r"g:\GitHub\26-Arch\eeprom_backup"
os.makedirs(backup_dir, exist_ok=True)
ts = datetime.now().strftime("%Y%m%d_%H%M%S")

# JSON 备份（结构化）
backup_json = {
    "backup_time": ts,
    "device_count": num_devices.value,
    "Signature1": f"0x{data.Signature1:08x}",
    "Signature2": f"0x{data.Signature2:08x}",
    "Version": data.Version,
    "VendorId": f"0x{data.VendorId:04x}",
    "ProductId": f"0x{data.ProductId:04x}",
    "Manufacturer": mfr,
    "ManufacturerId": mfr_id,
    "Description": desc,
    "SerialNumber": serial,
    "MaxPower": data.MaxPower,
    "MaxPower_mA": data.MaxPower * 2,
    "PnP": data.PnP,
    "SelfPowered": data.SelfPowered,
    "RemoteWakeup": data.RemoteWakeup,
    "Rev4": data.Rev4,
    "IsoIn": data.IsoIn,
    "IsoOut": data.IsoOut,
    "PullDownEnable": data.PullDownEnable,
    "SerNumEnable": data.SerNumEnable,
    "USBVersionEnable": data.USBVersionEnable,
    "USBVersion": data.USBVersion,
    "PortA": {
        "Mode": mode_str(data.AIsFifo, data.AIsFifoTar, data.AIsFastSer),
        "Driver": driver_str(data.ADriverType),
        "IsFifo": data.AIsFifo,
        "IsFifoTar": data.AIsFifoTar,
        "IsFastSer": data.AIsFastSer,
        "DriverType": data.ADriverType,
        "HighSpeed": data.AHighSpeed,
    },
    "PortB": {
        "Mode": mode_str(data.BIsFifo, data.BIsFifoTar, data.BIsFastSer),
        "Driver": driver_str(data.BDriverType),
        "IsFifo": data.BIsFifo,
        "IsFifoTar": data.BIsFifoTar,
        "IsFastSer": data.BIsFastSer,
        "DriverType": data.BDriverType,
        "HighSpeed": data.BHighSpeed,
    },
    "UserArea_hex": ua_bytes.hex() if ua_bytes else "",
    "UserArea_size": len(ua_bytes),
}

json_path = os.path.join(backup_dir, f"eeprom_backup_{ts}.json")
with open(json_path, "w", encoding="utf-8") as f:
    json.dump(backup_json, f, indent=2, ensure_ascii=False)
print(f"\n[OK] JSON backup saved: {json_path}")

# raw user area
if ua_bytes:
    ua_path = os.path.join(backup_dir, f"user_area_{ts}.bin")
    with open(ua_path, "wb") as f:
        f.write(ua_bytes)
    print(f"[OK] User area saved: {ua_path}")

print(f"\n[DONE] Backup complete. Files in: {backup_dir}")
