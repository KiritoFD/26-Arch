`ifdef VERILATOR
`include "include/common.sv"
`include "src/core.sv"
`include "util/IBusToCBus.sv"
`include "util/DBusToCBus.sv"
`include "util/CBusArbiter.sv"
`include "util/mmu.sv"
`endif

`include "device.svh"

module SimTopFPGA import common::*;(
  input         clock,
  input         reset,
  input  [63:0] io_logCtrl_log_begin,
  input  [63:0] io_logCtrl_log_end,
  input  [63:0] io_logCtrl_log_level,
  input         io_perfInfo_clean,
  input         io_perfInfo_dump,
  output        io_uart_out_valid,
  output [7:0]  io_uart_out_ch,
  output        io_uart_in_valid,
  input  [7:0]  io_uart_in_ch
);

    cbus_req_t  oreq;
    cbus_resp_t oresp;
    logic trint, swint, exint;

    // VTop: core + mmu + bus converters + arbiter
    VTop u_vtop(
        .clk(clock),
        .reset(reset),
        .oreq(oreq),
        .oresp(oresp),
        .trint(trint),
        .swint(swint),
        .exint(exint)
    );

    // Interrupts: disabled (same as FPGA)
    assign trint = 1'b0;
    assign swint = 1'b0;
    assign exint = 1'b0;

    // ================================================================
    // CBus → cbus_crossbar signal mapping
    // ================================================================
    logic [63:0] xbar_addr;
    logic [63:0] xbar_wdata;
    logic [1:0]  xbar_burst;
    logic [7:0]  xbar_len;
    logic [7:0]  xbar_wstrobe;
    logic [63:0] xbar_rdata;
    logic        xbar_ready;
    logic        xbar_last;

    assign xbar_addr   = oreq.addr;
    assign xbar_wdata  = oreq.data;
    assign xbar_burst  = oreq.burst;
    assign xbar_len    = oreq.len;
    assign xbar_wstrobe = oreq.strobe;

    assign oresp.ready = xbar_ready;
    assign oresp.last  = xbar_last;
    assign oresp.data  = xbar_rdata;

    // ================================================================
    // cbus_crossbar: routes addr[31]=1 → RAM, addr[31]=0 → Device
    // ================================================================
    logic        ram_valid;
    logic [63:0] ram_addr;
    logic [63:0] ram_wdata;
    logic [1:0]  ram_burst;
    logic [7:0]  ram_len;
    logic [7:0]  ram_wstrobe;
    logic [63:0] ram_rdata;
    logic        ram_ready;
    logic        ram_last;

    logic        device_valid;
    logic [63:0] device_addr;
    logic [63:0] device_wdata;
    logic        device_wvalid;
    logic [7:0]  device_wstrobe;
    logic [63:0] device_rdata;
    logic        device_ready;
    logic        device_last;

    cbus_crossbar u_crossbar(
        .clk(clock),
        .reset(reset),
        .valid(oreq.valid),
        .addr(xbar_addr),
        .wdata(xbar_wdata),
        .burst(xbar_burst),
        .len(xbar_len),
        .wstrobe(xbar_wstrobe),
        .rdata(xbar_rdata),
        .ready(xbar_ready),
        .last(xbar_last),
        .ram_valid(ram_valid),
        .ram_addr(ram_addr),
        .ram_wdata(ram_wdata),
        .ram_burst(ram_burst),
        .ram_len(ram_len),
        .ram_wstrobe(ram_wstrobe),
        .ram_rdata(ram_rdata),
        .ram_ready(ram_ready),
        .ram_last(ram_last),
        .device_valid(device_valid),
        .device_addr(device_addr),
        .device_wdata(device_wdata),
        .device_wvalid(device_wvalid),
        .device_wstrobe(device_wstrobe),
        .device_rdata(device_rdata),
        .device_ready(device_ready),
        .device_last(device_last)
    );

    // ================================================================
    // Behavioral BRAM (replaces FPGA bram_wrapper)
    // 2-cycle read latency, 64-bit data width
    // ================================================================
    BehavioralBRAM #(
        .ADDR_WIDTH(18),
        .DATA_WIDTH(64),
        .READ_LATENCY(2)
    ) u_bram(
        .clk(clock),
        .reset(reset),
        .valid(ram_valid),
        .addr(ram_addr),
        .wdata(ram_wdata),
        .wstrobe(ram_wstrobe),
        .rdata(ram_rdata),
        .ready(ram_ready),
        .last(ram_last)
    );

    // ================================================================
    // Device (FPGA device.sv with SIMULATION=1)
    // ================================================================
    logic dbg_cpu_tx_write, dbg_any_device_write;
    logic dbg_ever_uart_write, dbg_ever_device_read;
    logic dbg_lsr_read;
    logic [63:0] dbg_lsr_rdata;

    device #(.SIMULATION(1'b1)) u_device(
        .clk(clock),
        .reset(reset),
        .cpu_clk(clock),
        .led(),
        .sw(4'd0),
        .tx(),
        .rx(1'b1),
        .spi_cs_n(),
        .spi_sck(),
        .spi_mosi(),
        .spi_miso(1'b1),
        .valid(device_valid),
        .addr(device_addr),
        .wvalid(device_wvalid),
        .wstrobe(device_wstrobe),
        .size(8'd0),
        .wdata(device_wdata),
        .rdata(device_rdata),
        .ready(device_ready),
        .last(device_last),
        .dbg_cpu_tx_write(dbg_cpu_tx_write),
        .dbg_any_device_write(dbg_any_device_write),
        .dbg_ever_uart_write(dbg_ever_uart_write),
        .dbg_ever_device_read(dbg_ever_device_read),
        .dbg_lsr_read(dbg_lsr_read),
        .dbg_lsr_rdata(dbg_lsr_rdata)
    );

    // UART output for difftest infrastructure (unused)
    assign {io_uart_out_valid, io_uart_out_ch, io_uart_in_valid} = '0;

    // ================================================================
    // Debug: monitor device bus activity
    // ================================================================
    `ifdef FPGA_SIM
    integer dbg_cycle_count;
    integer dbg_device_access_count;
    integer dbg_ram_access_count;
    integer dbg_stall_count;
    integer dbg_post_commit_count;

    always_ff @(posedge clock) begin
        if (reset) begin
            dbg_cycle_count <= 0;
            dbg_device_access_count <= 0;
            dbg_ram_access_count <= 0;
            dbg_stall_count <= 0;
            dbg_post_commit_count <= 0;
        end else begin
            dbg_cycle_count <= dbg_cycle_count + 1;

            // Track RAM accesses (count only, no print)
            if (ram_valid && ram_ready) begin
                dbg_ram_access_count <= dbg_ram_access_count + 1;
            end

            // Track device accesses
            if (device_valid && device_ready) begin
                dbg_device_access_count <= dbg_device_access_count + 1;

                // Print ALL device accesses (up to 500)
                if (dbg_device_access_count <= 500) begin
                    if (device_wvalid) begin
                        $display("[DEV_W] cyc=%0d #%0d addr=0x%0h wdata=0x%0h wstrobe=0x%02h",
                                 dbg_cycle_count, dbg_device_access_count, device_addr, device_wdata, device_wstrobe);
                    end else begin
                        $display("[DEV_R] cyc=%0d #%0d addr=0x%0h rdata=0x%0h",
                                 dbg_cycle_count, dbg_device_access_count, device_addr, device_rdata);
                    end
                end
            end

            // Debug: trace disk access pattern
            // Print first 20 accesses to disk address range
            if (device_valid && device_ready && device_addr >= 64'h10001000 && device_addr <= 64'h10001500) begin
                if (dbg_device_access_count <= 510) begin
                    if (device_wvalid) begin
                        $display("[DISK_W] cyc=%0d #%0d addr=0x%0h wdata=0x%0h",
                                 dbg_cycle_count, dbg_device_access_count, device_addr, device_wdata);
                    end else begin
                        $display("[DISK_R] cyc=%0d #%0d addr=0x%0h rdata=0x%0h",
                                 dbg_cycle_count, dbg_device_access_count, device_addr, device_rdata);
                    end
                end
            end

            // Debug: trace oresp around disk access time
            // Print when oresp changes state near disk access
            if (dbg_cycle_count > 11342000 && dbg_cycle_count < 11343000) begin
                if (oreq.valid) begin
                    $display("[OREQ] cyc=%0d valid=%0b addr=0x%0h is_write=%0b strobe=0x%02h ready=%0b last=%0b",
                             dbg_cycle_count, oreq.valid, oreq.addr, oreq.is_write, oreq.strobe,
                             oresp.ready, oresp.last);
                end
            end

            // Periodic status
            if (dbg_cycle_count > 0 && dbg_cycle_count % 1000000 == 0) begin
                $display("[STATUS] cyc=%0d ram=%0d dev=%0d uart_w=%0b dev_r=%0b",
                         dbg_cycle_count, dbg_ram_access_count, dbg_device_access_count,
                         dbg_ever_uart_write, dbg_ever_device_read);
            end
        end
    end
    `endif

endmodule
