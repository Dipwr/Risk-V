// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmain_cpu.h for the primary calling header

#include "Vmain_cpu__pch.h"

bool Vmain_cpu___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 2> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___trigger_anySet__ico\n"); );
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

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmain_cpu___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vmain_cpu___024root___eval_phase__ico(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_phase__ico\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__ico
        vlSelfRef.__VicoTriggered[0U] = (QData)((IData)(
                                                        (((vlSelfRef.DrIO 
                                                           != vlSelfRef.__Vtrigprevexpr___TOP__DrIO__0) 
                                                          << 1U) 
                                                         | ((IData)(vlSelfRef.CLK) 
                                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__CLK__0)))));
        vlSelfRef.__Vtrigprevexpr___TOP__CLK__0 = vlSelfRef.CLK;
        vlSelfRef.__Vtrigprevexpr___TOP__DrIO__0 = vlSelfRef.DrIO;
        if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.__VicoDidInit)))))) {
            vlSelfRef.__VicoDidInit = 1U;
            vlSelfRef.__VicoTriggered[0U] = (1ULL | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (2ULL | vlSelfRef.__VicoTriggered[0U]);
        }
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vmain_cpu___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = Vmain_cpu___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        {
            // Inlined CFunc: _eval_ico
            if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
                {
                    // Inlined CFunc: _ico_sequent__TOP__0
                    vlSelfRef.CLKIO = vlSelfRef.CLK;
                }
            }
            if ((2ULL & vlSelfRef.__VicoTriggered[0U])) {
                {
                    // Inlined CFunc: _ico_sequent__TOP__1
                    vlSelfRef.main_cpu__DOT__s11 = 
                        ((1U < (vlSelfRef.AddIO >> 0x00000012U))
                          ? vlSelfRef.DrIO : ((1U == 
                                               (vlSelfRef.AddIO 
                                                >> 0x00000012U))
                                               ? ((
                                                   (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory
                                                             [
                                                             (0x0003ffffU 
                                                              & ((IData)(3U) 
                                                                 + 
                                                                 (0x0003fffcU 
                                                                  & vlSelfRef.AddIO)))]) 
                                                     << 8U) 
                                                    | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory
                                                    [
                                                    (0x0003ffffU 
                                                     & ((IData)(2U) 
                                                        + 
                                                        (0x0003fffcU 
                                                         & vlSelfRef.AddIO)))]) 
                                                   << 0x00000010U) 
                                                  | (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory
                                                              [
                                                              (0x0003ffffU 
                                                               & ((IData)(1U) 
                                                                  + 
                                                                  (0x0003fffcU 
                                                                   & vlSelfRef.AddIO)))]) 
                                                      << 8U) 
                                                     | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory
                                                     [
                                                     (0x0003fffcU 
                                                      & vlSelfRef.AddIO)]))
                                               : (vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__data_rom_inst__DOT__my_rom
                                                  [
                                                  (0x000001ffU 
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
                                                                       >> 2U)))))))));
                    if ((0U == (3U & vlSelfRef.AddIO))) {
                        vlSelfRef.__VdfgRegularize_hebeb780c_0_1 
                            = (0x000000ffU & vlSelfRef.main_cpu__DOT__s11);
                        vlSelfRef.__VdfgRegularize_hebeb780c_0_2 
                            = (0x0000ffffU & vlSelfRef.main_cpu__DOT__s11);
                    } else if ((1U == (3U & vlSelfRef.AddIO))) {
                        vlSelfRef.__VdfgRegularize_hebeb780c_0_1 
                            = (0x000000ffU & (vlSelfRef.main_cpu__DOT__s11 
                                              >> 8U));
                        vlSelfRef.__VdfgRegularize_hebeb780c_0_2 
                            = (0x0000ffffU & (vlSelfRef.main_cpu__DOT__s11 
                                              >> 8U));
                    } else {
                        vlSelfRef.__VdfgRegularize_hebeb780c_0_1 
                            = (0x000000ffU & ((2U == 
                                               (3U 
                                                & vlSelfRef.AddIO))
                                               ? (vlSelfRef.main_cpu__DOT__s11 
                                                  >> 0x00000010U)
                                               : (vlSelfRef.main_cpu__DOT__s11 
                                                  >> 0x00000018U)));
                        vlSelfRef.__VdfgRegularize_hebeb780c_0_2 
                            = (0x0000ffffU & ((vlSelfRef.main_cpu__DOT__s11 
                                               >> 0x00000010U) 
                                              & (- (IData)(
                                                           (2U 
                                                            == 
                                                            (3U 
                                                             & vlSelfRef.AddIO))))));
                    }
                }
            }
        }
    }
    return (__VicoExecute);
}

bool Vmain_cpu___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

extern const VlUnpacked<CData/*3:0*/, 2048> Vmain_cpu__ConstPool__TABLE_h76366c4f_0;

void Vmain_cpu___024root___nba_sequent__TOP__0(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_sequent__TOP__0\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v0;
    __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v0 = 0;
    IData/*17:0*/ __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v0;
    __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v0 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v0;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v0 = 0;
    CData/*7:0*/ __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v1;
    __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v1 = 0;
    IData/*17:0*/ __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v1;
    __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v1 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v1;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v1 = 0;
    CData/*7:0*/ __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v2;
    __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v2 = 0;
    IData/*17:0*/ __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v2;
    __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v2 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v2;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v2 = 0;
    CData/*7:0*/ __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v3;
    __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v3 = 0;
    IData/*17:0*/ __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v3;
    __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v3 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v3;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v3 = 0;
    IData/*31:0*/ __VdlyVal__main_cpu__DOT__Registers_i5__DOT__regs__v0;
    __VdlyVal__main_cpu__DOT__Registers_i5__DOT__regs__v0 = 0;
    CData/*4:0*/ __VdlyDim0__main_cpu__DOT__Registers_i5__DOT__regs__v0;
    __VdlyDim0__main_cpu__DOT__Registers_i5__DOT__regs__v0 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__Registers_i5__DOT__regs__v0;
    __VdlySet__main_cpu__DOT__Registers_i5__DOT__regs__v0 = 0;
    // Body
    __VdlySet__main_cpu__DOT__Registers_i5__DOT__regs__v0 = 0U;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v0 = 0U;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v1 = 0U;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v2 = 0U;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v3 = 0U;
    if ((((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
          >> 1U) & (0U != (0x0000001fU & (vlSelfRef.main_cpu__DOT__s26 
                                          >> 7U))))) {
        __VdlyVal__main_cpu__DOT__Registers_i5__DOT__regs__v0 
            = ((0x00000010U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                ? (vlSelfRef.main_cpu__DOT__s21 & (
                                                   (- (IData)(
                                                              (1U 
                                                               & (~ 
                                                                  ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                                                   >> 3U))))) 
                                                   & (- (IData)(
                                                                (1U 
                                                                 & (~ 
                                                                    ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                                                     >> 2U)))))))
                : ((8U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                    ? ((4U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                        ? vlSelfRef.main_cpu__DOT__s20
                        : ((IData)(4U) + vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__pc))
                    : ((4U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                        ? ((0U == (3U & (vlSelfRef.main_cpu__DOT__s26 
                                         >> 0x0000000cU)))
                            ? ((((- (IData)((1U & ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_1) 
                                                   >> 7U)))) 
                                 & (- (IData)((1U & 
                                               (~ (vlSelfRef.main_cpu__DOT__s26 
                                                   >> 0x0000000eU)))))) 
                                << 8U) | (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_1))
                            : ((1U == (3U & (vlSelfRef.main_cpu__DOT__s26 
                                             >> 0x0000000cU)))
                                ? ((((- (IData)((1U 
                                                 & ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_2) 
                                                    >> 0x0000000fU)))) 
                                     & (- (IData)((1U 
                                                   & (~ 
                                                      (vlSelfRef.main_cpu__DOT__s26 
                                                       >> 0x0000000eU)))))) 
                                    << 0x00000010U) 
                                   | (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_2))
                                : vlSelfRef.main_cpu__DOT__s11))
                        : vlSelfRef.AddIO)));
        __VdlyDim0__main_cpu__DOT__Registers_i5__DOT__regs__v0 
            = (0x0000001fU & (vlSelfRef.main_cpu__DOT__s26 
                              >> 7U));
        __VdlySet__main_cpu__DOT__Registers_i5__DOT__regs__v0 = 1U;
    }
    if (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT____Vcellinp__ram__We) 
         & (IData)(vlSelfRef.main_cpu__DOT__s17))) {
        __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v0 
            = (0x000000ffU & vlSelfRef.DwIO);
        __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v0 
            = (0x0003fffcU & vlSelfRef.AddIO);
        __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v0 = 1U;
    }
    if (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT____Vcellinp__ram__We) 
         & ((IData)(vlSelfRef.main_cpu__DOT__s17) >> 1U))) {
        __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v1 
            = (0x000000ffU & (vlSelfRef.DwIO >> 8U));
        __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v1 
            = (0x0003ffffU & ((IData)(1U) + (0x0003fffcU 
                                             & vlSelfRef.AddIO)));
        __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v1 = 1U;
    }
    if (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT____Vcellinp__ram__We) 
         & ((IData)(vlSelfRef.main_cpu__DOT__s17) >> 2U))) {
        __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v2 
            = (0x000000ffU & (vlSelfRef.DwIO >> 0x10U));
        __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v2 
            = (0x0003ffffU & ((IData)(2U) + (0x0003fffcU 
                                             & vlSelfRef.AddIO)));
        __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v2 = 1U;
    }
    if (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT____Vcellinp__ram__We) 
         & ((IData)(vlSelfRef.main_cpu__DOT__s17) >> 3U))) {
        __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v3 
            = (vlSelfRef.DwIO >> 0x18U);
        __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v3 
            = (0x0003ffffU & ((IData)(3U) + (0x0003fffcU 
                                             & vlSelfRef.AddIO)));
        __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v3 = 1U;
    }
    if (__VdlySet__main_cpu__DOT__Registers_i5__DOT__regs__v0) {
        vlSelfRef.main_cpu__DOT__Registers_i5__DOT__regs[__VdlyDim0__main_cpu__DOT__Registers_i5__DOT__regs__v0] 
            = __VdlyVal__main_cpu__DOT__Registers_i5__DOT__regs__v0;
    }
    if (__VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v0) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory[__VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v0] 
            = __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v0;
    }
    if (__VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v1) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory[__VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v1] 
            = __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v1;
    }
    if (__VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v2) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory[__VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v2] 
            = __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v2;
    }
    if (__VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v3) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory[__VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v3] 
            = __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory__v3;
    }
    vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__pc 
        = (0xfffffffeU & ((0U == (3U & ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                        >> 6U))) ? vlSelfRef.main_cpu__DOT__s19
                           : ((1U == (3U & ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                            >> 6U)))
                               ? vlSelfRef.main_cpu__DOT__s21
                               : ((2U == (3U & ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                                >> 6U)))
                                   ? vlSelfRef.AddIO
                                   : ((1U & ((0U == (IData)(vlSelfRef.main_cpu__DOT__s30))
                                              ? (0U 
                                                 == vlSelfRef.main_cpu__DOT__ALU_i4__DOT__subtraction)
                                              : ((1U 
                                                  == (IData)(vlSelfRef.main_cpu__DOT__s30))
                                                  ? 
                                                 (0U 
                                                  != vlSelfRef.main_cpu__DOT__ALU_i4__DOT__subtraction)
                                                  : 
                                                 ((2U 
                                                   == (IData)(vlSelfRef.main_cpu__DOT__s30))
                                                   ? (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)
                                                   : 
                                                  (~ (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0))))))
                                       ? vlSelfRef.main_cpu__DOT__s21
                                       : vlSelfRef.main_cpu__DOT__s19)))));
    vlSelfRef.main_cpu__DOT__s19 = ((IData)(4U) + vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__pc);
    vlSelfRef.main_cpu__DOT__s26 = ((1U == (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__pc 
                                            >> 0x00000012U))
                                     ? (((((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory
                                                   [
                                                   (0x0003ffffU 
                                                    & ((IData)(3U) 
                                                       + 
                                                       (0x0003fffcU 
                                                        & vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__pc)))]) 
                                           << 8U) | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory
                                          [(0x0003ffffU 
                                            & ((IData)(2U) 
                                               + (0x0003fffcU 
                                                  & vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__pc)))]) 
                                         << 0x00000010U) 
                                        | (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory
                                                    [
                                                    (0x0003ffffU 
                                                     & ((IData)(1U) 
                                                        + 
                                                        (0x0003fffcU 
                                                         & vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__pc)))]) 
                                            << 8U) 
                                           | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory
                                           [(0x0003fffcU 
                                             & vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__pc)]))
                                     : (vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__ins_rom__DOT__my_rom
                                        [(0x000001ffU 
                                          & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__pc 
                                             >> 2U))] 
                                        & (- (IData)(
                                                     ((0x0130U 
                                                       >= 
                                                       (0x000001ffU 
                                                        & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__pc 
                                                           >> 2U))) 
                                                      & (0x0130U 
                                                         >= 
                                                         (0x000007ffU 
                                                          & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__pc 
                                                             >> 2U))))))));
    vlSelfRef.main_cpu__DOT__s30 = ((2U & (vlSelfRef.main_cpu__DOT__s26 
                                           >> 0x0000000dU)) 
                                    | (1U & (vlSelfRef.main_cpu__DOT__s26 
                                             >> 0x0000000cU)));
    vlSelfRef.main_cpu__DOT__s2 = (vlSelfRef.main_cpu__DOT__Registers_i5__DOT__regs
                                   [(0x0000001fU & 
                                     (vlSelfRef.main_cpu__DOT__s26 
                                      >> 0x0000000fU))] 
                                   & (- (IData)((0U 
                                                 != 
                                                 (0x0000001fU 
                                                  & (vlSelfRef.main_cpu__DOT__s26 
                                                     >> 0x0000000fU))))));
    vlSelfRef.main_cpu__DOT__s10 = (vlSelfRef.main_cpu__DOT__Registers_i5__DOT__regs
                                    [(0x0000001fU & 
                                      (vlSelfRef.main_cpu__DOT__s26 
                                       >> 0x00000014U))] 
                                    & (- (IData)((0U 
                                                  != 
                                                  (0x0000001fU 
                                                   & (vlSelfRef.main_cpu__DOT__s26 
                                                      >> 0x00000014U))))));
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1 
        = (vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom
           [(0x0000001fU & (vlSelfRef.main_cpu__DOT__s26 
                            >> 2U))] & (- (IData)((0x1bU 
                                                   >= 
                                                   (0x0000001fU 
                                                    & (vlSelfRef.main_cpu__DOT__s26 
                                                       >> 2U))))));
    vlSelfRef.DwIO = ((0U == (3U & (vlSelfRef.main_cpu__DOT__s26 
                                    >> 0x0000000cU)))
                       ? ((vlSelfRef.main_cpu__DOT__s10 
                           << 0x00000018U) | ((0x00ff0000U 
                                               & (vlSelfRef.main_cpu__DOT__s10 
                                                  << 0x00000010U)) 
                                              | ((0x0000ff00U 
                                                  & (vlSelfRef.main_cpu__DOT__s10 
                                                     << 8U)) 
                                                 | (0x000000ffU 
                                                    & vlSelfRef.main_cpu__DOT__s10))))
                       : ((1U == (3U & (vlSelfRef.main_cpu__DOT__s26 
                                        >> 0x0000000cU)))
                           ? ((vlSelfRef.main_cpu__DOT__s10 
                               << 0x00000010U) | (0x0000ffffU 
                                                  & vlSelfRef.main_cpu__DOT__s10))
                           : vlSelfRef.main_cpu__DOT__s10));
    vlSelfRef.main_cpu__DOT__s0 = (0x0000000fU & ((0x00001000U 
                                                   & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                                   ? 
                                                  ((0x56U 
                                                    >> 
                                                    (4U 
                                                     & (vlSelfRef.main_cpu__DOT__s26 
                                                        >> 0x0000000bU))) 
                                                   & (- (IData)(
                                                                (1U 
                                                                 & ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                                                    >> 0x0000000bU)))))
                                                   : Vmain_cpu__ConstPool__TABLE_h76366c4f_0
                                                  [
                                                  ((0x00000780U 
                                                    & ((0x10U 
                                                        >> 
                                                        ((IData)(
                                                                 ((0x0800U 
                                                                   == 
                                                                   (0x1800U 
                                                                    & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))) 
                                                                  & (vlSelfRef.main_cpu__DOT__s26 
                                                                     >> 0x0000001eU))) 
                                                         << 2U)) 
                                                       << 7U)) 
                                                   | ((0x00000078U 
                                                       & ((0x98U 
                                                           >> 
                                                           (4U 
                                                            & (vlSelfRef.main_cpu__DOT__s26 
                                                               >> 0x0000001cU))) 
                                                          << 3U)) 
                                                      | (7U 
                                                         & (vlSelfRef.main_cpu__DOT__s26 
                                                            >> 0x0000000cU))))]));
    vlSelfRef.main_cpu__DOT__s20 = ((0x00000400U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                     ? ((- (IData)(
                                                   (1U 
                                                    & (~ 
                                                       ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                                        >> 8U))))) 
                                        & (((((0x00000ffeU 
                                               & ((- (IData)(
                                                             (vlSelfRef.main_cpu__DOT__s26 
                                                              >> 0x0000001fU))) 
                                                  << 1U)) 
                                              | (vlSelfRef.main_cpu__DOT__s26 
                                                 >> 0x0000001fU)) 
                                             << 0x00000014U) 
                                            | ((((0x000001feU 
                                                  & (vlSelfRef.main_cpu__DOT__s26 
                                                     >> 0x0000000bU)) 
                                                 | (1U 
                                                    & (vlSelfRef.main_cpu__DOT__s26 
                                                       >> 0x00000014U))) 
                                                << 0x0000000bU) 
                                               | (0x000007feU 
                                                  & (vlSelfRef.main_cpu__DOT__s26 
                                                     >> 0x00000014U)))) 
                                           & (- (IData)(
                                                        (1U 
                                                         & (~ 
                                                            ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                                             >> 9U)))))))
                                     : ((0x00000200U 
                                         & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                         ? (((0x00000100U 
                                              & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                              ? (0x7ffff800U 
                                                 & (vlSelfRef.main_cpu__DOT__s26 
                                                    >> 1U))
                                              : ((0x7ffff000U 
                                                  & ((- (IData)(
                                                                (vlSelfRef.main_cpu__DOT__s26 
                                                                 >> 0x0000001fU))) 
                                                     << 0x0000000cU)) 
                                                 | ((((2U 
                                                       & (vlSelfRef.main_cpu__DOT__s26 
                                                          >> 0x0000001eU)) 
                                                      | (1U 
                                                         & (vlSelfRef.main_cpu__DOT__s26 
                                                            >> 7U))) 
                                                     << 0x0000000aU) 
                                                    | ((0x000003f0U 
                                                        & (vlSelfRef.main_cpu__DOT__s26 
                                                           >> 0x00000015U)) 
                                                       | (0x0000000fU 
                                                          & (vlSelfRef.main_cpu__DOT__s26 
                                                             >> 8U)))))) 
                                            << 1U) : 
                                        (((- (IData)(
                                                     (vlSelfRef.main_cpu__DOT__s26 
                                                      >> 0x0000001fU))) 
                                          << 0x0000000cU) 
                                         | ((0x00000fe0U 
                                             & (vlSelfRef.main_cpu__DOT__s26 
                                                >> 0x00000014U)) 
                                            | (0x0000001fU 
                                               & ((0x00000100U 
                                                   & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                                   ? 
                                                  (vlSelfRef.main_cpu__DOT__s26 
                                                   >> 7U)
                                                   : 
                                                  (vlSelfRef.main_cpu__DOT__s26 
                                                   >> 0x00000014U)))))));
}

void Vmain_cpu___024root___nba_sequent__TOP__1(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_sequent__TOP__1\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ main_cpu__DOT__s1;
    main_cpu__DOT__s1 = 0;
    CData/*0:0*/ main_cpu__DOT__ALU_i4__DOT__less_unsigned;
    main_cpu__DOT__ALU_i4__DOT__less_unsigned = 0;
    CData/*0:0*/ main_cpu__DOT__ALU_i4__DOT__less_signed;
    main_cpu__DOT__ALU_i4__DOT__less_signed = 0;
    // Body
    vlSelfRef.main_cpu__DOT__s21 = (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__pc 
                                    + vlSelfRef.main_cpu__DOT__s20);
    main_cpu__DOT__s1 = ((0x00000020U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                          ? vlSelfRef.main_cpu__DOT__s20
                          : vlSelfRef.main_cpu__DOT__s10);
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__subtraction 
        = (vlSelfRef.main_cpu__DOT__s2 - main_cpu__DOT__s1);
    main_cpu__DOT__ALU_i4__DOT__less_unsigned = (vlSelfRef.main_cpu__DOT__s2 
                                                 < main_cpu__DOT__s1);
    main_cpu__DOT__ALU_i4__DOT__less_signed = VL_LTS_III(32, vlSelfRef.main_cpu__DOT__s2, main_cpu__DOT__s1);
    vlSelfRef.__VdfgRegularize_hebeb780c_0_0 = ((6U 
                                                 == (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                 ? (IData)(main_cpu__DOT__ALU_i4__DOT__less_signed)
                                                 : (IData)(main_cpu__DOT__ALU_i4__DOT__less_unsigned));
    vlSelfRef.AddIO = ((8U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                        ? ((- (IData)((1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__s0) 
                                                >> 1U))))) 
                           & (((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                ? VL_SHIFTRS_III(32,32,5, vlSelfRef.main_cpu__DOT__s2, 
                                                 (0x0000001fU 
                                                  & main_cpu__DOT__s1))
                                : (vlSelfRef.main_cpu__DOT__s2 
                                   >> (0x0000001fU 
                                       & main_cpu__DOT__s1))) 
                              & (- (IData)((1U & (~ 
                                                  ((IData)(vlSelfRef.main_cpu__DOT__s0) 
                                                   >> 2U)))))))
                        : ((4U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                            ? ((2U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                ? ((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                    ? (vlSelfRef.main_cpu__DOT__s2 
                                       << (0x0000001fU 
                                           & main_cpu__DOT__s1))
                                    : (IData)(main_cpu__DOT__ALU_i4__DOT__less_signed))
                                : ((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                    ? (IData)(main_cpu__DOT__ALU_i4__DOT__less_unsigned)
                                    : (main_cpu__DOT__s1 
                                       ^ vlSelfRef.main_cpu__DOT__s2)))
                            : ((2U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                ? ((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                    ? (main_cpu__DOT__s1 
                                       | vlSelfRef.main_cpu__DOT__s2)
                                    : (main_cpu__DOT__s1 
                                       & vlSelfRef.main_cpu__DOT__s2))
                                : ((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                    ? vlSelfRef.main_cpu__DOT__ALU_i4__DOT__subtraction
                                    : (main_cpu__DOT__s1 
                                       + vlSelfRef.main_cpu__DOT__s2)))));
    vlSelfRef.ReIO = (IData)(((4U == (0x001cU & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))) 
                              & (1U < (vlSelfRef.AddIO 
                                       >> 0x00000012U))));
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT____Vcellinp__ram__We 
        = ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
           & (1U == (vlSelfRef.AddIO >> 0x00000012U)));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_3 = (0x0000000fU 
                                                & ((0U 
                                                    == 
                                                    (3U 
                                                     & (vlSelfRef.main_cpu__DOT__s26 
                                                        >> 0x0000000cU)))
                                                    ? 
                                                   ((IData)(1U) 
                                                    << 
                                                    (3U 
                                                     & vlSelfRef.AddIO))
                                                    : 
                                                   ((0x8c63U 
                                                     >> 
                                                     (0x0000000cU 
                                                      & (vlSelfRef.AddIO 
                                                         << 2U))) 
                                                    | (- (IData)(
                                                                 (1U 
                                                                  != 
                                                                  (3U 
                                                                   & (vlSelfRef.main_cpu__DOT__s26 
                                                                      >> 0x0000000cU))))))));
    vlSelfRef.main_cpu__DOT__s11 = ((1U < (vlSelfRef.AddIO 
                                           >> 0x00000012U))
                                     ? vlSelfRef.DrIO
                                     : ((1U == (vlSelfRef.AddIO 
                                                >> 0x00000012U))
                                         ? (((((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory
                                                       [
                                                       (0x0003ffffU 
                                                        & ((IData)(3U) 
                                                           + 
                                                           (0x0003fffcU 
                                                            & vlSelfRef.AddIO)))]) 
                                               << 8U) 
                                              | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory
                                              [(0x0003ffffU 
                                                & ((IData)(2U) 
                                                   + 
                                                   (0x0003fffcU 
                                                    & vlSelfRef.AddIO)))]) 
                                             << 0x00000010U) 
                                            | (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory
                                                        [
                                                        (0x0003ffffU 
                                                         & ((IData)(1U) 
                                                            + 
                                                            (0x0003fffcU 
                                                             & vlSelfRef.AddIO)))]) 
                                                << 8U) 
                                               | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__ram__DOT__memory
                                               [(0x0003fffcU 
                                                 & vlSelfRef.AddIO)]))
                                         : (vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__data_rom_inst__DOT__my_rom
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
                                                                 >> 2U)))))))));
    vlSelfRef.main_cpu__DOT__s17 = (((1U == (3U & (vlSelfRef.main_cpu__DOT__s26 
                                                   >> 0x0000000cU))) 
                                     << 5U) | (((0U 
                                                 == 
                                                 (3U 
                                                  & (vlSelfRef.main_cpu__DOT__s26 
                                                     >> 0x0000000cU))) 
                                                << 4U) 
                                               | (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3)));
    vlSelfRef.WeIO = ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3) 
                      & (- (IData)(((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                    & (1U < (vlSelfRef.AddIO 
                                             >> 0x00000012U))))));
    if ((0U == (3U & vlSelfRef.AddIO))) {
        vlSelfRef.__VdfgRegularize_hebeb780c_0_1 = 
            (0x000000ffU & vlSelfRef.main_cpu__DOT__s11);
        vlSelfRef.__VdfgRegularize_hebeb780c_0_2 = 
            (0x0000ffffU & vlSelfRef.main_cpu__DOT__s11);
    } else if ((1U == (3U & vlSelfRef.AddIO))) {
        vlSelfRef.__VdfgRegularize_hebeb780c_0_1 = 
            (0x000000ffU & (vlSelfRef.main_cpu__DOT__s11 
                            >> 8U));
        vlSelfRef.__VdfgRegularize_hebeb780c_0_2 = 
            (0x0000ffffU & (vlSelfRef.main_cpu__DOT__s11 
                            >> 8U));
    } else {
        vlSelfRef.__VdfgRegularize_hebeb780c_0_1 = 
            (0x000000ffU & ((2U == (3U & vlSelfRef.AddIO))
                             ? (vlSelfRef.main_cpu__DOT__s11 
                                >> 0x00000010U) : (vlSelfRef.main_cpu__DOT__s11 
                                                   >> 0x00000018U)));
        vlSelfRef.__VdfgRegularize_hebeb780c_0_2 = 
            (0x0000ffffU & ((vlSelfRef.main_cpu__DOT__s11 
                             >> 0x00000010U) & (- (IData)(
                                                          (2U 
                                                           == 
                                                           (3U 
                                                            & vlSelfRef.AddIO))))));
    }
}

void Vmain_cpu___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmain_cpu___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vmain_cpu___024root___eval_phase__act(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_phase__act\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__act
        vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                        ((IData)(vlSelfRef.CLK) 
                                                         & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__CLK__1)))));
        vlSelfRef.__Vtrigprevexpr___TOP__CLK__1 = vlSelfRef.CLK;
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vmain_cpu___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vmain_cpu___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vmain_cpu___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vmain_cpu___024root___eval_phase__nba(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_phase__nba\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vmain_cpu___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        {
            // Inlined CFunc: _eval_nba
            if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
                Vmain_cpu___024root___nba_sequent__TOP__0(vlSelf);
                Vmain_cpu___024root___nba_sequent__TOP__1(vlSelf);
            }
        }
        Vmain_cpu___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vmain_cpu___024root___eval(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VicoIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vmain_cpu___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("main_cpu.v", 1723, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 10000 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        vlSelfRef.__VicoPhaseResult = Vmain_cpu___024root___eval_phase__ico(vlSelf);
    } while (vlSelfRef.__VicoPhaseResult);
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vmain_cpu___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("main_cpu.v", 1723, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vmain_cpu___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("main_cpu.v", 1723, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vmain_cpu___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vmain_cpu___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vmain_cpu___024root___eval_debug_assertions(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_debug_assertions\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.CLK & 0xfeU)))) {
        Verilated::overWidthError("CLK");
    }
}
#endif  // VL_DEBUG
