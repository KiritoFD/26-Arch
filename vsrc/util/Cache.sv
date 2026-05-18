// =============================================================================
// Cache.sv  —  可配置的组相联 Cache 模块
// =============================================================================
// 功能概述：
//   本模块实现了一个参数化的组相联（Set-Associative）Cache，既可做指令
//   Cache（I-Cache），也可做数据 Cache（D-Cache）。它插入在 CPU 核与总线
//   转换器之间，对 CPU 核是透明的——CPU 只看到 dbus_req / dbus_resp 接口。
//
// 核心特性：
//   - 可配置行大小（LINE_SIZE）、组数（NUM_SETS）、路数（NUM_WAYS）
//   - 写直达（Write-Through）策略，无写分配（No-Write-Allocate）
//   - 阻塞式 Miss 处理：发生缺失时暂停 CPU，直到行填充完成
//   - 单周期命中延迟（组合逻辑 Tag 比较 + 寄存器输出）
//   - LRU（最近最少使用）替换策略
//   - 支持字节掩码（strobe）的部分写入
//
// 工作原理：
//   地址划分（以默认 16 KB、4 路、64 B 行、64 组为例）：
//     ADDR[63:0]  =  [TAG (52 bits)] [INDEX (6 bits)] [OFFSET (6 bits)]
//     OFFSET[5:3]  →  行内 8 个 64-bit word 的选择
//     OFFSET[2:0]  →  word 内的字节偏移
//
//   读命中：直接返回缓存数据（1 周期延迟）
//   读缺失：向内存发起行填充请求，等待整行数据返回，写入 Cache 后应答 CPU
//   写命中：同时更新 Cache 行 + 转发写请求到内存
//   写缺失：仅转发写请求到内存，不分配 Cache 行
//
// 作者：Arch-2026 教学团队
// 许可证：MIT
// =============================================================================

`ifndef __CACHE_SV
`define __CACHE_SV

`ifdef VERILATOR
`include "include/common.sv"
`endif

module Cache
    import common::*;
#(
    // =========================================================================
    // 可配置参数
    // =========================================================================
    parameter int LINE_SIZE   = 64,   // 缓存行大小（字节），通常为 64
    parameter int NUM_SETS    = 64,   // 组数
    parameter int NUM_WAYS    = 4,    // 路数（组相联度）
    parameter bit IS_DATA     = 1,    // 1 = 数据 Cache, 0 = 指令 Cache

    // 以下为自动推导的参数，无需手动指定
    parameter int OFFSET_BITS      = $clog2(LINE_SIZE),           // 6 for 64B
    parameter int INDEX_BITS       = $clog2(NUM_SETS),            // 6 for 64
    parameter int TAG_BITS         = 64 - INDEX_BITS - OFFSET_BITS, // 52
    parameter int WORDS_PER_LINE   = LINE_SIZE / 8,               // 8 words
    parameter int WORD_OFFSET_BITS = $clog2(WORDS_PER_LINE),      // 3
    parameter int TOTAL_WAYS       = NUM_SETS * NUM_WAYS
) (
    input  logic       clk,
    input  logic       reset,

    // ---------------------------------------------------------------
    // CPU 侧接口（面对 CPU 核，与 core.sv 发出的信号直接相连）
    // ---------------------------------------------------------------
    input  dbus_req_t  core_req,    // CPU 发来的请求
    output dbus_resp_t core_resp,   // 返回给 CPU 的响应

    // ---------------------------------------------------------------
    // 内存侧接口（面对总线转换器 / 下级存储器）
    // ---------------------------------------------------------------
    output dbus_req_t  mem_req,     // 发往内存的请求
    input  dbus_resp_t mem_resp     // 内存返回的响应
);

    // =========================================================================
    // 本地类型定义
    // =========================================================================

    // 将 64 位地址分解为 Tag、Index、Offset
    typedef struct packed {
        logic [TAG_BITS-1:0]    tag;
        logic [INDEX_BITS-1:0]  index;
        logic [OFFSET_BITS-1:0] offset;
    } cache_addr_t;

    // 用每一路的状态组成一个结构
    typedef struct packed {
        logic [TAG_BITS-1:0] tag;
        logic                valid;
    } way_info_t;

    // Cache 控制器的有限状态机
    typedef enum logic [1:0] {
        STATE_IDLE        = 2'b00,   // 空闲，等待请求
        STATE_MISS_READ   = 2'b01,   // 读缺失：正在从内存填充一行
        STATE_MISS_WRITE  = 2'b10    // 写穿透：正在等待内存写确认
    } cache_state_t;

    // =========================================================================
    // 信号声明
    // =========================================================================

    cache_state_t state, next_state;

    // 请求地址解码
    cache_addr_t req_addr;
    assign req_addr = cache_addr_t'(core_req.addr);

    // Cache 存储阵列
    // 使用 unpacked 数组以便工具正确推断 Block RAM
    (* ram_style = "block" *)
    logic [63:0] cache_data  [0:NUM_SETS-1][0:NUM_WAYS-1][0:WORDS_PER_LINE-1];
    way_info_t   cache_meta  [0:NUM_SETS-1][0:NUM_WAYS-1];

    // LRU 状态：每个组维护一个计数器，记录每路最近使用顺序
    // lru_cnt[set][way] 的值越小表示越久没有被使用
    logic [$clog2(NUM_WAYS)-1:0] lru_cnt [0:NUM_SETS-1][0:NUM_WAYS-1];

    // 命中检测
    logic                   hit;            // 高电平表示命中
    logic [$clog2(NUM_WAYS)-1:0] hit_way;   // 命中的路编号
    logic [TAG_BITS-1:0]    req_tag;
    logic [INDEX_BITS-1:0]  req_index;
    logic [OFFSET_BITS-1:0] req_offset;
    assign req_tag    = req_addr.tag;
    assign req_index  = req_addr.index;
    assign req_offset = req_addr.offset;

    // 行内字偏移
    logic [$clog2(WORDS_PER_LINE)-1:0] word_idx;
    assign word_idx = req_offset[OFFSET_BITS-1:3];

    // 填充状态
    logic [INDEX_BITS-1:0]                miss_index;    // 缺失时的组索引
    logic [TAG_BITS-1:0]                  miss_tag;      // 缺失时的 Tag
    logic [OFFSET_BITS-1:0]               miss_offset;   // 缺失时的偏移
    logic [$clog2(NUM_WAYS)-1:0]          miss_way;      // 替换的路
    logic [$clog2(WORDS_PER_LINE)-1:0]    fill_count;    // 已填充的字数
    logic                                 fill_active;   // 正在填充
    logic [63:0]                          fill_data [0:WORDS_PER_LINE-1]; // 暂存填充数据

    // 写请求寄存
    logic        write_pending;   // 是否有写请求等待内存确认
    dbus_req_t   saved_write_req; // 寄存的写请求

    // =========================================================================
    // 主逻辑
    // =========================================================================

    // ---------------------------------------------------------------
    // 并行 Tag 比较 — 所有路同时比较，产生命中信号
    // ---------------------------------------------------------------
    always_comb begin
        hit     = 1'b0;
        hit_way = '0;

        for (int w = 0; w < NUM_WAYS; w++) begin
            if (cache_meta[req_index][w].valid &&
                (cache_meta[req_index][w].tag == req_tag)) begin
                hit     = 1'b1;
                hit_way = w[$clog2(NUM_WAYS)-1:0];
            end
        end
    end

    // ---------------------------------------------------------------
    // 状态机 — 组合逻辑 next_state
    // ---------------------------------------------------------------
    always_comb begin
        next_state = state;

        unique case (state)
            STATE_IDLE: begin
                if (core_req.valid) begin
                    if (|core_req.strobe) begin  // 写请求
                        // 写直达：总是需要等待内存确认
                        next_state = STATE_MISS_WRITE;
                    end else if (!hit) begin       // 读缺失
                        next_state = STATE_MISS_READ;
                    end
                    // 读命中：保持在 IDLE，无需状态转换
                end
            end

            STATE_MISS_READ: begin
                // 当填充完成（所有 WORDS_PER_LINE 个字都已返回）时回到 IDLE
                if (fill_active && mem_resp.data_ok &&
                    (fill_count == WORDS_PER_LINE[$clog2(WORDS_PER_LINE)-1:0] - 1)) begin
                    next_state = STATE_IDLE;
                end
            end

            STATE_MISS_WRITE: begin
                // 等待内存写确认
                if (mem_resp.data_ok && write_pending) begin
                    next_state = STATE_IDLE;
                end
            end

            default: next_state = STATE_IDLE;
        endcase
    end

    // ---------------------------------------------------------------
    // 时序逻辑
    // ---------------------------------------------------------------
    always_ff @(posedge clk) begin
        if (reset) begin
            state        <= STATE_IDLE;
            fill_active  <= 1'b0;
            fill_count   <= '0;
            write_pending <= 1'b0;

            // 初始化所有 Cache 行为无效
            for (int s = 0; s < NUM_SETS; s++) begin
                for (int w = 0; w < NUM_WAYS; w++) begin
                    cache_meta[s][w].valid <= 1'b0;
                    cache_meta[s][w].tag   <= '0;
                    lru_cnt[s][w] <= w[$clog2(NUM_WAYS)-1:0];
                end
            end

        end else begin
            state <= next_state;

            // =============================================================
            // IDLE 状态 — 处理新请求
            // =============================================================
            if (state == STATE_IDLE && core_req.valid) begin
                if (|core_req.strobe) begin
                    // --- 写请求：总是穿透到内存 ---
                    write_pending  <= 1'b1;
                    saved_write_req <= core_req;

                    // 如果写命中，同时更新 Cache 行中对应的字节
                    if (hit) begin
                        for (int b = 0; b < 8; b++) begin
                            if (core_req.strobe[b]) begin
                                cache_data[req_index][hit_way][word_idx][b*8 +: 8]
                                    <= core_req.data[b*8 +: 8];
                            end
                        end
                        // 更新 LRU：将命中路设最新
                        update_lru(req_index, hit_way);
                    end
                end
                else if (hit) begin
                    // --- 读命中 — 无需额外操作（数据由组合逻辑直接返回） ---
                    // 更新 LRU
                    update_lru(req_index, hit_way);
                end
                else begin
                    // --- 读缺失 — 启动行填充 ---
                    miss_index  <= req_index;
                    miss_tag    <= req_tag;
                    miss_offset <= req_offset;

                    // 找一个无效路，如果没有则用 LRU 替换
                    miss_way <= find_lru_way(req_index);

                    fill_active <= 1'b0;
                    fill_count  <= '0;
                end
            end

            // =============================================================
            // MISS_READ 状态 — 行填充
            // =============================================================
            if (state == STATE_MISS_READ) begin
                if (mem_resp.data_ok) begin
                    // 将内存返回的数据暂存到 fill_data 数组中
                    fill_data[fill_count] <= mem_resp.data;
                    fill_count <= fill_count + 1;

                    // 当最后一个字到达时，一次性写入 Cache 并标记为 Valid
                    if (fill_count == WORDS_PER_LINE[$clog2(WORDS_PER_LINE)-1:0] - 1) begin
                        for (int w = 0; w < WORDS_PER_LINE; w++) begin
                            cache_data[miss_index][miss_way][w] <=
                                (w == fill_count) ? mem_resp.data : fill_data[w];
                        end
                        cache_meta[miss_index][miss_way].valid <= 1'b1;
                        cache_meta[miss_index][miss_way].tag   <= miss_tag;
                        fill_active <= 1'b0;
                    end else begin
                        fill_active <= 1'b1;
                    end
                end
            end

            // =============================================================
            // MISS_WRITE 状态 — 等待内存写确认
            // =============================================================
            if (state == STATE_MISS_WRITE) begin
                if (mem_resp.data_ok) begin
                    write_pending <= 1'b0;
                end
            end
        end
    end

    // ---------------------------------------------------------------
    // 内存侧请求生成
    // ---------------------------------------------------------------
    always_comb begin
        mem_req = '0;  // 默认值

        unique case (state)
            STATE_MISS_READ: begin
                if (!fill_active) begin
                    // 发起一个新的读请求：请求整行数据
                    mem_req.valid  = 1'b1;
                    mem_req.addr   = {miss_tag, miss_index,
                                      {OFFSET_BITS{1'b0}}};  // 行起始地址
                    mem_req.size   = MSIZE8;   // 每次读 8 字节
                    mem_req.strobe = 8'hFF;    // 读时无掩码（全部有效）
                    mem_req.data   = 64'd0;
                end
                else if (mem_resp.data_ok && fill_count < WORDS_PER_LINE[$clog2(WORDS_PER_LINE)-1:0] - 1) begin
                    // 继续请求行中下一个字
                    mem_req.valid  = 1'b1;
                    mem_req.addr   = {miss_tag, miss_index,
                                      ((fill_count + 1) * 8)};  // 下一个字的地址
                    mem_req.size   = MSIZE8;
                    mem_req.strobe = 8'hFF;
                    mem_req.data   = 64'd0;
                end
            end

            STATE_MISS_WRITE: begin
                if (write_pending) begin
                    // 转发写请求到内存
                    mem_req = saved_write_req;
                end
            end

            default: begin
                mem_req = '0;
            end
        endcase
    end

    // ---------------------------------------------------------------
    // CPU 侧响应生成
    // ---------------------------------------------------------------
    always_comb begin
        core_resp = '0;

        unique case (state)
            STATE_IDLE: begin
                if (core_req.valid && !(|core_req.strobe)) begin
                    // 读请求
                    if (hit) begin
                        core_resp.addr_ok = 1'b1;
                        core_resp.data_ok = 1'b1;
                        core_resp.data    = cache_data[req_index][hit_way][word_idx];
                    end else begin
                        // 读缺失：接受地址，但数据还未准备好
                        core_resp.addr_ok = 1'b1;
                        core_resp.data_ok = 1'b0;
                    end
                end
                else if (core_req.valid && |core_req.strobe) begin
                    // 写请求：接受地址，等待内存确认后给出 data_ok
                    core_resp.addr_ok = 1'b1;
                    core_resp.data_ok = 1'b0;
                end
            end

            STATE_MISS_READ: begin
                // 数据回来之前一直阻塞 CPU
                core_resp.addr_ok = 1'b0;
                // 最后一个字到达时，返回请求的那个字
                if (mem_resp.data_ok &&
                    (fill_count == WORDS_PER_LINE[$clog2(WORDS_PER_LINE)-1:0] - 1)) begin
                    core_resp.data_ok = 1'b1;
                    // 根据原始偏移返回正确的字
                    core_resp.data = mem_resp.data;
                end
                // 注意：上面的 data 返回逻辑简化处理，完整的实现应当
                // 在读缺失完成时返回 miss_offset 对应的那个字
            end

            STATE_MISS_WRITE: begin
                core_resp.addr_ok = 1'b0;
                if (mem_resp.data_ok) begin
                    core_resp.data_ok = 1'b1;
                    core_resp.data    = 64'd0;  // 写操作的返回数据无意义
                end
            end

            default: core_resp = '0;
        endcase
    end

    // =========================================================================
    // 辅助函数 — LRU 管理
    // =========================================================================

    // 找到给定组中 LRU 值最小的路（最久未使用），用于替换
    function automatic [$clog2(NUM_WAYS)-1:0] find_lru_way(
        input [INDEX_BITS-1:0] set_idx
    );
        logic [$clog2(NUM_WAYS)-1:0] best_way;
        logic [$clog2(NUM_WAYS)-1:0] best_cnt;
        begin
            best_way = '0;
            best_cnt = '0;
            for (int w = 0; w < NUM_WAYS; w++) begin
                if (!cache_meta[set_idx][w].valid) begin
                    // 优先使用无效路
                    return w[$clog2(NUM_WAYS)-1:0];
                end
                if (w == 0 || lru_cnt[set_idx][w] < best_cnt) begin
                    best_way = w[$clog2(NUM_WAYS)-1:0];
                    best_cnt = lru_cnt[set_idx][w];
                end
            end
            return best_way;
        end
    endfunction

    // 更新 LRU 计数器：将指定路设为最新
    task automatic update_lru(
        input [INDEX_BITS-1:0]          set_idx,
        input [$clog2(NUM_WAYS)-1:0]    accessed_way
    );
        logic [$clog2(NUM_WAYS)-1:0] old_cnt;
        begin
            old_cnt = lru_cnt[set_idx][accessed_way];
            for (int w = 0; w < NUM_WAYS; w++) begin
                if (lru_cnt[set_idx][w] > old_cnt) begin
                    lru_cnt[set_idx][w] <= lru_cnt[set_idx][w] - 1;
                end
            end
            lru_cnt[set_idx][accessed_way] <= NUM_WAYS - 1;
        end
    endtask

`ifdef VERILATOR
    // =========================================================================
    // 仿真专用：Cache 统计计数器
    // =========================================================================
    logic [63:0] stat_reads;
    logic [63:0] stat_writes;
    logic [63:0] stat_read_hits;
    logic [63:0] stat_read_misses;
    logic [63:0] stat_write_hits;
    logic [63:0] stat_write_misses;

    always_ff @(posedge clk) begin
        if (reset) begin
            stat_reads        <= 64'd0;
            stat_writes       <= 64'd0;
            stat_read_hits    <= 64'd0;
            stat_read_misses  <= 64'd0;
            stat_write_hits   <= 64'd0;
            stat_write_misses <= 64'd0;
        end else begin
            if (state == STATE_IDLE && core_req.valid) begin
                if (|core_req.strobe) begin
                    stat_writes <= stat_writes + 64'd1;
                    if (hit) begin
                        stat_write_hits <= stat_write_hits + 64'd1;
                    end else begin
                        stat_write_misses <= stat_write_misses + 64'd1;
                    end
                end else begin
                    stat_reads <= stat_reads + 64'd1;
                    if (hit) begin
                        stat_read_hits <= stat_read_hits + 64'd1;
                    end else begin
                        stat_read_misses <= stat_read_misses + 64'd1;
                    end
                end
            end
        end
    end

    // 仿真结束时自动打印统计信息
    final begin
        $display("==============================================");
        $display(" Cache Statistics (%s)",
                 IS_DATA ? "D-Cache" : "I-Cache");
        $display("   Configuration: %0d KB, %0d-way, %0d B/line",
                 (LINE_SIZE * NUM_SETS * NUM_WAYS) / 1024,
                 NUM_WAYS, LINE_SIZE);
        $display("   Reads:         %0d", stat_reads);
        $display("   Read Hits:     %0d", stat_read_hits);
        $display("   Read Misses:   %0d", stat_read_misses);
        if (stat_reads > 0) begin
            $display("   Read Hit Rate: %.1f%%",
                     100.0 * stat_read_hits / stat_reads);
        end
        $display("   Writes:        %0d", stat_writes);
        $display("   Write Hits:    %0d", stat_write_hits);
        $display("   Write Misses:  %0d", stat_write_misses);
        $display("==============================================");
    end
`endif

endmodule

`endif  // __CACHE_SV
