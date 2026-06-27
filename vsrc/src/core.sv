`ifndef __CORE_SV
`define __CORE_SV

`ifdef VERILATOR
`include "include/common.sv"
`endif

`ifdef VERILATOR
`include "src/core/core_pkg.sv"
`include "src/core/core_decode.sv"
`include "src/core/core_execute.sv"
`include "src/core/core_mdu.sv"
`include "src/core/core_csr.sv"
`include "src/core/core_commit.sv"
`endif

module core
	import common::*;
	import core_pkg::*;
(
	input  logic       clk, reset,
	output ibus_req_t  ireq,
	input  ibus_resp_t iresp,
	output dbus_req_t  dreq,
	input  dbus_resp_t dresp,
	input  logic       trint, swint, exint,
	output logic [63:0]  csr_satp_o,
	output logic [63:0]  csr_pmpcfg0_o,
	output logic [63:0]  csr_pmpaddr0_o,
	output logic [1:0]   privilege_mode_o,
	output logic         mstatus_sum_o,    // SUM bit for MMU
	output logic         flush_mmu_o,
	input  logic         walk_fault,
	input  logic [63:0]  fault_vaddr,
	input  logic         fault_is_insn,
	input  logic [63:0]  fault_cause
);
	// The top level keeps only long-lived pipeline state and control flow.
	// Decode / execute / MDU details live in dedicated source files now.
	id_reg_t      id_r;
	ex_reg_t      ex_r;
	wb_like_reg_t mem_r;
	wb_like_reg_t wb_r;

	logic [63:0] gpr [31:0];
	logic [63:0] gpr_diff [31:0];

	logic [63:0] fetch_pc;
	logic        fetch_fire;
	logic        fetch_pending;
	logic [63:0] fetch_req_pc;
	logic        fetch_buf_valid;
	logic [63:0] fetch_buf_pc;
	logic [31:0] fetch_buf_instr;
	logic        fetch_issue_fire;
	logic        fetch_req_new_fire;
	logic        fetch_resp_fire;
	logic        fetch_pop_buf;
	logic        fetch_resp_to_id;
	logic        fetch_resp_to_buf;
	logic        fetch_can_consume;
	logic [63:0] fetch_req_addr;
	logic        fetch_redirect_pending;
	logic [63:0] fetch_redirect_pc;
	logic [1:0]  fetch_redirect_bubble;
	logic        fetch_drop_resp_pending;

	logic [4:0]  id_rs1;
	logic [4:0]  id_rs2;
	logic        id_use_rs1;
	logic        id_use_rs2;
	logic        id_dec_valid;
	logic        id_dec_trap;
	logic        id_dec_wen;
	logic        id_dec_is_word;
	logic [3:0]  id_dec_alu_cmd;
	logic [63:0] id_dec_op1;
	logic [63:0] id_dec_op2;
	logic [63:0] id_dec_imm;
	logic [63:0] id_dec_rs2_store;
	logic [4:0]  id_dec_rd;
	logic        id_dec_is_load;
	logic        id_dec_is_store;
	logic [2:0]  id_dec_mem_size;
	logic        id_dec_mem_unsigned;
	logic        id_dec_is_branch;
	logic [2:0]  id_dec_br_funct3;
	logic        id_dec_is_jal;
	logic        id_dec_is_jalr;
	logic        id_dec_wb_pc4;
	logic        id_dec_csr_wen;
	logic [11:0] id_dec_csr_addr;
	logic [63:0] id_dec_csr_wdata;
	logic        id_dec_is_ecall;
	logic        id_dec_is_mret;
	logic        id_dec_is_sret;
	logic        id_dec_is_amo;
	logic [4:0]  id_dec_amo_cmd;
	logic        id_dec_is_illegal;
	logic        id_dec_is_ebreak;
	logic        id_dec_is_sfence;
	logic        ex_misalign;
	logic        ex_instr_misalign;
	logic        front_trap_pending;

	logic [63:0] csr_mstatus;
	logic [63:0] csr_sstatus;
	logic [63:0] csr_mtvec;
	logic [63:0] csr_stvec;
	logic [63:0] csr_mip;
	logic [63:0] csr_sip;
	logic [63:0] csr_mie;
	logic [63:0] csr_sie;
	logic [63:0] csr_mscratch;
	logic [63:0] csr_sscratch;
	logic [63:0] csr_mcause;
	logic [63:0] csr_scause;
	logic [63:0] csr_mtval;
	logic [63:0] csr_stval;
	logic [63:0] csr_mepc;
	logic [63:0] csr_sepc;
	logic [63:0] csr_mhartid;
	logic [63:0] csr_satp;
	logic [63:0] csr_medeleg;
	logic [63:0] csr_mideleg;
	logic [63:0] csr_mcounteren;
	logic [63:0] csr_menvcfg;
	logic [63:0] csr_pmpcfg0;
	logic [63:0] csr_pmpaddr0;
	logic [63:0] csr_mstatus_diff;
	logic [63:0] csr_mtvec_diff;
	logic [63:0] csr_mip_diff;
	logic [63:0] csr_mie_diff;
	logic [63:0] csr_mscratch_diff;
	logic [63:0] csr_mcause_diff;
	logic [63:0] csr_mtval_diff;
	logic [63:0] csr_mepc_diff;
	logic [63:0] csr_satp_diff;
	logic [63:0] csr_medeleg_diff;
	logic [63:0] csr_mideleg_diff;
	logic [63:0] csr_stvec_diff;
	logic [63:0] csr_sscratch_diff;
	logic [63:0] csr_scause_diff;
	logic [63:0] csr_stval_diff;
	logic [63:0] csr_sepc_diff;
	logic [1:0]  privilege_mode;
	logic [1:0]  privilege_mode_diff;

	logic        halted;
	logic        trap_commit;
	logic        trap_valid_latched;
	logic [2:0]  trap_code_latched;
	logic [63:0] trap_pc_latched;
	logic [63:0] trap_cycle_latched;
	logic [63:0] trap_instr_latched;
	logic [63:0] cycle_cnt;
	logic [63:0] instr_cnt;

	logic        mmu_trap;
	logic [63:0] trap_vaddr;
	logic [63:0] fault_pc;
	logic        trap_redirect;
	logic        mret_redirect;
	logic [63:0] trap_redirect_pc;
	logic [63:0] intr_fetch_pc;

	logic        ex_is_mdu;
	logic        mdu_req;
	logic        ex_to_mem_blocks_front;
	logic        ex_result_ready;
	logic        ex_forwardable;
	logic        stall_ex_busy;
	logic        stall_mem_busy;
	logic        stall_if_mem;
	logic        raw_hazard_ex;
	logic        raw_hazard_mem;
	logic        stall_pipe;
	logic        stall_front;
	logic        mem_result_ready;
	logic        mem_access_done;
	logic [63:0] mem_stage_result;
	logic [63:0] ex_result;
	logic [63:0] ex_mem_addr;
	logic        ex_flush_front;
	logic [63:0] ex_redirect_pc;
	logic        difftest_skip;
	logic [63:0] mem_store_data_shifted;
	logic [7:0]  mem_store_strobe;
	logic        mdu_out_valid;
	logic [63:0] mdu_out_result;
	logic        mdu_core_out_valid;
	logic [63:0] mdu_core_out_result;
	logic [63:0] amo_result;
	// ===== Hardware AMO state machine (replaces DPI-C AMOHelper, T014) =====
	logic [2:0]  amo_state;
	logic [63:0] amo_addr_q;        // latched AMO address
	logic [63:0] amo_wdata_q;       // latched rs2 (original, unshifted)
	logic [4:0]  amo_cmd_q;         // latched AMO command
	logic [63:0] amo_old_data_q;    // loaded old value
	logic        amo_dreq_valid;    // AMO-driven dreq.valid
	logic [63:0] amo_dreq_addr;
	logic [7:0]  amo_dreq_strobe;
	logic [63:0] amo_dreq_data;
	logic        amo_busy;
	logic        amo_issue;
	logic        amo_issued_q;
	logic        amo_done_q;
	// ===== LR/SC Reservation Set (T015) — 2 entries =====
	logic [63:0] rs_addr  [0:1];
	logic        rs_valid [0:1];
	logic        rs_hit;          // SC: address matches a reservation
	logic        rs_slot;         // which slot LR will use
	assign mdu_req = is_mdu_cmd(ex_r.alu_cmd);
	assign ex_is_mdu = mdu_req || ex_r.is_amo;
	assign ex_to_mem_blocks_front = ex_r.valid && (ex_r.is_load || ex_r.is_store);
	assign amo_issue = ex_r.valid && ex_r.is_amo && (amo_state == AMO_ST_IDLE) && !amo_done_q &&
	                   !mem_r.valid;   // ensure MEM stage has no in-flight access
	assign amo_busy  = ex_r.valid && ex_r.is_amo && ((amo_state != AMO_ST_IDLE) || amo_done_q);
	// Compute AMO result from loaded old data + rs2 (word-aligned, sign-extended)
	// amo_wdata_q is the unshifted rs2; old data in amo_old_data_q is already
	// aligned by dresp.data with size=MSIZE4 (read returns aligned word at [31:0]
	// by cbus/bram_wrapper since strobe is byte-enable).
	// Word at byte position: extract word from old 64-bit data
	wire [31:0] amo_old_word = amo_old_data_q[31 + {amo_addr_q[2:0], 3'b0} -: 32];
	wire [31:0] amo_rs2_word  = amo_wdata_q[31:0];
	reg  [31:0] amo_new_word;
	always_comb begin
		unique case (amo_cmd_q)
			AMO_CMD_SWAP: amo_new_word = amo_rs2_word;
			AMO_CMD_ADD:  amo_new_word = amo_old_word + amo_rs2_word;
			AMO_CMD_XOR:  amo_new_word = amo_old_word ^ amo_rs2_word;
			AMO_CMD_AND:  amo_new_word = amo_old_word & amo_rs2_word;
			AMO_CMD_OR:   amo_new_word = amo_old_word | amo_rs2_word;
			AMO_CMD_MIN:  amo_new_word = ($signed(amo_old_word) < $signed(amo_rs2_word)) ? amo_old_word : amo_rs2_word;
			AMO_CMD_MAX:  amo_new_word = ($signed(amo_old_word) > $signed(amo_rs2_word)) ? amo_old_word : amo_rs2_word;
			AMO_CMD_MINU: amo_new_word = (amo_old_word < amo_rs2_word) ? amo_old_word : amo_rs2_word;
			AMO_CMD_MAXU: amo_new_word = (amo_old_word > amo_rs2_word) ? amo_old_word : amo_rs2_word;
			default:      amo_new_word = amo_rs2_word;
		endcase
	end
	// Build full 64-bit store data: keep untouched bytes, replace target word
	wire [2:0] amo_word_off = amo_addr_q[2:0];
	reg  [63:0] amo_store_data;
	always_comb begin
		amo_store_data = amo_old_data_q;
		case (amo_word_off)
			3'd0: amo_store_data[31:0]  = amo_new_word;
			3'd4: amo_store_data[63:32] = amo_new_word;
			default: amo_store_data[31:0] = amo_new_word;
		endcase
	end
	wire [7:0] amo_store_strobe = 8'h0f << amo_word_off;
	// rd value to commit:
	//   LR.W  -> zero-extended loaded word
	//   SC.W  -> 0 (success) or 1 (failure)
	//   AMO.* -> zero-extended old word
	// SC failure is detected during state machine; latch a flag.
	logic amo_sc_fail_q;
	wire [31:0] amo_rd_word = (amo_cmd_q == AMO_CMD_SC) ? (amo_sc_fail_q ? 32'd1 : 32'd0) :
	                          (amo_cmd_q == AMO_CMD_LR) ? amo_old_word[31:0] :
	                          amo_old_word[31:0];
	// Reservation Set: pick an empty slot for LR
	assign rs_slot = !rs_valid[0] ? 1'b0 : 1'b1;
	assign rs_hit  = (rs_valid[0] && rs_addr[0] == amo_addr_q) ||
	                  (rs_valid[1] && rs_addr[1] == amo_addr_q);
	// Result driven back to pipeline
	assign amo_result = {32'd0, amo_rd_word};

	core_decode u_decode(
		.id_r(id_r),
		.ex_r(ex_r),
		.mem_r(mem_r),
		.wb_r(wb_r),
		.gpr(gpr),
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
		.csr_mcycle(cycle_cnt),
		.csr_mhartid(csr_mhartid),
		.csr_satp(csr_satp),
		.csr_medeleg(csr_medeleg),
		.csr_mideleg(csr_mideleg),
		.csr_mcounteren(csr_mcounteren),
		.csr_menvcfg(csr_menvcfg),
		.csr_pmpcfg0(csr_pmpcfg0),
		.csr_pmpaddr0(csr_pmpaddr0),
		.privilege_mode(privilege_mode),
		.ex_forwardable(ex_forwardable),
		.ex_result(ex_result),
		.mem_stage_result(mem_stage_result),
		.id_rs1(id_rs1),
		.id_rs2(id_rs2),
		.id_use_rs1(id_use_rs1),
		.id_use_rs2(id_use_rs2),
		.id_dec_valid(id_dec_valid),
		.id_dec_trap(id_dec_trap),
		.id_dec_wen(id_dec_wen),
		.id_dec_is_word(id_dec_is_word),
		.id_dec_alu_cmd(id_dec_alu_cmd),
		.id_dec_op1(id_dec_op1),
		.id_dec_op2(id_dec_op2),
		.id_dec_imm(id_dec_imm),
		.id_dec_rs2_store(id_dec_rs2_store),
		.id_dec_rd(id_dec_rd),
		.id_dec_is_load(id_dec_is_load),
		.id_dec_is_store(id_dec_is_store),
		.id_dec_mem_size(id_dec_mem_size),
		.id_dec_mem_unsigned(id_dec_mem_unsigned),
		.id_dec_is_branch(id_dec_is_branch),
		.id_dec_br_funct3(id_dec_br_funct3),
		.id_dec_is_jal(id_dec_is_jal),
		.id_dec_is_jalr(id_dec_is_jalr),
		.id_dec_wb_pc4(id_dec_wb_pc4),
		.id_dec_csr_wen(id_dec_csr_wen),
		.id_dec_csr_addr(id_dec_csr_addr),
		.id_dec_csr_wdata(id_dec_csr_wdata),
		.id_dec_is_ecall(id_dec_is_ecall),
		.id_dec_is_mret(id_dec_is_mret),
		.id_dec_is_sret(id_dec_is_sret),
		.id_dec_is_amo(id_dec_is_amo),
		.id_dec_amo_cmd(id_dec_amo_cmd),
		.id_dec_is_illegal(id_dec_is_illegal),
		.id_dec_is_ebreak(id_dec_is_ebreak),
		.id_dec_is_sfence(id_dec_is_sfence)
	);

	core_execute u_execute(
		.ex_r(ex_r),
		.mem_r(mem_r),
		.wb_r(wb_r),
		.dresp(dresp),
		.ex_is_mdu(ex_is_mdu),
		.mdu_out_valid(mdu_out_valid),
		.mdu_out_result(mdu_out_result),
		.ex_result_ready(ex_result_ready),
		.ex_forwardable(ex_forwardable),
		.stall_ex_busy(stall_ex_busy),
		.ex_result(ex_result),
		.ex_mem_addr(ex_mem_addr),
		.ex_flush_front(ex_flush_front),
		.ex_redirect_pc(ex_redirect_pc),
		.mem_access_done(mem_access_done),
		.mem_result_ready(mem_result_ready),
		.stall_mem_busy(stall_mem_busy),
		.stall_if_mem(stall_if_mem),
		.mem_stage_result(mem_stage_result),
		.mem_store_data_shifted(mem_store_data_shifted),
		.mem_store_strobe(mem_store_strobe),
		.difftest_skip(difftest_skip),
		.ex_misalign(ex_misalign),
		.ex_instr_misalign(ex_instr_misalign)
	);

	core_mdu u_mdu(
		.clk(clk),
		.reset(reset),
		.halted(halted),
		.trap_commit(trap_commit),
		.stall_pipe(stall_pipe),
		.ex_r(ex_r),
		.ex_is_mdu(mdu_req),
		.mdu_out_valid(mdu_core_out_valid),
		.mdu_out_result(mdu_core_out_result)
	);

	// ===== Hardware AMO state machine (T014): replaces DPI-C AMOHelper =====
	// Old amo_helper_result no longer needed; amo_result is computed above.
	// MDU/AMO result mux now also drives ex_is_mdu stall until amo_done_q.
	// (no DPI-C, no Verilator-specific code — pure RTL works in both sim and FPGA)

	assign mdu_out_valid = ex_r.is_amo ? amo_done_q : mdu_core_out_valid;
	assign mdu_out_result = ex_r.is_amo ? amo_result : mdu_core_out_result;

	assign intr_fetch_pc = mem_r.valid ? mem_r.pc :
	                       ex_r.valid  ? ex_r.pc  :
	                       id_r.valid  ? id_r.pc  :
	                                     fetch_pc;

	core_commit u_commit(
		.clk(clk),
		.reset(reset),
		.wb_r(wb_r),
		.trint(trint),
		.swint(swint),
		.exint(exint),
		.mmu_trap(mmu_trap),
		.trap_vaddr(trap_vaddr),
		.fault_is_insn(fault_is_insn),
		.fault_cause(fault_cause),
		.fault_pc(fault_pc),
		.trap_commit(trap_commit),
		.halted(halted),
		.trap_valid_latched(trap_valid_latched),
		.trap_code_latched(trap_code_latched),
		.trap_pc_latched(trap_pc_latched),
		.trap_cycle_latched(trap_cycle_latched),
		.trap_instr_latched(trap_instr_latched),
		.cycle_cnt(cycle_cnt),
		.instr_cnt(instr_cnt),
		.gpr(gpr),
		.gpr_diff(gpr_diff),
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
		.privilege_mode(privilege_mode),
		.privilege_mode_diff(privilege_mode_diff),
		.intr_fetch_pc(intr_fetch_pc),
		.ex_r_is_amo_active(amo_busy),   // T016: AMO in-flight suppresses interrupts
		.trap_redirect(trap_redirect),
		.mret_redirect(mret_redirect),
		.trap_redirect_pc(trap_redirect_pc)
	);

	assign raw_hazard_ex =
		id_r.valid && ex_r.valid && ex_r.wen && (ex_r.rd != 0) && !ex_result_ready &&
		((id_use_rs1 && (id_rs1 == ex_r.rd)) || (id_use_rs2 && (id_rs2 == ex_r.rd)));
	assign raw_hazard_mem =
		id_r.valid && mem_r.valid && mem_r.wen && (mem_r.rd != 0) && stall_if_mem &&
		((id_use_rs1 && (id_rs1 == mem_r.rd)) || (id_use_rs2 && (id_rs2 == mem_r.rd)));
	assign front_trap_pending =
		(ex_r.valid && ex_r.is_instr_misalign) ||
		(mem_r.valid && mem_r.is_instr_misalign) ||
		(wb_r.valid && wb_r.is_instr_misalign);
	assign stall_pipe  = stall_ex_busy || stall_mem_busy || raw_hazard_ex || raw_hazard_mem;
	assign stall_front = stall_ex_busy || raw_hazard_ex || raw_hazard_mem || fetch_redirect_pending || stall_if_mem || front_trap_pending || ex_to_mem_blocks_front;

	assign fetch_can_consume   = (!halted) && (!trap_commit) && (fetch_redirect_bubble == 2'd0) && (!stall_front) && !ex_flush_front;
	assign fetch_pop_buf       = fetch_can_consume && fetch_buf_valid;
	assign fetch_resp_fire     = fetch_pending && iresp.data_ok && !fetch_drop_resp_pending;
	assign fetch_resp_to_id    = fetch_can_consume && (!fetch_buf_valid) && fetch_resp_fire;
	assign fetch_resp_to_buf   = fetch_resp_fire && !fetch_resp_to_id && !fetch_redirect_pending && !trap_redirect && !mret_redirect;
	assign fetch_fire          = fetch_pop_buf || fetch_resp_to_id;
	assign fetch_req_new_fire  = fetch_can_consume && (!fetch_pending);
	assign fetch_issue_fire    = fetch_req_new_fire;
	assign fetch_req_addr      = fetch_pending ? fetch_req_pc : fetch_pc;

	assign ireq.valid = !halted && !trap_commit && (fetch_pending || fetch_issue_fire) && !stall_if_mem;
	assign ireq.addr  = fetch_req_addr;

	// ===== dreq bus mux: AMO state machine vs normal load/store =====
	// AMO drives dreq during EX-stage state machine (when ex_r.is_amo && amo_busy);
	// otherwise the normal MEM-stage load/store path drives dreq.
	// Note: when ex_r.is_amo is active, ex_is_mdu stalls the pipeline, so mem_r
	// does not advance — no conflict between the two dreq sources.
	wire amo_owns_dreq = ex_r.valid && ex_r.is_amo && (amo_state != AMO_ST_IDLE);
	assign dreq.valid  = amo_owns_dreq ? amo_dreq_valid :
	                     (mem_r.valid && (mem_r.is_load || mem_r.is_store) && !mem_r.is_amo && !trap_commit);
	assign dreq.addr   = amo_owns_dreq ? amo_dreq_addr   : mem_r.mem_addr;
	assign dreq.size   = amo_owns_dreq ? MSIZE4          : msize_t'(mem_r.mem_size);
	assign dreq.strobe = amo_owns_dreq ? amo_dreq_strobe : mem_r.mem_wstrb;
	assign dreq.data   = amo_owns_dreq ? amo_dreq_data   : mem_r.mem_wdata;

	always_ff @(posedge clk) begin
		if (reset) begin
			fetch_pc <= PCINIT;
			fetch_pending <= 1'b0;
			fetch_req_pc <= 64'd0;
			fetch_redirect_pending <= 1'b0;
			fetch_redirect_pc <= 64'd0;
			fetch_redirect_bubble <= 2'd0;
			fetch_drop_resp_pending <= 1'b0;
			fetch_buf_valid <= 1'b0;
			fetch_buf_pc <= 64'd0;
			fetch_buf_instr <= 32'd0;
			id_r <= '0;
			ex_r <= '0;
			mem_r <= '0;
			wb_r <= '0;
			amo_issued_q <= 1'b0;
			amo_done_q <= 1'b0;
			amo_state <= AMO_ST_IDLE;
			amo_addr_q <= '0;
			amo_wdata_q <= '0;
			amo_cmd_q <= '0;
			amo_old_data_q <= '0;
			amo_dreq_valid <= 1'b0;
			amo_dreq_addr <= '0;
			amo_dreq_strobe <= '0;
			amo_dreq_data <= '0;
			amo_sc_fail_q <= 1'b0;
			rs_addr[0] <= '0;
			rs_addr[1] <= '0;
			rs_valid[0] <= 1'b0;
			rs_valid[1] <= 1'b0;
		end else begin
			if (!ex_r.valid || !ex_r.is_amo) begin
				// Reset AMO state when no AMO instruction is in EX
				amo_issued_q <= 1'b0;
				amo_done_q   <= 1'b0;
				amo_state     <= AMO_ST_IDLE;
				amo_dreq_valid <= 1'b0;
			end else begin
				unique case (amo_state)
					AMO_ST_IDLE: begin
					// Latch AMO operands and start state machine
					if (amo_issue) begin
						amo_addr_q  <= ex_mem_addr;
						amo_wdata_q <= ex_r.rs2_store;
						amo_cmd_q   <= ex_r.amo_cmd;
						amo_issued_q <= 1'b1;
						amo_done_q  <= 1'b0;
						amo_sc_fail_q <= 1'b0;   // default: assume success
						// LR.W: only load, no store. SC.W: store conditional on rs_hit.
						// Other AMO.*: load -> compute -> store
						amo_state    <= AMO_ST_LOAD;
						amo_dreq_valid <= 1'b1;
						amo_dreq_addr  <= ex_mem_addr;
						amo_dreq_strobe <= 8'd0;          // read
						amo_dreq_data  <= 64'd0;
					end
				end
				AMO_ST_LOAD: begin
					// Wait for load data_ok
					if (dresp.data_ok) begin
						amo_old_data_q <= dresp.data;
						amo_dreq_valid <= 1'b0;
						// Determine next state based on command
						if (amo_cmd_q == AMO_CMD_LR) begin
							// LR.W: register reservation, then DONE
							rs_addr[rs_slot]  <= amo_addr_q;
							rs_valid[rs_slot] <= 1'b1;
							amo_state <= AMO_ST_DONE;
						end else if (amo_cmd_q == AMO_CMD_SC) begin
							// SC.W: check reservation, store if hit
							if (rs_hit) begin
								amo_dreq_valid <= 1'b1;
								amo_dreq_addr  <= amo_addr_q;
								amo_dreq_strobe <= amo_store_strobe;
								amo_dreq_data  <= amo_store_data;
								amo_state <= AMO_ST_STORE_W;
								// On successful SC, clear all reservations
								rs_valid[0] <= 1'b0;
								rs_valid[1] <= 1'b0;
							end else begin
								// SC failed: rd = 1, no store
								amo_sc_fail_q <= 1'b1;
								amo_state <= AMO_ST_DONE;
							end
						end else begin
						// Other AMO.*: store the computed value
						amo_dreq_valid <= 1'b1;
						amo_dreq_addr  <= amo_addr_q;
						amo_dreq_strobe <= amo_store_strobe;
						amo_dreq_data  <= amo_store_data;
						amo_state <= AMO_ST_STORE_W;
						end
					end
				end
					AMO_ST_STORE_W: begin
						// Wait for store completion
						if (dresp.data_ok) begin
							amo_dreq_valid <= 1'b0;
							amo_state <= AMO_ST_DONE;
						end
					end
					AMO_ST_DONE: begin
						// Result is ready, wait for stall_ex_busy to clear
						amo_done_q <= 1'b1;
						if (!stall_ex_busy) begin
							amo_done_q   <= 1'b0;
							amo_issued_q <= 1'b0;
							amo_state    <= AMO_ST_IDLE;
						end
					end
					default: amo_state <= AMO_ST_IDLE;
			endcase
		end

			if (trap_commit) begin
				fetch_pending <= 1'b0;
				fetch_redirect_pending <= 1'b0;
				fetch_buf_valid <= 1'b0;
			end

		if (!halted && !trap_commit) begin
			if (fetch_drop_resp_pending && iresp.data_ok) begin
				fetch_drop_resp_pending <= 1'b0;
			end
			if (fetch_redirect_bubble != 2'd0) begin
				fetch_redirect_bubble <= fetch_redirect_bubble - 2'd1;
			end
			// Trap redirect (exception/interrupt) and MRET redirect have highest priority
		if (trap_redirect || mret_redirect) begin
			if (fetch_pending) begin
					fetch_drop_resp_pending <= 1'b1;
				end
				fetch_buf_valid <= 1'b0;
				fetch_pending <= 1'b0;
				fetch_req_pc <= 64'd0;
				fetch_redirect_pending <= 1'b0;
				fetch_pc <= trap_redirect_pc;
				fetch_redirect_bubble <= 2'd2;
			end else if (mmu_trap) begin
				if (fetch_pending) begin
					fetch_drop_resp_pending <= 1'b1;
				end
				fetch_buf_valid <= 1'b0;
				fetch_pending <= 1'b0;
				fetch_req_pc <= 64'd0;
				fetch_redirect_pending <= 1'b0;
			end else if (ex_instr_misalign) begin
				if (fetch_pending) begin
					fetch_drop_resp_pending <= 1'b1;
				end
				fetch_buf_valid <= 1'b0;
				fetch_pending <= 1'b0;
				fetch_req_pc <= 64'd0;
				fetch_redirect_pending <= 1'b0;
			end else if (ex_flush_front) begin
					if (fetch_pending) begin
						fetch_drop_resp_pending <= 1'b1;
					end
					fetch_buf_valid <= 1'b0;
					fetch_pending <= 1'b0;
					fetch_req_pc <= 64'd0;
					fetch_redirect_pending <= 1'b0;
					fetch_pc <= ex_redirect_pc;
					fetch_redirect_bubble <= 2'd2;
				end else if (fetch_resp_fire) begin
					if (fetch_redirect_pending) begin
						fetch_pending <= 1'b0;
						fetch_req_pc <= 64'd0;
						fetch_redirect_pending <= 1'b0;
						fetch_pc <= fetch_redirect_pc;
						fetch_redirect_bubble <= 2'd2;
					end else begin
						fetch_pending <= 1'b0;
						fetch_req_pc <= 64'd0;
						fetch_pc <= fetch_req_pc + 64'd4;
					end
				end else if (fetch_req_new_fire) begin
					fetch_pending <= 1'b1;
					fetch_req_pc <= fetch_pc;
				end

				if (!ex_flush_front) begin
					if (fetch_resp_to_buf) begin
						fetch_buf_valid <= 1'b1;
						fetch_buf_pc <= fetch_req_pc;
						fetch_buf_instr <= iresp.data;
					end else if (fetch_pop_buf) begin
						fetch_buf_valid <= 1'b0;
					end
				end

				if (trap_redirect || mret_redirect || mmu_trap || stall_mem_busy) begin
					wb_r.valid <= 1'b0;
				end else begin
					wb_r.valid <= mem_r.valid;
					wb_r.trap  <= mem_r.trap;
					wb_r.wen   <= mem_r.wen;
					wb_r.rd    <= mem_r.rd;
					wb_r.pc    <= mem_r.pc;
					wb_r.instr <= mem_r.instr;
					wb_r.result<= mem_stage_result;
					wb_r.is_load <= mem_r.is_load;
					wb_r.is_store <= mem_r.is_store;
					wb_r.mem_addr <= mem_r.mem_addr;
					wb_r.csr_wen <= mem_r.csr_wen;
					wb_r.csr_addr <= mem_r.csr_addr;
					wb_r.csr_wdata <= mem_r.csr_wdata;
				wb_r.is_ecall <= mem_r.is_ecall;
				wb_r.is_mret <= mem_r.is_mret;
				wb_r.is_sret <= mem_r.is_sret;
				wb_r.is_illegal <= mem_r.is_illegal;
			wb_r.is_ebreak <= mem_r.is_ebreak;
				wb_r.is_sfence <= mem_r.is_sfence;
				wb_r.is_misalign <= mem_r.is_misalign;
				wb_r.is_instr_misalign <= mem_r.is_instr_misalign;
			end

				if (mmu_trap) begin
					mem_r <= '0;
					ex_r <= '0;
					id_r.valid <= 1'b0;
					id_r.pc    <= 64'd0;
					id_r.instr <= 32'd0;
				end else if (stall_mem_busy) begin
					// Hold MEM steady until the external bus returns valid data.
					mem_r <= mem_r;
					ex_r <= '0;
					id_r <= id_r;
			end else if (trap_redirect || mret_redirect || mmu_trap || stall_ex_busy || raw_hazard_mem || fetch_redirect_pending) begin
				mem_r <= '0;
				if (trap_redirect || mret_redirect || mmu_trap) begin
					ex_r <= '0;
					id_r.valid <= 1'b0;
					id_r.pc    <= 64'd0;
					id_r.instr <= 32'd0;
				end
				end else begin
					mem_r.valid <= ex_r.valid;
					mem_r.trap  <= ex_r.trap;
					mem_r.wen   <= ex_r.wen;
					mem_r.rd    <= ex_r.rd;
					mem_r.pc    <= ex_r.pc;
					mem_r.instr <= ex_r.instr;
					mem_r.result<= ex_r.is_amo ? amo_result : (ex_r.wb_pc4 ? (ex_r.pc + 64'd4) : ex_result);
					mem_r.is_load <= ex_r.is_load;
					mem_r.is_store <= ex_r.is_store;
					mem_r.mem_size <= ex_r.mem_size;
					mem_r.mem_unsigned <= ex_r.mem_unsigned;
					mem_r.mem_addr <= ex_mem_addr;
					mem_r.mem_wdata <= mem_store_data_shifted;
					mem_r.mem_wstrb <= ex_r.is_store ? mem_store_strobe : 8'd0;
				mem_r.csr_wen <= ex_r.csr_wen;
				mem_r.csr_addr <= ex_r.csr_addr;
				mem_r.csr_wdata <= ex_r.csr_wdata;
				mem_r.is_ecall <= ex_r.is_ecall;
				mem_r.is_mret <= ex_r.is_mret;
				mem_r.is_sret <= ex_r.is_sret;
				mem_r.is_amo <= ex_r.is_amo;
				mem_r.amo_cmd <= ex_r.amo_cmd;
				mem_r.is_illegal <= ex_r.is_illegal;
			mem_r.is_ebreak <= ex_r.is_ebreak;
				mem_r.is_sfence <= ex_r.is_sfence;
				mem_r.is_misalign <= ex_misalign;
				mem_r.is_instr_misalign <= ex_instr_misalign;

				if (trap_redirect || mret_redirect) begin
					ex_r <= '0;
					id_r.valid <= 1'b0;
					id_r.pc    <= 64'd0;
					id_r.instr <= 32'd0;
				end else if (ex_flush_front || ex_instr_misalign) begin
					ex_r <= '0;
					id_r.valid <= 1'b0;
					id_r.pc    <= 64'd0;
					id_r.instr <= 32'd0;
				end else if (ex_to_mem_blocks_front) begin
					ex_r <= '0;
					id_r <= id_r;
				end else if (raw_hazard_ex) begin
						ex_r <= '0;
					end else begin
						ex_r.valid   <= id_dec_valid;
						ex_r.trap    <= id_dec_trap;
						ex_r.wen     <= id_dec_wen;
						ex_r.is_word <= id_dec_is_word;
						ex_r.alu_cmd <= id_dec_alu_cmd;
						ex_r.rd      <= id_dec_rd;
						ex_r.pc      <= id_r.pc;
						ex_r.instr   <= id_r.instr;
						ex_r.op1     <= id_dec_op1;
						ex_r.op2     <= id_dec_op2;
						ex_r.imm     <= id_dec_imm;
						ex_r.rs2_store <= id_dec_rs2_store;
						ex_r.is_load <= id_dec_is_load;
						ex_r.is_store <= id_dec_is_store;
						ex_r.mem_size <= id_dec_mem_size;
						ex_r.mem_unsigned <= id_dec_mem_unsigned;
						ex_r.is_branch <= id_dec_is_branch;
						ex_r.br_funct3 <= id_dec_br_funct3;
						ex_r.is_jal <= id_dec_is_jal;
						ex_r.is_jalr <= id_dec_is_jalr;
						ex_r.wb_pc4 <= id_dec_wb_pc4;
				ex_r.csr_wen <= id_dec_csr_wen;
				ex_r.csr_addr <= id_dec_csr_addr;
				ex_r.csr_wdata <= id_dec_csr_wdata;
				ex_r.is_ecall <= id_dec_is_ecall;
				ex_r.is_mret <= id_dec_is_mret;
				ex_r.is_sret <= id_dec_is_sret;
				ex_r.is_amo <= id_dec_is_amo;
				ex_r.amo_cmd <= id_dec_amo_cmd;
				ex_r.is_illegal <= id_dec_is_illegal;
				ex_r.is_ebreak <= id_dec_is_ebreak;
				ex_r.is_sfence <= id_dec_is_sfence;
				ex_r.is_misalign <= ex_misalign;
				ex_r.is_instr_misalign <= ex_instr_misalign;

						if (fetch_pop_buf) begin
							id_r.valid <= 1'b1;
							id_r.pc    <= fetch_buf_pc;
							id_r.instr <= fetch_buf_instr;
						end else if (fetch_resp_to_id) begin
							id_r.valid <= 1'b1;
							id_r.pc    <= fetch_req_pc;
							id_r.instr <= iresp.data;
						end else begin
							id_r.valid <= 1'b0;
							id_r.pc    <= 64'd0;
							id_r.instr <= 32'd0;
						end
					end
				end
			end else begin
				id_r.valid  <= 1'b0;
				ex_r.valid  <= 1'b0;
				mem_r.valid <= 1'b0;
				wb_r.valid  <= 1'b0;
			end
		end
	end

	// Output port assignments
	assign csr_satp_o = csr_satp;
	assign csr_pmpcfg0_o = csr_pmpcfg0;
	assign csr_pmpaddr0_o = csr_pmpaddr0;
	assign privilege_mode_o = privilege_mode;
	assign mstatus_sum_o = csr_mstatus[18];   // SUM bit for MMU U-page access
	assign flush_mmu_o = trap_redirect || mret_redirect || ex_flush_front || ex_instr_misalign || mmu_trap;
	assign trap_vaddr = fault_vaddr;

`ifdef VERILATOR
	// Debug: stuck detector - prints when no instruction commits for a long time
	integer dbg_stall_cnt;
	integer dbg_commit_total;
	integer dbg_cycle_cnt;
	always_ff @(posedge clk) begin
		if (reset) begin
			dbg_stall_cnt <= 0;
			dbg_commit_total <= 0;
			dbg_cycle_cnt <= 0;
		end else begin
			dbg_cycle_cnt <= dbg_cycle_cnt + 1;
			if (wb_r.valid && !trap_commit) begin
				dbg_commit_total <= dbg_commit_total + 1;
				dbg_stall_cnt <= 0;
				if (dbg_commit_total < 100 || (dbg_commit_total % 10000 == 0)) begin
					$display("[C#%0d] pc=0x%016h instr=0x%08h wen=%0b rd=%0d isL=%0b isS=%0b",
					         dbg_commit_total, wb_r.pc, wb_r.instr, wb_r.wen, wb_r.rd, wb_r.is_load, wb_r.is_store);
				end
			end else begin
				dbg_stall_cnt <= dbg_stall_cnt + 1;
				if (dbg_stall_cnt == 100 || dbg_stall_cnt == 500 || dbg_stall_cnt == 1000 || dbg_stall_cnt == 5000) begin
					$display("[STUCK %0d] cyc=%0d fetch_pc=0x%016h id_pc=0x%016h ex_pc=0x%016h mem_pc=0x%016h wb_pc=0x%016h",
					         dbg_stall_cnt, dbg_cycle_cnt, fetch_pc, id_r.pc, ex_r.pc, mem_r.pc, wb_r.pc);
					$display("[STUCK %0d] stall_front=%0b stall_pipe=%0b stall_ex_busy=%0b stall_mem_busy=%0b stall_if_mem=%0b",
					         dbg_stall_cnt, stall_front, stall_pipe, stall_ex_busy, stall_mem_busy, stall_if_mem);
					$display("[STUCK %0d] raw_hazard_ex=%0b raw_hazard_mem=%0b fetch_redirect=%0b trap_redirect=%0b mret_redirect=%0b mmu_trap=%0b",
					         dbg_stall_cnt, raw_hazard_ex, raw_hazard_mem, fetch_redirect_pending, trap_redirect, mret_redirect, mmu_trap);
					$display("[STUCK %0d] satp=0x%016h priv=%0d halted=%0b trap_commit=%0b trap_valid=%0b",
					         dbg_stall_cnt, csr_satp, privilege_mode, halted, trap_commit, trap_valid_latched);
					$display("[STUCK %0d] id_valid=%0b ex_valid=%0b mem_valid=%0b wb_valid=%0b",
					         dbg_stall_cnt, id_r.valid, ex_r.valid, mem_r.valid, wb_r.valid);
					$display("[STUCK %0d] mem_is_load=%0b mem_is_store=%0b dreq_valid=%0b dresp_data_ok=%0b",
					         dbg_stall_cnt, mem_r.is_load, mem_r.is_store, dreq.valid, dresp.data_ok);
					$display("[STUCK %0d] ireq_valid=%0b iresp_data_ok=%0b fetch_pending=%0b fetch_buf_valid=%0b fetch_buf_instr=0x%08h",
					         dbg_stall_cnt, ireq.valid, iresp.data_ok, fetch_pending, fetch_buf_valid, fetch_buf_instr);
				end
			end
		end
	end
`endif

	assign fault_pc = mem_r.valid ? mem_r.pc :
	                  ex_r.valid  ? ex_r.pc  :
	                  wb_r.valid  ? wb_r.pc  :
	                                64'd0;
	assign mmu_trap = walk_fault && (fetch_redirect_bubble == 2'd0);

`ifdef VERILATOR
`ifdef FPGA_SIM
	// Debug: print trap events and instruction trace
	integer dbg_trap_count;
	integer dbg_commit_count;
	always_ff @(posedge clk) begin
		if (reset) begin
			dbg_trap_count <= 0;
			dbg_commit_count <= 0;
		end else begin
			// Track committed instructions (first 5000, then only disk-related)
			if (wb_r.valid && !trap_commit) begin
				dbg_commit_count <= dbg_commit_count + 1;
				if (dbg_commit_count < 100) begin
					$display("[COMMIT] #%0d pc=0x%016h instr=0x%08h wen=%0b rd=%0d",
					         dbg_commit_count, wb_r.pc, wb_r.instr, wb_r.wen, wb_r.rd);
				end
			end
			if (trap_redirect && dbg_trap_count < 20) begin
				dbg_trap_count <= dbg_trap_count + 1;
				$display("[TRAP] #%0d pc=0x%016h redirect_pc=0x%016h mcause=0x%016h mepc=0x%016h mtvec=0x%016h priv=%0d",
				         dbg_trap_count,
				         mem_r.valid ? mem_r.pc : (ex_r.valid ? ex_r.pc : 64'h0),
				         trap_redirect_pc,
				         csr_mcause,
				         csr_mepc,
				         csr_mtvec,
				         privilege_mode);
			end
			if (mret_redirect && dbg_trap_count < 50) begin
				$display("[MRET] pc=0x%016h redirect_pc=0x%016h mepc=0x%016h priv=%0d",
				         mem_r.valid ? mem_r.pc : (ex_r.valid ? ex_r.pc : 64'h0),
				         trap_redirect_pc,
				         csr_mepc,
				         privilege_mode);
			end
		end
	end
`endif // FPGA_SIM
`ifndef FPGA_SIM
	DifftestInstrCommit DifftestInstrCommit(
		.clock              (clk),
		.coreid             (csr_mhartid[7:0]),
		.index              (0),
		.valid              (wb_r.valid),
		.pc                 (wb_r.pc),
		.instr              (wb_r.instr),
		.skip               (difftest_skip),
		.isRVC              (0),
		.scFailed           (0),
		.wen                (wb_r.valid && wb_r.wen && (wb_r.rd != 0)),
		.wdest              ({3'd0, wb_r.rd}),
		.wdata              (wb_r.result)
	);

	DifftestArchIntRegState DifftestArchIntRegState (
		.clock              (clk),
		.coreid             (csr_mhartid[7:0]),
		.gpr_0              (gpr_diff[0]),
		.gpr_1              (gpr_diff[1]),
		.gpr_2              (gpr_diff[2]),
		.gpr_3              (gpr_diff[3]),
		.gpr_4              (gpr_diff[4]),
		.gpr_5              (gpr_diff[5]),
		.gpr_6              (gpr_diff[6]),
		.gpr_7              (gpr_diff[7]),
		.gpr_8              (gpr_diff[8]),
		.gpr_9              (gpr_diff[9]),
		.gpr_10             (gpr_diff[10]),
		.gpr_11             (gpr_diff[11]),
		.gpr_12             (gpr_diff[12]),
		.gpr_13             (gpr_diff[13]),
		.gpr_14             (gpr_diff[14]),
		.gpr_15             (gpr_diff[15]),
		.gpr_16             (gpr_diff[16]),
		.gpr_17             (gpr_diff[17]),
		.gpr_18             (gpr_diff[18]),
		.gpr_19             (gpr_diff[19]),
		.gpr_20             (gpr_diff[20]),
		.gpr_21             (gpr_diff[21]),
		.gpr_22             (gpr_diff[22]),
		.gpr_23             (gpr_diff[23]),
		.gpr_24             (gpr_diff[24]),
		.gpr_25             (gpr_diff[25]),
		.gpr_26             (gpr_diff[26]),
		.gpr_27             (gpr_diff[27]),
		.gpr_28             (gpr_diff[28]),
		.gpr_29             (gpr_diff[29]),
		.gpr_30             (gpr_diff[30]),
		.gpr_31             (gpr_diff[31])
	);

	DifftestTrapEvent DifftestTrapEvent(
		.clock              (clk),
		.coreid             (csr_mhartid[7:0]),
		.valid              (trap_valid_latched),
		.code               (trap_code_latched),
		.pc                 (trap_pc_latched),
		.cycleCnt           (trap_cycle_latched),
		.instrCnt           (trap_instr_latched)
	);

	DifftestCSRState DifftestCSRState(
		.clock              (clk),
		.coreid             (csr_mhartid[7:0]),
		.priviledgeMode     (privilege_mode_diff),
		.mstatus            (csr_mstatus_diff),
		.sstatus            (csr_mstatus_diff & SSTATUS_MASK),
		.mepc               (csr_mepc_diff),
		.sepc               (csr_sepc_diff),
		.mtval              (csr_mtval_diff),
		.stval              (csr_stval_diff),
		.mtvec              (csr_mtvec_diff),
		.stvec              (csr_stvec_diff),
		.mcause             (csr_mcause_diff),
		.scause             (csr_scause_diff),
		.satp               (csr_satp_diff),
		.mip                (csr_mip_diff),
		.mie                (csr_mie_diff),
		.mscratch           (csr_mscratch_diff),
		.sscratch           (csr_sscratch_diff),
		.mideleg            (csr_mideleg_diff),
		.medeleg            (csr_medeleg_diff)
	);
`endif // FPGA_SIM
`endif

endmodule

`endif
