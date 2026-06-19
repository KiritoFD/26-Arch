`ifndef __MMU_SV
`define __MMU_SV

`ifdef VERILATOR
`include "include/common.sv"
`endif

module mmu
	import common::*;(
	input  logic         clk,
	input  logic         reset,
	input  logic [63:0]  satp,
	input  logic [63:0]  pmpcfg0,
	input  logic [63:0]  pmpaddr0,
	input  logic [1:0]   privilege_mode,
	input  logic         flush,

	input  ibus_req_t    ireq_in,
	output ibus_resp_t   iresp_in,

	input  dbus_req_t    dreq_in,
	output dbus_resp_t   dresp_in,

	output ibus_req_t    ireq_out,
	input  ibus_resp_t   iresp_out,

	output dbus_req_t    dreq_out,
	input  dbus_resp_t   dresp_out,

	output logic         walk_fault,
	output logic [63:0]  fault_vaddr,
	output logic         fault_is_insn,
	output logic [63:0]  fault_cause
);

	typedef enum logic [2:0] {
		WALK_IDLE,
		WALK_LEVEL2,
		WALK_LEVEL1,
		WALK_LEVEL0,
		WALK_DONE_INSN,
		WALK_DONE_DATA
	} walk_state_t;

	walk_state_t state;
	logic        walk_active;
	logic        translate_en;
	logic        saved_is_insn;
	logic [63:0] saved_vaddr;
	logic [63:0] saved_wdata;
	logic [7:0]  saved_wstrb;
	logic [2:0]  saved_size;
	logic [63:0] pte_addr;
	logic [63:0] saved_pte;
	logic [1:0]  saved_level;
	logic [8:0]  vpn2, vpn1, vpn0;
	logic [11:0] page_offset;
	logic [63:0] phys_addr;
	logic        trap_pending;
	logic        satp_mode;
	logic [43:0] satp_ppn;
	logic        direct_insn_pmp_fault;
	logic        direct_load_pmp_fault;
	logic        direct_store_pmp_fault;
	logic        done_insn_pmp_fault;
	logic        done_load_pmp_fault;
	logic        done_store_pmp_fault;
	logic        data_is_store;
	logic        pmp_active;
	logic        pmp_hit;
	logic        pmp_allow_r;
	logic        pmp_allow_w;
	logic        pmp_allow_x;

	assign satp_mode = (satp[63:60] == 4'd8);
	assign satp_ppn  = satp[43:0];
	assign translate_en = satp_mode && (privilege_mode != 2'd3);
	assign walk_active  = (state == WALK_LEVEL2) || (state == WALK_LEVEL1) || (state == WALK_LEVEL0);

	assign vpn2 = saved_vaddr[38:30];
	assign vpn1 = saved_vaddr[29:21];
	assign vpn0 = saved_vaddr[20:12];
	assign page_offset = saved_vaddr[11:0];
	assign data_is_store = |saved_wstrb;

	function automatic logic pmp_entry_match(
		input logic [63:0] addr,
		input logic [63:0] cfg,
		input logic [63:0] paddr
	);
		logic [1:0] a_mode;
		logic [63:0] base;
		logic [63:0] top;
		int ones;
		begin
			a_mode = cfg[4:3];
			pmp_entry_match = 1'b0;
			unique case (a_mode)
				2'b00: pmp_entry_match = 1'b0;
				2'b01: begin
					base = 64'd0;
					top  = {8'd0, paddr[53:0], 2'b00};
					pmp_entry_match = (addr >= base) && (addr < top);
				end
				2'b10: pmp_entry_match = (addr[63:2] == paddr[63:2]);
				2'b11: begin
					ones = 0;
					while ((ones < 54) && paddr[ones]) begin
						ones = ones + 1;
					end
					base = ({8'd0, paddr[53:0], 2'b00} & ~((64'd1 << (ones + 3)) - 64'd1));
					top  = base + (64'd1 << (ones + 3));
					pmp_entry_match = (addr >= base) && (addr < top);
				end
				default: pmp_entry_match = 1'b0;
			endcase
		end
	endfunction

	function automatic logic pmp_req_fault(
		input logic [63:0] addr,
		input logic is_exec,
		input logic is_write,
		input logic [63:0] cfg,
		input logic [63:0] paddr,
		input logic [1:0] mode
	);
		logic active, hit, allow;
		begin
			active = (cfg[4:3] != 2'b00);
			hit = pmp_entry_match(addr, cfg, paddr);
			allow = is_exec ? cfg[2] : (is_write ? cfg[1] : cfg[0]);
			if (mode == 2'd3) begin
				pmp_req_fault = 1'b0;
			end else if (!active) begin
				pmp_req_fault = 1'b0;
			end else if (!hit) begin
				pmp_req_fault = 1'b1;
			end else begin
				pmp_req_fault = !allow;
			end
		end
	endfunction

	// Detect page walk failure
	// Note: In WALK_IDLE, walk_fault_next is always 0 because we haven't started walking yet
	// In other states, we check the PTE from the bus response
	logic walk_fault_next;
	assign walk_fault_next =
		(state == WALK_LEVEL2 && dresp_out.data_ok && !dresp_out.data[0]) ||
		(state == WALK_LEVEL1 && dresp_out.data_ok && !dresp_out.data[0]) ||
		(state == WALK_LEVEL0 && dresp_out.data_ok && !dresp_out.data[0]) ||
		(state == WALK_LEVEL0 && dresp_out.data_ok && dresp_out.data[0] &&
		 !dresp_out.data[3] && !dresp_out.data[1] && !dresp_out.data[2]);
	assign pmp_active  = (pmpcfg0[4:3] != 2'b00);
	assign pmp_hit     = pmp_entry_match(phys_addr, pmpcfg0, pmpaddr0);
	assign pmp_allow_r = pmp_hit && pmpcfg0[0];
	assign pmp_allow_w = pmp_hit && pmpcfg0[1];
	assign pmp_allow_x = pmp_hit && pmpcfg0[2];

	assign direct_insn_pmp_fault  = !translate_en && ireq_in.valid &&
	                                pmp_req_fault(ireq_in.addr, 1'b1, 1'b0, pmpcfg0, pmpaddr0, privilege_mode);
	assign direct_load_pmp_fault  = !translate_en && dreq_in.valid && (dreq_in.strobe == 8'd0) &&
	                                pmp_req_fault(dreq_in.addr, 1'b0, 1'b0, pmpcfg0, pmpaddr0, privilege_mode);
	assign direct_store_pmp_fault = !translate_en && dreq_in.valid && (dreq_in.strobe != 8'd0) &&
	                                pmp_req_fault(dreq_in.addr, 1'b0, 1'b1, pmpcfg0, pmpaddr0, privilege_mode);
	assign done_insn_pmp_fault    = (state == WALK_DONE_INSN) &&
	                                pmp_req_fault(phys_addr, 1'b1, 1'b0, pmpcfg0, pmpaddr0, privilege_mode);
	assign done_load_pmp_fault    = (state == WALK_DONE_DATA) && !data_is_store &&
	                                pmp_req_fault(phys_addr, 1'b0, 1'b0, pmpcfg0, pmpaddr0, privilege_mode);
	assign done_store_pmp_fault   = (state == WALK_DONE_DATA) && data_is_store &&
	                                pmp_req_fault(phys_addr, 1'b0, 1'b1, pmpcfg0, pmpaddr0, privilege_mode);

	assign walk_fault = (walk_active && walk_fault_next) ||
	                    direct_insn_pmp_fault || direct_load_pmp_fault || direct_store_pmp_fault ||
	                    done_insn_pmp_fault || done_load_pmp_fault || done_store_pmp_fault;
	assign fault_is_insn = (walk_active && walk_fault_next) ? saved_is_insn :
	                       (direct_insn_pmp_fault || done_insn_pmp_fault);
	assign fault_vaddr = (walk_active && walk_fault_next) ? saved_vaddr :
	                     direct_insn_pmp_fault ? ireq_in.addr :
	                     direct_load_pmp_fault ? dreq_in.addr :
	                     direct_store_pmp_fault ? dreq_in.addr :
	                     done_insn_pmp_fault ? saved_vaddr :
	                     done_load_pmp_fault ? saved_vaddr :
	                     done_store_pmp_fault ? saved_vaddr :
	                     64'd0;
	assign fault_cause = (walk_active && walk_fault_next) ?
	                     (saved_is_insn ? 64'd12 : (data_is_store ? 64'd15 : 64'd13)) :
	                     (direct_insn_pmp_fault || done_insn_pmp_fault) ? 64'd1 :
	                     (direct_store_pmp_fault || done_store_pmp_fault) ? 64'd7 :
	                     (direct_load_pmp_fault || done_load_pmp_fault) ? 64'd5 :
	                     64'd0;

	// Compute physical address from saved PTE and level
	always_comb begin
		phys_addr = 64'd0;
		unique case (saved_level)
			2'd2: phys_addr = {10'd0, saved_pte[53:30], vpn1, vpn0, page_offset};        // 10+24+9+9+12 = 64
			2'd1: phys_addr = {10'd0, saved_pte[53:21], vpn0, page_offset};               // 10+33+9+12 = 64
			2'd0: phys_addr = {8'd0, saved_pte[53:10], page_offset};                      // 8+44+12 = 64
			default: phys_addr = 64'd0;
		endcase
	end

	// Core response: passthrough when no translation needed
	assign iresp_in.addr_ok = (!translate_en) ? iresp_out.addr_ok : 1'b0;
	assign iresp_in.data_ok = (!translate_en) ? iresp_out.data_ok :
	                          (state == WALK_DONE_INSN && iresp_out.data_ok);
	assign iresp_in.data    = iresp_out.data;

	assign dresp_in.addr_ok = (!translate_en) ? dresp_out.addr_ok : 1'b0;
	assign dresp_in.data_ok = (!translate_en) ? dresp_out.data_ok :
	                          (state == WALK_DONE_DATA && dresp_out.data_ok);
	assign dresp_in.data    = dresp_out.data;

	// IBus output
	always_comb begin
		if (!translate_en) begin
			ireq_out = ireq_in;
			if (direct_insn_pmp_fault) begin
				ireq_out.valid = 1'b0;
			end
		end else if (state == WALK_DONE_INSN) begin
			ireq_out.valid = !done_insn_pmp_fault;
			ireq_out.addr  = phys_addr;
		end else if (flush) begin
			ireq_out.valid = 1'b0;
			ireq_out.addr  = 64'd0;
		end else begin
			ireq_out.valid = 1'b0;
			ireq_out.addr  = 64'd0;
		end
	end

	// DBus output
	always_comb begin
		if (!translate_en) begin
			dreq_out = dreq_in;
			if (direct_load_pmp_fault || direct_store_pmp_fault) begin
				dreq_out.valid = 1'b0;
			end
		end else if (walk_active) begin
			dreq_out.valid  = 1'b1;
			dreq_out.addr   = pte_addr;
			dreq_out.size   = MSIZE8;
			dreq_out.strobe = 8'd0;
			dreq_out.data   = 64'd0;
		end else if (state == WALK_DONE_DATA) begin
			dreq_out.valid  = !(done_load_pmp_fault || done_store_pmp_fault);
			dreq_out.addr   = phys_addr;
			dreq_out.size   = msize_t'(saved_size);
			dreq_out.strobe = saved_wstrb;
			dreq_out.data   = saved_wdata;
		end else begin
			dreq_out.valid  = 1'b0;
			dreq_out.addr   = 64'd0;
			dreq_out.size   = MSIZE8;
			dreq_out.strobe = 8'd0;
			dreq_out.data   = 64'd0;
		end
	end

	// Page table walker FSM
	always_ff @(posedge clk) begin
		if (reset) begin
			state         <= WALK_IDLE;
			saved_is_insn <= 1'b0;
			saved_vaddr   <= 64'd0;
			saved_wdata   <= 64'd0;
			saved_wstrb   <= 8'd0;
			saved_size    <= 3'd0;
			pte_addr      <= 64'd0;
			saved_pte     <= 64'd0;
			saved_level   <= 2'd0;
			trap_pending  <= 1'b0;
		end else if (flush) begin
			state         <= WALK_IDLE;
			saved_is_insn <= 1'b0;
			saved_vaddr   <= 64'd0;
			saved_wdata   <= 64'd0;
			saved_wstrb   <= 8'd0;
			saved_size    <= 3'd0;
			pte_addr      <= 64'd0;
			saved_pte     <= 64'd0;
			saved_level   <= 2'd0;
			trap_pending  <= 1'b0;
		end else begin
			case (state)
				WALK_IDLE: begin
					if (trap_pending) begin
						trap_pending <= trap_pending;
					end else begin
						trap_pending <= 1'b0;
						if (translate_en && privilege_mode != 2'd3) begin
							if (ireq_in.valid) begin
								state         <= WALK_LEVEL2;
								saved_is_insn <= 1'b1;
								saved_vaddr   <= ireq_in.addr;
								pte_addr      <= {8'd0, satp_ppn, ireq_in.addr[38:30], 3'b000};
							end else if (dreq_in.valid) begin
								state         <= WALK_LEVEL2;
								saved_is_insn <= 1'b0;
								saved_vaddr   <= dreq_in.addr;
								saved_wdata   <= dreq_in.data;
								saved_wstrb   <= dreq_in.strobe;
								saved_size    <= dreq_in.size;
								pte_addr      <= {8'd0, satp_ppn, dreq_in.addr[38:30], 3'b000};
							end
						end
					end
				end

				WALK_LEVEL2: begin
					if (dresp_out.data_ok) begin
						if (!dresp_out.data[0]) begin
							state <= WALK_IDLE;
						end else if (dresp_out.data[3] || dresp_out.data[1] || dresp_out.data[2]) begin
							saved_pte   <= dresp_out.data;
							saved_level <= 2'd2;
							state       <= saved_is_insn ? WALK_DONE_INSN : WALK_DONE_DATA;
						end else begin
							state    <= WALK_LEVEL1;
							pte_addr <= {8'd0, dresp_out.data[53:10], vpn1, 3'b000};
						end
					end
				end

				WALK_LEVEL1: begin
					if (dresp_out.data_ok) begin
						if (!dresp_out.data[0]) begin
							state <= WALK_IDLE;
						end else if (dresp_out.data[3] || dresp_out.data[1] || dresp_out.data[2]) begin
							saved_pte   <= dresp_out.data;
							saved_level <= 2'd1;
							state       <= saved_is_insn ? WALK_DONE_INSN : WALK_DONE_DATA;
						end else begin
							state    <= WALK_LEVEL0;
							pte_addr <= {8'd0, dresp_out.data[53:10], vpn0, 3'b000};
						end
					end
				end

				WALK_LEVEL0: begin
					if (dresp_out.data_ok) begin
						if (!dresp_out.data[0]) begin
							state <= WALK_IDLE;
						end else if (dresp_out.data[3] || dresp_out.data[1] || dresp_out.data[2]) begin
							saved_pte   <= dresp_out.data;
							saved_level <= 2'd0;
							state       <= saved_is_insn ? WALK_DONE_INSN : WALK_DONE_DATA;
						end else begin
							state <= WALK_IDLE;
						end
					end
				end

				WALK_DONE_INSN: begin
					if (iresp_out.data_ok) begin
						state <= WALK_IDLE;
					end
				end

				WALK_DONE_DATA: begin
					if (dresp_out.data_ok) begin
						state <= WALK_IDLE;
					end
				end

				default: state <= WALK_IDLE;
			endcase
		end
	end

endmodule

`endif
