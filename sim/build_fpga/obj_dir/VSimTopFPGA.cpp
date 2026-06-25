// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VSimTopFPGA__pch.h"

//============================================================
// Constructors

VSimTopFPGA::VSimTopFPGA(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VSimTopFPGA__Syms(contextp(), _vcname__, this)}
    , clock{vlSymsp->TOP.clock}
    , reset{vlSymsp->TOP.reset}
    , io_perfInfo_clean{vlSymsp->TOP.io_perfInfo_clean}
    , io_perfInfo_dump{vlSymsp->TOP.io_perfInfo_dump}
    , io_uart_out_valid{vlSymsp->TOP.io_uart_out_valid}
    , io_uart_out_ch{vlSymsp->TOP.io_uart_out_ch}
    , io_uart_in_valid{vlSymsp->TOP.io_uart_in_valid}
    , io_uart_in_ch{vlSymsp->TOP.io_uart_in_ch}
    , io_logCtrl_log_begin{vlSymsp->TOP.io_logCtrl_log_begin}
    , io_logCtrl_log_end{vlSymsp->TOP.io_logCtrl_log_end}
    , io_logCtrl_log_level{vlSymsp->TOP.io_logCtrl_log_level}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

VSimTopFPGA::VSimTopFPGA(const char* _vcname__)
    : VSimTopFPGA(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VSimTopFPGA::~VSimTopFPGA() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VSimTopFPGA___024root___eval_debug_assertions(VSimTopFPGA___024root* vlSelf);
#endif  // VL_DEBUG
void VSimTopFPGA___024root___eval_static(VSimTopFPGA___024root* vlSelf);
void VSimTopFPGA___024root___eval_initial(VSimTopFPGA___024root* vlSelf);
void VSimTopFPGA___024root___eval_settle(VSimTopFPGA___024root* vlSelf);
void VSimTopFPGA___024root___eval(VSimTopFPGA___024root* vlSelf);

void VSimTopFPGA::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VSimTopFPGA::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VSimTopFPGA___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        VSimTopFPGA___024root___eval_static(&(vlSymsp->TOP));
        VSimTopFPGA___024root___eval_initial(&(vlSymsp->TOP));
        VSimTopFPGA___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    VSimTopFPGA___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool VSimTopFPGA::eventsPending() { return false; }

uint64_t VSimTopFPGA::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VSimTopFPGA::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void VSimTopFPGA___024root___eval_final(VSimTopFPGA___024root* vlSelf);

VL_ATTR_COLD void VSimTopFPGA::final() {
    VSimTopFPGA___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VSimTopFPGA::hierName() const { return vlSymsp->name(); }
const char* VSimTopFPGA::modelName() const { return "VSimTopFPGA"; }
unsigned VSimTopFPGA::threads() const { return 1; }
void VSimTopFPGA::prepareClone() const { contextp()->prepareClone(); }
void VSimTopFPGA::atClone() const {
    contextp()->threadPoolpOnClone();
}
