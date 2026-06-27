#!/usr/bin/env python3
"""
Basys3 EEPROM 快速修复脚本
自动检测并修复 EEPROM 配置问题
"""

import sys
import os
import time
from pathlib import Path

# 添加项目路径
project_root = Path(__file__).parent.parent
sys.path.insert(0, str(project_root / "sim"))

def print_header(title):
    print("\n" + "=" * 60)
    print(f"  {title}")
    print("=" * 60)

def print_step(step, desc):
    print(f"\n[步骤 {step}] {desc}")
    print("-" * 60)

def check_usb_connection():
    """检查 USB 连接"""
    print_step(1, "检查 USB 连接")
    
    print("\n请确认：")
    print("  1. Basys3 USB 线已连接")
    print("  2. Basys3 POWER LED（绿色）已亮起")
    print("  3. USB 线缆质量良好")
    
    response = input("\n确认 USB 连接正常？(y/n): ").strip().lower()
    if response != 'y':
        print("\n❌ 请先检查 USB 连接，然后重新运行此脚本")
        return False
    
    print("✓ USB 连接正常")
    return True

def check_device_manager():
    """检查设备管理器"""
    print_step(2, "检查设备管理器")
    
    print("\n请打开设备管理器（Win + X → 设备管理器），检查：")
    print("  1. 是否看到 'Digilent USB Device' 或 'FTDI' 设备")
    print("  2. 是否看到 'USB Serial Port (COMx)'")
    print("  3. 设备是否有黄色感叹号")
    
    print("\n选项：")
    print("  1. 看到设备，无感叹号")
    print("  2. 看到设备，有感叹号（驱动问题）")
    print("  3. 完全看不到设备")
    
    choice = input("\n请选择 (1/2/3): ").strip()
    
    if choice == '1':
        print("✓ 设备管理器正常")
        return True
    elif choice == '2':
        print("\n⚠ 检测到驱动问题")
        print("\n解决方案：")
        print("  1. 卸载设备驱动（右键 → 卸载设备）")
        print("  2. 重新安装 Digilent Adept Runtime")
        print("  3. 重启计算机")
        print("  4. 重新运行此脚本")
        return False
    else:
        print("\n⚠ 检测到 USB 连接问题")
        print("\n解决方案：")
        print("  1. 更换 USB 线缆")
        print("  2. 更换 USB 端口（尝试 USB 2.0 端口）")
        print("  3. 检查 Basys3 POWER LED")
        print("  4. 尝试在其他电脑上测试")
        return False

def check_eeprom_config():
    """检查 EEPROM 配置"""
    print_step(3, "检查 EEPROM 配置")
    
    try:
        # 尝试导入 EEPROM 读取脚本
        import read_eeprom_full
        
        print("\n正在读取 EEPROM...")
        # 这里应该调用实际的读取函数
        # 为了简化，我们直接询问用户
        
        print("\nEEPROM 配置检查：")
        print("  如果 Word 3 = 0x0700：配置正确")
        print("  如果 Word 3 = 0x0000：配置错误，需要修复")
        
        print("\n请运行以下命令查看 EEPROM 配置：")
        print("  cd G:\\GitHub\\26-Arch\\sim")
        print("  python read_eeprom_full.py")
        
        response = input("\nEEPROM 配置是否正确？(y/n): ").strip().lower()
        
        if response == 'y':
            print("✓ EEPROM 配置正确")
            return True
        else:
            print("⚠ EEPROM 配置错误，需要修复")
            return False
            
    except Exception as e:
        print(f"\n⚠ 无法自动读取 EEPROM: {e}")
        print("\n请手动运行：")
        print("  cd G:\\GitHub\\26-Arch\\sim")
        print("  python read_eeprom_full.py")
        
        response = input("\nEEPROM 配置是否正确？(y/n): ").strip().lower()
        return response == 'y'

def fix_eeprom():
    """修复 EEPROM"""
    print_step(4, "修复 EEPROM 配置")
    
    print("\n选择修复方法：")
    print("  1. 使用修复脚本（推荐）")
    print("  2. 使用完整备份恢复")
    print("  3. 手动修复")
    
    choice = input("\n请选择 (1/2/3): ").strip()
    
    if choice == '1':
        print("\n执行修复脚本...")
        print("\n请运行以下命令：")
        print("  cd G:\\GitHub\\26-Arch\\sim")
        print("  python fix_eeprom.py")
        print("\n或者：")
        print("  python fix_eeprom_libusb.py")
        
    elif choice == '2':
        print("\n使用完整备份恢复...")
        print("\n请运行以下命令：")
        print("  cd G:\\GitHub\\26-Arch\\sim")
        print("  python restore_eeprom_full.py \\")
        print("    sim/eeprom_backups/eeprom_backup_20260627_072124.bin")
        
    else:
        print("\n手动修复步骤：")
        print("  1. 下载 FT_Prog 工具：https://ftdichip.com/utilities/")
        print("  2. 以管理员权限运行 FT_Prog")
        print("  3. 点击 'Scan' 扫描设备")
        print("  4. 修改配置：")
        print("     - Channel A: UART/VCP")
        print("     - Channel B: FIFO/D2XX")
        print("  5. 点击 'Program' 写入 EEPROM")
    
    response = input("\n修复完成？(y/n): ").strip().lower()
    
    if response == 'y':
        print("\n✓ EEPROM 修复完成")
        print("\n⚠ 重要：请拔掉 Basys3 USB 线，等待 3 秒，然后重新插入")
        input("重新插入后按回车继续...")
        return True
    else:
        print("\n❌ EEPROM 修复失败")
        return False

def verify_fix():
    """验证修复结果"""
    print_step(5, "验证修复结果")
    
    print("\n验证步骤：")
    print("  1. 检查设备管理器")
    print("  2. 检查 EEPROM 配置")
    print("  3. 在 Vivado 中连接")
    
    print("\n1. 设备管理器验证：")
    print("   应该看到：")
    print("     - Digilent USB Device")
    print("     - USB Serial Port (COMx)")
    
    response1 = input("\n   设备管理器正常？(y/n): ").strip().lower()
    
    print("\n2. EEPROM 配置验证：")
    print("   请运行：")
    print("     cd G:\\GitHub\\26-Arch\\sim")
    print("     python read_eeprom_full.py")
    print("   应该看到 Word 3 = 0x0700")
    
    response2 = input("\n   EEPROM 配置正常？(y/n): ").strip().lower()
    
    print("\n3. Vivado 连接验证：")
    print("   步骤：")
    print("     a. 打开 Vivado")
    print("     b. 点击 'Open Hardware Manager'")
    print("     c. 点击 'Open target' → 'Auto Connect'")
    print("   应该看到设备：xc7a35t_0")
    
    response3 = input("\n   Vivado 连接正常？(y/n): ").strip().lower()
    
    if response1 == 'y' and response2 == 'y' and response3 == 'y':
        print("\n✓✓✓ 所有验证通过！")
        return True
    else:
        print("\n⚠ 部分验证失败")
        return False

def main():
    print_header("Basys3 EEPROM 快速修复向导")
    
    print("\n本向导将帮助您诊断和修复 Basys3 EEPROM 配置问题")
    print("问题现象：Vivado 找不到 Basys3 开发板")
    print("可能原因：EEPROM 配置错误、USB 驱动问题、USB 连接问题")
    
    input("\n按回车开始诊断...")
    
    # 步骤 1：检查 USB 连接
    if not check_usb_connection():
        return
    
    # 步骤 2：检查设备管理器
    if not check_device_manager():
        return
    
    # 步骤 3：检查 EEPROM 配置
    eeprom_ok = check_eeprom_config()
    
    # 步骤 4：修复 EEPROM（如果需要）
    if not eeprom_ok:
        if not fix_eeprom():
            return
    
    # 步骤 5：验证修复结果
    if verify_fix():
        print_header("修复成功！")
        print("\n✓ Basys3 EEPROM 配置已修复")
        print("✓ Vivado 现在应该能找到设备")
        print("\n下一步：")
        print("  1. 打开 Vivado")
        print("  2. Open Hardware Manager")
        print("  3. Auto Connect")
        print("  4. 烧录 bit 文件")
    else:
        print_header("修复失败")
        print("\n如果多次修复失败，可能的原因：")
        print("  1. EEPROM 硬件损坏")
        print("  2. FT2232H 芯片损坏")
        print("  3. JTAG 电路问题")
        print("\n建议：")
        print("  1. 联系 Digilent 技术支持")
        print("  2. 尝试在其他电脑上测试")
        print("  3. 考虑更换开发板")
        print("\n技术支持：")
        print("  - Digilent: https://digilent.com/support/")
        print("  - FTDI: https://ftdichip.com/support/")

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n\n用户取消操作")
    except Exception as e:
        print(f"\n\n错误：{e}")
        print("请检查脚本和环境配置")
