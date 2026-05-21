module bram_wrapper #(
	parameter logic SIMULATION = 1'b0
)(
	input logic clk, reset,

	input logic valid,
	input logic [63:0] addr,
	input logic [63:0] wdata,
	output logic [63:0] rdata,
	input logic [7:0] wstrobe,
	input logic [1:0] burst,
	input logic [7:0] len,

	output logic ready,
	output logic last

);
	localparam BRAM_DELAY = 32;
	logic [15:0] counter;
	logic txn_active;
	logic [63:0] latched_addr;
	logic [63:0] latched_wdata;
	logic [7:0]  latched_wstrobe;
	logic [1:0]  latched_burst;
	logic [7:0]  latched_len;

	logic real_valid;
	always_ff @(posedge clk) begin
		if (reset) begin
			counter <= '0;
			txn_active <= 1'b0;
			latched_addr <= '0;
			latched_wdata <= '0;
			latched_wstrobe <= '0;
			latched_burst <= '0;
			latched_len <= '0;
		end else begin
			if (!txn_active) begin
				counter <= '0;
				if (valid) begin
					txn_active <= 1'b1;
					latched_addr <= addr;
					latched_wdata <= wdata;
					latched_wstrobe <= wstrobe;
					latched_burst <= burst;
					latched_len <= len;
				end
			end else if (last) begin
				counter <= '0;
				txn_active <= 1'b0;
			end else if (counter != BRAM_DELAY) begin
				counter <= counter + 1;
			end
		end
	end
	
	always_ff @(posedge clk) begin
		if (reset || !txn_active || counter != BRAM_DELAY || last) real_valid <= '0;
		else real_valid <= '1;
	end

	wire [17:0] base_addr = latched_addr[20:3];
	logic [17:0] burst_addr;

	wire is_incr = latched_burst == 2'b1;
	
	logic [17:0] burst_counter;
	always_ff @(posedge clk) begin
		if (real_valid && is_incr && ~reset) begin
			burst_counter <= burst_counter + 1;
		end else begin
			burst_counter <= '0;
		end
	end
	assign burst_addr = base_addr + burst_counter;

	bram_0 bram_0_inst (
		.clka(clk),
		.ena(real_valid),
		.wea(latched_wstrobe),
		.addra(is_incr ? burst_addr : base_addr),
		.dina(latched_wdata),
		.douta(rdata)
	);

	logic ready_read, ready_write;
	logic last_read, last_write;

	always_ff @(posedge clk) begin
		ready_read <= ready_write;
		last_read <= last_write;
	end

	assign ready_write = real_valid;
	assign last_write = ~is_incr ? real_valid : real_valid && burst_counter == latched_len;
	
	assign ready = |latched_wstrobe ? ready_write : ready_read;
	assign last = |latched_wstrobe ? last_write : last_read;
endmodule
