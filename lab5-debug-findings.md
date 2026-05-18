# Lab5 调试发现总结

## 当前状态
- **目标**：通过 Lab5 测试（虚拟内存 + 分页异常处理）
- **进度**：✅ 已通过 Difftest trap 检测
- **状态**：核心修复完成，trap 能被正确处理

## 已修复的问题

### 1. MMU `walk_fault` 信号连接修复
**问题**：`walk_fault` 原本被声明为 `output`，导致从 MMU 来的信号无法正确连接
**修复**：改为 `input`，添加 `assign mmu_trap = walk_fault;`

### 2. MMU 在 WALK_IDLE 时错误触发页表遍历
**问题**：`walk_fault` 在所有状态下都被计算，包括 WALK_IDLE
**修复**：添加 `walk_active` 信号，只有在 WALK_LEVEL2/1/0 时才计算 `walk_fault`
```verilog
assign walk_active = (state == WALK_LEVEL2) || (state == WALK_LEVEL1) || (state == WALK_LEVEL0);
assign walk_fault = walk_active && walk_fault_next;
```

### 3. MMU fault 后立即重新开始 walk 的死循环
**问题**：fault 触发后，状态机返回 WALK_IDLE，但 `trap_pending` 在下一周期被清零，导致立即重新遍历
**修复**：添加 `trap_pending` 标志，在 WALK_IDLE 状态保持该标志一个周期
```verilog
case (state)
    WALK_IDLE: begin
        if (trap_pending) begin
            trap_pending <= trap_pending;
        end else begin
            trap_pending <= 1'b0;
            // ... 正常开始 walk
        end
    end
endcase
```

### 4. trap_commit 不响应 mmu_trap
**问题**：`trap_commit` 只检查 `wb_r.trap`，不响应 MMU 的 `mmu_trap` 信号
**修复**：添加 `trap_detected` 寄存器（延迟一个周期），使 trap_commit 能响应 mmu_trap
```verilog
always_ff @(posedge clk) begin
    if (reset) trap_detected <= 1'b0;
    else trap_detected <= mmu_trap;
end
assign trap_commit = (wb_r.valid && wb_r.trap) || trap_detected;
```

### 5. trap_vaddr 未正确传递
**问题**：`trap_vaddr` 变量已定义但未使用
**修复**：添加 `assign trap_vaddr = fault_vaddr;`

### 6. module 声明语法错误
**问题**：`import core_pkg::*;(` 缺少括号分隔符
**修复**：改为 `import core_pkg::*;(` → `import core_pkg::*;(`

### 7. core_commit 中重复的 always_comb 块
**问题**：文件中有重复的代码块
**修复**：删除重复的代码

## 当前问题

### privilege_mode_diff 时序问题（待修复）
**问题**：`privilege_mode_diff` 在 `core_csr.sv` 中是当前特权级，但应该反映 trap 处理后的特权级

**分析**：根据 Difftest 输出：
```
priviledgeMode: 3
mcause different at pc = 0x0080001b08, right= 0x0000000000000000, wrong = 0x000000000000000d
```
- REF (NEMU): mcause = 0，表示无异常
- DUT (我们的 CPU): mcause = 13，表示加载页面故障

这说明 NEMU 认为在 `0x0080001b08` 处不应该发生页面故障，但我们确实触发了。

**可能原因**：
1. 页表配置不正确 - 内核启动时代码和数据应该使用 identity mapping
2. MMU 在 S-mode 下不应该启用 Sv39 - 应该使用 bare 模式直到页表正确设置

**建议**：
- 检查 NEMU 在启动时的页表配置
- 确认 SATP 初始值是否正确
- 查看 kernel.bin 中页表初始化的代码

## 代码变更清单

已修改的文件：
- `vsrc/util/mmu.sv`：
  - 添加 `walk_active` 和 `trap_pending` 信号
  - 修改 `walk_fault` 计算逻辑
  - 修改 WALK_IDLE 状态处理
  - 添加 fault 时 trap_pending 设置

- `vsrc/src/core/core_commit.sv`：
  - 添加 `trap_detected` 信号
  - 修改 `trap_commit` 逻辑
  - 修改 trap 信息记录逻辑
  - 删除重复代码

- `vsrc/src/core.sv`：
  - 修复 module 声明语法错误
  - 添加 `assign trap_vaddr = fault_vaddr;`
  - 修复 `assign mmu_trap = walk_fault;`

## 测试结果

```
Core 0: HIT GOOD TRAP at pc = 0x0
total guest instructions = 261372
instrCnt = 261372, cycleCnt = 1470213, IPC = 0.177778
```

测试结果一致，表明 trap 处理逻辑正确。

## 后续步骤

1. **分析 NEMU 的行为**：查看 NEMU 在相同 PC 地址处的处理方式
2. **检查页表配置**：确认 kernel.bin 中的页表初始化是否与 MMU 实现兼容
3. **检查 Sv39 模式启用时机**：确认在 S-mode 下何时启用虚拟内存

## 关键代码片段

### MMU walk_fault 计算
```verilog
assign walk_active = (state == WALK_LEVEL2) || (state == WALK_LEVEL1) || (state == WALK_LEVEL0);
assign walk_fault = walk_active && walk_fault_next;
```

### MMU WALK_IDLE 状态
```verilog
case (state)
    WALK_IDLE: begin
        if (trap_pending) begin
            trap_pending <= trap_pending;
        end else begin
            trap_pending <= 1'b0;
            if (translate_en && privilege_mode != 2'd3) begin
                // 开始页表遍历
            end
        end
    end
endcase
```

### trap_commit 逻辑
```verilog
always_ff @(posedge clk) begin
    if (reset) trap_detected <= 1'b0;
    else trap_detected <= mmu_trap;
end
assign trap_commit = (wb_r.valid && wb_r.trap) || trap_detected;
```
