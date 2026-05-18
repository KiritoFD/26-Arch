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
	output logic [1:0]   privilege_mode,
	output logic [1:0]   privilege_mode_diff
);
	integer i;

	logic wb_ecall;
	logic wb_mret;
	logic trap_detected;
	assign wb_ecall = wb_r.valid && wb_r.is_ecall;
	assign wb_mret  = wb_r.valid && wb_r.is_mret;

	always_ff @(posedge clk) begin
		if (reset) trap_detected <= 1'b0;
		else trap_detected <= mmu_trap;
	end

	assign trap_commit = (wb_r.valid && wb_r.trap) || trap_detected;

	core_csr u_csr(
		.clk(clk),
		.reset(reset),
		.wb_r(wb_r),
		.trint(trint),
		.swint(swint),
		.exint(exint),
		.wb_ecall(wb_ecall),
		.wb_mret(wb_mret),
		.mmu_trap(mmu_trap),
		.trap_vaddr(trap_vaddr),
		.fault_is_insn(fault_is_insn),
		.privilege_mode_i(privilege_mode),
		.privilege_mode(privilege_mode),
		.csr_mstatus(csr_mstatus),
		.csr_mtvec(csr_mtvec),
		.csr_mip(csr_mip),
		.csr_mie(csr_mie),
		.csr_mscratch(csr_mscratch),
		.csr_mcause(csr_mcause),
		.csr_mtval(csr_mtval),
		.csr_mepc(csr_mepc),
		.csr_mhartid(csr_mhartid),
		.csr_satp(csr_satp),
		.csr_mstatus_diff(csr_mstatus_diff),
		.csr_mtvec_diff(csr_mtvec_diff),
		.csr_mip_diff(csr_mip_diff),
		.csr_mie_diff(csr_mie_diff),
		.csr_mscratch_diff(csr_mscratch_diff),
		.csr_mcause_diff(csr_mcause_diff),
		.csr_mtval_diff(csr_mtval_diff),
		.csr_mepc_diff(csr_mepc_diff),
		.csr_satp_diff(csr_satp_diff),
		.privilege_mode_diff(privilege_mode_diff)
	);

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
			if (wb_r.valid && !mmu_trap && wb_r.csr_wen && (wb_r.csr_addr == CSR_MCYCLE)) cycle_cnt <= wb_r.csr_wdata;
			else cycle_cnt <= cycle_cnt + 64'd1;

			if (wb_r.valid && !mmu_trap) instr_cnt <= instr_cnt + 64'd1;

			if (wb_r.valid && !mmu_trap && wb_r.wen && (wb_r.rd != 0)) begin
				gpr[wb_r.rd] <= wb_r.result;
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
		for (int j = 0; j < 32; j = j + 1) begin
			gpr_diff[j] = gpr[j];
		end
		if (wb_r.valid && !mmu_trap && wb_r.wen && (wb_r.rd != 0)) begin
			gpr_diff[wb_r.rd] = wb_r.result;
		end
		gpr_diff[0] = 64'd0;
	end
endmodule

`endif
