// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VMAIN_CPU__SYMS_H_
#define VERILATED_VMAIN_CPU__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vmain_cpu.h"

// INCLUDE MODULE CLASSES
#include "Vmain_cpu___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vmain_cpu__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vmain_cpu* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vmain_cpu___024root            TOP;

    // CONSTRUCTORS
    Vmain_cpu__Syms(VerilatedContext* contextp, const char* namep, Vmain_cpu* modelp);
    ~Vmain_cpu__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
