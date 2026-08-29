// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vmain_cpu__pch.h"

//============================================================
// Constructors

Vmain_cpu::Vmain_cpu(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vmain_cpu__Syms(contextp(), _vcname__, this)}
    , CLK{vlSymsp->TOP.CLK}
    , CLKIO{vlSymsp->TOP.CLKIO}
    , WeIO{vlSymsp->TOP.WeIO}
    , ReIO{vlSymsp->TOP.ReIO}
    , DrIO{vlSymsp->TOP.DrIO}
    , AddIO{vlSymsp->TOP.AddIO}
    , DwIO{vlSymsp->TOP.DwIO}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vmain_cpu::Vmain_cpu(const char* _vcname__)
    : Vmain_cpu(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vmain_cpu::~Vmain_cpu() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vmain_cpu___024root___eval_debug_assertions(Vmain_cpu___024root* vlSelf);
#endif  // VL_DEBUG
void Vmain_cpu___024root___eval_static(Vmain_cpu___024root* vlSelf);
void Vmain_cpu___024root___eval_initial(Vmain_cpu___024root* vlSelf);
void Vmain_cpu___024root___eval_settle(Vmain_cpu___024root* vlSelf);
void Vmain_cpu___024root___eval(Vmain_cpu___024root* vlSelf);

void Vmain_cpu::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vmain_cpu::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vmain_cpu___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vmain_cpu___024root___eval_static(&(vlSymsp->TOP));
        Vmain_cpu___024root___eval_initial(&(vlSymsp->TOP));
        Vmain_cpu___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vmain_cpu___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vmain_cpu::eventsPending() { return false; }

uint64_t Vmain_cpu::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vmain_cpu::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vmain_cpu___024root___eval_final(Vmain_cpu___024root* vlSelf);

VL_ATTR_COLD void Vmain_cpu::final() {
    contextp()->executingFinal(true);
    Vmain_cpu___024root___eval_final(&(vlSymsp->TOP));
    contextp()->executingFinal(false);
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vmain_cpu::hierName() const { return vlSymsp->name(); }
const char* Vmain_cpu::modelName() const { return "Vmain_cpu"; }
unsigned Vmain_cpu::threads() const { return 1; }
void Vmain_cpu::prepareClone() const { contextp()->prepareClone(); }
void Vmain_cpu::atClone() const {
    contextp()->threadPoolpOnClone();
}
