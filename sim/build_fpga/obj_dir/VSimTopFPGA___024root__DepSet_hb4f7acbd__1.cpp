// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSimTopFPGA.h for the primary calling header

#include "VSimTopFPGA__pch.h"
#include "VSimTopFPGA___024root.h"

void VSimTopFPGA___024root___eval_triggers__act(VSimTopFPGA___024root* vlSelf);
void VSimTopFPGA___024root___eval_act(VSimTopFPGA___024root* vlSelf);

bool VSimTopFPGA___024root___eval_phase__act(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___eval_phase__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    VSimTopFPGA___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        VSimTopFPGA___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

void VSimTopFPGA___024root___eval_nba(VSimTopFPGA___024root* vlSelf);

bool VSimTopFPGA___024root___eval_phase__nba(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___eval_phase__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        VSimTopFPGA___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VSimTopFPGA___024root___dump_triggers__ico(VSimTopFPGA___024root* vlSelf);
#endif  // VL_DEBUG
bool VSimTopFPGA___024root___eval_phase__ico(VSimTopFPGA___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void VSimTopFPGA___024root___dump_triggers__nba(VSimTopFPGA___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VSimTopFPGA___024root___dump_triggers__act(VSimTopFPGA___024root* vlSelf);
#endif  // VL_DEBUG

void VSimTopFPGA___024root___eval(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___eval\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY((0x64U < __VicoIterCount))) {
#ifdef VL_DEBUG
            VSimTopFPGA___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("/mnt/g/GitHub/26-Arch/vsrc/SimTopFPGA.sv", 12, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (VSimTopFPGA___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            VSimTopFPGA___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("/mnt/g/GitHub/26-Arch/vsrc/SimTopFPGA.sv", 12, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelfRef.__VactIterCount))) {
#ifdef VL_DEBUG
                VSimTopFPGA___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("/mnt/g/GitHub/26-Arch/vsrc/SimTopFPGA.sv", 12, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (VSimTopFPGA___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (VSimTopFPGA___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void VSimTopFPGA___024root___eval_debug_assertions(VSimTopFPGA___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    VSimTopFPGA__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimTopFPGA___024root___eval_debug_assertions\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY((vlSelfRef.clock & 0xfeU))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY((vlSelfRef.reset & 0xfeU))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY((vlSelfRef.io_perfInfo_clean & 0xfeU))) {
        Verilated::overWidthError("io_perfInfo_clean");}
    if (VL_UNLIKELY((vlSelfRef.io_perfInfo_dump & 0xfeU))) {
        Verilated::overWidthError("io_perfInfo_dump");}
}
#endif  // VL_DEBUG
