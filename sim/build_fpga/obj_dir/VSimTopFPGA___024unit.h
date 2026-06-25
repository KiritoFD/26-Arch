// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VSimTopFPGA.h for the primary calling header

#ifndef VERILATED_VSIMTOPFPGA___024UNIT_H_
#define VERILATED_VSIMTOPFPGA___024UNIT_H_  // guard

#include "verilated.h"


class VSimTopFPGA__Syms;

class alignas(VL_CACHE_LINE_BYTES) VSimTopFPGA___024unit final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    VSimTopFPGA__Syms* const vlSymsp;

    // CONSTRUCTORS
    VSimTopFPGA___024unit(VSimTopFPGA__Syms* symsp, const char* v__name);
    ~VSimTopFPGA___024unit();
    VL_UNCOPYABLE(VSimTopFPGA___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
