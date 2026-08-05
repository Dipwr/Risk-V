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
    VL_OUT8(WeIO,0,0);
    VL_OUT8(ReIO,0,0);
    VL_OUT8(CLKIO,0,0);
    CData/*3:0*/ main_cpu__DOT__s0;
    CData/*0:0*/ main_cpu__DOT__MemoryMapperExp_i0__DOT__s12;
    CData/*3:0*/ main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__s0;
    CData/*0:0*/ main_cpu__DOT__DataController_i1__DOT__s24;
    CData/*0:0*/ main_cpu__DOT__PcInSelector_i9__DOT__s3;
    CData/*0:0*/ main_cpu__DOT__PcInSelector_i9__DOT__s4;
    CData/*0:0*/ __VdfgRegularize_hebeb780c_0_3;
    CData/*1:0*/ __VdfgRegularize_hebeb780c_0_6;
    CData/*0:0*/ __VdfgRegularize_hebeb780c_0_10;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__CLK__0;
    CData/*0:0*/ __VicoDidInit;
    CData/*0:0*/ __VicoPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__CLK__1;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    SData/*12:0*/ main_cpu__DOT__ControlLogic_i3__DOT__s1;
    VL_IN(DrIO,31,0);
    VL_OUT(AddIO,31,0);
    VL_OUT(DwIO,31,0);
    IData/*31:0*/ main_cpu__DOT__s2;
    IData/*31:0*/ main_cpu__DOT__s11;
    IData/*31:0*/ main_cpu__DOT__s20;
    IData/*31:0*/ main_cpu__DOT__s26;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__s0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s9;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s10;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s8;
    IData/*31:0*/ main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i0__DOT__state;
    IData/*31:0*/ __Vtrigprevexpr___TOP__DrIO__0;
    IData/*31:0*/ __VactIterCount;
    QData/*32:0*/ main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp;
    QData/*32:0*/ __VdfgRegularize_hebeb780c_0_5;
    QData/*32:0*/ __VdfgRegularize_hebeb780c_0_7;
    VlUnpacked<CData/*7:0*/, 65536> main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory;
    VlUnpacked<CData/*7:0*/, 65536> main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory;
    VlUnpacked<CData/*7:0*/, 65536> main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory;
    VlUnpacked<CData/*7:0*/, 65536> main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory;
    VlUnpacked<IData/*31:0*/, 302> main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom;
    VlUnpacked<IData/*31:0*/, 302> main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom;
    VlUnpacked<IData/*31:0*/, 32> main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory;
    VlUnpacked<SData/*12:0*/, 28> main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 2> __VicoTriggered;
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
