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
	output logic         fault_is_insn
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

	assign satp_mode = (satp[63:60] == 4'd8);
	assign satp_ppn  = satp[43:0];
	assign translate_en = satp_mode && (privilege_mode != 2'd3);
	assign walk_active  = (state == WALK_LEVEL2) || (state == WALK_LEVEL1) || (state == WALK_LEVEL0);

	assign vpn2 = saved_vaddr[38:30];
	assign vpn1 = saved_vaddr[29:21];
	assign vpn0 = saved_vaddr[20:12];
	assign page_offset = saved_vaddr[11:0];

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
	// Only assert walk_fault when we are actively walking (not in WALK_IDLE)
	assign walk_fault = walk_active && walk_fault_next;

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
		end else if (state == WALK_DONE_INSN) begin
			ireq_out.valid = 1'b1;
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
		end else if (walk_active) begin
			dreq_out.valid  = 1'b1;
			dreq_out.addr   = pte_addr;
			dreq_out.size   = MSIZE8;
			dreq_out.strobe = 8'd0;
			dreq_out.data   = 64'd0;
		end else if (state == WALK_DONE_DATA) begin
			dreq_out.valid  = 1'b1;
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
			fault_vaddr   <= 64'd0;
			fault_is_insn <= 1'b0;
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
			fault_vaddr   <= 64'd0;
			fault_is_insn <= 1'b0;
			trap_pending  <= 1'b0;
		end else begin
			if (walk_fault_next) begin
				fault_vaddr   <= saved_vaddr;
				fault_is_insn <= saved_is_insn;
				trap_pending  <= 1'b1;
			end

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
