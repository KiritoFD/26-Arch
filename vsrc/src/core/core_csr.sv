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
	input  logic         wb_sret,
	input  logic         wb_illegal,
	input  logic         wb_ebreak,
	input  logic         wb_sfence,      // SFENCE.VMA: flush TLB
	input  logic         wb_misalign_data,
	input  logic         wb_misalign_instr,
	input  logic         mmu_trap,
	input  logic [63:0]  trap_vaddr,
	input  logic         fault_is_insn,
	input  logic [63:0]  fault_cause,
	input  logic [63:0]  fault_pc,
	input  logic [1:0]   privilege_mode_i,
	input  logic         intr_eval,  // evaluate interrupts this cycle
	input  logic [63:0]  intr_fetch_pc,  // current fetch PC for interrupt mepc
	output logic [1:0]   privilege_mode,
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
	output logic [1:0]   privilege_mode_diff,
	output logic         trap_redirect,  // pipeline should redirect to mtvec
	output logic         mret_redirect,  // pipeline should redirect to mepc
	output logic [63:0]  trap_redirect_pc  // target PC for redirect
);
	logic [63:0] csr_mip_raw;
	logic [63:0] csr_mip_raw_diff;
	logic [63:0] csr_stvec_r;
	logic [63:0] csr_sscratch_r;
	logic [63:0] csr_sepc_r;
	logic [63:0] csr_scause_r;
	logic [63:0] csr_stval_r;
	logic [63:0] csr_medeleg_r;
	logic [63:0] csr_mideleg_r;
	logic [63:0] csr_mcounteren_r;
	logic [63:0] csr_menvcfg_r;
	logic [63:0] csr_pmpcfg0_r;
	logic [63:0] csr_pmpaddr0_r;

	// Interrupt evaluation
	logic intr_pending;
	logic [63:0] intr_cause;
	logic intr_meip, intr_msip, intr_mtip;
	logic intr_seip, intr_ssip, intr_stip;
	logic [63:0] intr_mstatus;
	logic [63:0] intr_mie;
	logic [63:0] intr_sie;
	logic sync_trap_or_mret;

	assign intr_mstatus =
		(wb_r.valid && wb_r.csr_wen && (wb_r.csr_addr == CSR_MSTATUS)) ? wb_r.csr_wdata :
		(wb_r.valid && wb_r.csr_wen && (wb_r.csr_addr == CSR_SSTATUS)) ? ((csr_mstatus & ~SSTATUS_MASK) | (wb_r.csr_wdata & SSTATUS_MASK)) :
		csr_mstatus;
	assign intr_mie     = (wb_r.valid && wb_r.csr_wen && (wb_r.csr_addr == CSR_MIE))     ? wb_r.csr_wdata : csr_mie;
	assign intr_sie     = (wb_r.valid && wb_r.csr_wen && (wb_r.csr_addr == CSR_SIE))     ?
	                     ((csr_mie & ~SIE_MASK) | (wb_r.csr_wdata & SIE_MASK)) : csr_sie;

	assign intr_meip = (privilege_mode_i != 2'd3 || intr_mstatus[3]) &&
	                   !csr_mideleg_r[11] && csr_mip[11] && intr_mie[11];
	assign intr_msip = (privilege_mode_i != 2'd3 || intr_mstatus[3]) &&
	                   !csr_mideleg_r[3]  && csr_mip[3]  && intr_mie[3];
	assign intr_mtip = (privilege_mode_i != 2'd3 || intr_mstatus[3]) &&
	                   !csr_mideleg_r[7]  && csr_mip[7]  && intr_mie[7];
	assign intr_seip = ((privilege_mode_i == 2'd1 && intr_mstatus[1]) || privilege_mode_i == 2'd0) &&
	                   csr_mideleg_r[11] && csr_sip[11] && intr_sie[11];
	assign intr_ssip = ((privilege_mode_i == 2'd1 && intr_mstatus[1]) || privilege_mode_i == 2'd0) &&
	                   csr_mideleg_r[3] && csr_sip[3] && intr_sie[3];
	assign intr_stip = ((privilege_mode_i == 2'd1 && intr_mstatus[1]) || privilege_mode_i == 2'd0) &&
	                   csr_mideleg_r[7] && csr_sip[7] && intr_sie[7];

	assign intr_pending = intr_seip || intr_ssip || intr_stip || intr_meip || intr_msip || intr_mtip;
	assign intr_cause = intr_seip ? {1'b1, 63'd9} :
	                    intr_ssip ? {1'b1, 63'd1} :
	                    intr_stip ? {1'b1, 63'd5} :
	                    intr_meip ? {1'b1, 63'd11} :  // MEIP  (11)
	                    intr_msip ? {1'b1, 63'd3}  :  // MSIP  (3)
	                    {1'b1, 63'd7};                  // MTIP  (7)
	assign sync_trap_or_mret = wb_ecall || wb_illegal || wb_ebreak || wb_misalign_instr ||
	                           wb_misalign_data || mmu_trap || wb_mret || wb_sret || wb_sfence;

	assign csr_mhartid = 64'd0;
	assign csr_sstatus = csr_mstatus & SSTATUS_MASK;
	assign csr_mip = (csr_mip_raw & ~64'h0000_0000_0000_0888) |
	                 ({63'd0, exint} << 11) |
	                 ({63'd0, trint} << 7) |
	                 ({63'd0, swint} << 3);
	assign csr_sip = csr_mip & SIP_MASK;
	assign csr_mip_diff = (csr_mip_raw_diff & ~64'h0000_0000_0000_0888) |
	                      ({63'd0, exint} << 11) |
	                      ({63'd0, trint} << 7) |
	                      ({63'd0, swint} << 3);
	assign csr_stvec = csr_stvec_r;
	assign csr_sie = csr_mie & SIE_MASK;
	assign csr_sscratch = csr_sscratch_r;
	assign csr_scause = csr_scause_r;
	assign csr_stval = csr_stval_r;
	assign csr_sepc = csr_sepc_r;
	assign csr_medeleg = csr_medeleg_r;
	assign csr_mideleg = csr_mideleg_r;
	assign csr_mcounteren = csr_mcounteren_r;
	assign csr_menvcfg = csr_menvcfg_r;
	assign csr_pmpcfg0 = csr_pmpcfg0_r;
	assign csr_pmpaddr0 = csr_pmpaddr0_r;

	// Trap cause selection for exceptions (interrupts handled separately)
	function automatic logic [63:0] get_ecall_cause(input logic [1:0] mode);
		unique case (mode)
			2'd0: get_ecall_cause = 64'd8;   // ECALL from U-mode
			2'd1: get_ecall_cause = 64'd9;   // ECALL from S-mode
			2'd3: get_ecall_cause = 64'd11;  // ECALL from M-mode
			default: get_ecall_cause = 64'd11;
		endcase
	endfunction

	function automatic logic [63:0] get_excp_cause();
		if (mmu_trap) begin
			return fault_cause;
		end else if (wb_ecall) begin
			return get_ecall_cause(privilege_mode_i);
		end else if (wb_ebreak) begin
			return 64'd3;
		end else if (wb_illegal) begin
			return 64'd2;
		end else if (wb_misalign_instr) begin
			return 64'd0;
		end else if (wb_misalign_data) begin
			if (wb_r.is_store) return 64'd6;
			else return 64'd4;
		end
		return 64'd0;
	endfunction

	function automatic logic delegate_to_s(input logic is_interrupt, input logic [63:0] cause);
		begin
			if (privilege_mode_i == 2'd3) begin
				delegate_to_s = 1'b0;
			end else if (is_interrupt) begin
				delegate_to_s = csr_mideleg_r[cause[5:0]];
			end else begin
				delegate_to_s = csr_medeleg_r[cause[5:0]];
			end
		end
	endfunction

	// Compute "next" values for diffs combinationally
	logic [63:0] next_mstatus, next_mepc, next_mcause, next_mtval, next_mtvec;
	logic [63:0] next_mip_raw, next_mie, next_mscratch, next_satp;
	logic [63:0] next_stvec, next_sscratch, next_sepc, next_scause, next_stval;
	logic [63:0] next_medeleg, next_mideleg, next_mcounteren, next_menvcfg;
	logic [63:0] next_pmpcfg0, next_pmpaddr0;
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
			csr_stvec_r     <= 64'd0;
			csr_sscratch_r  <= 64'd0;
			csr_sepc_r      <= 64'd0;
			csr_scause_r    <= 64'd0;
			csr_stval_r     <= 64'd0;
			csr_medeleg_r   <= 64'd0;
			csr_mideleg_r   <= 64'd0;
			csr_mcounteren_r<= 64'd0;
			csr_menvcfg_r   <= 64'd0;
			csr_pmpcfg0_r   <= 64'd0;
			csr_pmpaddr0_r  <= 64'd0;
			privilege_mode <= 2'd3;
		end else begin
			if (intr_eval && intr_pending && !sync_trap_or_mret) begin
				if (delegate_to_s(1'b1, intr_cause[63:0])) begin
					csr_sepc_r   <= intr_fetch_pc;
					csr_scause_r <= intr_cause;
					csr_stval_r  <= 64'd0;
					csr_mstatus[5] <= csr_mstatus[1];
					csr_mstatus[1] <= 1'b0;
					csr_mstatus[8] <= privilege_mode_i[0];
					privilege_mode <= 2'd1;
				end else begin
					csr_mepc   <= intr_fetch_pc;
					csr_mcause <= intr_cause;
					csr_mtval  <= 64'd0;
					csr_mstatus[7] <= intr_mstatus[3];
					csr_mstatus[3] <= 1'b0;
					csr_mstatus[12:11] <= privilege_mode_i;
					privilege_mode <= 2'd3;
				end
			end else if (wb_ecall) begin
				if (delegate_to_s(1'b0, get_ecall_cause(privilege_mode_i))) begin
					csr_sepc_r   <= wb_r.pc;
					csr_scause_r <= get_ecall_cause(privilege_mode_i);
					csr_stval_r  <= 64'd0;
					csr_mstatus[5] <= csr_mstatus[1];
					csr_mstatus[1] <= 1'b0;
					csr_mstatus[8] <= privilege_mode_i[0];
					privilege_mode <= 2'd1;
				end else begin
					csr_mepc   <= wb_r.pc;
					csr_mcause <= get_ecall_cause(privilege_mode_i);
					csr_mtval  <= 64'd0;
					csr_mstatus[7] <= csr_mstatus[3];
					csr_mstatus[3] <= 1'b0;
					csr_mstatus[12:11] <= privilege_mode_i;
					privilege_mode <= 2'd3;
				end
			end else if (mmu_trap) begin
				if (delegate_to_s(1'b0, get_excp_cause())) begin
					csr_sepc_r   <= fault_is_insn ? trap_vaddr : fault_pc;
					csr_scause_r <= fault_cause;
					csr_stval_r  <= trap_vaddr;
					csr_mstatus[5] <= csr_mstatus[1];
					csr_mstatus[1] <= 1'b0;
					csr_mstatus[8] <= privilege_mode_i[0];
					privilege_mode <= 2'd1;
				end else begin
					csr_mepc   <= fault_is_insn ? trap_vaddr : fault_pc;
					csr_mcause <= fault_cause;
					csr_mtval  <= trap_vaddr;
					csr_mstatus[7] <= csr_mstatus[3];
					csr_mstatus[3] <= 1'b0;
					csr_mstatus[12:11] <= privilege_mode_i;
					privilege_mode <= 2'd3;
				end
			end else if (wb_illegal) begin
				if (delegate_to_s(1'b0, 64'd2)) begin
					csr_sepc_r   <= wb_r.pc;
					csr_scause_r <= 64'd2;
					csr_stval_r  <= {32'd0, wb_r.instr};
					csr_mstatus[5] <= csr_mstatus[1];
					csr_mstatus[1] <= 1'b0;
					csr_mstatus[8] <= privilege_mode_i[0];
					privilege_mode <= 2'd1;
				end else begin
					csr_mepc   <= wb_r.pc;
					csr_mcause <= 64'd2;
					csr_mtval  <= {32'd0, wb_r.instr};
					csr_mstatus[7] <= csr_mstatus[3];
					csr_mstatus[3] <= 1'b0;
					csr_mstatus[12:11] <= privilege_mode_i;
					privilege_mode <= 2'd3;
				end
			end else if (wb_ebreak) begin
				if (delegate_to_s(1'b0, 64'd3)) begin
					csr_sepc_r   <= wb_r.pc;
					csr_scause_r <= 64'd3;
					csr_stval_r  <= 64'd0;
					csr_mstatus[5] <= csr_mstatus[1];
					csr_mstatus[1] <= 1'b0;
					csr_mstatus[8] <= privilege_mode_i[0];
					privilege_mode <= 2'd1;
				end else begin
					csr_mepc   <= wb_r.pc;
					csr_mcause <= 64'd3;
					csr_mtval  <= 64'd0;
					csr_mstatus[7] <= csr_mstatus[3];
					csr_mstatus[3] <= 1'b0;
					csr_mstatus[12:11] <= privilege_mode_i;
					privilege_mode <= 2'd3;
				end
			end else if (wb_misalign_instr) begin
				if (delegate_to_s(1'b0, 64'd0)) begin
					csr_sepc_r   <= wb_r.pc;
					csr_scause_r <= 64'd0;
					csr_stval_r  <= wb_r.result;
					csr_mstatus[5] <= csr_mstatus[1];
					csr_mstatus[1] <= 1'b0;
					csr_mstatus[8] <= privilege_mode_i[0];
					privilege_mode <= 2'd1;
				end else begin
					csr_mepc   <= wb_r.pc;
					csr_mcause <= 64'd0;
					csr_mtval  <= wb_r.result;
					csr_mstatus[7] <= csr_mstatus[3];
					csr_mstatus[3] <= 1'b0;
					csr_mstatus[12:11] <= privilege_mode_i;
					privilege_mode <= 2'd3;
				end
			end else if (wb_misalign_data) begin
				if (delegate_to_s(1'b0, wb_r.is_store ? 64'd6 : 64'd4)) begin
					csr_sepc_r   <= wb_r.pc;
					csr_scause_r <= wb_r.is_store ? 64'd6 : 64'd4;
					csr_stval_r  <= wb_r.mem_addr;
					csr_mstatus[5] <= csr_mstatus[1];
					csr_mstatus[1] <= 1'b0;
					csr_mstatus[8] <= privilege_mode_i[0];
					privilege_mode <= 2'd1;
				end else begin
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
				end
			end else if (wb_mret) begin
				csr_mstatus[3] <= csr_mstatus[7];
				csr_mstatus[7] <= 1'b1;
				csr_mstatus[12:11] <= 2'b00;
				privilege_mode <= csr_mstatus[12:11];
			end else if (wb_sret) begin
				csr_mstatus[1] <= csr_mstatus[5];
				csr_mstatus[5] <= 1'b1;
				csr_mstatus[8] <= 1'b0;
				privilege_mode <= {1'b0, csr_mstatus[8]};
			end else if (wb_r.valid && wb_r.csr_wen) begin
				unique case (wb_r.csr_addr)
					CSR_MSTATUS:  csr_mstatus  <= wb_r.csr_wdata;
					CSR_SSTATUS:  csr_mstatus  <= (csr_mstatus & ~SSTATUS_MASK) | (wb_r.csr_wdata & SSTATUS_MASK);
					CSR_MTVEC:    csr_mtvec    <= wb_r.csr_wdata;
					CSR_STVEC:    csr_stvec_r  <= wb_r.csr_wdata;
					CSR_MIP:      csr_mip_raw  <= wb_r.csr_wdata;
					CSR_SIP:      csr_mip_raw  <= (csr_mip_raw & ~SIP_MASK) | (wb_r.csr_wdata & SIP_MASK);
					CSR_MIE:      csr_mie      <= wb_r.csr_wdata;
					CSR_SIE:      csr_mie      <= (csr_mie & ~SIE_MASK) | (wb_r.csr_wdata & SIE_MASK);
					CSR_MSCRATCH: csr_mscratch <= wb_r.csr_wdata;
					CSR_SSCRATCH: csr_sscratch_r <= wb_r.csr_wdata;
					CSR_MCAUSE:   csr_mcause   <= wb_r.csr_wdata;
					CSR_SCAUSE:   csr_scause_r <= wb_r.csr_wdata;
					CSR_MTVAL:    csr_mtval    <= wb_r.csr_wdata;
					CSR_STVAL:    csr_stval_r  <= wb_r.csr_wdata;
					CSR_MEPC:     csr_mepc     <= wb_r.csr_wdata;
					CSR_SEPC:     csr_sepc_r   <= wb_r.csr_wdata;
					CSR_SATP:     csr_satp     <= wb_r.csr_wdata;
					CSR_MEDELEG:  csr_medeleg_r <= wb_r.csr_wdata;
					CSR_MIDELEG:  csr_mideleg_r <= wb_r.csr_wdata;
					CSR_MCOUNTEREN: csr_mcounteren_r <= wb_r.csr_wdata;
					CSR_MENVCFG:  csr_menvcfg_r <= wb_r.csr_wdata;
					CSR_PMPCFG0:  csr_pmpcfg0_r <= wb_r.csr_wdata & 64'hff;
					CSR_PMPADDR0: csr_pmpaddr0_r <= wb_r.csr_wdata;
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
		next_stvec     = csr_stvec_r;
		next_sscratch  = csr_sscratch_r;
		next_sepc      = csr_sepc_r;
		next_scause    = csr_scause_r;
		next_stval     = csr_stval_r;
		next_medeleg   = csr_medeleg_r;
		next_mideleg   = csr_mideleg_r;
		next_mcounteren= csr_mcounteren_r;
		next_menvcfg   = csr_menvcfg_r;
		next_pmpcfg0   = csr_pmpcfg0_r;
		next_pmpaddr0  = csr_pmpaddr0_r;
		next_privilege_mode = privilege_mode;

		trap_redirect = 1'b0;
		mret_redirect = 1'b0;
		trap_redirect_pc = 64'd0;

		// Debug: log all traps and redirects

		if (intr_eval && intr_pending && !sync_trap_or_mret) begin
			if (delegate_to_s(1'b1, intr_cause)) begin
				next_sepc = intr_fetch_pc;
				next_scause = intr_cause;
				next_stval = 64'd0;
				next_mstatus = csr_mstatus;
				next_mstatus[5] = csr_mstatus[1];
				next_mstatus[1] = 1'b0;
				next_mstatus[8] = privilege_mode_i[0];
				next_privilege_mode = 2'd1;
				trap_redirect = 1'b1;
				trap_redirect_pc = csr_stvec_r;
			end else begin
				next_mepc = intr_fetch_pc;
				next_mcause = intr_cause;
				next_mtval = 64'd0;
				next_mstatus = intr_mstatus;
				next_mstatus[7] = intr_mstatus[3];
				next_mstatus[3] = 1'b0;
				next_mstatus[12:11] = privilege_mode_i;
				next_privilege_mode = 2'd3;
				trap_redirect = 1'b1;
				trap_redirect_pc = csr_mtvec;
			end
	end else if (wb_ecall || wb_illegal || wb_ebreak || wb_misalign_instr || wb_misalign_data) begin
		if (delegate_to_s(1'b0, get_excp_cause())) begin
				next_sepc = wb_r.pc;
				next_scause = get_excp_cause();
				next_stval = wb_illegal ? {32'd0, wb_r.instr} :
				             (wb_misalign_instr ? wb_r.result : (wb_misalign_data ? wb_r.mem_addr : 64'd0));
				next_mstatus = csr_mstatus;
				next_mstatus[5] = csr_mstatus[1];
				next_mstatus[1] = 1'b0;
				next_mstatus[8] = privilege_mode_i[0];
				next_privilege_mode = 2'd1;
				trap_redirect = 1'b1;
				trap_redirect_pc = csr_stvec_r;
			end else begin
				next_mepc = wb_r.pc;
				next_mcause = get_excp_cause();
				next_mtval = wb_illegal ? {32'd0, wb_r.instr} :
				             (wb_misalign_instr ? wb_r.result : (wb_misalign_data ? wb_r.mem_addr : 64'd0));
				next_mstatus = csr_mstatus;
				next_mstatus[7] = csr_mstatus[3];
				next_mstatus[3] = 1'b0;
				next_mstatus[12:11] = privilege_mode_i;
				next_privilege_mode = 2'd3;
				trap_redirect = 1'b1;
				trap_redirect_pc = csr_mtvec;
			end
		end else if (mmu_trap) begin
			if (delegate_to_s(1'b0, get_excp_cause())) begin
				next_sepc = fault_is_insn ? trap_vaddr : fault_pc;
				next_scause = get_excp_cause();
				next_stval = trap_vaddr;
				next_mstatus = csr_mstatus;
				next_mstatus[5] = csr_mstatus[1];
				next_mstatus[1] = 1'b0;
				next_mstatus[8] = privilege_mode_i[0];
				next_privilege_mode = 2'd1;
				trap_redirect = 1'b1;
				trap_redirect_pc = csr_stvec_r;
			end else begin
				next_mepc = fault_is_insn ? trap_vaddr : fault_pc;
				next_mcause = get_excp_cause();
				next_mtval = trap_vaddr;
				next_mstatus = csr_mstatus;
				next_mstatus[7] = csr_mstatus[3];
				next_mstatus[3] = 1'b0;
				next_mstatus[12:11] = privilege_mode_i;
				next_privilege_mode = 2'd3;
				trap_redirect = 1'b1;
				trap_redirect_pc = csr_mtvec;
			end
	end else if (wb_mret) begin
		next_mstatus = csr_mstatus;
		next_mstatus[3] = csr_mstatus[7];
		next_mstatus[7] = 1'b1;
		next_mstatus[12:11] = 2'b00;
		next_privilege_mode = csr_mstatus[12:11];
		mret_redirect = 1'b1;
		trap_redirect_pc = csr_mepc;
	end else if (wb_sret) begin
		next_mstatus = csr_mstatus;
		next_mstatus[1] = csr_mstatus[5];
		next_mstatus[5] = 1'b1;
		next_mstatus[8] = 1'b0;
		next_privilege_mode = {1'b0, csr_mstatus[8]};
		mret_redirect = 1'b1;
		trap_redirect_pc = csr_sepc_r;
	end else if (wb_sfence) begin
			// SFENCE.VMA: redirect to PC+4, flush MMU (handled by flush_mmu_o in core.sv)
			mret_redirect = 1'b1;
			trap_redirect_pc = wb_r.pc + 64'd4;
		end else if (wb_r.valid && wb_r.csr_wen) begin
			unique case (wb_r.csr_addr)
				CSR_MSTATUS:  next_mstatus  = wb_r.csr_wdata;
				CSR_SSTATUS:  next_mstatus  = (csr_mstatus & ~SSTATUS_MASK) | (wb_r.csr_wdata & SSTATUS_MASK);
				CSR_MTVEC:    next_mtvec    = wb_r.csr_wdata;
				CSR_STVEC:    next_stvec    = wb_r.csr_wdata;
				CSR_MIP:      next_mip_raw  = wb_r.csr_wdata;
				CSR_SIP:      next_mip_raw  = (csr_mip_raw & ~SIP_MASK) | (wb_r.csr_wdata & SIP_MASK);
				CSR_MIE:      next_mie      = wb_r.csr_wdata;
				CSR_SIE:      next_mie      = (csr_mie & ~SIE_MASK) | (wb_r.csr_wdata & SIE_MASK);
				CSR_MSCRATCH: next_mscratch = wb_r.csr_wdata;
				CSR_SSCRATCH: next_sscratch = wb_r.csr_wdata;
				CSR_MCAUSE:   next_mcause   = wb_r.csr_wdata;
				CSR_SCAUSE:   next_scause   = wb_r.csr_wdata;
				CSR_MTVAL:    next_mtval    = wb_r.csr_wdata;
				CSR_STVAL:    next_stval    = wb_r.csr_wdata;
				CSR_MEPC:     next_mepc     = wb_r.csr_wdata;
				CSR_SATP:     next_satp     = wb_r.csr_wdata;
				CSR_MEDELEG:  next_medeleg  = wb_r.csr_wdata;
				CSR_MIDELEG:  next_mideleg  = wb_r.csr_wdata;
				CSR_MCOUNTEREN: next_mcounteren = wb_r.csr_wdata;
				CSR_MENVCFG:  next_menvcfg  = wb_r.csr_wdata;
				CSR_PMPCFG0:  next_pmpcfg0  = wb_r.csr_wdata & 64'hff;
				CSR_PMPADDR0: next_pmpaddr0 = wb_r.csr_wdata;
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
	assign csr_medeleg_diff  = next_medeleg;
	assign csr_mideleg_diff  = next_mideleg;
	assign csr_stvec_diff    = next_stvec;
	assign csr_sscratch_diff = next_sscratch;
	assign csr_scause_diff   = next_scause;
	assign csr_stval_diff    = next_stval;
	assign csr_sepc_diff     = next_sepc;
	assign privilege_mode_diff = next_privilege_mode;
endmodule

`endif
