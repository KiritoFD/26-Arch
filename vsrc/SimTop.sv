`ifdef VERILATOR
`include "include/common.sv"
`include "src/core.sv"
`include "util/IBusToCBus.sv"
`include "util/DBusToCBus.sv"
`include "util/CBusArbiter.sv"
`include "util/mmu.sv"

module SimTop import common::*;(
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

    // Core <-> MMU
    ibus_req_t  ireq_core;
    ibus_resp_t iresp_core;
    dbus_req_t  dreq_core;
    dbus_resp_t dresp_core;

    // MMU <-> Bus converters
    ibus_req_t  ireq_bus;
    ibus_resp_t iresp_bus;
    dbus_req_t  dreq_bus;
    dbus_resp_t dresp_bus;

    cbus_req_t  icreq,  dcreq;
    cbus_resp_t icresp, dcresp;

    logic [63:0] satp;
    logic [63:0] pmpcfg0;
    logic [63:0] pmpaddr0;
    logic [1:0]  priv_mode;
    logic        flush_mmu;
    logic        walk_fault;
    logic [63:0] fault_vaddr;
    logic        fault_is_insn;
    logic [63:0] fault_cause;

    core core(
      .clk(clock), .reset,
      .ireq(ireq_core), .iresp(iresp_core),
      .dreq(dreq_core), .dresp(dresp_core),
      .trint, .swint, .exint,
      .csr_satp_o(satp),
      .csr_pmpcfg0_o(pmpcfg0),
      .csr_pmpaddr0_o(pmpaddr0),
      .privilege_mode_o(priv_mode),
      .flush_mmu_o(flush_mmu),
      .walk_fault(walk_fault),
      .fault_vaddr(fault_vaddr),
      .fault_is_insn(fault_is_insn),
      .fault_cause(fault_cause)
    );

    mmu u_mmu(
      .clk(clock), .reset,
      .satp(satp),
      .pmpcfg0(pmpcfg0),
      .pmpaddr0(pmpaddr0),
      .privilege_mode(priv_mode),
      .flush(flush_mmu),
      .ireq_in(ireq_core),  .iresp_in(iresp_core),
      .dreq_in(dreq_core),  .dresp_in(dresp_core),
      .ireq_out(ireq_bus),  .iresp_out(iresp_bus),
      .dreq_out(dreq_bus),  .dresp_out(dresp_bus),
      .walk_fault(walk_fault),
      .fault_vaddr(fault_vaddr),
      .fault_is_insn(fault_is_insn),
      .fault_cause(fault_cause)
    );

    IBusToCBus icvt(
      .clk(clock),
      .reset(reset),
      .flush(flush_mmu),
      .ireq(ireq_bus), .iresp(iresp_bus),
      .icreq(icreq), .icresp(icresp)
    );
    DBusToCBus dcvt(
      .clk(clock),
      .reset(reset || flush_mmu),
      .dreq(dreq_bus), .dresp(dresp_bus),
      .dcreq(dcreq), .dcresp(dcresp)
    );

    CBusArbiter mux(
        .clk(clock), .reset,
        .ireqs({icreq, dcreq}),
        .iresps({icresp, dcresp}),
        .oreq(oreq), .oresp(oresp)
    );

    RAMHelper2 ram(
        .clk(clock), .reset, .oreq, .oresp, .trint, .swint, .exint
    );

    assign {io_uart_out_valid, io_uart_out_ch, io_uart_in_valid} = '0;

endmodule
`endif
