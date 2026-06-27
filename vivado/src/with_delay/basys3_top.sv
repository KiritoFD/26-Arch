module basys3_top (
	input logic clk, btnC,
	input logic [3:0] sw,
	output logic [3:0] led,
	output logic RsTx,
	input logic RsRx,

	/* SPI Flash */
	output logic QspiCSn,
	inout  logic [3:0] QspiDB
);
	logic dbg_clk_locked;
	logic dbg_sys_reset;
	(* mark_debug = "true", KEEP = "true" *) logic dbg_cpu_clk;
	(* mark_debug = "true", KEEP = "true" *) logic dbg_cpu_valid;
	logic dbg_ram_ready;
	logic dbg_device_valid;
	logic dbg_cpu_tx_write;
	logic dbg_any_device_write;
	(* mark_debug = "true", KEEP = "true" *) logic dbg_ever_uart_write;
	logic dbg_ever_device_read;
	logic dbg_lsr_read;
	(* mark_debug = "true" *) logic dbg_ever_thr_write;
	(* mark_debug = "true" *) logic dbg_tx_state_rdy;
	(* mark_debug = "true" *) logic dbg_tx_fifo_nonempty;
	(* mark_debug = "true" *) logic dbg_ever_tx_sent;
	(* mark_debug = "true" *) logic [7:0] dbg_tx_byte_cnt;
	logic [63:0] dbg_lsr_rdata;
	logic [63:0] dbg_device_addr;
	(* mark_debug = "true" *) logic cpu_tx;
	logic jtag_cpu_rx;
	logic [3:0] cpu_led;

	// SPI Flash internal signals
	logic spi_sck_int;
	logic spi_mosi_int;
	logic spi_miso_int;

	soc_top soc_top_inst (
		.clk,
		.reset(btnC),
		.sw(sw),
		.led(cpu_led),
		.tx(cpu_tx),
		.rx(jtag_cpu_rx),  // RX from JTAG UART, not RsRx
		.spi_cs_n(QspiCSn),
		.spi_sck(spi_sck_int),
		.spi_mosi(spi_mosi_int),
		.spi_miso(spi_miso_int),
		.dbg_clk_locked,
		.dbg_sys_reset,
		.dbg_cpu_clk,
		.dbg_cpu_valid,
		.dbg_ram_ready,
		.dbg_device_valid,
		.dbg_cpu_tx_write,
		.dbg_any_device_write,
		.dbg_ever_uart_write,
		.dbg_ever_device_read,
		.dbg_lsr_read,
		.dbg_ever_thr_write,
		.dbg_tx_state_rdy,
		.dbg_tx_fifo_nonempty,
		.dbg_ever_tx_sent,
		.dbg_tx_byte_cnt,
		.dbg_lsr_rdata,
		.dbg_device_addr
	);

	// ================================================================
	// SPI Flash pin mapping (Basys3 N25Q032):
	//   QspiDB[0] = D18 = DI (Data In)  = MOSI (FPGA→Flash)
	//   QspiDB[1] = D19 = DO (Data Out) = MISO (Flash→FPGA)
	//   QspiDB[2] = G18 = WP  (Write Protect, tie high)
	//   QspiDB[3] = F18 = HOLD (tie high)
	//   QspiCSn  = K19 = CS_N
	//   CCLK     = STARTUPE2 primitive (SPI clock output)
	// ================================================================
	assign QspiDB[0] = spi_mosi_int;  // DI = MOSI
	assign spi_miso_int = QspiDB[1];  // DO = MISO
	assign QspiDB[2] = 1'b1;          // WP = high (no write protect)
	assign QspiDB[3] = 1'b1;          // HOLD = high (no hold)

	// SPI Clock via STARTUPE2 primitive (Artix-7 CCLK output)
	STARTUPE2 #(
		.PROG_USR("FALSE"),
		.SIM_CCLK_FREQ(12.5)
	) STARTUPE2_inst (
		.CFGCLK(),
		.CFGMCLK(),
		.EOS(),
		.PREQ(),
		.CLK(clk),
		.GSR(1'b0),
		.GTS(1'b0),
		.KEYCLEARB(1'b0),
		.PACK(1'b0),
		.USRCCLKO(spi_sck_int),
		.USRCCLKTS(1'b0),
		.USRDONEO(1'b1),
		.USRDONETS(1'b1)
	);

	// ================================================================
	// JTAG UART Bridge DISABLED
	// BSCANE2 path proven non-functional (xsdb cannot read USER1 TDO),
	// and BSCANE2 primitive conflicts with Vivado ILA (both use JTAG).
	// jtag_cpu_rx tied to idle (1) so CPU UART RX sees no input.
	// ================================================================
	assign jtag_cpu_rx = 1'b1;  // UART idle line

	// RsTx outputs CPU UART TX directly (for USB-serial adapter on PC)
	assign RsTx = cpu_tx;

	// Debug LEDs
	logic [24:0] blink_cnt;
	always_ff @(posedge clk) begin
		if (btnC) blink_cnt <= 25'd0;
		else blink_cnt <= blink_cnt + 25'd1;
	end
	logic [23:0] cpu_clk_cnt;
	always_ff @(posedge dbg_cpu_clk) begin
		if (btnC) cpu_clk_cnt <= 24'd0;
		else cpu_clk_cnt <= cpu_clk_cnt + 24'd1;
	end
	assign led[0] = blink_cnt[24];        // ~3Hz blink = FPGA alive (100MHz domain)
assign led[1] = dbg_clk_locked;       // PLL lock status
assign led[2] = dbg_ever_thr_write;   // 1=CPU ever wrote THR DATA byte
assign led[3] = dbg_ever_tx_sent;     // 1=TX state machine ever left RDY
endmodule
