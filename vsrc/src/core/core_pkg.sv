`ifndef __CORE_PKG_SV
`define __CORE_PKG_SV

package core_pkg;
	import common::*;

	localparam logic [31:0] TRAP_INSN = 32'h0005_006b;

	localparam logic [3:0] ALU_ADD  = 4'd0;
	localparam logic [3:0] ALU_SUB  = 4'd1;
	localparam logic [3:0] ALU_XOR  = 4'd2;
	localparam logic [3:0] ALU_OR   = 4'd3;
	localparam logic [3:0] ALU_AND  = 4'd4;
	localparam logic [3:0] ALU_SLL  = 4'd5;
	localparam logic [3:0] ALU_SRL  = 4'd6;
	localparam logic [3:0] ALU_SRA  = 4'd7;
	localparam logic [3:0] ALU_SLT  = 4'd8;
	localparam logic [3:0] ALU_SLTU = 4'd9;
	localparam logic [3:0] ALU_MUL  = 4'd10;
	localparam logic [3:0] ALU_DIV  = 4'd11;
	localparam logic [3:0] ALU_DIVU = 4'd12;
	localparam logic [3:0] ALU_REM  = 4'd13;
	localparam logic [3:0] ALU_REMU = 4'd14;

	localparam logic [4:0] AMO_CMD_SWAP = 5'd4;
	localparam logic [4:0] AMO_CMD_XOR  = 5'd5;
	localparam logic [4:0] AMO_CMD_LR   = 5'd6;
	localparam logic [4:0] AMO_CMD_SC   = 5'd7;
	localparam logic [4:0] AMO_CMD_ADD  = 5'd8;
	localparam logic [4:0] AMO_CMD_AND  = 5'd9;
	localparam logic [4:0] AMO_CMD_OR   = 5'd10;
	localparam logic [4:0] AMO_CMD_MIN  = 5'd11;
	localparam logic [4:0] AMO_CMD_MAX  = 5'd12;
	localparam logic [4:0] AMO_CMD_MINU = 5'd13;
	localparam logic [4:0] AMO_CMD_MAXU = 5'd14;

	// AMO hardware execution state machine states
	localparam logic [2:0] AMO_ST_IDLE    = 3'd0;
	localparam logic [2:0] AMO_ST_LOAD    = 3'd1;
	localparam logic [2:0] AMO_ST_LOAD_W  = 3'd2;  // wait for load data
	localparam logic [2:0] AMO_ST_STORE    = 3'd3;
	localparam logic [2:0] AMO_ST_STORE_W  = 3'd4;  // wait for store complete
	localparam logic [2:0] AMO_ST_DONE    = 3'd5;

	localparam logic [11:0] CSR_SATP     = 12'h180;
	localparam logic [11:0] CSR_SSTATUS  = 12'h100;
	localparam logic [11:0] CSR_SIE      = 12'h104;
	localparam logic [11:0] CSR_STVEC    = 12'h105;
	localparam logic [11:0] CSR_MSTATUS  = 12'h300;
	localparam logic [11:0] CSR_MEDELEG  = 12'h302;
	localparam logic [11:0] CSR_MIDELEG  = 12'h303;
	localparam logic [11:0] CSR_MIE      = 12'h304;
	localparam logic [11:0] CSR_MTVEC    = 12'h305;
	localparam logic [11:0] CSR_MCOUNTEREN = 12'h306;
	localparam logic [11:0] CSR_MENVCFG  = 12'h30a;
	localparam logic [11:0] CSR_PMPCFG0  = 12'h3a0;
	localparam logic [11:0] CSR_MSCRATCH = 12'h340;
	localparam logic [11:0] CSR_SSCRATCH = 12'h140;
	localparam logic [11:0] CSR_MEPC     = 12'h341;
	localparam logic [11:0] CSR_SEPC     = 12'h141;
	localparam logic [11:0] CSR_MCAUSE   = 12'h342;
	localparam logic [11:0] CSR_SCAUSE   = 12'h142;
	localparam logic [11:0] CSR_MTVAL    = 12'h343;
	localparam logic [11:0] CSR_STVAL    = 12'h143;
	localparam logic [11:0] CSR_MIP      = 12'h344;
	localparam logic [11:0] CSR_SIP      = 12'h144;
	localparam logic [11:0] CSR_PMPADDR0 = 12'h3b0;
	localparam logic [11:0] CSR_MCYCLE   = 12'hb00;
	localparam logic [11:0] CSR_MHARTID  = 12'hf14;

	localparam logic [63:0] MSTATUS_MASK = 64'h0000_0000_007e_79bb;
	localparam logic [63:0] SSTATUS_MASK = 64'h8000_0003_000d_e122;  // SD+UXL+MXR+SUM+XS+FS+SPP(8)+SPIE(5)+SIE(1)
	localparam logic [63:0] MIP_MASK     = 64'h0000_0000_0000_0333;
	localparam logic [63:0] MTVEC_MASK   = ~64'h0000_0000_0000_0002;
	localparam logic [63:0] STVEC_MASK   = ~64'h0000_0000_0000_0002;
	localparam logic [63:0] SIE_MASK     = 64'h0000_0000_0000_0222;
	localparam logic [63:0] SIP_MASK     = 64'h0000_0000_0000_0222;
	localparam logic [63:0] MEDELEG_MASK = 64'h0000_0000_0000_f3ff;
	localparam logic [63:0] MIDELEG_MASK = 64'h0000_0000_0000_0222;

	typedef struct packed {
		logic        valid;
		logic [63:0] pc;
		logic [31:0] instr;
	} id_reg_t;

	typedef struct packed {
		logic        valid;
		logic        trap;
		logic        wen;
		logic        is_word;
		logic [3:0]  alu_cmd;
		logic [4:0]  rd;
		logic [63:0] pc;
		logic [31:0] instr;
		logic [63:0] op1;
		logic [63:0] op2;
		logic [63:0] imm;
		logic [63:0] rs2_store;
		logic        is_load;
		logic        is_store;
		logic [2:0]  mem_size;
		logic        mem_unsigned;
		logic        is_branch;
		logic [2:0]  br_funct3;
		logic        is_jal;
		logic        is_jalr;
		logic        wb_pc4;
		logic        csr_wen;
		logic [11:0] csr_addr;
		logic [63:0] csr_wdata;
		logic        is_ecall;
		logic        is_mret;
		logic        is_sret;
		logic        is_amo;
		logic [4:0]  amo_cmd;
		logic        is_sfence;     // SFENCE.VMA: flush TLB
		logic        is_misalign;
		logic        is_instr_misalign;
		logic        is_illegal;
		logic        is_ebreak;
	} ex_reg_t;

	typedef struct packed {
		logic        valid;
		logic        trap;
		logic        wen;
		logic [4:0]  rd;
		logic [63:0] pc;
		logic [31:0] instr;
		logic [63:0] result;
		logic        is_load;
		logic        is_store;
		logic [2:0]  mem_size;
		logic        mem_unsigned;
		logic [63:0] mem_addr;
		logic [63:0] mem_wdata;
		logic [7:0]  mem_wstrb;
		logic        csr_wen;
		logic [11:0] csr_addr;
		logic [63:0] csr_wdata;
		logic        is_ecall;
		logic        is_mret;
		logic        is_sret;
		logic        is_amo;
		logic [4:0]  amo_cmd;
		logic        is_sfence;     // SFENCE.VMA: flush TLB
		logic        is_misalign;
		logic        is_instr_misalign;
		logic        is_illegal;
		logic        is_ebreak;
	} wb_like_reg_t;

	function automatic logic is_mdu_cmd(input logic [3:0] cmd);
		begin
			is_mdu_cmd = (cmd == ALU_MUL) || (cmd == ALU_DIV) || (cmd == ALU_DIVU) ||
			             (cmd == ALU_REM) || (cmd == ALU_REMU);
		end
	endfunction

	function automatic logic [63:0] sanitize_csr_write(input logic [11:0] addr, input logic [63:0] data);
		begin
			sanitize_csr_write = data;
			unique case (addr)
				CSR_MSTATUS: sanitize_csr_write = data & MSTATUS_MASK;
				CSR_SSTATUS: sanitize_csr_write = data & SSTATUS_MASK;
				CSR_SIE:     sanitize_csr_write = data & SIE_MASK;
				CSR_SIP:     sanitize_csr_write = data & SIP_MASK;
				CSR_MEDELEG: sanitize_csr_write = data & MEDELEG_MASK;
				CSR_MIDELEG: sanitize_csr_write = data & MIDELEG_MASK;
				CSR_MTVEC:   sanitize_csr_write = data & MTVEC_MASK;
				CSR_STVEC:   sanitize_csr_write = data & STVEC_MASK;
				CSR_MIP:     sanitize_csr_write = data & MIP_MASK;
				default  : begin end
			endcase
		end
	endfunction
endpackage

`endif
