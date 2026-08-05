// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmain_cpu.h for the primary calling header

#include "Vmain_cpu__pch.h"

void Vmain_cpu___024root___ctor_var_reset(Vmain_cpu___024root* vlSelf);

Vmain_cpu___024root::Vmain_cpu___024root(Vmain_cpu__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vmain_cpu___024root___ctor_var_reset(this);
}

void Vmain_cpu___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vmain_cpu___024root::~Vmain_cpu___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
