`include "device.svh"

module device #(
	parameter logic SIMULATION = 1'b0
)(
	input logic clk, reset,
	input logic cpu_clk,

	/* From Board */
	output logic [3:0] led,
	input logic [3:0] sw,
	output logic tx,

	/* From CPU */
	input logic valid,
	input logic [63:0] addr,
	input logic wvalid,
	input logic [7:0] wstrobe,
	input logic [7:0] size,
	input logic [63:0] wdata,
	output logic [63:0] rdata,

	output logic ready,
	output logic last
);
	logic txn_fire;
	logic fifo_full, fifo_empty;

	/* Counter */
	logic [63:0] cnter, cnter1;

	always_ff @(posedge cpu_clk) begin
		if (reset) {cnter, cnter1} <= '0;
		else begin
			cnter1 <= cnter1 + 1;
			if (cnter1 == 100) begin
				cnter1 <= '0;
				cnter <= cnter + 1;
			end
		end
	end

	/* Switch */
	logic [3:0] switch;
	always_ff @(posedge cpu_clk) begin
		switch <= sw;
	end

	always_comb begin
		rdata = 'x;
		unique case(addr)
			SW_ADDR: begin
				unique case(switch)
					4'd0: begin
						rdata = 64'd31;
					end
					4'd1: begin
						rdata = 64'd1;
					end
					4'd2: begin
						rdata = 64'd2;
					end
					4'd3: begin
						rdata = 64'd4;
					end
					4'd4: begin
						rdata = 64'd8;
					end
					4'd5: begin
						rdata = 64'd16;
					end
					default: begin
						
					end
				endcase
			end
			COUNTER_1, COUNTER_2: begin
				rdata = cnter;
			end
			TX_READY: begin
				rdata = {60'b0, fifo_full, 3'b0};
			end
			default: begin
				
			end
		endcase
	end

	
	always_ff @(posedge cpu_clk) begin
		if (reset) led <= '0;
		else if (txn_fire && wvalid && (addr == FINISH_ADDR)) led <= '1;
	end
	
	// assign ready = '1;
	assign last = ready;

	/* UART */
	parameter logic [13:0] BIT_TMR_MAX = 14'd216;
    parameter BIT_INDEX_MAX = 10;
	localparam int TX_FIFO_DEPTH = 256;

	logic finish;
	always_ff @(posedge cpu_clk) begin
		if (reset) finish <= '0;
		else if (txn_fire && addr == FINISH_ADDR && wvalid) finish <= '1;
	end

    logic [13:0] bitTmr;

    localparam type state_t = enum logic [1:0] {
        RDY, LOAD_BIT, SEND_BIT
    };

    logic bitDone;
    int bitIndex;
    logic txBit;
    logic [9:0] txData;
    state_t txState;
    logic tx_data_access;
    logic [7:0] tx_write_byte;
    logic accepted_write;
    logic tx_start;
    logic [7:0] tx_fifo [0:TX_FIFO_DEPTH-1];
    logic [7:0] fifo_wptr, fifo_rptr;
    logic [8:0] fifo_count;

    always_comb begin
        tx_write_byte = wdata[7:0];
        unique casez (wstrobe)
            8'b???????1: tx_write_byte = wdata[7:0];
            8'b??????10: tx_write_byte = wdata[15:8];
            8'b?????100: tx_write_byte = wdata[23:16];
            8'b????1000: tx_write_byte = wdata[31:24];
            8'b???10000: tx_write_byte = wdata[39:32];
            8'b??100000: tx_write_byte = wdata[47:40];
            8'b?1000000: tx_write_byte = wdata[55:48];
            8'b10000000: tx_write_byte = wdata[63:56];
            default: begin end
        endcase
    end

    assign txn_fire = valid && ready && last;
    assign tx_data_access = (((addr & ~64'h7) == (TX_DATA & ~64'h7)) && valid && wvalid);
    assign fifo_full = (fifo_count == TX_FIFO_DEPTH);
    assign fifo_empty = (fifo_count == 0);
    assign accepted_write = txn_fire && tx_data_access && ~fifo_full;
    assign tx_start = (txState == RDY) && ~fifo_empty;

    always_ff @(posedge cpu_clk) begin
        if (reset) begin
            fifo_wptr <= '0;
            fifo_rptr <= '0;
            fifo_count <= '0;
        end else begin
            if (accepted_write) begin
                tx_fifo[fifo_wptr] <= tx_write_byte;
                fifo_wptr <= fifo_wptr + 1'b1;
            end
            if (tx_start) begin
                fifo_rptr <= fifo_rptr + 1'b1;
            end

            unique case ({accepted_write, tx_start})
                2'b10: fifo_count <= fifo_count + 1'b1;
                2'b01: fifo_count <= fifo_count - 1'b1;
                default: begin end
            endcase
        end
    end

    always_ff @(posedge cpu_clk) begin
        if (reset) begin
            txState <= RDY;
        end else begin
            unique case(txState)
                RDY: begin
                    if (tx_start) txState <= LOAD_BIT;
                end
                LOAD_BIT: begin
                    txState <= SEND_BIT;
                end
                SEND_BIT: begin
                    if (bitDone) begin
                        if (bitIndex == BIT_INDEX_MAX) txState <= RDY;
                        else txState <= LOAD_BIT;
                    end
                end
                default: begin
                    txState <= RDY;
                end
            endcase
        end
    end

    always_ff @(posedge cpu_clk) begin
        if (reset || txState == RDY || bitDone) bitTmr <= '0;
        else bitTmr <= bitTmr + 1;
    end

    assign bitDone = bitTmr == BIT_TMR_MAX;

    always_ff @(posedge cpu_clk) begin
        if (reset) bitIndex <= '0;
        else if (txState == RDY) bitIndex <= '0;
        else if (txState == LOAD_BIT) bitIndex <= bitIndex + 1;
    end

    always_ff @(posedge cpu_clk) begin
        if (reset) txData <= 10'h3ff;
        else if (tx_start) txData <= {1'b1, tx_fifo[fifo_rptr], 1'b0};
    end

    always_ff @(posedge cpu_clk) begin
        if (reset) begin
            txBit <= '1;
        end else if (txState == RDY) begin
            txBit <= '1;
        end else if (txState == LOAD_BIT) begin
            txBit <= txData[bitIndex];
        end
    end

    assign tx = txBit;
	assign ready = tx_data_access ? ~fifo_full : '1;
		
	always_ff @(posedge cpu_clk) begin
		if (~reset && txn_fire && wvalid) begin
			if ((addr & ~64'h7) == (TX_DATA & ~64'h7)) begin
				$write("%c", tx_write_byte);
			end else if (addr == FINISH_ADDR) begin
				$write("Hello World!\n");
			end
		end
	end

endmodule
