"""
FT2232H EEPROM 修改脚本（使用 ftd2xx Python 包）
修改 Channel A: AIsVCP 0→1 (启用 VCP，生成 COM 口)
Channel B 保持 BIsVCP=0 (D2XX，给 Vivado JTAG)
"""
import ftd2xx
import json
import os
from datetime import datetime

def driver_str(vcp):
    return "VCP(COM)" if vcp else "D2XX"

def print_config(data, label):
    print(f"\n{'=' * 60}")
    print(f"{label}")
    print(f"{'=' * 60}")
    print(f"VID=0x{data.VendorId:04x} PID=0x{data.ProductId:04x}")
    print(f"Manufacturer: {data.Manufacturer.decode('ascii', errors='replace') if data.Manufacturer else ''}")
    print(f"Description : {data.Description.decode('ascii', errors='replace') if data.Description else ''}")
    print(f"SerialNumber: {data.SerialNumber.decode('ascii', errors='replace') if data.SerialNumber else ''}")
    print(f"MaxPower    : {data.MaxPower} (×2mA = {data.MaxPower*2}mA)")
    print(f"SerNumEnable: {data.SerNumEnable}")
    print(f"Port A: AIsVCP={data.AIsVCP} Driver={driver_str(data.AIsVCP)}")
    print(f"Port B: BIsVCP={data.BIsVCP} Driver={driver_str(data.BIsVCP)}")
    print(f"Port A: IFAIsFifo={data.IFAIsFifo} IFAIsFastSer={data.IFAIsFastSer}")
    print(f"Port B: IFBIsFifo={data.IFBIsFifo} IFBIsFastSer={data.IFBIsFastSer}")
    print(f"{'=' * 60}")

# ============================================================
# 1. 枚举设备
# ============================================================
devices = ftd2xx.listDevices()
if not devices:
    print("[ERROR] No FTDI devices found")
    exit(1)
print(f"[INFO] Found {len(devices)} FTDI device(s): {devices}")

# ============================================================
# 2. 打开 channel 1（B，D2XX 模式可靠打开）
# ============================================================
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

# ============================================================
# 3. 读取当前 EEPROM 配置
# ============================================================
try:
    data = dev.eeRead()
except Exception as e:
    print(f"[ERROR] eeRead failed: {e}")
    dev.close()
    exit(1)

print_config(data, "修改前配置")

# ============================================================
# 4. 备份
# ============================================================
backup_dir = r"g:\GitHub\26-Arch\eeprom_backup"
os.makedirs(backup_dir, exist_ok=True)
ts = datetime.now().strftime("%Y%m%d_%H%M%S")
backup_path = os.path.join(backup_dir, f"eeprom_pre_modify_pkg_{ts}.json")
backup_data = {
    "backup_time": ts,
    "VendorId": f"0x{data.VendorId:04x}",
    "ProductId": f"0x{data.ProductId:04x}",
    "Manufacturer": data.Manufacturer.decode('ascii', errors='replace') if data.Manufacturer else "",
    "Description": data.Description.decode('ascii', errors='replace') if data.Description else "",
    "SerialNumber": data.SerialNumber.decode('ascii', errors='replace') if data.SerialNumber else "",
    "MaxPower": data.MaxPower,
    "AIsVCP": data.AIsVCP,
    "BIsVCP": data.BIsVCP,
    "IFAIsFifo": data.IFAIsFifo,
    "IFBIsFifo": data.IFBIsFifo,
    "SerNumEnable": data.SerNumEnable,
}
with open(backup_path, "w", encoding="utf-8") as f:
    json.dump(backup_data, f, indent=2, ensure_ascii=False)
print(f"\n[OK] Pre-modify backup: {backup_path}")

# ============================================================
# 5. 修改 Channel A: 启用 VCP
# ============================================================
if data.AIsVCP:
    print("[INFO] Channel A 已经是 VCP，无需修改")
    dev.close()
    exit(0)

old_a = data.AIsVCP
data.AIsVCP = 1  # 启用 VCP，生成 COM 口
print(f"\n[PLAN] Channel A: AIsVCP {old_a} → {data.AIsVCP} (D2XX → VCP)")
print(f"[PLAN] Channel B: BIsVCP={data.BIsVCP} (不变)")

# ============================================================
# 6. 写入 EEPROM
# ============================================================
print("\n[WRITE] 正在写入 EEPROM...")
try:
    dev.eeProgram(data)
    print("[OK] eeProgram 成功")
except Exception as e:
    print(f"[ERROR] eeProgram failed: {e}")
    dev.close()
    exit(1)

# ============================================================
# 7. 读回验证
# ============================================================
print("\n[VERIFY] 读回验证...")
try:
    data2 = dev.eeRead()
except Exception as e:
    print(f"[ERROR] 读回失败: {e}")
    dev.close()
    exit(1)

dev.close()

print_config(data2, "修改后配置（读回）")

# ============================================================
# 8. 结果判断
# ============================================================
if data2.AIsVCP == 1 and data2.BIsVCP == 0:
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
    print(f"  AIsVCP={data2.AIsVCP} (期望 1), BIsVCP={data2.BIsVCP} (期望 0)")
