# lab5 实现说明

## 1. 任务概述

lab5 要求在自研 CPU 上运行一个简化的 xv6 内核，完成 `kinit → procinit → trapinit → plicinit → userinit → scheduler` 的启动流程，最终由 `userinit` 内嵌的 initcode 打印 `Return from init! Test passed`。

本报告记录仿真调通过程中的关键问题与修复，并给出上板准备步骤。

## 2. 仿真环境

### 2.1 磁盘 MMIO 模型

上游 lab5 的 `kernel.bin`（8720B）本身不访问磁盘，但仿真环境仍需为 difftest 提供一致的设备语义。`difftest/src/test/vsrc/common/ram.sv` 中实现了简化的磁盘 MMIO：

- `0x10001000`（写）：寄存存 blockno
- `0x10001008`（读）：磁盘状态，恒返回 1（ready）
- `0x10001100 ~ 0x10001500`（读）：按 `blockno * 1024 + offset` 从 `SDCARD_IMAGE` 镜像取 8 字节

数据来源由 `difftest/src/test/csrc/common/sdcard.cpp` 的 `disk_read_helper` 提供，启动时通过环境变量 `SDCARD_IMAGE` 加载镜像到内存。

### 2.2 difftest skip 机制

磁盘 MMIO 访问属于仿真侧外挂设备，NEMU 参考模型不感知。`ram.sv` 在 DUT 侧拦截这些地址后，通过 difftest 的 `skip` 机制把 DUT 结果同步给 NEMU，避免寄存器比对失败。因此磁盘 MMIO 必须始终启用——曾尝试用 `NO_DISK_MMIO` 条件编译为 lab5 关闭磁盘 MMIO，结果 difftest 因失去 skip 同步而崩溃，故最终保持始终启用。

### 2.3 内存与串口

- `ram.cpp`：`EMU_RAM_SIZE` 由 224KB 提升到 1MB，避免 `exec("sh")` 时 kalloc 池耗尽
- `uart.cpp`：重写为 `stdin_reader_thread` 后台线程读取 stdin，支持交互终端
- `ram.sv`：`0x10000000` RHR 读取返回 0（仿真无输入），`0x10000005` LSR 返回 `0x60`（THRE/TEMT 就绪）

## 3. 调试过程

### 3.1 现象

仿真启动后内核正常打印 `kinit/procinit/trapinit/plicinit/userinit` 各阶段日志，`forkret` 中 `fsinit` 也通过，但随后 `exec /init` 失败：

```
[DBG] forkret: kexec /init...
[DBG] exec: /init
DISK_RD_OOB: blockno=170 offset=0 pos=174080 size=53248
...
exec: bad ELF magic 0x0
panic: exec
```

`blockno=170` 对应字节偏移 174080，但 `fs_mini.img` 仅 53248 字节，读取越界返回 0，被识别为非法 ELF。

### 3.2 条件编译定位

为确认内核、镜像、MMIO 地址三者是否匹配，在 `ram.sv` 和 `sdcard.cpp` 中加入 `LAB5_DEBUG` 条件编译打印：

```systemverilog
`ifdef LAB5_DEBUG
  $display("LAB5_DBG: WRITE blockno=%0d addr=0x%x", oreq.data[31:0], oreq.addr);
`endif
```

编译时通过 `USER_VEXTRA_FLAGS=+define+LAB5_DEBUG -CFLAGS -DLAB5_DEBUG` 同时向 Verilog 和 C++ 传递宏。运行后确认：

- 内核路径、磁盘路径、MMIO 地址（`0x10001000`/`0x10001100`）全部正确
- `blockno=170` 确由 CPU 正确写入，非 MMIO 解析错误
- `fsinit` 读取 block 1（superblock）正常，元数据解析成功

### 3.3 镜像解析

用 Python 解析 `fs_mini.img`：

| 字段 | 值 |
|------|-----|
| 镜像大小 | 53248 字节（52 块） |
| superblock magic | 0x10203040 |
| size | 2000 块（2MB） |
| nblocks | 1971 |
| inodestart | 15 |
| inode 1（root） | type=0, size=0, addrs 全 0 |
| inode 8（/init） | type=2, size=36040, addrs[0]=170 |

关键矛盾：superblock 声明 2000 块（2MB），但镜像实际只有 52 块；root inode 全 0，/init 的 `addrs[0]=170` 越界。结论是 `fs_mini.img` 是从 2MB 完整镜像裁剪出来的损坏副本。

### 3.4 上游对比

访问上游仓库 `github.com/26-Arch/26-Arch` 的 `ready-to-run/lab5/` 目录，发现：

- **上游没有 `fs_mini.img`**
- 上游 `kernel.bin` 仅 8720B，而本地是 40368B
- 反汇编上游 `kernel.asm`，`main` 函数只调用 `kinit/procinit/trapinit/plicinit/userinit/scheduler`，`userinit` 内嵌 initcode 直接打印 `Return from init! Test passed`，**完全不访问磁盘**

本地 40368B 的 `kernel.bin` 是带文件系统的魔改版，会执行 `fsinit` 与 `exec /init`，需要完整 2MB 的 `fs.img`，而 `fs_mini.img` 只有 52KB 且已损坏——这是 `bad ELF magic 0x0` 的根本原因。

## 4. 修复方案

1. 备份本地魔改版为 `kernel.bin.local_mod` / `kernel.asm.local_mod`
2. 下载上游原版 `kernel.bin`（8720B）/ `kernel.asm`（130325B）替换
3. 用 `bin2coe.py` 重新生成 `kernel.coe`
4. 用 `gen_xv6_coe.py` 重新生成 `xv6-kernel.coe`（depth=21000，BRAM 初始化用）
5. 重建干净 emu（不带 `LAB5_DEBUG`），所有测试共用同一份 emu

`LAB5_DEBUG` 条件打印用 `#ifdef` / `` `ifdef `` 包裹，默认不启用，不影响其他测试。

## 5. 仿真结果

```
xv6 kernel is booting
kinit ok
procinit ok
trapinit ok
plicinit ok
userinit ok
Return from init! Test passed
```

lab5 通过，其他 lab 测试不受影响（共用同一份干净 emu）。

## 6. 上板准备

### 6.1 BRAM 初始化文件

上游原版 `kernel.bin`（8720B）不访问磁盘，上板只需 BRAM 中的 kernel，无需 SPI Flash 存 fs.img。已重新生成：

- `ready-to-run/lab5/kernel.coe`（bin2coe.py，1092 条目）
- `ready-to-run/lab5/xv6-kernel.coe`（gen_xv6_coe.py，21000 条目，填充 0 至 BRAM 深度）

`vivado/lab5_project/lab5_project.xpr` 引用的 COE 为 `$PPRDIR/../../ready-to-run/lab5/xv6-kernel.coe`，已更新。

### 6.2 上板步骤

1. 在 Vivado 打开 `vivado/lab5_project/lab5_project.xpr`
2. 确认 BRAM IP 引用的 COE 已更新为新 `xv6-kernel.coe`
3. Run Synthesis → Run Implementation → Generate Bitstream
4. 用 JTAG 烧写 bitstream 到 Basys3（或生成 MCS 烧写 SPI Flash 以持久化）
5. 上电后观察 UART 输出，应依次打印 `kinit ok / procinit ok / trapinit ok / plicinit ok / userinit ok / Return from init! Test passed`

### 6.3 注意事项

- 上游 kernel 不读磁盘，故无需 SPI Flash fs.img，`full_flash.mcs`（xv6 用）不适用于 lab5
- 若需交互式 shell，应使用 xv6 内核（`test-xv6` 目标）配合 SPI Flash 存 fs.img
- Basys3 FT2232H 需配置为 Port A=UART+VCP、Port B=FIFO(JTAG)，详见 `docs/basys3_eeprom_troubleshooting.md`
