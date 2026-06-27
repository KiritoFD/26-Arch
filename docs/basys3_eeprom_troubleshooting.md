# Basys3 EEPROM 问题排查与修复指南

> **问题描述**：Vivado 找不到 Basys3 开发板
> **可能原因**：EEPROM 配置错误、USB 驱动问题、USB 线缆问题
> **创建日期**：2026-06-27

---

## 一、问题诊断流程

### 1.1 检查设备管理器

**步骤**：
1. 打开 Windows 设备管理器（Win + X → 设备管理器）
2. 查看"通用串行总线控制器"或"端口 (COM 和 LPT)"

**预期结果**：
- 应该看到 **FTDI** 或 **Digilent** 相关设备
- 如果看到黄色感叹号：驱动问题
- 如果完全看不到：USB 连接或硬件问题

**设备名称参考**：
- `Digilent USB Device` (JTAG)
- `USB Serial Port (COMx)` (UART)
- `FT2232H` (FTDI 芯片)

---

### 1.2 检查 USB 连接

**步骤**：
1. 检查 USB 线缆是否插好
2. 尝试更换 USB 端口（优先使用 USB 2.0 端口）
3. 尝试更换 USB 线缆
4. 观察 Basys3 上的 LED 指示灯

**Basys3 LED 指示**：
- **POWER LED（绿色）**：应该常亮
- **DONE LED（绿色）**：FPGA 配置完成后亮起
- 如果 POWER LED 不亮：电源问题或 USB 供电不足

---

### 1.3 检查 Digilent Adept 驱动

**步骤**：
1. 打开命令提示符（管理员权限）
2. 运行：`digilent-adept-runtime --version`

**预期结果**：
```
digilent-adept-runtime version 2.x.x
```

**如果命令不存在**：
- 需要安装 Digilent Adept Runtime
- 下载地址：https://digilent.com/shop/software/digilent-adept/

**重新安装驱动**：
1. 下载 Digilent Adept Runtime
2. 安装时选择"Install Drivers"
3. 重启计算机

---

### 1.4 检查 Vivado Hardware Manager

**步骤**：
1. 打开 Vivado
2. 点击"Open Hardware Manager"
3. 点击"Open target" → "Auto Connect"

**预期结果**：
- 应该看到设备：`xc7a35t_0`

**如果找不到设备**：
1. 点击"Open target" → "Open New Hardware Target"
2. 手动选择 JTAG 电缆
3. 如果仍然找不到：可能是 EEPROM 配置问题

---

## 二、EEPROM 配置问题

### 2.1 EEPROM 配置说明

**Basys3 使用 FT2232H 双通道 USB 芯片**：
- **Channel A**：UART 通信（COM 口）
- **Channel B**：JTAG 编程（Vivado 使用）

**EEPROM Word 3 配置**：
```
Bit 0-2: Channel A type
  0 = UART/VCP
  4 = FIFO/D2XX

Bit 8-10: Channel B type
  0 = UART/VCP
  7 = FIFO/D2XX (JTAG)
```

**正确配置**：
- Channel A: UART/VCP (type = 0)
- Channel B: FIFO/D2XX (type = 7)
- Word 3 = `0x0700`

**错误配置示例**：
- Word 3 = `0x0000` → Channel B 也是 UART，Vivado 找不到 JTAG

---

### 2.2 EEPROM 备份文件

**当前可用备份**：

| 文件路径 | 时间 | 说明 |
|---------|------|------|
| `sim/eeprom_backups/eeprom_backup_20260627_072124.bin` | 2026-06-27 07:21 | 最新备份（完整 512 字节） |
| `sim/eeprom_backups/eeprom_backup_latest.bin` | 2026-06-27 07:21 | 最新备份副本 |
| `eeprom_dump_current.bin` | 2026-06-27 07:21 | 当前 EEPROM 内容 |
| `eeprom_backup_before_restore.bin` | 2026-06-27 03:43 | 恢复前备份（256 字节） |

**推荐使用**：
- `sim/eeprom_backups/eeprom_backup_20260627_072124.bin`（最新完整备份）

---

### 2.3 EEPROM 修复脚本

**可用脚本**：

| 脚本路径 | 功能 | 使用场景 |
|---------|------|---------|
| `sim/restore_eeprom_full.py` | 完整恢复 EEPROM | EEPROM 配置完全错误 |
| `tools/fix_eeprom_all.py` | 修复所有 EEPROM 配置 | 批量修复 |
| `tools/restore_ftdi_eeprom.py` | 使用 FTDI API 恢复 | D2XX 驱动可用 |
| `sim/fix_eeprom.py` | 基本修复脚本 | 简单修复 |

---

## 三、修复步骤

### 3.1 方案一：使用现有修复脚本（推荐）

**前提条件**：
- Python 3.x 已安装
- FTDI D2XX 驱动已安装（或使用 libusb 方式）

**步骤**：

**1. 检查当前 EEPROM 配置**：
```bash
cd G:\GitHub\26-Arch\sim
python read_eeprom_full.py
```

**预期输出**：
```
Word 3: 0x0700
  Channel A type: 0 (UART/VCP)
  Channel B type: 7 (FIFO/D2XX - JTAG)
```

**如果输出不是上述内容**，继续下一步。

---

**2. 备份当前 EEPROM**：
```bash
python backup_eeprom_full.py
```

**输出**：
```
Backup saved to eeprom_backups/eeprom_backup_YYYYMMDD_HHMMSS.bin
```

---

**3. 恢复 EEPROM 配置**：

**方法 A：使用完整备份恢复**：
```bash
python restore_eeprom_full.py sim/eeprom_backups/eeprom_backup_20260627_072124.bin
```

**方法 B：使用修复脚本**：
```bash
python fix_eeprom.py
```

**输出**：
```
Writing new EEPROM word 3...
EEPROM write successful!
Verification - word 3: 0x0700
  Channel A type: 0 (UART/VCP)
  Channel B type: 7 (FIFO/D2XX - JTAG)

Done! Please unplug and replug the Basys3 USB cable.
```

---

**4. 重新插拔 USB 线缆**：
- 拔掉 Basys3 的 USB 线
- 等待 3 秒
- 重新插入 USB 线

---

**5. 验证修复结果**：
```bash
# 再次检查 EEPROM
python read_eeprom_full.py

# 检查设备管理器
# 应该看到 Digilent USB Device 和 USB Serial Port

# 在 Vivado 中连接
# Open Hardware Manager → Auto Connect
```

---

### 3.2 方案二：重新安装 Digilent 驱动

**步骤**：

**1. 卸载现有驱动**：
- 打开设备管理器
- 找到 Digilent/FTDI 设备
- 右键 → 卸载设备
- 勾选"删除驱动软件"

**2. 安装 Digilent Adept Runtime**：
- 下载：https://digilent.com/shop/software/digilent-adept/
- 安装时选择"Install Drivers"
- 重启计算机

**3. 重新插拔 USB**：
- 拔掉 Basys3 USB
- 重启后重新插入

**4. 验证**：
- 设备管理器应该显示 Digilent 设备
- Vivado 应该能找到设备

---

### 3.3 方案三：使用 FT_Prog 工具（FTDI 官方工具）

**步骤**：

**1. 下载 FT_Prog**：
- 官网：https://ftdichip.com/utilities/
- 下载 FT_Prog（FTDI EEPROM Programming Utility）

**2. 打开 FT_Prog**：
- 以管理员权限运行
- 点击"Scan"扫描设备

**3. 查看当前配置**：
- 应该看到 FT2232H 设备
- 查看 Channel A 和 Channel B 配置

**4. 修改配置**：
- Channel A: UART/VCP
- Channel B: FIFO/D2XX
- 点击"Program"写入 EEPROM

**5. 重新插拔 USB**：
- 拔掉 USB 线
- 等待 3 秒
- 重新插入

---

## 四、常见问题与解决方案

### 4.1 问题：设备管理器中看到设备，但 Vivado 找不到

**可能原因**：
- EEPROM Channel B 配置错误（设置为 UART 而非 FIFO）
- Vivado 驱动版本不匹配

**解决方案**：
1. 使用方案一修复 EEPROM 配置
2. 确保 Vivado 版本 >= 2017.4
3. 重新安装 Digilent 驱动

---

### 4.2 问题：设备管理器中看不到任何设备

**可能原因**：
- USB 线缆问题
- USB 端口问题
- 硬件损坏

**解决方案**：
1. 更换 USB 线缆（使用质量好的线缆）
2. 更换 USB 端口（尝试 USB 2.0 端口）
3. 检查 Basys3 的 POWER LED 是否亮起
4. 尝试在其他电脑上测试

---

### 4.3 问题：看到黄色感叹号（驱动问题）

**可能原因**：
- 驱动未安装或损坏
- 驱动版本不兼容

**解决方案**：
1. 卸载设备驱动
2. 重新安装 Digilent Adept Runtime
3. 重启计算机

---

### 4.4 问题：EEPROM 写入失败

**可能原因**：
- FTDI D2XX 驱动未安装
- 权限不足
- EEPROM 损坏

**解决方案**：

**1. 安装 FTDI D2XX 驱动**：
- 下载：https://ftdichip.com/drivers/d2xx-drivers/
- 选择 Windows 版本
- 安装后重启

**2. 以管理员权限运行**：
```bash
# 以管理员权限打开 PowerShell
python restore_eeprom_full.py sim/eeprom_backups/eeprom_backup_20260627_072124.bin
```

**3. 使用 libusb 方式**（如果 D2XX 失败）：
```bash
python fix_eeprom_libusb.py
```

---

### 4.5 问题：修复后仍然找不到设备

**可能原因**：
- EEPROM 损坏
- FT2232H 芯片损坏
- JTAG 电路问题

**解决方案**：

**1. 尝试多次修复**：
- 有时 EEPROM 需要多次写入才能成功
- 重复执行修复脚本 2-3 次

**2. 使用 FT_Prog 工具**：
- FT_Prog 可以更底层地访问 EEPROM
- 尝试使用 FT_Prog 恢复配置

**3. 硬件检测**：
- 如果多次修复失败，可能是硬件问题
- 联系 Digilent 技术支持或更换板子

---

## 五、预防措施

### 5.1 EEPROM 备份策略

**建议**：
1. **定期备份**：每次修改 EEPROM 前备份
2. **多份备份**：保存多个时间点的备份
3. **文档记录**：记录每次修改的原因和内容

**备份命令**：
```bash
cd G:\GitHub\26-Arch\sim
python backup_eeprom_full.py
```

---

### 5.2 避免误操作

**注意事项**：
1. 不要随意修改 EEPROM 配置
2. 使用 Vivado 时不要强制断开 USB
3. 避免同时使用多个 JTAG 工具
4. 不要在 EEPROM 写入过程中断电

---

### 5.3 驱动管理

**建议**：
1. 保持 Digilent Adept Runtime 更新
2. 保持 Vivado 更新
3. 不要混用不同版本的驱动
4. 定期检查设备管理器中的设备状态

---

## 六、快速参考

### 6.1 EEPROM 配置速查

| Word 3 值 | Channel A | Channel B | 说明 |
|----------|-----------|-----------|------|
| `0x0700` | UART/VCP | FIFO/D2XX | ✓ 正确配置 |
| `0x0000` | UART/VCP | UART/VCP | ✗ Vivado 找不到 |
| `0x0004` | FIFO/D2XX | UART/VCP | ✗ 通道反转 |
| `0x0704` | FIFO/D2XX | FIFO/D2XX | ✗ 无 UART |

---

### 6.2 常用命令速查

```bash
# 检查 EEPROM
python read_eeprom_full.py

# 备份 EEPROM
python backup_eeprom_full.py

# 恢复 EEPROM
python restore_eeprom_full.py sim/eeprom_backups/eeprom_backup_20260627_072124.bin

# 修复 EEPROM
python fix_eeprom.py

# 使用 libusb 修复
python fix_eeprom_libusb.py
```

---

### 6.3 设备信息速查

**Basys3 规格**：
- FPGA: Artix-7 XC7A35T
- USB 芯片: FT2232H (双通道)
- Serial Number: 210183A8A984
- VID: 0x0403 (FTDI)
- PID: 0x6010 (FT2232H)

**正确设备名称**：
- 设备管理器：`Digilent USB Device`, `USB Serial Port (COMx)`
- Vivado：`xc7a35t_0`

---

## 七、故障排查清单

**按顺序检查**：

- [ ] **1. USB 连接**：POWER LED 是否亮起？
- [ ] **2. 设备管理器**：是否看到 Digilent/FTDI 设备？
- [ ] **3. 驱动状态**：是否有黄色感叹号？
- [ ] **4. EEPROM 配置**：Word 3 是否为 `0x0700`？
- [ ] **5. Vivado 连接**：Hardware Manager 能否连接？
- [ ] **6. JTAG 测试**：能否识别 FPGA (`xc7a35t_0`)？

**如果所有检查都通过**：
- 问题已解决

**如果某一步失败**：
- 参考对应的解决方案章节

---

## 八、联系支持

**如果所有方案都失败**：

1. **Digilent 技术支持**：
   - 官网：https://digilent.com/support/
   - 论坛：https://reference.digilentinc.com/discuss

2. **FTDI 技术支持**：
   - 官网：https://ftdichip.com/support/
   - 邮件：support@ftdichip.com

3. **Xilinx 论坛**：
   - https://forums.xilinx.com/

**提供信息**：
- Basys3 序列号
- Vivado 版本
- 操作系统版本
- 设备管理器截图
- EEPROM 备份文件
- 已尝试的修复步骤

---

**文档版本**：v1.0
**最后更新**：2026-06-27
**维护者**：CPU 优化实验团队
