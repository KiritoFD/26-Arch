# xv6 FPGA 上板调试计划

## 当前状态

### 已完成
- 核心bug已修复：UART寄存器rdata byte lane（LSR/IER/ISR/LCR值现在放在正确的byte位置）
- disk_data临时移除（LUT超限），后续用BRAM实现
- bitstream已编译成功（0错误0警告）
- 新增LED3 = any_device_write

### 当前LED映射
- LED0 = clk_locked
- LED1 = device_valid（CPU访问设备）
- LED2 = cpu_tx_write（CPU写UART THR）
- LED3 = any_device_write（CPU写任何设备寄存器）

### SW0
- SW0=1: RsTx = standalone测试（发'A'）
- SW0=0: RsTx = cpu_tx（CPU UART输出）

### 关键代码路径
- CPU写THR: `wdata`已按addr[2:0]左移到正确byte lane（core_execute.sv L119: `mem_store_data_shifted`），`wstrobe`也已左移（L111-114）
- device.sv `tx_write_byte`用wstrobe从wdata提取字节（L41-53），这是正确的
- CPU读LSR: rdata = `{16'b0, 8'h60, 40'b0}`（byte 5），CPU右移addr[2:0]*8=40位后得到0x60，THRE=1 ✓
- cbus_crossbar: addr[31]=1→RAM, addr[31]=0→Device

### 潜在风险点
1. **cbus_crossbar用addr（非锁存）选择rdata** — CBusArbiter锁存请求后addr可能变化，但crossbar的rdata/ready/last选择用的是组合逻辑addr，如果CPU发起新请求时addr变了，可能读到错误数据
2. **mtime增长太慢** — 每25个cpu_clk周期+1，25MHz下约1MHz，xv6期望1MHz CLINT，应该OK
3. **BRAM范围** — 164KB = 0x80000000~0x80029000，xv6 kernel约80KB，但运行时可能访问超出范围

## 调试步骤

### Step 1: 烧写bitstream，SW0=OFF，观察LED和串口
- 烧写 `G:\GitHub\26-Arch\vivado\test-cpu\project\project_3\project_3.runs\impl_1\basys3_top.bit`
- SW0=OFF（RsTx=cpu_tx）
- 打开串口终端 COM4 115200
- 观察LED：
  - LED0亮 = clk_locked ✓
  - LED1微亮 = CPU偶尔访问设备 ✓
  - LED2亮/微亮 = CPU写THR（之前灭，修复后应亮）✓
  - LED3微亮 = CPU写设备寄存器（LCR/IER等）✓
- 串口应显示xv6启动信息

### Step 2: 如果串口有输出但乱码
- 检查波特率：device.sv BIT_TMR_MAX=216，25MHz/216≈115740，偏差0.5%以内应该OK
- 检查数据位/停止位：10位（1起始+8数据+1停止），标准

### Step 3: 如果LED2仍灭（CPU仍不写THR）
- 可能CPU卡在更早的位置
- 需要添加更多调试信号：捕获CPU读设备时的rdata值
- 或者添加PC采样到LED

### Step 4: 如果串口有输出但卡在磁盘读取
- disk_data已移除，xv6读磁盘会得到0
- 需要实现disk_data BRAM + disk_bridge.py
- 但xv6应该先打印启动信息再读磁盘

### Step 5: 实现disk_data BRAM（如果UART输出正常）
- 用Xilinx BRAM IP替代分布式RAM
- 256x32bit = 1KB，用1个BRAM36即可
- 修改device.sv：添加BRAM实例，CPU读/写disk_data走BRAM端口
- disk_bridge.py：PC端串口桥接程序

### Step 6: 如果cbus_crossbar的addr选择有问题
- cbus_crossbar用组合逻辑addr选择rdata源
- 当CBusArbiter锁存请求后，CPU可能改变addr
- 需要在crossbar中锁存addr，用锁存后的addr选择rdata

## 文件修改清单

### 必要修改（Step 1-4调试阶段）
- 无代码修改，纯烧写+观察

### 可能需要的修改
1. `device.sv` — 如果需要更多调试信号
2. `cbus_crossbar.sv` — 如果需要锁存addr
3. `device.sv` — 添加disk_data BRAM（Step 5）
4. `basys3_top.sv` — 调整LED映射

## 验证标准
- LED2亮/微亮 = CPU写UART THR
- 串口显示xv6启动信息（至少"hart 1 starting"或"printf"输出）
- 最终目标：shell提示符
