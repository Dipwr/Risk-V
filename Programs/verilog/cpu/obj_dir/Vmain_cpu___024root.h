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
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(CLK,0,0);
        VL_OUT8(CLKIO,0,0);
        VL_OUT8(WeIO,3,0);
        VL_OUT8(ReIO,0,0);
        CData/*4:0*/ main_cpu__DOT__s0;
        CData/*0:0*/ main_cpu__DOT__s5;
        CData/*0:0*/ main_cpu__DOT__MemoryMapperExp_i0__DOT__s30;
        CData/*0:0*/ main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp;
        CData/*0:0*/ main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__nq_temp;
        CData/*3:0*/ main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s0;
        CData/*0:0*/ main_cpu__DOT__DataController_i1__DOT__s24;
        CData/*0:0*/ main_cpu__DOT__ALU_i4__DOT__s1;
        CData/*0:0*/ main_cpu__DOT__ALU_i4__DOT__s26;
        CData/*0:0*/ main_cpu__DOT__ALU_i4__DOT__s29;
        CData/*0:0*/ main_cpu__DOT__ALU_i4__DOT__s30;
        CData/*0:0*/ main_cpu__DOT__ALU_i4__DOT__s31;
        CData/*0:0*/ main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__s0;
        CData/*0:0*/ main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__s1;
        CData/*3:0*/ main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Counter_Nbit_i0__DOT__count;
        CData/*0:0*/ main_cpu__DOT__Registers_i5__DOT__s1;
        CData/*0:0*/ main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp;
        CData/*0:0*/ main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__nq_temp;
        CData/*0:0*/ main_cpu__DOT__PcInSelector_i9__DOT__s3;
        CData/*0:0*/ main_cpu__DOT__PcInSelector_i9__DOT__s4;
        CData/*0:0*/ main_cpu__DOT__ProgramCounter_i10__DOT__s1;
        CData/*0:0*/ main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp;
        CData/*0:0*/ main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__nq_temp;
        CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_0;
        CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_1;
        CData/*1:0*/ __VdfgRegularize_h6e95ff9d_0_2;
        CData/*0:0*/ __Vtrigprevexpr___TOP__main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp__0;
        CData/*0:0*/ __VstlDidInit;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VstlPhaseResult;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __VicoPhaseResult;
        CData/*0:0*/ __Vtrigprevexpr___TOP__main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp__1;
        CData/*0:0*/ __Vtrigprevexpr___TOP__main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp__1;
        CData/*0:0*/ __Vtrigprevexpr___TOP__main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp__1;
        CData/*0:0*/ __Vtrigprevexpr___TOP__CLKIO__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__CLK__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__main_cpu__DOT__Registers_i5__DOT__s1__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__main_cpu__DOT__ProgramCounter_i10__DOT__s1__0;
        CData/*0:0*/ __VactDidInit;
        CData/*0:0*/ __VactPhaseResult;
        CData/*0:0*/ __VnbaPhaseResult;
        SData/*12:0*/ main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0;
        VL_IN(DrIO,31,0);
        VL_OUT(AddIO,31,0);
        VL_OUT(DwIO,31,0);
        IData/*31:0*/ main_cpu__DOT__s1;
        IData/*31:0*/ main_cpu__DOT__s2;
        IData/*31:0*/ main_cpu__DOT__s3;
        IData/*31:0*/ main_cpu__DOT__s6;
        IData/*31:0*/ main_cpu__DOT__s12;
        IData/*31:0*/ main_cpu__DOT__s21;
        IData/*31:0*/ main_cpu__DOT__s22;
        IData/*31:0*/ main_cpu__DOT__s27;
        IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__s0;
        IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__s12;
        IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__s23;
        IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__s24;
    };
    struct {
        IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__s7;
        IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__rem_temp;
        IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s6;
        IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Register_BUS_i4__DOT__state;
        IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Register_BUS_i5__DOT__state;
        IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s12;
        IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s10;
        IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s12;
        IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s11;
        IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s13;
        IData/*31:0*/ main_cpu__DOT__ProgramCounter_i10__DOT__s0;
        IData/*31:0*/ main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state;
        IData/*31:0*/ __VactIterCount;
        QData/*32:0*/ main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp;
        QData/*63:0*/ main_cpu__DOT__ALU_i4__DOT__mul_i3__DOT__s0;
        QData/*32:0*/ __VdfgRegularize_he50b618e_0_4;
        VlUnpacked<IData/*31:0*/, 305> main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom;
        VlUnpacked<IData/*31:0*/, 305> main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom;
        VlUnpacked<CData/*7:0*/, 65536> main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory;
        VlUnpacked<CData/*7:0*/, 65536> main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory;
        VlUnpacked<CData/*7:0*/, 65536> main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory;
        VlUnpacked<CData/*7:0*/, 65536> main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory;
        VlUnpacked<SData/*12:0*/, 28> main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom;
        VlUnpacked<CData/*4:0*/, 62> main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom;
        VlUnpacked<IData/*31:0*/, 32> main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory;
        VlUnpacked<QData/*63:0*/, 2> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    };

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
