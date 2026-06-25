# Feature Specification: xv6 上板跑 Shell + Lab+ 完善

**Created**: 2026-06-24  
**Status**: Draft  
**Input**: 在 difftest 仿真和 FPGA 上板环境中让 xv6 内核正确启动并进入用户 shell；完善 lab+ 所有任务（原子指令扩展、PMP、分支预测等）；补全实验报告。

## Overview

将 RISC-V 五级流水 CPU 部署到 Basys3 FPGA 上运行 xv6 操作系统，使其正确启动内核、加载文件系统、进入用户 shell。核心挑战包括：将仿真侧 MMIO（UART 16550 + 磁盘 + CLINT）适配到 FPGA 的 device.sv、通过串口从 PC 加载磁盘镜像到 FPGA BRAM、确保 CPU 的 Supervisor 模式/MMU/原子指令正确工作，同时完善 lab+ 各项功能并通过测试。

## User Scenarios & Testing *(mandatory)*

### User Story 1 - difftest 仿真中 xv6 启动进 shell (Priority: P1)

用户在 WSL 中运行 `make test-xv6`，xv6 内核在 difftest 仿真环境中正确启动，串口输出 "xv6 kernel is booting"，加载文件系统，最终进入用户 shell 提示符。

**Why this priority**: 这是整个项目的核心验证路径——仿真通过是上板的前提。CPU 必须正确处理 M→S 模式切换、MMU 页表翻译、UART 输出、磁盘 MMIO 读写才能让 xv6 运行。

**Independent Test**: WSL 中 `make test-xv6`，观察 UART 输出是否包含启动信息和 shell 提示符。

**Acceptance Scenarios**:

1. **Given** xv6 kernel 已编译且 fs.img 已生成, **When** 用户运行 `make test-xv6`, **Then** 仿真输出 "xv6 kernel is booting" 启动信息
2. **Given** 内核启动完成, **When** 文件系统加载成功, **Then** 仿真输出 "init: starting sh"
3. **Given** shell 进程已启动, **When** 用户观察仿真输出, **Then** 看到 "$" 提示符，表示成功进入用户终端

---

### User Story 2 - FPGA 上板跑 xv6 进 shell (Priority: P1)

用户将综合后的 bit 流烧录到 Basys3，PC 通过串口助手观察 xv6 启动信息。磁盘镜像通过 UART 从 PC 加载到 FPGA 的 BRAM 中。

**Why this priority**: 上板跑 xv6 是课程超级加分项，也是验证 CPU 在真实硬件上可用性的终极目标。

**Independent Test**: Vivado 烧录 → PC 串口助手发送磁盘镜像 → 观察 xv6 启动输出。

**Acceptance Scenarios**:

1. **Given** device.sv 已增加 16550 UART 兼容 + MMIO 磁盘 + CLINT, **When** Vivado 综合+实现+生成 bit 流, **Then** 综合 Implementation 无 Error，时序 WNS ≥ 0
2. **Given** bit 流已烧录到 Basys3, **When** PC 通过串口助手发送 fs.img, **Then** FPGA 接收并存储磁盘数据到 BRAM
3. **Given** 磁盘加载完成, **When** CPU 启动 xv6, **Then** 串口输出 "xv6 kernel is booting"
4. **Given** 内核启动完成, **When** 文件系统加载且 shell 启动, **Then** 串口输出 "$" 提示符

---

### User Story 3 - Lab+ 原子指令扩展完善 (Priority: P2)

用户在 WSL 中运行 `make test-labplus-3`，全部 rv64a 原子指令测试通过，包括 AMO 全集 (amoswap/amoadd/amoxor/amoand/amoor/amomin/amomax/amominu/amomaxu) 和 LR/SC 指令。

**Why this priority**: 原子指令是多核基础，也是去年期末考点。当前只实现了 amoswap.w/amoadd.w/lr.w/sc.w，缺 7 个 AMO 操作和 LR/SC Reservation Set。

**Independent Test**: WSL 中 `make test-labplus-3`，观察输出 HIT GOOD TRAP。

**Acceptance Scenarios**:

1. **Given** CPU 已实现全部 .w AMO 指令, **When** 运行 `make test-labplus-3`, **Then** 全部 AMO 操作正确执行
2. **Given** LR/SC Reservation Set 已实现, **When** SC 指令执行, **Then** 正确判断保留标记并返回成功/失败
3. **Given** 原子指令期间中断/异常被抑制, **When** AMO 执行中间收到中断, **Then** AMO 操作不被打断

---

### User Story 4 - Lab+ PMP 与特权测试完善 (Priority: P2)

用户在 WSL 中运行 `make test-labplus-4`，PMP 和特权模式测试达到最佳通过率。

**Why this priority**: PMP 是 RISC-V 特权架构核心功能，当前只有 pmpaddr0/pmpcfg0 一个入口。需确认测试通过率并尝试修复 instr_misalign/breakpoint 项。

**Independent Test**: WSL 中 `make test-labplus-4`。

**Acceptance Scenarios**:

1. **Given** PMP 实现正确, **When** 运行 `make test-labplus-4`, **Then** PMP 相关子项全部通过
2. **Given** instr_misalign 修复完成, **When** JALR 目标地址不对齐, **Then** 正确触发指令对齐异常

---

### User Story 5 - Lab+ Microbench 性能测试通过 (Priority: P2)

用户在 WSL 中运行 `make test-labplus-2`，microbench 测试通过。可选：实现分支预测并统计准确率。

**Independent Test**: WSL 中 `make test-labplus-2`。

**Acceptance Scenarios**:

1. **Given** CPU 基础功能正确, **When** 运行 `make test-labplus-2`, **Then** microbench 全部 benchmark 完成且 HIT GOOD TRAP
2. **Given** 分支预测已实现, **When** 运行 microbench, **Then** 分支预测准确率统计输出

---

### User Story 6 - 实验报告与提交 (Priority: P3)

用户完成完整的 lab+ 实验报告，涵盖 xv6 上板、CPU 功能完善、测试结果，并成功生成提交包。

**Independent Test**: 审阅 `docs/report.md` 和 `make handin`。

**Acceptance Scenarios**:

1. **Given** 所有功能开发和测试完成, **When** 审阅报告, **Then** 包含 xv6 上板流程、CPU 修改记录、测试结果、性能数据
2. **Given** 报告完成, **When** 运行 `make handin`, **Then** 生成正确的提交 zip 包

---

### Edge Cases

- UART 16550 兼容：xv6 的 uart.c 读写多个寄存器（THR/RHR/IER/LCR/LSR/FCR/ISR），device.sv 必须正确响应所有偏移地址
- 磁盘加载时序：PC 串口发送磁盘镜像的速度可能与 CPU 读取速度不匹配，需要握手机制
- BRAM 容量：内核 38KB + 磁盘最小镜像约 100KB，总需求 ~140KB，Basys3 有 225KB BRAM，但当前已用 42/50 Tiles
- MMU 缺陷：U bit 未检查、A/D bit 未设置、SFENCE.VMA 未实现——可能导致 xv6 运行异常
- SRET 在 U-mode 下应触发 illegal instruction 异常，当前无此检查

## Requirements *(mandatory)*

### Functional Requirements

**xv6 运行必需（P1）:**

- **FR-001**: device.sv MUST 实现 16550 UART 兼容接口（地址 0x10000000-0x10000005），支持 THR/RHR/IER/LCR/LSR/FCR/ISR 寄存器读写
- **FR-002**: device.sv MUST 实现 MMIO 磁盘接口（地址 0x10001000 blockno + 0x10001008 status + 0x10001100-0x100014FF 数据），磁盘数据存储在 BRAM
- **FR-003**: device.sv MUST 实现 CLINT mtime 寄存器（地址 0x3800bff8），提供递增计时器
- **FR-004**: FPGA 上板 MUST 支持通过 UART 从 PC 加载磁盘镜像到 BRAM
- **FR-005**: CPU 的 S-mode MUST 正确工作：mret 从 M→S 切换、ecall 从 U/S 触发正确异常码、sret 从 S→U 切换
- **FR-006**: MMU MUST 正确处理 PTE 的 U bit（User 页在 S-mode 访问时检查 SUM 位）、A bit（访问位置位）、D bit（写脏位置位）
- **FR-007**: xv6 spinlock MUST 在单核环境下正确工作（改写为不依赖 rv64a，或实现完整 rv64a）
- **FR-008**: 仿真侧 ram.sv 的 MMIO MUST 与 FPGA 侧 device.sv 的行为一致

**Lab+ 功能完善（P2）:**

- **FR-009**: CPU MUST 实现全部 .w AMO 指令（amoswap/amoadd/amoxor/amoand/amoor/amomin/amomax/amominu/amomaxu）
- **FR-010**: CPU MUST 实现 LR.W/SC.W 指令，包含 Reservation Set 跟踪
- **FR-011**: AMO/LR/SC 执行期间 MUST 抑制中断和异常，保证原子性
- **FR-012**: AMO MUST 在 FPGA（非 Verilator）环境下正确工作，不能依赖 DPI-C
- **FR-013**: MMU MUST 实现至少 SFENCE.VMA 指令的 decode 和基本 flush 功能
- **FR-014**: `make test-labplus-2` MUST 通过（HIT GOOD TRAP）
- **FR-015**: `make test-labplus-3` MUST 通过（HIT GOOD TRAP）
- **FR-016**: `make test-labplus-4` MUST 尽可能高分通过

**报告与提交（P3）:**

- **FR-017**: 实验报告 MUST 包含完整的设计说明、修改记录、测试结果
- **FR-018**: `make handin` MUST 成功生成提交 zip 包

### Key Entities

- **Device (MMIO)**: FPGA 侧外设控制器，包含 16550 UART、MMIO 磁盘、CLINT 计时器、LED/Switch
- **Disk BRAM**: 存储磁盘镜像的独立 BRAM IP，通过 UART 从 PC 加载
- **CBus Crossbar**: 地址路由，addr[31] 区分 RAM/Device 区域
- **MMU**: Sv39 页表翻译器，需增强 U/A/D bit 处理
- **Reservation Set**: LR/SC 原子指令的地址跟踪结构

## Success Criteria *(mandatory)*

### Measurable Outcomes

- **SC-001**: WSL 仿真中 `make test-xv6` 成功输出 "xv6 kernel is booting" 并进入 shell 提示符
- **SC-002**: FPGA 上板烧录后串口输出 xv6 启动信息，PC 加载磁盘后进入 shell
- **SC-003**: `make test-labplus-3` 输出 HIT GOOD TRAP（原子指令全通过）
- **SC-004**: `make test-labplus-4` 通过率不低于 14/16（争取 16/16）
- **SC-005**: Vivado Implementation 时序收敛 WNS ≥ 0
- **SC-006**: `make handin` 成功生成提交 zip 包

## Assumptions

- xv6 已修改为使用简单 MMIO 磁盘驱动（virtio_disk.c 已改写），仿真侧 ram.sv 已支持
- 串口加载磁盘方案：PC 发送 fs.img 字节流 → FPGA UART 接收 → 写入磁盘 BRAM → CPU 启动后通过 MMIO 读取
- 磁盘镜像可缩小到 ~100KB（FSSIZE=200 blocks × 512B），适配 BRAM 余量
- CPU 单核环境下 spinlock 可改写为不依赖原子指令的简化版本（关中断即可）
- Basys3 有 50 个 BRAM36 Tiles (225KB)，当前用 42 个，剩 8 个 (36KB)
- Vivado 2018.3 已安装在 G:\Vivado\2018.3\
- WSL 可访问 Windows 文件系统

## Open Questions

- BRAM 余量是否足够同时容纳内核(38KB) + 缩小版磁盘(100KB)？可能需要新增第二个 BRAM IP 或扩展现有 BRAM
- 磁盘加载协议：PC→FPGA 串口传输如何标记开始/结束？需要自定义简单握手协议还是直接字节流？
- xv6 的 MMU 对 A/D bit 的实际依赖程度——是否必须硬件设置，还是 xv6 软件层面有 workaround？
