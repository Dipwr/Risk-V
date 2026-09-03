// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vmain_cpu.h for the primary calling header

#ifndef VERILATED_VMAIN_CPU___024ROOT_H_
#define VERILATED_VMAIN_CPU___024ROOT_H_  // guard

#include "verilated.h"


class Vmain_cpu__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vmain_cpu___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(CLK,0,0);
    VL_OUT8(CLKIO,0,0);
    VL_OUT8(WeIO,3,0);
    VL_OUT8(ReIO,0,0);
    CData/*3:0*/ main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__we_mask;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __VicoPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__CLKIO__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__CLK__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    SData/*12:0*/ main_cpu__DOT__ControlLogic_i3__DOT__rom0__DOT__D__out__strong__out0;
    VL_IN(DrIO,31,0);
    VL_OUT(AddIO,31,0);
    VL_OUT(DwIO,31,0);
    IData/*31:0*/ main_cpu__DOT__s3;
    IData/*31:0*/ main_cpu__DOT__s6;
    IData/*31:0*/ main_cpu__DOT__s21;
    IData/*31:0*/ main_cpu__DOT__s22;
    IData/*31:0*/ main_cpu__DOT__s23;
    IData/*31:0*/ main_cpu__DOT__s24;
    IData/*31:0*/ main_cpu__DOT__s27;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<IData/*31:0*/, 2048> main_cpu__DOT__MemoryMapperExp_i0__DOT__shared_rom__DOT__my_rom;
    VlUnpacked<IData/*31:0*/, 65536> main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory;
    VlUnpacked<SData/*12:0*/, 28> main_cpu__DOT__ControlLogic_i3__DOT__rom0__DOT__my_rom;
    VlUnpacked<CData/*4:0*/, 62> main_cpu__DOT__ControlLogic_i3__DOT__rom1__DOT__my_rom;
    VlUnpacked<IData/*31:0*/, 32> main_cpu__DOT__Registers_i5__DOT__regs;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vmain_cpu__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vmain_cpu___024root(Vmain_cpu__Syms* symsp, const char* namep);
    ~Vmain_cpu___024root();
    VL_UNCOPYABLE(Vmain_cpu___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
