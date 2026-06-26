module bram_wrapper #(
	parameter SIMULATION = 1'b0
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
	localparam BRAM_DELAY = 2;
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
		if (reset || !txn_active || counter != BRAM_DELAY || last || real_valid) real_valid <= '0;
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

	// ===== Read-Modify-Write for byte/sub-word stores =====
	// BRAM IP wea is only 1 bit (no byte write enable).
	// For partial writes (wstrobe != 0xFF), read old data first,
	// merge new bytes, then write full 64-bit word.
	wire is_write         = |latched_wstrobe;
	wire is_partial_write = is_write && (latched_wstrobe != 8'hFF);
	wire needs_rmw        = is_partial_write && !is_incr;

	logic rmw_phase;        // 0=read phase, 1=write phase
	logic [63:0] rmw_old_data;
	logic real_valid_d;     // real_valid delayed 1 cycle for latching BRAM read data
	logic rmw_write_done_q; // RMW write pulse completed

	always_ff @(posedge clk) begin
		if (reset) real_valid_d <= 1'b0;
		else real_valid_d <= real_valid;
	end

	always_ff @(posedge clk) begin
		if (reset || !txn_active) begin
			rmw_phase <= 1'b0;
			rmw_old_data <= '0;
		end else begin
			// On the cycle after real_valid (read phase), bram_douta holds old data
			if (real_valid_d && needs_rmw && !rmw_phase) begin
				rmw_old_data <= bram_douta_wire;
				rmw_phase <= 1'b1;
			end
		end
	end

	// RMW write pulse: single-cycle ena for the write phase
	// Fires when rmw_phase just set and write not yet done
	wire rmw_write_ena = needs_rmw && rmw_phase && !rmw_write_done_q;

	always_ff @(posedge clk) begin
		if (reset || !txn_active) rmw_write_done_q <= 1'b0;
		else if (rmw_write_ena) rmw_write_done_q <= 1'b1;
	end

	// Merge old data with new bytes (combinational)
	logic [63:0] merged_data;
	always_comb begin
		merged_data = rmw_old_data;
		if (latched_wstrobe[0]) merged_data[7:0]   = latched_wdata[7:0];
		if (latched_wstrobe[1]) merged_data[15:8]  = latched_wdata[15:8];
		if (latched_wstrobe[2]) merged_data[23:16] = latched_wdata[23:16];
		if (latched_wstrobe[3]) merged_data[31:24] = latched_wdata[31:24];
		if (latched_wstrobe[4]) merged_data[39:32] = latched_wdata[39:32];
		if (latched_wstrobe[5]) merged_data[47:40] = latched_wdata[47:40];
		if (latched_wstrobe[6]) merged_data[55:48] = latched_wdata[55:48];
		if (latched_wstrobe[7]) merged_data[63:56] = latched_wdata[63:56];
	end

	// BRAM port control
	wire bram_wea_wire = needs_rmw ? rmw_phase :    // RMW: read phase wea=0, write phase wea=1
	                     is_write  ? 1'b1 : 1'b0;   // normal: write wea=1, read wea=0
	wire [63:0] bram_dina_wire = (needs_rmw && rmw_phase) ? merged_data : latched_wdata;

	wire [63:0] bram_douta_wire;
	bram_0 bram_0_inst (
		.clka(clk),
		.ena(real_valid || rmw_write_ena),
		.wea(bram_wea_wire),
		.addra(is_incr ? burst_addr : base_addr),
		.dina(bram_dina_wire),
		.douta(bram_douta_wire)
	);

	assign rdata = bram_douta_wire;

	// ready/last: suppress during RMW read phase
	wire rmw_in_read_phase = needs_rmw && !rmw_phase;
	wire effective_valid   = real_valid && !rmw_in_read_phase;

	logic ready_read, ready_write;
	logic last_read, last_write;

	always_ff @(posedge clk) begin
		ready_read <= ready_write;
		last_read <= last_write;
	end

	// RMW write phase: ready/last pulse from rmw_write_ena
	assign ready_write = needs_rmw ? rmw_write_ena : effective_valid;
	assign last_write  = needs_rmw ? rmw_write_ena :
	                     ~is_incr ? effective_valid :
	                     (effective_valid && burst_counter == latched_len);

	assign ready = is_write ? ready_write : ready_read;
	assign last = is_write ? last_write : last_read;
endmodule
