# xv6 Main Track Progress

## Goal

Run xv6 on the current CPU in the difftest-based simulation environment, without diff checking, until the kernel can enter user space and reach the shell.

## Current Baseline

The following pieces are now in place:

- A local xv6 source tree exists at `third_party/xv6-riscv`.
- The WSL toolchain `gcc-riscv64-unknown-elf` and `binutils-riscv64-unknown-elf` are installed and can build xv6.
- The top-level `Makefile` now provides:
  - `build-xv6`
  - `test-xv6`
- `difftest` now accepts the disk image path at runtime through the `SDCARD_IMAGE` environment variable.
- The simulation-side UART compatibility path for xv6's `UART0=0x10000000` has been added.

Current observable result:

```text
xv6 kernel is booting
init: starting sh
$$
```

This confirms:

- the xv6 kernel image is loaded correctly at `0x80000000`
- the CPU can execute the early machine-mode and supervisor-mode boot path
- the ISA mismatch caused by xv6's default `rv64gc` target has been removed
- the UART compatibility layer is working well enough for kernel boot prints
- the first user process (`/init`) starts and runs its console setup path
- the shell process is launched and reaches the prompt
- the UART/MMIO write path is clean enough that the visible shell output is no longer duplicated

With the current bring-up branch, the boot path has progressed further:

- kernel init now advances through `kinit`, `kvminit`, `procinit`, `trapinit`, `binit`, `iinit`, `fileinit`, and `userinit`
- the first scheduled process reaches `forkret`
- `fsinit(ROOTDEV)` reads the xv6 superblock successfully through the MMIO disk path
- `prepare_return -> sret -> usertrap` is active and stable enough for `/init` and `sh`

## Source Changes Already Made

### Build / integration

- Added `build-xv6` and `test-xv6` targets to the repo `Makefile`
- Cloned upstream xv6 into `third_party/xv6-riscv`

### Toolchain / ISA compatibility

- Changed xv6 build flags from `rv64gc` to `rv64im_zicsr_zifencei`
- Added `-mabi=lp64`

### Single-core lock workaround

- Replaced xv6's `__atomic_exchange_n` / `__atomic_store_n` based spinlock implementation with a single-core version that relies on `push_off/pop_off` and plain load/store

### Simulation-side UART compatibility

- Added a minimal 16550-style UART compatibility model in `difftest/src/test/vsrc/common/ram.sv`
- Fixed byte-lane placement for byte MMIO reads so xv6's `lbu` from `UART0+5` sees `LSR_TX_IDLE`
- Avoided treating baud-rate setup writes as character output by honoring the DLAB bit

### MMIO disk path

- Added a simple disk block register at `VIRTIO0 + 0x000`
- Added a ready/status register at `VIRTIO0 + 0x008`
- Added a 1KB data window starting at `VIRTIO0 + 0x100`
- Backed the disk image with a host-side in-memory buffer loaded from `SDCARD_IMAGE`
- Added synchronous block reads and writes for xv6's `bread` / log traffic

### Supervisor-mode bring-up

- Added initial `sret` decode plumbing
- Added partial Supervisor CSR storage and delegation handling in the CPU
- Verified that `prepare_return()` writes `stvec` and `sepc`, and that `sret` executes
- Verified that user-mode `ecall` already traps back into the kernel (`scause = 8`)

## Current Status

The main xv6 shell bring-up path is working.

Open work remains outside the narrow main-track milestone:

1. clean up temporary bring-up shortcuts and logging where still present
2. harden Supervisor CSR and MMU behavior if stricter architectural correctness is required
3. continue with the later `labplus` items: branch prediction / performance, atomics, and PMP

## 上板 (FPGA)

- Vivado project: vivado/lab5_project/
- Bitstream: vivado/lab5_project/lab5_project.runs/impl_1/basys3_top.bit
- 上板方法：在 Windows 下通过 Vivado 硬件管理器连接板子
- 板子已识别为 xilinx_tcf/Xilinx/00001177d4a601
- 参考文档：wiki/上板.md

### Windows 上板步骤

1. 用 USB 连接板子
2. 在 Windows 下打开 Vivado Hardware Manager
3. Open Target → Auto Connect
4. 选择 xilinx_tcf/Xilinx/00001177d4a601
5. Program Device → 选择 bit 文件路径：
   G:\GitHub\26-Arch\vivado\lab5_project\lab5_project.runs\impl_1\basys3_top.bit
6. Program 后板子自动运行

## Next Step

Use this xv6 path as the stable baseline for any later work that depends on Supervisor mode, filesystem access, or user-space execution.

---

## FPGA 上板调试日志 (2026-06-26)

### 问题：xv6 在 FPGA 上无 UART 输出

仿真（difftest）已稳定进入 shell，但烧到 FPGA 后 CPU 无 UART 输出。

### 根因 1：Vivado imports 副本严重过期

Vivado 工程通过 `$PSRCDIR/sources_1/imports/...` 引用源文件副本，而不是源文件本身。
综合时使用 imports 副本，导致源文件修改对综合结果**不可见**。

发现 imports 副本中的 `basys3_top.sv` 是**完全过时的旧版本**：

- 旧 imports 副本：实现的是"Standalone UART TX test"（每 100ms 发送 'A'），**没有 jtag_uart bridge**
- 当前源文件：实现了完整的 JTAG UART bridge（BSCANE2 USER1/USER2），CPU UART TX 通过 JTAG 读取

旧 imports 副本的 LED 定义与源文件完全不同：
- 旧 LED0 = `dbg_clk_locked`（不是 blink！）
- 旧 LED1 = `dbg_lsr_read`（CPU 读过 LSR）
- 旧 LED2 = `dbg_cpu_tx_write`（live 信号）
- 旧 LED3 = `dbg_lsr_rdata[45]`（THRE bit）

这解释了之前 JTAG UART 读取 0 字节的现象——**bitstream 中根本没有 jtag_uart 模块**！

#### 修复

用源文件覆盖所有 imports 副本：
- `basys3_top.sv`
- `soc_top.sv`
- `bram_wrapper.sv`
- `cbus_crossbar.sv`
- `device.sv`
- `device.svh`

### 根因 2：jtag_uart.sv BSCANE2 多重驱动错误

综合新 imports 副本时，BSCANE2 USER1 的 `user1_shift_reg` 被两个 `always_ff @(posedge user1_tck)` 块驱动，触发 DRC MDRV-1 错误：

```text
ERROR: [DRC MDRV-1] Multiple Driver Nets: Net jtag_uart_inst/user1_tdo has multiple drivers
```

#### 修复

将 CAPTURE_DR 和 SHIFT_DR 两个 always 块合并为一个，用 if-else if 分支：

```systemverilog
always_ff @(posedge user1_tck) begin
    if (user1_sel) begin
        if (user1_capture) begin
            // latch FIFO output
        end else if (user1_shift) begin
            // shift out
        end
    end
end
```

### 验证进展

修复后重新综合 + 实现 + bitstream 成功（0 Errors）。

JTAG 加载新 bitstream 后：

- LED0 闪烁（FPGA 存活）✓
- LED1 亮（PLL locked）✓
- **LED2 亮（CPU 写过 UART）** ✓✓✓ — 这是**首次**观察到 CPU 到达 consoleinit() 并写 UART！
- LED3 亮（CPU 读过 device）

但 JTAG UART 读取仍为 0 字节。怀疑 jtag_uart 的 TX FIFO 没捕获到串行数据，
或 LED2 仅反映"写过 UART 寄存器"（含 LCR/IER/FCR 配置），不代表有 THR 数据字节。

### 下一步诊断

将 LED3 改为显示 `jtag_tx_avail`（jtag_uart TX FIFO 非空），用以判断是否捕获到串行数据。

- 若 LED3 亮 → jtag_uart 捕获成功，问题在 JTAG 时钟域或 BSCANE2 协议
- 若 LED3 灭 → jtag_uart 捕获失败，需检查 device.sv 的 UART TX 波特率与 jtag_uart 的采样逻辑

### 深入诊断结果 (2026-06-26 凌晨)

#### device.sv UART TX 状态机完全正常

通过逐级添加调试信号验证：

1. **`dbg_ever_thr_write`**（真正写 THR 数据字节）：LED3 亮 ✓
   - 证明 CPU 不仅到了 `uartinit()`，还到了 `printf()` → `uartputc_sync()` → `WriteReg(THR, c)`
   - 之前 LED2 亮只说明写过 UART 寄存器（含 LCR/IER/FCR 配置），不代表写过 THR 数据

2. **`dbg_tx_fifo_nonempty`**（device.sv 的 TX FIFO 非空）：LED2 灭 ✓
   - FIFO 为空，所有写入的 THR 数据都已被串行发送

3. **`dbg_tx_state_rdy`**（UART TX 状态机在 RDY 空闲）：LED3 亮 ✓
   - 状态机正常回到 RDY，没有卡死

**结论**：device.sv 的 UART TX 完全正常，数据已通过 `tx = txBit` 串行发送出去。

#### jtag_uart TX FIFO 短暂捕获到数据

LED2=`jtag_tx_avail` 测试：按下 btnC 后 LED2 闪一下然后灭。
- 说明 jtag_uart 的 TX FIFO 确实短暂有数据（捕获到了 device.sv 的 UART TX）
- 但数据很快被消费/丢失

#### BSCANE2 JTAG 读取路径完全失效

在 jtag_uart 中添加自检机制：复位后自动 push 3 个 'U'(0x55) 字节到 TX FIFO，
并且让 BSCANE2 USER1 的 CAPTURE_DR 始终加载 `{1'b1, 8'h55}`（valid=1, data='U'）。

**结果**：xsdb 仍读到 0 valid bytes / 5000 reads。

**结论**：问题不在 jtag_uart 的 FIFO 或捕获逻辑，而在 **xsdb 的 `jtag sequence` 命令无法正确读取 BSCANE2 USER1 的 TDO 输出**。xsdb 主要用于处理器调试（ARM/RISC-V），可能不支持 FPGA 内部 BSCANE2 原语的 USER1/USER2 指令访问。

#### 替代方案：RsTx 物理引脚输出

将 `assign RsTx = cpu_tx` —— 直接把 device.sv 的 UART TX 串行数据输出到 A18 引脚。

**结果**：LED2,3 亮（CPU 正常运行，写过 THR），但用户没有 USB 转 TTL 串口适配器或示波器，无法直接读取 A18 引脚的 UART 数据。

### 当前阻塞

1. **BSCANE2 读取路径不可用**：xsdb 的 `jtag sequence` 无法读取 BSCANE2 USER1 TDO
2. **无物理串口读取设备**：没有 USB-TTL 适配器或示波器

### 可能的解决方案

1. **获取 USB-TTL 串口适配器**：连接 Basys3 的 A18 (RsTx) 和 GND，在 PC 上用串口终端（如 PuTTY/Tera Term）读取 115200 baud UART 数据
2. **研究 OpenOCD**：OpenOCD 可能支持 BSCANE2 的 USER1/USER2 指令访问
3. **使用 Vivado ILA**：添加 Integrated Logic Analyzer 抓取 cpu_tx 信号波形

---

## FT232H UART 读取方案成功 + SPI Flash 磁盘读取 Bug 修复

### 时间：2026-06-26

### FT232H D2XX 直接读取 UART

Basys3 板载 FT2232H 双通道 USB 芯片：
- Channel A (index 0) = JTAG
- Channel B (index 1) = UART

使用 Python `ftd2xx` 库直接打开 Channel B，设置 115200 8N1，无需 VCP 驱动分配 COM 端口。

工具 `vivado/tools/prog_and_read.py`：
1. 先启动 FTDI Channel B UART 读取线程
2. 通过 Vivado subprocess 编程 FPGA（JTAG SRAM）
3. 持续捕获从第一个时钟周期开始的 UART 输出

**结果**：成功捕获 xv6 启动输出：
```
xv6 kernel is booting
panic: invalid file system
```

### SPI Flash 烧录

使用 Vivado GUI 手动烧录 `full_flash.mcs`：
- Flash 芯片：**S25FL032P** (Spansion)，part 名 `s25fl032p-spi-x1_x2_x4`
- 批处理 `program_hw_cfgmem` 持续失败（Labtools 27-3347），必须用 GUI
- MCS 布局：bitstream @ 0x000000 + fs.img @ 0x300000
- 烧录后需拔插 USB 重新上电（btnC 复位无效，FPGA fabric 被 Flash bridge 占用）

### FSDBG 调试：发现超级块读取全零

在 `kernel/fs.c` 的 `fsinit()` 添加 debug printf：
```c
if (sb.magic != FSMAGIC) {
    printf("FSDBG: magic=%x exp=%x\n", sb.magic, FSMAGIC);
    printf("FSDBG: first bytes:");
    char *p = (char*)&sb;
    for(int i = 0; i < 16; i++) printf(" %x", (unsigned char)p[i]);
    printf("\n");
    panic("invalid file system");
}
```

**FSDBG 输出**：
```
FSDBG: magic=0 exp=10203040
FSDBG: size=0 nblocks=0 ninodes=0
FSDBG: first bytes: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

所有字节为 0x00（不是 0xFF 擦除态），说明 SPI Flash 数据根本没读到。

### 根因分析：device.sv 磁盘数据读取时序 Bug

**问题**：`device.sv` 的 `ready` 信号在磁盘数据读取的第一个周期就置位，导致 CPU 锁存 `rdata=0`（BRAM 数据尚未就绪）。

**详细分析**：
- `disk_read_pending` 是寄存器，在读取请求的第一个周期为 0
- `disk_read_not_ready = disk_read_pending = 0` → `ready = 1`
- `txn_fire = valid && ready = 1` → CPU 读取 `rdata = disk_rdata_valid ? disk_rdata_shifted : 0 = 0`
- CPU 读到 0 后就完成了事务，不会再等待正确数据

**修复**：
```systemverilog
// 添加组合逻辑检测磁盘数据读取（从第 0 周期就生效）
logic is_disk_data_read;
assign is_disk_data_read = valid && !wvalid &&
                           addr >= DISK_DATA_BASE && addr < DISK_DATA_BASE + 1024;

// 修改 ready：磁盘数据读取时，等待 BRAM 数据有效
assign ready = uart_thr_write_req ? (~fifo_full & ~txn_done_pulse) :
               (is_disk_data_read ? (disk_rdata_valid & ~txn_done_pulse) : ~txn_done_pulse);
```

同时在仿真路径 `gen_sim_disk` 中设置 `disk_rdata_valid = 1'b1`（仿真中数据总是就绪）。

**时序**：
- Cycle 0: CPU 请求 → `is_disk_data_read=1`, `disk_rdata_valid=0` → `ready=0`（等待）
- Cycle 1: `disk_read_pending=1` → BRAM 读取完成 → `disk_rdata_valid=1`
- Cycle 2: `disk_rdata_valid=1` → `ready=1` → `txn_fire=1` → CPU 读到正确数据

### ILA 实施记录 (2026-06-26)

**选择方案**：Vivado ILA（方案 3）。无需额外硬件，通过 JTAG 读取 FPGA 内部信号。

#### 改动内容

1. **basys3_top.sv**：给关键信号添加 `(* mark_debug = "true" *)` 属性
   - `cpu_tx` —— UART TX 串行输出，ILA 主触发信号
   - `jtag_cpu_rx` —— JTAG UART RX 路径
   - `dbg_ever_thr_write` —— CPU 是否到达 `printf()` → `WriteReg(THR, c)`（之前 LED3 验证已亮）

2. **build_with_ila.tcl**（新增脚本）：自动化 ILA 构建流程
   - 复用 `build_bitstream_only.tcl` 的 IP 升级、BRAM COE 更新、OOC 综合
   - 综合后 `open_run synth_1`，调用 `setup_debug` 显式配置 ILA core
   - ILA 时钟域：`dbg_cpu_clk`（25MHz CPU 时钟，UART 状态机时基）
   - ILA 深度：4096（每 UART bit = 216 个 25MHz 周期，深度 4096 可抓约 19 个 bit = 1.9 个 UART 帧）
   - 实现 + `write_bitstream` 启用 `DEBUG_BITSTREAM`，生成 `.bit` + `.ltx`（探针定义文件）

3. **imports 副本同步**：所有源文件覆盖到 `project_3.srcs/sources_1/imports/`，避免 Vivado 综合时使用过期 RTL（前述根因 1 的预防）。

#### 触发策略

- probe0 (`cpu_tx`) 下降沿触发 —— 对应 UART 起始位
- 抓取 4096 个 `dbg_cpu_clk` 周期（约 164us），足以覆盖一个完整 UART 帧（10 bits × 8.64us = 86.4us）
- 验证目标：
  - 起始位（`cpu_tx = 0`）
  - 8 个数据位（LSB first）
  - 停止位（`cpu_tx = 1`）
  - 位周期：216 × 40ns = 8.64us（≈ 115740 baud，接近 115200）

#### 后续步骤

1. 运行 `vivado.bat -mode batch -source build_with_ila.tcl` 生成带 ILA 的 bitstream
2. 打开 Vivado Hardware Manager，连接 Basys3
3. Program Device 时选择 `basys3_top.bit`，Vivado 会自动加载 `basys3_top.ltx` 探针定义
4. 在 ILA Dashboard 设置 `probe0(cpu_tx)` 触发为下降沿
5. 按 btnC 复位 → ILA 触发抓取波形
6. 分析 `cpu_tx` 波形，确认 UART 数据正确性

### ILA 构建迭代记录 (2026-06-26)

`build_with_ila.tcl` 在 batch mode 下创建 ILA core 共经历 9 次迭代才走通 API 调用序列，每次错误及修复如下：

| # | 错误 | 根因 | 修复 |
|---|------|------|------|
| 1 | `invalid command name "setup_debug"` | `setup_debug` 是 GUI-only 命令 | 改用 `create_debug_core` + `create_debug_port` + `connect_debug_port` + `implement_debug_core` |
| 2 | `Could not create debug port as it exceeds the maximum '1' allowed` | `create_debug_core` 自动创建 clk 端口 | 移除 `create_debug_port u_ila clk`，只保留 `connect_debug_port u_ila/clk` |
| 3 | `Too many positional options when parsing '0'` | probe 索引由 Vivado 自动递增 | 改为 `create_debug_port u_ila probe`（无索引） |
| 4 | `Design needs to be saved before implementing debug cores` | 缺少 `save_constraints` | 在 `implement_debug_core` 前添加 `save_constraints` |
| 5 | `invalid command name "close_run"` | `close_run` 非有效命令 | 改为 `close_design` |
| 6 | `run does not have property STEPS.OPT_DESIGN.ARGS.DEBUG_ENABLED` | 属性名错误 | 移除该 set_property（ILA core 已通过 implement_debug_core 实现） |
| 7 | `probe3 has 1 unconnected channels` | ILA core 默认 4 probe，只接 3 个 | 添加 `dbg_cpu_valid` 作为 probe3，加 `mark_debug + KEEP` 属性 |
| 8 | `probe4 has 1 unconnected channels` | ILA core 默认 5 probe | `delete_debug_port [get_debug_ports -quiet u_ila/probe4]` |
| 9 | `[Place 30-433] Unplaced instances: jtag_uart_inst/bscane2_user1 (BSCANE2)` | BSCANE2 与 ILA 都用 JTAG 资源，无法共存 | **禁用 jtag_uart 模块**，`assign jtag_cpu_rx = 1'b1` |

#### mark_debug 信号被综合优化问题

`dbg_cpu_valid` 仅在 `always_ff` 中赋值且未被外部使用，综合时会被优化掉，导致 `get_nets -filter {MARK_DEBUG == 1}` 返回空。修复方法：

```systemverilog
(* mark_debug = "true", KEEP = "true" *) logic dbg_cpu_valid;
```

`KEEP = "true"` 属性防止综合器将该信号当作冗余逻辑优化掉，确保 ILA probe 能正确连接。

#### BSCANE2 与 ILA 冲突

BSCANE2 原语（`jtag_uart.sv` 中使用）和 Vivado ILA core 都使用 FPGA 的 JTAG 资源（TCK/TMS/TDI/TDO）。两者无法在同一 bitstream 中共存：

- BSCANE2 用于通过 JTAG 读写 FPGA 内部寄存器（USER1/USER2 指令）
- ILA 通过 JTAG 读取内部信号采样数据

由于 BSCANE2 路径之前已证明不可用（xsdb 无法读取 USER1 TDO），且 ILA 是当前选择的调试方案，禁用 jtag_uart 模块是合理的：

```systemverilog
// JTAG UART Bridge DISABLED
assign jtag_cpu_rx = 1'b1;  // UART idle line
```

CPU UART RX 永远看到 idle 状态（高电平），不影响 UART TX 输出抓取。

#### 最终 ILA core 配置

```tcl
create_debug_core u_ila ila
set_property C_DATA_DEPTH 4096 [get_debug_cores u_ila]
set_property C_TRIGOUT_EN false [get_debug_cores u_ila]
set_property C_INPUT_PIPE_STAGES 2 [get_debug_cores u_ila]
set_property ALL_PROBE_SAME_MU true [get_debug_cores u_ila]
set_property ALL_PROBE_SAME_MU_CNT 2 [get_debug_cores u_ila]

connect_debug_port u_ila/clk [get_nets $ila_clk]
# probe0: cpu_tx (1-bit)         — UART TX 串行输出
# probe1: jtag_cpu_rx (1-bit)    — 现为常量 1（jtag_uart 禁用后）
# probe2: dbg_ever_thr_write     — CPU 写过 THR 数据字节
# probe3: dbg_cpu_valid          — CPU valid 信号（带 KEEP 防优化）
# probe4: 已 delete（ILA core 默认创建但未用）
```

#### 当前阻塞解除

第 9 次构建阻塞于 BSCANE2/ILA 冲突，本次修改（jtag_uart 禁用）已同步到源文件与 imports 副本，重新运行 `build_with_ila.tcl` 应可完成 bitstream 生成。
