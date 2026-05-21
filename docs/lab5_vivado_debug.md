# Lab5 Vivado / 上板排查记录

## 当前结论

截至 2026-05-21，本仓库的 Lab5 已经满足以下条件：

- `make test-lab5` 能输出正确的 xv6 启动日志
- `vivado/test-cpu/project/project_3` 已重新综合、实现并生成 bitstream
- 实现通过，时序满足要求
- 板上串口最终可在 `COM4 @ 115200` 下输出正确结果

正确输出为：

```text
xv6 kernel is booting
kinit ok
procinit ok
trapinit ok
plicinit ok
userinit ok
Return from init! Test passed
```

## 这次真正修掉的问题

### 1. 原先烧录的不是 Lab5 镜像

`project_3` 的 `bram_0` 最初仍指向旧的测试镜像，因此早期板上出现的单个 `A` 或异常输出，不能直接用来判断 Lab5 RTL 对错。

已修复为使用：

- `ready-to-run/lab5/kernel.coe`

### 2. Vivado 设备路径没有完整传递写掩码

Lab5 内核通过字节写访问 UART。原先 Vivado 板级路径里，`wstrobe` 没有被完整传到 UART 设备，导致发送字节 lane 选择错误。

已修复文件：

- `vivado/src/device.sv`
- `vivado/src/with_delay/cbus_crossbar.sv`
- `vivado/src/with_delay/soc_top.sv`
- `project_3` 工程导入副本中的对应文件

### 3. 串口乱码的根因是波特率 / 分频不匹配

这次板上“只输出一个 `A`”以及后续的乱码，最终确认不是 CPU 没跑通，而是 UART 分频常量与实际 `cpu_clk` 不匹配。

板级 `cpu_clk` 实际为 `25MHz`，但 `device.sv` 中 UART 仍使用旧常量：

```text
BIT_TMR_MAX = 2603
```

修正后改为：

```text
BIT_TMR_MAX = 216
```

因此板上串口调试工具必须使用：

- 端口：`COM4`
- 波特率：`115200`

而不是：

- `COM20`
- 错误波特率（如 `57600`、`38400` 等）

### 4. 32-cycle BRAM 延迟路径没有锁存完整事务

Vivado 的 `with_delay` BRAM 包装路径原先在固定延迟期间没有稳定保存完整访存上下文，导致返回阶段可能拿到错位地址或控制信息。

已修复文件：

- `vivado/src/with_delay/bram_wrapper.sv`
- `project_3` 工程导入副本中的对应文件

### 5. 核心总线桥接会把旧响应当成新请求完成

这也是 Verilator 和板级路径都受影响的关键 RTL 问题。修复点包括：

- `vsrc/util/DBusToCBus.sv`
- `vsrc/util/IBusToCBus.sv`
- `vsrc/VTop.sv`
- `vsrc/SimTop.sv`
- `vsrc/src/core.sv`
- `difftest/src/test/vsrc/common/ram.sv`

修复后可以保证一次请求只对应一次完成脉冲，并且在 trap / redirect 后丢弃旧的取指返回。

## 最终可用工程

本次最终确认可用于 Lab5 的 Vivado 工程为：

- `vivado/test-cpu/project/project_3/project_3.xpr`

仓库中也整理了一个可直接查看的工程：

- `vivado/lab5_project/lab5_project.xpr`

## 实操备注

如果上板后再次看到乱码，优先检查以下三项：

1. 打开的串口是否为 `COM4`
2. 波特率是否为 `115200`
3. 烧录的 bitstream 是否来自 `project_3.runs/impl_1/basys3_top.bit`
