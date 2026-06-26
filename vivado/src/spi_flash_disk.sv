// ================================================================
// SPI Flash Disk Controller for Basys3 (N25Q032)
// Reads 1024-byte blocks from SPI Flash at a configurable offset.
// Uses standard SPI Read (0x03) command.
// disk_buf uses single-port Block RAM with word-level writes.
// ================================================================

module spi_flash_disk #(
	parameter FLASH_DISK_OFFSET = 32'h0040_0000  // 4MB offset in flash
)(
	input logic        clk,
	input logic        reset,
	input logic        req_valid,       // pulse: start reading a sector
	input logic [31:0] req_blockno,     // block number to read
	output logic       data_ready,      // pulse: block data is ready

	// CPU read interface (registered, 1-cycle latency)
	input  logic [7:0]  cpu_raddr,      // CPU read word address (addr[9:2] - 64)
	output logic [31:0] cpu_rdata,      // CPU read data (1 cycle after raddr)

	// CPU write interface (for kernel disk write path)
	input logic        cpu_we,          // CPU write enable
	input logic [7:0]  cpu_waddr,       // CPU write word address (addr[9:2] - 64)
	input logic [31:0] cpu_wdata,       // CPU write data
	input logic [3:0]  cpu_wstrobe,     // CPU write byte strobe (4 bits for 32-bit data)

	// SPI Flash pins
	output logic spi_cs_n,
	output logic spi_clk,
	output logic spi_mosi,
	input  logic spi_miso
);

	// ================================================================
	// Single-Port Block RAM for disk buffer (256 x 32-bit = 1KB)
	// Writes are full 32-bit words (read-modify-write for byte enables)
	// ================================================================
	(* ram_style = "block" *)
	logic [31:0] disk_buf [0:255];

	// DIAG TEST: Initialize ALL BRAM words to 0x12345678 at FPGA power-up.
	// This bypasses SPI FSM entirely — we only want to verify the CPU read
	// path (device.sv disk_rdata_shifted / ready handshake) returns the
	// value stored in BRAM. If CPU reads 0x12345678, the read path is OK
	// and the bug is in SPI write. If CPU reads a transformed value, the
	// read path is broken.
	initial begin
		for (int i = 0; i < 256; i++) begin
			disk_buf[i] = 32'h12345678;
		end
	end

	logic [7:0]  ram_addr;
	logic        ram_we;
	logic [31:0] ram_wdata;
	logic [31:0] ram_rdata;

	// Single-port BRAM: one always block for both read and write
	always_ff @(posedge clk) begin
		if (ram_we) begin
			disk_buf[ram_addr] <= ram_wdata;
		end
		ram_rdata <= disk_buf[ram_addr];
	end

	assign cpu_rdata = ram_rdata;

	// ================================================================
	// RAM access arbitration
	// Priority: SPI write > CPU write > CPU read
	// SPI and CPU never access simultaneously in practice
	// (xv6 disk driver is synchronous: write blockno, wait, read data)
	// ================================================================

	// SPI state machine signals
	logic        spi_ram_we;
	logic [7:0]  spi_ram_addr;
	logic [31:0] spi_ram_wdata;

	// CPU write with byte strobes → read-modify-write
	logic        cpu_rmw_we;
	logic [7:0]  cpu_rmw_addr;
	logic [31:0] cpu_rmw_wdata;

	// For read-modify-write, we need the current value.
	// Since BRAM read has 1-cycle latency, we pipeline the RMW:
	// Cycle 0: cpu_we asserted, read current word
	// Cycle 1: modify bytes, write back
	logic        cpu_rmw_pending;
	logic [7:0]  cpu_rmw_pending_addr;
	logic [31:0] cpu_rmw_pending_wdata;
	logic [3:0]  cpu_rmw_pending_strobe;

	always_ff @(posedge clk) begin
		if (reset) begin
			cpu_rmw_pending <= 1'b0;
		end else begin
			if (cpu_rmw_pending) begin
				// Cycle 1: write back modified word
				cpu_rmw_pending <= 1'b0;
			end else if (cpu_we) begin
				// Cycle 0: latch CPU write request, read current word
				cpu_rmw_pending <= 1'b1;
				cpu_rmw_pending_addr <= cpu_waddr;
				cpu_rmw_pending_wdata <= cpu_wdata;
				cpu_rmw_pending_strobe <= cpu_wstrobe;
			end
		end
	end

	// Compute modified word (combinational)
	always_comb begin
		cpu_rmw_wdata = ram_rdata;  // current value from BRAM
		if (cpu_rmw_pending_strobe[0]) cpu_rmw_wdata[7:0]   = cpu_rmw_pending_wdata[7:0];
		if (cpu_rmw_pending_strobe[1]) cpu_rmw_wdata[15:8]  = cpu_rmw_pending_wdata[15:8];
		if (cpu_rmw_pending_strobe[2]) cpu_rmw_wdata[23:16] = cpu_rmw_pending_wdata[23:16];
		if (cpu_rmw_pending_strobe[3]) cpu_rmw_wdata[31:24] = cpu_rmw_pending_wdata[31:24];
	end

	assign cpu_rmw_we = cpu_rmw_pending;
	assign cpu_rmw_addr = cpu_rmw_pending_addr;

	// Mux: SPI write has priority over CPU RMW write
	// When neither writes, address comes from CPU read
	always_comb begin
		ram_we = 1'b0;
		ram_addr = cpu_raddr;  // default: CPU read
		ram_wdata = 32'd0;

		if (spi_ram_we) begin
			ram_we = 1'b1;
			ram_addr = spi_ram_addr;
			ram_wdata = spi_ram_wdata;
		end else if (cpu_rmw_we) begin
			ram_we = 1'b1;
			ram_addr = cpu_rmw_addr;
			ram_wdata = cpu_rmw_wdata;
		end
	end

	// ================================================================
	// SPI clock divider: cpu_clk=25MHz, SPI clk target ~12.5MHz (div by 2)
	// ================================================================
	localparam SPI_CLK_DIV = 2;
	logic [1:0] spi_clk_cnt;
	logic       spi_clk_reg;
	logic       spi_clk_edge;

	// Gate spi_clk_reg by `active`: when inactive, hold SCK low so the
	// CS falling edge does not see a spurious rising edge (which would
	// cause the Flash to sample the MOSI bit one cycle early and shift
	// the command/address bits, returning wrong data).
	always_ff @(posedge clk) begin
		if (reset) begin
			spi_clk_cnt <= 2'd0;
			spi_clk_reg <= 1'b0;
		end else if (active) begin
			if (spi_clk_cnt == SPI_CLK_DIV - 1) begin
				spi_clk_cnt <= 2'd0;
				spi_clk_reg <= ~spi_clk_reg;
			end else begin
				spi_clk_cnt <= spi_clk_cnt + 2'd1;
			end
		end else begin
			spi_clk_cnt <= 2'd0;
			spi_clk_reg <= 1'b0;  // hold SCK low while inactive
		end
	end

	logic spi_clk_reg_d;
	always_ff @(posedge clk) begin
		spi_clk_reg_d <= spi_clk_reg;
	end
	assign spi_clk_edge = spi_clk_reg & ~spi_clk_reg_d;

	// ================================================================
	// SPI state machine
	// Accumulates 4 bytes into a 32-bit word, then writes full word to BRAM
	// ================================================================
	localparam S_IDLE       = 4'd0;
	localparam S_CMD        = 4'd1;
	localparam S_ADDR       = 4'd2;
	localparam S_READ       = 4'd4;
	localparam S_DONE       = 4'd5;

	logic [3:0]  state;
	logic [3:0]  bit_cnt;
	logic [7:0]  shift_reg;
	logic [7:0]  miso_shift;
	logic [9:0]  byte_cnt;
	logic [22:0] flash_addr;
	logic [7:0]  word_idx;
	logic [1:0]  byte_idx;
	logic        active;
	logic [31:0] spi_word_acc;  // 4-byte accumulator

	assign spi_cs_n = ~active;
	assign spi_clk  = active ? spi_clk_reg : 1'b0;
	assign spi_mosi = active ? shift_reg[7] : 1'b1;

	always_ff @(posedge clk) begin
		if (reset) begin
			state <= S_IDLE;
			bit_cnt <= 4'd0;
			shift_reg <= 8'd0;
			miso_shift <= 8'd0;
			byte_cnt <= 10'd0;
			flash_addr <= 23'd0;
			word_idx <= 8'd0;
			byte_idx <= 2'd0;
			active <= 1'b0;
			data_ready <= 1'b0;
			spi_word_acc <= 32'd0;
			spi_ram_we <= 1'b0;
			spi_ram_addr <= 8'd0;
			spi_ram_wdata <= 32'd0;
		end else begin
			data_ready <= 1'b0;
			spi_ram_we <= 1'b0;  // default: no write

			case (state)
				S_IDLE: begin
				if (req_valid) begin
					// DIAG TEST: Skip SPI read entirely. BRAM was initialized
					// to 0x12345678 by initial block. Go straight to DONE so
					// data_ready pulses and CPU reads the initial pattern.
					active <= 1'b0;
					state <= S_DONE;
				end
			end

				S_CMD: begin
					if (spi_clk_edge) begin
						shift_reg <= {shift_reg[6:0], 1'b0};
						if (bit_cnt == 4'd7) begin
							bit_cnt <= 4'd0;
							shift_reg <= flash_addr[22:16];
							state <= S_ADDR;
						end else begin
							bit_cnt <= bit_cnt + 4'd1;
						end
					end
				end

				S_ADDR: begin
					if (spi_clk_edge) begin
						shift_reg <= {shift_reg[6:0], 1'b0};
						if (bit_cnt == 4'd7) begin
							bit_cnt <= 4'd0;
							if (byte_cnt == 9'd0) begin
								shift_reg <= flash_addr[15:8];
								byte_cnt <= byte_cnt + 10'd1;
							end else if (byte_cnt == 9'd1) begin
								shift_reg <= flash_addr[7:0];
								byte_cnt <= byte_cnt + 10'd1;
							end else begin
								byte_cnt <= 9'd0;
								bit_cnt <= 4'd0;
								state <= S_READ;
							end
						end else begin
							bit_cnt <= bit_cnt + 4'd1;
						end
					end
				end

				S_READ: begin
				if (spi_clk_edge) begin
					miso_shift <= {miso_shift[6:0], spi_miso};
					if (bit_cnt == 4'd7) begin
						bit_cnt <= 4'd0;
						// TEST MODE: fill BRAM with known pattern 0xAAAAAAAA
						// to verify BRAM read path. If CPU reads 0xAAAAAAAA,
						// BRAM path is OK and problem is in SPI communication.
						case (byte_idx)
							2'd0: spi_word_acc[7:0]   <= 8'hAA;
							2'd1: spi_word_acc[15:8]  <= 8'hAA;
							2'd2: spi_word_acc[23:16] <= 8'hAA;
							2'd3: begin
								spi_ram_we <= 1'b1;
								spi_ram_addr <= word_idx;
								spi_ram_wdata <= 32'hAAAAAAAA;
								word_idx <= word_idx + 7'd1;
							end
						endcase
							byte_idx <= byte_idx + 2'd1;
							if (byte_cnt == 10'd1023) begin
								state <= S_DONE;
							end else begin
								byte_cnt <= byte_cnt + 10'd1;
							end
						end else begin
							bit_cnt <= bit_cnt + 4'd1;
						end
					end
				end

				S_DONE: begin
					active <= 1'b0;
					data_ready <= 1'b1;
					state <= S_IDLE;
				end

				default: state <= S_IDLE;
			endcase
		end
	end

endmodule
