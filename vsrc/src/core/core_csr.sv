`ifndef __CORE_CSR_SV
`define __CORE_CSR_SV

module core_csr
	import common::*;
	import core_pkg::*;(
	input  logic         clk,
	input  logic         reset,
	input  wb_like_reg_t wb_r,
	input  logic         trint,
	input  logic         swint,
	input  logic         exint,
	input  logic         wb_ecall,
	input  logic         wb_mret,
	input  logic         wb_illegal,
	input  logic         wb_misalign_data,
	input  logic         mmu_trap,
	input  logic [63:0]  trap_vaddr,
	input  logic         fault_is_insn,
	input  logic [1:0]   privilege_mode_i,
	input  logic         intr_eval,  // evaluate interrupts this cycle
	input  logic [63:0]  intr_fetch_pc,  // current fetch PC for interrupt mepc
	output logic [1:0]   privilege_mode,
	output logic [63:0]  csr_mstatus,
	output logic [63:0]  csr_mtvec,
	output logic [63:0]  csr_mip,
	output logic [63:0]  csr_mie,
	output logic [63:0]  csr_mscratch,
	output logic [63:0]  csr_mcause,
	output logic [63:0]  csr_mtval,
	output logic [63:0]  csr_mepc,
	output logic [63:0]  csr_mhartid,
	output logic [63:0]  csr_satp,
	output logic [63:0]  csr_mstatus_diff,
	output logic [63:0]  csr_mtvec_diff,
	output logic [63:0]  csr_mip_diff,
	output logic [63:0]  csr_mie_diff,
	output logic [63:0]  csr_mscratch_diff,
	output logic [63:0]  csr_mcause_diff,
	output logic [63:0]  csr_mtval_diff,
	output logic [63:0]  csr_mepc_diff,
	output logic [63:0]  csr_satp_diff,
	output logic [1:0]   privilege_mode_diff,
	output logic         trap_redirect,  // pipeline should redirect to mtvec
	output logic         mret_redirect,  // pipeline should redirect to mepc
	output logic [63:0]  trap_redirect_pc  // target PC for redirect
);
	logic [63:0] csr_mip_raw;
	logic [63:0] csr_mip_raw_diff;

	// Interrupt evaluation
	logic intr_pending;
	logic [63:0] intr_cause;
	logic intr_meip, intr_msip, intr_mtip;

	assign intr_meip = (privilege_mode_i != 2'd3 || csr_mstatus[3]) && csr_mip[11] && csr_mie[11];
	assign intr_msip = (privilege_mode_i != 2'd3 || csr_mstatus[3]) && csr_mip[3]  && csr_mie[3];
	assign intr_mtip = (privilege_mode_i != 2'd3 || csr_mstatus[3]) && csr_mip[7]  && csr_mie[7];

	assign intr_pending = intr_meip || intr_msip || intr_mtip;
	assign intr_cause = intr_meip ? {1'b1, 63'd11} :  // MEIP  (11)
	                    intr_msip ? {1'b1, 63'd3}  :  // MSIP  (3)
	                    {1'b1, 63'd7};                  // MTIP  (7)

	assign csr_mhartid = 64'd0;
	assign csr_mip = (csr_mip_raw & ~64'h0000_0000_0000_0888) |
	                 ({63'd0, exint} << 11) |
	                 ({63'd0, trint} << 7) |
	                 ({63'd0, swint} << 3);
	assign csr_mip_diff = (csr_mip_raw_diff & ~64'h0000_0000_0000_0888) |
	                      ({63'd0, exint} << 11) |
	                      ({63'd0, trint} << 7) |
	                      ({63'd0, swint} << 3);

	// Trap cause selection for exceptions (interrupts handled separately)
	function automatic logic [63:0] get_excp_cause();
		if (mmu_trap) begin
			if (fault_is_insn) return 64'd12;
			else if (wb_r.is_store) return 64'd15;
			else return 64'd13;
		end else if (wb_ecall) begin
			return 64'd11;
		end else if (wb_illegal) begin
			return 64'd2;
		end else if (wb_misalign_data) begin
			if (wb_r.is_store) return 64'd6;
			else return 64'd4;
		end
		return 64'd0;
	endfunction

	// Compute "next" values for diffs combinationally
	logic [63:0] next_mstatus, next_mepc, next_mcause, next_mtval, next_mtvec;
	logic [63:0] next_mip_raw, next_mie, next_mscratch, next_satp;
	logic [1:0]  next_privilege_mode;

	always_ff @(posedge clk) begin
		if (reset) begin
			csr_mstatus  <= 64'd0;
			csr_mtvec    <= 64'd0;
			csr_mip_raw  <= 64'd0;
			csr_mie      <= 64'd0;
			csr_mscratch <= 64'd0;
			csr_mcause   <= 64'd0;
			csr_mtval    <= 64'd0;
			csr_mepc     <= 64'd0;
			csr_satp     <= 64'd0;
			privilege_mode <= 2'd0;
		end else begin
			if (intr_eval && intr_pending) begin
				csr_mepc   <= intr_fetch_pc;
				csr_mcause <= intr_cause;
				csr_mtval  <= 64'd0;
				csr_mstatus[7] <= csr_mstatus[3];
				csr_mstatus[3] <= 1'b0;
				csr_mstatus[12:11] <= privilege_mode_i;
				privilege_mode <= 2'd3;
			end else if (mmu_trap) begin
				csr_mepc   <= trap_vaddr;
				if (fault_is_insn)
					csr_mcause <= 64'd12;
				else if (wb_r.is_store)
					csr_mcause <= 64'd15;
				else
					csr_mcause <= 64'd13;
				csr_mtval  <= trap_vaddr;
				csr_mstatus[7] <= csr_mstatus[3];
				csr_mstatus[3] <= 1'b0;
				csr_mstatus[12:11] <= privilege_mode_i;
				privilege_mode <= 2'd3;
			end else if (wb_ecall) begin
				csr_mepc   <= wb_r.pc;
				csr_mcause <= 64'd11;
				csr_mtval  <= 64'd0;
				csr_mstatus[7] <= csr_mstatus[3];
				csr_mstatus[3] <= 1'b0;
				csr_mstatus[12:11] <= privilege_mode_i;
				privilege_mode <= 2'd3;
			end else if (wb_illegal) begin
				csr_mepc   <= wb_r.pc;
				csr_mcause <= 64'd2;
				csr_mtval  <= {32'd0, wb_r.instr};
				csr_mstatus[7] <= csr_mstatus[3];
				csr_mstatus[3] <= 1'b0;
				csr_mstatus[12:11] <= privilege_mode_i;
				privilege_mode <= 2'd3;
			end else if (wb_misalign_data) begin
				csr_mepc   <= wb_r.pc;
				if (wb_r.is_store)
					csr_mcause <= 64'd6;
				else
					csr_mcause <= 64'd4;
				csr_mtval  <= wb_r.mem_addr;
				csr_mstatus[7] <= csr_mstatus[3];
				csr_mstatus[3] <= 1'b0;
				csr_mstatus[12:11] <= privilege_mode_i;
				privilege_mode <= 2'd3;
			end else if (wb_mret) begin
				csr_mstatus[3] <= csr_mstatus[7];
				csr_mstatus[7] <= 1'b1;
				csr_mstatus[12:11] <= 2'b00;
				privilege_mode <= csr_mstatus[12:11];
			end else if (wb_r.valid && wb_r.csr_wen) begin
				unique case (wb_r.csr_addr)
					CSR_MSTATUS:  csr_mstatus  <= wb_r.csr_wdata;
					CSR_MTVEC:    csr_mtvec    <= wb_r.csr_wdata;
					CSR_MIP:      csr_mip_raw  <= wb_r.csr_wdata;
					CSR_MIE:      csr_mie      <= wb_r.csr_wdata;
					CSR_MSCRATCH: csr_mscratch <= wb_r.csr_wdata;
					CSR_MCAUSE:   csr_mcause   <= wb_r.csr_wdata;
					CSR_MTVAL:    csr_mtval    <= wb_r.csr_wdata;
					CSR_MEPC:     csr_mepc     <= wb_r.csr_wdata;
					CSR_SATP:     csr_satp     <= wb_r.csr_wdata;
					default: begin end
				endcase
			end
		end
	end

	always_comb begin
		next_mstatus   = csr_mstatus;
		next_mepc      = csr_mepc;
		next_mcause    = csr_mcause;
		next_mtval     = csr_mtval;
		next_mtvec     = csr_mtvec;
		next_mip_raw   = csr_mip_raw;
		next_mie       = csr_mie;
		next_mscratch  = csr_mscratch;
		next_satp      = csr_satp;
		next_privilege_mode = privilege_mode;

		trap_redirect = 1'b0;
		mret_redirect = 1'b0;
		trap_redirect_pc = 64'd0;

		if (intr_eval && intr_pending) begin
			next_mepc = intr_fetch_pc;
			next_mcause = intr_cause;
			next_mtval = 64'd0;
			next_mstatus = csr_mstatus;
			next_mstatus[7] = csr_mstatus[3];
			next_mstatus[3] = 1'b0;
			next_mstatus[12:11] = privilege_mode_i;
			next_privilege_mode = 2'd3;
			trap_redirect = 1'b1;
			trap_redirect_pc = csr_mtvec;
		end else if (mmu_trap) begin
			next_mepc = trap_vaddr;
			next_mcause = get_excp_cause();
			next_mtval = trap_vaddr;
			next_mstatus = csr_mstatus;
			next_mstatus[7] = csr_mstatus[3];
			next_mstatus[3] = 1'b0;
			next_mstatus[12:11] = privilege_mode_i;
			next_privilege_mode = 2'd3;
			trap_redirect = 1'b1;
			trap_redirect_pc = csr_mtvec;
		end else if (wb_ecall || wb_illegal || wb_misalign_data) begin
			next_mepc = wb_r.pc;
			next_mcause = get_excp_cause();
			next_mtval = wb_illegal ? {32'd0, wb_r.instr} : (wb_misalign_data ? wb_r.mem_addr : 64'd0);
			next_mstatus = csr_mstatus;
			next_mstatus[7] = csr_mstatus[3];
			next_mstatus[3] = 1'b0;
			next_mstatus[12:11] = privilege_mode_i;
			next_privilege_mode = 2'd3;
			trap_redirect = 1'b1;
			trap_redirect_pc = csr_mtvec;
		end else if (wb_mret) begin
			next_mstatus = csr_mstatus;
			next_mstatus[3] = csr_mstatus[7];
			next_mstatus[7] = 1'b1;
			next_mstatus[12:11] = 2'b00;
			next_privilege_mode = csr_mstatus[12:11];
			mret_redirect = 1'b1;
			trap_redirect_pc = csr_mepc;
		end else if (wb_r.valid && wb_r.csr_wen) begin
			unique case (wb_r.csr_addr)
				CSR_MSTATUS:  next_mstatus  = wb_r.csr_wdata;
				CSR_MTVEC:    next_mtvec    = wb_r.csr_wdata;
				CSR_MIP:      next_mip_raw  = wb_r.csr_wdata;
				CSR_MIE:      next_mie      = wb_r.csr_wdata;
				CSR_MSCRATCH: next_mscratch = wb_r.csr_wdata;
				CSR_MCAUSE:   next_mcause   = wb_r.csr_wdata;
				CSR_MTVAL:    next_mtval    = wb_r.csr_wdata;
				CSR_MEPC:     next_mepc     = wb_r.csr_wdata;
				CSR_SATP:     next_satp     = wb_r.csr_wdata;
				default: begin end
			endcase
		end
	end

	assign csr_mstatus_diff  = next_mstatus;
	assign csr_mtvec_diff    = next_mtvec;
	assign csr_mip_raw_diff  = next_mip_raw;
	assign csr_mie_diff      = next_mie;
	assign csr_mscratch_diff = next_mscratch;
	assign csr_mcause_diff   = next_mcause;
	assign csr_mtval_diff    = next_mtval;
	assign csr_mepc_diff     = next_mepc;
	assign csr_satp_diff     = next_satp;
	assign privilege_mode_diff = privilege_mode;
endmodule

`endif
