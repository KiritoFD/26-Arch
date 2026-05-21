`ifndef __IBUSTOCBUS_SV
`define __IBUSTOCBUS_SV

`ifdef VERILATOR
`include "include/common.sv"
`else

`endif

module IBusToCBus 
    import common::*;(
    input  logic       clk,
    input  logic       reset,
    input  logic       flush,
    input  ibus_req_t  ireq,
    output ibus_resp_t iresp,
    output cbus_req_t  icreq,
    input  cbus_resp_t icresp
    );
    // since IBus is a subset of DBus, we can reuse DBusToCBus.
    dbus_resp_t dresp;
    DBusToCBus inst(
        .clk(clk),
        .reset(reset || flush),
        .dreq(`IREQ_TO_DREQ(ireq)),
        .dresp(dresp),
        .dcreq(icreq),
        .dcresp(icresp)
    );
    logic req_addr_bit2;
    logic req_inflight;
    logic issue_now;
    logic [63:0] req_addr_latched;
    logic active_addr_bit2;

    always_ff @(posedge clk) begin
        if (reset || flush) begin
            req_addr_bit2 <= 1'b0;
            req_inflight <= 1'b0;
            req_addr_latched <= 64'd0;
        end else begin
            if (issue_now) begin
                req_addr_bit2 <= ireq.addr[2];
                req_inflight <= 1'b1;
                req_addr_latched <= ireq.addr;
            end
            if (dresp.data_ok) begin
                req_inflight <= 1'b0;
            end
        end
    end

    assign issue_now = ireq.valid && !req_inflight;
    assign active_addr_bit2 =
        (req_inflight ? req_addr_bit2 : ireq.addr[2]);
    assign iresp = {dresp.addr_ok, dresp.data_ok, active_addr_bit2 ? dresp.data[63:32] : dresp.data[31:0]};

endmodule



`endif
