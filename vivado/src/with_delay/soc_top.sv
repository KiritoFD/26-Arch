module soc_top #(
	parameter SIMULATION = 1'b0
)(
	input logic clk, reset,

	output logic [3:0] led,
	input logic [3:0] sw,
	output logic tx,
	input logic rx,

	/* SPI Flash */
	output logic spi_cs_n,
	output logic spi_sck,
	output logic spi_mosi,
	input  logic spi_miso,

	output logic dbg_clk_locked,
	output logic dbg_sys_reset,
	output logic dbg_cpu_clk,
	output logic dbg_cpu_valid,
	output logic dbg_ram_ready,
	output logic dbg_device_valid,
	output logic dbg_cpu_tx_write,
	output logic dbg_any_device_write,
	output logic dbg_ever_uart_write,
	output logic dbg_ever_device_read,
	output logic dbg_lsr_read,
	output logic [63:0] dbg_lsr_rdata,
	output logic [63:0] dbg_device_addr
);
	logic valid;
	logic [63:0] addr;
	logic [63:0] wdata;
	logic [1:0] burst;
	logic [7:0] len;
	logic [7:0] wstrobe;
	logic [63:0] rdata;
	logic ready;
	logic last;
	logic [2:0] size;

	logic ram_valid;
	logic [63:0] ram_addr;
	logic [63:0] ram_wdata;
	logic [1:0] ram_burst;
	logic [7:0] ram_len;
	logic [7:0] ram_wstrobe;
	logic [63:0] ram_rdata;
	logic ram_ready;
	logic ram_last;

	logic device_valid;
	logic [63:0] device_addr;
	logic [63:0] device_wdata;
	logic device_wvalid;
	logic [7:0] device_wstrobe;
	logic [63:0] device_rdata;
	logic device_ready;
	logic device_last;
	logic device_dbg_cpu_tx_write;
	logic device_dbg_any_device_write;
	logic device_dbg_ever_uart_write;
	logic device_dbg_ever_device_read;
	logic device_dbg_lsr_read;
	logic [63:0] device_dbg_lsr_rdata;

	logic cpu_clk;
	logic clk_locked;
	logic sys_reset;

	assign sys_reset = SIMULATION ? reset : (reset | ~clk_locked);
	assign dbg_clk_locked = clk_locked;
	assign dbg_sys_reset = sys_reset;
	assign dbg_cpu_clk = cpu_clk;
	assign dbg_cpu_valid = valid;
	assign dbg_ram_ready = ram_ready;
	assign dbg_device_valid = device_valid;
	assign dbg_cpu_tx_write = device_dbg_cpu_tx_write;
	assign dbg_any_device_write = device_dbg_any_device_write;
	assign dbg_ever_uart_write = device_dbg_ever_uart_write;
	assign dbg_ever_device_read = device_dbg_ever_device_read;
	assign dbg_lsr_read = device_dbg_lsr_read;
	assign dbg_lsr_rdata = device_dbg_lsr_rdata;
	assign dbg_device_addr = device_addr;

	/* mycpu */
	mycpu_top mycpu_top_inst(
		.clk(cpu_clk),
		.reset(sys_reset),
		.valid,
		.addr,
		.wdata,
		.burst,
		.len,
		.wstrobe,
		.rdata,
		.ready,
		.last,
		.size
	);


	/* CBus Crossbar */
	cbus_crossbar cbus_crossbar_inst(.*);

	/* RAM */
	bram_wrapper #(SIMULATION) bram_wrapper_inst(
		.clk(cpu_clk), .reset(sys_reset),
		.valid(ram_valid),
		.addr(ram_addr),
		.wdata(ram_wdata),
		.rdata(ram_rdata),
		.wstrobe(ram_wstrobe),
		.burst(ram_burst),
		.len(ram_len),
		.ready(ram_ready),
		.last(ram_last)
	);

	/* Device */
	device #(SIMULATION) device_inst (
		.valid(device_valid),
		.addr(device_addr),
		.wdata(device_wdata),
		.rdata(device_rdata),
		.wvalid(device_wvalid),
		.wstrobe(device_wstrobe),
		.ready(device_ready),
		.last(device_last),
		.dbg_cpu_tx_write(device_dbg_cpu_tx_write),
		.dbg_any_device_write(device_dbg_any_device_write),
		.dbg_ever_uart_write(device_dbg_ever_uart_write),
		.dbg_ever_device_read(device_dbg_ever_device_read),
		.dbg_lsr_read(device_dbg_lsr_read),
		.dbg_lsr_rdata(device_dbg_lsr_rdata),
		.clk,
		.reset(sys_reset),
		.cpu_clk(cpu_clk),
		.led,
		.sw,
		.tx,
		.rx,
		.spi_cs_n,
		.spi_sck,
		.spi_mosi,
		.spi_miso,
		.size
	);

	if (SIMULATION)
		assign cpu_clk = clk;
	else
		clk_wiz_0 clk_wiz_0(
			.sys_clk(clk),
			.reset(reset),
			.locked(clk_locked),
			.cpu_clk(cpu_clk)
		);
	

endmodule
