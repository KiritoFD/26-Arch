# xv6 仿真启动调试文档

> **日期**: 2026-06-28
> **目标**: 在 NutShell CPU 仿真环境中启动 xv6，对齐 Basys3 FPGA 板子配置 (225KB BRAM, 3-4MB Flash)

---

## 一、问题概述

xv6 在仿真中无法正常启动。通过 `make test-xv6` 运行后，仅输出 `xv6 kernel is booting` 和一个字符 `i`，然后 CPU 进入 scheduler 空转。

### 1.1 基础环境

- **CPU**: NutShell 5 级流水线 (IF/ID/EX/MEM/WB)
- **仿真器**: Verilator + clang++-19 (-O3 -march=znver4 -flto)
- **板子**: Basys3 (Artix-7 XC7A35T), 225KB BRAM, SPI Flash
- **RAM**: 仿真 224KB (对齐板子), FPGA ~164KB BRAM IP

---

## 二、已完成的修改

### 2.1 xv6 内核裁剪 (third_party/xv6-riscv/)

#### 2.1.1 参数裁剪 (kernel/param.h)

| 参数 | 原值 | 新值 | 节省 BSS |
|------|------|------|----------|
| NPROC | 64 | 4 | 17KB (proc 表) |
| NCPU | 8 | 1 | 28KB (栈) |
| NOFILE | 16 | 8 | - |
| NFILE | 100 | 16 | 3KB (ftable) |
| NINODE | 50 | 16 | 5KB (itable) |
| NBUF | 30 | 8 | 25KB (bcache) |

**BSS 从 101KB 减到 ~19KB**，kernel 总占用从 146KB 减到 ~57KB。

#### 2.1.2 内存配置 (kernel/memlayout.h)

```
PHYSTOP: 128MB → 224KB (对齐 Basys3 225KB BRAM)
```

kalloc 可用: 224KB - 57KB = ~167KB = ~41 页。

#### 2.1.3 PLIC 映射缩减 (kernel/vm.c)

```
PLIC 映射: 64MB (0x4000000) → 4MB (0x400000)
```

64MB 需要 32+ 个 L0 页表页，4MB 只需 2 个。

#### 2.1.4 用户程序裁剪 (Makefile)

UPROGS 从 20 个裁剪到 11 个必要程序:
cat, echo, grep, init, kill, ln, ls, mkdir, rm, sh, wc

#### 2.1.5 简化磁盘接口 (kernel/virtio_disk.c)

重写为简化 MMIO 磁盘接口，替代标准 virtio 协议:

```c
#define DISK_BLOCKNO   0x10001000L  // 写: 设置块号
#define DISK_STATUS    0x10001008L  // 读: 1=就绪
#define DISK_DATA_BASE 0x10001100L  // 读: 1KB 数据窗口
```

### 2.2 仿真侧修改 (difftest/)

#### 2.2.1 RAM 大小 (src/test/csrc/common/ram.h + ram.cpp)

```
EMU_RAM_SIZE: 256MB → 224KB
```

在 ram.cpp 中用 `#undef/#define` 强制覆盖 (绕过 ccache 缓存)。

#### 2.2.2 磁盘加载 (src/test/csrc/common/sdcard.cpp)

重写 `init_sd()`: 用 `getenv("SDCARD_IMAGE")` 运行时加载磁盘镜像到内存缓冲。

添加 `disk_read_helper(blockno, offset)`: 
- 将 fs.img 加载到内存 `disk_buf`
- offset 向下对齐到 8 字节边界 (修复数据对齐 bug)
- 返回 8 字节数据供 CPU 按字节通道提取

**关键 bug 修复**: `disk_read_helper` 原来直接用 offset 读取，但 CPU 的 `mem_byte_shift = addr[2:0]`，需要 8 字节对齐的基地址 + 右移提取。修复后 `offset & ~7ULL`。

#### 2.2.3 磁盘 MMIO 响应 (src/test/vsrc/common/ram.sv)

在 ram.sv 中添加磁盘 MMIO 响应:

```systemverilog
// 写入
64'h10001000: disk_blockno <= oreq.data[31:0];  // DISK_BLOCKNO

// 读取
64'h10001008: oresp.data = 64'd1;               // DISK_STATUS: always ready
default: if (addr >= 0x10001100 && addr < 0x10001500)
    oresp.data = disk_read_helper(disk_blockno, addr - 0x10001100);
```

### 2.3 CPU 修改 (vsrc/)

#### 2.3.1 TLB 实现 (vsrc/util/mmu.sv)

**问题**: MMU 无 TLB，每次访问都 walk 页表 (3 次内存读取)。WALK_IDLE 状态中指令 fetch 优先于数据访问，导致数据 Load 被饿死。

**修复**: 实现 1-entry 指令 TLB + 2-entry 数据 TLB:

- TLB 命中时直接使用缓存的 PA，跳过 page walk
- walk 完成时更新 TLB (LRU 替换策略)
- satp 变化时清空 TLB (检测页表切换)
- trap 时不清 TLB (同一页表，条目仍有效)
- `walk_active` 优先于 TLB 命中 (避免 PTE 读取被 TLB 干扰)

#### 2.3.2 Trap/Redirect 调试 (vsrc/src/core/core_csr.sv)

添加 $display 追踪所有 trap 和 redirect:
- `TRAP: INTR` — 中断
- `TRAP: EXC` — 异常 (ecall, illegal 等)
- `REDIR: MRET` — mret 返回
- `REDIR: SRET` — sret 返回

---

## 三、诊断过程与发现

### 3.1 difftest 模式问题

`--diff` 模式在 pc=0x80000030 处失败:
```
csrr a5, 0x30a  (读取 mhpmevent11)
NEMU: illegal instruction (mcause=2)
CPU：不触发异常，返回 a5=0
```

**原因**: CPU 对未实现的 CSR 访问不触发 illegal instruction 异常。

### 3.2 xv6 启动问题排查

| 阶段 | 问题 | 修复 |
|------|------|------|
| kinit | 清零 128MB 太慢 (memset 无限循环) | PHYSTOP → 224KB |
| kvminit | PLIC 64MB 映射需太多页表页 | PLIC → 4MB |
| kalloc | 160KB 不够 exec 分配 | PHYSTOP → 224KB |
| virtio_disk_init | 仿真侧无 virtio 磁盘模型 | 实现简化 MMIO 磁盘 |
| fsinit | 磁盘数据 8 字节对齐错误 | disk_read_helper offset 对齐 |
| exec | uvmalloc 栈分配失败 (内存不足) | PHYSTOP → 224KB |
| printf | 只输出 1 个字符就停 | TLB 实现 + 数据 walk 饿死修复 |

### 3.3 当前状态

```
xv6 kernel is booting       ← 启动成功
i                           ← printf("init: starting sh\n") 第一个字符
                            ← CPU 进入 scheduler 空转
```

Trap 序列显示:
1. MRET → main (S-mode)
2. SRET → /init 入口 0xe4 (U-mode)
3. EXC cause=8 (ecall open) → SRET 返回
4. EXC cause=8 (ecall mknod) → SRET 返回
5. EXC cause=8 (ecall open) → SRET 返回
6. EXC cause=8 (ecall dup) × 2 → SRET 返回
7. EXC cause=8 (ecall write) → 输出 'i' → SRET 返回
8. EXC cause=8 (ecall write) ← 第二次 write 发生！

**关键发现**: 第二次 write 确实发生了，但输出 'n' 不可见。问题可能在:
- UART 输出缓冲/时序
- printf 的 *s Load 读取了错误数据
- write 系统调用内部处理问题

---

## 四、内存布局

### 4.1 仿真内存 (224KB)

```
0x80000000 - 0x8000a000  .text + .rodata (~40KB)
0x8000a820 - 0x8000a830  .data (16B)
0x8000a830 - 0x8000e1b0  .bss (~19KB, end=0x8000e1b0)
0x8000e1b0 - 0x80038000  kalloc 空闲页 (~167KB, ~41 页)
```

### 4.2 FPGA 内存 (164KB BRAM)

- BRAM IP: 64-bit × 21000 = 164KB
- kernel 占用 ~57KB
- kalloc 可用 ~107KB = ~26 页
- fs.img 在 SPI Flash (0x300000 偏移)

### 4.3 磁盘接口

| 地址 | 用途 |
|------|------|
| 0x10001000 | DISK_BLOCKNO (写块号) |
| 0x10001008 | DISK_STATUS (读就绪) |
| 0x10001100-0x100014FF | DISK_DATA_BASE (1KB 数据窗口) |

---

## 五、文件修改清单

### xv6 内核
- `third_party/xv6-riscv/kernel/param.h` — 参数裁剪
- `third_party/xv6-riscv/kernel/memlayout.h` — PHYSTOP 224KB
- `third_party/xv6-riscv/kernel/vm.c` — PLIC 4MB + copyin 调试(残留)
- `third_party/xv6-riscv/kernel/virtio_disk.c` — 简化磁盘接口
- `third_party/xv6-riscv/kernel/exec.c` — 调试代码(部分残留)
- `third_party/xv6-riscv/kernel/trap.c` — 调试代码(部分残留)
- `third_party/xv6-riscv/Makefile` — UPROGS 裁剪

### 仿真侧
- `difftest/src/test/csrc/common/ram.h` — EMU_RAM_SIZE 224KB
- `difftest/src/test/csrc/common/ram.cpp` — 强制 224KB + KB 格式
- `difftest/src/test/csrc/common/sdcard.cpp` — 运行时加载 + disk_read_helper
- `difftest/src/test/vsrc/common/ram.sv` — 磁盘 MMIO 响应

### CPU
- `vsrc/util/mmu.sv` — TLB 实现 (1-entry I-TLB + 2-entry D-TLB)
- `vsrc/src/core/core_csr.sv` — Trap/redirect 调试

---

## 六、后续工作

1. **诊断 printf 停止**: 第二次 write 发生但输出不可见，需追踪 write 系统调用内部的 consputc/copyin
2. **CSR illegal instruction**: CPU 对未实现 CSR 不触发异常，影响 --diff 模式
3. **清理调试代码**: exec.c/trap.c/vm.c 有残留调试 printf，需清理
4. **FPGA 适配**: BRAM IP 需从 164KB 扩展到 224KB，或进一步优化 BSS
5. **SPI Flash 磁盘**: FPGA 侧需实现 SPI Flash 磁盘控制器 (已有 spi_flash_disk.sv)
