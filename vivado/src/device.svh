`ifndef __DEVICE_SVH
`define __DEVICE_SVH

parameter [63:0] FINISH_ADDR = 64'h23333000;
parameter [63:0] SW_ADDR = 64'h23333008;

parameter [63:0] CLINT_MTIME = 64'h3800bff8;
parameter [63:0] COUNTER_2 = 64'h20003000;

parameter [63:0] UART_BASE   = 64'h10000000;
parameter [63:0] UART_RHR_THR = 64'h10000000;
parameter [63:0] UART_IER     = 64'h10000001;
parameter [63:0] UART_FCR_ISR = 64'h10000002;
parameter [63:0] UART_LCR     = 64'h10000003;
parameter [63:0] UART_LSR     = 64'h10000005;

parameter [63:0] DISK_BASE     = 64'h10001000;
parameter [63:0] DISK_BLOCKNO  = 64'h10001000;
parameter [63:0] DISK_STATUS   = 64'h10001008;
parameter [63:0] DISK_DATA_BASE = 64'h10001100;

parameter DISK_DATA_WORDS = 256;

`endif
