# Tasks: xv6 上板跑 Shell + Lab+ 完善

**Input**: Design documents from `spec/labplus-board/`
**Prerequisites**: plan.md (required), spec.md (required)

## Format: `[ID] [P?] [Story] Description`

- **[P]**: Can run in parallel (different files, no dependencies)
- **[Story]**: Which user story this task belongs to
- Include exact file paths in descriptions

---

## Phase 1: Setup (环境准备与基线确认)

- [X] T001 确认 WSL 中 xv6 编译环境可用: `cd third_party/xv6-riscv && make kernel` 在 WSL 中成功 — `third_party/xv6-riscv/`
- [X] T002 [P] 确认 `make test-xv6` 仿真 target 存在并理解其工作流程 — `Makefile`
- [X] T003 [P] 确认 Basys3 板子 USB 连接且 Vivado Hardware Manager 可识别 — `vivado/lab5_project/`
- [X] T004 [P] 确认 Python3 + pyserial 可用（PC 端磁盘桥脚本依赖）— 本地环境

---

## Phase 2: Foundational (CPU 核心功能修复 — xv6 运行的前置条件)

**⚠️ CRITICAL**: 此阶段完成前 xv6 无法运行

### 2A: MMU 增强

- [X] T005 mmu.sv 增加 U bit (PTE[4]) 检查: S-mode 访问 U=1 页时检查 mstatus.SUM，U-mode 访问 U=0 页触发 fault — `vsrc/util/mmu.sv`
- [X] T006 [P] mmu.sv A bit 处理: xv6 不使用 PTE_A，MMU 不检查 A=0 故障，无需硬件写回 — `vsrc/util/mmu.sv` (N/A for xv6)
- [X] T007 [P] mmu.sv D bit 处理: xv6 不使用 PTE_D，MMU 不检查 D=0 故障，无需硬件写回 — `vsrc/util/mmu.sv` (N/A for xv6)
- [X] T008 core_csr.sv 增加 mstatus.SUM 位处理: SSTATUS_MASK 增加 bit 18+19 (SUM+MXR)，core.sv 暴露 mstatus_sum_o 连接至 mmu — `vsrc/src/core/core_csr.sv`, `vsrc/src/core.sv`, `vsrc/VTop.sv`, `vsrc/SimTop.sv`

### 2B: 特权模式修复

- [X] T009 core_decode.sv 增加 SFENCE.VMA 指令 decode: 指令编码 0x12000073，S-mode 权限检查，pipeline 传播，core_csr 触发 flush MMU + redirect PC+4 — `vsrc/src/core/core_decode.sv`, `vsrc/src/core/core_pkg.sv`, `vsrc/src/core/core_csr.sv`, `vsrc/src/core.sv`
- [X] T010 core_decode.sv 增加 SRET/MRET 权限检查: SRET 需 S-mode+，MRET 需 M-mode — `vsrc/src/core/core_decode.sv`
- [X] T011 [P] core_csr.sv 确认 mret/ecall/sret 行为符合 RISC-V 规范（已有实现，验证正确性） — `vsrc/src/core/core_csr.sv`

### 2C: AMO 硬件化 (lab+3 + FPGA 上板必需)

- [ ] T012 core_pkg.sv 扩展 AMO_CMD 枚举: 添加 AMO_CMD_XOR/AND/OR/MIN/MAX/MINU/MAXU — `vsrc/src/core/core_pkg.sv`
- [ ] T013 core_decode.sv 扩展 AMO decode: 添加 amoxor.w/amoand.w/amoor.w/amomin.w/amomax.w/amominu.w/amomaxu.w — `vsrc/src/core/core_decode.sv`
- [ ] T014 core 内实现 AMO 硬件执行逻辑: load→compute→store 状态机，替代 DPI-C AMOHelper — `vsrc/src/core.sv`, `vsrc/src/core/core_execute.sv`
- [ ] T015 core 内实现 LR.W/SC.W Reservation Set: 2-entry 地址跟踪，LR 记录、SC 检查匹配 — `vsrc/src/core.sv`
- [ ] T016 core_commit.sv 原子指令中断抑制: AMO/LR/SC 执行期间不响应中断和异常 — `vsrc/src/core/core_commit.sv`

### 2D: CLINT 最小实现

- [ ] T017 mmu.sv 或 device 侧确认 CLINT mtime 地址 0x3800bff8 在仿真和 FPGA 都能正确响应 — `vsrc/util/mmu.sv`, `vivado/src/device.sv`

**Checkpoint**: CPU 核心功能修复完成，xv6 运行的前置条件满足

---

## Phase 3: User Story 1 - difftest 仿真 xv6 启动进 shell (P1)

**Goal**: WSL 中 `make test-xv6` 输出 "xv6 kernel is booting" 并进入 shell
**Independent Test**: WSL `make test-xv6`

### 3A: xv6 适配修改

- [X] T018 [US1] 修改 xv6 memlayout.h: PHYSTOP = P2V(0x80028000)（160KB 总物理内存） — `third_party/xv6-riscv/kernel/memlayout.h`
- [X] T019 [P] [US1] 修改 xv6 param.h: NBUF=8, FSSIZE=200 — `third_party/xv6-riscv/kernel/param.h`
- [X] T020 [P] [US1] 修改 xv6 spinlock.c: 已经改写为 push_off()+直接赋值方案（不依赖 amoswap） — `third_party/xv6-riscv/kernel/spinlock.c`
- [X] T021 [US1] 确认 xv6 start.c 的 M→S 切换流程正确: medeleg/mideleg/pmp/mepc/mret 均正确 — `third_party/xv6-riscv/kernel/start.c`

### 3B: 仿真侧验证

- [ ] T022 [US1] 确认 ram.sv 的 MMIO 与 xv6 驱动兼容: UART 0x10000000 + 磁盘 0x10001000 + CLINT 0x3800bff8 — `difftest/src/test/vsrc/common/ram.sv`
- [ ] T023 [US1] 编译 xv6 内核: `cd third_party/xv6-riscv && make kernel` — `third_party/xv6-riscv/`
- [ ] T024 [US1] 运行 `make test-xv6` 观察输出: 确认 "xv6 kernel is booting" 出现 — WSL
- [ ] T025 [US1] 调试 xv6 启动问题（如有）: 根据仿真输出定位 MMU/S-mode/UART/磁盘问题并修复 — `vsrc/`, `third_party/xv6-riscv/`
- [ ] T026 [US1] 运行 `make test-xv6` 确认进入 shell: 输出 "init: starting sh" + "$" 提示符 — WSL

**Checkpoint**: WSL 仿真中 xv6 成功启动进 shell

---

## Phase 4: User Story 2 - FPGA 上板 xv6 进 shell (P1)

**Goal**: Basys3 烧录后串口输出 xv6 启动信息，PC 加载磁盘后进 shell
**Independent Test**: Vivado 烧录 → 串口助手 → disk_bridge.py

### 4A: device.sv 重大修改

- [ ] T027 [US2] device.svh 更新 MMIO 地址定义: 添加 UART_16550_BASE=0x10000000, DISK_BLOCKNO/DISK_STATUS/DISK_DATA, CLINT_MTIME 地址 — `vivado/src/device.svh`
- [ ] T028 [US2] device.sv 实现 16550 UART 兼容: 地址 0x10000000 基址，响应 THR/RHR/IER/FCR/ISR/LCR/LSR 寄存器 — `vivado/src/device.sv`
- [ ] T029 [US2] device.sv 实现 UART RX 接收逻辑: 接收 PC 发来的磁盘数据，存入 disk_buffer — `vivado/src/device.sv`
- [ ] T030 [US2] device.sv 实现 MMIO 磁盘桥: blockno 寄存器、status 寄存器（数据就绪标志）、数据窗口寄存器，内部 disk_buffer[512B] — `vivado/src/device.sv`
- [ ] T031 [US2] device.sv 实现 CLINT mtime: 64-bit 递增计数器映射到 0x3800bff8 — `vivado/src/device.sv`
- [ ] T032 [US2] device.sv 实现磁盘请求→UART TX 发送协议: CPU 写 blockno 后通过 UART TX 向 PC 发送 [0xAA 0xBB blockno_3:0] — `vivado/src/device.sv`
- [ ] T033 [US2] device.sv 实现 UART RX→磁盘数据接收: 收到 [0xCC 0xDD] + 512B 后存入 disk_buffer，设置 status RDY — `vivado/src/device.sv`
- [ ] T034 [US2] device.sv 整合所有 MMIO 地址路由: rdata 根据 addr 返回对应寄存器值，ready 逻辑考虑磁盘桥延迟 — `vivado/src/device.sv`

### 4B: SoC 顶层修改

- [ ] T035 [US2] soc_top.sv 添加 rx 信号连接: device_inst 增加 .rx(rx) 端口 — `vivado/src/with_delay/soc_top.sv`
- [ ] T036 [US2] basys3_top.sv 添加 RsRx 输入: 映射到 Basys3 的 UART RX 引脚（约束文件中已有定义） — `vivado/src/with_delay/basys3_top.sv`

### 4C: BRAM 初始化与 Vivado 工程

- [ ] T037 [US2] 生成 xv6-kernel.coe: 从 kernel.bin 生成 COE 格式，适配 bram_0 的 21000×64bit — `ready-to-run/lab5/xv6-kernel.coe`
- [ ] T038 [US2] 更新 Vivado 工程: 替换 BRAM COE 初始化文件为 xv6-kernel.coe，更新 source files — `vivado/lab5_project/`
- [ ] T039 [US2] Vivado Synthesis: 运行综合并修复所有 Error — `vivado/lab5_project/`
- [ ] T040 [US2] Vivado Implementation + Generate Bitstream: 运行实现，确认 WNS≥0 — `vivado/lab5_project/`

### 4D: PC 端磁盘桥脚本

- [ ] T041 [US2] 编写 disk_bridge.py: 打开串口+fs.img，循环接收 [0xAA 0xBB blockno] 请求，读取对应 512B 块，发送 [0xCC 0xDD + 512B] 响应 — `vivado/tools/disk_bridge.py`

### 4E: 上板验证

- [ ] T042 [US2] 烧录 bit 文件到 Basys3 — `vivado/lab5_project/`
- [ ] T043 [US2] PC 串口助手观察 UART 输出: 确认内核启动信息 "xv6 kernel is booting" — 串口助手
- [ ] T044 [US2] 运行 disk_bridge.py 加载磁盘: PC 端 Python 脚本响应磁盘请求 — `vivado/tools/disk_bridge.py`
- [ ] T045 [US2] 确认 xv6 进入 shell: 串口输出 "init: starting sh" + "$" 提示符 — 串口助手

**Checkpoint**: FPGA 上板 xv6 成功启动进 shell

---

## Phase 5: User Story 3 - Lab+ 原子指令测试 (P2)

**Goal**: `make test-labplus-3` HIT GOOD TRAP
**Independent Test**: WSL `make test-labplus-3`

- [ ] T046 [US3] 验证 AMO 硬件化在仿真环境正确: 确认 core.sv 的 AMO 逻辑替代 AMOHelper 后仿真通过 — `vsrc/src/core.sv`
- [ ] T047 [US3] 运行 `make test-labplus-3`: 观察输出，如失败则定位具体 AMO 指令问题 — WSL
- [ ] T048 [US3] 修复 AMO 硬件执行问题（如有）: 调整状态机时序、Reservation Set 逻辑 — `vsrc/src/core.sv`, `vsrc/src/core/core_execute.sv`
- [ ] T049 [US3] 运行 `make test-labplus-3` 确认 HIT GOOD TRAP — WSL

**Checkpoint**: lab+3 原子指令测试通过

---

## Phase 6: User Story 4 - Lab+ PMP/特权测试 (P2)

**Goal**: `make test-labplus-4` 尽可能高分
**Independent Test**: WSL `make test-labplus-4`

- [ ] T050 [US4] 运行 `make test-labplus-4` 记录基线: 确认当前通过项和失败项 — WSL
- [ ] T051 [US4] 分析 instr_misalign 失败原因: 检查 JALR 对齐检查逻辑与 mem_detect 状态传递的兼容性 — `vsrc/src/core/core_execute.sv`, `vsrc/src/core/core_commit.sv`
- [ ] T052 [US4] 尝试修复 instr_misalign: 在 commit 阶段触发 JALR 对齐异常而非 execute 阶段，避免与 mem_detect 冲突 — `vsrc/src/core/`
- [ ] T053 [US4] 运行 `make test-labplus-4` 验证修复: 确认不回归，instr_misalign 项是否通过 — WSL

**Checkpoint**: lab+4 最终结果记录

---

## Phase 7: User Story 5 - Lab+ Microbench (P2)

**Goal**: `make test-labplus-2` HIT GOOD TRAP
**Independent Test**: WSL `make test-labplus-2`

- [ ] T054 [US5] 运行 `make test-labplus-2` 记录基线: 确认 microbench 是否通过 — WSL
- [ ] T055 [US5] 修复 microbench 失败问题（如有）: 定位指令执行/内存访问/性能计数器问题 — `vsrc/`
- [ ] T056 [US5] 运行 `make test-labplus-2` 确认 HIT GOOD TRAP — WSL

**Checkpoint**: lab+2 microbench 测试通过

---

## Phase 8: User Story 6 - 实验报告与提交 (P3)

**Goal**: 完整实验报告 + 提交包
**Independent Test**: 审阅报告 + `make handin`

- [ ] T057 [US6] 更新 docs/report.md: 补充 xv6 上板流程、串口磁盘桥方案、device.sv MMIO 设计 — `docs/report.md`
- [ ] T058 [US6] 更新 docs/report.md: 补充 AMO 硬件化实现、LR/SC Reservation Set、MMU A/D/U bit 修改 — `docs/report.md`
- [ ] T059 [US6] 更新 docs/report.md: 补充 lab+2/3/4 测试结果、FPGA 上板测试结果 — `docs/report.md`
- [ ] T060 [US6] 运行 `make handin` 生成提交 zip 包 — 项目根目录

**Checkpoint**: 报告完整，handin zip 生成

---

## Phase 9: Polish & Cross-Cutting

- [ ] T061 [P] 清理 Vivado 临时 tcl 脚本和调试日志 — `vivado/tmp_*.tcl`
- [ ] T062 [P] 确认 WSL 基础 lab 测试 (lab1-6) 无回归 — WSL
- [ ] T063 确认 git 状态干净，所有修改已提交 — 项目根目录

---

## Phase 10: Verification

<!-- verification_scope: build+ui -->

- [ ] T064 Vivado 综合+实现验证: 确认 Synthesis 和 Implementation 无 Error，Timing WNS≥0 — `vivado/lab5_project/`
- [ ] T065 WSL 仿真验证: 运行 `make test-labplus-2`, `make test-labplus-3`, `make test-labplus-4` 全部 HIT GOOD TRAP — WSL
- [ ] T066 FPGA 上板 UI 验证: 烧录 bit 文件，PC 运行 disk_bridge.py，串口确认 xv6 启动信息 + shell 提示符 — Basys3 + 串口助手

---

## Dependencies & Execution Order

### Phase Dependencies

- Setup (Phase 1): 无依赖，立即开始
- Foundational (Phase 2): 依赖 Setup 完成，**阻塞所有后续**
- US1 仿真 xv6 (Phase 3): 依赖 Foundational 完成
- US2 FPGA 上板 (Phase 4): 依赖 US1 完成（先仿真通过再上板）
- US3 lab+3 (Phase 5): 依赖 Foundational 2C 完成，可与 US2 并行
- US4 lab+4 (Phase 6): 依赖 US3 完成（避免代码冲突）
- US5 lab+2 (Phase 7): 依赖 Foundational 完成，可与 US3/US4 并行
- US6 报告 (Phase 8): 依赖 US1+US2+US3+US4+US5 完成
- Polish (Phase 9): 依赖 US6 完成
- Verification (Phase 10): 依赖所有实现完成

### Parallel Opportunities

| Phase | Tasks | Notes |
|-------|-------|-------|
| Setup | T001, T002, T003, T004 | 可全部并行 |
| Foundational 2A | T006, T007 | A/D bit 可并行 |
| Foundational 2B | T010, T011 | 可并行 |
| US1 xv6 适配 | T018, T019, T020 | 修改不同文件，可并行 |
| US2 SoC | T035, T036 | 可并行 |
| US2 磁盘桥 | T041 | 与上板流程并行 |
| US3+US4+US5 | Phase 5+6+7 | 不同文件，可并行 |
| US6 报告 | T057, T058, T059 | 不同章节，可并行 |

---

## Summary

- **Total tasks**: 66
- **US1 (仿真 xv6)**: 9 tasks (T018-T026)
- **US2 (FPGA 上板)**: 19 tasks (T027-T045)
- **US3 (lab+3 原子指令)**: 4 tasks (T046-T049)
- **US4 (lab+4 PMP/特权)**: 4 tasks (T050-T053)
- **US5 (lab+2 microbench)**: 3 tasks (T054-T056)
- **US6 (报告)**: 4 tasks (T057-T060)
- **Setup**: 4 tasks (T001-T004)
- **Foundational**: 13 tasks (T005-T017)
- **Polish**: 3 tasks (T061-T063)
- **Verification**: 3 tasks (T064-T066)
- **MVP scope**: Phase 1+2+3 (仿真 xv6 启动进 shell)
