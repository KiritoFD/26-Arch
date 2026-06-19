`ifndef __DBUSTOCBUS_SV
`define __DBUSTOCBUS_SV

`ifdef VERILATOR
`include "include/common.sv"
`else

`endif
/**
 * NOTE: CBus does not support byte write enable mask (write_en).
 */

module DBusToCBus
    import common::*;(
    input  logic       clk,
    input  logic       reset,
    input  dbus_req_t  dreq,
    output dbus_resp_t dresp,
    output cbus_req_t  dcreq,
    input  cbus_resp_t dcresp
);
    assign dcreq.valid    =  dreq.valid;
    assign dcreq.is_write = |dreq.strobe;
    assign dcreq.size     =  dreq.size;
    assign dcreq.addr     =  dreq.addr;
    assign dcreq.strobe   =  dreq.strobe;
    assign dcreq.data     =  dreq.data;
    assign dcreq.len      =  MLEN1;
	assign dcreq.burst = AXI_BURST_INCR;

    logic okay;
    logic req_inflight;
    logic resp_seen;
    logic issue_now;
    logic resp_fire;

    assign okay = dcresp.ready && dcresp.last;
    assign issue_now = dreq.valid && !req_inflight && !resp_seen;
    assign resp_fire = okay && ((req_inflight && dreq.valid) || issue_now) && !resp_seen;

    always_ff @(posedge clk) begin
        if (reset) begin
            req_inflight <= 1'b0;
            resp_seen    <= 1'b0;
        end else begin
            if (!okay) begin
                resp_seen <= 1'b0;
            end

            if (resp_fire) begin
                req_inflight <= 1'b0;
                resp_seen    <= 1'b1;
            end else if (issue_now) begin
                req_inflight <= 1'b1;
            end else if (!dreq.valid) begin
                req_inflight <= 1'b0;
            end
        end
    end

    assign dresp.addr_ok = resp_fire;
    assign dresp.data_ok = resp_fire;
    assign dresp.data    = dcresp.data;
endmodule



`endif
