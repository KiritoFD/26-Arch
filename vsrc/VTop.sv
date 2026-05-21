`ifndef __VTOP_SV
`define __VTOP_SV

`ifdef VERILATOR
`include "include/common.sv"
`include "src/core.sv"
`include "util/IBusToCBus.sv"
`include "util/DBusToCBus.sv"
`include "util/CBusArbiter.sv"
`include "util/mmu.sv"
`endif
module VTop 
	import common::*;(
	input logic clk, reset,

	output cbus_req_t  oreq,
	input  cbus_resp_t oresp,
	input logic trint, swint, exint
);

    // Core <-> MMU
    ibus_req_t  ireq_core;
    ibus_resp_t iresp_core;
    dbus_req_t  dreq_core;
    dbus_resp_t dresp_core;

    // MMU <-> bus converters
    ibus_req_t  ireq_bus;
    ibus_resp_t iresp_bus;
    dbus_req_t  dreq_bus;
    dbus_resp_t dresp_bus;

    cbus_req_t  icreq,  dcreq;
    cbus_resp_t icresp, dcresp;

	logic [63:0] satp;
	logic [1:0]  priv_mode;
	logic        flush_mmu;
	logic        walk_fault;
	logic [63:0] fault_vaddr;
	logic        fault_is_insn;
    core core(
        .clk(clk),
        .reset(reset),
        .ireq(ireq_core),
        .iresp(iresp_core),
        .dreq(dreq_core),
        .dresp(dresp_core),
        .trint(trint),
        .swint(swint),
        .exint(exint),
        .csr_satp_o(satp),
        .privilege_mode_o(priv_mode),
        .flush_mmu_o(flush_mmu),
        .walk_fault(walk_fault),
        .fault_vaddr(fault_vaddr),
        .fault_is_insn(fault_is_insn)
    );

    mmu u_mmu(
        .clk(clk),
        .reset(reset),
        .satp(satp),
        .privilege_mode(priv_mode),
        .flush(flush_mmu),
        .ireq_in(ireq_core),
        .iresp_in(iresp_core),
        .dreq_in(dreq_core),
        .dresp_in(dresp_core),
        .ireq_out(ireq_bus),
        .iresp_out(iresp_bus),
        .dreq_out(dreq_bus),
        .dresp_out(dresp_bus),
        .walk_fault(walk_fault),
        .fault_vaddr(fault_vaddr),
        .fault_is_insn(fault_is_insn)
    );

    IBusToCBus icvt(
        .clk(clk),
        .reset(reset),
        .flush(flush_mmu),
        .ireq(ireq_bus),
        .iresp(iresp_bus),
        .icreq(icreq),
        .icresp(icresp)
    );

    DBusToCBus dcvt(
        .clk(clk),
        .reset(reset || flush_mmu),
        .dreq(dreq_bus),
        .dresp(dresp_bus),
        .dcreq(dcreq),
        .dcresp(dcresp)
    );

    CBusArbiter mux(
        .clk(clk),
        .reset(reset),
        .ireqs({icreq, dcreq}),
        .iresps({icresp, dcresp}),
        .oreq(oreq),
        .oresp(oresp)
    );

endmodule



`endif
