// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmain_cpu.h for the primary calling header

#include "Vmain_cpu__pch.h"

VL_ATTR_COLD void Vmain_cpu___024root___eval_static(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_static\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    {
        // Inlined CFunc: _eval_static__TOP
        vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state = 0U;
    }
    vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp__0 
        = vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp;
    vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp__0 
        = vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp;
    vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp__0 
        = vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp;
    vlSelfRef.__Vtrigprevexpr___TOP__CLK__0 = vlSelfRef.CLK;
    vlSelfRef.__Vtrigprevexpr___TOP__DrIO__0 = vlSelfRef.DrIO;
    vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp__1 
        = vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp;
    vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp__1 
        = vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp;
    vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp__1 
        = vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp;
    vlSelfRef.__Vtrigprevexpr___TOP__CLKIO__0 = vlSelfRef.CLKIO;
    vlSelfRef.__Vtrigprevexpr_h7a48d089__1 = ((~ (IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp)) 
                                              & (IData)(vlSelfRef.CLK));
    vlSelfRef.__Vtrigprevexpr_h805998fe__1 = ((~ (IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp)) 
                                              & (IData)(vlSelfRef.CLK));
}

VL_ATTR_COLD void Vmain_cpu___024root___eval_initial__TOP(Vmain_cpu___024root* vlSelf);

VL_ATTR_COLD void Vmain_cpu___024root___eval_initial(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_initial\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vmain_cpu___024root___eval_initial__TOP(vlSelf);
}

VL_ATTR_COLD void Vmain_cpu___024root___eval_initial__TOP__4(Vmain_cpu___024root* vlSelf);
VL_ATTR_COLD void Vmain_cpu___024root___eval_initial__TOP__5(Vmain_cpu___024root* vlSelf);
VL_ATTR_COLD void Vmain_cpu___024root___eval_initial__TOP__6(Vmain_cpu___024root* vlSelf);

VL_ATTR_COLD void Vmain_cpu___024root___eval_initial__TOP(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_initial__TOP\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vmain_cpu___024root___eval_initial__TOP__4(vlSelf);
    Vmain_cpu___024root___eval_initial__TOP__5(vlSelf);
    Vmain_cpu___024root___eval_initial__TOP__6(vlSelf);
    {
        // Inlined CFunc: _eval_initial__TOP__7
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[298U] = 0x000f8067U;
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[299U] = 0x000025b7U;
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[300U] = 0x02058593U;
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[301U] = 0x000f8067U;
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[302U] = 0x000845b7U;
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[303U] = 0x24858593U;
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[304U] = 0x000f8067U;
    }
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[0U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[1U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[2U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[3U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[4U] = 7U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[5U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[6U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[7U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[8U] = 6U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[9U] = 6U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[10U] = 6U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[11U] = 6U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[12U] = 5U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[13U] = 5U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[14U] = 5U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[15U] = 5U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[16U] = 4U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[17U] = 4U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[18U] = 4U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[19U] = 4U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[20U] = 8U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[21U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[22U] = 9U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[23U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[24U] = 3U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[25U] = 3U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[26U] = 3U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[27U] = 3U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[28U] = 2U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[29U] = 2U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[30U] = 2U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[31U] = 2U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[32U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[33U] = 0x0aU;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[34U] = 1U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[35U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[36U] = 7U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[37U] = 0x0bU;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[38U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[39U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[40U] = 6U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[41U] = 0x0dU;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[42U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[43U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[44U] = 5U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[45U] = 0x0cU;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[46U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[47U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[48U] = 4U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[49U] = 0x0eU;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[50U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[51U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[52U] = 8U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[53U] = 0x0fU;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[54U] = 9U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[55U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[56U] = 3U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[57U] = 0x10U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[58U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[59U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[60U] = 2U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[61U] = 0x11U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[0U] = 0x1026U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[1U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[2U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[3U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[4U] = 0x0022U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[5U] = 0x0312U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[6U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[7U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[8U] = 0x1121U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[9U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[10U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[11U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[12U] = 0x0802U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[13U] = 0x030eU;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[14U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[15U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[16U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[17U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[18U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[19U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[20U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[21U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[22U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[23U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[24U] = 0x1ac0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[25U] = 0x10aaU;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[26U] = 0U;
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[27U] = 0x044aU;
}

VL_ATTR_COLD void Vmain_cpu___024root___eval_initial__TOP__0(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_initial__TOP__0\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[0U] = 0x000802b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[1U] = 0x0002a023U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[2U] = 0x00040437U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[3U] = 0x00082ab7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[4U] = 0xfff00c13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[5U] = 0x00000c93U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[6U] = 0x1f400fefU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[7U] = 0x00000d13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[8U] = 0x00000d93U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[9U] = 0x03e00513U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[10U] = 0x220000efU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[11U] = 0x02000513U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[12U] = 0x218000efU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[13U] = 0x00000493U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[14U] = 0x00000913U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[15U] = 0x00080337U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[16U] = 0x02430313U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[17U] = 0x00032383U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[18U] = 0x0013f393U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[19U] = 0xfe038ce3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[20U] = 0x00080337U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[21U] = 0x02030313U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[22U] = 0x00034503U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[23U] = 0x06100293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[24U] = 0x00554863U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[25U] = 0x07a00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[26U] = 0x00a2c463U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[27U] = 0xfe050513U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[28U] = 0x1d8000efU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[29U] = 0x00d00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[30U] = 0x04550e63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[31U] = 0x00a00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[32U] = 0x04550a63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[33U] = 0x03a00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[34U] = 0x0a550063U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[35U] = 0x05200293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[36U] = 0x14550c63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[37U] = 0x03000293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[38U] = 0xfa5542e3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[39U] = 0x03900293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[40U] = 0x00a2c663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[41U] = 0xfd050293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[42U] = 0x0180006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[43U] = 0x04100293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[44U] = 0xf85546e3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[45U] = 0x04600293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[46U] = 0xf8a2c2e3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[47U] = 0xfc950293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[48U] = 0x00f2f293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[49U] = 0x00449493U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[50U] = 0x0054e4b3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[51U] = 0x00100913U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[52U] = 0xf6dff06fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[53U] = 0x00090463U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[54U] = 0x00048413U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[55U] = 0x03a00513U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[56U] = 0x168000efU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[57U] = 0x02000513U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[58U] = 0x160000efU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[59U] = 0x00042983U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[60U] = 0x01c00a13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[61U] = 0x0149d2b3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[62U] = 0x00f2f293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[63U] = 0x00a00313U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[64U] = 0x0062c663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[65U] = 0x03728293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[66U] = 0x0080006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[67U] = 0x03028293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[68U] = 0x00028513U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[69U] = 0x134000efU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[70U] = 0xffca0a13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[71U] = 0xfc0a5ce3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[72U] = 0x00440413U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[73U] = 0x0e00006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[74U] = 0x00090463U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[75U] = 0x00048413U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[76U] = 0x00000493U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[77U] = 0x00000913U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[78U] = 0x00080337U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[79U] = 0x02430313U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[80U] = 0x00032383U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[81U] = 0x0013f393U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[82U] = 0xfe038ce3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[83U] = 0x00080337U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[84U] = 0x02030313U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[85U] = 0x00034503U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[86U] = 0x06100293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[87U] = 0x00554863U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[88U] = 0x07a00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[89U] = 0x00a2c463U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[90U] = 0xfe050513U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[91U] = 0x0dc000efU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[92U] = 0x02000293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[93U] = 0x04550a63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[94U] = 0x00d00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[95U] = 0x04550e63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[96U] = 0x00a00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[97U] = 0x04550a63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[98U] = 0x03000293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[99U] = 0xfa5546e3U;
}

VL_ATTR_COLD void Vmain_cpu___024root___eval_initial__TOP__1(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_initial__TOP__1\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[100U] = 0x03900293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[101U] = 0x00a2c663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[102U] = 0xfd050293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[103U] = 0x0180006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[104U] = 0x04100293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[105U] = 0xf8554ae3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[106U] = 0x04600293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[107U] = 0xf8a2c6e3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[108U] = 0xfc950293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[109U] = 0x00f2f293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[110U] = 0x00449493U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[111U] = 0x0054e4b3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[112U] = 0x00100913U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[113U] = 0xf75ff06fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[114U] = 0xf60908e3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[115U] = 0x00942023U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[116U] = 0x00440413U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[117U] = 0xf5dff06fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[118U] = 0x02090663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[119U] = 0x00942023U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[120U] = 0x00440413U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[121U] = 0x0200006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[122U] = 0x00090463U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[123U] = 0x00048413U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[124U] = 0x00000d13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[125U] = 0x00000d93U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[126U] = 0x01400fefU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[127U] = 0x00000093U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[128U] = 0x00040067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[129U] = 0x120000efU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[130U] = 0xe1dff06fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[131U] = 0x000a8293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[132U] = 0x00001337U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[133U] = 0xfa030313U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[134U] = 0x0182a023U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[135U] = 0x0182a223U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[136U] = 0x0182a423U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[137U] = 0x0182a623U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[138U] = 0x0182a823U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[139U] = 0x0182aa23U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[140U] = 0x0182ac23U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[141U] = 0x0182ae23U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[142U] = 0x02028293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[143U] = 0xfff30313U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[144U] = 0xfc031ce3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[145U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[146U] = 0x00a00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[147U] = 0x0c550c63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[148U] = 0x00d00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[149U] = 0x0c550863U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[150U] = 0x02000293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[151U] = 0x0a550e63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[152U] = 0x0e000fefU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[153U] = 0x002d1293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[154U] = 0x01a282b3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[155U] = 0x002d9313U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[156U] = 0x001d9393U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[157U] = 0x00730333U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[158U] = 0x00831e93U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[159U] = 0x00631f13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[160U] = 0x01ee8eb3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[161U] = 0x005e8eb3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[162U] = 0x001e9e93U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[163U] = 0x015e8eb3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[164U] = 0x01300893U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[165U] = 0x00000393U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[166U] = 0x0115df33U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[167U] = 0x001f7f13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[168U] = 0x000f0663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[169U] = 0x019e9023U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[170U] = 0x0080006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[171U] = 0x018e9023U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[172U] = 0xfff88893U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[173U] = 0x0115df33U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[174U] = 0x001f7f13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[175U] = 0x000f0663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[176U] = 0x019e9123U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[177U] = 0x0080006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[178U] = 0x018e9123U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[179U] = 0xfff88893U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[180U] = 0x0115df33U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[181U] = 0x001f7f13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[182U] = 0x000f0663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[183U] = 0x019e9223U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[184U] = 0x0080006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[185U] = 0x018e9223U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[186U] = 0xfff88893U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[187U] = 0x0115df33U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[188U] = 0x001f7f13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[189U] = 0x000f0663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[190U] = 0x019e9323U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[191U] = 0x0080006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[192U] = 0x018e9323U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[193U] = 0xfff88893U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[194U] = 0x280e8e93U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[195U] = 0x00138393U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[196U] = 0x00500f13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[197U] = 0xf9e3c2e3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[198U] = 0x001d0d13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[199U] = 0x04000293U;
}

VL_ATTR_COLD void Vmain_cpu___024root___eval_initial__TOP__2(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_initial__TOP__2\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[200U] = 0x005d4e63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[201U] = 0x00000d13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[202U] = 0x001d8d93U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[203U] = 0x02100293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[204U] = 0x005dc663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[205U] = 0x00000d93U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[206U] = 0xed5fffefU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[207U] = 0x00008067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[208U] = 0x03000293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[209U] = 0x08550e63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[210U] = 0x03100293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[211U] = 0x0a550063U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[212U] = 0x03200293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[213U] = 0x0a550263U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[214U] = 0x03300293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[215U] = 0x0a550463U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[216U] = 0x03400293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[217U] = 0x0a550663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[218U] = 0x03500293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[219U] = 0x0a550863U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[220U] = 0x03600293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[221U] = 0x0a550a63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[222U] = 0x03700293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[223U] = 0x0a550c63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[224U] = 0x03800293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[225U] = 0x0a550e63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[226U] = 0x03900293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[227U] = 0x0c550063U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[228U] = 0x04100293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[229U] = 0x0c550263U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[230U] = 0x04200293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[231U] = 0x0c550463U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[232U] = 0x04300293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[233U] = 0x0c550663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[234U] = 0x04400293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[235U] = 0x0c550863U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[236U] = 0x04500293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[237U] = 0x0c550a63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[238U] = 0x04600293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[239U] = 0x0c550c63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[240U] = 0x05200293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[241U] = 0x0c550e63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[242U] = 0x03a00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[243U] = 0x0e550063U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[244U] = 0x03e00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[245U] = 0x0e550263U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[246U] = 0x00000593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[247U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[248U] = 0x0006a5b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[249U] = 0x99658593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[250U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[251U] = 0x0004c5b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[252U] = 0x44e58593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[253U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[254U] = 0x000695b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[255U] = 0x24f58593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[256U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[257U] = 0x000f15b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[258U] = 0x61f58593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[259U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[260U] = 0x0009a5b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[261U] = 0xf1158593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[262U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[263U] = 0x000f95b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[264U] = 0xe1e58593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[265U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[266U] = 0x000795b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[267U] = 0xe9658593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[268U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[269U] = 0x000f15b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[270U] = 0x24458593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[271U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[272U] = 0x000695b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[273U] = 0x69658593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[274U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[275U] = 0x000695b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[276U] = 0x71658593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[277U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[278U] = 0x0006a5b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[279U] = 0xf9958593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[280U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[281U] = 0x000ea5b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[282U] = 0xe9e58593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[283U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[284U] = 0x0006a5b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[285U] = 0x89658593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[286U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[287U] = 0x000ea5b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[288U] = 0x99e58593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[289U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[290U] = 0x000f95b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[291U] = 0xe8f58593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[292U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[293U] = 0x000f95b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[294U] = 0xe8858593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[295U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[296U] = 0x000ea5b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[297U] = 0xea958593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[298U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[299U] = 0x000025b7U;
}

VL_ATTR_COLD void Vmain_cpu___024root___eval_initial__TOP__3(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_initial__TOP__3\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[300U] = 0x02058593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[301U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[302U] = 0x000845b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[303U] = 0x24858593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[304U] = 0x000f8067U;
}

VL_ATTR_COLD void Vmain_cpu___024root___eval_initial__TOP__4(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_initial__TOP__4\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vmain_cpu___024root___eval_initial__TOP__0(vlSelf);
    Vmain_cpu___024root___eval_initial__TOP__1(vlSelf);
    Vmain_cpu___024root___eval_initial__TOP__2(vlSelf);
    Vmain_cpu___024root___eval_initial__TOP__3(vlSelf);
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[0U] = 0x000802b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[1U] = 0x0002a023U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[2U] = 0x00040437U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[3U] = 0x00082ab7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[4U] = 0xfff00c13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[5U] = 0x00000c93U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[6U] = 0x1f400fefU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[7U] = 0x00000d13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[8U] = 0x00000d93U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[9U] = 0x03e00513U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[10U] = 0x220000efU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[11U] = 0x02000513U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[12U] = 0x218000efU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[13U] = 0x00000493U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[14U] = 0x00000913U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[15U] = 0x00080337U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[16U] = 0x02430313U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[17U] = 0x00032383U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[18U] = 0x0013f393U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[19U] = 0xfe038ce3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[20U] = 0x00080337U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[21U] = 0x02030313U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[22U] = 0x00034503U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[23U] = 0x06100293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[24U] = 0x00554863U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[25U] = 0x07a00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[26U] = 0x00a2c463U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[27U] = 0xfe050513U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[28U] = 0x1d8000efU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[29U] = 0x00d00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[30U] = 0x04550e63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[31U] = 0x00a00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[32U] = 0x04550a63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[33U] = 0x03a00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[34U] = 0x0a550063U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[35U] = 0x05200293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[36U] = 0x14550c63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[37U] = 0x03000293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[38U] = 0xfa5542e3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[39U] = 0x03900293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[40U] = 0x00a2c663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[41U] = 0xfd050293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[42U] = 0x0180006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[43U] = 0x04100293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[44U] = 0xf85546e3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[45U] = 0x04600293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[46U] = 0xf8a2c2e3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[47U] = 0xfc950293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[48U] = 0x00f2f293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[49U] = 0x00449493U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[50U] = 0x0054e4b3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[51U] = 0x00100913U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[52U] = 0xf6dff06fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[53U] = 0x00090463U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[54U] = 0x00048413U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[55U] = 0x03a00513U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[56U] = 0x168000efU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[57U] = 0x02000513U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[58U] = 0x160000efU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[59U] = 0x00042983U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[60U] = 0x01c00a13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[61U] = 0x0149d2b3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[62U] = 0x00f2f293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[63U] = 0x00a00313U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[64U] = 0x0062c663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[65U] = 0x03728293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[66U] = 0x0080006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[67U] = 0x03028293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[68U] = 0x00028513U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[69U] = 0x134000efU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[70U] = 0xffca0a13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[71U] = 0xfc0a5ce3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[72U] = 0x00440413U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[73U] = 0x0e00006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[74U] = 0x00090463U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[75U] = 0x00048413U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[76U] = 0x00000493U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[77U] = 0x00000913U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[78U] = 0x00080337U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[79U] = 0x02430313U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[80U] = 0x00032383U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[81U] = 0x0013f393U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[82U] = 0xfe038ce3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[83U] = 0x00080337U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[84U] = 0x02030313U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[85U] = 0x00034503U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[86U] = 0x06100293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[87U] = 0x00554863U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[88U] = 0x07a00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[89U] = 0x00a2c463U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[90U] = 0xfe050513U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[91U] = 0x0dc000efU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[92U] = 0x02000293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[93U] = 0x04550a63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[94U] = 0x00d00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[95U] = 0x04550e63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[96U] = 0x00a00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[97U] = 0x04550a63U;
}

VL_ATTR_COLD void Vmain_cpu___024root___eval_initial__TOP__5(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_initial__TOP__5\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[98U] = 0x03000293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[99U] = 0xfa5546e3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[100U] = 0x03900293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[101U] = 0x00a2c663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[102U] = 0xfd050293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[103U] = 0x0180006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[104U] = 0x04100293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[105U] = 0xf8554ae3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[106U] = 0x04600293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[107U] = 0xf8a2c6e3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[108U] = 0xfc950293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[109U] = 0x00f2f293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[110U] = 0x00449493U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[111U] = 0x0054e4b3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[112U] = 0x00100913U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[113U] = 0xf75ff06fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[114U] = 0xf60908e3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[115U] = 0x00942023U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[116U] = 0x00440413U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[117U] = 0xf5dff06fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[118U] = 0x02090663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[119U] = 0x00942023U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[120U] = 0x00440413U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[121U] = 0x0200006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[122U] = 0x00090463U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[123U] = 0x00048413U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[124U] = 0x00000d13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[125U] = 0x00000d93U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[126U] = 0x01400fefU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[127U] = 0x00000093U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[128U] = 0x00040067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[129U] = 0x120000efU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[130U] = 0xe1dff06fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[131U] = 0x000a8293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[132U] = 0x00001337U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[133U] = 0xfa030313U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[134U] = 0x0182a023U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[135U] = 0x0182a223U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[136U] = 0x0182a423U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[137U] = 0x0182a623U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[138U] = 0x0182a823U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[139U] = 0x0182aa23U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[140U] = 0x0182ac23U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[141U] = 0x0182ae23U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[142U] = 0x02028293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[143U] = 0xfff30313U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[144U] = 0xfc031ce3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[145U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[146U] = 0x00a00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[147U] = 0x0c550c63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[148U] = 0x00d00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[149U] = 0x0c550863U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[150U] = 0x02000293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[151U] = 0x0a550e63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[152U] = 0x0e000fefU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[153U] = 0x002d1293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[154U] = 0x01a282b3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[155U] = 0x002d9313U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[156U] = 0x001d9393U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[157U] = 0x00730333U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[158U] = 0x00831e93U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[159U] = 0x00631f13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[160U] = 0x01ee8eb3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[161U] = 0x005e8eb3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[162U] = 0x001e9e93U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[163U] = 0x015e8eb3U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[164U] = 0x01300893U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[165U] = 0x00000393U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[166U] = 0x0115df33U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[167U] = 0x001f7f13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[168U] = 0x000f0663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[169U] = 0x019e9023U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[170U] = 0x0080006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[171U] = 0x018e9023U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[172U] = 0xfff88893U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[173U] = 0x0115df33U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[174U] = 0x001f7f13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[175U] = 0x000f0663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[176U] = 0x019e9123U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[177U] = 0x0080006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[178U] = 0x018e9123U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[179U] = 0xfff88893U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[180U] = 0x0115df33U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[181U] = 0x001f7f13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[182U] = 0x000f0663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[183U] = 0x019e9223U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[184U] = 0x0080006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[185U] = 0x018e9223U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[186U] = 0xfff88893U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[187U] = 0x0115df33U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[188U] = 0x001f7f13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[189U] = 0x000f0663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[190U] = 0x019e9323U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[191U] = 0x0080006fU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[192U] = 0x018e9323U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[193U] = 0xfff88893U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[194U] = 0x280e8e93U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[195U] = 0x00138393U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[196U] = 0x00500f13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[197U] = 0xf9e3c2e3U;
}

VL_ATTR_COLD void Vmain_cpu___024root___eval_initial__TOP__6(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_initial__TOP__6\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[198U] = 0x001d0d13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[199U] = 0x04000293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[200U] = 0x005d4e63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[201U] = 0x00000d13U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[202U] = 0x001d8d93U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[203U] = 0x02100293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[204U] = 0x005dc663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[205U] = 0x00000d93U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[206U] = 0xed5fffefU;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[207U] = 0x00008067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[208U] = 0x03000293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[209U] = 0x08550e63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[210U] = 0x03100293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[211U] = 0x0a550063U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[212U] = 0x03200293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[213U] = 0x0a550263U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[214U] = 0x03300293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[215U] = 0x0a550463U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[216U] = 0x03400293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[217U] = 0x0a550663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[218U] = 0x03500293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[219U] = 0x0a550863U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[220U] = 0x03600293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[221U] = 0x0a550a63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[222U] = 0x03700293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[223U] = 0x0a550c63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[224U] = 0x03800293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[225U] = 0x0a550e63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[226U] = 0x03900293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[227U] = 0x0c550063U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[228U] = 0x04100293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[229U] = 0x0c550263U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[230U] = 0x04200293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[231U] = 0x0c550463U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[232U] = 0x04300293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[233U] = 0x0c550663U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[234U] = 0x04400293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[235U] = 0x0c550863U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[236U] = 0x04500293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[237U] = 0x0c550a63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[238U] = 0x04600293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[239U] = 0x0c550c63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[240U] = 0x05200293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[241U] = 0x0c550e63U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[242U] = 0x03a00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[243U] = 0x0e550063U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[244U] = 0x03e00293U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[245U] = 0x0e550263U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[246U] = 0x00000593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[247U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[248U] = 0x0006a5b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[249U] = 0x99658593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[250U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[251U] = 0x0004c5b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[252U] = 0x44e58593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[253U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[254U] = 0x000695b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[255U] = 0x24f58593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[256U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[257U] = 0x000f15b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[258U] = 0x61f58593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[259U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[260U] = 0x0009a5b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[261U] = 0xf1158593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[262U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[263U] = 0x000f95b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[264U] = 0xe1e58593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[265U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[266U] = 0x000795b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[267U] = 0xe9658593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[268U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[269U] = 0x000f15b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[270U] = 0x24458593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[271U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[272U] = 0x000695b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[273U] = 0x69658593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[274U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[275U] = 0x000695b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[276U] = 0x71658593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[277U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[278U] = 0x0006a5b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[279U] = 0xf9958593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[280U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[281U] = 0x000ea5b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[282U] = 0xe9e58593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[283U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[284U] = 0x0006a5b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[285U] = 0x89658593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[286U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[287U] = 0x000ea5b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[288U] = 0x99e58593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[289U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[290U] = 0x000f95b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[291U] = 0xe8f58593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[292U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[293U] = 0x000f95b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[294U] = 0xe8858593U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[295U] = 0x000f8067U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[296U] = 0x000ea5b7U;
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[297U] = 0xea958593U;
}

VL_ATTR_COLD void Vmain_cpu___024root___eval_final(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_final\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmain_cpu___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vmain_cpu___024root___eval_phase__stl(Vmain_cpu___024root* vlSelf);

VL_ATTR_COLD void Vmain_cpu___024root___eval_settle(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_settle\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vmain_cpu___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("main_cpu.v", 2003, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 10000 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vmain_cpu___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD bool Vmain_cpu___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 2> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmain_cpu___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vmain_cpu___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @([hybrid] main_cpu.MemoryMapperExp_i0.rs_i8.q_temp)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @([hybrid] main_cpu.Registers_i5.rs_i0.q_temp)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([hybrid] main_cpu.ProgramCounter_i10.rs_i0.q_temp)\n");
    }
    if ((1U & (IData)(triggers[1U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 64 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vmain_cpu___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 2> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___trigger_anySet__stl\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((2U > n));
    return (0U);
}

VL_ATTR_COLD void Vmain_cpu___024root___stl_sequent__TOP__0(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___stl_sequent__TOP__0\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ main_cpu__DOT__s1;
    main_cpu__DOT__s1 = 0;
    IData/*31:0*/ main_cpu__DOT__s2;
    main_cpu__DOT__s2 = 0;
    CData/*5:0*/ main_cpu__DOT__ControlLogic_i3__DOT__s8;
    main_cpu__DOT__ControlLogic_i3__DOT__s8 = 0;
    CData/*0:0*/ main_cpu__DOT__ALU_i4__DOT__lt_u;
    main_cpu__DOT__ALU_i4__DOT__lt_u = 0;
    CData/*0:0*/ main_cpu__DOT__ALU_i4__DOT__lt_s;
    main_cpu__DOT__ALU_i4__DOT__lt_s = 0;
    QData/*63:0*/ main_cpu__DOT__ALU_i4__DOT__mul_uu;
    main_cpu__DOT__ALU_i4__DOT__mul_uu = 0;
    CData/*0:0*/ main_cpu__DOT__ALU_i4__DOT__is_div_overflow;
    main_cpu__DOT__ALU_i4__DOT__is_div_overflow = 0;
    // Body
    vlSelfRef.__VdfgRegularize_hebeb780c_0_4 = (0x00000001ffffffffULL 
                                                & (4ULL 
                                                   + (QData)((IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state))));
    vlSelfRef.main_cpu__DOT__s27 = ((IData)((0x00040000U 
                                             != (0xfffc0000U 
                                                 & vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state)))
                                     ? (vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom
                                        [(0x000001ffU 
                                          & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state 
                                             >> 2U))] 
                                        & (- (IData)(
                                                     ((0x0130U 
                                                       >= 
                                                       (0x000001ffU 
                                                        & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state 
                                                           >> 2U))) 
                                                      & (0x0130U 
                                                         >= 
                                                         (0x000007ffU 
                                                          & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state 
                                                             >> 2U)))))))
                                     : (((((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory
                                                   [
                                                   (0x0000ffffU 
                                                    & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state 
                                                       >> 2U))]) 
                                           << 8U) | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory
                                          [(0x0000ffffU 
                                            & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state 
                                               >> 2U))]) 
                                         << 0x00000010U) 
                                        | (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory
                                                    [
                                                    (0x0000ffffU 
                                                     & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state 
                                                        >> 2U))]) 
                                            << 8U) 
                                           | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory
                                           [(0x0000ffffU 
                                             & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state 
                                                >> 2U))])));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_6 = (3U 
                                                & (~ 
                                                   (((0U 
                                                      == 
                                                      (3U 
                                                       & (vlSelfRef.main_cpu__DOT__s27 
                                                          >> 0x0000000cU))) 
                                                     << 1U) 
                                                    | (1U 
                                                       & (~ 
                                                          (vlSelfRef.main_cpu__DOT__s27 
                                                           >> 0x0000000eU))))));
    vlSelfRef.main_cpu__DOT__DataController_i1__DOT__s24 
        = ((0U == (3U & (vlSelfRef.main_cpu__DOT__s27 
                         >> 0x0000000cU))) | (1U == 
                                              (3U & 
                                               (vlSelfRef.main_cpu__DOT__s27 
                                                >> 0x0000000cU))));
    main_cpu__DOT__s2 = (vlSelfRef.main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory
                         [(0x0000001fU & (vlSelfRef.main_cpu__DOT__s27 
                                          >> 0x0000000fU))] 
                         & (- (IData)((0U != (0x0000001fU 
                                              & (vlSelfRef.main_cpu__DOT__s27 
                                                 >> 0x0000000fU))))));
    vlSelfRef.main_cpu__DOT__s11 = (vlSelfRef.main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory
                                    [(0x0000001fU & 
                                      (vlSelfRef.main_cpu__DOT__s27 
                                       >> 0x00000014U))] 
                                    & (- (IData)((0U 
                                                  != 
                                                  (0x0000001fU 
                                                   & (vlSelfRef.main_cpu__DOT__s27 
                                                      >> 0x00000014U))))));
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1 
        = (vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom
           [(0x0000001fU & (vlSelfRef.main_cpu__DOT__s27 
                            >> 2U))] & (- (IData)((0x1bU 
                                                   >= 
                                                   (0x0000001fU 
                                                    & (vlSelfRef.main_cpu__DOT__s27 
                                                       >> 2U))))));
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s6 
        = (0x000000ffU & ((0U == (3U & (vlSelfRef.main_cpu__DOT__s27 
                                        >> 0x0000000cU)))
                           ? vlSelfRef.main_cpu__DOT__s11
                           : (vlSelfRef.main_cpu__DOT__s11 
                              >> 8U)));
    if ((1U == (3U & (vlSelfRef.main_cpu__DOT__s27 
                      >> 0x0000000cU)))) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s7 
            = (0x000000ffU & vlSelfRef.main_cpu__DOT__s11);
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s8 
            = (0x000000ffU & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s6));
    } else if ((0U == (3U & (vlSelfRef.main_cpu__DOT__s27 
                             >> 0x0000000cU)))) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s7 
            = (0x000000ffU & vlSelfRef.main_cpu__DOT__s11);
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s8 
            = (0x000000ffU & vlSelfRef.main_cpu__DOT__s11);
    } else {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s7 
            = (0x000000ffU & (vlSelfRef.main_cpu__DOT__s11 
                              >> 0x00000010U));
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s8 
            = (0x000000ffU & (vlSelfRef.main_cpu__DOT__s11 
                              >> 0x00000018U));
    }
    main_cpu__DOT__ControlLogic_i3__DOT__s8 = (((1U 
                                                 == 
                                                 (3U 
                                                  & ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                                     >> 0x0000000bU))) 
                                                << 5U) 
                                               | ((0x0000001cU 
                                                   & (vlSelfRef.main_cpu__DOT__s27 
                                                      >> 0x0000000aU)) 
                                                  | ((2U 
                                                      & (vlSelfRef.main_cpu__DOT__s27 
                                                         >> 0x0000001dU)) 
                                                     | (1U 
                                                        & (vlSelfRef.main_cpu__DOT__s27 
                                                           >> 0x00000019U)))));
    vlSelfRef.main_cpu__DOT__s21 = ((0x00000400U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                     ? (((((0x00000ffeU 
                                            & ((- (IData)(
                                                          (vlSelfRef.main_cpu__DOT__s27 
                                                           >> 0x0000001fU))) 
                                               << 1U)) 
                                           | (vlSelfRef.main_cpu__DOT__s27 
                                              >> 0x0000001fU)) 
                                          << 0x00000014U) 
                                         | ((((0x000001feU 
                                               & (vlSelfRef.main_cpu__DOT__s27 
                                                  >> 0x0000000bU)) 
                                              | (1U 
                                                 & (vlSelfRef.main_cpu__DOT__s27 
                                                    >> 0x00000014U))) 
                                             << 0x0000000bU) 
                                            | (0x000007feU 
                                               & (vlSelfRef.main_cpu__DOT__s27 
                                                  >> 0x00000014U)))) 
                                        & ((- (IData)(
                                                      (1U 
                                                       & (~ 
                                                          ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                                           >> 9U))))) 
                                           & (- (IData)(
                                                        (1U 
                                                         & (~ 
                                                            ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                                             >> 8U)))))))
                                     : ((0x00000200U 
                                         & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                         ? (((0x00000100U 
                                              & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                              ? (0x7ffff800U 
                                                 & (vlSelfRef.main_cpu__DOT__s27 
                                                    >> 1U))
                                              : ((0x7ffff000U 
                                                  & ((- (IData)(
                                                                (vlSelfRef.main_cpu__DOT__s27 
                                                                 >> 0x0000001fU))) 
                                                     << 0x0000000cU)) 
                                                 | ((((2U 
                                                       & (vlSelfRef.main_cpu__DOT__s27 
                                                          >> 0x0000001eU)) 
                                                      | (1U 
                                                         & (vlSelfRef.main_cpu__DOT__s27 
                                                            >> 7U))) 
                                                     << 0x0000000aU) 
                                                    | ((0x000003f0U 
                                                        & (vlSelfRef.main_cpu__DOT__s27 
                                                           >> 0x00000015U)) 
                                                       | (0x0000000fU 
                                                          & (vlSelfRef.main_cpu__DOT__s27 
                                                             >> 8U)))))) 
                                            << 1U) : 
                                        (((- (IData)(
                                                     (vlSelfRef.main_cpu__DOT__s27 
                                                      >> 0x0000001fU))) 
                                          << 0x0000000cU) 
                                         | ((0x00000fe0U 
                                             & (vlSelfRef.main_cpu__DOT__s27 
                                                >> 0x00000014U)) 
                                            | (0x0000001fU 
                                               & ((0x00000100U 
                                                   & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                                   ? 
                                                  (vlSelfRef.main_cpu__DOT__s27 
                                                   >> 7U)
                                                   : 
                                                  (vlSelfRef.main_cpu__DOT__s27 
                                                   >> 0x00000014U)))))));
    vlSelfRef.main_cpu__DOT__s0 = (0x0000001fU & ((0x00001000U 
                                                   & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                                   ? 
                                                  ((0x00a6U 
                                                    >> 
                                                    ((IData)(5U) 
                                                     * 
                                                     (1U 
                                                      & (vlSelfRef.main_cpu__DOT__s27 
                                                         >> 0x0000000dU)))) 
                                                   & (- (IData)(
                                                                (1U 
                                                                 & ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                                                    >> 0x0000000bU)))))
                                                   : 
                                                  (vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom
                                                   [main_cpu__DOT__ControlLogic_i3__DOT__s8] 
                                                   & (- (IData)(
                                                                (0x3dU 
                                                                 >= (IData)(main_cpu__DOT__ControlLogic_i3__DOT__s8)))))));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_8 = (0x00000001ffffffffULL 
                                                & ((QData)((IData)(vlSelfRef.main_cpu__DOT__s21)) 
                                                   + (QData)((IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state))));
    main_cpu__DOT__s1 = ((0x00000020U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                          ? vlSelfRef.main_cpu__DOT__s21
                          : vlSelfRef.main_cpu__DOT__s11);
    vlSelfRef.DwIO = ((((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s8) 
                        << 0x00000018U) | ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s7) 
                                           << 0x00000010U)) 
                      | (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s6) 
                          << 8U) | (0x000000ffU & vlSelfRef.main_cpu__DOT__s11)));
    vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s2 
        = (main_cpu__DOT__s1 == main_cpu__DOT__s2);
    main_cpu__DOT__ALU_i4__DOT__mul_uu = ((QData)((IData)(main_cpu__DOT__s1)) 
                                          * (QData)((IData)(main_cpu__DOT__s2)));
    main_cpu__DOT__ALU_i4__DOT__is_div_overflow = (
                                                   (0x80000000U 
                                                    == main_cpu__DOT__s2) 
                                                   & (0xffffffffU 
                                                      == main_cpu__DOT__s1));
    main_cpu__DOT__ALU_i4__DOT__lt_u = (main_cpu__DOT__s2 
                                        < main_cpu__DOT__s1);
    main_cpu__DOT__ALU_i4__DOT__lt_s = VL_LTS_III(32, main_cpu__DOT__s2, main_cpu__DOT__s1);
    vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s4 
        = ((6U == (IData)(vlSelfRef.main_cpu__DOT__s0))
            ? (IData)(main_cpu__DOT__ALU_i4__DOT__lt_s)
            : (IData)(main_cpu__DOT__ALU_i4__DOT__lt_u));
    vlSelfRef.AddIO = ((0x00000010U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                        ? ((- (IData)((1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__s0) 
                                                >> 2U))))) 
                           & ((- (IData)((1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__s0) 
                                                   >> 1U))))) 
                              & (((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                   ? ((0U == main_cpu__DOT__s1)
                                       ? main_cpu__DOT__s2
                                       : VL_MODDIV_III(32, main_cpu__DOT__s2, main_cpu__DOT__s1))
                                   : ((0U == main_cpu__DOT__s1)
                                       ? main_cpu__DOT__s2
                                       : (VL_MODDIVS_III(32, main_cpu__DOT__s2, main_cpu__DOT__s1) 
                                          & (- (IData)(
                                                       (1U 
                                                        & (~ (IData)(main_cpu__DOT__ALU_i4__DOT__is_div_overflow)))))))) 
                                 & (- (IData)((1U & 
                                               (~ ((IData)(vlSelfRef.main_cpu__DOT__s0) 
                                                   >> 3U))))))))
                        : ((8U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                            ? ((4U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                ? ((2U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                    ? ((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                        ? (VL_DIV_III(32, main_cpu__DOT__s2, main_cpu__DOT__s1) 
                                           | (- (IData)(
                                                        (0U 
                                                         == main_cpu__DOT__s1))))
                                        : (((IData)(main_cpu__DOT__ALU_i4__DOT__is_div_overflow)
                                             ? 0x80000000U
                                             : VL_DIVS_III(32, main_cpu__DOT__s2, main_cpu__DOT__s1)) 
                                           | (- (IData)(
                                                        (0U 
                                                         == main_cpu__DOT__s1)))))
                                    : ((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                        ? (IData)((
                                                   VL_MULS_QQQ(64, 
                                                               VL_EXTENDS_QI(64,32, main_cpu__DOT__s2), 
                                                               VL_EXTENDS_QQ(64,33, (QData)((IData)(main_cpu__DOT__s1)))) 
                                                   >> 0x00000020U))
                                        : (IData)((main_cpu__DOT__ALU_i4__DOT__mul_uu 
                                                   >> 0x00000020U))))
                                : ((2U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                    ? ((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                        ? (IData)((
                                                   VL_MULS_QQQ(64, 
                                                               VL_EXTENDS_QI(64,32, main_cpu__DOT__s2), 
                                                               VL_EXTENDS_QI(64,32, main_cpu__DOT__s1)) 
                                                   >> 0x00000020U))
                                        : (IData)(main_cpu__DOT__ALU_i4__DOT__mul_uu))
                                    : ((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                        ? VL_SHIFTRS_III(32,32,5, main_cpu__DOT__s2, 
                                                         (0x0000001fU 
                                                          & main_cpu__DOT__s1))
                                        : (main_cpu__DOT__s2 
                                           >> (0x0000001fU 
                                               & main_cpu__DOT__s1)))))
                            : ((4U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                ? ((2U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                    ? ((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                        ? (main_cpu__DOT__s2 
                                           << (0x0000001fU 
                                               & main_cpu__DOT__s1))
                                        : (IData)(main_cpu__DOT__ALU_i4__DOT__lt_s))
                                    : ((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                        ? (IData)(main_cpu__DOT__ALU_i4__DOT__lt_u)
                                        : (main_cpu__DOT__s1 
                                           ^ main_cpu__DOT__s2)))
                                : ((2U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                    ? ((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                        ? (main_cpu__DOT__s1 
                                           | main_cpu__DOT__s2)
                                        : (main_cpu__DOT__s1 
                                           & main_cpu__DOT__s2))
                                    : ((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                        ? (main_cpu__DOT__s2 
                                           - main_cpu__DOT__s1)
                                        : (main_cpu__DOT__s1 
                                           + main_cpu__DOT__s2))))));
}

VL_ATTR_COLD void Vmain_cpu___024root___eval_stl(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_stl\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[1U])) {
        Vmain_cpu___024root___stl_sequent__TOP__0(vlSelf);
        {
            // Inlined CFunc: _stl_sequent__TOP__1
            CData/*3:0*/ __Vinline_0__stl_sequent__TOP__1_main_cpu__DOT__DataController_i1__DOT__s26;
            __Vinline_0__stl_sequent__TOP__1_main_cpu__DOT__DataController_i1__DOT__s26 = 0;
            __Vinline_0__stl_sequent__TOP__1_main_cpu__DOT__DataController_i1__DOT__s26 
                = (0x0000000fU & ((((((IData)(((2U 
                                                == 
                                                (3U 
                                                 & vlSelfRef.AddIO)) 
                                               & (0x00001000U 
                                                  == 
                                                  (0x00003000U 
                                                   & vlSelfRef.main_cpu__DOT__s27)))) 
                                      | (3U == (3U 
                                                & vlSelfRef.AddIO))) 
                                     << 3U) | (((IData)(
                                                        ((1U 
                                                          == 
                                                          (3U 
                                                           & vlSelfRef.AddIO)) 
                                                         & (0x00001000U 
                                                            == 
                                                            (0x00003000U 
                                                             & vlSelfRef.main_cpu__DOT__s27)))) 
                                                | (2U 
                                                   == 
                                                   (3U 
                                                    & vlSelfRef.AddIO))) 
                                               << 2U)) 
                                   | ((((IData)(((0U 
                                                  == 
                                                  (3U 
                                                   & vlSelfRef.AddIO)) 
                                                 & (0x00001000U 
                                                    == 
                                                    (0x00003000U 
                                                     & vlSelfRef.main_cpu__DOT__s27)))) 
                                        | (1U == (3U 
                                                  & vlSelfRef.AddIO))) 
                                       << 1U) | (0U 
                                                 == 
                                                 (3U 
                                                  & vlSelfRef.AddIO)))) 
                                  | (- (IData)((1U 
                                                & (~ (IData)(vlSelfRef.main_cpu__DOT__DataController_i1__DOT__s24)))))));
            vlSelfRef.__VdfgRegularize_hebeb780c_0_3 
                = (IData)((0x00040000U != (0xfffc0000U 
                                           & vlSelfRef.AddIO)));
            vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s0 
                = ((- (IData)((1U & ((~ (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3)) 
                                     & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))))) 
                   & __Vinline_0__stl_sequent__TOP__1_main_cpu__DOT__DataController_i1__DOT__s26);
            vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s12 
                = ((0U != (vlSelfRef.AddIO >> 0x00000012U)) 
                   & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3));
            vlSelfRef.ReIO = (IData)(((4U == (0x001cU 
                                              & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))) 
                                      & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s12)));
            vlSelfRef.WeIO = ((- (IData)(((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                          & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s12)))) 
                              & __Vinline_0__stl_sequent__TOP__1_main_cpu__DOT__DataController_i1__DOT__s26);
            vlSelfRef.main_cpu__DOT__s12 = ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s12)
                                             ? vlSelfRef.DrIO
                                             : ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3)
                                                 ? 
                                                (vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom
                                                 [(0x000001ffU 
                                                   & (vlSelfRef.AddIO 
                                                      >> 2U))] 
                                                 & (- (IData)(
                                                              ((0x0130U 
                                                                >= 
                                                                (0x000001ffU 
                                                                 & (vlSelfRef.AddIO 
                                                                    >> 2U))) 
                                                               & (0x0130U 
                                                                  >= 
                                                                  (0x000007ffU 
                                                                   & (vlSelfRef.AddIO 
                                                                      >> 2U)))))))
                                                 : 
                                                (((((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory
                                                            [
                                                            (0x0000ffffU 
                                                             & (vlSelfRef.AddIO 
                                                                >> 2U))]) 
                                                    << 8U) 
                                                   | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory
                                                   [
                                                   (0x0000ffffU 
                                                    & (vlSelfRef.AddIO 
                                                       >> 2U))]) 
                                                  << 0x00000010U) 
                                                 | (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory
                                                             [
                                                             (0x0000ffffU 
                                                              & (vlSelfRef.AddIO 
                                                                 >> 2U))]) 
                                                     << 8U) 
                                                    | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory
                                                    [
                                                    (0x0000ffffU 
                                                     & (vlSelfRef.AddIO 
                                                        >> 2U))]))));
        }
    }
    if ((2ULL & vlSelfRef.__VstlTriggered[0U])) {
        {
            // Inlined CFunc: _stl_sequent__TOP__2
            vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__nq_temp 
                = (1U & (~ (IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp)));
        }
    }
    if ((4ULL & vlSelfRef.__VstlTriggered[0U])) {
        {
            // Inlined CFunc: _stl_sequent__TOP__3
            vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__nq_temp 
                = (1U & (~ (IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp)));
        }
    }
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        {
            // Inlined CFunc: _stl_sequent__TOP__4
            vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__nq_temp 
                = (1U & (~ (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp)));
        }
    }
    if (((1ULL & vlSelfRef.__VstlTriggered[1U]) | (2ULL 
                                                   & vlSelfRef.__VstlTriggered[0U]))) {
        {
            // Inlined CFunc: _stl_comb__TOP__0
            vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp 
                = (1U & (~ ((~ (IData)(vlSelfRef.CLK)) 
                            | (IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__nq_temp))));
        }
    }
    if (((1ULL & vlSelfRef.__VstlTriggered[1U]) | (4ULL 
                                                   & vlSelfRef.__VstlTriggered[0U]))) {
        {
            // Inlined CFunc: _stl_comb__TOP__1
            vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp 
                = (1U & (~ ((~ (IData)(vlSelfRef.CLK)) 
                            | (IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__nq_temp))));
        }
    }
    if ((1ULL & (vlSelfRef.__VstlTriggered[1U] | vlSelfRef.__VstlTriggered[0U]))) {
        {
            // Inlined CFunc: _stl_comb__TOP__2
            vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp 
                = (1U & (~ ((~ (IData)(vlSelfRef.CLK)) 
                            | (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__nq_temp))));
            vlSelfRef.CLKIO = ((~ (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp)) 
                               & (IData)(vlSelfRef.CLK));
        }
    }
}

VL_ATTR_COLD bool Vmain_cpu___024root___eval_phase__stl(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_phase__stl\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__stl
        vlSelfRef.__VstlTriggered[1U] = ((0xfffffffffffffffeULL 
                                          & vlSelfRef.__VstlTriggered[1U]) 
                                         | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
        vlSelfRef.__VstlTriggered[0U] = (QData)((IData)(
                                                        ((((IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp) 
                                                           != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp__0)) 
                                                          << 2U) 
                                                         | ((((IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp) 
                                                              != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp__0)) 
                                                             << 1U) 
                                                            | ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp) 
                                                               != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp__0))))));
        vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp__0 
            = vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp;
        vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp__0 
            = vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp;
        vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp__0 
            = vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp;
        if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.__VstlDidInit)))))) {
            vlSelfRef.__VstlDidInit = 1U;
            vlSelfRef.__VstlTriggered[0U] = (1ULL | vlSelfRef.__VstlTriggered[0U]);
            vlSelfRef.__VstlTriggered[0U] = (2ULL | vlSelfRef.__VstlTriggered[0U]);
            vlSelfRef.__VstlTriggered[0U] = (4ULL | vlSelfRef.__VstlTriggered[0U]);
        }
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vmain_cpu___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vmain_cpu___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vmain_cpu___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vmain_cpu___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 2> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmain_cpu___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vmain_cpu___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @( CLK)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @( DrIO)\n");
    }
    if ((1U & (IData)(triggers[1U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 64 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vmain_cpu___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmain_cpu___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vmain_cpu___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @([hybrid] main_cpu.MemoryMapperExp_i0.rs_i8.q_temp)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @([hybrid] main_cpu.Registers_i5.rs_i0.q_temp)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([hybrid] main_cpu.ProgramCounter_i10.rs_i0.q_temp)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @(posedge CLKIO)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 4U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 4 is active: @(posedge ((~ main_cpu.Registers_i5.rs_i0.q_temp) & CLK))\n");
    }
    if ((1U & (IData)((triggers[0U] >> 5U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 5 is active: @(posedge ((~ main_cpu.ProgramCounter_i10.rs_i0.q_temp) & CLK))\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vmain_cpu___024root___ctor_var_reset(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___ctor_var_reset\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->CLK = 0;
    vlSelf->DrIO = 0;
    vlSelf->AddIO = 0;
    vlSelf->DwIO = 0;
    vlSelf->WeIO = 0;
    vlSelf->ReIO = 0;
    vlSelf->CLKIO = 0;
    vlSelf->main_cpu__DOT__s0 = 0;
    vlSelf->main_cpu__DOT__s11 = 0;
    vlSelf->main_cpu__DOT__s12 = 0;
    vlSelf->main_cpu__DOT__s21 = 0;
    vlSelf->main_cpu__DOT__s27 = 0;
    vlSelf->main_cpu__DOT__MemoryMapperExp_i0__DOT__s12 = 0;
    vlSelf->main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s0 = 0;
    vlSelf->main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s6 = 0;
    vlSelf->main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s7 = 0;
    vlSelf->main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s8 = 0;
    for (int __Vi0 = 0; __Vi0 < 65536; ++__Vi0) {
        vlSelf->main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 65536; ++__Vi0) {
        vlSelf->main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 65536; ++__Vi0) {
        vlSelf->main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 65536; ++__Vi0) {
        vlSelf->main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory[__Vi0] = 0;
    }
    vlSelf->main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp = 0;
    vlSelf->main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__nq_temp = 0;
    for (int __Vi0 = 0; __Vi0 < 305; ++__Vi0) {
        vlSelf->main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 305; ++__Vi0) {
        vlSelf->main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom[__Vi0] = 0;
    }
    vlSelf->main_cpu__DOT__DataController_i1__DOT__s24 = 0;
    vlSelf->main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp = 0;
    vlSelf->main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__nq_temp = 0;
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory[__Vi0] = 0;
    }
    vlSelf->main_cpu__DOT__ControlLogic_i3__DOT__s1 = 0;
    for (int __Vi0 = 0; __Vi0 < 62; ++__Vi0) {
        vlSelf->main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 28; ++__Vi0) {
        vlSelf->main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom[__Vi0] = 0;
    }
    vlSelf->main_cpu__DOT__PcInSelector_i9__DOT__s2 = 0;
    vlSelf->main_cpu__DOT__PcInSelector_i9__DOT__s4 = 0;
    vlSelf->main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp = 0;
    vlSelf->main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__nq_temp = 0;
    vlSelf->__VdfgRegularize_hebeb780c_0_3 = 0;
    vlSelf->__VdfgRegularize_hebeb780c_0_4 = 0;
    vlSelf->__VdfgRegularize_hebeb780c_0_6 = 0;
    vlSelf->__VdfgRegularize_hebeb780c_0_8 = 0;
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp__0 = 0;
    vlSelf->__VstlDidInit = 0;
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__CLK__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__DrIO__0 = 0;
    vlSelf->__VicoDidInit = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp__1 = 0;
    vlSelf->__Vtrigprevexpr___TOP__main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp__1 = 0;
    vlSelf->__Vtrigprevexpr___TOP__main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp__1 = 0;
    vlSelf->__Vtrigprevexpr___TOP__CLKIO__0 = 0;
    vlSelf->__Vtrigprevexpr_h7a48d089__1 = 0;
    vlSelf->__Vtrigprevexpr_h805998fe__1 = 0;
    vlSelf->__VactDidInit = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
