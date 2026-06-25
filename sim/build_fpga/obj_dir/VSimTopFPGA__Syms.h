// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VSIMTOPFPGA__SYMS_H_
#define VERILATED_VSIMTOPFPGA__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "VSimTopFPGA.h"

// INCLUDE MODULE CLASSES
#include "VSimTopFPGA___024root.h"
#include "VSimTopFPGA___024unit.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)VSimTopFPGA__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VSimTopFPGA* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    VSimTopFPGA___024root          TOP;

    // CONSTRUCTORS
    VSimTopFPGA__Syms(VerilatedContext* contextp, const char* namep, VSimTopFPGA* modelp);
    ~VSimTopFPGA__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
