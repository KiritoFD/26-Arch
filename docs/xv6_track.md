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
4. **使用 PMOD 接口**：Basys3 的 PMOD 可能有其他可用的通信接口
