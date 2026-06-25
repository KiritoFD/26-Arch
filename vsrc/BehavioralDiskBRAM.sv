module BehavioralDiskBRAM #(
    parameter ADDR_WIDTH = 14,
    parameter DATA_WIDTH = 32
)(
    input  logic             clk,
    input  logic             reset,
    input  logic             en,
    input  logic [ADDR_WIDTH-1:0] addr,
    input  logic [DATA_WIDTH-1:0] wdata,
    input  logic [3:0]       we,
    output logic [DATA_WIDTH-1:0] rdata
);

    logic [DATA_WIDTH-1:0] mem [0:(1<<ADDR_WIDTH)-1];

    initial begin
        $readmemh("disk_hex.txt", mem);
    end

    // Combinational read (no registered output, matches BRAM with no output register)
    assign rdata = mem[addr];

    always_ff @(posedge clk) begin
        if (en) begin
            for (int i = 0; i < 4; i++) begin
                if (we[i]) begin
                    mem[addr][i*8 +: 8] <= wdata[i*8 +: 8];
                end
            end
        end
    end

endmodule
