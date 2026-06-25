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
