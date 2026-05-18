// =============================================================================
// SimpleMem.sv  —  简易仿真内存模块
// =============================================================================
// 功能概述：
//   本模块实现了一个参数化的仿真内存，使用 CBus 接口（cbus_req / cbus_resp）
//   与上层通信。它模拟了真实 DRAM 的基本行为：可配置的读写延迟、字节掩码
//   写入、以及突发传输支持。
//
// 核心特性：
//   - 可配置容量（MEM_SIZE_MB），默认 128 MB
//   - 可配置读写延迟（LATENCY 个周期）
//   - 支持字节掩码（strobe）写入
//   - 支持突发传输（BURST）
//   - 使用 SystemVerilog unpacked 数组，仿真工具可高效访问
//
// 接口说明：
//   本模块使用 CBus 接口，事务流程如下：
//     1. 主设备拉高 creq.valid，给出地址、数据、控制信号
//     2. 从设备（本模块）在接受请求后，经过 LATENCY 个周期
//     3. 在最后一个周期同时拉高 cresp.ready 和 cresp.last
//     4. 对于读请求，cresp.data 同时有效
//
// 作者：Arch-2026 教学团队
// 许可证：MIT
// =============================================================================

`ifndef __SIMPLEMEM_SV
`define __SIMPLEMEM_SV

`ifdef VERILATOR
`include "include/common.sv"
`endif

module SimpleMem
    import common::*;
#(
    // =========================================================================
    // 可配置参数
    // =========================================================================
    parameter int MEM_SIZE_MB = 128,            // 内存容量（MB）
    parameter int LATENCY     = 4              // 读写延迟（周期数）
) (
    input  logic       clk,
    input  logic       reset,

    // ---------------------------------------------------------------
    // CBus 接口 — 与 CBusArbiter 直接连接
    // ---------------------------------------------------------------
    input  cbus_req_t  creq,     // 主设备发来的请求
    output cbus_resp_t cresp     // 返回给主设备的响应
);

    // =========================================================================
    // 本地参数与常量
    // =========================================================================
    localparam int MEM_SIZE_BYTES     = MEM_SIZE_MB * 1024 * 1024;
    localparam int ADDR_WIDTH         = $clog2(MEM_SIZE_BYTES);
    localparam int BURST_WORDS        = 16;  // 最大突发长度对应的字数

    // =========================================================================
    // 信号声明
    // =========================================================================

    // 内存阵列 — 按 64 位字组织
    // 地址按字对齐（低 3 位忽略），所以总共 MEM_SIZE_BYTES/8 个字
    logic [63:0] mem [0:(MEM_SIZE_BYTES/8)-1];

    // 请求处理管线
    logic        req_accepted;          // 是否接受当前请求
    logic        req_is_write;          // 当前请求是写？
    logic [63:0] req_addr;              // 请求地址
    logic [63:0] req_wdata;             // 写数据
    logic [7:0]  req_strobe;            // 字节掩码

    // 延迟计数器
    logic [15:0] delay_cnt;             // 倒数计数器
    logic        delay_active;          // 正在等待中

    // 响应信号
    logic        resp_ready;
    logic        resp_last;
    logic [63:0] resp_data;

    // 突发传输状态
    logic [7:0]  burst_cnt;             // 当前突发已传字数
    logic [7:0]  burst_len;             // 突发总字数
    logic [63:0] burst_addr;            // 突发起始地址

    // =========================================================================
    // 请求接受逻辑
    // =========================================================================
    assign req_accepted = creq.valid && !delay_active;

    // =========================================================================
    // 延时管线 — 核心时序
    // =========================================================================
    always_ff @(posedge clk) begin
        if (reset) begin
            delay_active <= 1'b0;
            delay_cnt    <= 16'd0;
            req_is_write <= 1'b0;
            req_addr     <= 64'd0;
            req_wdata    <= 64'd0;
            req_strobe   <= 8'd0;
            burst_cnt    <= 8'd0;
            burst_len    <= 8'd0;
            burst_addr   <= 64'd0;
            resp_ready   <= 1'b0;
            resp_last    <= 1'b0;
            resp_data    <= 64'd0;

        end else begin
            // 默认值
            resp_ready <= 1'b0;
            resp_last  <= 1'b0;

            if (!delay_active) begin
                // ---------------------------------------------------------
                // 空闲状态：接受新请求
                // ---------------------------------------------------------
                if (creq.valid) begin
                    // 记录请求信息
                    req_is_write <= creq.is_write;
                    req_addr     <= creq.addr;
                    req_wdata    <= creq.data;
                    req_strobe   <= creq.strobe;
                    burst_addr   <= creq.addr;
                    burst_len    <= {4'd0, creq.len[3:0]} + 8'd1; // len+1 = 总字数
                    burst_cnt    <= 8'd0;

                    // 启动延迟计数
                    delay_active <= 1'b1;
                    delay_cnt    <= LATENCY - 1;
                end
            end
            else begin
                // ---------------------------------------------------------
                // 等待延迟
                // ---------------------------------------------------------
                if (delay_cnt > 0) begin
                    delay_cnt <= delay_cnt - 1;
                end
                else begin
                    // -----------------------------------------------------
                    // 延迟结束：执行实际的内存操作
                    // -----------------------------------------------------

                    // 计算当前访问的字地址（忽略低 3 位）
                    logic [63:0] word_addr;
                    word_addr = (burst_addr >> 3) + burst_cnt;
                    word_addr = word_addr & (MEM_SIZE_BYTES/8 - 1);  // 地址卷绕

                    if (req_is_write) begin
                        // 按字节掩码写入
                        for (int b = 0; b < 8; b++) begin
                            if (req_strobe[b]) begin
                                mem[word_addr][b*8 +: 8] <= req_wdata[b*8 +: 8];
                            end
                        end
                    end
                    else begin
                        // 读取数据
                        resp_data <= mem[word_addr];
                    end

                    // 响应握手
                    resp_ready <= 1'b1;
                    burst_cnt  <= burst_cnt + 8'd1;

                    if (burst_cnt == burst_len - 1) begin
                        // 突发传输结束
                        resp_last    <= 1'b1;
                        delay_active <= 1'b0;
                    end
                end
            end
        end
    end

    // =========================================================================
    // 输出信号连接
    // =========================================================================
    assign cresp.ready = resp_ready;
    assign cresp.last  = resp_last;
    assign cresp.data  = resp_data;

    // =========================================================================
    // 仿真辅助：内存初始化（Verilator 仿真时可用）
    // =========================================================================
`ifdef VERILATOR
    // 允许从外部加载二进制文件到内存
    // 用法：在测试平台中调用 $readmemh("program.hex", SimpleMem.mem);
    // 或使用 Verilator 的 --mem-init 功能

    // 统计计数器
    logic [63:0] stat_reads;
    logic [63:0] stat_writes;

    always_ff @(posedge clk) begin
        if (reset) begin
            stat_reads  <= 64'd0;
            stat_writes <= 64'd0;
        end else begin
            if (resp_ready && resp_last) begin
                if (req_is_write) begin
                    stat_writes <= stat_writes + 64'd1;
                end else begin
                    stat_reads <= stat_reads + 64'd1;
                end
            end
        end
    end

    final begin
        $display("==============================================");
        $display(" SimpleMem Statistics");
        $display("   Capacity: %0d MB", MEM_SIZE_MB);
        $display("   Latency:  %0d cycles", LATENCY);
        $display("   Reads:    %0d", stat_reads);
        $display("   Writes:   %0d", stat_writes);
        $display("==============================================");
    end
`endif

endmodule

`endif  // __SIMPLEMEM_SV
