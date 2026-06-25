# Basys3 上板调试日志

## 2026-06-25 调试记录

### 15:45 状态总结
- 比特流已成功生成 (2.1MB, 0 DRC errors)
- JTAG烧写成功 (End of startup status: HIGH)
- 串口无输出 (COM4/COM20均无数据)

### 根因分析
1. **standalone UART test使用dbg_cpu_clk** — 如果PLL未锁定，cpu_clk无时钟，test无法运行
2. **SW0控制RsTx选择** — SW0=0时RsTx=cpu_tx(依赖CPU运行)，SW0=1时RsTx=uart_test_tx
3. 即使SW0=1，uart_test_tx也依赖dbg_cpu_clk，PLL未锁定则无法工作

### 修复方案
- 将standalone UART test改为使用100MHz原始clk，不依赖PLL
- 强制RsTx=uart_test_tx，绕过SW0选择
- 100MHz下BIT_TMR_MAX = 100000000/115200 - 1 = 867
- 100MHz下发送间隔 = 10000000 cycles = 100ms

### 构建状态
- 修改已写入 basys3_top.sv
- Vivado构建两次卡住，需要清理后重试
