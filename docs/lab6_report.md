# Lab6 实验报告：中断与异常支持

## 1. 实验目标

Lab6 要求 CPU 支持基本的 RISC-V 特权级中断与异常处理。本地 `wiki/Lab-6.md` 的内容较简略，只说明需要支持：

- 时钟中断
- 外部中断
- ECALL
- 非法指令
- 页错误等异常

该 Wiki 页面没有单独写出测试命令。实际测试入口来自 `Makefile` 中的 `test-lab6`：

```makefile
test-lab6: sim
	TEST=sys ./build/emu --no-diff -i ./ready-to-run/lab6/lab6-test.bin $(VOPT) || true
```

因此本实验使用 WSL 中的 `make test-lab6` 验证。由于 Makefile 在测试命令末尾加了 `|| true`，且 Lab5/Lab6 仿真在打印通过信息后不一定自然退出，最终判断以输出中的 `Test ... [OK]`、`Single test passed.` 等关键通过信息为准，而不是只看 shell 退出码。

## 2. 相关模块

本次修改集中在以下文件：

- `vsrc/src/core.sv`
- `vsrc/src/core/core_commit.sv`
- `vsrc/src/core/core_csr.sv`
- `vsrc/src/core/core_execute.sv`
- `vsrc/src/core/core_pkg.sv`
- `vsrc/SimTop.sv`
- `vsrc/util/mmu.sv`

核心思路是把异常与中断统一接入 commit/CSR 路径，由 CSR 模块维护 `mepc`、`mcause`、`mtval`、`mstatus`、`mie`、`mip`、`satp` 等状态，并在 trap/mret 时对前端和 MMU 状态做 flush，避免旧请求污染新特权级下的执行。

## 3. 异常处理实现

### 3.1 ECALL cause

ECALL 的 `mcause` 需要根据当前特权级区分：

- U-mode ECALL：`mcause = 8`
- S-mode ECALL：`mcause = 9`
- M-mode ECALL：`mcause = 11`

CSR 模块中新增 `get_ecall_cause()`，根据 `privilege_mode_i` 生成对应 cause。这样 Lab6 中的 `ecall_u` 和后续 M-mode trap 测试都能得到正确的异常原因。

### 3.2 非法指令

非法指令进入 trap 时：

- `mepc = wb_r.pc`
- `mcause = 2`
- `mtval = {32'd0, wb_r.instr}`

这样 trap handler 可以从 `mtval` 中看到触发异常的原始指令编码。

### 3.3 地址不对齐异常

Lab6 测试覆盖了取指、load、store 三类 misalign：

- 取指地址不对齐：`mcause = 0`
- load 地址不对齐：`mcause = 4`
- store 地址不对齐：`mcause = 6`

执行模块在跳转目标地址低两位非零时生成 `ex_instr_misalign`，并禁止错误跳转继续 flush 前端。访存地址不对齐沿用 `ex_misalign`，在 CSR trap 中根据 load/store 类型写入不同 cause。对应的 `mtval` 写入出错地址。

## 4. 中断处理实现

### 4.1 中断 pending 与 enable

CSR 模块根据 `mip`、`mie` 和 `mstatus.MIE` 判断机器级中断：

- MTIP：timer interrupt，`mcause = 0x8000000000000007`
- MSIP：software interrupt，`mcause = 0x8000000000000003`
- MEIP：external interrupt，`mcause = 0x800000000000000b`

当 CPU 已在 M-mode 时，只有 `mstatus.MIE = 1` 才响应中断；当 CPU 处于低特权级时，机器级中断可以进入 M-mode trap。

### 4.2 本拍 CSR 写回后的中断判定

Lab6 的 `m_trap` 测试中有如下关键序列：

```asm
csrsi mstatus, 8
csrci mstatus, 8
```

测试期望 timer interrupt 精确落在 `csrci mstatus, 8` 这条指令处，并在这条指令清掉 MIE 后不再重复进入中断。原先如果直接用旧的 `csr_mstatus` 判断 pending，中断可能在 `csrci` 写回同一拍仍按旧 MIE 触发，导致重复 trap。

修复方式是为中断判定引入本拍有效值：

- 如果 WB 正在写 `mstatus`，中断判定使用 `wb_r.csr_wdata`
- 如果 WB 正在写 `mie`，中断判定使用 `wb_r.csr_wdata`
- 否则使用寄存器中的 `csr_mstatus` / `csr_mie`

这样 CSR 写回和中断响应的优先关系与测试预期一致。

### 4.3 精确中断 mepc

中断进入 trap 时，`mepc` 应保存流水线中最老的未提交指令 PC，而不是简单使用当前 fetch PC。否则当前端已经预取到后续指令时，`mepc` 会偏后。

当前实现按流水线阶段优先选择：

```verilog
assign intr_fetch_pc = mem_r.valid ? mem_r.pc :
                       ex_r.valid  ? ex_r.pc  :
                       id_r.valid  ? id_r.pc  :
                                     fetch_pc;
```

这保证 `m_trap` 中 timer interrupt 的 `mepc` 能落在测试期望的 `0x80008048`。

## 5. trap/mret 与前端 flush

trap 或 mret 发生后，前端必须立即切换到新 PC：

- trap 跳转到 `mtvec`
- mret 跳转到 `mepc`
- 执行级跳转跳转到 `ex_redirect_pc`

实现中在 `trap_redirect || mret_redirect || ex_flush_front` 时清理：

- `fetch_pending`
- `fetch_req_pc`
- `fetch_redirect_pending`
- `fetch_buf_valid`

并加入短暂的 `fetch_redirect_bubble`，避免 redirect 后旧响应立刻被当成新指令消费。这样可以防止旧 U-mode 虚拟地址请求在切回 M-mode 后继续流入流水线。

## 6. MMU flush 与页错误处理

`SimTop.sv` 将 core 的 `flush_mmu_o` 接入 MMU。MMU 在 flush 时清理：

- page walk 状态机
- 保存的虚拟地址和 PTE 信息
- fault 地址
- fault 类型
- `trap_pending`

这样在 trap/mret/前端 flush 后，旧的 page walk 或旧 fault 不会污染新的异常处理路径。此前调试中曾出现过 ECALL 被旧的 page fault 抢优先级的问题，这一处 flush 可以避免该类问题。

## 7. Difftest 特权级状态

`DifftestCSRState.priviledgeMode` 原先固定上报 M-mode。Lab5/Lab6 中涉及 U-mode 与 M-mode 之间的 mret/trap 切换，因此需要上报真实的下一拍特权级：

```verilog
.priviledgeMode(privilege_mode_diff)
```

同时 `core_csr.sv` 中 `privilege_mode_diff` 使用 `next_privilege_mode`，避免 difftest 看到滞后一拍的 privilege mode。

## 8. 验证结果

### 8.1 Lab6

在 WSL 中运行：

```bash
make test-lab6
```

关键输出：

```text
Single test passed.
Run sys-test
trap here, epc 8000600c, cause 8
Test ecall_u [OK]
trap here, epc 80006028, cause 0
Test instr_misalign [OK]
trap here, epc 80006040, cause 4
Test load_misalign [OK]
trap here, epc 80006050, cause 6
Test store_misalign [OK]
trap here, epc 800060b0, cause 8000000000000007
Test timer_intr [OK]
trap here, epc 80006090, cause 8000000000000003
Test software_intr [OK]
Test m_trap [OK]
```

### 8.2 前五个 Lab 回归

为确认没有破坏前五个测试，分别运行已有仿真镜像，结果如下：

```text
Lab1: HIT GOOD TRAP at pc = 0x80010004
Lab2: HIT GOOD TRAP at pc = 0x8001fffc
Lab3: HIT GOOD TRAP at pc = 0x80000030
Lab4: HIT GOOD TRAP at pc = 0x8001fff8
Lab5: Return from init! Test passed
```

Lab5 和 Lab6 在打印通过信息后不会在 timeout 前自然退出，因此验证时使用 timeout 截断仿真进程。测试是否通过以输出中的通过信息为准。

## 9. 小结

本次 Lab6 完成了机器级中断和常见同步异常的基本支持，并修复了几个和流水线精确性相关的问题：

- 异常 cause 和 `mtval` 按类型正确写入
- 中断 `mepc` 取流水线最老未提交指令 PC
- CSR 写回后的 `mstatus`/`mie` 参与同拍中断判定
- trap/mret 后清理前端与 MMU 旧状态
- Difftest 上报真实 privilege mode

最终 `make test-lab6` 的功能项全部输出 `[OK]`，同时 Lab1-Lab5 回归保持通过。
