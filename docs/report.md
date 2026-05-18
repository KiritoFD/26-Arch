# Lab5 实验报告：虚拟内存与分页异常处理

## 设计实现

### 1. MMU 模块设计

MMU 是虚拟内存管理的核心组件，负责地址翻译和异常检测。

#### 1.1 主要信号

```verilog
module mmu
    import common::*;(
    // 输入信号
    input  logic [63:0]  satp,              // 页表基址寄存器
    input  logic [1:0]   privilege_mode,    // 当前特权级

    // 与 Core 的接口
    input  ibus_req_t    ireq_in,           // Core 指令请求
    output ibus_resp_t   iresp_in,         // Core 指令响应
    input  dbus_req_t    dreq_in,          // Core 数据请求
    output dbus_resp_t   dresp_in,         // Core 数据响应

    // 与 Bus 的接口
    output ibus_req_t    ireq_out,         // Bus 指令请求
    input  ibus_resp_t   iresp_out,        // Bus 指令响应
    output dbus_req_t    dreq_out,         // Bus 数据请求
    input  dbus_resp_t   dresp_out,        // Bus 数据响应

    // 异常信号
    output logic         walk_fault,        // 页表遍历故障
    output logic [63:0]  fault_vaddr,      // 故障虚拟地址
    output logic         fault_is_insn     // 是否是指南取故障
);
```

#### 1.2 Sv39 地址格式

Sv39 使用三级页表结构，虚拟地址格式如下：

```
63        38 37        30 29        21 20        12 11         0
+--------+--------+--------+--------+--------+--------+--------+
|  Reserved  |   VPN[2]  |   VPN[1]  |   VPN[0]  |   Page Offset  |
+--------+--------+--------+--------+--------+--------+--------+
```

物理地址格式：

```
63        54 53        30 29        21 20        12 11         0
+--------+--------+--------+--------+--------+--------+--------+
|  Reserved  |   PPN[2]  |   PPN[1]  |   PPN[0]  |   Page Offset  |
+--------+--------+--------+--------+--------+--------+--------+
```

#### 1.3 状态机设计

MMU 使用有限状态机实现页表遍历：

```verilog
typedef enum logic [2:0] {
    WALK_IDLE,        // 空闲状态，等待地址翻译请求
    WALK_LEVEL2,      // 遍历 Level 2 页表
    WALK_LEVEL1,      // 遍历 Level 1 页表
    WALK_LEVEL0,      // 遍历 Level 0 页表
    WALK_DONE_INSN,   // 指令翻译完成
    WALK_DONE_DATA    // 数据翻译完成
} walk_state_t;
```

状态转换图：

```
                    +-----------------+
                    |   WALK_IDLE     |<---------+
                    +-----------------+          |
                          |                      |
        ireq_in.valid / dreq_in.valid            |
                          v                      |
          +-------+-------+-------+-------+      |
          | WALK  | WALK  | WALK  | WALK  |      |
          | LEVEL2| LEVEL1| LEVEL0| DONE  |------+
          +---+---+---+---+---+---+---+---+
              |   |   |   |   |
              v   v   v   v
          PTE返回完成状态
```

### 2. 页表遍历实现

#### 2.1 虚拟地址提取

```verilog
assign vpn2 = saved_vaddr[38:30];  // VPN[2]
assign vpn1 = saved_vaddr[29:21];   // VPN[1]
assign vpn0 = saved_vaddr[20:12];  // VPN[0]
assign page_offset = saved_vaddr[11:0];  // 页内偏移
```

#### 2.2 PTE 地址计算

页表基址来自 SATP 寄存器的 PPN 字段：

```verilog
assign satp_mode = (satp[63:60] == 4'd8);  // Sv39 模式
assign satp_ppn  = satp[43:0];              // 页表基址

// Level 2 PTE 地址: satp_ppn * 4KB + vpn2 * 8
pte_addr = {8'd0, satp_ppn, vpn2, 3'b000};
```

#### 2.3 PTE 解析

```verilog
// PTE 格式（Sv39）
// [63:54] Reserved
// [53:28] PPN[2]
// [27:19] PPN[1]
// [18:10] PPN[0]
// [9:8]   Reserved
// [7]     RSW
// [6]     A    (Accessed)
// [5]     D    (Dirty)
// [4]     G    (Global)
// [3]     X    (Execute)
// [2]     W    (Write)
// [1]     R    (Read)
// [0]     V    (Valid)

// 判断是否为叶子页表项
if (dresp_out.data[3] || dresp_out.data[1] || dresp_out.data[2]) begin
    // 是叶子页表项（X/W/R 任一为1）
    saved_pte <= dresp_out.data;
    saved_level <= current_level;
    state <= saved_is_insn ? WALK_DONE_INSN : WALK_DONE_DATA;
end else begin
    // 是指针页表项，指向下一级
    state <= next_level_state;
    pte_addr <= {8'd0, dresp_out.data[53:10], next_vpn, 3'b000};
end
```

### 3. 页面故障检测

#### 3.1 故障条件

```verilog
// 检测页表遍历失败
assign walk_fault_next =
    // V=0: 页表项无效
    (state == WALK_LEVEL2 && dresp_out.data_ok && !dresp_out.data[0]) ||
    (state == WALK_LEVEL1 && dresp_out.data_ok && !dresp_out.data[0]) ||
    (state == WALK_LEVEL0 && dresp_out.data_ok && !dresp_out.data[0]) ||
    // 不是叶子页表项也不是指针页表项（RsV）
    (state == WALK_LEVEL0 && dresp_out.data_ok && dresp_out.data[0] &&
     !dresp_out.data[3] && !dresp_out.data[1] && !dresp_out.data[2]);

// 只有在活跃遍历时才触发故障
assign walk_fault = walk_active && walk_fault_next;
```

#### 3.2 故障类型

| 故障类型          | mcause 值 | 触发条件                   |
| ----------------- | --------- | -------------------------- |
| 指令页面故障      | 12        | 取指时发生页故障           |
| 加载页面故障      | 13        | 加载时发生页故障           |
| 存储/原子页面故障 | 15        | 存储或原子操作时发生页故障 |

### 4. 异常处理

#### 4.1 trap_pending 机制

防止故障后立即重新开始遍历导致死循环：

```verilog
case (state)
    WALK_IDLE: begin
        if (trap_pending) begin
            // 保持 trap_pending 一个周期
            trap_pending <= trap_pending;
        end else begin
            trap_pending <= 1'b0;
            // 正常处理新的翻译请求
            if (translate_en && privilege_mode != 2'd3) begin
                // 开始页表遍历
            end
        end
    end
endcase
```

#### 4.2 trap_commit 逻辑

MMU 故障需要延迟一个周期才能被 commit 模块感知：

```verilog
// trap_detected 延迟 mmu_trap 一个周期
always_ff @(posedge clk) begin
    if (reset) trap_detected <= 1'b0;
    else trap_detected <= mmu_trap;
end

// trap_commit 响应两种异常源
assign trap_commit = (wb_r.valid && wb_r.trap) || trap_detected;
```

### 5. 物理地址计算

根据遍历到的 PTE 级别计算物理地址：

```verilog
always_comb begin
    phys_addr = 64'd0;
    unique case (saved_level)
        2'd2: phys_addr = {10'd0, saved_pte[53:30], vpn1, vpn0, page_offset};
        2'd1: phys_addr = {10'd0, saved_pte[53:21], vpn0, page_offset};
        2'd0: phys_addr = {8'd0, saved_pte[53:10], page_offset};
        default: phys_addr = 64'd0;
    endcase
end
```

## 调试过程

### 问题 1：walk_fault 信号类型错误

**现象**：Difftest 报告在不应触发异常的位置触发了 mcause=13。

**分析**：初始实现中 `walk_fault` 被声明为 `output`，但实际应作为输入传入 core。

**修复**：

```verilog
// core.sv
input logic walk_fault,           // 从 MMU 来
assign mmu_trap = walk_fault;
```

### 问题 2：MMU 在 WALK_IDLE 时错误触发 walk_fault

**现象**：页表遍历尚未开始，walk_fault 就被错误断言。

**分析**：`walk_fault_next` 在所有状态下都被计算，包括 WALK_IDLE。

**修复**：添加 `walk_active` 信号，限定 `walk_fault` 只在活跃遍历时计算：

```verilog
assign walk_active = (state == WALK_LEVEL2) || (state == WALK_LEVEL1) || (state == WALK_LEVEL0);
assign walk_fault = walk_active && walk_fault_next;
```

### 问题 3：fault 后立即重新 walk 导致死循环

**现象**：CPU 在页面故障后不断重新尝试遍历，无法处理异常。

**分析**：状态机返回 WALK_IDLE 时，trap_pending 被立即清零，导致立即开始新的遍历。

**修复**：在 WALK_IDLE 状态保持 trap_pending 一个周期：

```verilog
WALK_IDLE: begin
    if (trap_pending) begin
        trap_pending <= trap_pending;
    end else begin
        trap_pending <= 1'b0;
        // 开始新的遍历
    end
end
```

### 问题 4：trap_commit 不响应 mmu_trap

**现象**：MMU 触发了 walk_fault，但 trap_commit 未被置位。

**分析**：原始的 `trap_commit` 只检查 `wb_r.trap`，不响应 MMU 的 `mmu_trap` 信号。

**修复**：添加 `trap_detected` 寄存器，延迟一个周期后响应：

```verilog
assign trap_commit = (wb_r.valid && wb_r.trap) || trap_detected;
```

## 测试结果

### Difftest 测试输出

```
Core 0: HIT GOOD TRAP at pc = 0x0
total guest instructions = 261372
instrCnt = 261372, cycleCnt = 1470213, IPC = 0.177778
```

### 测试验证

- ✅ trap 被正确检测
- ✅ 指令数稳定：261372
- ✅ 周期数稳定：1470213
- ✅ 连续多次运行结果一致

## 核心代码

### MMU 模块关键实现

```verilog
// 虚拟地址翻译使能
assign translate_en = satp_mode && (privilege_mode != 2'd3);

// 故障检测
assign walk_fault_next =
    (state == WALK_LEVEL2 && dresp_out.data_ok && !dresp_out.data[0]) ||
    (state == WALK_LEVEL1 && dresp_out.data_ok && !dresp_out.data[0]) ||
    (state == WALK_LEVEL0 && dresp_out.data_ok && !dresp_out.data[0]) ||
    (state == WALK_LEVEL0 && dresp_out.data_ok && dresp_out.data[0] &&
     !dresp_out.data[3] && !dresp_out.data[1] && !dresp_out.data[2]);

// 物理地址计算
always_comb begin
    unique case (saved_level)
        2'd2: phys_addr = {10'd0, saved_pte[53:30], vpn1, vpn0, page_offset};
        2'd1: phys_addr = {10'd0, saved_pte[53:21], vpn0, page_offset};
        2'd0: phys_addr = {8'd0, saved_pte[53:10], page_offset};
    endcase
end
```

## 实验总结

本实验成功实现了基于 Sv39 的虚拟内存管理单元，主要贡献包括：

1. **完整的三级页表遍历硬件**：使用状态机实现了高效的页表遍历
2. **准确的页面故障检测**：能够正确识别 V=0 和 RsV 等故障情况
3. **正确的异常处理机制**：trap 能够正确传播并被 commit 模块响应
4. **完善的调试框架**：通过 Difftest 验证了实现的正确性

实验过程中遇到的几个关键问题最终都通过仔细分析波形和状态机逻辑得以解决，体现了虚拟内存系统实现的复杂性。

## 参考资料

1. RISC-V Spec Volume II: Privileged Architecture
2. Sv39: RISC-V Instruction Set Manual, Volume II
3. XiangShan 项目框架
