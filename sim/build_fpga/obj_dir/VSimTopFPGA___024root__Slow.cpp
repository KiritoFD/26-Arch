// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSimTopFPGA.h for the primary calling header

#include "VSimTopFPGA__pch.h"
#include "VSimTopFPGA__Syms.h"
#include "VSimTopFPGA___024root.h"

void VSimTopFPGA___024root___ctor_var_reset(VSimTopFPGA___024root* vlSelf);

VSimTopFPGA___024root::VSimTopFPGA___024root(VSimTopFPGA__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    VSimTopFPGA___024root___ctor_var_reset(this);
}

void VSimTopFPGA___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

VSimTopFPGA___024root::~VSimTopFPGA___024root() {
}
