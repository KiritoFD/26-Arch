// Behavioral BRAM model for simulation
// Matches the real bram_wrapper's transaction-based behavior:
// - Latches one request at a time
// - After BRAM_DELAY cycles, asserts ready/last for exactly one cycle
// - Then waits for the next request
// This prevents stale pipeline data from being returned for new requests.

module BehavioralBRAM #(
    parameter ADDR_WIDTH = 18,   // 2^18 = 262144 entries
    parameter DATA_WIDTH = 64,   // 64-bit data width
    parameter READ_LATENCY = 2   // cycles of read latency (matches BRAM_DELAY)
)(
    input  logic             clk,
    input  logic             reset,
    input  logic             valid,
    input  logic [63:0]      addr,
    input  logic [DATA_WIDTH-1:0] wdata,
    input  logic [7:0]       wstrobe,
    output logic [DATA_WIDTH-1:0] rdata,
    output logic             ready,
    output logic             last
);

    // Memory array
    logic [DATA_WIDTH-1:0] mem [0:(1<<ADDR_WIDTH)-1];

    // Initialize from hex file
    initial begin
        $readmemh("kernel_hex.txt", mem);
    end

    // Transaction state machine (matches bram_wrapper)
    localparam BRAM_DELAY = READ_LATENCY;
    logic [15:0] counter;
    logic        txn_active;
    logic [63:0] latched_addr;
    logic [DATA_WIDTH-1:0] latched_wdata;
    logic [7:0]  latched_wstrobe;
    logic        is_write;

    logic real_valid;

    always_ff @(posedge clk) begin
        if (reset) begin
            counter     <= '0;
            txn_active  <= 1'b0;
            latched_addr  <= '0;
            latched_wdata <= '0;
            latched_wstrobe <= '0;
            is_write    <= 1'b0;
        end else begin
            if (!txn_active) begin
                counter <= '0;
                if (valid) begin
                    txn_active     <= 1'b1;
                    latched_addr   <= addr;
                    latched_wdata  <= wdata;
                    latched_wstrobe <= wstrobe;
                    is_write       <= (|wstrobe);
                end
            end else if (last) begin
                counter    <= '0;
                txn_active <= 1'b0;
            end else if (counter != BRAM_DELAY) begin
                counter <= counter + 1;
            end
        end
    end

    // real_valid: asserted for exactly one cycle when counter reaches BRAM_DELAY
    // The `|| real_valid` term ensures it's a single-cycle pulse.
    // Without it, real_valid stays high for 2 cycles on reads because
    // last_read (used in state machine) is delayed by 1 cycle from real_valid,
    // so the state machine doesn't clear txn_active until the cycle after
    // real_valid first fires. This 2-cycle pulse confuses CBusArbiter.
    always_ff @(posedge clk) begin
        if (reset || !txn_active || counter != BRAM_DELAY || last || real_valid)
            real_valid <= 1'b0;
        else
            real_valid <= 1'b1;
    end

    // Write logic
    always_ff @(posedge clk) begin
        if (real_valid && is_write) begin
            automatic logic [ADDR_WIDTH-1:0] waddr = latched_addr[ADDR_WIDTH+2:3];
            automatic logic [DATA_WIDTH-1:0] wmask = '0;
            for (int i = 0; i < 8; i++) begin
                if (latched_wstrobe[i]) begin
                    wmask[i*8 +: 8] = 8'hFF;
                end
            end
            mem[waddr] <= (latched_wdata & wmask) | (mem[waddr] & ~wmask);
        end
    end

    // Read logic: use BRAM IP behavior - data appears when real_valid is asserted
    // The Xilinx BRAM IP outputs data on the cycle when ena=1, with 1-cycle pipeline
    // For simplicity, we read directly from the memory array when real_valid is high
    logic [DATA_WIDTH-1:0] bram_rdata;
    always_ff @(posedge clk) begin
        if (real_valid && !is_write) begin
            bram_rdata <= mem[latched_addr[ADDR_WIDTH+2:3]];
        end
    end

    // Output mux: ready_write for writes, ready_read (1 cycle delayed) for reads
    logic ready_write, last_write;
    logic ready_read, last_read;

    assign ready_write = real_valid;
    assign last_write  = real_valid;  // single-beat transaction

    always_ff @(posedge clk) begin
        ready_read <= ready_write;
        last_read  <= last_write;
    end

    assign ready = is_write ? ready_write : ready_read;
    assign last  = is_write ? last_write : last_read;
    assign rdata = bram_rdata;

    // Debug: count BRAM reads (no print to reduce output)
    `ifdef FPGA_SIM
    integer dbg_bram_read_count;
    always_ff @(posedge clk) begin
        if (reset) begin
            dbg_bram_read_count <= 0;
        end else if (real_valid && !is_write) begin
            dbg_bram_read_count <= dbg_bram_read_count + 1;
        end
    end
    `endif

endmodule
