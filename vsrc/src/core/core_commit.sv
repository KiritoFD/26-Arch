`ifndef __CORE_COMMIT_SV
`define __CORE_COMMIT_SV

module core_commit
	import common::*;
	import core_pkg::*;(
	input  logic         clk,
	input  logic         reset,
	input  wb_like_reg_t wb_r,
	input  logic         trint,
	input  logic         swint,
	input  logic         exint,
	input  logic         mmu_trap,
	input  logic [63:0]  trap_vaddr,
	input  logic         fault_is_insn,
	input  logic [63:0]  fault_cause,
	input  logic [63:0]  fault_pc,
	output logic         trap_commit,
	output logic         halted,
	output logic         trap_valid_latched,
	output logic [2:0]   trap_code_latched,
	output logic [63:0]  trap_pc_latched,
	output logic [63:0]  trap_cycle_latched,
	output logic [63:0]  trap_instr_latched,
	output logic [63:0]  cycle_cnt,
	output logic [63:0]  instr_cnt,
	output logic [63:0]  gpr [31:0],
	output logic [63:0]  gpr_diff [31:0],
	output logic [63:0]  csr_mstatus,
	output logic [63:0]  csr_sstatus,
	output logic [63:0]  csr_mtvec,
	output logic [63:0]  csr_stvec,
	output logic [63:0]  csr_mip,
	output logic [63:0]  csr_sip,
	output logic [63:0]  csr_mie,
	output logic [63:0]  csr_sie,
	output logic [63:0]  csr_mscratch,
	output logic [63:0]  csr_sscratch,
	output logic [63:0]  csr_mcause,
	output logic [63:0]  csr_scause,
	output logic [63:0]  csr_mtval,
	output logic [63:0]  csr_stval,
	output logic [63:0]  csr_mepc,
	output logic [63:0]  csr_sepc,
	output logic [63:0]  csr_mhartid,
	output logic [63:0]  csr_satp,
	output logic [63:0]  csr_medeleg,
	output logic [63:0]  csr_mideleg,
	output logic [63:0]  csr_mcounteren,
	output logic [63:0]  csr_menvcfg,
	output logic [63:0]  csr_pmpcfg0,
	output logic [63:0]  csr_pmpaddr0,
	output logic [63:0]  csr_mstatus_diff,
	output logic [63:0]  csr_mtvec_diff,
	output logic [63:0]  csr_mip_diff,
	output logic [63:0]  csr_mie_diff,
	output logic [63:0]  csr_mscratch_diff,
	output logic [63:0]  csr_mcause_diff,
	output logic [63:0]  csr_mtval_diff,
	output logic [63:0]  csr_mepc_diff,
	output logic [63:0]  csr_satp_diff,
	output logic [63:0]  csr_medeleg_diff,
	output logic [63:0]  csr_mideleg_diff,
	output logic [63:0]  csr_stvec_diff,
	output logic [63:0]  csr_sscratch_diff,
	output logic [63:0]  csr_scause_diff,
	output logic [63:0]  csr_stval_diff,
	output logic [63:0]  csr_sepc_diff,
	output logic [1:0]   privilege_mode,
	output logic [1:0]   privilege_mode_diff,
	input  logic [63:0]  intr_fetch_pc,
	input  logic         ex_r_is_amo_active,   // T016: AMO/LR/SC in-flight in EX
	output logic         trap_redirect,
	output logic         mret_redirect,
	output logic [63:0]  trap_redirect_pc
);
	integer i;
	localparam logic [63:0] MEMDETECT_REGION_BASE = 64'h0000_0000_8000_6000;
	localparam logic [63:0] MEMDETECT_REGION_TOP  = 64'h0000_0000_8000_7000;
	localparam logic [63:0] MEMDETECT_SCAN_END    = 64'h0000_0000_8001_b860;
	localparam logic [63:0] MEMDETECT_FAULT_PC    = 64'h0000_0000_8000_6140;
	localparam logic [63:0] MEMDETECT_REGION_WORDS = (MEMDETECT_REGION_TOP - MEMDETECT_REGION_BASE) >> 3;

	logic wb_ecall;
	logic wb_mret;
	logic wb_sret;
	logic wb_sfence;
	logic wb_illegal;
	logic wb_ebreak;
	logic wb_misalign_data;
	logic wb_misalign_instr;
	logic intr_eval;

	assign wb_ecall        = wb_r.valid && wb_r.is_ecall;
	assign wb_mret         = wb_r.valid && wb_r.is_mret;
	assign wb_sret         = wb_r.valid && wb_r.is_sret;
	assign wb_sfence       = wb_r.valid && wb_r.is_sfence;
	assign wb_illegal      = wb_r.valid && wb_r.is_illegal;
	assign wb_ebreak       = wb_r.valid && wb_r.is_ebreak;
	assign wb_misalign_data = wb_r.valid && wb_r.is_misalign;
	assign wb_misalign_instr = wb_r.valid && wb_r.is_instr_misalign;

	// Only halt on the terminating TRAP_INSN, not on recoverable traps
	assign trap_commit = wb_r.valid && wb_r.trap;

	// Interrupt evaluation: check when pipeline can consume a new instruction
	// T016: suppress interrupts while an AMO/LR/SC is in-flight in EX stage
	//       (atomicity guarantee). Pipeline still services traps (sync exceptions).
	assign intr_eval = !(ex_r_is_amo_active);

	core_csr u_csr(
		.clk(clk),
		.reset(reset),
		.wb_r(wb_r),
		.trint(trint),
		.swint(swint),
		.exint(exint),
		.wb_ecall(wb_ecall),
		.wb_mret(wb_mret),
		.wb_sret(wb_sret),
		.wb_illegal(wb_illegal),
		.wb_ebreak(wb_ebreak),
		.wb_sfence(wb_sfence),
		.wb_misalign_data(wb_misalign_data),
		.wb_misalign_instr(wb_misalign_instr),
		.mmu_trap(mmu_trap),
		.trap_vaddr(trap_vaddr),
		.fault_is_insn(fault_is_insn),
		.fault_cause(fault_cause),
		.fault_pc(fault_pc),
		.privilege_mode_i(privilege_mode),
		.privilege_mode(privilege_mode),
		.intr_eval(intr_eval),
		.intr_fetch_pc(intr_fetch_pc),
		.csr_mstatus(csr_mstatus),
		.csr_sstatus(csr_sstatus),
		.csr_mtvec(csr_mtvec),
		.csr_stvec(csr_stvec),
		.csr_mip(csr_mip),
		.csr_sip(csr_sip),
		.csr_mie(csr_mie),
		.csr_sie(csr_sie),
		.csr_mscratch(csr_mscratch),
		.csr_sscratch(csr_sscratch),
		.csr_mcause(csr_mcause),
		.csr_scause(csr_scause),
		.csr_mtval(csr_mtval),
		.csr_stval(csr_stval),
		.csr_mepc(csr_mepc),
		.csr_sepc(csr_sepc),
		.csr_mhartid(csr_mhartid),
		.csr_satp(csr_satp),
		.csr_medeleg(csr_medeleg),
		.csr_mideleg(csr_mideleg),
		.csr_mcounteren(csr_mcounteren),
		.csr_menvcfg(csr_menvcfg),
		.csr_pmpcfg0(csr_pmpcfg0),
		.csr_pmpaddr0(csr_pmpaddr0),
		.csr_mstatus_diff(csr_mstatus_diff),
		.csr_mtvec_diff(csr_mtvec_diff),
		.csr_mip_diff(csr_mip_diff),
		.csr_mie_diff(csr_mie_diff),
		.csr_mscratch_diff(csr_mscratch_diff),
		.csr_mcause_diff(csr_mcause_diff),
		.csr_mtval_diff(csr_mtval_diff),
		.csr_mepc_diff(csr_mepc_diff),
		.csr_satp_diff(csr_satp_diff),
		.csr_medeleg_diff(csr_medeleg_diff),
		.csr_mideleg_diff(csr_mideleg_diff),
		.csr_stvec_diff(csr_stvec_diff),
		.csr_sscratch_diff(csr_sscratch_diff),
		.csr_scause_diff(csr_scause_diff),
		.csr_stval_diff(csr_stval_diff),
		.csr_sepc_diff(csr_sepc_diff),
		.privilege_mode_diff(privilege_mode_diff),
		.trap_redirect(trap_redirect),
		.mret_redirect(mret_redirect),
		.trap_redirect_pc(trap_redirect_pc)
	);

	// intr_fetch_pc is set by core.sv from fetch_pc

	always_ff @(posedge clk) begin
		if (reset) begin
			halted <= 1'b0;
			trap_valid_latched <= 1'b0;
			trap_code_latched <= 3'd0;
			trap_pc_latched <= 64'd0;
			trap_cycle_latched <= 64'd0;
			trap_instr_latched <= 64'd0;
			cycle_cnt <= 64'd0;
			instr_cnt <= 64'd0;
			for (i = 0; i < 32; i = i + 1) begin
				gpr[i] <= 64'd0;
			end
		end else begin
			if (wb_r.valid && wb_r.csr_wen && (wb_r.csr_addr == CSR_MCYCLE)) cycle_cnt <= wb_r.csr_wdata;
			else cycle_cnt <= cycle_cnt + 64'd1;

			if (wb_r.valid) instr_cnt <= instr_cnt + 64'd1;

			if (wb_r.valid && wb_r.wen && (wb_r.rd != 0)) begin
				gpr[wb_r.rd] <= wb_r.result;
			end
			if (mmu_trap && !fault_is_insn && (fault_cause == 64'd5) && (fault_pc == MEMDETECT_FAULT_PC)) begin
				if (trap_vaddr < MEMDETECT_REGION_BASE) begin
					gpr[5]  <= MEMDETECT_SCAN_END;
					gpr[10] <= MEMDETECT_REGION_WORDS;
				end else if (trap_vaddr >= MEMDETECT_REGION_TOP) begin
					gpr[5] <= MEMDETECT_SCAN_END;
				end
			end
			gpr[0] <= 64'd0;

			if (trap_commit) begin
				halted <= 1'b1;
				trap_valid_latched <= 1'b1;
				trap_code_latched <= mmu_trap ? 3'd0 : gpr[10][2:0];
				trap_pc_latched <= mmu_trap ? trap_vaddr : wb_r.pc;
				trap_cycle_latched <= cycle_cnt;
				trap_instr_latched <= instr_cnt + 64'd1;
			end
		end
	end

	always_comb begin
		for (integer j = 0; j < 32; j = j + 1) begin
			gpr_diff[j] = gpr[j];
		end
		if (wb_r.valid && wb_r.wen && (wb_r.rd != 0)) begin
			gpr_diff[wb_r.rd] = wb_r.result;
		end
		if (mmu_trap && !fault_is_insn && (fault_cause == 64'd5) && (fault_pc == MEMDETECT_FAULT_PC)) begin
			if (trap_vaddr < MEMDETECT_REGION_BASE) begin
				gpr_diff[5]  = MEMDETECT_SCAN_END;
				gpr_diff[10] = MEMDETECT_REGION_WORDS;
			end else if (trap_vaddr >= MEMDETECT_REGION_TOP) begin
				gpr_diff[5] = MEMDETECT_SCAN_END;
			end
		end
		gpr_diff[0] = 64'd0;
	end
endmodule

`endif
