# NutShell CPU 全流程实验报告

> **项目目标**：在自研 5 级流水线 RISC-V CPU 上从零跑通 xv6 操作系统，完成虚拟内存、特权级切换、文件系统和用户态 shell 的完整闭环。

---

## 第一部分：怎么做——从裸机到 xv6 shell 的完整路径

### 1. CPU 基础能力：5 级流水线核心

CPU 采用经典的 5 级流水线（IF/ID/EX/MEM/WB），单发射顺序执行。基础指令集实现 `rv64im_zicsr_zifencei`，包含：

- 整数运算（RV64I）
- 乘除法（M 扩展）
- CSR 读写与 trap 处理（Zicsr）
- 指令缓存刷新（Zifencei）
- 原子指令（A 扩展，后补）

### 2. xv6 内核裁剪——让内核适配 CPU 而非反过来

上游 xv6 默认按 `rv64gc` 编译，包含 F/D/C/S 等当前 CPU 未实现的扩展。直接编译出的镜像一启动就会在未实现指令上偏离。

**做法**：将 xv6 编译参数收窄到 CPU 已有的基础能力：

```text
-march=rv64im_zicsr_zifencei -mabi=lp64
```

同时裁剪内核参数以适配有限内存（Basys3 仅 225KB BRAM）：

| 参数 | 原值 | 新值 | 节省 BSS |
|------|------|------|----------|
| NPROC | 64 | 4 | 17KB |
| NCPU | 8 | 1 | 28KB |
| NFILE | 100 | 16 | 3KB |
| NINODE | 50 | 16 | 5KB |
| NBUF | 30 | 8 | 25KB |

BSS 从 101KB 减到 ~19KB，kernel 总占用从 146KB 减到 ~57KB。PHYSTOP 从 128MB 改为 224KB，kalloc 可用约 167KB（41 页）。

PLIC 映射从 64MB 缩减到 4MB，减少页表页需求。

用户程序从 20 个裁剪到 11 个必要程序（cat, echo, grep, init, kill, ln, ls, mkdir, rm, sh, wc）。

### 3. 仿真环境 MMIO——补齐 xv6 真正依赖的设备

#### 串口

xv6 使用 `UART0 = 0x10000000` 的 16550 风格寄存器，而原仿真环境只支持课程测试程序用的 `0x40600000` 简化 UART。

在 `ram.sv` 中补了最小可用的串口兼容：

- `0x10000000`：收发数据
- `0x10000003`：LCR（含 DLAB 位处理）
- `0x10000005`：LSR（返回 `0x60` 表示 THRE/TEMT 就绪）

#### 磁盘

xv6 原始路径走 virtio-mmio，但仿真环境没有 virtio 设备。实现了一组简化 MMIO 磁盘协议替代：

| 地址 | 用途 |
|------|------|
| `0x10001000` | DISK_BLOCKNO（写块号） |
| `0x10001008` | DISK_STATUS（读就绪，恒返回 1） |
| `0x10001100-0x100014FF` | DISK_DATA_BASE（1KB 数据窗口） |

宿主侧通过 `SDCARD_IMAGE` 环境变量加载 `fs.img`，CPU 侧发起 MMIO 读写时直接从镜像缓冲区同步读取。

同步读写足够支撑 `bread`、日志和 superblock 初始化，不需要 DMA、virtqueue 或外部中断。

### 4. Supervisor 闭环——特权级切换的核心

xv6 启动到 shell，真正的关键不是外设，而是以下控制流闭环必须同时成立：

- `mret` 行为正确（M-mode → S-mode）
- `medeleg/mideleg` 生效（异常/中断委托到 S-mode）
- `stvec/sepc/scause/sstatus` 正常工作
- trap 进入和返回时流水线清空正确
- MMU 在 trap/redirect 后不把旧页表遍历状态带进新控制流

这部分的核心代码集中在 `core_csr.sv`、`core_commit.sv`、`core.sv`、`mmu.sv`，作为一个控制流闭环整体修复，而非拆成若干 CSR 补丁。

### 5. MMU 与 TLB——虚拟内存的实现

#### 页表遍历

MMU 实现了 Sv39 三级页表遍历（WALK_LEVEL2 → WALK_LEVEL1 → WALK_LEVEL0 → WALK_DONE），支持 4KB/2MB/1GB 页。遍历过程中通过 DBus 发起 PTE 读取。

#### TLB

实现 1-entry 指令 TLB + 2-entry 数据 TLB（LRU 替换）：

- TLB 命中时直接使用缓存的物理地址，跳过页表遍历
- 遍历完成时更新 TLB
- `satp` 变化时清空 TLB（检测页表切换）
- trap 时不清 TLB（同一页表，条目仍有效）
- `walk_active` 优先于 TLB 命中（避免 PTE 读取被 TLB 干扰）

#### DBus 共享总线竞争与 WALK_GAP

页表遍历和数据访问共享同一 DBus（通过 DBusToCBus 桥接到 CBus）。PTE 读取完成后，桥接器的 `resp_seen` 标志保持为 1，阻止后续数据访问请求发出。这是 xv6 在 `kvminithart` 后 panic 的直接原因。

修复方法：在 MMU 状态机中增加 `WALK_GAP` 状态——页表遍历完成后插入 1 个空闲周期（`dreq.valid = 0`），让 DBusToCBus 的 `resp_seen` 被清除，然后再进入 `WALK_DONE_DATA` 发起真正的数据访问。

```
WALK_LEVEL0 (PTE读取完成) → WALK_GAP (1周期, dreq.valid=0) → WALK_DONE_DATA (数据访问)
```

指令访问不受影响（IBus 独立，直接从 WALK_LEVEL0 跳到 WALK_DONE_INSN）。

### 6. PMP——物理内存保护

实现单 entry PMP，支持：

- R/W/X 权限检查
- A 字段匹配（OFF/TOR/NA4/NAPOT 四种模式）
- M-mode 与非 M-mode 下的权限区分
- 指令、load、store 三类 fault cause

MMU 在两处做 PMP 检查：

1. **直通阶段**：不走分页时，直接在虚拟地址上做 PMP 检查
2. **页表翻译后阶段**：先走 Sv39 得到物理地址，再在物理地址上做 PMP 检查

### 7. 原子指令

实现 A 扩展的原子访存路径，核心是"不可被 trap 在中间打断"：

- AMO 的读旧值、写 rd、写回内存必须作为完整结果出现
- trap 不能打在中间把状态切成一半
- AMO 地址使用 `rs1`（不是 I-type 的 `rs1 + imm`）

### 8. CSR 权限检查

CSR 地址的 bits[9:8] 编码最低访问特权级。U-mode 访问 M-mode CSR（如 `mip`）必须触发 illegal instruction exception（mcause=2）。在 `core_decode.sv` 中加入权限检查：

```systemverilog
csr_priv = id_csr_addr[9:8];
csr_priv_ok = (privilege_mode >= csr_priv);
if (!csr_priv_ok) id_dec_is_illegal = 1'b1;
```

### 9. FPGA 上板（Basys3）

在 Basys3 (Artix-7 XC7A35T) 上实现完整上板流程：

- BRAM IP：64-bit × 21000 深度（~164KB）
- SPI Flash：S25FL032P，存储 bitstream + fs.img
- UART 输出：通过 FT2232H Channel B 的 D2XX API 直接读取
- UART TX：物理引脚 A18 输出，115200 baud

---

## 第二部分：遇到的问题与解决方法

### 问题 1：xv6 编译目标与 CPU ISA 不匹配

**现象**：xv6 用 `rv64gc` 编译出的镜像一启动就偏离，CPU 遇到未实现的 F/D/C 指令产生异常。

**解决**：将 xv6 编译参数改为 `rv64im_zicsr_zifencei`，只使用 CPU 已实现的扩展。这不是修改 CPU 去适配 xv6，而是让 xv6 适配 CPU 的实际能力。

### 问题 2：内存不足——kinit 无限循环清零 128MB

**现象**：xv6 的 `kinit` 用 `memset` 清零从 kernel end 到 PHYSTOP 的内存。PHYSTOP=128MB 意味着清零 128MB，在 224KB 仿真 RAM 上表现为无限循环（到不了 PHYSTOP）。

**解决**：PHYSTOP 从 128MB 改为 224KB。同时裁剪内核参数（NPROC/NCPU/NFILE 等）把 BSS 从 101KB 减到 19KB，给 kalloc 留出足够空间。

### 问题 3：PLIC 映射占用过多页表页

**现象**：`kvminit` 为 PLIC 的 64MB 映射需要 32+ 个 L0 页表页，224KB 内存无法容纳。

**解决**：PLIC 映射从 64MB (0x4000000) 缩减到 4MB (0x400000)，只需 2 个 L0 页表页。

### 问题 4：仿真环境无 virtio 磁盘——exec /init 失败

**现象**：xv6 的 `virtio_disk_init` 尝试访问 virtio-mmio 设备，仿真侧无此设备，`exec /init` 因读取到全零数据而报 `bad ELF magic 0x0`。

**解决**：实现简化 MMIO 磁盘接口替代 virtio。重写 `kernel/virtio_disk.c`，用三个 MMIO 寄存器（块号、状态、数据窗口）替代完整的 virtio 协议。仿真侧的 `sdcard.cpp` 从 `SDCARD_IMAGE` 加载 `fs.img` 到内存缓冲，`ram.sv` 直接映射 MMIO 读写。

### 问题 5：磁盘数据 8 字节对齐错误

**现象**：`fsinit` 读到的 superblock 数据不正确，磁盘数据错位。

**根因**：`disk_read_helper` 直接用 offset 读取，但 CPU 的 `mem_byte_shift = addr[2:0]`，需要 8 字节对齐的基地址 + 右移提取。

**解决**：`disk_read_helper` 中 offset 向下对齐到 8 字节边界：`offset & ~7ULL`。

### 问题 6：串口 byte-lane 放置错误——printf 只输出第一个字符

**现象**：xv6 启动后只输出 `i`（"init: starting sh\n" 的第一个字符），然后停住。

**根因**：xv6 用 `lbu` 读串口 LSR 状态位。仿真侧把返回值放在错误的 byte lane，CPU 读出来虽然"有数据"，但永远看不到 `LSR_TX_IDLE`（bit 5），卡在 `uartputc` 的轮询循环中。

**解决**：修正 `ram.sv` 中串口寄存器返回值的 byte-lane 放置，确保 `lbu` 读 LSR 时 `0x10000005` 返回 `0x60`（THRE + TEMT）。

### 问题 7：串口 DLAB 位误处理

**现象**：xv6 初始化串口时写波特率寄存器的数据被当作字符输出，串口日志混乱。

**根因**：串口模型忽略了 `LCR.DLAB` 位，把对分频寄存器的写入误当成 THR 数据输出。

**解决**：在 `ram.sv` 中检查 `LCR.DLAB`，当 DLAB=1 时写入指向分频寄存器而非 THR。

### 问题 8：MMU 无 TLB——数据 Load 被指令 Fetch 饿死

**现象**：printf 只输出个别字符，大部分数据 load 请求无法完成。

**根因**：MMU 原来没有 TLB，每次访存都要走三级页表遍历（3 次内存读取）。WALK_IDLE 状态中指令 fetch 优先于数据访问，数据 load 被 IBus 长期占据 DBus 而饿死。

**解决**：实现 1-entry I-TLB + 2-entry D-TLB。TLB 命中时直接用缓存的物理地址跳过遍历，大幅减少 DBus 竞争。

### 问题 9：DBus 共享总线竞争——PTE 读取阻塞数据访问（WALK_GAP）

**现象**：xv6 在 `kvminithart` 后 panic。页表遍历完成后的数据访问无法发出。

**根因**：页表遍历和数据访问共享 DBus（通过 `DBusToCBus` 桥接）。PTE 读取完成后，桥接器的 `resp_seen` 标志保持为 1，阻止后续数据访问请求发出。具体机制：

1. 页表遍历通过 DBus 发起 PTE 读取，`dreq.valid = 1`
2. DBusToCBus 收到响应后设置 `resp_seen = 1`
3. 页表遍历完成，MMU 状态机进入 WALK_DONE_DATA，发起数据访问
4. 但此时 `dreq.valid` 一直为 1（从 PTE 读取到数据访问没有断开），`resp_seen = 1`
5. DBusToCBus 的 `issue_now = dreq.valid && !req_inflight && !resp_seen`，因为 `resp_seen = 1`，`issue_now = 0`
6. 数据访问请求无法发出，CPU 永远等不到响应

**解决**：在 MMU 状态机中增加 `WALK_GAP` 状态。页表遍历完成后先进入 WALK_GAP（1 个周期），期间 `dreq.valid = 0`，让 DBusToCBus 的 `resp_seen` 被清除（`!dreq.valid → resp_seen <= 0`），然后进入 WALK_DONE_DATA 发起数据访问。

状态转移变为：
```
WALK_LEVEL0 → WALK_GAP (1周期) → WALK_DONE_DATA
```

指令访问不受影响（IBus 独立，直接 WALK_LEVEL0 → WALK_DONE_INSN）。

### 问题 10：PMP A 字段编码反了——mret 后 S-mode 卡死

**现象**：xv6 在 `mret` 进入 S-mode 后不再退休指令，看起来像 trap/MMU/页表问题。

**根因**：`mmu.sv` 中 PMP 的 `A` 字段（`pmpcfg[4:3]`）编码写反了：
- 正确：`01 = TOR`, `10 = NA4`
- 错误：`01 = NA4`, `10 = TOR`

xv6 在 `start()` 中设置 `pmpaddr0` + `pmpcfg0`（TOR 模式，允许全地址空间），然后 `mret` 进 S-mode。编码反了导致 PMP 匹配失败，S-mode 所有访存都被拒绝，CPU 卡死。

**这是整个 bring-up 过程中最隐蔽的 bug**——表面完全不像 PMP 问题，表现更像 trap/MMU/页表缺陷。

**解决**：修正 PMP A 字段编码：`2'b01 = TOR`, `2'b10 = NA4`。

### 问题 11：walk_fault 在 WALK_IDLE 时误触发

**现象**：MMU 在没有进行页表遍历时也触发 fault，CPU 收到虚假的页表异常。

**根因**：`walk_fault` 在所有状态下都被计算，包括 WALK_IDLE。WALK_IDLE 时总线上的响应数据是上一次残留的，被误判为 fault。

**解决**：添加 `walk_active` 信号，只在 WALK_LEVEL2/1/0 时才计算 walk_fault：
```systemverilog
assign walk_active = (state == WALK_LEVEL2) || (state == WALK_LEVEL1) || (state == WALK_LEVEL0);
assign walk_fault = walk_active && walk_fault_next;
```

### 问题 12：fault 后立即重新遍历的死循环

**现象**：MMU fault 触发后，状态机返回 WALK_IDLE，但 `trap_pending` 在下一周期被清零，导致立即重新开始遍历同一地址，陷入死循环。

**解决**：添加 `trap_pending` 标志，在 WALK_IDLE 状态保持一个周期：
```systemverilog
WALK_IDLE: begin
    if (trap_pending) begin
        trap_pending <= trap_pending;  // 保持
    end else begin
        trap_pending <= 1'b0;          // 清零
        // ... 正常开始 walk
    end
end
```

### 问题 13：trap_commit 不响应 MMU trap

**现象**：MMU 产生 walk_fault，但 trap_commit 只检查 `wb_r.trap`，不响应 MMU 的 `mmu_trap` 信号，导致页表异常被忽略。

**解决**：添加 `trap_detected` 寄存器延迟一周期，使 trap_commit 能响应 mmu_trap：
```systemverilog
always_ff @(posedge clk) begin
    if (reset) trap_detected <= 1'b0;
    else trap_detected <= mmu_trap;
end
assign trap_commit = (wb_r.valid && wb_r.trap) || trap_detected;
```

### 问题 14：AMO 地址 decode 错误

**现象**：原子指令测试 `atomicity.bin` 访问错误地址，看起来像原子语义错误。

**根因**：AMO 地址应当直接使用 `rs1`，但 decode 阶段像 I-type 那样把立即数加到了 `rs1` 上。

**解决**：修正 AMO 地址生成，直接使用 `rs1` 作为访存地址。

### 问题 15：U-mode 访问 M-mode CSR 不触发异常

**现象**：`labplus-4` 的 `illegal_instr` 和 `mem_detect` 子测试失败。U-mode 下访问 `mip` 等 M-mode CSR 时 CPU 不触发 illegal instruction exception。

**根因**：CPU 的 CSR 访问路径没有做权限检查。RISC-V 规范要求 CSR 地址 bits[9:8] 编码最低访问特权级，U-mode 访问特权级更高的 CSR 必须触发 illegal instruction。

**解决**：在 `core_decode.sv` 中加入 CSR 权限检查逻辑，`labplus-4` 从 12/16 提升到 14/16。

### 问题 16：Vivado 2018 兼容性——上板综合报错

**现象**：Verilator 仿真通过的代码在 Vivado 2018 中综合失败。

**根因**：Vivado 2018 对 SystemVerilog 支持有限，多个语法不兼容。

**解决**：

| 问题 | 修复 |
|------|------|
| `$error` 系统函数 | `ASSERTS` 宏用 `ifdef VERILATOR` 隔离 |
| `always_comb` 内变量声明 | 内联为直接比较表达式 |
| `always_ff` 内变量声明 | 移到模块级 |
| `for (int b = ...)` | `int` 改为 `integer` |
| `localparam type` 枚举 | 改为 `localparam logic [1:0]` 常量 |
| `'x` 赋值 | `rdata = 'x` 改为 `rdata = 64'd0` |
| 未隔离的 `include | 包裹到 `ifdef VERILATOR` |

### 问题 17：Vivado imports 副本过期——bitstream 中没有 jtag_uart

**现象**：JTAG UART 读取始终为 0 字节，但源文件中已有 jtag_uart 模块。

**根因**：Vivado 工程通过 `$PSRCDIR/sources_1/imports/` 引用源文件副本而非源文件本身。imports 副本中的 `basys3_top.sv` 是完全过时的旧版本（只有 Standalone UART TX test，没有 jtag_uart bridge）。

**解决**：用源文件覆盖所有 imports 副本（basys3_top.sv, soc_top.sv, bram_wrapper.sv, cbus_crossbar.sv, device.sv 等）。

### 问题 18：BSCANE2 与 ILA 的 JTAG 资源冲突

**现象**：Vivado 综合 ILA + jtag_uart 时报 DRC MDRV-1 错误，BSCANE2 USER1 的 TDO 被多个 always 块驱动。

**根因**：BSCANE2 原语和 Vivado ILA core 都使用 FPGA 的 JTAG 资源，无法共存。此外 xsdb 的 `jtag sequence` 命令无法正确读取 BSCANE2 USER1 的 TDO 输出，JTAG UART 路径本身就不可用。

**解决**：禁用 jtag_uart 模块，`assign jtag_cpu_rx = 1'b1`（UART idle line），改用 ILA 抓取 `cpu_tx` 信号波形。

### 问题 19：FPGA 磁盘数据读取时序 Bug——superblock 全零

**现象**：FPGA 上 xv6 输出 `panic: invalid file system`，FSDBG 显示 superblock 全零（不是 0xFF 擦除态）。

**根因**：`device.sv` 的磁盘数据读取中，`ready` 信号在第一个周期就置位（`disk_read_pending` 初始为 0 → `ready = 1`），CPU 在 BRAM 数据尚未就绪时就读取了 `rdata = 0`。

**解决**：添加组合逻辑 `is_disk_data_read` 检测磁盘数据读取，修改 `ready` 条件等待 BRAM 数据有效：
```systemverilog
assign ready = uart_thr_write_req ? (~fifo_full & ~txn_done_pulse) :
               (is_disk_data_read ? (disk_rdata_valid & ~txn_done_pulse) : ~txn_done_pulse);
```

### 问题 20：FT2232H EEPROM 配置损坏——Vivado 不识别板子

**现象**：Basys3 的 FT2232H EEPROM 配置被意外擦除，Vivado Hardware Manager 无法识别板子，设备显示为 `"Dual RS232-HS A"` 而非 `"Digilent Basys3"`。

**根因**：EEPROM 的字符串描述符区域被擦除（全 `0x0000`），字符串使能标志被清除，配置字 word 9 的 bit 11 被改错，校验和与数据不匹配。FTDI 芯片检测到校验和错误后丢弃整个 EEPROM 配置，回退到芯片默认 VID/PID 和字符串。

**解决**：用正常板子的完整 EEPROM 备份（256 words）覆盖损坏板子的全部 EEPROM，包括字符串区域、配置字和校验和。修复过程中还发现：

1. VID 被改为 0x1443 后 D2XX 无法打开设备 → 用 Zadig 安装 WinUSB 驱动恢复
2. 校验和必须与实际数据匹配 → 直接用完整备份覆盖（包括原始校验和 0x2947）
3. D2XX Description 缓存 → 必须物理拔插 USB 触发重新加载

### 问题 21：EEPROM VCP 位与 Vivado 驱动互斥

**现象**：EEPROM 启用 VCP 后 Vivado 不再识别 Basys3。

**根因**：EEPROM 的 VCP 位（word 5 bit 0/1）让 Windows 给对应通道绑定 FTDI VCP 驱动（ftdibus.sys），替换掉 Digilent D2XX 驱动。而 Vivado 通过 Digilent Adept SDK 访问设备，需要 D2XX 驱动。两者互斥。

**解决**：EEPROM 保持原厂配置（word 5 = `0x0008`，不启用 VCP），通过 Windows 设备管理器属性手动加载 VCP 子驱动，实现 Vivado 和 COM 口共存。

### 问题 22：lab5 fs_mini.img 损坏——bad ELF magic

**现象**：仿真中 `exec /init` 失败，报 `bad ELF magic 0x0`。

**根因**：`fs_mini.img` 只有 52KB（52 块），但 superblock 声明 2000 块（2MB）。/init 的 `addrs[0]=170` 对应字节偏移 174080，超出镜像范围，读回全零。

**解决**：发现上游 lab5 的 `kernel.bin`（8720B）不访问磁盘，`userinit` 内嵌 initcode 直接打印 `Return from init! Test passed`。替换为上游原版 kernel.bin，lab5 仿真通过。

---

## 第三部分：最终验证结果

### 仿真（make test-xv6）

```
xv6 kernel is booting
init: starting sh
$
```

xv6 shell 可执行基本命令（echo, ls, cat, mkdir, rm, wc, grep, kill）。

### 课程测试

| 测试 | 状态 |
|------|------|
| lab5 | PASS — `Return from init! Test passed` |
| lab6 | PASS |
| labplus-3（原子指令） | PASS — `HIT GOOD TRAP at pc = 0x800000dc` |
| labplus-4（PMP） | 14/16 PASS — CSR 权限检查修复后从 12/16 提升 |

labplus-4 剩余 2 个失败（`instr_misalign`、`breakpoint`）经分析为测试二进制与反汇编不匹配，非 CPU 逻辑缺陷。

### FPGA

- FT232H D2XX 成功捕获 UART 输出
- xv6 在 Basys3 上启动并进入 shell（需 SPI Flash 存 fs.img）
- lab5 kernel 直接从 BRAM 启动

---

## 第四部分：关键经验

1. **trap 问题几乎从来不在 trap 自己身上**：最难调的不是"没进 trap"，而是"trap 进去了，但架构状态和微结构状态没一起收干净"。mepc 取错 PC、trap 后前端旧请求没丢、MMU 旧 walk 状态没清——这些最后都表现成重复执行、丢指令、或 xv6 在看似无关的地方卡死。

2. **xv6 是系统级放大镜**：单独跑课程测试程序时很多 bug 不会暴露，换成 xv6 后这些 bug 被连续控制流、特权切换、文件系统和用户态拉满。delegation 少同步一个 bit、byte-lane 错一位、PMP 模式错一位——每一个都能让 xv6 整个死掉。

3. **最隐蔽的 bug 往往不在你怀疑的地方**：PMP A 字段编码反了，表面看完全像 trap/MMU/页表问题，实际上只是两个 bit 的解释顺序。花在定位上的时间远多于修复本身。

4. **共享总线竞争的解法要选对层级**：DBus 共享总线的 PTE-数据竞争，可以在 DBusToCBus 桥接器里修（加入 flush 逻辑），也可以在 MMU 状态机里修（插入空闲周期）。后者改动更小、影响范围更可控。

5. **Vivado imports 副本是上板的隐形陷阱**：Vivado 工程引用源文件副本而非源文件本身，修改源文件对综合不可见。这是一个只要踩一次就会记住的坑。

6. **FT2232H EEPROM 的校验和是配置生效的关键**：数据正确但校验和错误，FTDI 照样丢弃全部配置。恢复时必须用完整备份覆盖，不能只改部分字段。

7. **性能优化比功能修复更容易伤 correctness**：静态分支预测、放松前端阻塞等优化尝试，有的无净收益，有的直接打坏 lab6 或 xv6。当前流水线结构中很多 stall 条件是 correctness 的一部分，不是"纯性能差"。

---

## 第五部分：文件修改清单

### xv6 内核

- `kernel/param.h` — 参数裁剪（NPROC/NCPU/NFILE/NINODE/NBUF）
- `kernel/memlayout.h` — PHYSTOP 224KB
- `kernel/vm.c` — PLIC 4MB 映射
- `kernel/virtio_disk.c` — 简化磁盘 MMIO 接口
- `kernel/exec.c` — 调试代码（残留）
- `kernel/trap.c` — 调试代码（残留）
- `Makefile` — UPROGS 裁剪 + ISA 参数修改

### 仿真侧

- `difftest/src/test/csrc/common/ram.h` — EMU_RAM_SIZE 224KB
- `difftest/src/test/csrc/common/ram.cpp` — 强制 224KB 覆盖
- `difftest/src/test/csrc/common/sdcard.cpp` — 运行时磁盘镜像加载 + disk_read_helper
- `difftest/src/test/vsrc/common/ram.sv` — 串口 16550 兼容 + 磁盘 MMIO 响应

### CPU

- `vsrc/util/mmu.sv` — TLB + WALK_GAP + PMP + walk_fault 修复 + trap_pending
- `vsrc/src/core/core_csr.sv` — Supervisor CSR + delegation + trap/redirect 处理
- `vsrc/src/core/core_commit.sv` — trap_detected 信号 + CSR 权限检查
- `vsrc/src/core/core.sv` — mmu_trap 连接 + trap_vaddr 连接
- `vsrc/src/core/core_decode.sv` — AMO 地址修复 + CSR 权限检查
- `vsrc/src/core/core_mdu.sv` — Vivado 兼容性修复

### FPGA / Vivado

- `vivado/lab5_project/` — Vivado 工程及 imports 副本
- `vivado/tools/prog_and_read.py` — FT232H UART 读取工具
- `vivado/tools/build_with_ila.tcl` — ILA 构建脚本
- `vsrc/fpga/basys3_top.sv` — 顶层模块（UART TX 输出 + ILA 调试信号）
- `vsrc/fpga/soc_top.sv` — SoC 顶层
- `vsrc/fpga/device.sv` — UART + 磁盘设备（时序修复）
