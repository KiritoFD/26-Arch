// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSimTopFPGA.h for the primary calling header

#include "VSimTopFPGA__pch.h"
#include "VSimTopFPGA___024root.h"

void VSimTopFPGA___024root___ico_sequent__TOP__0(VSimTopFPGA___024root* vlSelf);

void VSimTopFPGA___024root___eval_ico(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___eval_ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VSimTopFPGA___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void VSimTopFPGA___024root___ico_sequent__TOP__0(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___ico_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__dcvt__reset 
        = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__flush_mmu) 
           | (IData)(vlSelfRef.reset));
}

void VSimTopFPGA___024root___eval_triggers__ico(VSimTopFPGA___024root* vlSelf);

bool VSimTopFPGA___024root___eval_phase__ico(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___eval_phase__ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    VSimTopFPGA___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        VSimTopFPGA___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void VSimTopFPGA___024root___eval_act(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___eval_act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void VSimTopFPGA___024root___nba_sequent__TOP__0(VSimTopFPGA___024root* vlSelf);

void VSimTopFPGA___024root___eval_nba(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___eval_nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSimTopFPGA___024root___nba_sequent__TOP__0(vlSelf);
    }
}

extern const VlWide<15>/*479:0*/ VSimTopFPGA__ConstPool__CONST_hbda38995_0;
extern const VlWide<13>/*415:0*/ VSimTopFPGA__ConstPool__CONST_h2986b6f6_0;

VL_INLINE_OPT void VSimTopFPGA___024root___nba_sequent__TOP__0(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___nba_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlWide<5>/*131:0*/ SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps;
    VL_ZERO_W(132, SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps);
    VlWide<10>/*301:0*/ SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs;
    VL_ZERO_W(302, SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs);
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_can_consume;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_can_consume = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_use_rs1;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_use_rs1 = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_use_rs2;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_use_rs2 = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_is_mdu;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_is_mdu = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result_ready;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result_ready = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_forwardable;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_forwardable = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_if_mem;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_if_mem = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_access_done;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_access_done = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_out_valid;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_out_valid = 0;
    QData/*63:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_out_result;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_out_result = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT____VdfgRegularize_h47660625_0_10;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT____VdfgRegularize_h47660625_0_10 = 0;
    QData/*63:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs1_val;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs1_val = 0;
    QData/*63:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_imm_i;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_imm_i = 0;
    QData/*63:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_imm_u;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_imm_u = 0;
    QData/*63:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_csr_rdata;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_csr_rdata = 0;
    QData/*63:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__ex_result_word;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__ex_result_word = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__ex_branch_taken;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__ex_branch_taken = 0;
    QData/*63:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__mem_aligned_data;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__mem_aligned_data = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT____VdfgRegularize_he51b31ad_0_3;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT____VdfgRegularize_he51b31ad_0_3 = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_sfence;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_sfence = 0;
    QData/*63:0*/ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__walk_active;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__walk_active = 0;
    QData/*63:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__phys_addr;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__phys_addr = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_insn_pmp_fault;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_insn_pmp_fault = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_load_pmp_fault;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_load_pmp_fault = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_store_pmp_fault;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_store_pmp_fault = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_insn_pmp_fault;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_insn_pmp_fault = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_load_pmp_fault;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_load_pmp_fault = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_store_pmp_fault;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_store_pmp_fault = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_insn;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_insn = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_load;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_load = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_store;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_store = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__walk_fault_next;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__walk_fault_next = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_4;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_4 = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_7;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_7 = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_8;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_8 = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_9;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_9 = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_15;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_15 = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_17;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_17 = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_18;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_18 = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_22;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_22 = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_23;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_23 = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_24;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_24 = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_25;
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_25 = 0;
    CData/*0:0*/ SimTopFPGA__DOT__u_device__DOT____VdfgRegularize_heab64b38_0_1;
    SimTopFPGA__DOT__u_device__DOT____VdfgRegularize_heab64b38_0_1 = 0;
    QData/*63:0*/ __VdfgRegularize_hd87f99a1_0_0;
    __VdfgRegularize_hd87f99a1_0_0 = 0;
    CData/*0:0*/ __VdfgRegularize_hd87f99a1_0_6;
    __VdfgRegularize_hd87f99a1_0_6 = 0;
    IData/*31:0*/ __VdfgRegularize_hd87f99a1_0_8;
    __VdfgRegularize_hd87f99a1_0_8 = 0;
    CData/*0:0*/ __Vfunc_is_mdu_cmd__0__Vfuncout;
    __Vfunc_is_mdu_cmd__0__Vfuncout = 0;
    CData/*3:0*/ __Vfunc_is_mdu_cmd__0__cmd;
    __Vfunc_is_mdu_cmd__0__cmd = 0;
    CData/*0:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__3__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__3__Vfuncout = 0;
    QData/*63:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__3__cause;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__3__cause = 0;
    QData/*63:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__4__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__4__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__4__mode;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__4__mode = 0;
    QData/*63:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__5__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__5__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__5__mode;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__5__mode = 0;
    QData/*63:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__6__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__6__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__6__mode;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__6__mode = 0;
    CData/*0:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__7__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__7__Vfuncout = 0;
    QData/*63:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__7__cause;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__7__cause = 0;
    QData/*63:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__8__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__8__Vfuncout = 0;
    QData/*63:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__9__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__9__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__9__mode;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__9__mode = 0;
    CData/*0:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__10__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__10__Vfuncout = 0;
    CData/*0:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__11__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__11__Vfuncout = 0;
    CData/*0:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__12__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__12__Vfuncout = 0;
    CData/*0:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__13__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__13__Vfuncout = 0;
    QData/*63:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__13__cause;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__13__cause = 0;
    QData/*63:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__18__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__18__Vfuncout = 0;
    QData/*63:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__20__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__20__Vfuncout = 0;
    QData/*63:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__25__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__25__Vfuncout = 0;
    QData/*63:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__27__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__27__Vfuncout = 0;
    IData/*31:0*/ __Vdly__SimTopFPGA__DOT__dbg_cycle_count;
    __Vdly__SimTopFPGA__DOT__dbg_cycle_count = 0;
    IData/*31:0*/ __Vdly__SimTopFPGA__DOT__dbg_device_access_count;
    __Vdly__SimTopFPGA__DOT__dbg_device_access_count = 0;
    IData/*31:0*/ __Vdly__SimTopFPGA__DOT__dbg_ram_access_count;
    __Vdly__SimTopFPGA__DOT__dbg_ram_access_count = 0;
    CData/*0:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_drop_resp_pending;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_drop_resp_pending = 0;
    QData/*63:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pc;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pc = 0;
    QData/*63:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc = 0;
    CData/*0:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending = 0;
    CData/*1:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_bubble;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_bubble = 0;
    QData/*63:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_pc;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_pc = 0;
    VlWide<4>/*96:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r;
    VL_ZERO_W(97, __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r);
    VlWide<15>/*468:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r;
    VL_ZERO_W(469, __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r);
    VlWide<13>/*400:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r;
    VL_ZERO_W(401, __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r);
    CData/*0:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_issued_q;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_issued_q = 0;
    CData/*0:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_done_q;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_done_q = 0;
    IData/*31:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_trap_count;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_trap_count = 0;
    IData/*31:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_commit_count;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_commit_count = 0;
    CData/*0:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy = 0;
    CData/*0:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid = 0;
    CData/*3:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_cmd;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_cmd = 0;
    CData/*0:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word = 0;
    CData/*6:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left = 0;
    QData/*63:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_acc;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_acc = 0;
    QData/*63:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_a;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_a = 0;
    QData/*63:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_b;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_b = 0;
    VlWide<3>/*64:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem;
    VL_ZERO_W(65, __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem);
    QData/*63:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_quot;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_quot = 0;
    QData/*63:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_divisor;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_divisor = 0;
    CData/*0:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_signed;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_signed = 0;
    CData/*0:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_is_rem;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_is_rem = 0;
    CData/*0:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_q_neg;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_q_neg = 0;
    CData/*0:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_r_neg;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_r_neg = 0;
    QData/*63:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus = 0;
    QData/*63:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mip_raw;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mip_raw = 0;
    QData/*63:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mie;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mie = 0;
    QData/*63:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r = 0;
    CData/*1:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode = 0;
    CData/*2:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state = 0;
    CData/*0:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_is_insn;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_is_insn = 0;
    CData/*0:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__trap_pending;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__trap_pending = 0;
    CData/*0:0*/ __Vdly__SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_valid;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_valid = 0;
    SData/*15:0*/ __Vdly__SimTopFPGA__DOT__u_bram__DOT__counter;
    __Vdly__SimTopFPGA__DOT__u_bram__DOT__counter = 0;
    CData/*0:0*/ __Vdly__SimTopFPGA__DOT__u_bram__DOT__txn_active;
    __Vdly__SimTopFPGA__DOT__u_bram__DOT__txn_active = 0;
    CData/*0:0*/ __Vdly__SimTopFPGA__DOT__u_bram__DOT__real_valid;
    __Vdly__SimTopFPGA__DOT__u_bram__DOT__real_valid = 0;
    IData/*31:0*/ __Vdly__SimTopFPGA__DOT__u_device__DOT__gen_dbg_live__DOT__dbg_live_count;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__gen_dbg_live__DOT__dbg_live_count = 0;
    QData/*63:0*/ __Vdly__SimTopFPGA__DOT__u_device__DOT__mtime;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__mtime = 0;
    SData/*15:0*/ __Vdly__SimTopFPGA__DOT__u_device__DOT__mtime_div;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__mtime_div = 0;
    CData/*4:0*/ __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_wptr;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_wptr = 0;
    CData/*5:0*/ __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_count;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_count = 0;
    CData/*4:0*/ __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_rptr;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_rptr = 0;
    CData/*7:0*/ __Vdly__SimTopFPGA__DOT__u_device__DOT__fifo_count;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__fifo_count = 0;
    CData/*1:0*/ __Vdly__SimTopFPGA__DOT__u_device__DOT__txState;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__txState = 0;
    SData/*13:0*/ __Vdly__SimTopFPGA__DOT__u_device__DOT__bitTmr;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__bitTmr = 0;
    IData/*31:0*/ __Vdly__SimTopFPGA__DOT__u_device__DOT__bitIndex;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__bitIndex = 0;
    CData/*1:0*/ __Vdly__SimTopFPGA__DOT__u_device__DOT__rxState;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__rxState = 0;
    CData/*3:0*/ __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitIndex;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitIndex = 0;
    SData/*13:0*/ __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitTmr;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitTmr = 0;
    SData/*9:0*/ __Vdly__SimTopFPGA__DOT__u_device__DOT__rxShiftReg;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__rxShiftReg = 0;
    CData/*0:0*/ __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v0;
    __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v0 = 0;
    QData/*63:0*/ __VdlyVal__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v32;
    __VdlyVal__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v32 = 0;
    CData/*4:0*/ __VdlyDim0__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v32;
    __VdlyDim0__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v32 = 0;
    CData/*0:0*/ __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v32;
    __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v32 = 0;
    CData/*0:0*/ __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v33;
    __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v33 = 0;
    CData/*0:0*/ __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v35;
    __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v35 = 0;
    CData/*0:0*/ __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v36;
    __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v36 = 0;
    QData/*63:0*/ __VdlyVal__SimTopFPGA__DOT__u_bram__DOT__mem__v0;
    __VdlyVal__SimTopFPGA__DOT__u_bram__DOT__mem__v0 = 0;
    IData/*17:0*/ __VdlyDim0__SimTopFPGA__DOT__u_bram__DOT__mem__v0;
    __VdlyDim0__SimTopFPGA__DOT__u_bram__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__SimTopFPGA__DOT__u_bram__DOT__mem__v0;
    __VdlySet__SimTopFPGA__DOT__u_bram__DOT__mem__v0 = 0;
    CData/*7:0*/ __VdlyVal__SimTopFPGA__DOT__u_device__DOT__console_rx_fifo__v0;
    __VdlyVal__SimTopFPGA__DOT__u_device__DOT__console_rx_fifo__v0 = 0;
    CData/*3:0*/ __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__console_rx_fifo__v0;
    __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__console_rx_fifo__v0 = 0;
    CData/*0:0*/ __VdlySet__SimTopFPGA__DOT__u_device__DOT__console_rx_fifo__v0;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__console_rx_fifo__v0 = 0;
    CData/*7:0*/ __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v0;
    __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v0 = 0;
    IData/*17:0*/ __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v0;
    __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v0;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v0 = 0;
    CData/*7:0*/ __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v1;
    __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v1 = 0;
    IData/*17:0*/ __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v1;
    __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v1 = 0;
    CData/*0:0*/ __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v1;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v1 = 0;
    CData/*7:0*/ __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v2;
    __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v2 = 0;
    IData/*17:0*/ __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v2;
    __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v2 = 0;
    CData/*0:0*/ __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v2;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v2 = 0;
    CData/*7:0*/ __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v3;
    __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v3 = 0;
    IData/*17:0*/ __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v3;
    __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v3 = 0;
    CData/*0:0*/ __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v3;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v3 = 0;
    CData/*7:0*/ __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v4;
    __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v4 = 0;
    IData/*17:0*/ __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v4;
    __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v4 = 0;
    CData/*0:0*/ __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v4;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v4 = 0;
    CData/*7:0*/ __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v5;
    __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v5 = 0;
    IData/*17:0*/ __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v5;
    __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v5 = 0;
    CData/*0:0*/ __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v5;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v5 = 0;
    CData/*7:0*/ __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v6;
    __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v6 = 0;
    IData/*17:0*/ __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v6;
    __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v6 = 0;
    CData/*0:0*/ __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v6;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v6 = 0;
    CData/*7:0*/ __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v7;
    __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v7 = 0;
    IData/*17:0*/ __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v7;
    __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v7 = 0;
    CData/*0:0*/ __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v7;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v7 = 0;
    VlWide<3>/*95:0*/ __Vtemp_2;
    VlWide<3>/*95:0*/ __Vtemp_5;
    VlWide<3>/*95:0*/ __Vtemp_6;
    // Body
    __Vdly__SimTopFPGA__DOT__u_device__DOT__bitIndex 
        = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__bitIndex;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__bitTmr 
        = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__bitTmr;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__txState 
        = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txState;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__rxState 
        = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxState;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitIndex 
        = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBitIndex;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitTmr 
        = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBitTmr;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__rxShiftReg 
        = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxShiftReg;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__mtime_div 
        = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__mtime_div;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__mtime = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__mtime;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__fifo_count 
        = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__fifo_count;
    __Vdly__SimTopFPGA__DOT__u_bram__DOT__real_valid 
        = vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__real_valid;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__gen_dbg_live__DOT__dbg_live_count 
        = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__gen_dbg_live__DOT__dbg_live_count;
    __Vdly__SimTopFPGA__DOT__u_bram__DOT__counter = vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__counter;
    __Vdly__SimTopFPGA__DOT__u_bram__DOT__txn_active 
        = vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__txn_active;
    if ((((~ (IData)(vlSelfRef.reset)) & (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txn_fire)) 
         & (0U != (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                            >> 0xaU))))) {
        if (VL_UNLIKELY(((0x10000000ULL == (((QData)((IData)(
                                                             vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                             << 0x2eU) 
                                            | (((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                << 0xeU) 
                                               | ((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                  >> 0x12U)))) 
                         & (~ ((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__uart_lcr) 
                               >> 7U))))) {
            VL_WRITEF_NX("%c",0,8,vlSelfRef.SimTopFPGA__DOT__u_device__DOT__tx_write_byte);
        } else if (VL_UNLIKELY((0x23333000ULL == (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                                   << 0x2eU) 
                                                  | (((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                      << 0xeU) 
                                                     | ((QData)((IData)(
                                                                        vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                        >> 0x12U)))))) {
            VL_WRITEF_NX("Hello World!\n",0);
        }
    }
    __Vdly__SimTopFPGA__DOT__dbg_cycle_count = vlSelfRef.SimTopFPGA__DOT__dbg_cycle_count;
    __Vdly__SimTopFPGA__DOT__dbg_device_access_count 
        = vlSelfRef.SimTopFPGA__DOT__dbg_device_access_count;
    __Vdly__SimTopFPGA__DOT__dbg_ram_access_count = vlSelfRef.SimTopFPGA__DOT__dbg_ram_access_count;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_rptr 
        = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_rptr;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_wptr 
        = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_wptr;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__console_rx_fifo__v0 = 0U;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_count 
        = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_count;
    __VdlySet__SimTopFPGA__DOT__u_bram__DOT__mem__v0 = 0U;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v0 = 0U;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v1 = 0U;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v2 = 0U;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v3 = 0U;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v4 = 0U;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v5 = 0U;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v6 = 0U;
    __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v7 = 0U;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_valid 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_valid;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_cmd 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_cmd;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_acc 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_acc;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_a 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_a;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_b 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_b;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[0U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[0U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[1U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[1U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[2U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[2U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_quot 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_quot;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_divisor 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_divisor;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_signed 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_signed;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_is_rem 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_is_rem;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_q_neg 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_q_neg;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_r_neg 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_r_neg;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_pc 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_pc;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_issued_q 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_issued_q;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pc 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pc;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_bubble 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_bubble;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_done_q 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_done_q;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[1U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[1U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[3U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[3U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[4U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[4U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[8U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[8U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[9U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[9U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xaU] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xaU];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xbU] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xbU];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU];
    __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v0 = 0U;
    __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v32 = 0U;
    __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v33 = 0U;
    __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v35 = 0U;
    __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v36 = 0U;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[1U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[1U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[4U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[4U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[6U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[6U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU];
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_drop_resp_pending 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_drop_resp_pending;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mip_raw 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mip_raw;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mie 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mie;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__trap_pending 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__trap_pending;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_is_insn 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_is_insn;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_trap_count 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_trap_count;
    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_commit_count 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_commit_count;
    __Vdly__SimTopFPGA__DOT__u_device__DOT__bitTmr 
        = ((((IData)(vlSelfRef.reset) | (0U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txState))) 
            | (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__bitDone))
            ? 0U : (0x3fffU & ((IData)(1U) + (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__bitTmr))));
    __Vdly__SimTopFPGA__DOT__u_bram__DOT__real_valid 
        = (1U & (~ (((((IData)(vlSelfRef.reset) | (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__txn_active))) 
                      | (2U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__counter))) 
                     | (IData)(vlSelfRef.SimTopFPGA__DOT__ram_last)) 
                    | (IData)(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__real_valid))));
    if (vlSelfRef.reset) {
        __Vdly__SimTopFPGA__DOT__u_device__DOT__bitIndex = 0U;
        __Vdly__SimTopFPGA__DOT__u_device__DOT__txState = 0U;
        __Vdly__SimTopFPGA__DOT__u_device__DOT__mtime = 0ULL;
        __Vdly__SimTopFPGA__DOT__u_device__DOT__mtime_div = 0U;
        __Vdly__SimTopFPGA__DOT__u_device__DOT__fifo_count = 0U;
    } else {
        if ((0U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txState))) {
            __Vdly__SimTopFPGA__DOT__u_device__DOT__bitIndex = 0U;
            if (vlSelfRef.SimTopFPGA__DOT__u_device__DOT__tx_start) {
                __Vdly__SimTopFPGA__DOT__u_device__DOT__txState = 1U;
            }
        } else if ((1U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txState))) {
            __Vdly__SimTopFPGA__DOT__u_device__DOT__bitIndex 
                = ((IData)(1U) + vlSelfRef.SimTopFPGA__DOT__u_device__DOT__bitIndex);
            __Vdly__SimTopFPGA__DOT__u_device__DOT__txState = 2U;
        } else if ((2U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txState))) {
            if ((0xd8U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__bitTmr))) {
                __Vdly__SimTopFPGA__DOT__u_device__DOT__txState 
                    = ((0xaU == vlSelfRef.SimTopFPGA__DOT__u_device__DOT__bitIndex)
                        ? 0U : 1U);
            }
        } else {
            __Vdly__SimTopFPGA__DOT__u_device__DOT__txState = 0U;
        }
        if ((0x18U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__mtime_div))) {
            __Vdly__SimTopFPGA__DOT__u_device__DOT__mtime 
                = (1ULL + vlSelfRef.SimTopFPGA__DOT__u_device__DOT__mtime);
            __Vdly__SimTopFPGA__DOT__u_device__DOT__mtime_div = 0U;
        } else {
            __Vdly__SimTopFPGA__DOT__u_device__DOT__mtime_div 
                = (0xffffU & ((IData)(1U) + (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__mtime_div)));
        }
        if ((2U == ((((IData)(vlSelfRef.SimTopFPGA__DOT__dbg_cpu_tx_write) 
                      & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__fifo_full))) 
                     << 1U) | (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__tx_start)))) {
            __Vdly__SimTopFPGA__DOT__u_device__DOT__fifo_count 
                = (0xffU & ((IData)(1U) + (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__fifo_count)));
        } else if ((1U == ((((IData)(vlSelfRef.SimTopFPGA__DOT__dbg_cpu_tx_write) 
                             & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__fifo_full))) 
                            << 1U) | (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__tx_start)))) {
            __Vdly__SimTopFPGA__DOT__u_device__DOT__fifo_count 
                = (0xffU & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__fifo_count) 
                            - (IData)(1U)));
        }
    }
    if (vlSelfRef.reset) {
        __Vdly__SimTopFPGA__DOT__u_device__DOT__gen_dbg_live__DOT__dbg_live_count = 0U;
    } else if (VL_UNLIKELY(((IData)(vlSelfRef.SimTopFPGA__DOT__device_valid) 
                            & VL_GTS_III(32, 5U, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__gen_dbg_live__DOT__dbg_live_count)))) {
        VL_WRITEF_NX("[DEV_LIVE] valid=%0b ready=%0b txn_fire=%0b wvalid=%0b addr=0x%0x wdata=0x%0x wstrobe=0x%02x\n",0,
                     1,vlSelfRef.SimTopFPGA__DOT__device_valid,
                     1,(IData)(vlSelfRef.SimTopFPGA__DOT__device_ready),
                     1,vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txn_fire,
                     1,(0U != (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                        >> 0xaU))),
                     64,(((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                          << 0x2eU) | (((QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                        << 0xeU) | 
                                       ((QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                        >> 0x12U))),
                     64,(((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                          << 0x36U) | (((QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__oreq[1U])) 
                                        << 0x16U) | 
                                       ((QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__oreq[0U])) 
                                        >> 0xaU))),
                     8,(0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                 >> 0xaU)));
        __Vdly__SimTopFPGA__DOT__u_device__DOT__gen_dbg_live__DOT__dbg_live_count 
            = ((IData)(1U) + vlSelfRef.SimTopFPGA__DOT__u_device__DOT__gen_dbg_live__DOT__dbg_live_count);
    }
    if (vlSelfRef.reset) {
        __Vdly__SimTopFPGA__DOT__dbg_cycle_count = 0U;
        __Vdly__SimTopFPGA__DOT__dbg_device_access_count = 0U;
        __Vdly__SimTopFPGA__DOT__dbg_ram_access_count = 0U;
    } else {
        __Vdly__SimTopFPGA__DOT__dbg_cycle_count = 
            ((IData)(1U) + vlSelfRef.SimTopFPGA__DOT__dbg_cycle_count);
        if (((IData)(vlSelfRef.SimTopFPGA__DOT__ram_valid) 
             & (IData)(vlSelfRef.SimTopFPGA__DOT__ram_ready))) {
            __Vdly__SimTopFPGA__DOT__dbg_ram_access_count 
                = ((IData)(1U) + vlSelfRef.SimTopFPGA__DOT__dbg_ram_access_count);
        }
        if (((IData)(vlSelfRef.SimTopFPGA__DOT__device_valid) 
             & (IData)(vlSelfRef.SimTopFPGA__DOT__device_ready))) {
            __Vdly__SimTopFPGA__DOT__dbg_device_access_count 
                = ((IData)(1U) + vlSelfRef.SimTopFPGA__DOT__dbg_device_access_count);
            if (VL_GTES_III(32, 0x1f4U, vlSelfRef.SimTopFPGA__DOT__dbg_device_access_count)) {
                if ((0U != (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                     >> 0xaU)))) {
                    VL_WRITEF_NX("[DEV_W] cyc=%0d #%0d addr=0x%0x wdata=0x%0x wstrobe=0x%02x\n",0,
                                 32,vlSelfRef.SimTopFPGA__DOT__dbg_cycle_count,
                                 32,vlSelfRef.SimTopFPGA__DOT__dbg_device_access_count,
                                 64,(((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                      << 0x2eU) | (
                                                   ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                    << 0xeU) 
                                                   | ((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                      >> 0x12U))),
                                 64,(((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                      << 0x36U) | (
                                                   ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__oreq[1U])) 
                                                    << 0x16U) 
                                                   | ((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__oreq[0U])) 
                                                      >> 0xaU))),
                                 8,(0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                             >> 0xaU)));
                } else {
                    VL_WRITEF_NX("[DEV_R] cyc=%0d #%0d addr=0x%0x rdata=0x%0x\n",0,
                                 32,vlSelfRef.SimTopFPGA__DOT__dbg_cycle_count,
                                 32,vlSelfRef.SimTopFPGA__DOT__dbg_device_access_count,
                                 64,(((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                      << 0x2eU) | (
                                                   ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                    << 0xeU) 
                                                   | ((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                      >> 0x12U))),
                                 64,vlSelfRef.SimTopFPGA__DOT__device_rdata);
                }
            }
        }
        if (((((IData)(vlSelfRef.SimTopFPGA__DOT__device_valid) 
               & (IData)(vlSelfRef.SimTopFPGA__DOT__device_ready)) 
              & (0x10001000ULL <= (((QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                    << 0x2eU) | (((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                  << 0xeU) 
                                                 | ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                    >> 0x12U))))) 
             & (0x10001500ULL >= (((QData)((IData)(
                                                   vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                   << 0x2eU) | (((QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                 << 0xeU) 
                                                | ((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                   >> 0x12U)))))) {
            if (VL_GTES_III(32, 0x1feU, vlSelfRef.SimTopFPGA__DOT__dbg_device_access_count)) {
                if ((0U != (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                     >> 0xaU)))) {
                    VL_WRITEF_NX("[DISK_W] cyc=%0d #%0d addr=0x%0x wdata=0x%0x\n",0,
                                 32,vlSelfRef.SimTopFPGA__DOT__dbg_cycle_count,
                                 32,vlSelfRef.SimTopFPGA__DOT__dbg_device_access_count,
                                 64,(((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                      << 0x2eU) | (
                                                   ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                    << 0xeU) 
                                                   | ((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                      >> 0x12U))),
                                 64,(((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                      << 0x36U) | (
                                                   ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__oreq[1U])) 
                                                    << 0x16U) 
                                                   | ((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__oreq[0U])) 
                                                      >> 0xaU))));
                } else {
                    VL_WRITEF_NX("[DISK_R] cyc=%0d #%0d addr=0x%0x rdata=0x%0x\n",0,
                                 32,vlSelfRef.SimTopFPGA__DOT__dbg_cycle_count,
                                 32,vlSelfRef.SimTopFPGA__DOT__dbg_device_access_count,
                                 64,(((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                      << 0x2eU) | (
                                                   ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                    << 0xeU) 
                                                   | ((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                      >> 0x12U))),
                                 64,vlSelfRef.SimTopFPGA__DOT__device_rdata);
                }
            }
        }
        if ((VL_LTS_III(32, 0xad10b0U, vlSelfRef.SimTopFPGA__DOT__dbg_cycle_count) 
             & VL_GTS_III(32, 0xad1498U, vlSelfRef.SimTopFPGA__DOT__dbg_cycle_count))) {
            if (VL_UNLIKELY((0x400000U & vlSelfRef.SimTopFPGA__DOT__oreq[4U]))) {
                VL_WRITEF_NX("[OREQ] cyc=%0d valid=%0b addr=0x%0x is_write=%0b strobe=0x%02x ready=%0b last=%0b\n",0,
                             32,vlSelfRef.SimTopFPGA__DOT__dbg_cycle_count,
                             1,(1U & (vlSelfRef.SimTopFPGA__DOT__oreq[4U] 
                                      >> 0x16U)),64,
                             (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                               << 0x2eU) | (((QData)((IData)(
                                                             vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                             << 0xeU) 
                                            | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                               >> 0x12U))),
                             1,(1U & (vlSelfRef.SimTopFPGA__DOT__oreq[4U] 
                                      >> 0x15U)),8,
                             (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                       >> 0xaU)),1,
                             (1U & (vlSelfRef.SimTopFPGA__DOT__oresp[2U] 
                                    >> 1U)),1,(1U & 
                                               vlSelfRef.SimTopFPGA__DOT__oresp[2U]));
            }
        }
        if (VL_UNLIKELY((VL_LTS_III(32, 0U, vlSelfRef.SimTopFPGA__DOT__dbg_cycle_count) 
                         & (0U == VL_MODDIVS_III(32, vlSelfRef.SimTopFPGA__DOT__dbg_cycle_count, (IData)(0xf4240U)))))) {
            VL_WRITEF_NX("[STATUS] cyc=%0d ram=%0d dev=%0d uart_w=%0b dev_r=%0b\n",0,
                         32,vlSelfRef.SimTopFPGA__DOT__dbg_cycle_count,
                         32,vlSelfRef.SimTopFPGA__DOT__dbg_ram_access_count,
                         32,vlSelfRef.SimTopFPGA__DOT__dbg_device_access_count,
                         1,(IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__dbg_ever_uart_write_reg),
                         1,vlSelfRef.SimTopFPGA__DOT__u_device__DOT__dbg_ever_device_read_reg);
        }
    }
    if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__real_valid) 
         & (IData)(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__is_write))) {
        vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__waddr 
            = (0x3ffffU & (IData)((vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__latched_addr 
                                   >> 3U)));
        vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask = 0ULL;
        if ((1U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__latched_wstrobe))) {
            vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask 
                = (0xffULL | vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask);
        }
        if ((2U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__latched_wstrobe))) {
            vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask 
                = (0xff00ULL | vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask);
        }
        if ((4U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__latched_wstrobe))) {
            vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask 
                = (0xff0000ULL | vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask);
        }
        if ((8U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__latched_wstrobe))) {
            vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask 
                = (0xff000000ULL | vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask);
        }
        if ((0x10U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__latched_wstrobe))) {
            vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask 
                = (0xff00000000ULL | vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask);
        }
        if ((0x20U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__latched_wstrobe))) {
            vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask 
                = (0xff0000000000ULL | vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask);
        }
        if ((0x40U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__latched_wstrobe))) {
            vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask 
                = (0xff000000000000ULL | vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask);
        }
        if ((0x80U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__latched_wstrobe))) {
            vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask 
                = (0xff00000000000000ULL | vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask);
        }
        __VdlyVal__SimTopFPGA__DOT__u_bram__DOT__mem__v0 
            = ((vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__latched_wdata 
                & vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask) 
               | (vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__mem
                  [vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__waddr] 
                  & (~ vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask)));
        __VdlyDim0__SimTopFPGA__DOT__u_bram__DOT__mem__v0 
            = vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__waddr;
        __VdlySet__SimTopFPGA__DOT__u_bram__DOT__mem__v0 = 1U;
    }
    if ((((((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txn_fire) 
            & (0U != (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                               >> 0xaU)))) & (0x10001100ULL 
                                              <= (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                                   << 0x2eU) 
                                                  | (((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                      << 0xeU) 
                                                     | ((QData)((IData)(
                                                                        vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                        >> 0x12U))))) 
          & (0x10001500ULL > (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                               << 0x2eU) | (((QData)((IData)(
                                                             vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                             << 0xeU) 
                                            | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                               >> 0x12U))))) 
         & (0U != (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                            >> 0xaU))))) {
        if ((0x400U & vlSelfRef.SimTopFPGA__DOT__oreq[2U])) {
            vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h24e30222__0 
                = (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[0U] 
                            >> 0xaU));
            if ((0x3e7ffU >= (0x3ffffU & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                           + (0xffU 
                                              & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                 >> 0x14U))) 
                                          - (IData)(0x40U))))) {
                __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v0 
                    = vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h24e30222__0;
                __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v0 
                    = (0x3ffffU & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                    + (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                >> 0x14U))) 
                                   - (IData)(0x40U)));
                __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v0 = 1U;
            }
        }
        if ((0x800U & vlSelfRef.SimTopFPGA__DOT__oreq[2U])) {
            vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h24e30222__0 
                = (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[0U] 
                            >> 0x12U));
            if ((0x3e7ffU >= (0x3ffffU & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                           + (0xffU 
                                              & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                 >> 0x14U))) 
                                          - (IData)(0x40U))))) {
                __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v1 
                    = vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h24e30222__0;
                __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v1 
                    = (0x3ffffU & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                    + (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                >> 0x14U))) 
                                   - (IData)(0x40U)));
                __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v1 = 1U;
            }
        }
        if ((0x1000U & vlSelfRef.SimTopFPGA__DOT__oreq[2U])) {
            vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h24e30222__0 
                = (0xffU & ((vlSelfRef.SimTopFPGA__DOT__oreq[1U] 
                             << 6U) | (vlSelfRef.SimTopFPGA__DOT__oreq[0U] 
                                       >> 0x1aU)));
            if ((0x3e7ffU >= (0x3ffffU & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                           + (0xffU 
                                              & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                 >> 0x14U))) 
                                          - (IData)(0x40U))))) {
                __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v2 
                    = vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h24e30222__0;
                __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v2 
                    = (0x3ffffU & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                    + (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                >> 0x14U))) 
                                   - (IData)(0x40U)));
                __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v2 = 1U;
            }
        }
        if ((0x2000U & vlSelfRef.SimTopFPGA__DOT__oreq[2U])) {
            vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h24e30222__0 
                = (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[1U] 
                            >> 2U));
            if ((0x3e7ffU >= (0x3ffffU & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                           + (0xffU 
                                              & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                 >> 0x14U))) 
                                          - (IData)(0x40U))))) {
                __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v3 
                    = vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h24e30222__0;
                __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v3 
                    = (0x3ffffU & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                    + (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                >> 0x14U))) 
                                   - (IData)(0x40U)));
                __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v3 = 1U;
            }
        }
        if ((0x4000U & vlSelfRef.SimTopFPGA__DOT__oreq[2U])) {
            vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h24e30222__0 
                = (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[1U] 
                            >> 0xaU));
            if ((0x3e7ffU >= (0x3ffffU & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                           + (0xffU 
                                              & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                 >> 0x14U))) 
                                          - (IData)(0x40U))))) {
                __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v4 
                    = vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h24e30222__0;
                __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v4 
                    = (0x3ffffU & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                    + (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                >> 0x14U))) 
                                   - (IData)(0x40U)));
                __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v4 = 1U;
            }
        }
        if ((0x8000U & vlSelfRef.SimTopFPGA__DOT__oreq[2U])) {
            vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h24e30222__0 
                = (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[1U] 
                            >> 0x12U));
            if ((0x3e7ffU >= (0x3ffffU & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                           + (0xffU 
                                              & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                 >> 0x14U))) 
                                          - (IData)(0x40U))))) {
                __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v5 
                    = vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h24e30222__0;
                __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v5 
                    = (0x3ffffU & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                    + (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                >> 0x14U))) 
                                   - (IData)(0x40U)));
                __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v5 = 1U;
            }
        }
        if ((0x10000U & vlSelfRef.SimTopFPGA__DOT__oreq[2U])) {
            vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h24e30222__0 
                = (0xffU & ((vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                             << 6U) | (vlSelfRef.SimTopFPGA__DOT__oreq[1U] 
                                       >> 0x1aU)));
            if ((0x3e7ffU >= (0x3ffffU & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                           + (0xffU 
                                              & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                 >> 0x14U))) 
                                          - (IData)(0x40U))))) {
                __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v6 
                    = vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h24e30222__0;
                __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v6 
                    = (0x3ffffU & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                    + (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                >> 0x14U))) 
                                   - (IData)(0x40U)));
                __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v6 = 1U;
            }
        }
        if ((0x20000U & vlSelfRef.SimTopFPGA__DOT__oreq[2U])) {
            vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h24e30222__0 
                = (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                            >> 2U));
            if ((0x3e7ffU >= (0x3ffffU & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                           + (0xffU 
                                              & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                 >> 0x14U))) 
                                          - (IData)(0x40U))))) {
                __VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v7 
                    = vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h24e30222__0;
                __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v7 
                    = (0x3ffffU & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                    + (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                >> 0x14U))) 
                                   - (IData)(0x40U)));
                __VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v7 = 1U;
            }
        }
    }
    if (vlSelfRef.reset) {
        __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_rptr = 0U;
        __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_wptr = 0U;
        __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_count = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__cycle_cnt = 0ULL;
        __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v0 = 1U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_drop_resp_pending = 0U;
    } else {
        if ((((((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txn_fire) 
                & (~ (IData)((0U != (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                              >> 0xaU)))))) 
               & (0x10000000ULL == (((QData)((IData)(
                                                     vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                     << 0x2eU) | (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                   << 0xeU) 
                                                  | ((QData)((IData)(
                                                                     vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                     >> 0x12U))))) 
              & (~ ((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__uart_lcr) 
                    >> 7U))) & (0U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_count)))) {
            __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_rptr 
                = (0x1fU & ((IData)(1U) + (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_rptr)));
        }
        if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxByteReady) 
             & (0x10U > (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_count)))) {
            __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_count 
                = (0x3fU & ((IData)(1U) + (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_count)));
            __VdlyVal__SimTopFPGA__DOT__u_device__DOT__console_rx_fifo__v0 
                = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxByte;
            __VdlyDim0__SimTopFPGA__DOT__u_device__DOT__console_rx_fifo__v0 
                = (0xfU & (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_wptr));
            __VdlySet__SimTopFPGA__DOT__u_device__DOT__console_rx_fifo__v0 = 1U;
            __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_wptr 
                = (0x1fU & ((IData)(1U) + (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_wptr)));
        }
        if ((((((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txn_fire) 
                & (~ (IData)((0U != (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                              >> 0xaU)))))) 
               & (0x10000000ULL == (((QData)((IData)(
                                                     vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                     << 0x2eU) | (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                   << 0xeU) 
                                                  | ((QData)((IData)(
                                                                     vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                     >> 0x12U))))) 
              & (~ ((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__uart_lcr) 
                    >> 7U))) & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_empty)))) {
            __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_count 
                = (0x3fU & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_count) 
                            - (IData)(1U)));
        }
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__cycle_cnt 
            = ((IData)(((0x6c00000U == (0x7ffc000U 
                                        & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                        & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                           >> 0x10U))) ? (((QData)((IData)(
                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                           << 0x32U) 
                                          | (((QData)((IData)(
                                                              vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                              << 0x12U) 
                                             | ((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                >> 0xeU)))
                : (1ULL + vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__cycle_cnt));
        if (((IData)((0x14000U == (0x14000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU]))) 
             & (0U != (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                                >> 9U))))) {
            __VdlyVal__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v32 
                = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[9U])) 
                    << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[8U])) 
                                  << 0x17U) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) 
                                               >> 9U)));
            __VdlyDim0__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v32 
                = (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                            >> 9U));
            __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v32 = 1U;
        }
        if (((((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap) 
               & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_is_insn))) 
              & (5ULL == vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_cause)) 
             & (0x80006140ULL == vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fault_pc))) {
            if ((0x80006000ULL > vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_vaddr)) {
                __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v33 = 1U;
            } else if ((0x80007000ULL <= vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_vaddr)) {
                __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v35 = 1U;
            }
        }
        __VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v36 = 1U;
        if ((1U & ((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__halted)) 
                   & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_commit))))) {
            if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_drop_resp_pending) 
                 & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__iresp_core 
                            >> 0x20U)))) {
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_drop_resp_pending = 0U;
            }
            if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect) 
                 | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mret_redirect))) {
                if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending) {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_drop_resp_pending = 1U;
                }
            } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap) {
                if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending) {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_drop_resp_pending = 1U;
                }
            } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_instr_misalign) {
                if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending) {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_drop_resp_pending = 1U;
                }
            } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_flush_front) {
                if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending) {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_drop_resp_pending = 1U;
                }
            }
        }
    }
    if (vlSelfRef.reset) {
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_trap_count = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_commit_count = 0U;
    } else {
        if ((IData)(((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                      >> 0x10U) & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_commit))))) {
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_commit_count 
                = ((IData)(1U) + vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_commit_count);
            if (VL_UNLIKELY(VL_GTS_III(32, 0x64U, vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_commit_count))) {
                VL_WRITEF_NX("[COMMIT] #%0d pc=0x%016x instr=0x%08x wen=%0b rd=%0#\n",0,
                             32,vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_commit_count,
                             64,(((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU])) 
                                  << 0x37U) | (((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xbU])) 
                                                << 0x17U) 
                                               | ((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU])) 
                                                  >> 9U))),
                             32,((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU] 
                                  << 0x17U) | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[9U] 
                                               >> 9U)),
                             1,(1U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                                      >> 0xeU)),5,(0x1fU 
                                                   & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                                                      >> 9U)));
            }
        }
        if (VL_UNLIKELY(((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect) 
                         & VL_GTS_III(32, 0x14U, vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_trap_count)))) {
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_trap_count 
                = ((IData)(1U) + vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_trap_count);
            VL_WRITEF_NX("[TRAP] #%0d pc=0x%016x redirect_pc=0x%016x mcause=0x%016x mepc=0x%016x mtvec=0x%016x priv=%0#\n",0,
                         32,vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_trap_count,
                         64,((0x10000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU])
                              ? (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU])) 
                                  << 0x37U) | (((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xbU])) 
                                                << 0x17U) 
                                               | ((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xaU])) 
                                                  >> 9U)))
                              : ((0x100000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                                  ? (((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])) 
                                      << 0x38U) | (
                                                   ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU])) 
                                                    << 0x18U) 
                                                   | ((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU])) 
                                                      >> 8U)))
                                  : 0ULL)),64,vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect_pc,
                         64,vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mcause,
                         64,vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mepc,
                         64,vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mtvec,
                         2,(IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode));
        }
        if (VL_UNLIKELY(((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mret_redirect) 
                         & VL_GTS_III(32, 0x32U, vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_trap_count)))) {
            VL_WRITEF_NX("[MRET] pc=0x%016x redirect_pc=0x%016x mepc=0x%016x priv=%0#\n",0,
                         64,((0x10000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU])
                              ? (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU])) 
                                  << 0x37U) | (((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xbU])) 
                                                << 0x17U) 
                                               | ((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xaU])) 
                                                  >> 9U)))
                              : ((0x100000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                                  ? (((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])) 
                                      << 0x38U) | (
                                                   ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU])) 
                                                    << 0x18U) 
                                                   | ((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU])) 
                                                      >> 8U)))
                                  : 0ULL)),64,vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect_pc,
                         64,vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mepc,
                         2,(IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode));
        }
    }
    if (((IData)(vlSelfRef.reset) | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__flush_mmu))) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__req_inflight = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__req_addr_bit2 = 0U;
    } else {
        if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__issue_now) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__req_inflight = 1U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__req_addr_bit2 
                = (1U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[0U] 
                         >> 2U));
        }
        if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__resp_fire) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__req_inflight = 0U;
        }
    }
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__switch = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txn_done_pulse 
        = ((~ ((IData)(vlSelfRef.reset) | (~ (IData)(vlSelfRef.SimTopFPGA__DOT__device_valid)))) 
           & (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txn_fire));
    vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__ready_read 
        = vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__real_valid;
    vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__last_read 
        = vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__real_valid;
    if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__real_valid) 
         & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__is_write)))) {
        vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__bram_rdata 
            = vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__mem
            [(0x3ffffU & (IData)((vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__latched_addr 
                                  >> 3U)))];
    }
    if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__dcvt__reset) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__resp_seen = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__resp_seen = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__req_inflight = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__req_inflight = 0U;
    } else {
        if ((1U & ((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__okay)) 
                   | (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[2U])))) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__resp_seen = 0U;
        }
        if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__resp_fire) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__resp_seen = 1U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__req_inflight = 0U;
        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__issue_now) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__req_inflight = 1U;
        } else if ((1U & (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[2U]))) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__req_inflight = 0U;
        }
        if ((1U & ((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__okay)) 
                   | (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[4U] 
                         >> 0xbU))))) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__resp_seen = 0U;
        }
        if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__resp_fire) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__resp_seen = 1U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__req_inflight = 0U;
        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__issue_now) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__req_inflight = 1U;
        } else if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[4U] 
                             >> 0xbU)))) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__req_inflight = 0U;
        }
    }
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__bitIndex 
        = __Vdly__SimTopFPGA__DOT__u_device__DOT__bitIndex;
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__bitTmr 
        = __Vdly__SimTopFPGA__DOT__u_device__DOT__bitTmr;
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txState 
        = __Vdly__SimTopFPGA__DOT__u_device__DOT__txState;
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__mtime_div 
        = __Vdly__SimTopFPGA__DOT__u_device__DOT__mtime_div;
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__mtime 
        = __Vdly__SimTopFPGA__DOT__u_device__DOT__mtime;
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__fifo_count 
        = __Vdly__SimTopFPGA__DOT__u_device__DOT__fifo_count;
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__gen_dbg_live__DOT__dbg_live_count 
        = __Vdly__SimTopFPGA__DOT__u_device__DOT__gen_dbg_live__DOT__dbg_live_count;
    vlSelfRef.SimTopFPGA__DOT__dbg_cycle_count = __Vdly__SimTopFPGA__DOT__dbg_cycle_count;
    vlSelfRef.SimTopFPGA__DOT__dbg_device_access_count 
        = __Vdly__SimTopFPGA__DOT__dbg_device_access_count;
    vlSelfRef.SimTopFPGA__DOT__dbg_ram_access_count 
        = __Vdly__SimTopFPGA__DOT__dbg_ram_access_count;
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_rptr 
        = __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_rptr;
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_wptr 
        = __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_wptr;
    if (__VdlySet__SimTopFPGA__DOT__u_device__DOT__console_rx_fifo__v0) {
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_fifo[__VdlyDim0__SimTopFPGA__DOT__u_device__DOT__console_rx_fifo__v0] 
            = __VdlyVal__SimTopFPGA__DOT__u_device__DOT__console_rx_fifo__v0;
    }
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_count 
        = __Vdly__SimTopFPGA__DOT__u_device__DOT__console_rx_count;
    if (__VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v0) {
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem[__VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v0] 
            = ((0xffffff00U & vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem
                [__VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v0]) 
               | (IData)(__VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v0));
    }
    if (__VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v1) {
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem[__VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v1] 
            = ((0xffff00ffU & vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem
                [__VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v1]) 
               | ((IData)(__VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v1) 
                  << 8U));
    }
    if (__VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v2) {
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem[__VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v2] 
            = ((0xff00ffffU & vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem
                [__VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v2]) 
               | ((IData)(__VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v2) 
                  << 0x10U));
    }
    if (__VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v3) {
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem[__VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v3] 
            = ((0xffffffU & vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem
                [__VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v3]) 
               | ((IData)(__VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v3) 
                  << 0x18U));
    }
    if (__VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v4) {
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem[__VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v4] 
            = ((0xffffff00U & vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem
                [__VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v4]) 
               | (IData)(__VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v4));
    }
    if (__VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v5) {
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem[__VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v5] 
            = ((0xffff00ffU & vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem
                [__VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v5]) 
               | ((IData)(__VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v5) 
                  << 8U));
    }
    if (__VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v6) {
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem[__VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v6] 
            = ((0xff00ffffU & vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem
                [__VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v6]) 
               | ((IData)(__VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v6) 
                  << 0x10U));
    }
    if (__VdlySet__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v7) {
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem[__VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v7] 
            = ((0xffffffU & vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem
                [__VdlyDim0__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v7]) 
               | ((IData)(__VdlyVal__SimTopFPGA__DOT__u_device__DOT__sim_disk_mem__v7) 
                  << 0x18U));
    }
    if (__VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v0) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[1U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[2U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[3U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[4U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[5U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[6U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[7U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[8U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[9U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0xaU] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0xbU] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0xcU] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0xdU] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0xeU] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0xfU] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0x10U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0x11U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0x12U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0x13U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0x14U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0x15U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0x16U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0x17U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0x18U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0x19U] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0x1aU] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0x1bU] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0x1cU] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0x1dU] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0x1eU] = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0x1fU] = 0ULL;
    }
    if (__VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v32) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[__VdlyDim0__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v32] 
            = __VdlyVal__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v32;
    }
    if (__VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v33) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[5U] = 0x8001b860ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0xaU] = 0x200ULL;
    }
    if (__VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v35) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[5U] = 0x8001b860ULL;
    }
    if (__VdlySet__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr__v36) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[0U] = 0ULL;
    }
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_drop_resp_pending 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_drop_resp_pending;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_trap_count 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_trap_count;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_commit_count 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_commit_count;
    if (__VdlySet__SimTopFPGA__DOT__u_bram__DOT__mem__v0) {
        vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__mem[__VdlyDim0__SimTopFPGA__DOT__u_bram__DOT__mem__v0] 
            = __VdlyVal__SimTopFPGA__DOT__u_bram__DOT__mem__v0;
    }
    vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__real_valid 
        = __Vdly__SimTopFPGA__DOT__u_bram__DOT__real_valid;
    if (vlSelfRef.reset) {
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_rdy = 1U;
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__uart_ier = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__uart_ier = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_valid = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_req[0U] = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_req[1U] = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_req[2U] = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_req[3U] = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_req[4U] = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_select = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_valid 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_valid;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_valid = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_result = 0ULL;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_cmd = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_acc = 0ULL;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_a = 0ULL;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_b = 0ULL;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[0U] = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[1U] = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[2U] = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_quot = 0ULL;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_divisor = 0ULL;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_signed = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_is_rem = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_q_neg = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_r_neg = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_cmd 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_cmd;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_acc 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_acc;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_a 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_a;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_b 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_b;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[0U] 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[0U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[1U] 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[1U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[2U] 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[2U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_quot 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_quot;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_divisor 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_divisor;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_signed 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_signed;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_is_rem 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_is_rem;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_q_neg 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_q_neg;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_r_neg 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_r_neg;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_is_insn = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_wdata = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_wstrb = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_size = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pte_addr = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_pte = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_level = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__trap_pending = 0U;
    } else {
        if ((((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txn_fire) 
              & (0U != (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                 >> 0xaU)))) & (0x10001000ULL 
                                                == 
                                                (((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                                  << 0x2eU) 
                                                 | (((QData)((IData)(
                                                                     vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                     << 0xeU) 
                                                    | ((QData)((IData)(
                                                                       vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                       >> 0x12U)))))) {
            vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_rdy = 1U;
        }
        if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txn_fire) 
             & (0U != (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                >> 0xaU))))) {
            if ((0x10000000ULL != (((QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                    << 0x2eU) | (((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                  << 0xeU) 
                                                 | ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                    >> 0x12U))))) {
                if ((0x10000001ULL == (((QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                        << 0x2eU) | 
                                       (((QData)((IData)(
                                                         vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                         << 0xeU) | 
                                        ((QData)((IData)(
                                                         vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                         >> 0x12U))))) {
                    if ((1U & (~ ((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__uart_lcr) 
                                  >> 7U)))) {
                        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__uart_ier 
                            = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__tx_write_byte;
                    }
                }
            }
        }
        if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_valid) {
            if ((IData)((3U == vlSelfRef.SimTopFPGA__DOT__oresp[2U]))) {
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_valid = 0U;
            }
        } else if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__any_valid) 
                    & (~ (IData)((3U == vlSelfRef.SimTopFPGA__DOT__oresp[2U]))))) {
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_valid = 1U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_req[0U] 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[0U];
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_req[1U] 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[1U];
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_req[2U] 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[2U];
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_req[3U] 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[3U];
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_req[4U] 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[4U];
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_select 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select;
        }
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_valid 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_valid;
        if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_commit) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_valid = 0U;
        }
        if ((1U & ((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__halted)) 
                   & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_commit))))) {
            if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect) 
                 | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mret_redirect))) {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_valid = 0U;
            } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap) {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_valid = 0U;
            } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_instr_misalign) {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_valid = 0U;
            } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_flush_front) {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_valid = 0U;
            }
            if ((1U & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_flush_front)))) {
                if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_resp_to_buf) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_valid = 1U;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pop_buf) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_valid = 0U;
                }
            }
        }
        if ((0x20000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask = 0xffffffffULL;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_steps = 0x20U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__sign_bit = 0x1fU;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_eff 
                = (QData)((IData)(((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU] 
                                    << 0x18U) | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U] 
                                                 >> 8U))));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op2_eff 
                = (QData)((IData)(((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U] 
                                    << 0x18U) | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
                                                 >> 8U))));
        } else {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask = 0xffffffffffffffffULL;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_steps = 0x40U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__sign_bit = 0x3fU;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_eff 
                = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
                    << 0x38U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                                  << 0x18U) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                               >> 8U)));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op2_eff 
                = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                    << 0x38U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U])) 
                                  << 0x18U) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U])) 
                                               >> 8U)));
        }
        if (((((((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__halted)) 
                 & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_commit))) 
                & (~ ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_ex_busy) 
                      | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_mem_busy) 
                         | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT____VdfgRegularize_h47660625_0_12))))) 
               & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                  >> 0x14U)) & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_req)) 
             & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid))) {
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid = 0U;
        }
        if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy) {
            if ((0xaU == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_cmd))) {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_acc_next 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_acc;
                if ((1U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_b))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_acc_next 
                        = ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_acc 
                            + vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_a) 
                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                }
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_a_next 
                    = (VL_SHIFTL_QQI(64,64,32, vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_a, 1U) 
                       & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_b_next 
                    = VL_SHIFTR_QQI(64,64,32, vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_b, 1U);
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_acc 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_acc_next;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_a 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_a_next;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_b 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_b_next;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left 
                    = (0x7fU & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left) 
                                - (IData)(1U)));
                if ((1U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left))) {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy = 0U;
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_result 
                        = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word)
                            ? (((QData)((IData)((- (IData)(
                                                           (1U 
                                                            & (IData)(
                                                                      (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_acc_next 
                                                                       >> 0x1fU))))))) 
                                << 0x20U) | (QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_acc_next)))
                            : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_acc_next);
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid = 1U;
                } else if ((0ULL == vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_b_next)) {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy = 0U;
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_result 
                        = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word)
                            ? (((QData)((IData)((- (IData)(
                                                           (1U 
                                                            & (IData)(
                                                                      (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_acc_next 
                                                                       >> 0x1fU))))))) 
                                << 0x20U) | (QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_acc_next)))
                            : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_acc_next);
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid = 1U;
                }
            } else {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_rem_next[0U] 
                    = (((IData)((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[1U])) 
                                  << 0x20U) | (QData)((IData)(
                                                              vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[0U])))) 
                        << 1U) | (1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_quot 
                                                >> 0x3fU))));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_rem_next[1U] 
                    = (((IData)((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[1U])) 
                                  << 0x20U) | (QData)((IData)(
                                                              vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[0U])))) 
                        >> 0x1fU) | ((IData)(((((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[1U])) 
                                                << 0x20U) 
                                               | (QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[0U]))) 
                                              >> 0x20U)) 
                                     << 1U));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_rem_next[2U] 
                    = ((IData)(((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[1U])) 
                                  << 0x20U) | (QData)((IData)(
                                                              vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[0U]))) 
                                >> 0x20U)) >> 0x1fU);
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_quot_next 
                    = (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_quot 
                       << 1U);
                __Vtemp_2[0U] = (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_divisor);
                __Vtemp_2[1U] = (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_divisor 
                                         >> 0x20U));
                __Vtemp_2[2U] = 0U;
                if (VL_GTE_W(3, vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_rem_next, __Vtemp_2)) {
                    __Vtemp_5[0U] = (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_divisor);
                    __Vtemp_5[1U] = (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_divisor 
                                             >> 0x20U));
                    __Vtemp_5[2U] = 0U;
                    VL_SUB_W(3, __Vtemp_6, vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_rem_next, __Vtemp_5);
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_rem_next[0U] 
                        = __Vtemp_6[0U];
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_rem_next[1U] 
                        = __Vtemp_6[1U];
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_rem_next[2U] 
                        = (1U & __Vtemp_6[2U]);
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_quot_next 
                        = (1ULL | vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_quot_next);
                }
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[0U] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_rem_next[0U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[1U] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_rem_next[1U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[2U] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_rem_next[2U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_quot 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_quot_next;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left 
                    = (0x7fU & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left) 
                                - (IData)(1U)));
                if ((1U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__q_unsigned 
                        = (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_quot_next 
                           & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word)
                               ? 0xffffffffULL : 0xffffffffffffffffULL));
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__r_unsigned 
                        = ((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_rem_next[1U])) 
                             << 0x20U) | (QData)((IData)(
                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_rem_next[0U]))) 
                           & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word)
                               ? 0xffffffffULL : 0xffffffffffffffffULL));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy = 0U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid = 1U;
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                        = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_is_rem)
                            ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__r_unsigned
                            : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__q_unsigned);
                    if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_signed) {
                        if (((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_is_rem)) 
                             & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_q_neg))) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                                = ((1ULL + (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__q_unsigned)) 
                                   & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word)
                                       ? 0xffffffffULL
                                       : 0xffffffffffffffffULL));
                        }
                        if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_is_rem) 
                             & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_r_neg))) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                                = ((1ULL + (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__r_unsigned)) 
                                   & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word)
                                       ? 0xffffffffULL
                                       : 0xffffffffffffffffULL));
                        }
                    }
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_result 
                        = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word)
                            ? (((QData)((IData)((- (IData)(
                                                           (1U 
                                                            & (IData)(
                                                                      (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                                                                       >> 0x1fU))))))) 
                                << 0x20U) | (QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val)))
                            : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val);
                }
            }
        } else if (((((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__halted)) 
                      & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                         >> 0x14U)) & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_req)) 
                    & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid)))) {
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_cmd 
                = (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                           >> 0xdU));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word 
                = (1U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                         >> 0x11U));
            if ((0xaU == (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                  >> 0xdU)))) {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_src0 
                    = (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_eff 
                       & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_src1 
                    = (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op2_eff 
                       & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                if (((0ULL == vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_src0) 
                     | (0ULL == vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_src1))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val = 0ULL;
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_result = 0ULL;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid = 1U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy = 0U;
                } else if ((1ULL == vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_src0)) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_src1;
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_result 
                        = ((0x20000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                            ? (((QData)((IData)((- (IData)(
                                                           (1U 
                                                            & (IData)(
                                                                      (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                                                                       >> 0x1fU))))))) 
                                << 0x20U) | (QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val)))
                            : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val);
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid = 1U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy = 0U;
                } else if ((1ULL == vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_src1)) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_src0;
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_result 
                        = ((0x20000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                            ? (((QData)((IData)((- (IData)(
                                                           (1U 
                                                            & (IData)(
                                                                      (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                                                                       >> 0x1fU))))))) 
                                << 0x20U) | (QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val)))
                            : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val);
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid = 1U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy = 0U;
                } else {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy = 1U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_steps;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_acc = 0ULL;
                    if ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_src0 
                         <= vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_src1)) {
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_a 
                            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_src1;
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_b 
                            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_src0;
                    } else {
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_a 
                            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_src0;
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_b 
                            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_src1;
                    }
                }
            } else {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_signed 
                    = ((0xbU == (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                         >> 0xdU))) 
                       | (0xdU == (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                           >> 0xdU))));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_rem 
                    = ((0xdU == (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                         >> 0xdU))) 
                       | (0xeU == (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                           >> 0xdU))));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_signed 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_signed;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_is_rem 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_rem;
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_neg 
                    = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_signed) 
                       & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_eff 
                                  >> (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__sign_bit))));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op2_neg 
                    = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_signed) 
                       & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op2_eff 
                                  >> (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__sign_bit))));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__dividend_abs 
                    = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_neg)
                        ? ((1ULL + (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_eff)) 
                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask)
                        : (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_eff 
                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                    = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op2_neg)
                        ? ((1ULL + (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op2_eff)) 
                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask)
                        : (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op2_eff 
                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_pow2 
                    = (0ULL == (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   - 1ULL)));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0U;
                if ((1U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 1U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 1U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 2U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 2U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 3U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 3U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 4U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 4U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 5U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 5U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 6U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 6U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 7U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 7U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 8U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 8U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 9U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 9U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0xaU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0xaU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0xbU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0xbU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0xcU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0xcU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0xdU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0xdU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0xeU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0xeU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0xfU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0xfU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x10U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x10U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x11U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x11U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x12U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x12U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x13U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x13U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x14U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x14U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x15U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x15U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x16U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x16U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x17U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x17U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x18U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x18U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x19U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x19U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x1aU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x1aU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x1bU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x1bU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x1cU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x1cU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x1dU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x1dU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x1eU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x1eU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x1fU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x1fU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x20U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x20U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x21U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x21U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x22U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x22U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x23U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x23U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x24U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x24U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x25U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x25U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x26U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x26U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x27U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x27U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x28U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x28U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x29U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x29U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x2aU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x2aU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x2bU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x2bU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x2cU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x2cU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x2dU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x2dU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x2eU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x2eU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x2fU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x2fU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x30U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x30U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x31U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x31U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x32U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x32U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x33U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x33U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x34U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x34U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x35U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x35U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x36U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x36U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x37U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x37U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x38U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x38U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x39U)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x39U;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x3aU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x3aU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x3bU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x3bU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x3cU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x3cU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x3dU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x3dU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x3eU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x3eU;
                }
                if ((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                                   >> 0x3fU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = 0x3fU;
                }
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_mask 
                    = ((0U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift))
                        ? 0ULL : ((1ULL << (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift)) 
                                  - 1ULL));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_q_neg 
                    = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_neg) 
                       ^ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op2_neg));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_r_neg 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_neg;
                if ((0ULL == (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op2_eff 
                              & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                        = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_rem)
                            ? (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_eff 
                               & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask)
                            : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_result 
                        = ((0x20000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                            ? (((QData)((IData)((- (IData)(
                                                           (1U 
                                                            & (IData)(
                                                                      (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                                                                       >> 0x1fU))))))) 
                                << 0x20U) | (QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val)))
                            : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val);
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid = 1U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy = 0U;
                } else if (((((0xbU == (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                                >> 0xdU))) 
                              | (0xdU == (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                                  >> 0xdU)))) 
                             & ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_eff 
                                 & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask) 
                                == ((0x20000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                                     ? 0x80000000ULL
                                     : 0x8000000000000000ULL))) 
                            & ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op2_eff 
                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask) 
                               == ((0x20000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                                    ? 0xffffffffULL
                                    : 0xffffffffffffffffULL)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                        = ((0xbU == (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                             >> 0xdU)))
                            ? (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_eff 
                               & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask)
                            : 0ULL);
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_result 
                        = ((0x20000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                            ? (((QData)((IData)((- (IData)(
                                                           (1U 
                                                            & (IData)(
                                                                      (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                                                                       >> 0x1fU))))))) 
                                << 0x20U) | (QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val)))
                            : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val);
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid = 1U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy = 0U;
                } else if ((0ULL == vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__dividend_abs)) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val = 0ULL;
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_result = 0ULL;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid = 1U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy = 0U;
                } else if ((1ULL == vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs)) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_q_abs_fast 
                        = (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__dividend_abs 
                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_r_abs_fast = 0ULL;
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__q_unsigned 
                        = (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_q_abs_fast 
                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__r_unsigned = 0ULL;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid = 1U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy = 0U;
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                        = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_rem)
                            ? 0ULL : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__q_unsigned);
                    if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_signed) {
                        if (((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_rem)) 
                             & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_neg) 
                                ^ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op2_neg)))) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                                = ((1ULL + (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__q_unsigned)) 
                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                        }
                        if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_rem) 
                             & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_neg))) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                                = ((1ULL + (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__r_unsigned)) 
                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                        }
                    }
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_result 
                        = ((0x20000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                            ? (((QData)((IData)((- (IData)(
                                                           (1U 
                                                            & (IData)(
                                                                      (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                                                                       >> 0x1fU))))))) 
                                << 0x20U) | (QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val)))
                            : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val);
                } else if ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__dividend_abs 
                            < vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs)) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_r_abs_fast 
                        = (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__dividend_abs 
                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_q_abs_fast = 0ULL;
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__q_unsigned = 0ULL;
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__r_unsigned 
                        = (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_r_abs_fast 
                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid = 1U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy = 0U;
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                        = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_rem)
                            ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__r_unsigned
                            : 0ULL);
                    if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_signed) {
                        if (((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_rem)) 
                             & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_neg) 
                                ^ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op2_neg)))) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                                = ((1ULL + (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__q_unsigned)) 
                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                        }
                        if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_rem) 
                             & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_neg))) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                                = ((1ULL + (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__r_unsigned)) 
                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                        }
                    }
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_result 
                        = ((0x20000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                            ? (((QData)((IData)((- (IData)(
                                                           (1U 
                                                            & (IData)(
                                                                      (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                                                                       >> 0x1fU))))))) 
                                << 0x20U) | (QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val)))
                            : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val);
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_pow2) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_q_abs_fast 
                        = ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__dividend_abs 
                            >> (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift)) 
                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_r_abs_fast 
                        = (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__dividend_abs 
                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_mask);
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__q_unsigned 
                        = (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_q_abs_fast 
                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid = 1U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy = 0U;
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__r_unsigned 
                        = (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_r_abs_fast 
                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                        = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_rem)
                            ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__r_unsigned
                            : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__q_unsigned);
                    if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_signed) {
                        if (((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_rem)) 
                             & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_neg) 
                                ^ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op2_neg)))) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                                = ((1ULL + (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__q_unsigned)) 
                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                        }
                        if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_rem) 
                             & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_neg))) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                                = ((1ULL + (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__r_unsigned)) 
                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                        }
                    }
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_result 
                        = ((0x20000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                            ? (((QData)((IData)((- (IData)(
                                                           (1U 
                                                            & (IData)(
                                                                      (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val 
                                                                       >> 0x1fU))))))) 
                                << 0x20U) | (QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val)))
                            : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val);
                } else {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy = 1U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_steps;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[0U] = 0U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[1U] = 0U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[2U] = 0U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_quot 
                        = VL_SHIFTL_QQI(64,64,7, (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__dividend_abs 
                                                  & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask), 
                                        (0x7fU & ((IData)(0x40U) 
                                                  - (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_steps))));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_divisor 
                        = (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs 
                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask);
                }
            }
        }
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_cmd 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_cmd;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_acc 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_acc;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_a 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_a;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_b 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_b;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[0U] 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[0U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[1U] 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[1U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[2U] 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem[2U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_quot 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_quot;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_divisor 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_divisor;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_signed 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_signed;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_is_rem 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_is_rem;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_q_neg 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_q_neg;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_r_neg 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_r_neg;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid 
            = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid;
        if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__flush_mmu) {
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state = 0U;
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_is_insn = 0U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr = 0ULL;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_wdata = 0ULL;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_wstrb = 0U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_size = 0U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pte_addr = 0ULL;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_pte = 0ULL;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_level = 0U;
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__trap_pending = 0U;
        } else if ((4U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state))) {
            if ((2U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state))) {
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state = 0U;
            } else if ((1U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state))) {
                if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[2U])) {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state = 0U;
                }
            } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__resp_fire) {
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state = 0U;
            }
        } else if ((2U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state))) {
            if ((1U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state))) {
                if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[2U])) {
                    if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[0U])) {
                        if ((IData)((0U != (0xeU & 
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[0U])))) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_pte 
                                = (((QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[1U])) 
                                    << 0x20U) | (QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[0U])));
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_level = 0U;
                            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state 
                                = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_is_insn)
                                    ? 4U : 5U);
                        } else {
                            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state = 0U;
                        }
                    } else {
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state = 0U;
                    }
                }
            } else if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[2U])) {
                if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[0U])) {
                    if ((IData)((0U != (0xeU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[0U])))) {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_pte 
                            = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[1U])) 
                                << 0x20U) | (QData)((IData)(
                                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[0U])));
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_level = 1U;
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state 
                            = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_is_insn)
                                ? 4U : 5U);
                    } else {
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state = 3U;
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pte_addr 
                            = ((0xfffffffffff000ULL 
                                & (((QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[1U])) 
                                    << 0x22U) | (0xfffffffffffff000ULL 
                                                 & ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[0U])) 
                                                    << 2U)))) 
                               | (QData)((IData)(((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__vpn0) 
                                                  << 3U))));
                    }
                } else {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state = 0U;
                }
            }
        } else if ((1U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state))) {
            if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[2U])) {
                if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[0U])) {
                    if ((IData)((0U != (0xeU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[0U])))) {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_pte 
                            = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[1U])) 
                                << 0x20U) | (QData)((IData)(
                                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[0U])));
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_level = 2U;
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state 
                            = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_is_insn)
                                ? 4U : 5U);
                    } else {
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state = 2U;
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pte_addr 
                            = ((0xfffffffffff000ULL 
                                & (((QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[1U])) 
                                    << 0x22U) | (0xfffffffffffff000ULL 
                                                 & ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[0U])) 
                                                    << 2U)))) 
                               | (QData)((IData)(((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__vpn1) 
                                                  << 3U))));
                    }
                } else {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state = 0U;
                }
            }
        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__trap_pending) {
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__trap_pending 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__trap_pending;
        } else {
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__trap_pending = 0U;
            if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__translate_en) 
                 & (3U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)))) {
                if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_core[2U])) {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state = 1U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_is_insn = 1U;
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr 
                        = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_core[1U])) 
                            << 0x20U) | (QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_core[0U])));
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pte_addr 
                        = ((0xfffffffffff000ULL & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_satp 
                                                   << 0xcU)) 
                           | (QData)((IData)((0xff8U 
                                              & ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_core[1U] 
                                                  << 5U) 
                                                 | (0x18U 
                                                    & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_core[0U] 
                                                       >> 0x1bU)))))));
                } else if ((0x800U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[4U])) {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state = 1U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_is_insn = 0U;
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr 
                        = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[4U])) 
                            << 0x35U) | (((QData)((IData)(
                                                          vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[3U])) 
                                          << 0x15U) 
                                         | ((QData)((IData)(
                                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[2U])) 
                                            >> 0xbU)));
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_wdata 
                        = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[1U])) 
                            << 0x20U) | (QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[0U])));
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_wstrb 
                        = (0xffU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[2U]);
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_size 
                        = (7U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[2U] 
                                 >> 8U));
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pte_addr 
                        = ((0xfffffffffff000ULL & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_satp 
                                                   << 0xcU)) 
                           | (QData)((IData)((0xff8U 
                                              & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[3U] 
                                                 >> 6U)))));
                }
            }
        }
    }
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__trap_pending 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__trap_pending;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_is_insn 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_is_insn;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state;
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__bitDone 
        = (0xd8U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__bitTmr));
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__fifo_full 
        = (0x40U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__fifo_count));
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__tx_start 
        = ((0U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__fifo_count)) 
           & (0U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txState)));
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_empty 
        = (0U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_count));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__vpn1 
        = (0x1ffU & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr 
                             >> 0x15U)));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__vpn0 
        = (0x1ffU & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr 
                             >> 0xcU)));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__phys_addr 
        = ((2U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_level))
            ? (((QData)((IData)((0xffffffU & (IData)(
                                                     (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_pte 
                                                      >> 0x1eU))))) 
                << 0x1eU) | (QData)((IData)((0x3fffffffU 
                                             & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr)))))
            : ((1U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_level))
                ? ((0x3fffffffe00000ULL & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_pte) 
                   | (QData)((IData)((0x1fffffU & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr)))))
                : ((0U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_level))
                    ? ((0xfffffffffff000ULL & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_pte 
                                               << 2U)) 
                       | (QData)((IData)((0xfffU & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr)))))
                    : 0ULL)));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__walk_active 
        = ((1U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state)) 
           | ((2U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state)) 
              | (3U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state))));
    if (vlSelfRef.reset) {
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__dbg_ever_uart_write_reg = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__dbg_ever_device_read_reg = 0U;
        __Vdly__SimTopFPGA__DOT__u_device__DOT__rxState = 0U;
        __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitIndex = 0U;
        __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitTmr = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxByteReady = 0U;
        __Vdly__SimTopFPGA__DOT__u_device__DOT__rxShiftReg = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxByte = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__uart_lcr = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__uart_lcr = 0U;
        __Vdly__SimTopFPGA__DOT__u_bram__DOT__counter = 0U;
        __Vdly__SimTopFPGA__DOT__u_bram__DOT__txn_active = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__latched_addr = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__latched_wdata = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__latched_wstrobe = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__is_write = 0U;
    } else {
        if (((((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txn_fire) 
               & (0U != (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                  >> 0xaU)))) & (0x10000000ULL 
                                                 <= 
                                                 (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                                   << 0x2eU) 
                                                  | (((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                      << 0xeU) 
                                                     | ((QData)((IData)(
                                                                        vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                        >> 0x12U))))) 
             & (0x10000005ULL >= (((QData)((IData)(
                                                   vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                   << 0x2eU) | (((QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                 << 0xeU) 
                                                | ((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                   >> 0x12U)))))) {
            vlSelfRef.SimTopFPGA__DOT__u_device__DOT__dbg_ever_uart_write_reg = 1U;
        }
        if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txn_fire) 
             & (~ (IData)((0U != (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                           >> 0xaU))))))) {
            vlSelfRef.SimTopFPGA__DOT__u_device__DOT__dbg_ever_device_read_reg = 1U;
        }
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxByteReady = 0U;
        if ((2U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxState))) {
            if ((1U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxState))) {
                __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitTmr 
                    = (0x3fffU & ((IData)(1U) + (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBitTmr)));
                if ((0xd8U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBitTmr))) {
                    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxByte 
                        = (0xffU & (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxShiftReg));
                    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxByteReady = 1U;
                    __Vdly__SimTopFPGA__DOT__u_device__DOT__rxState = 0U;
                }
            } else {
                __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitTmr 
                    = (0x3fffU & ((IData)(1U) + (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBitTmr)));
                if ((0xd8U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBitTmr))) {
                    vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h99cc83ff__0 
                        = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBit;
                    __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitTmr = 0U;
                    if ((9U >= (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBitIndex))) {
                        __Vdly__SimTopFPGA__DOT__u_device__DOT__rxShiftReg 
                            = (((~ ((IData)(1U) << (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBitIndex))) 
                                & (IData)(__Vdly__SimTopFPGA__DOT__u_device__DOT__rxShiftReg)) 
                               | (0x3ffU & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vlvbound_h99cc83ff__0) 
                                            << (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBitIndex))));
                    }
                    if ((7U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBitIndex))) {
                        __Vdly__SimTopFPGA__DOT__u_device__DOT__rxState = 3U;
                    } else {
                        __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitIndex 
                            = (0xfU & ((IData)(1U) 
                                       + (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBitIndex)));
                    }
                }
            }
        } else if ((1U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxState))) {
            __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitTmr 
                = (0x3fffU & ((IData)(1U) + (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBitTmr)));
            if ((0x6cU == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBitTmr))) {
                if (vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBit) {
                    __Vdly__SimTopFPGA__DOT__u_device__DOT__rxState = 0U;
                } else {
                    __Vdly__SimTopFPGA__DOT__u_device__DOT__rxState = 2U;
                    __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitIndex = 0U;
                    __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitTmr = 0U;
                }
            }
        } else if ((1U & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBit)))) {
            __Vdly__SimTopFPGA__DOT__u_device__DOT__rxState = 1U;
            __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitTmr = 0U;
        }
        if ((((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txn_fire) 
              & (0U != (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                 >> 0xaU)))) & (0x10001000ULL 
                                                == 
                                                (((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                                  << 0x2eU) 
                                                 | (((QData)((IData)(
                                                                     vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                     << 0xeU) 
                                                    | ((QData)((IData)(
                                                                       vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                       >> 0x12U)))))) {
            vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno 
                = ((vlSelfRef.SimTopFPGA__DOT__oreq[1U] 
                    << 0x16U) | (vlSelfRef.SimTopFPGA__DOT__oreq[0U] 
                                 >> 0xaU));
        }
        if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txn_fire) 
             & (0U != (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                >> 0xaU))))) {
            if ((0x10000000ULL != (((QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                    << 0x2eU) | (((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                  << 0xeU) 
                                                 | ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                    >> 0x12U))))) {
                if ((0x10000001ULL != (((QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                        << 0x2eU) | 
                                       (((QData)((IData)(
                                                         vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                         << 0xeU) | 
                                        ((QData)((IData)(
                                                         vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                         >> 0x12U))))) {
                    if ((0x10000002ULL != (((QData)((IData)(
                                                            vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                            << 0x2eU) 
                                           | (((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                               << 0xeU) 
                                              | ((QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                 >> 0x12U))))) {
                        if ((0x10000003ULL == (((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                                << 0x2eU) 
                                               | (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                   << 0xeU) 
                                                  | ((QData)((IData)(
                                                                     vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                     >> 0x12U))))) {
                            vlSelfRef.SimTopFPGA__DOT__u_device__DOT__uart_lcr 
                                = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__tx_write_byte;
                        }
                    }
                }
            }
        }
        if (vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__txn_active) {
            if (vlSelfRef.SimTopFPGA__DOT__ram_last) {
                __Vdly__SimTopFPGA__DOT__u_bram__DOT__counter = 0U;
                __Vdly__SimTopFPGA__DOT__u_bram__DOT__txn_active = 0U;
            } else if ((2U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__counter))) {
                __Vdly__SimTopFPGA__DOT__u_bram__DOT__counter 
                    = (0xffffU & ((IData)(1U) + (IData)(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__counter)));
            }
        } else {
            __Vdly__SimTopFPGA__DOT__u_bram__DOT__counter = 0U;
            if (vlSelfRef.SimTopFPGA__DOT__ram_valid) {
                __Vdly__SimTopFPGA__DOT__u_bram__DOT__txn_active = 1U;
                vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__latched_addr 
                    = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                        << 0x2eU) | (((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                      << 0xeU) | ((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                  >> 0x12U)));
                vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__latched_wdata 
                    = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                        << 0x36U) | (((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__oreq[1U])) 
                                      << 0x16U) | ((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__oreq[0U])) 
                                                   >> 0xaU)));
                vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__latched_wstrobe 
                    = (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                >> 0xaU));
                vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__is_write 
                    = (0U != (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                       >> 0xaU)));
            }
        }
    }
    if (vlSelfRef.reset) {
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mtvec = 0ULL;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mip_raw = 0ULL;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mie = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mscratch = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mcause = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mtval = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mepc = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_satp = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_stvec_r = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_sscratch_r = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_sepc_r = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_scause_r = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_stval_r = 0ULL;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mideleg_r = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mcounteren_r = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_menvcfg_r = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpcfg0_r = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpaddr0_r = 0ULL;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode = 3U;
    } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ecall) {
        if (([&]() {
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__4__mode 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__4__Vfuncout 
                        = ((0U == (IData)(__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__4__mode))
                            ? 8ULL : ((1U == (IData)(__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__4__mode))
                                       ? 9ULL : 0xbULL));
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__3__cause 
                        = __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__4__Vfuncout;
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__3__Vfuncout 
                        = ((3U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
                           && (1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r 
                                             >> (0x3fU 
                                                 & (IData)(__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__3__cause))))));
                }(), (IData)(__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__3__Vfuncout))) {
            __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__5__mode 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
            __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__5__Vfuncout 
                = ((0U == (IData)(__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__5__mode))
                    ? 8ULL : ((1U == (IData)(__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__5__mode))
                               ? 9ULL : 0xbULL));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_sepc_r 
                = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU])) 
                    << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xbU])) 
                                  << 0x17U) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU])) 
                                               >> 9U)));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_scause_r 
                = __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__5__Vfuncout;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_stval_r = 0ULL;
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffffdfULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                     >> 1U))))) 
                      << 5U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = (0xfffffffffffffffdULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus);
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xfffffffffffffeffULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)))) 
                      << 8U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode = 1U;
        } else {
            __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__6__mode 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
            __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__6__Vfuncout 
                = ((0U == (IData)(__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__6__mode))
                    ? 8ULL : ((1U == (IData)(__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__6__mode))
                               ? 9ULL : 0xbULL));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mepc 
                = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU])) 
                    << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xbU])) 
                                  << 0x17U) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU])) 
                                               >> 9U)));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mcause 
                = __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__6__Vfuncout;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mtval = 0ULL;
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffff7fULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                     >> 3U))))) 
                      << 7U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = (0xfffffffffffffff7ULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus);
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffe7ffULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
                      << 0xbU));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode = 3U;
        }
    } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap) {
        if (([&]() {
                    {
                        if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap) {
                            __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__8__Vfuncout 
                                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_cause;
                            goto __Vlabel1;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ecall) {
                            __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__9__mode 
                                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                            __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__9__Vfuncout 
                                = ((0U == (IData)(__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__9__mode))
                                    ? 8ULL : ((1U == (IData)(__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__9__mode))
                                               ? 9ULL
                                               : 0xbULL));
                            __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__8__Vfuncout 
                                = __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__9__Vfuncout;
                            goto __Vlabel1;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ebreak) {
                            __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__8__Vfuncout = 3ULL;
                            goto __Vlabel1;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_illegal) {
                            __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__8__Vfuncout = 2ULL;
                            goto __Vlabel1;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_instr) {
                            __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__8__Vfuncout = 0ULL;
                            goto __Vlabel1;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_data) {
                            if ((0x80U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) {
                                __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__8__Vfuncout = 6ULL;
                                goto __Vlabel1;
                            } else {
                                __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__8__Vfuncout = 4ULL;
                                goto __Vlabel1;
                            }
                        }
                        __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__8__Vfuncout = 0ULL;
                        __Vlabel1: ;
                    }
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__7__cause 
                        = __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__8__Vfuncout;
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__7__Vfuncout 
                        = ((3U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
                           && (1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r 
                                             >> (0x3fU 
                                                 & (IData)(__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__7__cause))))));
                }(), (IData)(__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__7__Vfuncout))) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_sepc_r 
                = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_is_insn)
                    ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_vaddr
                    : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fault_pc);
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_scause_r 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_cause;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_stval_r 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_vaddr;
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffffdfULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                     >> 1U))))) 
                      << 5U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = (0xfffffffffffffffdULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus);
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xfffffffffffffeffULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)))) 
                      << 8U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode = 1U;
        } else {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mepc 
                = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_is_insn)
                    ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_vaddr
                    : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fault_pc);
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mcause 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_cause;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mtval 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_vaddr;
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffff7fULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                     >> 3U))))) 
                      << 7U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = (0xfffffffffffffff7ULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus);
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffe7ffULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
                      << 0xbU));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode = 3U;
        }
    } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_illegal) {
        if (([&]() {
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__10__Vfuncout 
                        = ((3U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
                           && (1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r 
                                             >> 2U))));
                }(), (IData)(__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__10__Vfuncout))) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_sepc_r 
                = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU])) 
                    << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xbU])) 
                                  << 0x17U) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU])) 
                                               >> 9U)));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_scause_r = 2ULL;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_stval_r 
                = (QData)((IData)(((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU] 
                                    << 0x17U) | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[9U] 
                                                 >> 9U))));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffffdfULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                     >> 1U))))) 
                      << 5U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = (0xfffffffffffffffdULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus);
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xfffffffffffffeffULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)))) 
                      << 8U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode = 1U;
        } else {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mepc 
                = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU])) 
                    << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xbU])) 
                                  << 0x17U) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU])) 
                                               >> 9U)));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mcause = 2ULL;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mtval 
                = (QData)((IData)(((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU] 
                                    << 0x17U) | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[9U] 
                                                 >> 9U))));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffff7fULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                     >> 3U))))) 
                      << 7U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = (0xfffffffffffffff7ULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus);
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffe7ffULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
                      << 0xbU));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode = 3U;
        }
    } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ebreak) {
        if (([&]() {
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__11__Vfuncout 
                        = ((3U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
                           && (1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r 
                                             >> 3U))));
                }(), (IData)(__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__11__Vfuncout))) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_sepc_r 
                = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU])) 
                    << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xbU])) 
                                  << 0x17U) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU])) 
                                               >> 9U)));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_scause_r = 3ULL;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_stval_r = 0ULL;
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffffdfULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                     >> 1U))))) 
                      << 5U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = (0xfffffffffffffffdULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus);
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xfffffffffffffeffULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)))) 
                      << 8U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode = 1U;
        } else {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mepc 
                = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU])) 
                    << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xbU])) 
                                  << 0x17U) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU])) 
                                               >> 9U)));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mcause = 3ULL;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mtval = 0ULL;
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffff7fULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                     >> 3U))))) 
                      << 7U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = (0xfffffffffffffff7ULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus);
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffe7ffULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
                      << 0xbU));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode = 3U;
        }
    } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_instr) {
        if (([&]() {
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__12__Vfuncout 
                        = ((3U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
                           && (1U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r)));
                }(), (IData)(__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__12__Vfuncout))) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_sepc_r 
                = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU])) 
                    << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xbU])) 
                                  << 0x17U) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU])) 
                                               >> 9U)));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_scause_r = 0ULL;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_stval_r 
                = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[9U])) 
                    << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[8U])) 
                                  << 0x17U) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) 
                                               >> 9U)));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffffdfULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                     >> 1U))))) 
                      << 5U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = (0xfffffffffffffffdULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus);
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xfffffffffffffeffULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)))) 
                      << 8U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode = 1U;
        } else {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mepc 
                = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU])) 
                    << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xbU])) 
                                  << 0x17U) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU])) 
                                               >> 9U)));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mcause = 0ULL;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mtval 
                = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[9U])) 
                    << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[8U])) 
                                  << 0x17U) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) 
                                               >> 9U)));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffff7fULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                     >> 3U))))) 
                      << 7U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = (0xfffffffffffffff7ULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus);
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffe7ffULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
                      << 0xbU));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode = 3U;
        }
    } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_data) {
        if (([&]() {
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__13__cause 
                        = ((0x80U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])
                            ? 6ULL : 4ULL);
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__13__Vfuncout 
                        = ((3U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
                           && (1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r 
                                             >> (0x3fU 
                                                 & (IData)(__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__13__cause))))));
                }(), (IData)(__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__13__Vfuncout))) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_sepc_r 
                = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU])) 
                    << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xbU])) 
                                  << 0x17U) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU])) 
                                               >> 9U)));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_scause_r 
                = ((0x80U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])
                    ? 6ULL : 4ULL);
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_stval_r 
                = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) 
                    << 0x3dU) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[6U])) 
                                  << 0x1dU) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[5U])) 
                                               >> 3U)));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffffdfULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                     >> 1U))))) 
                      << 5U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = (0xfffffffffffffffdULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus);
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xfffffffffffffeffULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)))) 
                      << 8U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode = 1U;
        } else {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mepc 
                = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU])) 
                    << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xbU])) 
                                  << 0x17U) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU])) 
                                               >> 9U)));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mcause 
                = ((0x80U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])
                    ? 6ULL : 4ULL);
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mtval 
                = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) 
                    << 0x3dU) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[6U])) 
                                  << 0x1dU) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[5U])) 
                                               >> 3U)));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffff7fULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)((1U & (IData)(
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                     >> 3U))))) 
                      << 7U));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = (0xfffffffffffffff7ULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus);
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                = ((0xffffffffffffe7ffULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                   | ((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
                      << 0xbU));
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode = 3U;
        }
    } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_mret) {
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
            = ((0xfffffffffffffff7ULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
               | ((QData)((IData)((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                 >> 7U))))) 
                  << 3U));
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
            = (0x80ULL | __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus);
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
            = (0xffffffffffffe7ffULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus);
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode 
            = (3U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                             >> 0xbU)));
    } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_sret) {
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
            = ((0xfffffffffffffffdULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
               | ((QData)((IData)((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                 >> 5U))))) 
                  << 1U));
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
            = (0x20ULL | __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus);
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
            = (0xfffffffffffffeffULL & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus);
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode 
            = (1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                             >> 8U)));
    } else if (((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                 >> 0x1aU) & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                              >> 0x10U))) {
        if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                      >> 0x19U)))) {
            if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                          >> 0x18U)))) {
                if ((0x800000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                    if ((0x400000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                        if ((0x200000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                            if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                          >> 0x14U)))) {
                                if ((0x80000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                    if ((0x40000U & 
                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                        if ((1U & (~ 
                                                   (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                    >> 0x11U)))) {
                                            if ((1U 
                                                 & (~ 
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                     >> 0x10U)))) {
                                                if (
                                                    (1U 
                                                     & (~ 
                                                        (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                         >> 0xfU)))) {
                                                    if (
                                                        (1U 
                                                         & (~ 
                                                            (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                             >> 0xeU)))) {
                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpaddr0_r 
                                                            = 
                                                            (((QData)((IData)(
                                                                              vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                              << 0x32U) 
                                                             | (((QData)((IData)(
                                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                                 << 0x12U) 
                                                                | ((QData)((IData)(
                                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                                   >> 0xeU)));
                                                    }
                                                }
                                            }
                                        }
                                    } else if ((1U 
                                                & (~ 
                                                   (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                    >> 0x11U)))) {
                                        if ((1U & (~ 
                                                   (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                    >> 0x10U)))) {
                                            if ((1U 
                                                 & (~ 
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                     >> 0xfU)))) {
                                                if (
                                                    (1U 
                                                     & (~ 
                                                        (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                         >> 0xeU)))) {
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpcfg0_r 
                                                        = 
                                                        (0xffULL 
                                                         & ((QData)((IData)(
                                                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                            >> 0xeU));
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        } else if ((0x100000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                            if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                          >> 0x13U)))) {
                                if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                              >> 0x12U)))) {
                                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                  >> 0x11U)))) {
                                        if ((0x10000U 
                                             & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                            if ((1U 
                                                 & (~ 
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                     >> 0xfU)))) {
                                                if (
                                                    (1U 
                                                     & (~ 
                                                        (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                         >> 0xeU)))) {
                                                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mip_raw 
                                                        = 
                                                        (((QData)((IData)(
                                                                          vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                          << 0x32U) 
                                                         | (((QData)((IData)(
                                                                             vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                             << 0x12U) 
                                                            | ((QData)((IData)(
                                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                               >> 0xeU)));
                                                }
                                            }
                                        } else if (
                                                   (0x8000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                            if ((0x4000U 
                                                 & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mtval 
                                                    = 
                                                    (((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                      << 0x32U) 
                                                     | (((QData)((IData)(
                                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                         << 0x12U) 
                                                        | ((QData)((IData)(
                                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                           >> 0xeU)));
                                            } else {
                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mcause 
                                                    = 
                                                    (((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                      << 0x32U) 
                                                     | (((QData)((IData)(
                                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                         << 0x12U) 
                                                        | ((QData)((IData)(
                                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                           >> 0xeU)));
                                            }
                                        } else if (
                                                   (0x4000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mepc 
                                                = (
                                                   ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                    << 0x32U) 
                                                   | (((QData)((IData)(
                                                                       vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                       << 0x12U) 
                                                      | ((QData)((IData)(
                                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                         >> 0xeU)));
                                        } else {
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mscratch 
                                                = (
                                                   ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                    << 0x32U) 
                                                   | (((QData)((IData)(
                                                                       vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                       << 0x12U) 
                                                      | ((QData)((IData)(
                                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                         >> 0xeU)));
                                        }
                                    }
                                }
                            }
                        } else if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                             >> 0x13U)))) {
                            if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                          >> 0x12U)))) {
                                if ((0x20000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                  >> 0x10U)))) {
                                        if ((0x8000U 
                                             & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                            if ((1U 
                                                 & (~ 
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                     >> 0xeU)))) {
                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_menvcfg_r 
                                                    = 
                                                    (((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                      << 0x32U) 
                                                     | (((QData)((IData)(
                                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                         << 0x12U) 
                                                        | ((QData)((IData)(
                                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                           >> 0xeU)));
                                            }
                                        }
                                    }
                                } else if ((0x10000U 
                                            & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                    if ((0x8000U & 
                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                        if ((1U & (~ 
                                                   (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                    >> 0xeU)))) {
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mcounteren_r 
                                                = (
                                                   ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                    << 0x32U) 
                                                   | (((QData)((IData)(
                                                                       vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                       << 0x12U) 
                                                      | ((QData)((IData)(
                                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                         >> 0xeU)));
                                        }
                                    } else if ((0x4000U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mtvec 
                                            = (((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                << 0x32U) 
                                               | (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                   << 0x12U) 
                                                  | ((QData)((IData)(
                                                                     vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                     >> 0xeU)));
                                    } else {
                                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mie 
                                            = (((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                << 0x32U) 
                                               | (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                   << 0x12U) 
                                                  | ((QData)((IData)(
                                                                     vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                     >> 0xeU)));
                                    }
                                } else if ((0x8000U 
                                            & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                    if ((0x4000U & 
                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mideleg_r 
                                            = (((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                << 0x32U) 
                                               | (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                   << 0x12U) 
                                                  | ((QData)((IData)(
                                                                     vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                     >> 0xeU)));
                                    } else {
                                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r 
                                            = (((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                << 0x32U) 
                                               | (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                   << 0x12U) 
                                                  | ((QData)((IData)(
                                                                     vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                     >> 0xeU)));
                                    }
                                } else if ((1U & (~ 
                                                  (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                   >> 0xeU)))) {
                                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                        = (((QData)((IData)(
                                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                            << 0x32U) 
                                           | (((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                               << 0x12U) 
                                              | ((QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                 >> 0xeU)));
                                }
                            }
                        }
                    }
                } else if ((0x400000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                    if ((0x200000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                        if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                      >> 0x14U)))) {
                            if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                          >> 0x13U)))) {
                                if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                              >> 0x12U)))) {
                                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                  >> 0x11U)))) {
                                        if ((1U & (~ 
                                                   (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                    >> 0x10U)))) {
                                            if ((1U 
                                                 & (~ 
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                     >> 0xfU)))) {
                                                if (
                                                    (1U 
                                                     & (~ 
                                                        (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                         >> 0xeU)))) {
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_satp 
                                                        = 
                                                        (((QData)((IData)(
                                                                          vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                          << 0x32U) 
                                                         | (((QData)((IData)(
                                                                             vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                             << 0x12U) 
                                                            | ((QData)((IData)(
                                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                               >> 0xeU)));
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else if ((0x100000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                        if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                      >> 0x13U)))) {
                            if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                          >> 0x12U)))) {
                                if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                              >> 0x11U)))) {
                                    if ((0x10000U & 
                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                        if ((1U & (~ 
                                                   (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                    >> 0xfU)))) {
                                            if ((1U 
                                                 & (~ 
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                     >> 0xeU)))) {
                                                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mip_raw 
                                                    = 
                                                    ((0xfffffffffffffdddULL 
                                                      & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mip_raw) 
                                                     | (0x222ULL 
                                                        & ((QData)((IData)(
                                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                           >> 0xeU)));
                                            }
                                        }
                                    } else if ((0x8000U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                        if ((0x4000U 
                                             & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_stval_r 
                                                = (
                                                   ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                    << 0x32U) 
                                                   | (((QData)((IData)(
                                                                       vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                       << 0x12U) 
                                                      | ((QData)((IData)(
                                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                         >> 0xeU)));
                                        } else {
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_scause_r 
                                                = (
                                                   ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                    << 0x32U) 
                                                   | (((QData)((IData)(
                                                                       vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                       << 0x12U) 
                                                      | ((QData)((IData)(
                                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                         >> 0xeU)));
                                        }
                                    } else if ((0x4000U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_sepc_r 
                                            = (((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                << 0x32U) 
                                               | (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                   << 0x12U) 
                                                  | ((QData)((IData)(
                                                                     vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                     >> 0xeU)));
                                    } else {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_sscratch_r 
                                            = (((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                << 0x32U) 
                                               | (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                   << 0x12U) 
                                                  | ((QData)((IData)(
                                                                     vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                     >> 0xeU)));
                                    }
                                }
                            }
                        }
                    } else if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                         >> 0x13U)))) {
                        if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                      >> 0x12U)))) {
                            if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                          >> 0x11U)))) {
                                if ((0x10000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                  >> 0xfU)))) {
                                        if ((0x4000U 
                                             & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_stvec_r 
                                                = (
                                                   ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                    << 0x32U) 
                                                   | (((QData)((IData)(
                                                                       vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                       << 0x12U) 
                                                      | ((QData)((IData)(
                                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                         >> 0xeU)));
                                        } else {
                                            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mie 
                                                = (
                                                   (0xfffffffffffffdddULL 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mie) 
                                                   | (0x222ULL 
                                                      & ((QData)((IData)(
                                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                         >> 0xeU)));
                                        }
                                    }
                                } else if ((1U & (~ 
                                                  (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                   >> 0xfU)))) {
                                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                  >> 0xeU)))) {
                                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                            = ((0x7ffffffcfff21fffULL 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                                               | (0x80000003000de000ULL 
                                                  & (((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                      << 0x32U) 
                                                     | (((QData)((IData)(
                                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                         << 0x12U) 
                                                        | ((QData)((IData)(
                                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                           >> 0xeU)))));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxState 
        = __Vdly__SimTopFPGA__DOT__u_device__DOT__rxState;
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBitIndex 
        = __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitIndex;
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBitTmr 
        = __Vdly__SimTopFPGA__DOT__u_device__DOT__rxBitTmr;
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxShiftReg 
        = __Vdly__SimTopFPGA__DOT__u_device__DOT__rxShiftReg;
    vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__txn_active 
        = __Vdly__SimTopFPGA__DOT__u_bram__DOT__txn_active;
    vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__counter 
        = __Vdly__SimTopFPGA__DOT__u_bram__DOT__counter;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mip_raw 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mip_raw;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mie 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mie;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBit 
        = ((IData)(vlSelfRef.reset) || (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBitSync));
    if (vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__is_write) {
        vlSelfRef.SimTopFPGA__DOT__ram_ready = vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__real_valid;
        vlSelfRef.SimTopFPGA__DOT__ram_last = vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__real_valid;
    } else {
        vlSelfRef.SimTopFPGA__DOT__ram_ready = vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__ready_read;
        vlSelfRef.SimTopFPGA__DOT__ram_last = vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__last_read;
    }
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_22 
        = ((~ (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_pte 
                       >> 4U))) & (0U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_15 
        = ((1U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
           & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_pte 
                      >> 4U)));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_insn_pmp_fault 
        = ((4U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state)) 
           & ([&]() {
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__mode 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__paddr 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpaddr0_r;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__cfg 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpcfg0_r;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__addr 
                    = SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__phys_addr;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__active 
                    = (0U != (3U & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__cfg 
                                            >> 3U))));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__paddr 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__paddr;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__cfg 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__cfg;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__addr 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__addr;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__a_mode 
                    = (3U & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__cfg 
                                     >> 3U)));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__Vfuncout = 0U;
                if ((2U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__a_mode))) {
                    if ((1U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__a_mode))) {
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__ones = 0U;
                        while ((VL_GTS_III(32, 0x36U, vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__ones) 
                                & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__paddr 
                                           >> (0x3fU 
                                               & vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__ones))))) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__ones 
                                = ((IData)(1U) + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__ones);
                        }
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__base 
                            = (0xfffffffffffffcULL 
                               & ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__paddr 
                                   << 2U) & (~ (VL_SHIFTL_QQI(64,64,32, 1ULL, 
                                                              ((IData)(3U) 
                                                               + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__ones)) 
                                                - 1ULL))));
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__top 
                            = (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__base 
                               + VL_SHIFTL_QQI(64,64,32, 1ULL, 
                                               ((IData)(3U) 
                                                + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__ones)));
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__Vfuncout 
                            = ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__addr 
                                >= vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__base) 
                               & (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__addr 
                                  < vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__top));
                    } else {
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__Vfuncout 
                            = ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__addr 
                                >> 2U) == (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__paddr 
                                           >> 2U));
                    }
                } else if ((1U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__a_mode))) {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__top 
                        = (0xfffffffffffffcULL & (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__paddr 
                                                  << 2U));
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__base = 0ULL;
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__Vfuncout 
                        = (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__addr 
                           < vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__top);
                } else {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__Vfuncout = 0U;
                }
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__hit 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__Vfuncout;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__allow 
                    = (1U & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__cfg 
                                     >> 2U)));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__Vfuncout 
                    = ((3U != (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__mode)) 
                       && ((IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__active) 
                           && ((1U & (~ (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__hit))) 
                               || (1U & (~ (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__allow))))));
            }(), (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__Vfuncout)));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_load_pmp_fault 
        = (((5U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state)) 
            & (~ (IData)((0U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_wstrb))))) 
           & ([&]() {
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__mode 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__paddr 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpaddr0_r;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__cfg 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpcfg0_r;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__addr 
                    = SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__phys_addr;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__active 
                    = (0U != (3U & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__cfg 
                                            >> 3U))));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__paddr 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__paddr;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__cfg 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__cfg;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__addr 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__addr;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__a_mode 
                    = (3U & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__cfg 
                                     >> 3U)));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__Vfuncout = 0U;
                if ((2U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__a_mode))) {
                    if ((1U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__a_mode))) {
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__ones = 0U;
                        while ((VL_GTS_III(32, 0x36U, vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__ones) 
                                & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__paddr 
                                           >> (0x3fU 
                                               & vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__ones))))) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__ones 
                                = ((IData)(1U) + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__ones);
                        }
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__base 
                            = (0xfffffffffffffcULL 
                               & ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__paddr 
                                   << 2U) & (~ (VL_SHIFTL_QQI(64,64,32, 1ULL, 
                                                              ((IData)(3U) 
                                                               + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__ones)) 
                                                - 1ULL))));
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__top 
                            = (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__base 
                               + VL_SHIFTL_QQI(64,64,32, 1ULL, 
                                               ((IData)(3U) 
                                                + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__ones)));
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__Vfuncout 
                            = ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__addr 
                                >= vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__base) 
                               & (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__addr 
                                  < vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__top));
                    } else {
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__Vfuncout 
                            = ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__addr 
                                >> 2U) == (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__paddr 
                                           >> 2U));
                    }
                } else if ((1U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__a_mode))) {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__top 
                        = (0xfffffffffffffcULL & (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__paddr 
                                                  << 2U));
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__base = 0ULL;
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__Vfuncout 
                        = (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__addr 
                           < vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__top);
                } else {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__Vfuncout = 0U;
                }
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__hit 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__Vfuncout;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__allow 
                    = (1U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__cfg));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__Vfuncout 
                    = ((3U != (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__mode)) 
                       && ((IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__active) 
                           && ((1U & (~ (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__hit))) 
                               || (1U & (~ (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__allow))))));
            }(), (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__Vfuncout)));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_store_pmp_fault 
        = (((5U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state)) 
            & (0U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_wstrb))) 
           & ([&]() {
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__mode 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__paddr 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpaddr0_r;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__cfg 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpcfg0_r;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__addr 
                    = SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__phys_addr;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__active 
                    = (0U != (3U & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__cfg 
                                            >> 3U))));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__paddr 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__paddr;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__cfg 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__cfg;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__addr 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__addr;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__a_mode 
                    = (3U & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__cfg 
                                     >> 3U)));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__Vfuncout = 0U;
                if ((2U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__a_mode))) {
                    if ((1U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__a_mode))) {
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__ones = 0U;
                        while ((VL_GTS_III(32, 0x36U, vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__ones) 
                                & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__paddr 
                                           >> (0x3fU 
                                               & vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__ones))))) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__ones 
                                = ((IData)(1U) + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__ones);
                        }
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__base 
                            = (0xfffffffffffffcULL 
                               & ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__paddr 
                                   << 2U) & (~ (VL_SHIFTL_QQI(64,64,32, 1ULL, 
                                                              ((IData)(3U) 
                                                               + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__ones)) 
                                                - 1ULL))));
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__top 
                            = (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__base 
                               + VL_SHIFTL_QQI(64,64,32, 1ULL, 
                                               ((IData)(3U) 
                                                + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__ones)));
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__Vfuncout 
                            = ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__addr 
                                >= vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__base) 
                               & (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__addr 
                                  < vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__top));
                    } else {
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__Vfuncout 
                            = ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__addr 
                                >> 2U) == (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__paddr 
                                           >> 2U));
                    }
                } else if ((1U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__a_mode))) {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__top 
                        = (0xfffffffffffffcULL & (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__paddr 
                                                  << 2U));
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__base = 0ULL;
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__Vfuncout 
                        = (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__addr 
                           < vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__top);
                } else {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__Vfuncout = 0U;
                }
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__hit 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__Vfuncout;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__allow 
                    = (1U & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__cfg 
                                     >> 1U)));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__Vfuncout 
                    = ((3U != (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__mode)) 
                       && ((IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__active) 
                           && ((1U & (~ (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__hit))) 
                               || (1U & (~ (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__allow))))));
            }(), (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__Vfuncout)));
    if (vlSelfRef.reset) {
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pc = 0x80000000ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc = 0ULL;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_bubble = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_pc = 0ULL;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U] = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U] = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U] = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
            = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[1U] 
            = VSimTopFPGA__ConstPool__CONST_hbda38995_0[1U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U] 
            = VSimTopFPGA__ConstPool__CONST_hbda38995_0[2U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U] 
            = VSimTopFPGA__ConstPool__CONST_hbda38995_0[3U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[4U] 
            = VSimTopFPGA__ConstPool__CONST_hbda38995_0[4U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U] 
            = VSimTopFPGA__ConstPool__CONST_hbda38995_0[5U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[6U] 
            = VSimTopFPGA__ConstPool__CONST_hbda38995_0[6U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
            = VSimTopFPGA__ConstPool__CONST_hbda38995_0[7U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U] 
            = VSimTopFPGA__ConstPool__CONST_hbda38995_0[8U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U] 
            = VSimTopFPGA__ConstPool__CONST_hbda38995_0[9U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU] 
            = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xaU];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU] 
            = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xbU];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU] 
            = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xcU];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU] 
            = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xdU];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
            = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xeU];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[0U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[1U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[1U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[2U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[3U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[3U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[4U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[4U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[5U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[6U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[7U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[8U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[8U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[9U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[9U];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xaU] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[0xaU];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xbU] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[0xbU];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[0xcU];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[0U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[1U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[2U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[3U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[3U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[4U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[4U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[5U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[5U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[6U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[6U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[7U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[8U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[8U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[9U] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[9U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[0xaU];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xbU] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[0xbU];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
            = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[0xcU];
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_issued_q = 0U;
        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_done_q = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pc = 0ULL;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_instr = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__halted = 0U;
    } else {
        if ((1U & ((~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                       >> 0x14U)) | (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
                                        >> 0xaU))))) {
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_issued_q = 0U;
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_done_q = 0U;
        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_issue) {
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_issued_q = 1U;
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_done_q = 0U;
        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_issued_q) {
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_issued_q = 0U;
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_done_q = 1U;
        } else if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_done_q) 
                    & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_ex_busy)))) {
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_done_q = 0U;
        }
        if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_commit) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending = 0U;
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending = 0U;
        }
        if ((1U & ((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__halted)) 
                   & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_commit))))) {
            if ((0U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_bubble))) {
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_bubble 
                    = (3U & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_bubble) 
                             - (IData)(1U)));
            }
            if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect) 
                 | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mret_redirect))) {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending = 0U;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc = 0ULL;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending = 0U;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pc 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect_pc;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_bubble = 2U;
            } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap) {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending = 0U;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc = 0ULL;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending = 0U;
            } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_instr_misalign) {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending = 0U;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc = 0ULL;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending = 0U;
            } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_flush_front) {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending = 0U;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc = 0ULL;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending = 0U;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pc 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_redirect_pc;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_bubble = 2U;
            } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_resp_fire) {
                if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending = 0U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc = 0ULL;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending = 0U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pc 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pc;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_bubble = 2U;
                } else {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending = 0U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pc 
                        = (4ULL + vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc);
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc = 0ULL;
                }
            } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_new_fire) {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending = 1U;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pc;
            }
            if (((((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect) 
                   | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mret_redirect)) 
                  | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap)) 
                 | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_mem_busy))) {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                    = (0xffffU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU]);
            } else {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U] 
                    = ((0xffU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U]) 
                       | (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_stage_result) 
                           << 9U) | (0x100U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[8U] 
                    = ((0xffU & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_stage_result) 
                                 >> 0x17U)) | ((0x100U 
                                                & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_stage_result) 
                                                   >> 0x17U)) 
                                               | ((IData)(
                                                          (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_stage_result 
                                                           >> 0x20U)) 
                                                  << 9U)));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[9U] 
                    = ((0xffU & ((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_stage_result 
                                          >> 0x20U)) 
                                 >> 0x17U)) | ((0xfffffe00U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[9U]) 
                                               | (0x100U 
                                                  & ((IData)(
                                                             (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_stage_result 
                                                              >> 0x20U)) 
                                                     >> 0x17U))));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU] 
                    = ((0xffU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xaU]) 
                       | ((0x100U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xaU]) 
                          | (0xfffffe00U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xaU])));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xbU] 
                    = ((0xffU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xbU]) 
                       | ((0x100U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xbU]) 
                          | (0xfffffe00U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xbU])));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                    = (0x1ffffU & ((0xffU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU]) 
                                   | ((0x100U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU]) 
                                      | (0x1fe00U & 
                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU]))));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U] 
                    = ((0xffffff7fU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U]) 
                       | (0x80U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U]));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[5U] 
                    = ((7U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[5U]) 
                       | ((IData)((((QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])) 
                                    << 0x3dU) | (((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U])) 
                                                  << 0x1dU) 
                                                 | ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U])) 
                                                    >> 3U)))) 
                          << 3U));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[6U] 
                    = (((IData)((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])) 
                                  << 0x3dU) | (((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U])) 
                                                << 0x1dU) 
                                               | ((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U])) 
                                                  >> 3U)))) 
                        >> 0x1dU) | ((IData)(((((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])) 
                                                << 0x3dU) 
                                               | (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U])) 
                                                   << 0x1dU) 
                                                  | ((QData)((IData)(
                                                                     vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U])) 
                                                     >> 3U))) 
                                              >> 0x20U)) 
                                     << 3U));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U] 
                    = ((0xfffffff8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U]) 
                       | ((IData)(((((QData)((IData)(
                                                     vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])) 
                                     << 0x3dU) | (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U])) 
                                                   << 0x1dU) 
                                                  | ((QData)((IData)(
                                                                     vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U])) 
                                                     >> 3U))) 
                                   >> 0x20U)) >> 0x1dU));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U] 
                    = ((0x7ffU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U]) 
                       | (0xfffff800U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U]));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U] 
                    = ((0x7ffU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[1U]) 
                       | (0xfffff800U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[1U]));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                    = ((0xf8000000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U]) 
                       | ((0x7ffU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U]) 
                          | (0x7fff800U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U])));
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U] 
                    = ((0xffffffe0U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U]) 
                       | (0x1fU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U]));
            }
            if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap) {
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[0U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[1U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[1U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[2U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[3U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[3U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[4U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[4U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[5U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[6U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[7U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[8U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[8U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[9U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[9U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xaU] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[0xaU];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xbU] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[0xbU];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[0xcU];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[1U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[1U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[2U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[3U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[4U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[4U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[5U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[6U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[6U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[7U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[8U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[9U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xaU];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xbU];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xcU];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xdU];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xeU];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] = 0U;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U] = 0U;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U] = 0U;
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U] = 0U;
            } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_mem_busy) {
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[1U] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[1U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[3U] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[3U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[4U] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[4U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[8U] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[8U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[9U] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[9U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xaU] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xaU];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xbU] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xbU];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U] 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[1U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[1U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[2U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[3U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[4U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[4U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[5U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[6U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[6U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[7U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[8U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[9U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xaU];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xbU];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xcU];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xdU];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                    = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xeU];
            } else if (((((((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect) 
                            | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mret_redirect)) 
                           | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap)) 
                          | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_ex_busy)) 
                         | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__raw_hazard_mem)) 
                        | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending))) {
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[0U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[1U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[1U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[2U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[3U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[3U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[4U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[4U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[5U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[6U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[7U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[8U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[8U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[9U] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[9U];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xaU] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[0xaU];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xbU] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[0xbU];
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
                    = VSimTopFPGA__ConstPool__CONST_h2986b6f6_0[0xcU];
                if ((((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect) 
                      | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mret_redirect)) 
                     | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap))) {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[1U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[1U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[2U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[3U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[4U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[4U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[5U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[6U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[6U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[7U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[8U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[9U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xaU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xbU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xcU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xdU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xeU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] = 0U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U] = 0U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U] = 0U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U] = 0U;
                }
            } else {
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[9U] 
                    = ((0x1ffU & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[9U]) 
                       | (0xfffffe00U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU] 
                                         << 1U)));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xaU] 
                    = (((0x1feU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU] 
                                   << 1U)) | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU] 
                                              >> 0x1fU)) 
                       | (0xfffffe00U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU] 
                                         << 1U)));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xbU] 
                    = (((0x1feU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU] 
                                   << 1U)) | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU] 
                                              >> 0x1fU)) 
                       | (0xfffffe00U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU] 
                                         << 1U)));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
                    = (0x1ffffU & (((0x1feU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                               << 1U)) 
                                    | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU] 
                                       >> 0x1fU)) | 
                                   ((0x1c000U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                                 >> 4U)) 
                                    | (0x3e00U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                                  << 1U)))));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U] 
                    = ((0x1ffU & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U]) 
                       | ((IData)(((0x400U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U])
                                    ? 0ULL : ((0x8000000U 
                                               & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U])
                                               ? (4ULL 
                                                  + 
                                                  (((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])) 
                                                    << 0x38U) 
                                                   | (((QData)((IData)(
                                                                       vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU])) 
                                                       << 0x18U) 
                                                      | ((QData)((IData)(
                                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU])) 
                                                         >> 8U))))
                                               : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result))) 
                          << 9U));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[8U] 
                    = (((IData)(((0x400U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U])
                                  ? 0ULL : ((0x8000000U 
                                             & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U])
                                             ? (4ULL 
                                                + (
                                                   ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])) 
                                                    << 0x38U) 
                                                   | (((QData)((IData)(
                                                                       vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU])) 
                                                       << 0x18U) 
                                                      | ((QData)((IData)(
                                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU])) 
                                                         >> 8U))))
                                             : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result))) 
                        >> 0x17U) | ((IData)((((0x400U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U])
                                                ? 0ULL
                                                : (
                                                   (0x8000000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U])
                                                    ? 
                                                   (4ULL 
                                                    + 
                                                    (((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])) 
                                                      << 0x38U) 
                                                     | (((QData)((IData)(
                                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU])) 
                                                         << 0x18U) 
                                                        | ((QData)((IData)(
                                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU])) 
                                                           >> 8U))))
                                                    : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result)) 
                                              >> 0x20U)) 
                                     << 9U));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[9U] 
                    = ((0xfffffe00U & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[9U]) 
                       | ((IData)((((0x400U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U])
                                     ? 0ULL : ((0x8000000U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U])
                                                ? (4ULL 
                                                   + 
                                                   (((QData)((IData)(
                                                                     vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])) 
                                                     << 0x38U) 
                                                    | (((QData)((IData)(
                                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU])) 
                                                        << 0x18U) 
                                                       | ((QData)((IData)(
                                                                          vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU])) 
                                                          >> 8U))))
                                                : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result)) 
                                   >> 0x20U)) >> 0x17U));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U] 
                    = ((0x7ffffffU & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U]) 
                       | (((0x40U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U])
                            ? (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_store_strobe)
                            : 0U) << 0x1bU));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[3U] 
                    = (((0x7fffff8U & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_store_data_shifted) 
                                       << 3U)) | ((
                                                   (0x40U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U])
                                                    ? (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_store_strobe)
                                                    : 0U) 
                                                  >> 5U)) 
                       | (0xf8000000U & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_store_data_shifted) 
                                         << 3U)));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[4U] 
                    = ((((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_store_data_shifted) 
                         >> 0x1dU) | (0x7fffff8U & 
                                      ((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_store_data_shifted 
                                                >> 0x20U)) 
                                       << 3U))) | (0xf8000000U 
                                                   & ((IData)(
                                                              (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_store_data_shifted 
                                                               >> 0x20U)) 
                                                      << 3U)));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U] 
                    = ((0xfffffff8U & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U]) 
                       | ((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_store_data_shifted 
                                   >> 0x20U)) >> 0x1dU));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U] 
                    = ((7U & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U]) 
                       | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_mem_addr) 
                          << 3U));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U] 
                    = (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_mem_addr) 
                        >> 0x1dU) | ((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_mem_addr 
                                              >> 0x20U)) 
                                     << 3U));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U] 
                    = ((0xfffffe00U & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U]) 
                       | (((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_mem_addr 
                                    >> 0x20U)) >> 0x1dU) 
                          | (0x1f8U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U] 
                                       << 1U))));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U] 
                    = ((0x1fU & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U]) 
                       | (0xffffffe0U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U]));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[1U] 
                    = ((0x1fU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[1U]) 
                       | (0xffffffe0U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[1U]));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U] 
                    = ((0xf8000000U & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U]) 
                       | ((0x1fU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U]) 
                          | (0x7ffffe0U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U])));
                __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U] 
                    = ((0xffffffe0U & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U]) 
                       | ((0x10U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U]) 
                          | (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_misalign) 
                              << 3U) | (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_instr_misalign) 
                                         << 2U) | (3U 
                                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U])))));
                if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect) 
                     | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mret_redirect))) {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[1U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[1U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[2U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[3U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[4U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[4U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[5U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[6U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[6U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[7U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[8U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[9U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xaU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xbU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xcU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xdU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xeU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] = 0U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U] = 0U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U] = 0U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U] = 0U;
                } else if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_flush_front) 
                            | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_instr_misalign))) {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[1U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[1U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[2U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[3U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[4U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[4U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[5U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[6U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[6U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[7U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[8U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[9U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xaU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xbU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xcU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xdU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xeU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] = 0U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U] = 0U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U] = 0U;
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U] = 0U;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_to_mem_blocks_front) {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U] 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U] 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U] 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[1U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[1U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[2U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[3U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[4U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[4U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[5U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[6U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[6U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[7U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[8U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[9U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xaU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xbU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xcU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xdU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xeU];
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__raw_hazard_ex) {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[1U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[1U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[2U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[3U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[4U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[4U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[5U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[6U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[6U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[7U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[8U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[9U];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xaU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xbU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xcU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xdU];
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                        = VSimTopFPGA__ConstPool__CONST_hbda38995_0[0xeU];
                } else {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                        = ((0x1ffffU & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU]) 
                           | (0x1e0000U & ((((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_valid) 
                                             << 0x14U) 
                                            | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_trap) 
                                               << 0x13U)) 
                                           | (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen) 
                                               << 0x12U) 
                                              | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_word) 
                                                 << 0x11U)))));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU] 
                        = ((0xffU & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU]) 
                           | ((IData)((((QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U])) 
                                        << 0x20U) | (QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U])))) 
                              << 8U));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU] 
                        = (((IData)((((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U])) 
                                      << 0x20U) | (QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U])))) 
                            >> 0x18U) | ((IData)(((
                                                   ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U])) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U]))) 
                                                  >> 0x20U)) 
                                         << 8U));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                        = ((0x1e0000U & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU]) 
                           | (0x1fffffU & (((IData)(
                                                    ((((QData)((IData)(
                                                                       vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U])) 
                                                       << 0x20U) 
                                                      | (QData)((IData)(
                                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U]))) 
                                                     >> 0x20U)) 
                                            >> 0x18U) 
                                           | (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_alu_cmd) 
                                               << 0xdU) 
                                              | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rd) 
                                                 << 8U)))));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
                        = ((0xffU & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U]) 
                           | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op2) 
                              << 8U));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U] 
                        = (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op2) 
                            >> 0x18U) | ((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op2 
                                                  >> 0x20U)) 
                                         << 8U));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U] 
                        = (((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op2 
                                     >> 0x20U)) >> 0x18U) 
                           | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op1) 
                              << 8U));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU] 
                        = (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op1) 
                            >> 0x18U) | ((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op1 
                                                  >> 0x20U)) 
                                         << 8U));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU] 
                        = (((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op1 
                                     >> 0x20U)) >> 0x18U) 
                           | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                              << 8U));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU] 
                        = ((0xffffff00U & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU]) 
                           | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                              >> 0x18U));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U] 
                        = ((7U & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U]) 
                           | (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs2_val) 
                               << 8U) | (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_load) 
                                          << 7U) | 
                                         (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_store) 
                                           << 6U) | 
                                          ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_mem_size) 
                                           << 3U)))));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[4U] 
                        = (((7U & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs2_val) 
                                   >> 0x18U)) | ((7U 
                                                  & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_load) 
                                                     >> 0x19U)) 
                                                 | ((7U 
                                                     & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_store) 
                                                        >> 0x1aU)) 
                                                    | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_mem_size) 
                                                       >> 0x1dU)))) 
                           | ((0xf8U & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs2_val) 
                                        >> 0x18U)) 
                              | ((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs2_val 
                                          >> 0x20U)) 
                                 << 8U)));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U] 
                        = ((0xffffff00U & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U]) 
                           | ((7U & ((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs2_val 
                                              >> 0x20U)) 
                                     >> 0x18U)) | (0xf8U 
                                                   & ((IData)(
                                                              (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs2_val 
                                                               >> 0x20U)) 
                                                      >> 0x18U))));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U] 
                        = ((0xffU & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U]) 
                           | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_imm) 
                              << 8U));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[6U] 
                        = (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_imm) 
                            >> 0x18U) | ((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_imm 
                                                  >> 0x20U)) 
                                         << 8U));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
                        = ((0xffffff00U & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U]) 
                           | ((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_imm 
                                       >> 0x20U)) >> 0x18U));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U] 
                        = ((0x1fffffffU & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U]) 
                           | (0xe0000000U & (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_br_funct3) 
                                              << 0x1eU) 
                                             | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_jal) 
                                                << 0x1dU))));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U] 
                        = ((0xfffffff8U & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U]) 
                           | (0x1fffffffU & (((0x1ffffffcU 
                                               & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_mem_unsigned) 
                                                  << 2U)) 
                                              | (0x1ffffffeU 
                                                 & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_branch) 
                                                    << 1U))) 
                                             | ((0x1fffffffU 
                                                 & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_br_funct3) 
                                                    >> 2U)) 
                                                | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_jal) 
                                                   >> 3U)))));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U] 
                        = ((0xe0003fffU & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U]) 
                           | (0xffffc000U & (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_jalr) 
                                              << 0x1cU) 
                                             | (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wb_pc4) 
                                                 << 0x1bU) 
                                                | (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wen) 
                                                    << 0x1aU) 
                                                   | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_csr_addr) 
                                                      << 0xeU))))));
                    if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pop_buf) {
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_instr;
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U] 
                            = (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_pc);
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U] 
                            = (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_pc 
                                       >> 0x20U));
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U] = 1U;
                    } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_resp_to_id) {
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                            = (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__iresp_core);
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U] 
                            = (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc);
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U] 
                            = (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc 
                                       >> 0x20U));
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U] = 1U;
                    } else {
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] = 0U;
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U] = 0U;
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U] = 0U;
                        __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U] = 0U;
                    }
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
                        = ((0x7ffU & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U]) 
                           | (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wdata) 
                               << 0xeU) | (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_ecall) 
                                            << 0xdU) 
                                           | (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_mret) 
                                               << 0xcU) 
                                              | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_sret) 
                                                 << 0xbU)))));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[1U] 
                        = (((0x7ffU & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wdata) 
                                       >> 0x12U)) | 
                            ((0x7ffU & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_ecall) 
                                        >> 0x13U)) 
                             | ((0x7ffU & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_mret) 
                                           >> 0x14U)) 
                                | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_sret) 
                                   >> 0x15U)))) | (
                                                   (0x3800U 
                                                    & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wdata) 
                                                       >> 0x12U)) 
                                                   | ((IData)(
                                                              (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wdata 
                                                               >> 0x20U)) 
                                                      << 0xeU)));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U] 
                        = ((0xffffc000U & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U]) 
                           | ((0x7ffU & ((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wdata 
                                                  >> 0x20U)) 
                                         >> 0x12U)) 
                              | (0x3800U & ((IData)(
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wdata 
                                                     >> 0x20U)) 
                                            >> 0x12U))));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
                        = ((0xfffff81fU & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U]) 
                           | (0xffffffe0U & (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_amo) 
                                              << 0xaU) 
                                             | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_amo_cmd) 
                                                << 5U))));
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
                        = ((0xffffffe0U & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U]) 
                           | ((((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_sfence) 
                                << 4U) | (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_misalign) 
                                           << 3U) | 
                                          ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_instr_misalign) 
                                           << 2U))) 
                              | (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal) 
                                  << 1U) | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_ebreak))));
                }
            }
            if ((1U & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_flush_front)))) {
                if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_resp_to_buf) {
                    __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_pc 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc;
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_instr 
                        = (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__iresp_core);
                }
            }
        } else {
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U] = 0U;
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                = (0xfffffU & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU]);
            __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
                = (0xffffU & __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU]);
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                = (0xffffU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU]);
        }
        if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_commit) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__halted = 1U;
        }
    }
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__translate_en 
        = (IData)(((0x8000000000000000ULL == (0xf000000000000000ULL 
                                              & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_satp)) 
                   & (3U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode))));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_store 
        = ((5U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state)) 
           & ((0U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_wstrb)) 
              & ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_22) 
                 | (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_15))));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_load 
        = ((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_is_insn)) 
           & ((4U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state)) 
              & ((~ (IData)((0U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_wstrb)))) 
                 & ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_22) 
                    | ((~ (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                   >> 0x12U))) & (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_15))))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_pc 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_pc;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_issued_q 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_issued_q;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pc 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pc;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_bubble 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_bubble;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_done_q 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_done_q;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[1U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[1U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[3U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[3U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[4U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[4U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[8U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[8U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[9U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[9U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xaU] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xaU];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xbU] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xbU];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[1U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[1U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[4U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[4U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[6U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[6U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
        = __Vdly__SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU];
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__rxBitSync = 1U;
    __VdfgRegularize_hd87f99a1_0_0 = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending)
                                       ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc
                                       : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pc);
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ecall 
        = ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U] 
            >> 0xdU) & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                        >> 0x10U));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_mret 
        = ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U] 
            >> 0xcU) & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                        >> 0x10U));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_sret 
        = ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U] 
            >> 0xbU) & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                        >> 0x10U));
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_sfence 
        = ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U] 
            >> 4U) & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                      >> 0x10U));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_illegal 
        = ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U] 
            >> 1U) & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                      >> 0x10U));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ebreak 
        = (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U] 
           & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
              >> 0x10U));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_data 
        = ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U] 
            >> 3U) & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                      >> 0x10U));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_instr 
        = ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U] 
            >> 2U) & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                      >> 0x10U));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_ebreak = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_br_funct3 = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_word = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_ecall = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_jalr = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wb_pc4 = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_jal = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_trap = 0U;
    if ((0x5006bU == vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_trap = 1U;
    }
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_branch = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_mem_unsigned = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_amo_cmd = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_mem_size = 3U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_alu_cmd = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_amo = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_store = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_load = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_csr_addr 
        = (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
           >> 0x14U);
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rd 
        = (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                    >> 7U));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_sfence = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_mret = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_valid 
        = (1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U]);
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wen = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_sret = 0U;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_imm_u 
        = (((QData)((IData)((- (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                        >> 0x1fU))))) 
            << 0x20U) | (QData)((IData)((0xfffff000U 
                                         & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U]))));
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_imm_i 
        = (((- (QData)((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                >> 0x1fU)))) << 0xcU) 
           | (QData)((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                              >> 0x14U))));
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_use_rs2 
        = ((0x33U == (0x7fU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) 
           | ((0x3bU == (0x7fU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) 
              | ((0x23U == (0x7fU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) 
                 | ((0x63U == (0x7fU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) 
                    | ((0x2fU == (0x7fU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) 
                       & ((8U != (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                  >> 0x19U)) & (0xaU 
                                                != 
                                                (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                 >> 0x19U))))))));
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_use_rs1 
        = ((0x13U == (0x7fU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) 
           | ((0x33U == (0x7fU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) 
              | ((0x1bU == (0x7fU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) 
                 | ((0x3bU == (0x7fU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) 
                    | ((3U == (0x7fU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) 
                       | ((0x23U == (0x7fU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) 
                          | ((0x63U == (0x7fU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) 
                             | ((0x67U == (0x7fU & 
                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) 
                                | ((0x2fU == (0x7fU 
                                              & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) 
                                   | ((0x73U == (0x7fU 
                                                 & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) 
                                      & ((1U == (7U 
                                                 & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                    >> 0xcU))) 
                                         | ((2U == 
                                             (7U & 
                                              (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                               >> 0xcU))) 
                                            | (3U == 
                                               (7U 
                                                & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                   >> 0xcU)))))))))))))));
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_if_mem 
        = (IData)(((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
                    >> 0x10U) & (0U != (0x180U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U]))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_issue 
        = (((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
             >> 0xaU) & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                         >> 0x14U)) & (~ ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_done_q) 
                                          | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_issued_q))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fault_pc 
        = ((0x10000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU])
            ? (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU])) 
                << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xbU])) 
                              << 0x17U) | ((QData)((IData)(
                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xaU])) 
                                           >> 9U)))
            : ((0x100000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                ? (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])) 
                    << 0x38U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU])) 
                                  << 0x18U) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU])) 
                                               >> 8U)))
                : ((0x10000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU])
                    ? (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU])) 
                        << 0x37U) | (((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xbU])) 
                                      << 0x17U) | ((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU])) 
                                                   >> 9U)))
                    : 0ULL)));
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_csr_rdata 
        = ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
            >> 0x1fU) ? ((0x40000000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                          ? 0ULL : ((0x20000000U & 
                                     vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                     ? ((0x10000000U 
                                         & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                         ? ((0x8000000U 
                                             & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                             ? 0ULL
                                             : ((0x4000000U 
                                                 & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                 ? 0ULL
                                                 : 
                                                ((0x2000000U 
                                                  & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                  ? 0ULL
                                                  : 
                                                 ((0x1000000U 
                                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                   ? 0ULL
                                                   : 
                                                  ((0x800000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                    ? 0ULL
                                                    : 
                                                   ((0x400000U 
                                                     & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                     ? 0ULL
                                                     : 
                                                    ((0x200000U 
                                                      & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                      ? 0ULL
                                                      : 
                                                     ((0x100000U 
                                                       & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                       ? 0ULL
                                                       : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__cycle_cnt))))))))
                                         : 0ULL) : 0ULL))
            : ((0x40000000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                ? 0ULL : ((0x20000000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                           ? ((0x10000000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                               ? ((0x8000000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                   ? ((0x4000000U & 
                                       vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                       ? 0ULL : ((0x2000000U 
                                                  & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                  ? 
                                                 ((0x1000000U 
                                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                   ? 
                                                  ((0x800000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                    ? 0ULL
                                                    : 
                                                   ((0x400000U 
                                                     & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                     ? 0ULL
                                                     : 
                                                    ((0x200000U 
                                                      & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                      ? 0ULL
                                                      : 
                                                     ((0x100000U 
                                                       & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                       ? 0ULL
                                                       : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpaddr0_r))))
                                                   : 
                                                  ((0x800000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                    ? 0ULL
                                                    : 
                                                   ((0x400000U 
                                                     & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                     ? 0ULL
                                                     : 
                                                    ((0x200000U 
                                                      & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                      ? 0ULL
                                                      : 
                                                     ((0x100000U 
                                                       & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                       ? 0ULL
                                                       : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpcfg0_r)))))
                                                  : 0ULL))
                                   : ((0x4000000U & 
                                       vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                       ? ((0x2000000U 
                                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                           ? 0ULL : 
                                          ((0x1000000U 
                                            & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                            ? 0ULL : 
                                           ((0x800000U 
                                             & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                             ? 0ULL
                                             : ((0x400000U 
                                                 & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                 ? 
                                                ((0x200000U 
                                                  & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                  ? 0ULL
                                                  : 
                                                 ((0x100000U 
                                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                   ? 0ULL
                                                   : 
                                                  (0xfffffffffffff777ULL 
                                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mip_raw)))
                                                 : 
                                                ((0x200000U 
                                                  & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                  ? 
                                                 ((0x100000U 
                                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                   ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mtval
                                                   : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mcause)
                                                  : 
                                                 ((0x100000U 
                                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                   ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mepc
                                                   : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mscratch))))))
                                       : ((0x2000000U 
                                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                           ? 0ULL : 
                                          ((0x1000000U 
                                            & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                            ? 0ULL : 
                                           ((0x800000U 
                                             & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                             ? ((0x400000U 
                                                 & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                 ? 0ULL
                                                 : 
                                                ((0x200000U 
                                                  & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                  ? 
                                                 ((0x100000U 
                                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                   ? 0ULL
                                                   : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_menvcfg_r)
                                                  : 0ULL))
                                             : ((0x400000U 
                                                 & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                 ? 
                                                ((0x200000U 
                                                  & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                  ? 
                                                 ((0x100000U 
                                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                   ? 0ULL
                                                   : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mcounteren_r)
                                                  : 
                                                 ((0x100000U 
                                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                   ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mtvec
                                                   : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mie))
                                                 : 
                                                ((0x200000U 
                                                  & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                  ? 
                                                 ((0x100000U 
                                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                   ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mideleg_r
                                                   : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r)
                                                  : 
                                                 ((0x100000U 
                                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                   ? 0ULL
                                                   : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus))))))))
                               : 0ULL) : ((0x10000000U 
                                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                           ? ((0x8000000U 
                                               & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                               ? ((0x4000000U 
                                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                   ? 0ULL
                                                   : 
                                                  ((0x2000000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                    ? 0ULL
                                                    : 
                                                   ((0x1000000U 
                                                     & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                     ? 0ULL
                                                     : 
                                                    ((0x800000U 
                                                      & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                      ? 0ULL
                                                      : 
                                                     ((0x400000U 
                                                       & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                       ? 0ULL
                                                       : 
                                                      ((0x200000U 
                                                        & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                        ? 0ULL
                                                        : 
                                                       ((0x100000U 
                                                         & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                         ? 0ULL
                                                         : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_satp)))))))
                                               : ((0x4000000U 
                                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                   ? 
                                                  ((0x2000000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                    ? 0ULL
                                                    : 
                                                   ((0x1000000U 
                                                     & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                     ? 0ULL
                                                     : 
                                                    ((0x800000U 
                                                      & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                      ? 0ULL
                                                      : 
                                                     ((0x400000U 
                                                       & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                       ? 
                                                      ((0x200000U 
                                                        & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                        ? 0ULL
                                                        : 
                                                       ((0x100000U 
                                                         & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                         ? 0ULL
                                                         : 
                                                        (0x222ULL 
                                                         & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mip_raw)))
                                                       : 
                                                      ((0x200000U 
                                                        & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                        ? 
                                                       ((0x100000U 
                                                         & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                         ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_stval_r
                                                         : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_scause_r)
                                                        : 
                                                       ((0x100000U 
                                                         & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                         ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_sepc_r
                                                         : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_sscratch_r))))))
                                                   : 
                                                  ((0x2000000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                    ? 0ULL
                                                    : 
                                                   ((0x1000000U 
                                                     & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                     ? 0ULL
                                                     : 
                                                    ((0x800000U 
                                                      & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                      ? 0ULL
                                                      : 
                                                     ((0x400000U 
                                                       & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                       ? 
                                                      ((0x200000U 
                                                        & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                        ? 0ULL
                                                        : 
                                                       ((0x100000U 
                                                         & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                         ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_stvec_r
                                                         : 
                                                        (0x222ULL 
                                                         & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mie)))
                                                       : 
                                                      ((0x200000U 
                                                        & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                        ? 0ULL
                                                        : 
                                                       ((0x100000U 
                                                         & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                         ? 0ULL
                                                         : 
                                                        (0x80000003000de000ULL 
                                                         & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus)))))))))
                                           : 0ULL))));
    if ((((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
           >> 0x14U) & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U] 
                        >> 0x1aU)) & ((0xfffU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U] 
                                                 >> 0xeU)) 
                                      == (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                          >> 0x14U)))) {
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_csr_rdata 
            = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U])) 
                << 0x32U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[1U])) 
                              << 0x12U) | ((QData)((IData)(
                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U])) 
                                           >> 0xeU)));
    } else if ((((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
                  >> 0x10U) & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U] 
                               >> 0x1aU)) & ((0xfffU 
                                              & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U] 
                                                 >> 0xeU)) 
                                             == (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                 >> 0x14U)))) {
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_csr_rdata 
            = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U])) 
                << 0x32U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[1U])) 
                              << 0x12U) | ((QData)((IData)(
                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U])) 
                                           >> 0xeU)));
    } else if ((((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                  >> 0x10U) & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                               >> 0x1aU)) & ((0xfffU 
                                              & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                 >> 0xeU)) 
                                             == (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                 >> 0x14U)))) {
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_csr_rdata 
            = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                << 0x32U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                              << 0x12U) | ((QData)((IData)(
                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                           >> 0xeU)));
    }
    if ((0x400U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U])) {
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_out_result = 0ULL;
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_out_valid 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_done_q;
    } else {
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_out_result 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_result;
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_out_valid 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid;
    }
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_to_mem_blocks_front 
        = (IData)(((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                    >> 0x14U) & (0U != (0xc0U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U]))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_mem_addr 
        = ((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
             << 0x38U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                           << 0x18U) | ((QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                        >> 8U))) + 
           (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U])) 
             << 0x38U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[6U])) 
                           << 0x18U) | ((QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U])) 
                                        >> 8U))));
    __Vfunc_is_mdu_cmd__0__cmd = (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                          >> 0xdU));
    __Vfunc_is_mdu_cmd__0__Vfuncout = (((((0xaU == (IData)(__Vfunc_is_mdu_cmd__0__cmd)) 
                                          | (0xbU == (IData)(__Vfunc_is_mdu_cmd__0__cmd))) 
                                         | (0xcU == (IData)(__Vfunc_is_mdu_cmd__0__cmd))) 
                                        | (0xdU == (IData)(__Vfunc_is_mdu_cmd__0__cmd))) 
                                       | (0xeU == (IData)(__Vfunc_is_mdu_cmd__0__cmd)));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_req 
        = __Vfunc_is_mdu_cmd__0__Vfuncout;
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__ex_branch_taken = 0U;
    if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U])) {
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__ex_branch_taken 
            = ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U])
                ? ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U] 
                    >> 0x1fU) ? ((0x40000000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U])
                                  ? ((((QData)((IData)(
                                                       vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
                                       << 0x38U) | 
                                      (((QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                                        << 0x18U) | 
                                       ((QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                        >> 8U))) >= 
                                     (((QData)((IData)(
                                                       vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                       << 0x38U) | 
                                      (((QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U])) 
                                        << 0x18U) | 
                                       ((QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U])) 
                                        >> 8U)))) : 
                                 ((((QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
                                    << 0x38U) | (((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                                    >> 8U))) 
                                  < (((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                      << 0x38U) | (
                                                   ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U])) 
                                                    << 0x18U) 
                                                   | ((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U])) 
                                                      >> 8U)))))
                    : ((0x40000000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U])
                        ? VL_GTES_IQQ(64, (((QData)((IData)(
                                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
                                            << 0x38U) 
                                           | (((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                                               << 0x18U) 
                                              | ((QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                                 >> 8U))), 
                                      (((QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                        << 0x38U) | 
                                       (((QData)((IData)(
                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U])) 
                                         << 0x18U) 
                                        | ((QData)((IData)(
                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U])) 
                                           >> 8U))))
                        : VL_LTS_IQQ(64, (((QData)((IData)(
                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
                                           << 0x38U) 
                                          | (((QData)((IData)(
                                                              vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                                              << 0x18U) 
                                             | ((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                                >> 8U))), 
                                     (((QData)((IData)(
                                                       vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                       << 0x38U) | 
                                      (((QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U])) 
                                        << 0x18U) | 
                                       ((QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U])) 
                                        >> 8U))))))
                : ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U] 
                             >> 0x1fU))) && ((0x40000000U 
                                              & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U])
                                              ? ((((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
                                                   << 0x38U) 
                                                  | (((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                                                      << 0x18U) 
                                                     | ((QData)((IData)(
                                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                                        >> 8U))) 
                                                 != 
                                                 (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                                   << 0x38U) 
                                                  | (((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U])) 
                                                      << 0x18U) 
                                                     | ((QData)((IData)(
                                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U])) 
                                                        >> 8U))))
                                              : ((((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
                                                   << 0x38U) 
                                                  | (((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                                                      << 0x18U) 
                                                     | ((QData)((IData)(
                                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                                        >> 8U))) 
                                                 == 
                                                 (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                                   << 0x38U) 
                                                  | (((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U])) 
                                                      << 0x18U) 
                                                     | ((QData)((IData)(
                                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U])) 
                                                        >> 8U)))))));
    }
    if ((IData)((0U != (0x30000000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U])))) {
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__ex_branch_taken = 1U;
    }
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_imm 
        = SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_imm_i;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__raw_hazard_mem 
        = (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U] 
           & (IData)((((0x14000U == (0x14000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU])) 
                       & (IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_if_mem)) 
                      & ((0U != (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
                                          >> 9U))) 
                         & (((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_use_rs1) 
                             & ((0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                          >> 0xfU)) 
                                == (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
                                             >> 9U)))) 
                            | ((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_use_rs2) 
                               & ((0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                            >> 0x14U)) 
                                  == (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
                                               >> 9U)))))))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result = 0ULL;
    if ((0x10000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])) {
        if ((0x8000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])) {
            if ((0x4000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])) {
                if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                              >> 0xdU)))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result 
                        = SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_out_result;
                }
            } else {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result 
                    = SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_out_result;
            }
        } else {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result 
                = ((0x4000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                    ? SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_out_result
                    : ((0x2000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                        ? (((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
                              << 0x38U) | (((QData)((IData)(
                                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                                            << 0x18U) 
                                           | ((QData)((IData)(
                                                              vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                              >> 8U))) 
                            < (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                << 0x38U) | (((QData)((IData)(
                                                              vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U])) 
                                              << 0x18U) 
                                             | ((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U])) 
                                                >> 8U))))
                            ? 1ULL : 0ULL) : (VL_LTS_IQQ(64, 
                                                         (((QData)((IData)(
                                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
                                                           << 0x38U) 
                                                          | (((QData)((IData)(
                                                                              vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                                                              << 0x18U) 
                                                             | ((QData)((IData)(
                                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                                                >> 8U))), 
                                                         (((QData)((IData)(
                                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                                           << 0x38U) 
                                                          | (((QData)((IData)(
                                                                              vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U])) 
                                                              << 0x18U) 
                                                             | ((QData)((IData)(
                                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U])) 
                                                                >> 8U))))
                                               ? 1ULL
                                               : 0ULL)));
        }
    } else {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result 
            = ((0x8000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                ? ((0x4000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                    ? ((0x2000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                        ? ((0x20000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                            ? (QData)((IData)(VL_SHIFTRS_III(32,32,5, 
                                                             ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU] 
                                                               << 0x18U) 
                                                              | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U] 
                                                                 >> 8U)), 
                                                             (0x1fU 
                                                              & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
                                                                 >> 8U)))))
                            : VL_SHIFTRS_QQI(64,64,6, 
                                             (((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
                                               << 0x38U) 
                                              | (((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                                                  << 0x18U) 
                                                 | ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                                    >> 8U))), 
                                             (0x3fU 
                                              & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
                                                 >> 8U))))
                        : ((0x20000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                            ? (QData)((IData)((((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU] 
                                                 << 0x18U) 
                                                | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U] 
                                                   >> 8U)) 
                                               >> (0x1fU 
                                                   & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
                                                      >> 8U)))))
                            : ((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
                                 << 0x38U) | (((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                                               << 0x18U) 
                                              | ((QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                                 >> 8U))) 
                               >> (0x3fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
                                            >> 8U)))))
                    : ((0x2000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                        ? ((0x20000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                            ? (QData)((IData)((((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU] 
                                                 << 0x18U) 
                                                | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U] 
                                                   >> 8U)) 
                                               << (0x1fU 
                                                   & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
                                                      >> 8U)))))
                            : ((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
                                 << 0x38U) | (((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                                               << 0x18U) 
                                              | ((QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                                 >> 8U))) 
                               << (0x3fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U] 
                                            >> 8U))))
                        : ((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
                             << 0x38U) | (((QData)((IData)(
                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                                           << 0x18U) 
                                          | ((QData)((IData)(
                                                             vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                             >> 8U))) 
                           & (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                               << 0x38U) | (((QData)((IData)(
                                                             vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U])) 
                                             << 0x18U) 
                                            | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U])) 
                                               >> 8U))))))
                : ((0x4000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                    ? ((0x2000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                        ? ((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
                             << 0x38U) | (((QData)((IData)(
                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                                           << 0x18U) 
                                          | ((QData)((IData)(
                                                             vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                             >> 8U))) 
                           | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                               << 0x38U) | (((QData)((IData)(
                                                             vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U])) 
                                             << 0x18U) 
                                            | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U])) 
                                               >> 8U))))
                        : ((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
                             << 0x38U) | (((QData)((IData)(
                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                                           << 0x18U) 
                                          | ((QData)((IData)(
                                                             vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                             >> 8U))) 
                           ^ (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                               << 0x38U) | (((QData)((IData)(
                                                             vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U])) 
                                             << 0x18U) 
                                            | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U])) 
                                               >> 8U)))))
                    : ((0x2000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])
                        ? ((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
                             << 0x38U) | (((QData)((IData)(
                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                                           << 0x18U) 
                                          | ((QData)((IData)(
                                                             vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                             >> 8U))) 
                           - (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                               << 0x38U) | (((QData)((IData)(
                                                             vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U])) 
                                             << 0x18U) 
                                            | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U])) 
                                               >> 8U))))
                        : ((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xbU])) 
                             << 0x38U) | (((QData)((IData)(
                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xaU])) 
                                           << 0x18U) 
                                          | ((QData)((IData)(
                                                             vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                                             >> 8U))) 
                           + (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[9U])) 
                               << 0x38U) | (((QData)((IData)(
                                                             vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[8U])) 
                                             << 0x18U) 
                                            | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U])) 
                                               >> 8U)))))));
    }
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__ex_result_word 
        = (((QData)((IData)((- (IData)((1U & (IData)(
                                                     (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result 
                                                      >> 0x1fU))))))) 
            << 0x20U) | (QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result)));
    if (((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
          >> 0x11U) & ((((((((0U == (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                             >> 0xdU))) 
                             | (1U == (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                               >> 0xdU)))) 
                            | (2U == (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                              >> 0xdU)))) 
                           | (3U == (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                             >> 0xdU)))) 
                          | (4U == (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                            >> 0xdU)))) 
                         | (5U == (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                           >> 0xdU)))) 
                        | (6U == (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                          >> 0xdU)))) 
                       | (7U == (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                         >> 0xdU)))))) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result 
            = SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__ex_result_word;
    }
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_store_strobe 
        = ((0x20U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U])
            ? 0U : (0xffU & ((0x10U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U])
                              ? ((8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U])
                                  ? 0xffU : ((IData)(0xfU) 
                                             << (7U 
                                                 & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_mem_addr))))
                              : ((8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U])
                                  ? ((IData)(3U) << 
                                     (7U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_mem_addr)))
                                  : ((IData)(1U) << 
                                     (7U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_mem_addr)))))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_misalign = 0U;
    if ((IData)(((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                  >> 0x14U) & ((IData)((0U != (0xc0U 
                                               & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U]))) 
                               | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
                                  >> 0xaU))))) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_misalign 
            = (1U & ((1U == (7U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U] 
                                   >> 3U))) ? (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_mem_addr)
                      : ((2U == (7U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U] 
                                       >> 3U))) ? (0U 
                                                   != 
                                                   (3U 
                                                    & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_mem_addr)))
                          : ((3U == (7U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U] 
                                           >> 3U))) 
                             && (0U != (7U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_mem_addr)))))));
    }
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_store_data_shifted 
        = ((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U])) 
             << 0x38U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[4U])) 
                           << 0x18U) | ((QData)((IData)(
                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U])) 
                                        >> 8U))) << 
           (0x38U & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_mem_addr) 
                     << 3U)));
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_is_mdu 
        = (1U & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_req) 
                 | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
                    >> 0xaU)));
    if (SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__ex_branch_taken) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_redirect_pc 
            = ((0x10000000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[2U])
                ? (0xfffffffffffffffeULL & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_mem_addr)
                : ((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])) 
                     << 0x38U) | (((QData)((IData)(
                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU])) 
                                   << 0x18U) | ((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU])) 
                                                >> 8U))) 
                   + (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[7U])) 
                       << 0x38U) | (((QData)((IData)(
                                                     vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[6U])) 
                                     << 0x18U) | ((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[5U])) 
                                                  >> 8U)))));
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT____VdfgRegularize_he51b31ad_0_3 
            = (1U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                     >> 0x14U));
    } else {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_redirect_pc 
            = (4ULL + (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])) 
                        << 0x38U) | (((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xdU])) 
                                      << 0x18U) | ((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xcU])) 
                                                   >> 8U))));
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT____VdfgRegularize_he51b31ad_0_3 = 0U;
    }
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_ex_busy 
        = ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
            >> 0x14U) & ((~ (IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_out_valid)) 
                         & (IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_is_mdu)));
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result_ready 
        = (1U & ((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_is_mdu)
                  ? (IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_out_valid)
                  : (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[3U] 
                        >> 7U))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_instr_misalign 
        = ((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT____VdfgRegularize_he51b31ad_0_3) 
           & (0U != (3U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_redirect_pc))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_commit 
        = (IData)((0x18000U == (0x18000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU])));
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_forwardable 
        = (IData)((((0x140000U == (0x140000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])) 
                    & (IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result_ready)) 
                   & (0U != (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                      >> 8U)))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__raw_hazard_ex 
        = (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U] 
           & (IData)((((0x140000U == (0x140000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU])) 
                       & (~ (IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result_ready))) 
                      & ((0U != (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                          >> 8U))) 
                         & (((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_use_rs1) 
                             & ((0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                          >> 0xfU)) 
                                == (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                             >> 8U)))) 
                            | ((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_use_rs2) 
                               & ((0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                            >> 0x14U)) 
                                  == (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                               >> 8U)))))))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_flush_front 
        = ((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_instr_misalign)) 
           & (IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT____VdfgRegularize_he51b31ad_0_3));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[0U] 
        = (IData)((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U])) 
                    << 0x3dU) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[4U])) 
                                  << 0x1dU) | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[3U])) 
                                               >> 3U))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[1U] 
        = (IData)(((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U])) 
                     << 0x3dU) | (((QData)((IData)(
                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[4U])) 
                                   << 0x1dU) | ((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[3U])) 
                                                >> 3U))) 
                   >> 0x20U));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[2U] 
        = ((0xfffff800U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[2U]) 
           | ((0x700U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U] 
                         << 4U)) | (0xffU & ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[3U] 
                                              << 5U) 
                                             | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[2U] 
                                                >> 0x1bU)))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[2U] 
        = ((0x7ffU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[2U]) 
           | ((IData)((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])) 
                        << 0x3dU) | (((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U])) 
                                      << 0x1dU) | ((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U])) 
                                                   >> 3U)))) 
              << 0xbU));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[3U] 
        = (((IData)((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])) 
                      << 0x3dU) | (((QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U])) 
                                    << 0x1dU) | ((QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U])) 
                                                 >> 3U)))) 
            >> 0x15U) | ((IData)(((((QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])) 
                                    << 0x3dU) | (((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U])) 
                                                  << 0x1dU) 
                                                 | ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U])) 
                                                    >> 3U))) 
                                  >> 0x20U)) << 0xbU));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[4U] 
        = ((0x800U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[4U]) 
           | (0xfffU & ((IData)(((((QData)((IData)(
                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])) 
                                   << 0x3dU) | (((QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U])) 
                                                 << 0x1dU) 
                                                | ((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U])) 
                                                   >> 3U))) 
                                 >> 0x20U)) >> 0x15U)));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[4U] 
        = ((0x7ffU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[4U]) 
           | (0xfffU & (((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_if_mem) 
                         & ((~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U] 
                                >> 0xaU)) & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_commit)))) 
                        << 0xbU)));
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT____VdfgRegularize_h47660625_0_10 
        = (1U & ((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__halted)) 
                 & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_commit))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs2_val 
        = ((0U == (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                            >> 0x14U))) ? 0ULL : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr
           [(0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                      >> 0x14U))]);
    if ((((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_use_rs2) 
          & (IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_forwardable)) 
         & ((0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                      >> 8U)) == (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                           >> 0x14U))))) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs2_val 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result;
    } else if (((((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_use_rs2) 
                  & (0x14000U == (0x14000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU]))) 
                 & (0U != (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
                                    >> 9U)))) & ((0x1fU 
                                                  & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
                                                     >> 9U)) 
                                                 == 
                                                 (0x1fU 
                                                  & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                     >> 0x14U))))) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs2_val 
            = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[9U])) 
                << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[8U])) 
                              << 0x17U) | ((QData)((IData)(
                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])) 
                                           >> 9U)));
    } else if (((((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_use_rs2) 
                  & (0x14000U == (0x14000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU]))) 
                 & (0U != (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                                    >> 9U)))) & ((0x1fU 
                                                  & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                                                     >> 9U)) 
                                                 == 
                                                 (0x1fU 
                                                  & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                     >> 0x14U))))) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs2_val 
            = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[9U])) 
                << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[8U])) 
                              << 0x17U) | ((QData)((IData)(
                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) 
                                           >> 9U)));
    }
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs1_val 
        = ((0U == (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                            >> 0xfU))) ? 0ULL : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr
           [(0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                      >> 0xfU))]);
    if ((((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_use_rs1) 
          & (IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_forwardable)) 
         & ((0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                      >> 8U)) == (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                           >> 0xfU))))) {
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs1_val 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result;
    } else if (((((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_use_rs1) 
                  & (0x14000U == (0x14000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU]))) 
                 & (0U != (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
                                    >> 9U)))) & ((0x1fU 
                                                  & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
                                                     >> 9U)) 
                                                 == 
                                                 (0x1fU 
                                                  & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                     >> 0xfU))))) {
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs1_val 
            = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[9U])) 
                << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[8U])) 
                              << 0x17U) | ((QData)((IData)(
                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])) 
                                           >> 9U)));
    } else if (((((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_use_rs1) 
                  & (0x14000U == (0x14000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU]))) 
                 & (0U != (0x1fU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                                    >> 9U)))) & ((0x1fU 
                                                  & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                                                     >> 9U)) 
                                                 == 
                                                 (0x1fU 
                                                  & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                     >> 0xfU))))) {
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs1_val 
            = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[9U])) 
                << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[8U])) 
                              << 0x17U) | ((QData)((IData)(
                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) 
                                           >> 9U)));
    }
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT____VdfgRegularize_h47660625_0_12 
        = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__raw_hazard_ex) 
           | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__raw_hazard_mem));
    if ((0x5006bU != vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
        if ((0x40U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
            if ((0x20U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                if ((0x10U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                  >> 3U)))) {
                        if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                      >> 2U)))) {
                            if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    if ((0x73U != vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                        if ((0x30200073U 
                                             != vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                            if ((0x10200073U 
                                                 != 
                                                 vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                if (
                                                    (0x10500073U 
                                                     != 
                                                     vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                    if (
                                                        (0x12000073U 
                                                         != 
                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                        if (
                                                            (0x100073U 
                                                             == 
                                                             vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_ebreak = 1U;
                                                        }
                                                        if (
                                                            (0x100073U 
                                                             != 
                                                             vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                            if (
                                                                ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode) 
                                                                 >= 
                                                                 (3U 
                                                                  & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                     >> 0x1cU)))) {
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen 
                                                                    = 
                                                                    (0U 
                                                                     != 
                                                                     (0x1fU 
                                                                      & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                         >> 7U)));
                                                                if (
                                                                    (0x4000U 
                                                                     & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                                    if (
                                                                        (1U 
                                                                         & (~ 
                                                                            (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                             >> 0xdU)))) {
                                                                        if (
                                                                            (1U 
                                                                             & (~ 
                                                                                (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                                >> 0xcU)))) {
                                                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_valid = 0U;
                                                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 0U;
                                                                        }
                                                                    }
                                                                    if (
                                                                        (0x2000U 
                                                                         & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wen 
                                                                            = 
                                                                            ((0x1000U 
                                                                              & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                                              ? 
                                                                             (0U 
                                                                              != 
                                                                              (0x1fU 
                                                                               & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                                >> 0xfU)))
                                                                              : 
                                                                             (0U 
                                                                              != 
                                                                              (0x1fU 
                                                                               & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                                >> 0xfU))));
                                                                    } else if (
                                                                               (0x1000U 
                                                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wen = 1U;
                                                                    }
                                                                } else {
                                                                    if (
                                                                        (1U 
                                                                         & (~ 
                                                                            (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                             >> 0xdU)))) {
                                                                        if (
                                                                            (1U 
                                                                             & (~ 
                                                                                (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                                >> 0xcU)))) {
                                                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_valid = 0U;
                                                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 0U;
                                                                        }
                                                                    }
                                                                    if (
                                                                        (0x2000U 
                                                                         & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wen 
                                                                            = 
                                                                            ((0x1000U 
                                                                              & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                                              ? 
                                                                             (0U 
                                                                              != 
                                                                              (0x1fU 
                                                                               & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                                >> 0xfU)))
                                                                              : 
                                                                             (0U 
                                                                              != 
                                                                              (0x1fU 
                                                                               & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                                >> 0xfU))));
                                                                    } else if (
                                                                               (0x1000U 
                                                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wen = 1U;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                    if (
                                                        (0x12000073U 
                                                         == 
                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                        if (
                                                            (1U 
                                                             <= (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode))) {
                                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_sfence = 1U;
                                                        }
                                                    }
                                                }
                                            }
                                            if ((0x10200073U 
                                                 == 
                                                 vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                if (
                                                    (1U 
                                                     <= (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode))) {
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_sret = 1U;
                                                }
                                            }
                                        }
                                        if ((0x30200073U 
                                             == vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                            if ((3U 
                                                 <= (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode))) {
                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_mret = 1U;
                                            }
                                        }
                                    }
                                    if ((0x73U == vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_ecall = 1U;
                                    }
                                }
                            }
                        }
                    }
                    if ((8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                    } else if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                    } else if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((0x73U != vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((0x30200073U == 
                                     vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    if ((3U > (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode))) {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                                    }
                                } else if ((0x10200073U 
                                            == vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    if ((1U > (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode))) {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                                    }
                                } else if ((0x10500073U 
                                            != vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    if ((0x12000073U 
                                         == vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                        if ((1U > (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode))) {
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                                        }
                                    } else if ((0x100073U 
                                                != 
                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                        if (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode) 
                                             < (3U 
                                                & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                   >> 0x1cU)))) {
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                                        } else if (
                                                   (0x4000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                            if ((1U 
                                                 & (~ 
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                     >> 0xdU)))) {
                                                if (
                                                    (1U 
                                                     & (~ 
                                                        (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                         >> 0xcU)))) {
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                                                }
                                            }
                                        } else if (
                                                   (1U 
                                                    & (~ 
                                                       (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                        >> 0xdU)))) {
                                            if ((1U 
                                                 & (~ 
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                     >> 0xcU)))) {
                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                        }
                    } else {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                    }
                } else if ((8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((1U & (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U]))) {
                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                            }
                            if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 1U;
                            }
                        } else {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                        }
                    } else {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                    }
                } else if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((1U & (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U]))) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                        }
                        if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((0U == (7U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                              >> 0xcU)))) {
                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 1U;
                            }
                        }
                    } else {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                    }
                } else if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((1U & (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U]))) {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                    }
                } else {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                }
                if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                              >> 4U)))) {
                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                  >> 3U)))) {
                        if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                      >> 2U)))) {
                            if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_br_funct3 
                                        = (7U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                 >> 0xcU));
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_branch = 1U;
                                }
                            }
                        }
                        if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    if ((0U == (7U 
                                                & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                   >> 0xcU)))) {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_jalr = 1U;
                                    }
                                }
                            }
                        }
                    }
                    if ((8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wb_pc4 = 1U;
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_jal = 1U;
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_imm 
                                        = (((- (QData)((IData)(
                                                               (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                >> 0x1fU)))) 
                                            << 0x15U) 
                                           | (QData)((IData)(
                                                             (((0x100000U 
                                                                & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                   >> 0xbU)) 
                                                               | ((0xff000U 
                                                                   & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U]) 
                                                                  | (0x800U 
                                                                     & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                        >> 9U)))) 
                                                              | (0x7feU 
                                                                 & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                    >> 0x14U))))));
                                }
                            }
                        }
                    } else if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((0U == (7U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                  >> 0xcU)))) {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wb_pc4 = 1U;
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_imm 
                                        = SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_imm_i;
                                }
                            }
                        }
                    } else if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_imm 
                                = (((- (QData)((IData)(
                                                       (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                        >> 0x1fU)))) 
                                    << 0xdU) | (QData)((IData)(
                                                               (((0x1000U 
                                                                  & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                     >> 0x13U)) 
                                                                 | (0x800U 
                                                                    & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                       << 4U))) 
                                                                | ((0x7e0U 
                                                                    & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                       >> 0x14U)) 
                                                                   | (0x1eU 
                                                                      & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                         >> 7U)))))));
                        }
                    }
                }
            } else {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
            }
        } else if ((0x20U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
            if ((0x10U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                if ((8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                    } else if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((1U & (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U]))) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                        }
                    } else {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                    }
                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((1U == (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                            >> 0x19U))) {
                                    if ((0x4000U & 
                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 1U;
                                    } else if ((1U 
                                                & (~ 
                                                   (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                    >> 0xdU)))) {
                                        if ((1U & (~ 
                                                   (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                    >> 0xcU)))) {
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 1U;
                                        }
                                    }
                                } else if ((0U == (7U 
                                                   & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                      >> 0xcU)))) {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 1U;
                                } else if ((1U == (7U 
                                                   & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                      >> 0xcU)))) {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 1U;
                                } else if ((5U == (7U 
                                                   & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                      >> 0xcU)))) {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 1U;
                                }
                            }
                        }
                    }
                } else if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((1U & (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U]))) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                        }
                        if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 1U;
                        }
                    } else {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                    }
                } else if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((1U & (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U]))) {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                    }
                    if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((1U == (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                    >> 0x19U))) {
                            if ((0x4000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 1U;
                            } else if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                 >> 0xdU)))) {
                                if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                              >> 0xcU)))) {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 1U;
                                }
                            }
                        } else {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 1U;
                        }
                    }
                } else {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                }
            } else if ((8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((2U == (7U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                              >> 0xcU)))) {
                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen 
                                    = (0U != (0x1fU 
                                              & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                 >> 7U)));
                                if ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                     >> 0x1fU)) {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 0U;
                                } else if ((0x40000000U 
                                            & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 0U;
                                } else if ((0x20000000U 
                                            & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 0U;
                                }
                            } else {
                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                            }
                        } else {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                        }
                    } else {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                    }
                } else {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                }
            } else if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
            } else if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                if ((1U & (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U]))) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                }
            } else {
                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
            }
            if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                          >> 4U)))) {
                if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((0x4000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_valid = 0U;
                                }
                            }
                        }
                    }
                }
                if ((8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((2U == (7U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                  >> 0xcU)))) {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_imm = 0ULL;
                                }
                            }
                        }
                    }
                } else if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                     >> 2U)))) {
                    if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_imm 
                                = (((- (QData)((IData)(
                                                       (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                        >> 0x1fU)))) 
                                    << 0xcU) | (QData)((IData)(
                                                               ((0xfe0U 
                                                                 & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                    >> 0x14U)) 
                                                                | (0x1fU 
                                                                   & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                      >> 7U))))));
                        }
                    }
                }
            }
        } else {
            if ((0x10U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                if ((8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                    } else if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((1U & (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U]))) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                        }
                    } else {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                    }
                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((0U == (7U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                  >> 0xcU)))) {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 1U;
                                } else if ((1U == (7U 
                                                   & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                      >> 0xcU)))) {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 1U;
                                } else if ((5U == (7U 
                                                   & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                      >> 0xcU)))) {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 1U;
                                }
                            }
                        }
                    }
                } else if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((1U & (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U]))) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                        }
                        if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 1U;
                        }
                    } else {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                    }
                } else if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((1U & (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U]))) {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                    }
                    if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 1U;
                    }
                } else {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                }
            } else {
                if ((8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((1U & (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U]))) {
                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                            }
                        } else {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                        }
                    } else {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                    }
                } else if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                } else if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((1U & (~ vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U]))) {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                    }
                } else {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 1U;
                }
                if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 1U;
                            }
                        }
                    }
                }
            }
            if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                          >> 4U)))) {
                if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((0x4000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    if ((0x2000U & 
                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                        if ((0x1000U 
                                             & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_valid = 0U;
                                        }
                                    }
                                }
                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_imm 
                                    = SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_imm_i;
                            }
                        }
                    }
                }
            }
        }
        if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                      >> 6U)))) {
            if ((0x20U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                if ((0x10U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                      >> 2U)))) {
                            if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    if ((1U == (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                >> 0x19U))) {
                                        if ((0x4000U 
                                             & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_word = 1U;
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_alu_cmd 
                                                = (
                                                   (0x2000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                    ? 
                                                   ((0x1000U 
                                                     & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                     ? 0xeU
                                                     : 0xdU)
                                                    : 
                                                   ((0x1000U 
                                                     & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                     ? 0xcU
                                                     : 0xbU));
                                        } else if (
                                                   (1U 
                                                    & (~ 
                                                       (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                        >> 0xdU)))) {
                                            if ((1U 
                                                 & (~ 
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                     >> 0xcU)))) {
                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_word = 1U;
                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_alu_cmd = 0xaU;
                                            }
                                        }
                                    } else if ((0U 
                                                == 
                                                (7U 
                                                 & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                    >> 0xcU)))) {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_word = 1U;
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_alu_cmd 
                                            = ((0x40000000U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                ? 1U
                                                : 0U);
                                    } else if ((1U 
                                                == 
                                                (7U 
                                                 & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                    >> 0xcU)))) {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_word = 1U;
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_alu_cmd = 5U;
                                    } else if ((5U 
                                                == 
                                                (7U 
                                                 & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                    >> 0xcU)))) {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_word = 1U;
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_alu_cmd 
                                            = ((0x40000000U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                ? 7U
                                                : 6U);
                                    }
                                }
                            }
                        }
                    } else if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                         >> 2U)))) {
                        if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((1U == (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                            >> 0x19U))) {
                                    if ((0x4000U & 
                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_alu_cmd 
                                            = ((0x2000U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                ? (
                                                   (0x1000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                    ? 0xeU
                                                    : 0xdU)
                                                : (
                                                   (0x1000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                    ? 0xcU
                                                    : 0xbU));
                                    } else if ((1U 
                                                & (~ 
                                                   (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                    >> 0xdU)))) {
                                        if ((1U & (~ 
                                                   (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                    >> 0xcU)))) {
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_alu_cmd = 0xaU;
                                        }
                                    }
                                } else {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_alu_cmd 
                                        = ((0x4000U 
                                            & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                            ? ((0x2000U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                ? (
                                                   (0x1000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                    ? 4U
                                                    : 3U)
                                                : (
                                                   (0x1000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                    ? 
                                                   ((0x40000000U 
                                                     & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                     ? 7U
                                                     : 6U)
                                                    : 2U))
                                            : ((0x2000U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                ? (
                                                   (0x1000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                    ? 9U
                                                    : 8U)
                                                : (
                                                   (0x1000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                    ? 5U
                                                    : 
                                                   ((0x40000000U 
                                                     & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                     ? 1U
                                                     : 0U))));
                                }
                            }
                        }
                    }
                }
                if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                              >> 4U)))) {
                    if ((8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    if ((2U == (7U 
                                                & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                   >> 0xcU)))) {
                                        if ((1U & (~ 
                                                   (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                    >> 0x1fU)))) {
                                            if ((1U 
                                                 & (~ 
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                     >> 0x1eU)))) {
                                                if (
                                                    (1U 
                                                     & (~ 
                                                        (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                         >> 0x1dU)))) {
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_amo_cmd 
                                                        = 
                                                        ((0x10000000U 
                                                          & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                          ? 
                                                         ((0x8000000U 
                                                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                           ? 7U
                                                           : 6U)
                                                          : 
                                                         ((0x8000000U 
                                                           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                           ? 4U
                                                           : 8U));
                                                }
                                            }
                                        }
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_mem_size = 2U;
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_amo = 1U;
                                        if ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                             >> 0x1fU)) {
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_amo = 0U;
                                        } else if (
                                                   (0x40000000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_amo = 0U;
                                        } else if (
                                                   (0x20000000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_amo = 0U;
                                        }
                                    }
                                }
                            }
                        }
                    } else if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                         >> 2U)))) {
                        if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                              >> 0xeU)))) {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_mem_size 
                                        = ((0x2000U 
                                            & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                            ? ((0x1000U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                ? 3U
                                                : 2U)
                                            : ((0x1000U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                ? 1U
                                                : 0U));
                                }
                            }
                        }
                    }
                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                  >> 3U)))) {
                        if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                      >> 2U)))) {
                            if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_store = 1U;
                                }
                            }
                        }
                    }
                }
            } else {
                if ((0x10U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                      >> 2U)))) {
                            if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    if ((0U == (7U 
                                                & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                   >> 0xcU)))) {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_word = 1U;
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_alu_cmd = 0U;
                                    } else if ((1U 
                                                == 
                                                (7U 
                                                 & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                    >> 0xcU)))) {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_word = 1U;
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_alu_cmd = 5U;
                                    } else if ((5U 
                                                == 
                                                (7U 
                                                 & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                    >> 0xcU)))) {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_word = 1U;
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_alu_cmd 
                                            = ((0x40000000U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                ? 7U
                                                : 6U);
                                    }
                                }
                            }
                        }
                    } else if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                         >> 2U)))) {
                        if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_alu_cmd 
                                    = ((0x4000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                        ? ((0x2000U 
                                            & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                            ? ((0x1000U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                ? 4U
                                                : 3U)
                                            : ((0x1000U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                ? (
                                                   (0x40000000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                    ? 7U
                                                    : 6U)
                                                : 2U))
                                        : ((0x2000U 
                                            & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                            ? ((0x1000U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                ? 9U
                                                : 8U)
                                            : ((0x1000U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                ? 5U
                                                : 0U)));
                            }
                        }
                    }
                }
                if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                              >> 4U)))) {
                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                  >> 3U)))) {
                        if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                      >> 2U)))) {
                            if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    if ((0x4000U & 
                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                        if ((0x2000U 
                                             & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                            if ((1U 
                                                 & (~ 
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                     >> 0xcU)))) {
                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_mem_size = 2U;
                                            }
                                        } else {
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_mem_size 
                                                = (
                                                   (0x1000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                    ? 1U
                                                    : 0U);
                                        }
                                    } else {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_mem_size 
                                            = ((0x2000U 
                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                ? (
                                                   (0x1000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                    ? 3U
                                                    : 2U)
                                                : (
                                                   (0x1000U 
                                                    & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                    ? 1U
                                                    : 0U));
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                          >> 5U)))) {
                if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                              >> 4U)))) {
                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                  >> 3U)))) {
                        if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                      >> 2U)))) {
                            if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    if ((0x4000U & 
                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                        if ((0x2000U 
                                             & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                            if ((1U 
                                                 & (~ 
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                     >> 0xcU)))) {
                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_mem_unsigned = 1U;
                                            }
                                        } else {
                                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_mem_unsigned = 1U;
                                        }
                                    } else {
                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_mem_unsigned = 0U;
                                    }
                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_load = 1U;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_load_pmp_fault 
        = ((((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__translate_en)) 
             & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[4U] 
                >> 0xbU)) & (0U == (0xffU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[2U]))) 
           & ([&]() {
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__mode 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__paddr 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpaddr0_r;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__cfg 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpcfg0_r;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__addr 
                    = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[4U])) 
                        << 0x35U) | (((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[3U])) 
                                      << 0x15U) | ((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[2U])) 
                                                   >> 0xbU)));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__active 
                    = (0U != (3U & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__cfg 
                                            >> 3U))));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__paddr 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__paddr;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__cfg 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__cfg;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__addr 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__addr;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__a_mode 
                    = (3U & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__cfg 
                                     >> 3U)));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__Vfuncout = 0U;
                if ((2U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__a_mode))) {
                    if ((1U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__a_mode))) {
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__ones = 0U;
                        while ((VL_GTS_III(32, 0x36U, vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__ones) 
                                & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__paddr 
                                           >> (0x3fU 
                                               & vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__ones))))) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__ones 
                                = ((IData)(1U) + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__ones);
                        }
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__base 
                            = (0xfffffffffffffcULL 
                               & ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__paddr 
                                   << 2U) & (~ (VL_SHIFTL_QQI(64,64,32, 1ULL, 
                                                              ((IData)(3U) 
                                                               + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__ones)) 
                                                - 1ULL))));
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__top 
                            = (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__base 
                               + VL_SHIFTL_QQI(64,64,32, 1ULL, 
                                               ((IData)(3U) 
                                                + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__ones)));
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__Vfuncout 
                            = ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__addr 
                                >= vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__base) 
                               & (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__addr 
                                  < vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__top));
                    } else {
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__Vfuncout 
                            = ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__addr 
                                >> 2U) == (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__paddr 
                                           >> 2U));
                    }
                } else if ((1U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__a_mode))) {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__top 
                        = (0xfffffffffffffcULL & (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__paddr 
                                                  << 2U));
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__base = 0ULL;
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__Vfuncout 
                        = (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__addr 
                           < vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__top);
                } else {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__Vfuncout = 0U;
                }
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__hit 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__Vfuncout;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__allow 
                    = (1U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__cfg));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__Vfuncout 
                    = ((3U != (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__mode)) 
                       && ((IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__active) 
                           && ((1U & (~ (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__hit))) 
                               || (1U & (~ (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__allow))))));
            }(), (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__Vfuncout)));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_store_pmp_fault 
        = ((((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__translate_en)) 
             & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[4U] 
                >> 0xbU)) & (0U != (0xffU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[2U]))) 
           & ([&]() {
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__mode 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__paddr 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpaddr0_r;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__cfg 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpcfg0_r;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__addr 
                    = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[4U])) 
                        << 0x35U) | (((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[3U])) 
                                      << 0x15U) | ((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[2U])) 
                                                   >> 0xbU)));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__active 
                    = (0U != (3U & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__cfg 
                                            >> 3U))));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__paddr 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__paddr;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__cfg 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__cfg;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__addr 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__addr;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__a_mode 
                    = (3U & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__cfg 
                                     >> 3U)));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__Vfuncout = 0U;
                if ((2U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__a_mode))) {
                    if ((1U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__a_mode))) {
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__ones = 0U;
                        while ((VL_GTS_III(32, 0x36U, vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__ones) 
                                & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__paddr 
                                           >> (0x3fU 
                                               & vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__ones))))) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__ones 
                                = ((IData)(1U) + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__ones);
                        }
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__base 
                            = (0xfffffffffffffcULL 
                               & ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__paddr 
                                   << 2U) & (~ (VL_SHIFTL_QQI(64,64,32, 1ULL, 
                                                              ((IData)(3U) 
                                                               + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__ones)) 
                                                - 1ULL))));
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__top 
                            = (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__base 
                               + VL_SHIFTL_QQI(64,64,32, 1ULL, 
                                               ((IData)(3U) 
                                                + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__ones)));
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__Vfuncout 
                            = ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__addr 
                                >= vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__base) 
                               & (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__addr 
                                  < vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__top));
                    } else {
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__Vfuncout 
                            = ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__addr 
                                >> 2U) == (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__paddr 
                                           >> 2U));
                    }
                } else if ((1U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__a_mode))) {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__top 
                        = (0xfffffffffffffcULL & (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__paddr 
                                                  << 2U));
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__base = 0ULL;
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__Vfuncout 
                        = (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__addr 
                           < vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__top);
                } else {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__Vfuncout = 0U;
                }
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__hit 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__Vfuncout;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__allow 
                    = (1U & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__cfg 
                                     >> 1U)));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__Vfuncout 
                    = ((3U != (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__mode)) 
                       && ((IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__active) 
                           && ((1U & (~ (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__hit))) 
                               || (1U & (~ (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__allow))))));
            }(), (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__Vfuncout)));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op2 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs2_val;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op1 
        = SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs1_val;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wdata = 0ULL;
    if ((0x5006bU != vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
        if ((0x40U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
            if ((0x20U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                if ((0x10U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                  >> 3U)))) {
                        if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                      >> 2U)))) {
                            if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                    if ((0x73U != vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                        if ((0x30200073U 
                                             != vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                            if ((0x10200073U 
                                                 != 
                                                 vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                if (
                                                    (0x10500073U 
                                                     != 
                                                     vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                    if (
                                                        (0x12000073U 
                                                         != 
                                                         vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                        if (
                                                            (0x100073U 
                                                             != 
                                                             vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                            if (
                                                                ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode) 
                                                                 >= 
                                                                 (3U 
                                                                  & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                     >> 0x1cU)))) {
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op2 = 0ULL;
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op1 
                                                                    = SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_csr_rdata;
                                                                if (
                                                                    (0x4000U 
                                                                     & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                                    if (
                                                                        (0x2000U 
                                                                         & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wdata 
                                                                            = 
                                                                            ((0x1000U 
                                                                              & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                                              ? 
                                                                             (SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_csr_rdata 
                                                                              & (~ (QData)((IData)(
                                                                                (0x1fU 
                                                                                & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                                >> 0xfU))))))
                                                                              : 
                                                                             (SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_csr_rdata 
                                                                              | (QData)((IData)(
                                                                                (0x1fU 
                                                                                & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                                >> 0xfU))))));
                                                                    } else if (
                                                                               (0x1000U 
                                                                                & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wdata 
                                                                            = (QData)((IData)(
                                                                                (0x1fU 
                                                                                & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                                >> 0xfU))));
                                                                    }
                                                                } else if (
                                                                           (0x2000U 
                                                                            & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wdata 
                                                                        = 
                                                                        ((0x1000U 
                                                                          & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                                                          ? 
                                                                         (SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_csr_rdata 
                                                                          & (~ SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs1_val))
                                                                          : 
                                                                         (SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_csr_rdata 
                                                                          | SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs1_val));
                                                                } else if (
                                                                           (0x1000U 
                                                                            & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wdata 
                                                                        = SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs1_val;
                                                                }
                                                                vlSelfRef.__Vfunc_sanitize_csr_write__1__data 
                                                                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wdata;
                                                                vlSelfRef.__Vfunc_sanitize_csr_write__1__addr 
                                                                    = 
                                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                                     >> 0x14U);
                                                                vlSelfRef.__Vfunc_sanitize_csr_write__1__Vfuncout 
                                                                    = vlSelfRef.__Vfunc_sanitize_csr_write__1__data;
                                                                if (
                                                                    ((((((((0x300U 
                                                                            == (IData)(vlSelfRef.__Vfunc_sanitize_csr_write__1__addr)) 
                                                                           | (0x100U 
                                                                              == (IData)(vlSelfRef.__Vfunc_sanitize_csr_write__1__addr))) 
                                                                          | (0x104U 
                                                                             == (IData)(vlSelfRef.__Vfunc_sanitize_csr_write__1__addr))) 
                                                                         | (0x144U 
                                                                            == (IData)(vlSelfRef.__Vfunc_sanitize_csr_write__1__addr))) 
                                                                        | (0x302U 
                                                                           == (IData)(vlSelfRef.__Vfunc_sanitize_csr_write__1__addr))) 
                                                                       | (0x303U 
                                                                          == (IData)(vlSelfRef.__Vfunc_sanitize_csr_write__1__addr))) 
                                                                      | (0x305U 
                                                                         == (IData)(vlSelfRef.__Vfunc_sanitize_csr_write__1__addr))) 
                                                                     | (0x105U 
                                                                        == (IData)(vlSelfRef.__Vfunc_sanitize_csr_write__1__addr)))) {
                                                                    vlSelfRef.__Vfunc_sanitize_csr_write__1__Vfuncout 
                                                                        = 
                                                                        ((0x300U 
                                                                          == (IData)(vlSelfRef.__Vfunc_sanitize_csr_write__1__addr))
                                                                          ? 
                                                                         (0x7e79bbULL 
                                                                          & vlSelfRef.__Vfunc_sanitize_csr_write__1__data)
                                                                          : 
                                                                         ((0x100U 
                                                                           == (IData)(vlSelfRef.__Vfunc_sanitize_csr_write__1__addr))
                                                                           ? 
                                                                          (0x80000003000de000ULL 
                                                                           & vlSelfRef.__Vfunc_sanitize_csr_write__1__data)
                                                                           : 
                                                                          ((0x104U 
                                                                            == (IData)(vlSelfRef.__Vfunc_sanitize_csr_write__1__addr))
                                                                            ? 
                                                                           (0x222ULL 
                                                                            & vlSelfRef.__Vfunc_sanitize_csr_write__1__data)
                                                                            : 
                                                                           ((0x144U 
                                                                             == (IData)(vlSelfRef.__Vfunc_sanitize_csr_write__1__addr))
                                                                             ? 
                                                                            (0x222ULL 
                                                                             & vlSelfRef.__Vfunc_sanitize_csr_write__1__data)
                                                                             : 
                                                                            ((0x302U 
                                                                              == (IData)(vlSelfRef.__Vfunc_sanitize_csr_write__1__addr))
                                                                              ? 
                                                                             (0xf3ffULL 
                                                                              & vlSelfRef.__Vfunc_sanitize_csr_write__1__data)
                                                                              : 
                                                                             ((0x303U 
                                                                               == (IData)(vlSelfRef.__Vfunc_sanitize_csr_write__1__addr))
                                                                               ? 
                                                                              (0x222ULL 
                                                                               & vlSelfRef.__Vfunc_sanitize_csr_write__1__data)
                                                                               : 
                                                                              (0xfffffffffffffffdULL 
                                                                               & vlSelfRef.__Vfunc_sanitize_csr_write__1__data)))))));
                                                                } else if (
                                                                           (0x344U 
                                                                            == (IData)(vlSelfRef.__Vfunc_sanitize_csr_write__1__addr))) {
                                                                    vlSelfRef.__Vfunc_sanitize_csr_write__1__Vfuncout 
                                                                        = 
                                                                        (0x333ULL 
                                                                         & vlSelfRef.__Vfunc_sanitize_csr_write__1__data);
                                                                }
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wdata 
                                                                    = vlSelfRef.__Vfunc_sanitize_csr_write__1__Vfuncout;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if ((0x20U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
            if ((0x10U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                              >> 3U)))) {
                    if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op2 
                                    = SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_imm_u;
                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op1 = 0ULL;
                            }
                        }
                    }
                }
            }
        } else if ((0x10U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
            if ((8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                              >> 2U)))) {
                    if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            if ((0U == (7U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                              >> 0xcU)))) {
                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op2 
                                    = SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_imm_i;
                            } else if ((1U == (7U & 
                                               (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                >> 0xcU)))) {
                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op2 
                                    = (QData)((IData)(
                                                      (0x1fU 
                                                       & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                          >> 0x14U))));
                            } else if ((5U == (7U & 
                                               (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                >> 0xcU)))) {
                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op2 
                                    = (QData)((IData)(
                                                      (0x1fU 
                                                       & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                          >> 0x14U))));
                            }
                        }
                    }
                }
            } else if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op2 
                            = SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_imm_u;
                    }
                }
            } else if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op2 
                        = ((0x4000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                            ? ((0x2000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                ? SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_imm_i
                                : ((0x1000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                    ? (QData)((IData)(
                                                      (0x3fU 
                                                       & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                          >> 0x14U))))
                                    : SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_imm_i))
                            : ((0x2000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                ? SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_imm_i
                                : ((0x1000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])
                                    ? (QData)((IData)(
                                                      (0x3fU 
                                                       & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                                                          >> 0x14U))))
                                    : SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_imm_i)));
                }
            }
            if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U] 
                          >> 3U)))) {
                if ((4U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                    if ((2U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                        if ((1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[0U])) {
                            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op1 
                                = (((QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[2U])) 
                                    << 0x20U) | (QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[1U])));
                        }
                    }
                }
            }
        }
    }
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_can_consume 
        = ((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT____VdfgRegularize_h47660625_0_10) 
           & ((~ (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_ex_busy) 
                   | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT____VdfgRegularize_h47660625_0_12) 
                      | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending) 
                         | ((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_if_mem) 
                            | (((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                 >> 0x14U) & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0U] 
                                              >> 2U)) 
                               | ((((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
                                     >> 0x10U) & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0U] 
                                                  >> 2U)) 
                                   | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_instr)) 
                                  | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_to_mem_blocks_front))))))) 
                  | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_flush_front))) 
              & (0U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_bubble))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pop_buf 
        = ((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_can_consume) 
           & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_valid));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_new_fire 
        = ((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending)) 
           & (IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_can_consume));
    if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__translate_en) {
        if (SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__walk_active) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[0U] = 0U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[1U] = 0U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[2U] 
                = (0x300U | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pte_addr) 
                             << 0xbU));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[3U] 
                = (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pte_addr) 
                    >> 0x15U) | ((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pte_addr 
                                          >> 0x20U)) 
                                 << 0xbU));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[4U] 
                = (0x800U | ((IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pte_addr 
                                      >> 0x20U)) >> 0x15U));
        } else if ((5U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state))) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[2U] 
                = ((0x7ffU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[2U]) 
                   | ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__phys_addr) 
                      << 0xbU));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[3U] 
                = (((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__phys_addr) 
                    >> 0x15U) | ((IData)((SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__phys_addr 
                                          >> 0x20U)) 
                                 << 0xbU));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[4U] 
                = (0xfffU & (((IData)((SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__phys_addr 
                                       >> 0x20U)) >> 0x15U) 
                             | (0x800U & ((~ ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_load_pmp_fault) 
                                              | (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_store_pmp_fault))) 
                                          << 0xbU))));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[0U] 
                = (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_wdata);
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[1U] 
                = (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_wdata 
                           >> 0x20U));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[2U] 
                = ((0xfffff800U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[2U]) 
                   | (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_size) 
                       << 8U) | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_wstrb)));
        } else {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[0U] = 0U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[1U] = 0U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[2U] = 0x300U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[3U] = 0U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[4U] = 0U;
        }
    } else {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[0U] 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[0U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[1U] 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[1U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[2U] 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[2U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[3U] 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[3U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[4U] 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_core[4U];
        if (((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_load_pmp_fault) 
             | (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_store_pmp_fault))) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[4U] 
                = (0x7ffU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[4U]);
        }
    }
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__issue_now 
        = (IData)((((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[4U] 
                     >> 0xbU) & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__req_inflight))) 
                   & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__resp_seen))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_core[0U] 
        = (IData)(__VdfgRegularize_hd87f99a1_0_0);
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_core[1U] 
        = (IData)((__VdfgRegularize_hd87f99a1_0_0 >> 0x20U));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_core[2U] 
        = (((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT____VdfgRegularize_h47660625_0_10) 
            & (~ (IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_if_mem))) 
           & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending) 
              | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_new_fire)));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_insn_pmp_fault 
        = (((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__translate_en)) 
            & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_core[2U]) 
           & ([&]() {
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__mode 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__paddr 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpaddr0_r;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__cfg 
                    = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpcfg0_r;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__addr 
                    = (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_core[1U])) 
                        << 0x20U) | (QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_core[0U])));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__active 
                    = (0U != (3U & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__cfg 
                                            >> 3U))));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__paddr 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__paddr;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__cfg 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__cfg;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__addr 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__addr;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__a_mode 
                    = (3U & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__cfg 
                                     >> 3U)));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__Vfuncout = 0U;
                if ((2U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__a_mode))) {
                    if ((1U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__a_mode))) {
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__ones = 0U;
                        while ((VL_GTS_III(32, 0x36U, vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__ones) 
                                & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__paddr 
                                           >> (0x3fU 
                                               & vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__ones))))) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__ones 
                                = ((IData)(1U) + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__ones);
                        }
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__base 
                            = (0xfffffffffffffcULL 
                               & ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__paddr 
                                   << 2U) & (~ (VL_SHIFTL_QQI(64,64,32, 1ULL, 
                                                              ((IData)(3U) 
                                                               + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__ones)) 
                                                - 1ULL))));
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__top 
                            = (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__base 
                               + VL_SHIFTL_QQI(64,64,32, 1ULL, 
                                               ((IData)(3U) 
                                                + vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__ones)));
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__Vfuncout 
                            = ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__addr 
                                >= vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__base) 
                               & (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__addr 
                                  < vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__top));
                    } else {
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__Vfuncout 
                            = ((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__addr 
                                >> 2U) == (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__paddr 
                                           >> 2U));
                    }
                } else if ((1U & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__a_mode))) {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__top 
                        = (0xfffffffffffffcULL & (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__paddr 
                                                  << 2U));
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__base = 0ULL;
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__Vfuncout 
                        = (vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__addr 
                           < vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__top);
                } else {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__Vfuncout = 0U;
                }
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__hit 
                    = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__Vfuncout;
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__allow 
                    = (1U & (IData)((vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__cfg 
                                     >> 2U)));
                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__Vfuncout 
                    = ((3U != (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__mode)) 
                       && ((IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__active) 
                           && ((1U & (~ (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__hit))) 
                               || (1U & (~ (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__allow))))));
            }(), (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__Vfuncout)));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_18 
        = ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_insn_pmp_fault) 
           | (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_insn_pmp_fault));
    if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__translate_en) {
        if ((4U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state))) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[0U] 
                = (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__phys_addr);
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[1U] 
                = (IData)((SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__phys_addr 
                           >> 0x20U));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[2U] 
                = (1U & (~ (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_insn_pmp_fault)));
        } else {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[0U] = 0U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[1U] = 0U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[2U] = 0U;
        }
    } else {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[0U] 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_core[0U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[1U] 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_core[1U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[2U] 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_core[2U];
        if (SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_insn_pmp_fault) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[2U] = 0U;
        }
    }
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__issue_now 
        = ((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__req_inflight)) 
           & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[2U]);
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__issue_now 
        = ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[2U] 
            & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__req_inflight))) 
           & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__resp_seen)));
    SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[0U] 
        = (1U | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[0U] 
                 << 0xaU));
    SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[1U] 
        = ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[0U] 
            >> 0x16U) | (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[1U] 
                         << 0xaU));
    SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[2U] 
        = (((IData)((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[4U])) 
                      << 0x35U) | (((QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[3U])) 
                                    << 0x15U) | ((QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[2U])) 
                                                 >> 0xbU)))) 
            << 0x12U) | ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[1U] 
                          >> 0x16U) | (0x3fc00U & (
                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[2U] 
                                                   << 0xaU))));
    SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[3U] 
        = (((IData)((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[4U])) 
                      << 0x35U) | (((QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[3U])) 
                                    << 0x15U) | ((QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[2U])) 
                                                 >> 0xbU)))) 
            >> 0xeU) | ((IData)(((((QData)((IData)(
                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[4U])) 
                                   << 0x35U) | (((QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[3U])) 
                                                 << 0x15U) 
                                                | ((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[2U])) 
                                                   >> 0xbU))) 
                                 >> 0x20U)) << 0x12U));
    SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[4U] 
        = ((0xfffc0000U & SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[4U]) 
           | ((IData)(((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[4U])) 
                         << 0x35U) | (((QData)((IData)(
                                                       vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[3U])) 
                                       << 0x15U) | 
                                      ((QData)((IData)(
                                                       vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[2U])) 
                                       >> 0xbU))) >> 0x20U)) 
              >> 0xeU));
    SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[4U] 
        = ((0xff83ffffU & SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[4U]) 
           | (0xfffc0000U & ((0xffc00000U & ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[4U] 
                                              << 0xbU) 
                                             & (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__issue_now) 
                                                 | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__req_inflight)) 
                                                << 0x16U))) 
                             | ((((IData)((0U != (0xffU 
                                                  & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[2U]))) 
                                  << 3U) << 0x12U) 
                                | (0x1c0000U & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[2U] 
                                                << 0xaU))))));
    SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[4U] 
        = (0x800000U | (0x7fffffU & SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[4U]));
    SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[5U] = 0U;
    SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[6U] = 0U;
    SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[7U] 
        = ((0x7ffe00U & ((IData)((((QData)((IData)(
                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[1U])) 
                                   << 0x20U) | (QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[0U])))) 
                         << 9U)) | (0xff800000U & ((IData)(
                                                           (((QData)((IData)(
                                                                             vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[1U])) 
                                                             << 0x20U) 
                                                            | (QData)((IData)(
                                                                              vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[0U])))) 
                                                   << 9U)));
    SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[8U] 
        = ((((IData)((((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[1U])) 
                       << 0x20U) | (QData)((IData)(
                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[0U])))) 
             >> 0x17U) | (0x7ffe00U & ((IData)(((((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[1U])) 
                                                  << 0x20U) 
                                                 | (QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[0U]))) 
                                                >> 0x20U)) 
                                       << 9U))) | (0xff800000U 
                                                   & ((IData)(
                                                              ((((QData)((IData)(
                                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[1U])) 
                                                                 << 0x20U) 
                                                                | (QData)((IData)(
                                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[0U]))) 
                                                               >> 0x20U)) 
                                                      << 9U)));
    SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[9U] 
        = ((0x3e00U & SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[9U]) 
           | (0x3fffU & ((IData)(((((QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[1U])) 
                                    << 0x20U) | (QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[0U]))) 
                                  >> 0x20U)) >> 0x17U)));
    SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[9U] 
        = ((0x1ffU & SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[9U]) 
           | (0x3e00U & (0x400U | ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[2U] 
                                    & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__issue_now) 
                                       | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__req_inflight))) 
                                   << 0xdU))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__any_valid = 0U;
    if ((0x400000U & SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[4U])) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__any_valid = 1U;
    }
    if (((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__any_valid)) 
         & (SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[9U] 
            >> 0xdU))) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select = 1U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__any_valid = 1U;
    }
    if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__any_valid) {
        if ((0x12dU >= (0x1ffU & ((IData)(0x97U) * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select)))) {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[0U] 
                = (((0U == (0x1fU & ((IData)(0x97U) 
                                     * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select)))
                     ? 0U : (SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[
                             ((IData)(1U) + (0xfU & 
                                             (((IData)(0x97U) 
                                               * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select) 
                                              >> 5U)))] 
                             << ((IData)(0x20U) - (0x1fU 
                                                   & ((IData)(0x97U) 
                                                      * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select))))) 
                   | (SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[
                      (0xfU & (((IData)(0x97U) * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select) 
                               >> 5U))] >> (0x1fU & 
                                            ((IData)(0x97U) 
                                             * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select))));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[1U] 
                = (((0U == (0x1fU & ((IData)(0x97U) 
                                     * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select)))
                     ? 0U : (SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[
                             ((IData)(2U) + (0xfU & 
                                             (((IData)(0x97U) 
                                               * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select) 
                                              >> 5U)))] 
                             << ((IData)(0x20U) - (0x1fU 
                                                   & ((IData)(0x97U) 
                                                      * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select))))) 
                   | (SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[
                      ((IData)(1U) + (0xfU & (((IData)(0x97U) 
                                               * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select) 
                                              >> 5U)))] 
                      >> (0x1fU & ((IData)(0x97U) * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select))));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[2U] 
                = (((0U == (0x1fU & ((IData)(0x97U) 
                                     * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select)))
                     ? 0U : (SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[
                             ((IData)(3U) + (0xfU & 
                                             (((IData)(0x97U) 
                                               * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select) 
                                              >> 5U)))] 
                             << ((IData)(0x20U) - (0x1fU 
                                                   & ((IData)(0x97U) 
                                                      * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select))))) 
                   | (SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[
                      ((IData)(2U) + (0xfU & (((IData)(0x97U) 
                                               * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select) 
                                              >> 5U)))] 
                      >> (0x1fU & ((IData)(0x97U) * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select))));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[3U] 
                = (((0U == (0x1fU & ((IData)(0x97U) 
                                     * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select)))
                     ? 0U : (SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[
                             ((IData)(4U) + (0xfU & 
                                             (((IData)(0x97U) 
                                               * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select) 
                                              >> 5U)))] 
                             << ((IData)(0x20U) - (0x1fU 
                                                   & ((IData)(0x97U) 
                                                      * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select))))) 
                   | (SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[
                      ((IData)(3U) + (0xfU & (((IData)(0x97U) 
                                               * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select) 
                                              >> 5U)))] 
                      >> (0x1fU & ((IData)(0x97U) * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select))));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[4U] 
                = (0x7fffffU & (((0U == (0x1fU & ((IData)(0x97U) 
                                                  * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select)))
                                  ? 0U : (SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[
                                          ((IData)(5U) 
                                           + (0xfU 
                                              & (((IData)(0x97U) 
                                                  * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select) 
                                                 >> 5U)))] 
                                          << ((IData)(0x20U) 
                                              - (0x1fU 
                                                 & ((IData)(0x97U) 
                                                    * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select))))) 
                                | (SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__mux__ireqs[
                                   ((IData)(4U) + (0xfU 
                                                   & (((IData)(0x97U) 
                                                       * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select) 
                                                      >> 5U)))] 
                                   >> (0x1fU & ((IData)(0x97U) 
                                                * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select)))));
        } else {
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[0U] 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vxrand_hee1f0c2a__0[0U];
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[1U] 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vxrand_hee1f0c2a__0[1U];
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[2U] 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vxrand_hee1f0c2a__0[2U];
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[3U] 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vxrand_hee1f0c2a__0[3U];
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[4U] 
                = (0x7fffffU & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vxrand_hee1f0c2a__0[4U]);
        }
    } else {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[0U] = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[1U] = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[2U] = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[3U] = 0U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[4U] = 0U;
    }
    if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_valid) {
        vlSelfRef.SimTopFPGA__DOT__oreq[0U] = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_req[0U];
        vlSelfRef.SimTopFPGA__DOT__oreq[1U] = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_req[1U];
        vlSelfRef.SimTopFPGA__DOT__oreq[2U] = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_req[2U];
        vlSelfRef.SimTopFPGA__DOT__oreq[3U] = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_req[3U];
        vlSelfRef.SimTopFPGA__DOT__oreq[4U] = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_req[4U];
    } else {
        vlSelfRef.SimTopFPGA__DOT__oreq[0U] = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[0U];
        vlSelfRef.SimTopFPGA__DOT__oreq[1U] = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[1U];
        vlSelfRef.SimTopFPGA__DOT__oreq[2U] = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[2U];
        vlSelfRef.SimTopFPGA__DOT__oreq[3U] = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[3U];
        vlSelfRef.SimTopFPGA__DOT__oreq[4U] = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req[4U];
    }
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__tx_write_byte 
        = (0xffU & (vlSelfRef.SimTopFPGA__DOT__oreq[0U] 
                    >> 0xaU));
    if (((((((((1U == (1U & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                             >> 0xaU))) | (2U == (3U 
                                                  & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                     >> 0xaU)))) 
              | (4U == (7U & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                              >> 0xaU)))) | (8U == 
                                             (0xfU 
                                              & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                 >> 0xaU)))) 
            | (0x10U == (0x1fU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                  >> 0xaU)))) | (0x20U 
                                                 == 
                                                 (0x3fU 
                                                  & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                     >> 0xaU)))) 
          | (0x40U == (0x7fU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                >> 0xaU)))) | (0x80U 
                                               == (0xffU 
                                                   & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                      >> 0xaU))))) {
        vlSelfRef.SimTopFPGA__DOT__u_device__DOT__tx_write_byte 
            = (0xffU & ((1U == (1U & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                      >> 0xaU))) ? 
                        ((vlSelfRef.SimTopFPGA__DOT__oreq[0U] 
                          << 0x16U) | (vlSelfRef.SimTopFPGA__DOT__oreq[0U] 
                                       >> 0xaU)) : 
                        ((2U == (3U & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                       >> 0xaU))) ? 
                         ((vlSelfRef.SimTopFPGA__DOT__oreq[0U] 
                           << 0xeU) | (vlSelfRef.SimTopFPGA__DOT__oreq[0U] 
                                       >> 0x12U)) : 
                         ((4U == (7U & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                        >> 0xaU))) ? 
                          ((vlSelfRef.SimTopFPGA__DOT__oreq[1U] 
                            << 6U) | (vlSelfRef.SimTopFPGA__DOT__oreq[0U] 
                                      >> 0x1aU)) : 
                          ((8U == (0xfU & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                           >> 0xaU)))
                            ? ((vlSelfRef.SimTopFPGA__DOT__oreq[1U] 
                                << 0x1eU) | (vlSelfRef.SimTopFPGA__DOT__oreq[1U] 
                                             >> 2U))
                            : ((0x10U == (0x1fU & (
                                                   vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                   >> 0xaU)))
                                ? ((vlSelfRef.SimTopFPGA__DOT__oreq[1U] 
                                    << 0x16U) | (vlSelfRef.SimTopFPGA__DOT__oreq[1U] 
                                                 >> 0xaU))
                                : ((0x20U == (0x3fU 
                                              & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                 >> 0xaU)))
                                    ? ((vlSelfRef.SimTopFPGA__DOT__oreq[1U] 
                                        << 0xeU) | 
                                       (vlSelfRef.SimTopFPGA__DOT__oreq[1U] 
                                        >> 0x12U)) : 
                                   ((0x40U == (0x7fU 
                                               & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                  >> 0xaU)))
                                     ? ((vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                         << 6U) | (
                                                   vlSelfRef.SimTopFPGA__DOT__oreq[1U] 
                                                   >> 0x1aU))
                                     : ((vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                         << 0x1eU) 
                                        | (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                           >> 2U))))))))));
    }
    vlSelfRef.SimTopFPGA__DOT__ram_valid = ((vlSelfRef.SimTopFPGA__DOT__oreq[3U] 
                                             >> 0x11U) 
                                            & (vlSelfRef.SimTopFPGA__DOT__oreq[4U] 
                                               >> 0x16U));
    vlSelfRef.SimTopFPGA__DOT__device_rdata = 0ULL;
    if (((((((((0x10000000ULL == (((QData)((IData)(
                                                   vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                   << 0x2eU) | (((QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                 << 0xeU) 
                                                | ((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                   >> 0x12U)))) 
               | (0x10000001ULL == (((QData)((IData)(
                                                     vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                     << 0x2eU) | (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                   << 0xeU) 
                                                  | ((QData)((IData)(
                                                                     vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                     >> 0x12U))))) 
              | (0x10000002ULL == (((QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                    << 0x2eU) | (((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                  << 0xeU) 
                                                 | ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                    >> 0x12U))))) 
             | (0x10000003ULL == (((QData)((IData)(
                                                   vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                   << 0x2eU) | (((QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                 << 0xeU) 
                                                | ((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                   >> 0x12U))))) 
            | (0x10000005ULL == (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                  << 0x2eU) | (((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                << 0xeU) 
                                               | ((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                  >> 0x12U))))) 
           | (0x10001000ULL == (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                 << 0x2eU) | (((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                               << 0xeU) 
                                              | ((QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                 >> 0x12U))))) 
          | (0x10001008ULL == (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                << 0x2eU) | (((QData)((IData)(
                                                              vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                              << 0xeU) 
                                             | ((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                >> 0x12U))))) 
         | (0x3800bff8ULL == (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                               << 0x2eU) | (((QData)((IData)(
                                                             vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                             << 0xeU) 
                                            | ((QData)((IData)(
                                                               vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                               >> 0x12U)))))) {
        vlSelfRef.SimTopFPGA__DOT__device_rdata = (
                                                   (0x10000000ULL 
                                                    == 
                                                    (((QData)((IData)(
                                                                      vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                                      << 0x2eU) 
                                                     | (((QData)((IData)(
                                                                         vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                         << 0xeU) 
                                                        | ((QData)((IData)(
                                                                           vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                           >> 0x12U))))
                                                    ? (QData)((IData)(
                                                                      ((0U 
                                                                        == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_count))
                                                                        ? 0U
                                                                        : 
                                                                       vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_fifo
                                                                       [
                                                                       (0xfU 
                                                                        & (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_rptr))])))
                                                    : 
                                                   ((0x10000001ULL 
                                                     == 
                                                     (((QData)((IData)(
                                                                       vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                                       << 0x2eU) 
                                                      | (((QData)((IData)(
                                                                          vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                          << 0xeU) 
                                                         | ((QData)((IData)(
                                                                            vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                            >> 0x12U))))
                                                     ? 
                                                    ((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__uart_ier)) 
                                                     << 8U)
                                                     : 
                                                    ((0x10000002ULL 
                                                      == 
                                                      (((QData)((IData)(
                                                                        vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                                        << 0x2eU) 
                                                       | (((QData)((IData)(
                                                                           vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                           << 0xeU) 
                                                          | ((QData)((IData)(
                                                                             vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                             >> 0x12U))))
                                                      ? 0x10000ULL
                                                      : 
                                                     ((0x10000003ULL 
                                                       == 
                                                       (((QData)((IData)(
                                                                         vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                                         << 0x2eU) 
                                                        | (((QData)((IData)(
                                                                            vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                            << 0xeU) 
                                                           | ((QData)((IData)(
                                                                              vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                              >> 0x12U))))
                                                       ? 
                                                      ((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__uart_lcr)) 
                                                       << 0x18U)
                                                       : 
                                                      ((0x10000005ULL 
                                                        == 
                                                        (((QData)((IData)(
                                                                          vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                                          << 0x2eU) 
                                                         | (((QData)((IData)(
                                                                             vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                             << 0xeU) 
                                                            | ((QData)((IData)(
                                                                               vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                               >> 0x12U))))
                                                        ? 0x600000000000ULL
                                                        : 
                                                       ((0x10001000ULL 
                                                         == 
                                                         (((QData)((IData)(
                                                                           vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                                           << 0x2eU) 
                                                          | (((QData)((IData)(
                                                                              vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                              << 0xeU) 
                                                             | ((QData)((IData)(
                                                                                vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                                >> 0x12U))))
                                                         ? (QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno))
                                                         : 
                                                        ((0x10001008ULL 
                                                          == 
                                                          (((QData)((IData)(
                                                                            vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                                            << 0x2eU) 
                                                           | (((QData)((IData)(
                                                                               vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                               << 0xeU) 
                                                              | ((QData)((IData)(
                                                                                vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                                 >> 0x12U))))
                                                          ? (QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_rdy))
                                                          : vlSelfRef.SimTopFPGA__DOT__u_device__DOT__mtime)))))));
    } else if ((0x23333008ULL == (((QData)((IData)(
                                                   vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                   << 0x2eU) | (((QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                 << 0xeU) 
                                                | ((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                   >> 0x12U))))) {
        vlSelfRef.SimTopFPGA__DOT__device_rdata = (
                                                   (8U 
                                                    & (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__switch))
                                                    ? 0ULL
                                                    : 
                                                   ((4U 
                                                     & (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__switch))
                                                     ? 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__switch))
                                                      ? 0ULL
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__switch))
                                                       ? 0x10ULL
                                                       : 8ULL))
                                                     : 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__switch))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__switch))
                                                       ? 4ULL
                                                       : 2ULL)
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__switch))
                                                       ? 1ULL
                                                       : 0x1fULL))));
    } else if ((0x20003000ULL == (((QData)((IData)(
                                                   vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                   << 0x2eU) | (((QData)((IData)(
                                                                 vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                 << 0xeU) 
                                                | ((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                   >> 0x12U))))) {
        vlSelfRef.SimTopFPGA__DOT__device_rdata = vlSelfRef.SimTopFPGA__DOT__u_device__DOT__mtime;
    } else if (((0x10001100ULL <= (((QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                    << 0x2eU) | (((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                  << 0xeU) 
                                                 | ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                    >> 0x12U)))) 
                & (0x10001500ULL > (((QData)((IData)(
                                                     vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                     << 0x2eU) | (((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                   << 0xeU) 
                                                  | ((QData)((IData)(
                                                                     vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                     >> 0x12U)))))) {
        vlSelfRef.SimTopFPGA__DOT__device_rdata = VL_SHIFTL_QQI(64,64,32, (QData)((IData)(
                                                                                ((0x3e7ffU 
                                                                                >= 
                                                                                (0x3ffffU 
                                                                                & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                                                                + 
                                                                                (0xffU 
                                                                                & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                                                >> 0x14U))) 
                                                                                - (IData)(0x40U))))
                                                                                 ? 
                                                                                vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem
                                                                                [
                                                                                (0x3ffffU 
                                                                                & ((VL_SHIFTL_III(18,32,32, vlSelfRef.SimTopFPGA__DOT__u_device__DOT__disk_blockno, 8U) 
                                                                                + 
                                                                                (0xffU 
                                                                                & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                                                >> 0x14U))) 
                                                                                - (IData)(0x40U)))]
                                                                                 : vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vxrand_h8df4b479__0))), 
                                                                VL_SHIFTL_III(32,32,32, 
                                                                              (7U 
                                                                               & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                                                >> 0x12U)), 3U));
    }
    SimTopFPGA__DOT__u_device__DOT____VdfgRegularize_heab64b38_0_1 
        = ((~ ((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__uart_lcr) 
               >> 7U)) & (0x10000000ULL == (((QData)((IData)(
                                                             vlSelfRef.SimTopFPGA__DOT__oreq[4U])) 
                                             << 0x2eU) 
                                            | (((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__oreq[3U])) 
                                                << 0xeU) 
                                               | ((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__oreq[2U])) 
                                                  >> 0x12U)))));
    vlSelfRef.SimTopFPGA__DOT__device_valid = ((~ (
                                                   vlSelfRef.SimTopFPGA__DOT__oreq[3U] 
                                                   >> 0x11U)) 
                                               & (vlSelfRef.SimTopFPGA__DOT__oreq[4U] 
                                                  >> 0x16U));
    vlSelfRef.SimTopFPGA__DOT__device_ready = (1U & 
                                               (((IData)(vlSelfRef.SimTopFPGA__DOT__device_valid) 
                                                 & ((0U 
                                                     != 
                                                     (0xffU 
                                                      & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                         >> 0xaU))) 
                                                    & (IData)(SimTopFPGA__DOT__u_device__DOT____VdfgRegularize_heab64b38_0_1)))
                                                 ? 
                                                ((0x40U 
                                                  != (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__fifo_count)) 
                                                 & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txn_done_pulse)))
                                                 : 
                                                (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txn_done_pulse))));
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txn_fire 
        = ((IData)(vlSelfRef.SimTopFPGA__DOT__device_valid) 
           & (IData)(vlSelfRef.SimTopFPGA__DOT__device_ready));
    vlSelfRef.SimTopFPGA__DOT__oresp[0U] = (IData)(
                                                   ((0x20000U 
                                                     & vlSelfRef.SimTopFPGA__DOT__oreq[3U])
                                                     ? vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__bram_rdata
                                                     : vlSelfRef.SimTopFPGA__DOT__device_rdata));
    vlSelfRef.SimTopFPGA__DOT__oresp[1U] = (IData)(
                                                   (((0x20000U 
                                                      & vlSelfRef.SimTopFPGA__DOT__oreq[3U])
                                                      ? vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__bram_rdata
                                                      : vlSelfRef.SimTopFPGA__DOT__device_rdata) 
                                                    >> 0x20U));
    vlSelfRef.SimTopFPGA__DOT__oresp[2U] = ((2U & vlSelfRef.SimTopFPGA__DOT__oresp[2U]) 
                                            | (3U & 
                                               ((0x20000U 
                                                 & vlSelfRef.SimTopFPGA__DOT__oreq[3U])
                                                 ? (IData)(vlSelfRef.SimTopFPGA__DOT__ram_last)
                                                 : (IData)(vlSelfRef.SimTopFPGA__DOT__device_ready))));
    vlSelfRef.SimTopFPGA__DOT__oresp[2U] = ((1U & vlSelfRef.SimTopFPGA__DOT__oresp[2U]) 
                                            | (3U & 
                                               (((0x20000U 
                                                  & vlSelfRef.SimTopFPGA__DOT__oreq[3U])
                                                  ? (IData)(vlSelfRef.SimTopFPGA__DOT__ram_ready)
                                                  : (IData)(vlSelfRef.SimTopFPGA__DOT__device_ready)) 
                                                << 1U)));
    vlSelfRef.SimTopFPGA__DOT__dbg_cpu_tx_write = (
                                                   ((IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txn_fire) 
                                                    & (0U 
                                                       != 
                                                       (0xffU 
                                                        & (vlSelfRef.SimTopFPGA__DOT__oreq[2U] 
                                                           >> 0xaU)))) 
                                                   & (IData)(SimTopFPGA__DOT__u_device__DOT____VdfgRegularize_heab64b38_0_1));
    SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[0U] = 0U;
    SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[1U] = 0U;
    SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[2U] = 0U;
    SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[3U] = 0U;
    SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[4U] = 0U;
    if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_valid) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vlvbound_hfd226540__0[0U] 
            = vlSelfRef.SimTopFPGA__DOT__oresp[0U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vlvbound_hfd226540__0[1U] 
            = vlSelfRef.SimTopFPGA__DOT__oresp[1U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vlvbound_hfd226540__0[2U] 
            = vlSelfRef.SimTopFPGA__DOT__oresp[2U];
        if ((0x83U >= (0xffU & ((IData)(0x42U) * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_select)))) {
            VL_ASSIGNSEL_WW(132,66,(0xffU & ((IData)(0x42U) 
                                             * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_select)), SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps, vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vlvbound_hfd226540__0);
        }
    } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__any_valid) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vlvbound_h10130eb1__0[0U] 
            = vlSelfRef.SimTopFPGA__DOT__oresp[0U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vlvbound_h10130eb1__0[1U] 
            = vlSelfRef.SimTopFPGA__DOT__oresp[1U];
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vlvbound_h10130eb1__0[2U] 
            = vlSelfRef.SimTopFPGA__DOT__oresp[2U];
        if ((0x83U >= (0xffU & ((IData)(0x42U) * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select)))) {
            VL_ASSIGNSEL_WW(132,66,(0xffU & ((IData)(0x42U) 
                                             * vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select)), SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps, vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vlvbound_h10130eb1__0);
        }
    }
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__mem_aligned_data 
        = ((((QData)((IData)(SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[1U])) 
             << 0x20U) | (QData)((IData)(SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[0U]))) 
           >> (0x3fU & VL_SHIFTL_III(6,6,32, (7U & 
                                              (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U] 
                                               >> 3U)), 3U)));
    __VdfgRegularize_hd87f99a1_0_8 = ((1U & ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__req_inflight)
                                              ? (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__req_addr_bit2)
                                              : (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[0U] 
                                                 >> 2U)))
                                       ? ((SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[4U] 
                                           << 0x1eU) 
                                          | (SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[3U] 
                                             >> 2U))
                                       : ((SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[3U] 
                                           << 0x1eU) 
                                          | (SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[2U] 
                                             >> 2U)));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__okay 
        = (IData)((0xcU == (0xcU & SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[4U])));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_23 
        = (IData)((0U != (6U & SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[0U])));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__okay 
        = (IData)((3U == (3U & SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[2U])));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_stage_result 
        = ((0x100U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])
            ? ((0x40U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])
                ? SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__mem_aligned_data
                : ((0x20U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])
                    ? ((0x10U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])
                        ? SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__mem_aligned_data
                        : ((8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])
                            ? (QData)((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__mem_aligned_data))
                            : (((QData)((IData)((- (IData)(
                                                           (1U 
                                                            & (IData)(
                                                                      (SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__mem_aligned_data 
                                                                       >> 0x1fU))))))) 
                                << 0x20U) | (QData)((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__mem_aligned_data)))))
                    : ((0x10U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])
                        ? ((8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])
                            ? (QData)((IData)((0xffffU 
                                               & (IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__mem_aligned_data))))
                            : (((- (QData)((IData)(
                                                   (1U 
                                                    & (IData)(
                                                              (SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__mem_aligned_data 
                                                               >> 0xfU)))))) 
                                << 0x10U) | (QData)((IData)(
                                                            (0xffffU 
                                                             & (IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__mem_aligned_data))))))
                        : ((8U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])
                            ? (QData)((IData)((0xffU 
                                               & (IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__mem_aligned_data))))
                            : (((- (QData)((IData)(
                                                   (1U 
                                                    & (IData)(
                                                              (SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__mem_aligned_data 
                                                               >> 7U)))))) 
                                << 8U) | (QData)((IData)(
                                                         (0xffU 
                                                          & (IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_execute__DOT__mem_aligned_data)))))))))
            : (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[9U])) 
                << 0x37U) | (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[8U])) 
                              << 0x17U) | ((QData)((IData)(
                                                           vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])) 
                                           >> 9U))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__resp_fire 
        = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__okay) 
           & ((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__resp_seen)) 
              & (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__req_inflight) 
                  & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__ireq_bus[2U]) 
                 | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__issue_now))));
    __VdfgRegularize_hd87f99a1_0_6 = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__translate_en)
                                       ? ((4U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state)) 
                                          & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__resp_fire))
                                       : (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__resp_fire));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_25 
        = (1U & ((SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[0U] 
                  >> 3U) | (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_23)));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__resp_fire 
        = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__okay) 
           & ((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__resp_seen)) 
              & (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__req_inflight) 
                  & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dreq_bus[4U] 
                     >> 0xbU)) | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__issue_now))));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_24 
        = (SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[0U] 
           & (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_25));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[0U] 
        = (IData)((((QData)((IData)(SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[1U])) 
                    << 0x20U) | (QData)((IData)(SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[0U]))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[1U] 
        = (IData)(((((QData)((IData)(SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[1U])) 
                     << 0x20U) | (QData)((IData)(SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[0U]))) 
                   >> 0x20U));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dresp_bus[2U] 
        = (3U & (- (IData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__resp_fire))));
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_access_done 
        = (1U & ((IData)((0U == (0x180U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U]))) 
                 | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__translate_en)
                     ? ((5U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state)) 
                        & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__resp_fire))
                     : (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__resp_fire))));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_4 
        = ((1U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state)) 
           & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__resp_fire));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_7 
        = ((2U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state)) 
           & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__resp_fire));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_8 
        = ((3U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state)) 
           & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__resp_fire));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__iresp_core 
        = (((QData)((IData)(((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__translate_en)) 
                             & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__resp_fire)))) 
            << 0x21U) | (((QData)((IData)(__VdfgRegularize_hd87f99a1_0_6)) 
                          << 0x20U) | (QData)((IData)(__VdfgRegularize_hd87f99a1_0_8))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_resp_fire 
        = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending) 
           & ((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_drop_resp_pending)) 
              & (IData)(__VdfgRegularize_hd87f99a1_0_6)));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_mem_busy 
        = ((~ (IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_access_done)) 
           & (IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_if_mem));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_9 
        = ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_8) 
           & SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[0U]);
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_resp_to_id 
        = ((IData)(SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_can_consume) 
           & ((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_valid)) 
              & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_resp_fire)));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__walk_fault_next 
        = (((~ SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[0U]) 
            & (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_4)) 
           | (((~ SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[0U]) 
               & (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_7)) 
              | (((~ SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[0U]) 
                  & (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_8)) 
                 | ((~ (SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[0U] 
                        >> 3U)) & ((~ (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_23)) 
                                   & (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_9))))));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_insn 
        = ((((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_4) 
             & (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_24)) 
            | (((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_7) 
                & (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_24)) 
               | ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_9) 
                  & (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_25)))) 
           & (((~ (SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[0U] 
                   >> 4U)) & (0U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode))) 
              | ((1U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
                 & (SimTopFPGA__DOT__u_vtop__DOT____Vcellout__mux__iresps[0U] 
                    >> 4U))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_cause 
        = (((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__walk_active) 
            & (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__walk_fault_next))
            ? ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_is_insn)
                ? 0xcULL : ((0U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_wstrb))
                             ? 0xfULL : 0xdULL)) : 
           ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_insn)
             ? 0xcULL : ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_load)
                          ? 0xdULL : ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_store)
                                       ? 0xfULL : ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_18)
                                                    ? 1ULL
                                                    : 
                                                   (((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_store_pmp_fault) 
                                                     | (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_store_pmp_fault))
                                                     ? 7ULL
                                                     : 
                                                    (((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_load_pmp_fault) 
                                                      | (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_load_pmp_fault))
                                                      ? 5ULL
                                                      : 0ULL)))))));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_17 
        = ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__walk_active) 
           & ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__walk_fault_next) 
              | (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_insn)));
    if (SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_17) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_is_insn 
            = ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_insn) 
               | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_is_insn));
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_vaddr 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr;
    } else {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_is_insn 
            = ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_18) 
               | (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_insn));
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_vaddr 
            = ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_load)
                ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr
                : ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_store)
                    ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr
                    : ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_insn_pmp_fault)
                        ? __VdfgRegularize_hd87f99a1_0_0
                        : ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_load_pmp_fault)
                            ? (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])) 
                                << 0x3dU) | (((QData)((IData)(
                                                              vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U])) 
                                              << 0x1dU) 
                                             | ((QData)((IData)(
                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U])) 
                                                >> 3U)))
                            : ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_store_pmp_fault)
                                ? (((QData)((IData)(
                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U])) 
                                    << 0x3dU) | (((QData)((IData)(
                                                                  vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[6U])) 
                                                  << 0x1dU) 
                                                 | ((QData)((IData)(
                                                                    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[5U])) 
                                                    >> 3U)))
                                : ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_insn_pmp_fault)
                                    ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr
                                    : ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_load_pmp_fault)
                                        ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr
                                        : ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_store_pmp_fault)
                                            ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr
                                            : 0ULL))))))));
    }
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap 
        = (((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_17) 
            | ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_load) 
               | ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__u_bit_fault_store) 
                  | ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_insn_pmp_fault) 
                     | ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_load_pmp_fault) 
                        | ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__direct_store_pmp_fault) 
                           | ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_insn_pmp_fault) 
                              | ((IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_load_pmp_fault) 
                                 | (IData)(SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__done_store_pmp_fault))))))))) 
           & (0U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_bubble)));
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mret_redirect = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect_pc = 0ULL;
    if ((((((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ecall) 
            | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_illegal)) 
           | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ebreak)) 
          | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_instr)) 
         | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_data))) {
        if (([&]() {
                    {
                        if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__15__Vfuncout 
                                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_cause;
                            goto __Vlabel2;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ecall) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__16__mode 
                                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__16__Vfuncout 
                                = ((0U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__16__mode))
                                    ? 8ULL : ((1U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__16__mode))
                                               ? 9ULL
                                               : 0xbULL));
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__15__Vfuncout 
                                = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__16__Vfuncout;
                            goto __Vlabel2;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ebreak) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__15__Vfuncout = 3ULL;
                            goto __Vlabel2;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_illegal) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__15__Vfuncout = 2ULL;
                            goto __Vlabel2;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_instr) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__15__Vfuncout = 0ULL;
                            goto __Vlabel2;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_data) {
                            if ((0x80U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) {
                                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__15__Vfuncout = 6ULL;
                                goto __Vlabel2;
                            } else {
                                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__15__Vfuncout = 4ULL;
                                goto __Vlabel2;
                            }
                        }
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__15__Vfuncout = 0ULL;
                        __Vlabel2: ;
                    }
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__14__cause 
                        = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__15__Vfuncout;
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__14__Vfuncout 
                        = ((3U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
                           && (1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r 
                                             >> (0x3fU 
                                                 & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__14__cause))))));
                }(), (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__14__Vfuncout))) {
            {
                if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap) {
                    goto __Vlabel3;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ecall) {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__18__mode 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__18__Vfuncout 
                        = ((0U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__18__mode))
                            ? 8ULL : ((1U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__18__mode))
                                       ? 9ULL : 0xbULL));
                    goto __Vlabel3;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ebreak) {
                    goto __Vlabel3;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_illegal) {
                    goto __Vlabel3;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_instr) {
                    goto __Vlabel3;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_data) {
                    if ((0x80U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) {
                        goto __Vlabel3;
                    } else {
                        goto __Vlabel3;
                    }
                }
                __Vlabel3: ;
            }
            SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus;
            SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                = ((0xffffffffffffffdfULL & SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus) 
                   | ((QData)((IData)((1U & (IData)(
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                     >> 1U))))) 
                      << 5U));
            SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                = (0xfffffffffffffffdULL & SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus);
            SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                = ((0xfffffffffffffeffULL & SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus) 
                   | ((QData)((IData)((1U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)))) 
                      << 8U));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect = 1U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect_pc 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_stvec_r;
        } else {
            {
                if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap) {
                    goto __Vlabel4;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ecall) {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__20__mode 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__20__Vfuncout 
                        = ((0U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__20__mode))
                            ? 8ULL : ((1U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__20__mode))
                                       ? 9ULL : 0xbULL));
                    goto __Vlabel4;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ebreak) {
                    goto __Vlabel4;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_illegal) {
                    goto __Vlabel4;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_instr) {
                    goto __Vlabel4;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_data) {
                    if ((0x80U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) {
                        goto __Vlabel4;
                    } else {
                        goto __Vlabel4;
                    }
                }
                __Vlabel4: ;
            }
            SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus;
            SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                = ((0xffffffffffffff7fULL & SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus) 
                   | ((QData)((IData)((1U & (IData)(
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                     >> 3U))))) 
                      << 7U));
            SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                = (0xfffffffffffffff7ULL & SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus);
            SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                = ((0xffffffffffffe7ffULL & SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus) 
                   | ((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
                      << 0xbU));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect = 1U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect_pc 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mtvec;
        }
    } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap) {
        if (([&]() {
                    {
                        if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__22__Vfuncout 
                                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__fault_cause;
                            goto __Vlabel5;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ecall) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__23__mode 
                                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__23__Vfuncout 
                                = ((0U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__23__mode))
                                    ? 8ULL : ((1U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__23__mode))
                                               ? 9ULL
                                               : 0xbULL));
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__22__Vfuncout 
                                = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__23__Vfuncout;
                            goto __Vlabel5;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ebreak) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__22__Vfuncout = 3ULL;
                            goto __Vlabel5;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_illegal) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__22__Vfuncout = 2ULL;
                            goto __Vlabel5;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_instr) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__22__Vfuncout = 0ULL;
                            goto __Vlabel5;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_data) {
                            if ((0x80U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) {
                                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__22__Vfuncout = 6ULL;
                                goto __Vlabel5;
                            } else {
                                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__22__Vfuncout = 4ULL;
                                goto __Vlabel5;
                            }
                        }
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__22__Vfuncout = 0ULL;
                        __Vlabel5: ;
                    }
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__21__cause 
                        = vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__22__Vfuncout;
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__21__Vfuncout 
                        = ((3U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
                           && (1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r 
                                             >> (0x3fU 
                                                 & (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__21__cause))))));
                }(), (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__21__Vfuncout))) {
            {
                if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap) {
                    goto __Vlabel6;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ecall) {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__25__mode 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__25__Vfuncout 
                        = ((0U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__25__mode))
                            ? 8ULL : ((1U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__25__mode))
                                       ? 9ULL : 0xbULL));
                    goto __Vlabel6;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ebreak) {
                    goto __Vlabel6;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_illegal) {
                    goto __Vlabel6;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_instr) {
                    goto __Vlabel6;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_data) {
                    if ((0x80U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) {
                        goto __Vlabel6;
                    } else {
                        goto __Vlabel6;
                    }
                }
                __Vlabel6: ;
            }
            SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus;
            SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                = ((0xffffffffffffffdfULL & SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus) 
                   | ((QData)((IData)((1U & (IData)(
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                     >> 1U))))) 
                      << 5U));
            SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                = (0xfffffffffffffffdULL & SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus);
            SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                = ((0xfffffffffffffeffULL & SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus) 
                   | ((QData)((IData)((1U & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)))) 
                      << 8U));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect = 1U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect_pc 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_stvec_r;
        } else {
            {
                if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap) {
                    goto __Vlabel7;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ecall) {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__27__mode 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__27__Vfuncout 
                        = ((0U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__27__mode))
                            ? 8ULL : ((1U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__27__mode))
                                       ? 9ULL : 0xbULL));
                    goto __Vlabel7;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ebreak) {
                    goto __Vlabel7;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_illegal) {
                    goto __Vlabel7;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_instr) {
                    goto __Vlabel7;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_data) {
                    if ((0x80U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) {
                        goto __Vlabel7;
                    } else {
                        goto __Vlabel7;
                    }
                }
                __Vlabel7: ;
            }
            SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus;
            SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                = ((0xffffffffffffff7fULL & SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus) 
                   | ((QData)((IData)((1U & (IData)(
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                     >> 3U))))) 
                      << 7U));
            SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                = (0xfffffffffffffff7ULL & SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus);
            SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                = ((0xffffffffffffe7ffULL & SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus) 
                   | ((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
                      << 0xbU));
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect = 1U;
            vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect_pc 
                = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mtvec;
        }
    } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_mret) {
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus;
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
            = ((0xfffffffffffffff7ULL & SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus) 
               | ((QData)((IData)((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                 >> 7U))))) 
                  << 3U));
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
            = (0x80ULL | SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus);
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
            = (0xffffffffffffe7ffULL & SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus);
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mret_redirect = 1U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect_pc 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mepc;
    } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_sret) {
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus;
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
            = ((0xfffffffffffffffdULL & SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus) 
               | ((QData)((IData)((1U & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus 
                                                 >> 5U))))) 
                  << 1U));
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
            = (0x20ULL | SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus);
        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
            = (0xfffffffffffffeffULL & SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus);
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mret_redirect = 1U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect_pc 
            = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_sepc_r;
    } else if (SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_sfence) {
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mret_redirect = 1U;
        vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect_pc 
            = (4ULL + (((QData)((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU])) 
                        << 0x37U) | (((QData)((IData)(
                                                      vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xbU])) 
                                      << 0x17U) | ((QData)((IData)(
                                                                   vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xaU])) 
                                                   >> 9U))));
    } else if (((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                 >> 0x1aU) & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                              >> 0x10U))) {
        if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                      >> 0x19U)))) {
            if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                          >> 0x18U)))) {
                if ((0x800000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                    if ((0x400000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                        if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                      >> 0x15U)))) {
                            if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                          >> 0x14U)))) {
                                if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                              >> 0x13U)))) {
                                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                  >> 0x12U)))) {
                                        if ((1U & (~ 
                                                   (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                    >> 0x11U)))) {
                                            if ((1U 
                                                 & (~ 
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                     >> 0x10U)))) {
                                                if (
                                                    (1U 
                                                     & (~ 
                                                        (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                         >> 0xfU)))) {
                                                    if (
                                                        (1U 
                                                         & (~ 
                                                            (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                             >> 0xeU)))) {
                                                        SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                                                            = 
                                                            (((QData)((IData)(
                                                                              vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                              << 0x32U) 
                                                             | (((QData)((IData)(
                                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                                 << 0x12U) 
                                                                | ((QData)((IData)(
                                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                                   >> 0xeU)));
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else if ((0x400000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) {
                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                  >> 0x15U)))) {
                        if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                      >> 0x14U)))) {
                            if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                          >> 0x13U)))) {
                                if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                              >> 0x12U)))) {
                                    if ((1U & (~ (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                  >> 0x11U)))) {
                                        if ((1U & (~ 
                                                   (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                    >> 0x10U)))) {
                                            if ((1U 
                                                 & (~ 
                                                    (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                     >> 0xfU)))) {
                                                if (
                                                    (1U 
                                                     & (~ 
                                                        (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U] 
                                                         >> 0xeU)))) {
                                                    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__next_mstatus 
                                                        = 
                                                        ((0x7ffffffcfff21fffULL 
                                                          & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus) 
                                                         | (0x80000003000de000ULL 
                                                            & (((QData)((IData)(
                                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[2U])) 
                                                                << 0x32U) 
                                                               | (((QData)((IData)(
                                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[1U])) 
                                                                   << 0x12U) 
                                                                  | ((QData)((IData)(
                                                                                vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U])) 
                                                                     >> 0xeU)))));
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_resp_to_buf 
        = ((~ (((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mret_redirect) 
                | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect)) 
               | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_resp_to_id) 
                  | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending)))) 
           & (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_resp_fire));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__flush_mmu 
        = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect) 
           | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_flush_front) 
              | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mret_redirect) 
                 | ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_instr_misalign) 
                    | (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap)))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__dcvt__reset 
        = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__flush_mmu) 
           | (IData)(vlSelfRef.reset));
}
