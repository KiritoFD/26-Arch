// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSimTopFPGA.h for the primary calling header

#include "VSimTopFPGA__pch.h"
#include "VSimTopFPGA__Syms.h"
#include "VSimTopFPGA___024unit.h"

void VSimTopFPGA___024unit___ctor_var_reset(VSimTopFPGA___024unit* vlSelf);

VSimTopFPGA___024unit::VSimTopFPGA___024unit(VSimTopFPGA__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    VSimTopFPGA___024unit___ctor_var_reset(this);
}

void VSimTopFPGA___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

VSimTopFPGA___024unit::~VSimTopFPGA___024unit() {
}
