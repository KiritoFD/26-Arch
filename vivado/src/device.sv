`include "device.svh"

module device #(
	parameter SIMULATION = 1'b0
)(
	input logic clk, reset,
	input logic cpu_clk,

	/* From Board */
	output logic [3:0] led,
	input logic [3:0] sw,
	output logic tx,
	input logic rx,

	/* SPI Flash */
	output logic spi_cs_n,
	output logic spi_sck,
	output logic spi_mosi,
	input  logic spi_miso,

	/* From CPU */
	input logic valid,
	input logic [63:0] addr,
	input logic wvalid,
	input logic [7:0] wstrobe,
	input logic [7:0] size,
	input logic [63:0] wdata,
	output logic [63:0] rdata,

	output logic ready,
	output logic last,

	output logic dbg_cpu_tx_write,
	output logic dbg_any_device_write,
	output logic dbg_ever_uart_write,
	output logic dbg_ever_device_read,
	output logic dbg_lsr_read,
	output logic dbg_ever_thr_write,
	output logic dbg_tx_state_rdy,    // 1=UART TX state machine in RDY (idle)
	output logic dbg_tx_fifo_nonempty, // 1=TX FIFO has data
	output logic [63:0] dbg_lsr_rdata
);

	// ================================================================
	// Transaction handshake
	// ================================================================
	logic txn_fire;
	assign txn_fire = valid && ready;
	assign last = ready;

	// ================================================================
	// DEBUG: Verify device.sv is correctly compiled and signals are live
	// This is OUTSIDE any generate block to eliminate elaboration issues
	// ================================================================
	generate
		if (SIMULATION) begin : gen_dbg_live
			integer dbg_live_count;
			always_ff @(posedge cpu_clk) begin
				if (reset) begin
					dbg_live_count <= 0;
				end else if (valid && dbg_live_count < 5) begin
					$display("[DEV_LIVE] valid=%0b ready=%0b txn_fire=%0b wvalid=%0b addr=0x%0h wdata=0x%0h wstrobe=0x%02h",
					         valid, ready, txn_fire, wvalid, addr, wdata, wstrobe);
					dbg_live_count <= dbg_live_count + 1;
				end
			end
		end
	endgenerate

	// ================================================================
	// Byte extraction from wdata based on wstrobe
	// ================================================================
	logic [7:0] tx_write_byte;
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

	// ================================================================
	// UART 16550 Registers
	// ================================================================
	logic [7:0] uart_lcr;
	logic [7:0] uart_ier;

	always_ff @(posedge cpu_clk) begin
		if (reset) begin
			uart_lcr <= 8'h00;
			uart_ier <= 8'h00;
		end
	end

	// ================================================================
	// CLINT mtime
	// ================================================================
	logic [63:0] mtime;
	logic [15:0] mtime_div;

	always_ff @(posedge cpu_clk) begin
		if (reset) begin
			mtime <= 64'd0;
			mtime_div <= 16'd0;
		end else begin
			if (mtime_div == 16'd24) begin
				mtime_div <= 16'd0;
				mtime <= mtime + 64'd1;
			end else begin
				mtime_div <= mtime_div + 16'd1;
			end
		end
	end

	// ================================================================
	// Switch / LED / FINISH
	// ================================================================
	logic [3:0] switch;
	always_ff @(posedge cpu_clk) begin
		if (reset) switch <= 4'd0;
		else switch <= sw;
	end

	logic finish;
	always_ff @(posedge cpu_clk) begin
		if (reset) begin
			led <= 4'd0;
			finish <= 1'b0;
		end else if (txn_fire && wvalid && (addr == FINISH_ADDR)) begin
			led <= 4'hf;
			finish <= 1'b1;
		end
	end

	// ================================================================
	// Console RX FIFO (keyboard input from PC via UART)
	// ================================================================
	localparam RX_FIFO_DEPTH = 16;
	logic [7:0] console_rx_fifo [0:RX_FIFO_DEPTH-1];
	logic [4:0] console_rx_wptr, console_rx_rptr;
	logic [5:0] console_rx_count;
	logic console_rx_empty;

	assign console_rx_empty = (console_rx_count == 0);

	always_ff @(posedge cpu_clk) begin
		if (reset) begin
			console_rx_wptr <= 5'd0;
			console_rx_rptr <= 5'd0;
			console_rx_count <= 6'd0;
		end else begin
			// Push from UART RX
			if (rxByteReady && console_rx_count < RX_FIFO_DEPTH) begin
				console_rx_fifo[console_rx_wptr[3:0]] <= rxByte;
				console_rx_wptr <= console_rx_wptr + 1'b1;
				console_rx_count <= console_rx_count + 1'b1;
			end
			// Pop when CPU reads RHR
			if (txn_fire && !wvalid && addr == UART_RHR_THR && !uart_lcr[7] && !console_rx_empty) begin
				console_rx_rptr <= console_rx_rptr + 1'b1;
				console_rx_count <= console_rx_count - 1'b1;
			end
		end
	end

	// ================================================================
	// UART TX - simple FIFO-based transmitter (console only)
	// ================================================================
	parameter [13:0] BIT_TMR_MAX = 14'd216;
	parameter BIT_INDEX_MAX = 10;
	localparam TX_FIFO_DEPTH = 64;

	logic [13:0] bitTmr;
	localparam [1:0] RDY = 2'd0, LOAD_BIT = 2'd1, SEND_BIT = 2'd2;
	logic [1:0] txState;
	logic bitDone;
	integer bitIndex;
	logic txBit;
	logic [9:0] txData;
	logic tx_start;
	logic [7:0] tx_fifo [0:TX_FIFO_DEPTH-1];
	logic [6:0] fifo_wptr, fifo_rptr;
	logic [7:0] fifo_count;
	logic fifo_full, fifo_empty;

	assign fifo_full  = (fifo_count == TX_FIFO_DEPTH);
	assign fifo_empty = (fifo_count == 0);

	// CPU console write
	logic cpu_tx_write;
	assign cpu_tx_write = txn_fire && wvalid && (addr == UART_RHR_THR) && !uart_lcr[7];
	assign dbg_cpu_tx_write = cpu_tx_write;
	assign dbg_any_device_write = txn_fire && wvalid;

	// Debug latches
	logic dbg_ever_uart_write_reg;
	logic dbg_ever_device_read_reg;
	logic dbg_lsr_read_reg;
	logic dbg_ever_thr_write_reg;    // TRUE only when THR data byte written
	logic [63:0] dbg_lsr_rdata_reg;
	always_ff @(posedge cpu_clk) begin
		if (reset) begin
			dbg_ever_uart_write_reg <= 1'b0;
			dbg_ever_device_read_reg <= 1'b0;
			dbg_lsr_read_reg <= 1'b0;
			dbg_ever_thr_write_reg <= 1'b0;
			dbg_lsr_rdata_reg <= 64'd0;
		end else begin
			if (txn_fire && wvalid && addr >= UART_BASE && addr <= UART_LSR)
				dbg_ever_uart_write_reg <= 1'b1;
			if (cpu_tx_write)
				dbg_ever_thr_write_reg <= 1'b1;
			if (txn_fire && !wvalid) begin
				dbg_ever_device_read_reg <= 1'b1;
				if (addr == UART_LSR) begin
					dbg_lsr_read_reg <= 1'b1;
					dbg_lsr_rdata_reg <= rdata;
				end
			end
		end
	end
	assign dbg_ever_uart_write = dbg_ever_uart_write_reg;
	assign dbg_ever_device_read = dbg_ever_device_read_reg;
	assign dbg_lsr_read = dbg_lsr_read_reg;
	assign dbg_ever_thr_write = dbg_ever_thr_write_reg;
	assign dbg_tx_state_rdy = (txState == RDY);
	assign dbg_tx_fifo_nonempty = ~fifo_empty;
	assign dbg_lsr_rdata = dbg_lsr_rdata_reg;

	// Push byte into TX FIFO on console write
	always_ff @(posedge cpu_clk) begin
		if (reset) begin
			fifo_wptr <= 7'd0;
			fifo_rptr <= 7'd0;
			fifo_count <= 8'd0;
		end else begin
			if (cpu_tx_write && ~fifo_full) begin
				tx_fifo[fifo_wptr] <= tx_write_byte;
				fifo_wptr <= fifo_wptr + 1'b1;
			end
			if (tx_start) begin
				fifo_rptr <= fifo_rptr + 1'b1;
			end
			unique case ({cpu_tx_write && ~fifo_full, tx_start})
				2'b10: fifo_count <= fifo_count + 8'd1;
				2'b01: fifo_count <= fifo_count - 8'd1;
				default: begin end
			endcase
		end
	end

	assign tx_start = (txState == RDY) && ~fifo_empty;

	always_ff @(posedge cpu_clk) begin
		if (reset) txState <= RDY;
		else begin
			unique case(txState)
				RDY: if (tx_start) txState <= LOAD_BIT;
				LOAD_BIT: txState <= SEND_BIT;
				SEND_BIT: if (bitDone) begin
					if (bitIndex == BIT_INDEX_MAX) txState <= RDY;
					else txState <= LOAD_BIT;
				end
				default: txState <= RDY;
			endcase
		end
	end

	always_ff @(posedge cpu_clk) begin
		if (reset || txState == RDY || bitDone) bitTmr <= 14'd0;
		else bitTmr <= bitTmr + 14'd1;
	end
	assign bitDone = (bitTmr == BIT_TMR_MAX);

	always_ff @(posedge cpu_clk) begin
		if (reset) bitIndex <= 0;
		else if (txState == RDY) bitIndex <= 0;
		else if (txState == LOAD_BIT) bitIndex <= bitIndex + 1;
	end

	always_ff @(posedge cpu_clk) begin
		if (reset) txData <= 10'h3ff;
		else if (tx_start) txData <= {1'b1, tx_fifo[fifo_rptr], 1'b0};
	end

	always_ff @(posedge cpu_clk) begin
		if (reset) txBit <= 1'b1;
		else if (txState == RDY) txBit <= 1'b1;
		else if (txState == LOAD_BIT) txBit <= txData[bitIndex];
	end

	assign tx = txBit;

	// ================================================================
	// UART RX - physical serial port from PC (console only)
	// ================================================================
	logic [9:0]  rxShiftReg;
	logic [13:0] rxBitTmr;
	logic [3:0]  rxBitIndex;
	logic [1:0]  rxState;
	logic        rxBitSync;
	logic        rxBit;
	logic        rxByteReady;
	logic [7:0]  rxByte;

	always_ff @(posedge cpu_clk) begin
		if (reset) begin
			rxBitSync <= 1'b1;
			rxBit     <= 1'b1;
		end else begin
			rxBitSync <= rx;
			rxBit     <= rxBitSync;
		end
	end

	always_ff @(posedge cpu_clk) begin
		if (reset) begin
			rxState     <= 2'd0;
			rxBitIndex  <= 4'd0;
			rxBitTmr    <= 14'd0;
			rxByteReady <= 1'b0;
			rxShiftReg  <= 10'd0;
			rxByte      <= 8'd0;
		end else begin
			rxByteReady <= 1'b0;
			unique case (rxState)
				2'd0: begin
					if (rxBit == 1'b0) begin
						rxState  <= 2'd1;
						rxBitTmr <= 14'd0;
					end
				end
				2'd1: begin
					rxBitTmr <= rxBitTmr + 14'd1;
					if (rxBitTmr == (BIT_TMR_MAX >> 1)) begin
						if (rxBit == 1'b0) begin
							rxState     <= 2'd2;
							rxBitIndex  <= 4'd0;
							rxBitTmr   <= 14'd0;
						end else begin
							rxState <= 2'd0;
						end
					end
				end
				2'd2: begin
					rxBitTmr <= rxBitTmr + 14'd1;
					if (rxBitTmr == BIT_TMR_MAX) begin
						rxBitTmr <= 14'd0;
						rxShiftReg[rxBitIndex] <= rxBit;
						if (rxBitIndex == 4'd7) begin
							rxState <= 2'd3;
						end else begin
							rxBitIndex <= rxBitIndex + 4'd1;
						end
					end
				end
				2'd3: begin
					rxBitTmr <= rxBitTmr + 14'd1;
					if (rxBitTmr == BIT_TMR_MAX) begin
						rxByte      <= rxShiftReg[7:0];
						rxByteReady <= 1'b1;
						rxState     <= 2'd0;
					end
				end
				default: rxState <= 2'd0;
			endcase
		end
	end

	// ================================================================
	// MMIO Disk - SPI Flash (real) / Direct Memory (simulation)
	// ================================================================
	logic [31:0] disk_blockno;
	logic        disk_rdy;

	`ifdef VERILATOR
	logic [31:0] sim_disk_mem [0:255999];
	initial begin
		$readmemh("disk_hex.txt", sim_disk_mem);
	end
	`endif

	// Block RAM read data (1-cycle latency for real hardware)
	logic [31:0] disk_rdata_reg;
	logic        disk_rdata_valid;
	logic [63:0] disk_rdata_shifted;
	logic [2:0]  disk_raddr_offset;
	logic        disk_read_not_ready;  // set by gen_real_disk when BRAM read pending

	// ================================================================
	// Disk control logic
	// ================================================================
	generate
	if (!SIMULATION) begin : gen_real_disk
		// ============================================================
		// Real hardware: SPI Flash read with Block RAM buffer
		// ============================================================
		logic        spi_req_valid;
		logic [31:0] spi_req_blockno;
		logic        spi_data_ready;
		logic        disk_cpu_we;
		logic [7:0]  disk_cpu_waddr;
		logic [31:0] disk_cpu_wdata;
		logic [3:0]  disk_cpu_wstrobe;
		logic [7:0]  disk_cpu_raddr;

		assign disk_cpu_we = txn_fire && wvalid && addr >= DISK_DATA_BASE && addr < DISK_DATA_BASE + 1024 && |wstrobe;
		assign disk_cpu_waddr = addr[9:2] - 7'd64;
		assign disk_cpu_wdata = wdata[31:0];
		assign disk_cpu_wstrobe = wstrobe[3:0];
		assign disk_cpu_raddr = addr[9:2] - 7'd64;

		spi_flash_disk #(
			.FLASH_DISK_OFFSET(32'h0030_0000)  // 3MB offset (past ~2.1MB FPGA bitstream)
		) u_spi_flash (
			.clk(cpu_clk),
			.reset(reset),
			.req_valid(spi_req_valid),
			.req_blockno(spi_req_blockno),
			.data_ready(spi_data_ready),
			.cpu_raddr(disk_cpu_raddr),
			.cpu_rdata(disk_rdata_reg),
			.cpu_we(disk_cpu_we),
			.cpu_waddr(disk_cpu_waddr),
			.cpu_wdata(disk_cpu_wdata),
			.cpu_wstrobe(disk_cpu_wstrobe),
			.spi_cs_n(spi_cs_n),
			.spi_clk(spi_sck),
			.spi_mosi(spi_mosi),
			.spi_miso(spi_miso)
		);

		// Block RAM has 1-cycle read latency:
		// Cycle 0: CPU presents addr, device de-asserts ready
		// Cycle 1: BRAM data is available, device asserts ready with data
		logic disk_read_pending;
		always_ff @(posedge cpu_clk) begin
			if (reset) begin
				disk_read_pending <= 1'b0;
				disk_rdata_valid <= 1'b0;
				disk_raddr_offset <= 3'd0;
			end else begin
				disk_rdata_valid <= 1'b0;
				if (disk_read_pending) begin
					disk_read_pending <= 1'b0;
					disk_rdata_valid <= 1'b1;
					disk_rdata_shifted <= {32'd0, disk_rdata_reg} << (disk_raddr_offset * 8);
				end else if (valid && !wvalid && !txn_fire &&
			           addr >= DISK_DATA_BASE && addr < DISK_DATA_BASE + 1024) begin
				disk_read_pending <= 1'b1;
				disk_raddr_offset <= addr[2:0];
			end
			end
		end
		assign disk_read_not_ready = disk_read_pending;

		// Disk control: trigger SPI Flash read on blockno write,
		// poll data_ready to set disk_rdy for xv6 driver.
		always_ff @(posedge cpu_clk) begin
			if (reset) begin
				disk_blockno <= 32'd0;
				disk_rdy <= 1'b1;
				spi_req_valid <= 1'b0;
				spi_req_blockno <= 32'd0;
			end else begin
				spi_req_valid <= 1'b0;  // default: pulse

				if (txn_fire && wvalid && addr == DISK_BLOCKNO && disk_rdy) begin
					disk_blockno <= wdata[31:0];
					disk_rdy <= 1'b0;
					spi_req_valid <= 1'b1;
					spi_req_blockno <= wdata[31:0];
				end

				if (spi_data_ready) begin
					disk_rdy <= 1'b1;
				end
			end
		end
	end else begin : gen_sim_disk
		// ============================================================
		// Simulation: disk_blockno tracking + debug
		// ============================================================
		always_ff @(posedge cpu_clk) begin
			if (reset) begin
				disk_blockno <= 32'd0;
				disk_rdy <= 1'b1;
			end else begin
				if (txn_fire && wvalid && addr == DISK_BLOCKNO) begin
					disk_blockno <= wdata[31:0];
					disk_rdy <= 1'b1;
				end
			end
		end

		assign spi_cs_n = 1'b1;
	assign spi_sck  = 1'b0;
	assign spi_mosi = 1'b0;
	assign disk_read_not_ready = 1'b0;
	assign disk_rdata_reg = 32'd0;
	assign disk_rdata_valid = 1'b1;  // sim: data always ready (combinational)
	assign disk_rdata_shifted = 64'd0;
	end
	endgenerate

	// CPU write to disk_buf is handled inside spi_flash_disk (real hw)
	// or sim_disk_mem (simulation) via cpu_we port

	`ifdef VERILATOR
	always_ff @(posedge cpu_clk) begin
		if (txn_fire && wvalid && addr >= DISK_DATA_BASE && addr < DISK_DATA_BASE + 1024 && |wstrobe) begin
			for (int i = 0; i < 8; i++) begin
				if (wstrobe[i]) begin
					sim_disk_mem[disk_blockno * 256 + addr[9:2] - 7'd64][(i%4)*8 +: 8] <= wdata[i*8 +: 8];
				end
			end
		end
	end
	`endif

	// ================================================================
	// Read data mux
	// ================================================================
	logic disk_data_read;
	assign disk_data_read = (addr >= DISK_DATA_BASE && addr < DISK_DATA_BASE + 1024);

	always_comb begin
		rdata = 64'd0;
		unique case (addr)
			UART_RHR_THR: rdata = {56'b0, (console_rx_empty ? 8'h00 : console_rx_fifo[console_rx_rptr[3:0]])};
			UART_IER:     rdata = {48'b0, uart_ier, 8'b0};
			UART_FCR_ISR: rdata = {40'b0, 8'h01, 16'b0}; // ISR=1 (no pending interrupt)
			UART_LCR:     rdata = {32'b0, uart_lcr, 24'b0};
			UART_LSR:     rdata = {16'b0, 8'h60, 40'b0}; // THRE+TEMT

			DISK_BLOCKNO: rdata = {32'd0, disk_blockno};
			DISK_STATUS:  rdata = {63'd0, disk_rdy};

			CLINT_MTIME: rdata = mtime;

			SW_ADDR: begin
				unique case (switch)
					4'd0: rdata = 64'd31;
					4'd1: rdata = 64'd1;
					4'd2: rdata = 64'd2;
					4'd3: rdata = 64'd4;
					4'd4: rdata = 64'd8;
					4'd5: rdata = 64'd16;
					default: rdata = 64'd0;
				endcase
			end
			COUNTER_2: rdata = mtime;

			default: begin
				if (disk_data_read) begin
					`ifdef VERILATOR
					rdata = {32'd0, sim_disk_mem[disk_blockno * 256 + addr[9:2] - 7'd64]} << (addr[2:0] * 8);
					`else
					rdata = disk_rdata_valid ? disk_rdata_shifted : 64'd0;
					`endif
				end
			end
		endcase
	end

	// ================================================================
	// Write handling
	// ================================================================
	always_ff @(posedge cpu_clk) begin
		if (reset) begin
			uart_lcr <= 8'h00;
			uart_ier <= 8'h00;
		end else if (txn_fire && wvalid) begin
			unique case (addr)
				UART_RHR_THR: begin
					// THR write handled by TX FIFO via cpu_tx_write
				end
				UART_IER: begin
					if (!uart_lcr[7])
						uart_ier <= tx_write_byte;
				end
				UART_FCR_ISR: begin
					// FCR write - ignore
				end
				UART_LCR: begin
					uart_lcr <= tx_write_byte;
				end
				DISK_BLOCKNO: begin
					// Handled in disk control logic
				end
				default: begin
					// Disk data writes handled above
				end
			endcase
		end
	end

	// ================================================================
	// Ready signal
	// ================================================================
	// After a transaction fires (txn_fire), de-assert ready for one cycle
	// to prevent the same request from being processed multiple times.
	// This is critical because the bus arbiter may keep valid high across
	// cycles, and with always-ready devices, txn_fire would stay high.
	logic uart_thr_write_req;
	logic txn_done_pulse;
	assign uart_thr_write_req = valid && wvalid && (addr == UART_RHR_THR) && !uart_lcr[7];
	always_ff @(posedge cpu_clk) begin
		if (reset || !valid)
			txn_done_pulse <= 1'b0;
		else if (txn_fire)
			txn_done_pulse <= 1'b1;
		else
			txn_done_pulse <= 1'b0;
	end

	// Disk data reads need 1 extra cycle for BRAM read latency.
	// is_disk_data_read is combinational — active from cycle 0 of the request.
	// ready stays 0 until disk_rdata_valid is set (BRAM data available).
	// This prevents the CPU from latching rdata=0 on the first cycle.
	logic is_disk_data_read;
	assign is_disk_data_read = valid && !wvalid &&
	                           addr >= DISK_DATA_BASE && addr < DISK_DATA_BASE + 1024;

	assign ready = uart_thr_write_req ? (~fifo_full & ~txn_done_pulse) :
	               (is_disk_data_read ? (disk_rdata_valid & ~txn_done_pulse) : ~txn_done_pulse);

	// ================================================================
	// Simulation-only: print UART output
	// ================================================================
	generate
		if (SIMULATION) begin : gen_sim_print
			always_ff @(posedge cpu_clk) begin
				if (~reset && txn_fire && wvalid) begin
					if (addr == UART_RHR_THR && !uart_lcr[7]) begin
						$write("%c", tx_write_byte);
					end else if (addr == FINISH_ADDR) begin
						$write("Hello World!\n");
					end
				end
			end
		end
	endgenerate

endmodule
