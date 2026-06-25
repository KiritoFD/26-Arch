`ifndef __DBUSTOCBUS_SV
`define __DBUSTOCBUS_SV

`ifdef VERILATOR
`include "include/common.sv"
`else

`endif

module DBusToCBus
    import common::*;(
    input  logic       clk,
    input  logic       reset,
    input  dbus_req_t  dreq,
    output dbus_resp_t dresp,
    output cbus_req_t  dcreq,
    input  cbus_resp_t dcresp
);
    assign dcreq.is_write = |dreq.strobe;
    assign dcreq.size     =  dreq.size;
    assign dcreq.addr     =  dreq.addr;
    assign dcreq.strobe   =  dreq.strobe;
    assign dcreq.data     =  dreq.data;
    assign dcreq.len      =  MLEN1;
    assign dcreq.burst    =  AXI_BURST_INCR;

    logic okay;
    logic req_inflight;
    logic resp_seen;
    logic issue_now;
    logic resp_fire;

    assign okay = dcresp.ready && dcresp.last;

    // Issue a new transaction when CPU has a valid request, no transaction
    // is already in flight, and we haven't already seen a response.
    assign issue_now = dreq.valid && !req_inflight && !resp_seen;

    // Response fires when the bus returns okay for an active or just-issued
    // request and we haven't already consumed this response.
    assign resp_fire = okay && ((req_inflight && dreq.valid) || issue_now) && !resp_seen;

    // CRITICAL: Gate dcreq.valid so it's only asserted when we actually want
    // to issue or have an in-flight transaction. This prevents:
    //   1. BRAM/device from latching spurious requests when the CPU keeps
    //      valid high after a completed transaction (root cause of duplicate
    //      UART chars and double DISK_BLOCKNO writes)
    //   2. CBusArbiter from granting to DBus when we're waiting for the CPU
    //      to change its request, which would block IBus fetches
    assign dcreq.valid = dreq.valid && (issue_now || req_inflight);

    always_ff @(posedge clk) begin
        if (reset) begin
            req_inflight    <= 1'b0;
            resp_seen       <= 1'b0;
        end else begin
            // Clear resp_seen when the response is gone from the bus.
            // - For BRAM: real_valid is a single-cycle pulse, so okay goes
            //   low on the next cycle naturally.
            // - For device: txn_done_pulse de-asserts ready for one cycle
            //   after txn_fire, so okay goes low for one cycle.
            // - Also clear if CPU drops the request entirely.
            if (!okay || !dreq.valid) begin
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
