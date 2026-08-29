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
                    vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp 
                        = (1U & (~ ((~ (IData)(vlSelfRef.CLK)) 
                                    | (IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__nq_temp))));
                    vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp 
                        = (1U & (~ ((~ (IData)(vlSelfRef.CLK)) 
                                    | (IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__nq_temp))));
                    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp 
                        = (1U & (~ ((~ (IData)(vlSelfRef.CLK)) 
                                    | (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__nq_temp))));
                    vlSelfRef.CLKIO = ((~ (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp)) 
                                       & (IData)(vlSelfRef.CLK));
                }
            }
            if ((2ULL & vlSelfRef.__VicoTriggered[0U])) {
                {
                    // Inlined CFunc: _ico_sequent__TOP__1
                    vlSelfRef.main_cpu__DOT__s12 = 
                        ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s12)
                          ? vlSelfRef.DrIO : ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3)
                                               ? (vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom
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
                                                                       >> 2U)))))))
                                               : ((
                                                   (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory
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

void Vmain_cpu___024root___nba_sequent__TOP__1(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_sequent__TOP__1\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VdlyVal__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0;
    __VdlyVal__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0 = 0;
    CData/*4:0*/ __VdlyDim0__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0;
    __VdlyDim0__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0;
    __VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0 = 0;
    // Body
    __VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0 = 0U;
    if ((((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
          >> 1U) & (0U != (0x0000001fU & (vlSelfRef.main_cpu__DOT__s27 
                                          >> 7U))))) {
        __VdlyVal__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0 
            = ((0x00000010U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                ? ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_8) 
                   & ((- (IData)((1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                           >> 3U))))) 
                      & (- (IData)((1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                             >> 2U)))))))
                : ((8U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                    ? ((4U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                        ? vlSelfRef.main_cpu__DOT__s21
                        : ((IData)(4U) + vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state))
                    : ((4U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                        ? ((IData)(vlSelfRef.main_cpu__DOT__DataController_i1__DOT__s24)
                            ? ((2U & vlSelfRef.AddIO)
                                ? ((1U & vlSelfRef.AddIO)
                                    ? (((1U & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6))
                                         ? (vlSelfRef.main_cpu__DOT__s12 
                                            >> 0x00000018U)
                                         : (((- (IData)(
                                                        (vlSelfRef.main_cpu__DOT__s12 
                                                         >> 0x0000001fU))) 
                                             << 8U) 
                                            | (vlSelfRef.main_cpu__DOT__s12 
                                               >> 0x00000018U))) 
                                       & (- (IData)(
                                                    (1U 
                                                     & (~ 
                                                        ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6) 
                                                         >> 1U))))))
                                    : ((2U & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6))
                                        ? ((1U & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6))
                                            ? (vlSelfRef.main_cpu__DOT__s12 
                                               >> 0x00000010U)
                                            : (((- (IData)(
                                                           (vlSelfRef.main_cpu__DOT__s12 
                                                            >> 0x0000001fU))) 
                                                << 0x00000010U) 
                                               | (vlSelfRef.main_cpu__DOT__s12 
                                                  >> 0x00000010U)))
                                        : ((((- (IData)(
                                                        (1U 
                                                         & (vlSelfRef.main_cpu__DOT__s12 
                                                            >> 0x00000017U)))) 
                                             & (- (IData)(
                                                          (1U 
                                                           & (~ (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6)))))) 
                                            << 8U) 
                                           | (0x000000ffU 
                                              & (vlSelfRef.main_cpu__DOT__s12 
                                                 >> 0x00000010U)))))
                                : ((1U & vlSelfRef.AddIO)
                                    ? ((2U & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6))
                                        ? ((((- (IData)(
                                                        (1U 
                                                         & (vlSelfRef.main_cpu__DOT__s12 
                                                            >> 0x00000017U)))) 
                                             & (- (IData)(
                                                          (1U 
                                                           & (~ (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6)))))) 
                                            << 0x00000010U) 
                                           | (0x0000ffffU 
                                              & (vlSelfRef.main_cpu__DOT__s12 
                                                 >> 8U)))
                                        : ((((- (IData)(
                                                        (1U 
                                                         & (vlSelfRef.main_cpu__DOT__s12 
                                                            >> 0x0000000fU)))) 
                                             & (- (IData)(
                                                          (1U 
                                                           & (~ (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6)))))) 
                                            << 8U) 
                                           | (0x000000ffU 
                                              & (vlSelfRef.main_cpu__DOT__s12 
                                                 >> 8U))))
                                    : ((((2U & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6))
                                          ? ((0x00ffff00U 
                                              & (((- (IData)(
                                                             (1U 
                                                              & (vlSelfRef.main_cpu__DOT__s12 
                                                                 >> 0x0000000fU)))) 
                                                  & (- (IData)(
                                                               (1U 
                                                                & (~ (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6)))))) 
                                                 << 8U)) 
                                             | (0x000000ffU 
                                                & (vlSelfRef.main_cpu__DOT__s12 
                                                   >> 8U)))
                                          : ((- (IData)(
                                                        (1U 
                                                         & (vlSelfRef.main_cpu__DOT__s12 
                                                            >> 7U)))) 
                                             & (- (IData)(
                                                          (1U 
                                                           & (~ (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6))))))) 
                                        << 8U) | (0x000000ffU 
                                                  & vlSelfRef.main_cpu__DOT__s12))))
                            : vlSelfRef.main_cpu__DOT__s12)
                        : vlSelfRef.AddIO)));
        __VdlyDim0__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0 
            = (0x0000001fU & (vlSelfRef.main_cpu__DOT__s27 
                              >> 7U));
        __VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0 = 1U;
    }
    if (__VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0) {
        vlSelfRef.main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory[__VdlyDim0__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0] 
            = __VdlyVal__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0;
    }
}

void Vmain_cpu___024root___nba_comb__TOP__0(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_comb__TOP__0\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*5:0*/ main_cpu__DOT__ControlLogic_i3__DOT__s8;
    main_cpu__DOT__ControlLogic_i3__DOT__s8 = 0;
    // Body
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
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1 
        = (vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom
           [(0x0000001fU & (vlSelfRef.main_cpu__DOT__s27 
                            >> 2U))] & (- (IData)((0x1bU 
                                                   >= 
                                                   (0x0000001fU 
                                                    & (vlSelfRef.main_cpu__DOT__s27 
                                                       >> 2U))))));
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
}

void Vmain_cpu___024root___nba_comb__TOP__1(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_comb__TOP__1\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ main_cpu__DOT__s1;
    main_cpu__DOT__s1 = 0;
    IData/*31:0*/ main_cpu__DOT__s2;
    main_cpu__DOT__s2 = 0;
    CData/*3:0*/ main_cpu__DOT__DataController_i1__DOT__s26;
    main_cpu__DOT__DataController_i1__DOT__s26 = 0;
    CData/*0:0*/ main_cpu__DOT__ALU_i4__DOT__lt_u;
    main_cpu__DOT__ALU_i4__DOT__lt_u = 0;
    CData/*0:0*/ main_cpu__DOT__ALU_i4__DOT__lt_s;
    main_cpu__DOT__ALU_i4__DOT__lt_s = 0;
    QData/*63:0*/ main_cpu__DOT__ALU_i4__DOT__mul_uu;
    main_cpu__DOT__ALU_i4__DOT__mul_uu = 0;
    CData/*0:0*/ main_cpu__DOT__ALU_i4__DOT__is_div_overflow;
    main_cpu__DOT__ALU_i4__DOT__is_div_overflow = 0;
    // Body
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
    main_cpu__DOT__s1 = ((0x00000020U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                          ? vlSelfRef.main_cpu__DOT__s21
                          : vlSelfRef.main_cpu__DOT__s11);
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
    vlSelfRef.DwIO = ((((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s8) 
                        << 0x00000018U) | ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s7) 
                                           << 0x00000010U)) 
                      | (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s6) 
                          << 8U) | (0x000000ffU & vlSelfRef.main_cpu__DOT__s11)));
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
    main_cpu__DOT__DataController_i1__DOT__s26 = (0x0000000fU 
                                                  & ((((((IData)(
                                                                 ((2U 
                                                                   == 
                                                                   (3U 
                                                                    & vlSelfRef.AddIO)) 
                                                                  & (0x00001000U 
                                                                     == 
                                                                     (0x00003000U 
                                                                      & vlSelfRef.main_cpu__DOT__s27)))) 
                                                         | (3U 
                                                            == 
                                                            (3U 
                                                             & vlSelfRef.AddIO))) 
                                                        << 3U) 
                                                       | (((IData)(
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
                                                      | ((((IData)(
                                                                   ((0U 
                                                                     == 
                                                                     (3U 
                                                                      & vlSelfRef.AddIO)) 
                                                                    & (0x00001000U 
                                                                       == 
                                                                       (0x00003000U 
                                                                        & vlSelfRef.main_cpu__DOT__s27)))) 
                                                           | (1U 
                                                              == 
                                                              (3U 
                                                               & vlSelfRef.AddIO))) 
                                                          << 1U) 
                                                         | (0U 
                                                            == 
                                                            (3U 
                                                             & vlSelfRef.AddIO)))) 
                                                     | (- (IData)(
                                                                  (1U 
                                                                   & (~ (IData)(vlSelfRef.main_cpu__DOT__DataController_i1__DOT__s24)))))));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_3 = (IData)(
                                                       (0x00040000U 
                                                        != 
                                                        (0xfffc0000U 
                                                         & vlSelfRef.AddIO)));
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s0 
        = ((- (IData)((1U & ((~ (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3)) 
                             & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))))) 
           & (IData)(main_cpu__DOT__DataController_i1__DOT__s26));
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s12 
        = ((0U != (vlSelfRef.AddIO >> 0x00000012U)) 
           & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3));
    vlSelfRef.ReIO = (IData)(((4U == (0x001cU & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))) 
                              & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s12)));
    vlSelfRef.WeIO = ((- (IData)(((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                  & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s12)))) 
                      & (IData)(main_cpu__DOT__DataController_i1__DOT__s26));
    vlSelfRef.main_cpu__DOT__s12 = ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s12)
                                     ? vlSelfRef.DrIO
                                     : ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3)
                                         ? (vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom
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
                                         : (((((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory
                                                       [
                                                       (0x0000ffffU 
                                                        & (vlSelfRef.AddIO 
                                                           >> 2U))]) 
                                               << 8U) 
                                              | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory
                                              [(0x0000ffffU 
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
                                               [(0x0000ffffU 
                                                 & (vlSelfRef.AddIO 
                                                    >> 2U))]))));
}

void Vmain_cpu___024root___eval_nba(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_nba\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((8ULL & vlSelfRef.__VnbaTriggered[0U])) {
        {
            // Inlined CFunc: _nba_sequent__TOP__0
            CData/*7:0*/ __Vinline_0__nba_sequent__TOP__0___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0;
            __Vinline_0__nba_sequent__TOP__0___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 0;
            SData/*15:0*/ __Vinline_0__nba_sequent__TOP__0___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0;
            __Vinline_0__nba_sequent__TOP__0___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 0;
            CData/*0:0*/ __Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0;
            __Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 0;
            CData/*7:0*/ __Vinline_0__nba_sequent__TOP__0___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0;
            __Vinline_0__nba_sequent__TOP__0___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 0;
            SData/*15:0*/ __Vinline_0__nba_sequent__TOP__0___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0;
            __Vinline_0__nba_sequent__TOP__0___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 0;
            CData/*0:0*/ __Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0;
            __Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 0;
            CData/*7:0*/ __Vinline_0__nba_sequent__TOP__0___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0;
            __Vinline_0__nba_sequent__TOP__0___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 0;
            SData/*15:0*/ __Vinline_0__nba_sequent__TOP__0___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0;
            __Vinline_0__nba_sequent__TOP__0___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 0;
            CData/*0:0*/ __Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0;
            __Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 0;
            CData/*7:0*/ __Vinline_0__nba_sequent__TOP__0___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0;
            __Vinline_0__nba_sequent__TOP__0___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 0;
            SData/*15:0*/ __Vinline_0__nba_sequent__TOP__0___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0;
            __Vinline_0__nba_sequent__TOP__0___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 0;
            CData/*0:0*/ __Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0;
            __Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 0;
            __Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 0U;
            __Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 0U;
            __Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 0U;
            __Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 0U;
            if ((4U & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s0))) {
                __Vinline_0__nba_sequent__TOP__0___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 
                    = vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s7;
                __Vinline_0__nba_sequent__TOP__0___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 
                    = (0x0000ffffU & (vlSelfRef.AddIO 
                                      >> 2U));
                __Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 1U;
            }
            if ((8U & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s0))) {
                __Vinline_0__nba_sequent__TOP__0___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 
                    = vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s8;
                __Vinline_0__nba_sequent__TOP__0___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 
                    = (0x0000ffffU & (vlSelfRef.AddIO 
                                      >> 2U));
                __Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 1U;
            }
            if ((2U & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s0))) {
                __Vinline_0__nba_sequent__TOP__0___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 
                    = vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s6;
                __Vinline_0__nba_sequent__TOP__0___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 
                    = (0x0000ffffU & (vlSelfRef.AddIO 
                                      >> 2U));
                __Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 1U;
            }
            if ((1U & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s0))) {
                __Vinline_0__nba_sequent__TOP__0___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 
                    = (0x000000ffU & vlSelfRef.main_cpu__DOT__s11);
                __Vinline_0__nba_sequent__TOP__0___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 
                    = (0x0000ffffU & (vlSelfRef.AddIO 
                                      >> 2U));
                __Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 1U;
            }
            if (__Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0) {
                vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory[__Vinline_0__nba_sequent__TOP__0___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0] 
                    = __Vinline_0__nba_sequent__TOP__0___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0;
            }
            if (__Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0) {
                vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory[__Vinline_0__nba_sequent__TOP__0___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0] 
                    = __Vinline_0__nba_sequent__TOP__0___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0;
            }
            if (__Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0) {
                vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory[__Vinline_0__nba_sequent__TOP__0___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0] 
                    = __Vinline_0__nba_sequent__TOP__0___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0;
            }
            if (__Vinline_0__nba_sequent__TOP__0___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0) {
                vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory[__Vinline_0__nba_sequent__TOP__0___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0] 
                    = __Vinline_0__nba_sequent__TOP__0___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0;
            }
        }
    }
    if ((0x0000000000000010ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vmain_cpu___024root___nba_sequent__TOP__1(vlSelf);
    }
    if ((0x0000000000000020ULL & vlSelfRef.__VnbaTriggered[0U])) {
        {
            // Inlined CFunc: _nba_sequent__TOP__2
            vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state 
                = (((0x00000080U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                     ? ((0x00000040U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                         ? ((1U & ((0x00004000U & vlSelfRef.main_cpu__DOT__s27)
                                    ? ((0x00001000U 
                                        & vlSelfRef.main_cpu__DOT__s27)
                                        ? (~ (IData)(vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s4))
                                        : (IData)(vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s4))
                                    : ((0x00001000U 
                                        & vlSelfRef.main_cpu__DOT__s27)
                                        ? (~ (IData)(vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s2))
                                        : (IData)(vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s2))))
                             ? (IData)((vlSelfRef.__VdfgRegularize_hebeb780c_0_8 
                                        >> 1U)) : (IData)(
                                                          (vlSelfRef.__VdfgRegularize_hebeb780c_0_4 
                                                           >> 1U)))
                         : (vlSelfRef.AddIO >> 1U))
                     : ((0x00000040U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                         ? (IData)((vlSelfRef.__VdfgRegularize_hebeb780c_0_8 
                                    >> 1U)) : (IData)(
                                                      (vlSelfRef.__VdfgRegularize_hebeb780c_0_4 
                                                       >> 1U)))) 
                   << 1U);
            vlSelfRef.__VdfgRegularize_hebeb780c_0_4 
                = (0x00000001ffffffffULL & (4ULL + (QData)((IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state))));
        }
    }
    if ((0x0000000000000028ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vmain_cpu___024root___nba_comb__TOP__0(vlSelf);
    }
    if ((0x0000000000000038ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vmain_cpu___024root___nba_comb__TOP__1(vlSelf);
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
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__act
        CData/*0:0*/ __Vinline_0__eval_triggers_vec__act___Vtrigprevexpr_h7a48d089__0;
        __Vinline_0__eval_triggers_vec__act___Vtrigprevexpr_h7a48d089__0 = 0;
        CData/*0:0*/ __Vinline_0__eval_triggers_vec__act___Vtrigprevexpr_h805998fe__0;
        __Vinline_0__eval_triggers_vec__act___Vtrigprevexpr_h805998fe__0 = 0;
        __Vinline_0__eval_triggers_vec__act___Vtrigprevexpr_h7a48d089__0 
            = ((~ (IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp)) 
               & (IData)(vlSelfRef.CLK));
        __Vinline_0__eval_triggers_vec__act___Vtrigprevexpr_h805998fe__0 
            = ((~ (IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp)) 
               & (IData)(vlSelfRef.CLK));
        vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                        ((((__Vinline_0__eval_triggers_vec__act___Vtrigprevexpr_h805998fe__0 
                                                            & (~ (IData)(vlSelfRef.__Vtrigprevexpr_h805998fe__1))) 
                                                           << 5U) 
                                                          | ((__Vinline_0__eval_triggers_vec__act___Vtrigprevexpr_h7a48d089__0 
                                                              & (~ (IData)(vlSelfRef.__Vtrigprevexpr_h7a48d089__1))) 
                                                             << 4U)) 
                                                         | (((((IData)(vlSelfRef.CLKIO) 
                                                               & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__CLKIO__0))) 
                                                              << 3U) 
                                                             | (((IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp) 
                                                                 != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp__1)) 
                                                                << 2U)) 
                                                            | ((((IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp) 
                                                                 != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp__1)) 
                                                                << 1U) 
                                                               | ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp) 
                                                                  != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp__1)))))));
        vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp__1 
            = vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp;
        vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp__1 
            = vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp;
        vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp__1 
            = vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp;
        vlSelfRef.__Vtrigprevexpr___TOP__CLKIO__0 = vlSelfRef.CLKIO;
        vlSelfRef.__Vtrigprevexpr_h7a48d089__1 = __Vinline_0__eval_triggers_vec__act___Vtrigprevexpr_h7a48d089__0;
        vlSelfRef.__Vtrigprevexpr_h805998fe__1 = __Vinline_0__eval_triggers_vec__act___Vtrigprevexpr_h805998fe__0;
        if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.__VactDidInit)))))) {
            vlSelfRef.__VactDidInit = 1U;
            vlSelfRef.__VactTriggered[0U] = (1ULL | vlSelfRef.__VactTriggered[0U]);
            vlSelfRef.__VactTriggered[0U] = (2ULL | vlSelfRef.__VactTriggered[0U]);
            vlSelfRef.__VactTriggered[0U] = (4ULL | vlSelfRef.__VactTriggered[0U]);
        }
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vmain_cpu___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vmain_cpu___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vmain_cpu___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        {
            // Inlined CFunc: _eval_act
            if ((2ULL & vlSelfRef.__VactTriggered[0U])) {
                {
                    // Inlined CFunc: _act_sequent__TOP__0
                    vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__nq_temp 
                        = (1U & (~ (IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp)));
                    vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp 
                        = (1U & (~ ((~ (IData)(vlSelfRef.CLK)) 
                                    | (IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__nq_temp))));
                }
            }
            if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
                {
                    // Inlined CFunc: _act_sequent__TOP__1
                    vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__nq_temp 
                        = (1U & (~ (IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp)));
                    vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp 
                        = (1U & (~ ((~ (IData)(vlSelfRef.CLK)) 
                                    | (IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__nq_temp))));
                }
            }
            if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
                {
                    // Inlined CFunc: _act_sequent__TOP__2
                    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__nq_temp 
                        = (1U & (~ (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp)));
                    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp 
                        = (1U & (~ ((~ (IData)(vlSelfRef.CLK)) 
                                    | (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__nq_temp))));
                    vlSelfRef.CLKIO = ((~ (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp)) 
                                       & (IData)(vlSelfRef.CLK));
                }
            }
        }
    }
    return (__VactExecute);
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
        Vmain_cpu___024root___eval_nba(vlSelf);
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
            VL_FATAL_MT("main_cpu.v", 2003, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 10000 tries");
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
            VL_FATAL_MT("main_cpu.v", 2003, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vmain_cpu___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("main_cpu.v", 2003, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
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
