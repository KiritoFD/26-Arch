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
	logic dbg_cpu_clk;
	logic dbg_cpu_valid;
	logic dbg_ram_ready;
	logic dbg_device_valid;
	logic dbg_cpu_tx_write;
	logic dbg_any_device_write;
	logic dbg_ever_uart_write;
	logic dbg_ever_device_read;
	logic dbg_lsr_read;
	logic [63:0] dbg_lsr_rdata;
	logic [63:0] dbg_device_addr;
	logic cpu_tx;
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
	// JTAG UART Bridge
	// Captures CPU UART TX via BSCANE2, sends RX data back to CPU
	// This bypasses the non-functional FTDI Channel B UART path
	// ================================================================
	logic jtag_tx_avail;

	jtag_uart jtag_uart_inst (
		.clk(dbg_cpu_clk),      // Use 25MHz CPU clock for UART timing
		.reset(btnC),
		.cpu_tx(cpu_tx),        // CPU UART TX output
		.cpu_rx(jtag_cpu_rx),   // UART RX input to CPU
		.tx_data_avail(jtag_tx_avail)
	);

	// RsTx unused (FTDI Channel B not connected to FPGA UART pins on Basys3)
	assign RsTx = 1'b1;  // Idle high

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
	assign led[0] = blink_cnt[24];      // ~3Hz blink = FPGA alive (100MHz domain)
assign led[1] = dbg_clk_locked;     // PLL lock status
assign led[2] = dbg_ever_uart_write; // 1=CPU ever wrote UART (reached console output)
assign led[3] = jtag_tx_avail;       // 1=jtag_uart TX FIFO has data (capture worked)
endmodule
