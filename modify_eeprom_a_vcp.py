"""
FT2232H EEPROM 修改脚本（修复版）
修改 Channel A DriverType: D2XX → VCP
关键修复：字符串 buffer 在主流程分配，保证 FT_EE_Program 时指针有效
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
    print("[ERROR] ftd2xx.dll not found")
    sys.exit(1)

FT_OK = 0
FT_LIST_NUMBER_ONLY = 0x80000000

# ============================================================
# FT_PROGRAM_DATA 结构（FT2232H）
# 参考 FTDI D2XX Programmer's Guide
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
        ("Rev4", ctypes.c_uint8),
        ("IsoIn", ctypes.c_uint8),
        ("IsoOut", ctypes.c_uint8),
        ("PullDownEnable", ctypes.c_uint8),
        ("SerNumEnable", ctypes.c_uint8),
        ("USBVersionEnable", ctypes.c_uint8),
        ("USBVersion", ctypes.c_uint16),
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
        # Rev6 (FT232H, FT2232H 不用但结构体需要完整大小)
        ("CIsFifo", ctypes.c_uint8),
        ("CIsFifoTar", ctypes.c_uint8),
        ("CIsFastSer", ctypes.c_uint8),
        ("DIsFifo", ctypes.c_uint8),
        ("DIsFifoTar", ctypes.c_uint8),
        ("DIsFastSer", ctypes.c_uint8),
        ("CDriverType", ctypes.c_uint8),
        ("DDriverType", ctypes.c_uint8),
        # Rev7 (AIsVCP 等，部分 ftd2xx 版本用这个控制 VCP)
        ("AIsVCP", ctypes.c_uint16),
        ("BIsVCP", ctypes.c_uint16),
        ("CIsVCP", ctypes.c_uint16),
        ("DIsVCP", ctypes.c_uint16),
    ]

print(f"[INFO] FT_PROGRAM_DATA size = {ctypes.sizeof(FT_PROGRAM_DATA)} bytes")

# 函数原型
ftd2xx.FT_Open.restype = ctypes.c_uint32
ftd2xx.FT_Open.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_void_p)]
ftd2xx.FT_Close.restype = ctypes.c_uint32
ftd2xx.FT_Close.argtypes = [ctypes.c_void_p]
ftd2xx.FT_EE_Read.restype = ctypes.c_uint32
ftd2xx.FT_EE_Read.argtypes = [ctypes.c_void_p, ctypes.POINTER(FT_PROGRAM_DATA)]
ftd2xx.FT_EE_Program.restype = ctypes.c_uint32
ftd2xx.FT_EE_Program.argtypes = [ctypes.c_void_p, ctypes.POINTER(FT_PROGRAM_DATA)]
ftd2xx.FT_ListDevices.restype = ctypes.c_uint32
ftd2xx.FT_ListDevices.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_uint32]

def driver_str(d):
    if d == 0: return "D2XX"
    if d == 1: return "VCP(COM)"
    return f"UNKNOWN({d})"

# ============================================================
# 主流程
# ============================================================
# 1. 枚举设备
num_devices = ctypes.c_uint32(0)
ftd2xx.FT_ListDevices(ctypes.byref(num_devices), None, FT_LIST_NUMBER_ONLY)
print(f"[INFO] Found {num_devices.value} FTDI device(s)")

# 2. 打开 channel 1（B，D2XX 模式可靠打开；EEPROM 共享，B 也能读写 A 的配置）
handle = ctypes.c_void_p()
opened_idx = -1
for idx in range(int(num_devices.value)):
    status = ftd2xx.FT_Open(idx, ctypes.byref(handle))
    if status == FT_OK:
        opened_idx = idx
        print(f"[INFO] Opened channel index {idx}")
        break
if opened_idx < 0:
    print("[ERROR] Cannot open any FTDI channel (Vivado 可能占用 B，A 可能被 VCP 占用)")
    sys.exit(1)

# 3. 分配字符串 buffer（主流程作用域，保证整个写过程有效）
buf_mfr     = ctypes.create_string_buffer(256)
buf_mfr_id  = ctypes.create_string_buffer(256)
buf_desc    = ctypes.create_string_buffer(256)
buf_serial  = ctypes.create_string_buffer(256)

# 4. 填充 FT_PROGRAM_DATA 用于读取
data = FT_PROGRAM_DATA()
data.Signature1 = 0
data.Signature2 = 0xffffffff
data.Version = 2
data.Manufacturer   = ctypes.cast(buf_mfr, ctypes.c_char_p)
data.ManufacturerId = ctypes.cast(buf_mfr_id, ctypes.c_char_p)
data.Description    = ctypes.cast(buf_desc, ctypes.c_char_p)
data.SerialNumber   = ctypes.cast(buf_serial, ctypes.c_char_p)

# 5. FT_EE_Read（读当前配置，字符串会被写进 buf_*）
status = ftd2xx.FT_EE_Read(handle, ctypes.byref(data))
if status != FT_OK:
    print(f"[ERROR] FT_EE_Read failed: {status}")
    ftd2xx.FT_Close(handle)
    sys.exit(1)
print("[INFO] FT_EE_Read OK")

# 读出字符串值
mfr      = buf_mfr.value.decode('ascii', errors='replace')
mfr_id   = buf_mfr_id.value.decode('ascii', errors='replace')
desc     = buf_desc.value.decode('ascii', errors='replace')
serial   = buf_serial.value.decode('ascii', errors='replace')

print("\n" + "=" * 60)
print("修改前配置")
print("=" * 60)
print(f"VID=0x{data.VendorId:04x} PID=0x{data.ProductId:04x}")
print(f"Manufacturer: {mfr}")
print(f"ManufacturerId: {mfr_id}")
print(f"Description : {desc}")
print(f"SerialNumber: {serial}")
print(f"MaxPower    : {data.MaxPower} (×2mA = {data.MaxPower*2}mA)")
print(f"SerNumEnable: {data.SerNumEnable}")
print(f"Port A: Mode=UART Driver={driver_str(data.ADriverType)} (raw={data.ADriverType})")
print(f"Port B: Mode=UART Driver={driver_str(data.BDriverType)} (raw={data.BDriverType})")
print("=" * 60)

# 6. 备份（修改前）
backup_dir = r"g:\GitHub\26-Arch\eeprom_backup"
os.makedirs(backup_dir, exist_ok=True)
ts = datetime.now().strftime("%Y%m%d_%H%M%S")
backup_path = os.path.join(backup_dir, f"eeprom_pre_modify_{ts}.json")
backup_data = {
    "backup_time": ts,
    "VendorId": f"0x{data.VendorId:04x}",
    "ProductId": f"0x{data.ProductId:04x}",
    "Manufacturer": mfr,
    "ManufacturerId": mfr_id,
    "Description": desc,
    "SerialNumber": serial,
    "MaxPower": data.MaxPower,
    "SerNumEnable": data.SerNumEnable,
    "ADriverType": data.ADriverType,
    "BDriverType": data.BDriverType,
    "AIsFifo": data.AIsFifo,
    "AIsFifoTar": data.AIsFifoTar,
    "AIsFastSer": data.AIsFastSer,
    "BIsFifo": data.BIsFifo,
    "BIsFifoTar": data.BIsFifoTar,
    "BIsFastSer": data.BIsFastSer,
}
with open(backup_path, "w", encoding="utf-8") as f:
    json.dump(backup_data, f, indent=2, ensure_ascii=False)
print(f"\n[OK] Pre-modify backup: {backup_path}")

# 7. 确认是否需要修改
if data.ADriverType == 1:
    print("[INFO] Channel A 已经是 VCP，无需修改")
    ftd2xx.FT_Close(handle)
    sys.exit(0)

# 8. 修改：只改 ADriverType 0→1，其他全部保持
#    data 结构体本身不变，只改这一个字段
#    字符串指针仍然指向 buf_*（有效内存）
old_a = data.ADriverType
data.ADriverType = 1  # 0=D2XX, 1=VCP
print(f"\n[PLAN] Channel A: DriverType {old_a} → {data.ADriverType} (D2XX → VCP)")
print(f"[PLAN] Channel B: DriverType {data.BDriverType} (不变)")

# 9. 写入 EEPROM
print("\n[WRITE] 正在写入 EEPROM...")
status = ftd2xx.FT_EE_Program(handle, ctypes.byref(data))
if status != FT_OK:
    print(f"[ERROR] FT_EE_Program failed: {status}")
    ftd2xx.FT_Close(handle)
    sys.exit(1)
print("[OK] FT_EE_Program 成功")

# 10. 读回验证（重置 buffer 避免读到旧数据）
buf_mfr2    = ctypes.create_string_buffer(256)
buf_mfr_id2 = ctypes.create_string_buffer(256)
buf_desc2   = ctypes.create_string_buffer(256)
buf_serial2 = ctypes.create_string_buffer(256)

data2 = FT_PROGRAM_DATA()
data2.Signature1 = 0
data2.Signature2 = 0xffffffff
data2.Version = 2
data2.Manufacturer   = ctypes.cast(buf_mfr2, ctypes.c_char_p)
data2.ManufacturerId = ctypes.cast(buf_mfr_id2, ctypes.c_char_p)
data2.Description    = ctypes.cast(buf_desc2, ctypes.c_char_p)
data2.SerialNumber   = ctypes.cast(buf_serial2, ctypes.c_char_p)

status = ftd2xx.FT_EE_Read(handle, ctypes.byref(data2))
if status != FT_OK:
    print(f"[ERROR] 读回验证失败: {status}")
    ftd2xx.FT_Close(handle)
    sys.exit(1)

ftd2xx.FT_Close(handle)

print("\n" + "=" * 60)
print("修改后配置（读回验证）")
print("=" * 60)
print(f"VID=0x{data2.VendorId:04x} PID=0x{data2.ProductId:04x}")
print(f"Manufacturer: {buf_mfr2.value.decode('ascii', errors='replace')}")
print(f"Description : {buf_desc2.value.decode('ascii', errors='replace')}")
print(f"SerialNumber: {buf_serial2.value.decode('ascii', errors='replace')}")
print(f"Port A: Mode=UART Driver={driver_str(data2.ADriverType)} (raw={data2.ADriverType})")
print(f"Port B: Mode=UART Driver={driver_str(data2.BDriverType)} (raw={data2.BDriverType})")
print("=" * 60)

# 11. 结果判断
if data2.ADriverType == 1 and data2.BDriverType == 0:
    print("\n[SUCCESS] 修改成功！")
    print("  Channel A = VCP (将生成 COM 口)")
    print("  Channel B = D2XX (Vivado JTAG 可用)")
    print("\n[NEXT] 让配置生效:")
    print("  1. 拔掉 Basys3 USB 线")
    print("  2. 等待 3 秒")
    print("  3. 重新插入 USB 线")
    print("  4. Windows 自动加载 VCP 驱动，生成 COM 端口")
    print("  5. 设备管理器 → '端口 (COM 和 LPT)' 确认有新 COM 口")
else:
    print(f"\n[FAILED] 验证失败:")
    print(f"  A={data2.ADriverType} (期望 1=VCP), B={data2.BDriverType} (期望 0=D2XX)")
    print("  可能需要用 FT_Prog 手动修改，或重新插拔后重试")
