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
	input  logic         mmu_trap,
	input  logic [63:0]  trap_vaddr,
	input  logic         fault_is_insn,
	input  logic [1:0]   privilege_mode_i,
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
	output logic [1:0]   privilege_mode_diff
);
	logic [63:0] csr_mip_raw;
	logic [63:0] csr_mip_raw_diff;

	assign csr_mhartid = 64'd0;
	assign csr_mip = (csr_mip_raw & ~64'h0000_0000_0000_0888) |
	                 ({63'd0, exint} << 11) |
	                 ({63'd0, trint} << 7) |
	                 ({63'd0, swint} << 3);
	assign csr_mip_diff = (csr_mip_raw_diff & ~64'h0000_0000_0000_0888) |
	                      ({63'd0, exint} << 11) |
	                      ({63'd0, trint} << 7) |
	                      ({63'd0, swint} << 3);

	// Compute "next" values for diffs combinationally
	// This ensures Difftest sees the CSR state that becomes visible this cycle
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
			// Handle traps: higher priority than CSR writes
			if (mmu_trap) begin
				csr_mepc   <= trap_vaddr;
				// Determine mcause based on fault type
				if (fault_is_insn)
					csr_mcause <= 64'd12;  // Instruction page fault
				else if (wb_r.is_store)
					csr_mcause <= 64'd15;  // Store/AMO page fault
				else
					csr_mcause <= 64'd13;  // Load page fault
				csr_mtval  <= trap_vaddr;
				
				// Update mstatus: MPIE := MIE, MIE := 0, MPP := prev mode
				csr_mstatus[7] <= csr_mstatus[3];
				csr_mstatus[3] <= 1'b0;
				csr_mstatus[12:11] <= privilege_mode_i;
				
				privilege_mode <= 2'd3;
			end else if (wb_ecall) begin
				csr_mepc   <= wb_r.pc;
				csr_mcause <= 64'd11;
				csr_mtval  <= 64'd0;
				
				// Update mstatus: MPIE := MIE, MIE := 0, MPP := prev mode
				csr_mstatus[7] <= csr_mstatus[3];
				csr_mstatus[3] <= 1'b0;
				csr_mstatus[12:11] <= privilege_mode_i;
				
				privilege_mode <= 2'd3;
			end else if (wb_mret) begin
				// Update mstatus: MIE := MPIE, MPIE := 1, MPP := 0
				csr_mstatus[3] <= csr_mstatus[7];
				csr_mstatus[7] <= 1'b1;
				csr_mstatus[12:11] <= 2'b00;
				
				privilege_mode <= csr_mstatus[12:11];
			end else if (wb_r.valid && wb_r.csr_wen) begin
				// CSR write
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

	// Compute "next" values for diffs combinationally
	// This ensures Difftest sees the CSR state that becomes visible this cycle

	always_comb begin
		// Default: current values
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

		// Traps override
		if (mmu_trap) begin
			next_mepc = trap_vaddr;
			// Determine mcause based on fault type
			if (fault_is_insn)
				next_mcause = 64'd12;  // Instruction page fault
			else if (wb_r.is_store)
				next_mcause = 64'd15;  // Store/AMO page fault
			else
				next_mcause = 64'd13;  // Load page fault
			next_mtval = trap_vaddr;
			
			next_mstatus = csr_mstatus;
			next_mstatus[7] = csr_mstatus[3];
			next_mstatus[3] = 1'b0;
			next_mstatus[12:11] = privilege_mode_i;
			
			next_privilege_mode = 2'd3;
		end else if (wb_ecall) begin
			next_mepc = wb_r.pc;
			next_mcause = 64'd11;
			next_mtval = 64'd0;
			
			next_mstatus = csr_mstatus;
			next_mstatus[7] = csr_mstatus[3];
			next_mstatus[3] = 1'b0;
			next_mstatus[12:11] = privilege_mode_i;
			
			next_privilege_mode = 2'd3;
		end else if (wb_mret) begin
			next_mstatus = csr_mstatus;
			next_mstatus[3] = csr_mstatus[7];
			next_mstatus[7] = 1'b1;
			next_mstatus[12:11] = 2'b00;
			
			next_privilege_mode = csr_mstatus[12:11];
		end else if (wb_r.valid && wb_r.csr_wen) begin
			// CSR write overrides specific fields
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

	// Drive diff outputs from next-state values
	assign csr_mstatus_diff  = next_mstatus;
	assign csr_mtvec_diff    = next_mtvec;
	assign csr_mip_raw_diff  = next_mip_raw;
	assign csr_mie_diff      = next_mie;
	assign csr_mscratch_diff = next_mscratch;
	assign csr_mcause_diff   = next_mcause;
	assign csr_mtval_diff    = next_mtval;
	assign csr_mepc_diff     = next_mepc;
	assign csr_satp_diff     = next_satp;
	// privilege_mode_diff should reflect CURRENT mode, not the mode after trap handling
	assign privilege_mode_diff = privilege_mode;
endmodule

`endif
