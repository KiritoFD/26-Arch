// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSimTopFPGA.h for the primary calling header

#include "VSimTopFPGA__pch.h"
#include "VSimTopFPGA___024root.h"

VL_ATTR_COLD void VSimTopFPGA___024root___eval_static(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___eval_static\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void VSimTopFPGA___024root___eval_initial__TOP(VSimTopFPGA___024root* vlSelf);

VL_ATTR_COLD void VSimTopFPGA___024root___eval_initial(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___eval_initial\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VSimTopFPGA___024root___eval_initial__TOP(vlSelf);
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
}

VL_ATTR_COLD void VSimTopFPGA___024root___eval_initial__TOP(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___eval_initial__TOP\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlWide<5>/*159:0*/ __Vtemp_2;
    VlWide<4>/*127:0*/ __Vtemp_3;
    VlWide<3>/*95:0*/ __Vtemp_4;
    // Body
    vlSelfRef.io_uart_out_valid = 0U;
    vlSelfRef.io_uart_out_ch = 0U;
    vlSelfRef.io_uart_in_valid = 0U;
    VL_RAND_RESET_ASSIGN_W(151, __Vtemp_2);
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vxrand_hee1f0c2a__0[0U] 
        = __Vtemp_2[0U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vxrand_hee1f0c2a__0[1U] 
        = __Vtemp_2[1U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vxrand_hee1f0c2a__0[2U] 
        = __Vtemp_2[2U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vxrand_hee1f0c2a__0[3U] 
        = __Vtemp_2[3U];
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vxrand_hee1f0c2a__0[4U] 
        = (0x7fffffU & __Vtemp_2[4U]);
    __Vtemp_3[0U] = 0x2e747874U;
    __Vtemp_3[1U] = 0x5f686578U;
    __Vtemp_3[2U] = 0x726e656cU;
    __Vtemp_3[3U] = 0x6b65U;
    VL_READMEM_N(true, 64, 262144, 0, VL_CVT_PACK_STR_NW(4, __Vtemp_3)
                 ,  &(vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__mem)
                 , 0, ~0ULL);
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT____Vxrand_h8df4b479__0 
        = VL_RAND_RESET_ASSIGN_I(32);
    __Vtemp_4[0U] = 0x2e747874U;
    __Vtemp_4[1U] = 0x5f686578U;
    __Vtemp_4[2U] = 0x6469736bU;
    VL_READMEM_N(true, 32, 256000, 0, VL_CVT_PACK_STR_NW(3, __Vtemp_4)
                 ,  &(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__sim_disk_mem)
                 , 0, ~0ULL);
}

VL_ATTR_COLD void VSimTopFPGA___024root___eval_final(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___eval_final\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VSimTopFPGA___024root___dump_triggers__stl(VSimTopFPGA___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool VSimTopFPGA___024root___eval_phase__stl(VSimTopFPGA___024root* vlSelf);

VL_ATTR_COLD void VSimTopFPGA___024root___eval_settle(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___eval_settle\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            VSimTopFPGA___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("/mnt/g/GitHub/26-Arch/vsrc/SimTopFPGA.sv", 12, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (VSimTopFPGA___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VSimTopFPGA___024root___dump_triggers__stl(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___dump_triggers__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VSimTopFPGA___024root___stl_sequent__TOP__0(VSimTopFPGA___024root* vlSelf);

VL_ATTR_COLD void VSimTopFPGA___024root___eval_stl(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___eval_stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VSimTopFPGA___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void VSimTopFPGA___024root___stl_sequent__TOP__0(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___stl_sequent__TOP__0\n"); );
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
    QData/*63:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__18__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__18__Vfuncout = 0;
    QData/*63:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__20__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__20__Vfuncout = 0;
    QData/*63:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__25__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__25__Vfuncout = 0;
    QData/*63:0*/ __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__27__Vfuncout;
    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__27__Vfuncout = 0;
    // Body
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
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__vpn1 
        = (0x1ffU & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr 
                             >> 0x15U)));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__vpn0 
        = (0x1ffU & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr 
                             >> 0xcU)));
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__fifo_full 
        = (0x40U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__fifo_count));
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_empty 
        = (0U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__console_rx_count));
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__bitDone 
        = (0xd8U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__bitTmr));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_sfence = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_mret = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_valid 
        = (1U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r[3U]);
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wen = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_sret = 0U;
    vlSelfRef.SimTopFPGA__DOT__u_device__DOT__tx_start 
        = ((0U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__fifo_count)) 
           & (0U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_device__DOT__txState)));
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
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_22 
        = ((~ (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_pte 
                       >> 4U))) & (0U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)));
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT____VdfgRegularize_hcb8cfbef_0_15 
        = ((1U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode)) 
           & (IData)((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_pte 
                      >> 4U)));
    if (vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__is_write) {
        vlSelfRef.SimTopFPGA__DOT__ram_ready = vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__real_valid;
        vlSelfRef.SimTopFPGA__DOT__ram_last = vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__real_valid;
    } else {
        vlSelfRef.SimTopFPGA__DOT__ram_ready = vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__ready_read;
        vlSelfRef.SimTopFPGA__DOT__ram_last = vlSelfRef.SimTopFPGA__DOT__u_bram__DOT__last_read;
    }
    SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__walk_active 
        = ((1U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state)) 
           | ((2U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state)) 
              | (3U == (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state))));
    __VdfgRegularize_hd87f99a1_0_0 = ((IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending)
                                       ? vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc
                                       : vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pc);
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
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_instr 
        = ((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0U] 
            >> 2U) & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU] 
                      >> 0x10U));
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
    __Vfunc_is_mdu_cmd__0__cmd = (0xfU & (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r[0xeU] 
                                          >> 0xdU));
    __Vfunc_is_mdu_cmd__0__Vfuncout = (((((0xaU == (IData)(__Vfunc_is_mdu_cmd__0__cmd)) 
                                          | (0xbU == (IData)(__Vfunc_is_mdu_cmd__0__cmd))) 
                                         | (0xcU == (IData)(__Vfunc_is_mdu_cmd__0__cmd))) 
                                        | (0xdU == (IData)(__Vfunc_is_mdu_cmd__0__cmd))) 
                                       | (0xeU == (IData)(__Vfunc_is_mdu_cmd__0__cmd)));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_req 
        = __Vfunc_is_mdu_cmd__0__Vfuncout;
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
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__translate_en 
        = (IData)(((0x8000000000000000ULL == (0xf000000000000000ULL 
                                              & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_satp)) 
                   & (3U != (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode))));
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
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_commit 
        = (IData)((0x18000U == (0x18000U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[0xcU])));
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_if_mem 
        = (IData)(((vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[0xcU] 
                    >> 0x10U) & (0U != (0x180U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r[7U]))));
    vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_imm 
        = SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_imm_i;
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
    SimTopFPGA__DOT__u_vtop__DOT__core__DOT____VdfgRegularize_h47660625_0_10 
        = (1U & ((~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__halted)) 
                 & (~ (IData)(vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_commit))));
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
                            goto __Vlabel1;
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
                            goto __Vlabel1;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ebreak) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__15__Vfuncout = 3ULL;
                            goto __Vlabel1;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_illegal) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__15__Vfuncout = 2ULL;
                            goto __Vlabel1;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_instr) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__15__Vfuncout = 0ULL;
                            goto __Vlabel1;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_data) {
                            if ((0x80U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) {
                                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__15__Vfuncout = 6ULL;
                                goto __Vlabel1;
                            } else {
                                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__15__Vfuncout = 4ULL;
                                goto __Vlabel1;
                            }
                        }
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__15__Vfuncout = 0ULL;
                        __Vlabel1: ;
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
                    goto __Vlabel2;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ecall) {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__18__mode 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__18__Vfuncout 
                        = ((0U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__18__mode))
                            ? 8ULL : ((1U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__18__mode))
                                       ? 9ULL : 0xbULL));
                    goto __Vlabel2;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ebreak) {
                    goto __Vlabel2;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_illegal) {
                    goto __Vlabel2;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_instr) {
                    goto __Vlabel2;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_data) {
                    if ((0x80U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) {
                        goto __Vlabel2;
                    } else {
                        goto __Vlabel2;
                    }
                }
                __Vlabel2: ;
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
                    goto __Vlabel3;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ecall) {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__20__mode 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__20__Vfuncout 
                        = ((0U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__20__mode))
                            ? 8ULL : ((1U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__20__mode))
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
                            goto __Vlabel4;
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
                            goto __Vlabel4;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ebreak) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__22__Vfuncout = 3ULL;
                            goto __Vlabel4;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_illegal) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__22__Vfuncout = 2ULL;
                            goto __Vlabel4;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_instr) {
                            vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__22__Vfuncout = 0ULL;
                            goto __Vlabel4;
                        } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_data) {
                            if ((0x80U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) {
                                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__22__Vfuncout = 6ULL;
                                goto __Vlabel4;
                            } else {
                                vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__22__Vfuncout = 4ULL;
                                goto __Vlabel4;
                            }
                        }
                        vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__22__Vfuncout = 0ULL;
                        __Vlabel4: ;
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
                    goto __Vlabel5;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ecall) {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__25__mode 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__25__Vfuncout 
                        = ((0U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__25__mode))
                            ? 8ULL : ((1U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__25__mode))
                                       ? 9ULL : 0xbULL));
                    goto __Vlabel5;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ebreak) {
                    goto __Vlabel5;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_illegal) {
                    goto __Vlabel5;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_instr) {
                    goto __Vlabel5;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_data) {
                    if ((0x80U & vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r[7U])) {
                        goto __Vlabel5;
                    } else {
                        goto __Vlabel5;
                    }
                }
                __Vlabel5: ;
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
                    goto __Vlabel6;
                } else if (vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ecall) {
                    vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__27__mode 
                        = vlSelfRef.SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode;
                    __Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__27__Vfuncout 
                        = ((0U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__27__mode))
                            ? 8ULL : ((1U == (IData)(vlSelfRef.__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__27__mode))
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

VL_ATTR_COLD void VSimTopFPGA___024root___eval_triggers__stl(VSimTopFPGA___024root* vlSelf);

VL_ATTR_COLD bool VSimTopFPGA___024root___eval_phase__stl(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___eval_phase__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    VSimTopFPGA___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        VSimTopFPGA___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VSimTopFPGA___024root___dump_triggers__ico(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___dump_triggers__ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VSimTopFPGA___024root___dump_triggers__act(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___dump_triggers__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VSimTopFPGA___024root___dump_triggers__nba(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___dump_triggers__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VSimTopFPGA___024root___ctor_var_reset(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___ctor_var_reset\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->clock = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->io_logCtrl_log_begin = VL_RAND_RESET_Q(64);
    vlSelf->io_logCtrl_log_end = VL_RAND_RESET_Q(64);
    vlSelf->io_logCtrl_log_level = VL_RAND_RESET_Q(64);
    vlSelf->io_perfInfo_clean = VL_RAND_RESET_I(1);
    vlSelf->io_perfInfo_dump = VL_RAND_RESET_I(1);
    vlSelf->io_uart_out_valid = VL_RAND_RESET_I(1);
    vlSelf->io_uart_out_ch = VL_RAND_RESET_I(8);
    vlSelf->io_uart_in_valid = VL_RAND_RESET_I(1);
    vlSelf->io_uart_in_ch = VL_RAND_RESET_I(8);
    VL_RAND_RESET_W(151, vlSelf->SimTopFPGA__DOT__oreq);
    VL_RAND_RESET_W(66, vlSelf->SimTopFPGA__DOT__oresp);
    vlSelf->SimTopFPGA__DOT__ram_valid = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__ram_ready = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__ram_last = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__device_valid = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__device_rdata = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__device_ready = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__dbg_cpu_tx_write = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__dbg_cycle_count = VL_RAND_RESET_I(32);
    vlSelf->SimTopFPGA__DOT__dbg_device_access_count = VL_RAND_RESET_I(32);
    vlSelf->SimTopFPGA__DOT__dbg_ram_access_count = VL_RAND_RESET_I(32);
    VL_RAND_RESET_W(65, vlSelf->SimTopFPGA__DOT__u_vtop__DOT__ireq_core);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__iresp_core = VL_RAND_RESET_Q(34);
    VL_RAND_RESET_W(140, vlSelf->SimTopFPGA__DOT__u_vtop__DOT__dreq_core);
    VL_RAND_RESET_W(65, vlSelf->SimTopFPGA__DOT__u_vtop__DOT__ireq_bus);
    VL_RAND_RESET_W(140, vlSelf->SimTopFPGA__DOT__u_vtop__DOT__dreq_bus);
    VL_RAND_RESET_W(66, vlSelf->SimTopFPGA__DOT__u_vtop__DOT__dresp_bus);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__flush_mmu = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__fault_vaddr = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__fault_is_insn = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__fault_cause = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT____Vcellinp__dcvt__reset = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(97, vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_r);
    VL_RAND_RESET_W(469, vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_r);
    VL_RAND_RESET_W(401, vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_r);
    VL_RAND_RESET_W(401, vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__wb_r);
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__gpr[__Vi0] = VL_RAND_RESET_Q(64);
    }
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pc = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pending = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_pc = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_valid = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_pc = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_buf_instr = VL_RAND_RESET_I(32);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_req_new_fire = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_resp_fire = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_pop_buf = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_resp_to_id = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_resp_to_buf = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pending = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_pc = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_redirect_bubble = VL_RAND_RESET_I(2);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fetch_drop_resp_pending = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_valid = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_trap = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wen = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_word = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_alu_cmd = VL_RAND_RESET_I(4);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op1 = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_op2 = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_imm = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_load = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_store = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_mem_size = VL_RAND_RESET_I(3);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_mem_unsigned = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_branch = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_br_funct3 = VL_RAND_RESET_I(3);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_jal = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_jalr = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_wb_pc4 = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wen = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_csr_wdata = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_ecall = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_mret = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_sret = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_amo = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_amo_cmd = VL_RAND_RESET_I(5);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_illegal = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_ebreak = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__id_dec_is_sfence = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_misalign = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_instr_misalign = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mstatus = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mtvec = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mie = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mscratch = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mcause = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mtval = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_mepc = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__csr_satp = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__privilege_mode = VL_RAND_RESET_I(2);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__halted = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_commit = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__cycle_cnt = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mmu_trap = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__fault_pc = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mret_redirect = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__trap_redirect_pc = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_req = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_to_mem_blocks_front = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_ex_busy = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__stall_mem_busy = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__raw_hazard_ex = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__raw_hazard_mem = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_stage_result = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_result = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_mem_addr = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_flush_front = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__ex_redirect_pc = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_store_data_shifted = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mem_store_strobe = VL_RAND_RESET_I(8);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_valid = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__mdu_core_out_result = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_issue = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_issued_q = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__amo_done_q = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_trap_count = VL_RAND_RESET_I(32);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__dbg_commit_count = VL_RAND_RESET_I(32);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT____VdfgRegularize_h47660625_0_12 = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rs2_val = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_rd = VL_RAND_RESET_I(5);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_decode__DOT__id_csr_addr = VL_RAND_RESET_I(12);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_busy = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_cmd = VL_RAND_RESET_I(4);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_is_word = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_steps_left = VL_RAND_RESET_I(7);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_acc = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_a = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_mul_b = VL_RAND_RESET_Q(64);
    VL_RAND_RESET_W(65, vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_rem);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_quot = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_divisor = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_signed = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_div_is_rem = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_q_neg = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mdu_r_neg = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_mask = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__width_steps = VL_RAND_RESET_I(7);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__sign_bit = VL_RAND_RESET_I(6);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_eff = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op2_eff = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__dividend_abs = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__divisor_abs = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op1_neg = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__op2_neg = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_acc_next = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_a_next = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_b_next = VL_RAND_RESET_Q(64);
    VL_RAND_RESET_W(65, vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_rem_next);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_quot_next = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__q_unsigned = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__r_unsigned = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__final_val = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_src0 = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__mul_src1 = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_q_abs_fast = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_r_abs_fast = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_mask = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_pow2 = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_pow2_shift = VL_RAND_RESET_I(6);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_signed = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_mdu__DOT__div_is_rem = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ecall = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_mret = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_sret = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_illegal = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_ebreak = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_data = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__wb_misalign_instr = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mip_raw = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_stvec_r = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_sscratch_r = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_sepc_r = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_scause_r = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_stval_r = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_medeleg_r = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mideleg_r = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_mcounteren_r = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_menvcfg_r = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpcfg0_r = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__csr_pmpaddr0_r = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__state = VL_RAND_RESET_I(3);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__translate_en = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_is_insn = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_vaddr = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_wdata = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_wstrb = VL_RAND_RESET_I(8);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_size = VL_RAND_RESET_I(3);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pte_addr = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_pte = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__saved_level = VL_RAND_RESET_I(2);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__vpn1 = VL_RAND_RESET_I(9);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__vpn0 = VL_RAND_RESET_I(9);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__trap_pending = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__req_addr_bit2 = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__req_inflight = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__issue_now = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__okay = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__req_inflight = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__resp_seen = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__issue_now = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__icvt__DOT__inst__DOT__resp_fire = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__okay = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__req_inflight = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__resp_seen = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__issue_now = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__dcvt__DOT__resp_fire = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(151, vlSelf->SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vxrand_hee1f0c2a__0);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__select = 0;
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_select = 0;
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__any_valid = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(151, vlSelf->SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__selected_req);
    VL_RAND_RESET_W(151, vlSelf->SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_req);
    vlSelf->SimTopFPGA__DOT__u_vtop__DOT__mux__DOT__lock_valid = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(66, vlSelf->SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vlvbound_hfd226540__0);
    VL_RAND_RESET_W(66, vlSelf->SimTopFPGA__DOT__u_vtop__DOT__mux__DOT____Vlvbound_h10130eb1__0);
    for (int __Vi0 = 0; __Vi0 < 262144; ++__Vi0) {
        vlSelf->SimTopFPGA__DOT__u_bram__DOT__mem[__Vi0] = VL_RAND_RESET_Q(64);
    }
    vlSelf->SimTopFPGA__DOT__u_bram__DOT__counter = VL_RAND_RESET_I(16);
    vlSelf->SimTopFPGA__DOT__u_bram__DOT__txn_active = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_bram__DOT__latched_addr = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_bram__DOT__latched_wdata = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_bram__DOT__latched_wstrobe = VL_RAND_RESET_I(8);
    vlSelf->SimTopFPGA__DOT__u_bram__DOT__is_write = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_bram__DOT__real_valid = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_bram__DOT__bram_rdata = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_bram__DOT__ready_read = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_bram__DOT__last_read = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__waddr = VL_RAND_RESET_I(18);
    vlSelf->SimTopFPGA__DOT__u_bram__DOT__unnamedblk1__DOT__wmask = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_device__DOT____Vxrand_h8df4b479__0 = VL_RAND_RESET_I(32);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__txn_fire = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__tx_write_byte = VL_RAND_RESET_I(8);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__uart_lcr = VL_RAND_RESET_I(8);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__uart_ier = VL_RAND_RESET_I(8);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__mtime = VL_RAND_RESET_Q(64);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__mtime_div = VL_RAND_RESET_I(16);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__switch = VL_RAND_RESET_I(4);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->SimTopFPGA__DOT__u_device__DOT__console_rx_fifo[__Vi0] = VL_RAND_RESET_I(8);
    }
    vlSelf->SimTopFPGA__DOT__u_device__DOT__console_rx_wptr = VL_RAND_RESET_I(5);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__console_rx_rptr = VL_RAND_RESET_I(5);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__console_rx_count = VL_RAND_RESET_I(6);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__console_rx_empty = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__bitTmr = VL_RAND_RESET_I(14);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__txState = VL_RAND_RESET_I(2);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__bitDone = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__bitIndex = VL_RAND_RESET_I(32);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__tx_start = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__fifo_count = VL_RAND_RESET_I(8);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__fifo_full = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__dbg_ever_uart_write_reg = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__dbg_ever_device_read_reg = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__rxShiftReg = VL_RAND_RESET_I(10);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__rxBitTmr = VL_RAND_RESET_I(14);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__rxBitIndex = VL_RAND_RESET_I(4);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__rxState = VL_RAND_RESET_I(2);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__rxBitSync = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__rxBit = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__rxByteReady = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__rxByte = VL_RAND_RESET_I(8);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__disk_blockno = VL_RAND_RESET_I(32);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__disk_rdy = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 256000; ++__Vi0) {
        vlSelf->SimTopFPGA__DOT__u_device__DOT__sim_disk_mem[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->SimTopFPGA__DOT__u_device__DOT__txn_done_pulse = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_device__DOT__gen_dbg_live__DOT__dbg_live_count = VL_RAND_RESET_I(32);
    vlSelf->SimTopFPGA__DOT__u_device__DOT____Vlvbound_h99cc83ff__0 = VL_RAND_RESET_I(1);
    vlSelf->SimTopFPGA__DOT__u_device__DOT____Vlvbound_h24e30222__0 = VL_RAND_RESET_I(8);
    vlSelf->__Vfunc_sanitize_csr_write__1__Vfuncout = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_sanitize_csr_write__1__addr = VL_RAND_RESET_I(12);
    vlSelf->__Vfunc_sanitize_csr_write__1__data = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__14__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__14__cause = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__15__Vfuncout = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__16__Vfuncout = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__16__mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__18__mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__20__mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__21__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__delegate_to_s__21__cause = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_excp_cause__22__Vfuncout = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__23__Vfuncout = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__23__mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__25__mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__core__DOT__u_commit__DOT__u_csr__DOT__get_ecall_cause__27__mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__addr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__cfg = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__paddr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__active = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__hit = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__30__allow = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__addr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__cfg = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__paddr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__a_mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__base = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__top = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__31__ones = 0;
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__addr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__cfg = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__paddr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__active = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__hit = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__32__allow = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__addr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__cfg = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__paddr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__a_mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__base = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__top = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__33__ones = 0;
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__addr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__cfg = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__paddr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__active = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__hit = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__34__allow = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__addr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__cfg = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__paddr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__a_mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__base = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__top = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__35__ones = 0;
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__addr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__cfg = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__paddr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__active = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__hit = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__36__allow = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__addr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__cfg = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__paddr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__a_mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__base = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__top = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__37__ones = 0;
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__addr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__cfg = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__paddr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__active = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__hit = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__38__allow = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__addr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__cfg = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__paddr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__a_mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__base = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__top = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__39__ones = 0;
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__addr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__cfg = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__paddr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__active = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__hit = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_req_fault__40__allow = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__addr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__cfg = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__paddr = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__a_mode = VL_RAND_RESET_I(2);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__base = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__top = VL_RAND_RESET_Q(64);
    vlSelf->__Vfunc_SimTopFPGA__DOT__u_vtop__DOT__u_mmu__DOT__pmp_entry_match__41__ones = 0;
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = VL_RAND_RESET_I(1);
}
