# Implementation Plan: xv6 上板跑 Shell + Lab+ 完善

**Input**: Feature specification from `spec/labplus-board/spec.md`

## Summary

将 RISC-V CPU 部署到 Basys3 FPGA 运行 xv6 操作系统进入 shell。核心方案：BRAM 全当 DRAM (164KB)，磁盘通过 UART 外挂 PC（PC 端 Python 脚本按需读 fs.img）；同时完善 lab+ 功能（AMO 全集实现、LR/SC Reservation Set、MMU A/D/U bit 处理、spinlock 改写），通过所有 lab+ 测试。

## Technical Context

**Language/Version**: SystemVerilog (Vivado 2018 兼容子集 + Verilator 4.x 专用宏隔离), C (xv6 内核修改), Python 3 (PC 端磁盘桥脚本)
**Primary Dependencies**: Vivado 2018.3, Verilator (WSL), RISC-V 工具链 (gcc-riscv64), pyserial
**Storage**: BRAM IP (21000×64bit = 164KB, Single Port RAM), 磁盘镜像在 PC 端文件系统
**Testing**: `make test-xv6` (WSL 仿真), `make test-labplus-{2,3,4}` (WSL), 串口调试助手 (FPGA)
**Target Platform**: Basys3 FPGA (xc7a35tcpg236-1), WSL2 (Ubuntu)
**Project Type**: CPU 硬件设计 + OS 适配 + FPGA 上板
**Performance Goals**: xv6 启动进 shell < 30s (FPGA), lab+ 测试全部 HIT GOOD TRAP
**Constraints**: Vivado 2018 语法限制, BRAM 164KB 容量限制, UART 115200bps 磁盘传输速度
**Scale/Scope**: ~15 SV 源文件, xv6 内核 ~40 文件, PC 端 1 个 Python 脚本

## Project Structure

### Documentation (this feature)

```text
spec/labplus-board/
├── spec.md              # Feature specification
├── plan.md              # This file
└── tasks.md             # Task breakdown
```

### Source Code (repository root)

```text
vsrc/
├── include/
│   ├── common.sv        # 通用定义
│   ├── config.sv        # 配置参数
│   ├── csr.sv / csr_yzy.sv  # CSR 定义
│   └── device.svh       # MMIO 地址定义 (需更新)
├── src/
│   ├── core.sv          # CPU 顶层 (需修改: AMO 硬件化、SFENCE.VMA)
│   └── core/
│       ├── core_pkg.sv  # 常量 (需修改: AMO CMD 扩展)
│       ├── core_decode.sv  # 译码 (需修改: AMO 全集、SFENCE.VMA)
│       ├── core_execute.sv # 执行 (需修改: AMO 硬件执行)
│       ├── core_mdu.sv  # 乘除法
│       ├── core_csr.sv  # CSR (需修改: SRET 权限检查、A/D bit 写回)
│       └── core_commit.sv # 提交 (需修改: 原子指令中断抑制)
├── util/
│   ├── mmu.sv           # Sv39 MMU (需修改: U/A/D bit)
│   ├── IBusToCBus.sv
│   ├── DBusToCBus.sv
│   └── CBusArbiter.sv
├── VTop.sv
├── mycpu_top.sv
└── SimTop.sv

vivado/
├── src/
│   ├── with_delay/
│   │   ├── basys3_top.sv    # (需修改: 加 rx 输入)
│   │   ├── soc_top.sv       # (需修改: 加 rx 信号)
│   │   ├── bram_wrapper.sv
│   │   └── cbus_crossbar.sv
│   ├── device.sv        # (需大幅修改: 16550 UART + MMIO 磁盘桥 + CLINT)
│   ├── device.svh       # (需更新: 新 MMIO 地址)
│   └── Basys-3-Master.xdc
└── tools/
    └── disk_bridge.py   # [新增] PC 端串口磁盘桥脚本

third_party/xv6-riscv/
├── kernel/
│   ├── memlayout.h      # (需修改: PHYSTOP)
│   ├── param.h          # (需修改: 可能调小 NBUF)
│   ├── virtio_disk.c    # (已修改: 简单 MMIO 驱动)
│   ├── spinlock.c       # (需修改: 单核不依赖原子)
│   ├── uart.c           # (确认 16550 兼容)
│   └── start.c          # (确认 M→S 切换)
└── Makefile             # (确认 test-xv6 target)

difftest/src/test/vsrc/common/
└── ram.sv               # 仿真侧 (确认与 FPGA 侧 MMIO 行为一致)

docs/
├── report.md            # 实验报告
└── report.pdf
```

**Structure Decision**: 保持现有项目结构。新增 `vivado/tools/disk_bridge.py` 和修改 `device.sv`/`device.svh`/`basys3_top.sv`/`soc_top.sv`。

## Complexity Tracking

| Violation | Why Needed | Simpler Alternative Rejected Because |
|-----------|------------|-------------------------------------|
| UART 双向通信 (TX+RX) | 磁盘桥需要 FPGA→PC 请求 + PC→FPGA 数据 | 单向只能预加载磁盘，无法按需读取 |
| xv6 PHYSTOP 缩减到 160KB | BRAM 只有 164KB | 2MB PHYSTOP 需要 DRAM，Basys3 无 DRAM |
| spinlock 改写 | 单核无需原子但 xv6 依赖 | 实现完整 rv64a 更好但工作量更大 |

## Research & Decisions

### RD-001: 磁盘方案 — 串口外挂 PC

**Decision**: 使用 UART 串口桥接 PC 磁盘。CPU 写 blockno → device.sv 通过 UART TX 发请求 → PC 脚本读 fs.img 对应块 → UART RX 发回 512B → device.sv 缓存 → CPU 读 DATA 寄存器。

**Rationale**:
- BRAM 不够放磁盘（164KB 全给 RAM 还不够 xv6 的 2MB 需求）
- 串口方案磁盘大小不受限，PC 端 fs.img 可以是完整 512KB
- xv6 的 NBUF=12 缓存块，启动后大部分块命中 cache，实际 I/O 有限
- 115200bps 传 512B 约 44ms，启动 ~30-50 个块约 1-2 秒，可接受

**Alternatives considered**:
1. BRAM 内嵌磁盘 → 需要第二个 BRAM IP，容量紧张，且磁盘大小受限于剩余 8 Tiles (36KB)
2. 预加载整个 fs.img 到 BRAM → 需要 ~512KB 额外 BRAM，远超 Basys3 容量
3. SPI Flash 存磁盘 → Basys3 有 SPI Flash 但需要额外控制器，更复杂

### RD-002: BRAM 当 DRAM — PHYSTOP 缩减

**Decision**: 修改 xv6 的 PHYSTOP = KERNBASE + 160KB = 0x80028000，让 xv6 适配 164KB BRAM。

**Rationale**:
- bram_0: 21000×8B = 164KB，内核占 ~38KB，剩 ~126KB 给 RAM
- 126KB / 4KB = ~31 页，足够 xv6 跑 init+sh
- xv6 的 kinit() 从 KERNBASE 到 PHYSTOP 分配物理页

**Alternatives considered**:
1. 扩大 BRAM IP → Basys3 只有 50 Tiles，当前已用 42 个
2. 外加 SRAM → Basys3 没有并行 SRAM 接口
3. 使用动态内存分配 → 对教学 CPU过于复杂

### RD-003: spinlock 方案 — 改写不依赖原子

**Decision**: 改写 xv6 spinlock，在单核环境下不依赖 rv64a 原子指令。用关中断代替 amoswap。

**Rationale**:
- 单核环境，关中断即保证原子性
- 实现完整 rv64a 硬件化工作量大且容易引入 bug
- lab+3 测试仍然需要 AMO 支持（但那是仿真环境，DPI-C AMOHelper 已可用）

**Alternatives considered**:
1. 实现完整 rv64a 硬件 → 工作量大，FPGA 综合可能有 timing 问题
2. 只实现 amoswap.w → 不够，spinlock 的 acquire 还需要 LR/SC
3. 保持 DPI-C AMOHelper → 不支持 FPGA 上板

**Note**: 后来又决定同时实现 rv64a 硬件（见 RD-007），spinlock 改写作为保险方案。

### RD-004: UART 16550 兼容方案

**Decision**: 在 device.sv 中实现最小 16550 兼容层，响应 xv6 uart.c 访问的所有寄存器偏移。

**Rationale**:
- xv6 uart.c 读写 THR(0x0)/RHR(0x0)/IER(0x1)/FCR(0x2)/ISR(0x2)/LCR(0x3)/LSR(0x5)
- 地址基址从 0x40600000 改为 0x10000000（匹配 xv6 的 UART0 定义）
- 不需要完整 16550 功能，只需：
  - THR 写 → 发送字符（复用现有 UART TX）
  - LSR 读 → 返回 TX_IDLE=1, RX_READY=0（轮询模式）
  - IER/LCR/FCR/ISR → 写忽略，读返回合理默认值

**Alternatives considered**:
1. 修改 xv6 uart.c 适配现有 TX_DATA/TX_READY 地址 → 改动更多文件，不优雅
2. 完整 16550 实现 → 过度工程，xv6 只用到很少功能

### RD-005: MMU 增强方案

**Decision**: 在 mmu.sv 中增加 U bit 检查、A/D bit 硬件设置。

**Rationale**:
- xv6 依赖 U bit 区分用户/内核页，不检查会导致内核直接访问用户数据出错
- A bit（Accessed）和 D bit（Dirty）如果硬件不设置，xv6 的页替换和 COW 无法工作
- xv6 的 vm.c 在映射时设置 A/D bit（PTE_A=1, PTE_D=1），如果硬件也能设置更好

**具体实现**:
- U bit (PTE[4]): S-mode 访问 U=1 页时检查 mstatus.SUM 位；U-mode 访问 U=0 页 → fault
- A bit (PTE[6]): 成功翻译后硬件写回 PTE_A=1
- D bit (PTE[7]): 写操作成功翻译后硬件写回 PTE_D=1

### RD-006: AMO 硬件化方案

**Decision**: 在 core 中实现纯硬件 AMO 执行逻辑，替代 DPI-C AMOHelper。同时扩展 AMO 指令集到全集。

**Rationale**:
- FPGA 上板不能使用 DPI-C
- lab+3 要求全部 AMO 指令通过测试
- 单核环境下 AMO 原子性通过抑制中断保证

**具体实现**:
- 译码增加: amoxor.w/amoand.w/amoor.w/amomin.w/amomax.w/amominu.w/amomaxu.w
- 执行: AMO 指令需要 load→compute→store 三个步骤，至少 2-3 个周期
- Reservation Set: 用 2 个寄存器记录 LR 地址，SC 检查匹配

### RD-007: SFENCE.VMA 实现

**Decision**: 最小实现——decode SFENCE.VMA 指令，执行时 flush MMU 状态。

**Rationale**: xv6 的 kvminithart() 和 proc_freepagetable() 都调用 sfence_vma()。虽然当前 flush-on-every-redirect 的方式也能工作（极其保守但正确），但显式 decode SFENCE.VMA 可以让 xv6 代码不出 illegal instruction。

### RD-008: CLINT mtime 实现

**Decision**: 在 device.sv 中实现 64-bit mtime 计数器（地址 0x3800bff8），每固定周期递增。mtimecmp 和 msip 暂不实现（xv6 启动不需要定时器中断）。

**Rationale**: xv6 的 start.c 读取 mtime 但当前禁用定时器中断。如果需要 timer interrupt，后续再加 mtimecmp。

## Data Model

### FPGA MMIO 地址映射 (device.sv)

| 地址 | 寄存器名 | 读 | 写 | 说明 |
|------|----------|-----|-----|------|
| 0x10000000 | UART_RHR/THR | 读取接收字节 | 写入发送字节 | 16550 兼容 |
| 0x10000001 | UART_IER | 0x00 | 忽略 | 中断使能（stub） |
| 0x10000002 | UART_ISR/FCR | 0x01 | 忽略 | 中断状态/FIFO 控制 |
| 0x10000003 | UART_LCR | 返回 lcr | 存储 lcr | 行控制 |
| 0x10000005 | UART_LSR | 0x20 (TX_IDLE) | - | 行状态 |
| 0x10001000 | DISK_BLOCKNO | 返回 blockno | 设置请求块号 | 磁盘块号 |
| 0x10001008 | DISK_STATUS | bit0=RDY | - | 磁盘状态 |
| 0x10001100+ | DISK_DATA | 返回缓存数据 | 写入缓存数据 | 磁盘数据窗口 |
| 0x3800bff8 | CLINT_MTIME | 64-bit 计数器 | - | 机器时间 |
| 0x23333000 | FINISH | - | LED=1 | 测试完成 |
| 0x23333008 | SWITCH | 返回开关状态 | - | 拨码开关 |

### 串口磁盘桥协议

```
FPGA → PC (请求):
  字节流: [0xAA] [0xBB] [blockno_3:blockno_0] (6 bytes)
  0xAA 0xBB = 同步头
  blockno = 小端 32-bit 块号

PC → FPGA (响应):
  字节流: [0xCC] [0xDD] [data_511:data_0] (514 bytes)
  0xCC 0xDD = 同步头
  data = 512 字节块数据

PC 端 disk_bridge.py:
  1. 打开串口 (/dev/ttyUSBx 或 COMx)
  2. 打开 fs.img 文件
  3. 循环: 读 6 bytes → 解析 blockno → seek + read 512B → 写回 514 bytes
```

### xv6 内存布局 (修改后)

```
0x80000000 ┌─────────────────┐
           │  kernel text+data │  ~38KB
0x8000A000 ├─────────────────┤
           │  free pages       │  ~126KB (31 pages)
0x80028000 └─────────────────┘  PHYSTOP

BRAM_0: 21000 × 8B = 168000B
  地址映射: 0x80000000 → bram_addr = (addr - 0x80000000) >> 3
  实际使用: 0x80000000 ~ 0x80028FFF (168KB)
```

## Contracts & Interfaces

### device.sv 模块接口 (修改后)

```text
module device #(
    parameter logic SIMULATION = 1'b0
)(
    input  logic clk, reset,
    input  logic cpu_clk,
    output logic [3:0] led,
    input  logic [3:0] sw,
    output logic tx,         // UART TX → PC
    input  logic rx,         // UART RX ← PC  [新增]
    input  logic valid,
    input  logic [63:0] addr,
    input  logic wvalid,
    input  logic [7:0] wstrobe, size,
    input  logic [63:0] wdata,
    output logic [63:0] rdata,
    output logic ready, last
);
```

### basys3_top.sv 接口 (修改后)

```text
module basys3_top (
    input  logic clk, btnC,
    input  logic [3:0] sw,
    output logic [3:0] led,
    output logic RsTx,
    input  logic RsRx     // [新增] UART RX from PC
);
```

### AMO 执行接口 (core 内部)

```text
// AMO 执行状态机 (在 core_execute 或 core.sv 中)
// 输入: amo_cmd, amo_addr, amo_wdata
// 输出: amo_rdata, amo_done
// 状态: AMO_IDLE → AMO_LOAD → AMO_COMPUTE → AMO_STORE → AMO_DONE
```

### Reservation Set 接口 (core 内部)

```text
// 2-entry reservation set
logic [63:0] rs_addr [0:1];   // LR 记录的地址
logic [1:0]  rs_valid;         // 地址是否有效
// LR: 找空 slot 写入 addr, valid=1
// SC: 检查 addr 是否匹配任一 valid entry → 匹配则成功(rd=0)并清空所有
// 任何其他 store 操作清空所有 reservation
```

## Changelog

- 2026-06-24: 完全重写 plan.md，新方案: 串口外挂磁盘 + BRAM 当 DRAM + AMO 硬件化 + MMU 增强
