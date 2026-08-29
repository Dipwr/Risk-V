// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmain_cpu.h for the primary calling header

#include "Vmain_cpu__pch.h"

void Vmain_cpu___024root___eval_triggers_vec__ico(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_triggers_vec__ico\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
}

bool Vmain_cpu___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
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
    } while ((1U > n));
    return (0U);
}

void Vmain_cpu___024root___ico_sequent__TOP__0(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___ico_sequent__TOP__0\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.main_cpu__DOT__s12 = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_1)
                                     ? ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0)
                                         ? ((0x0130U 
                                             < (0x000007ffU 
                                                & (vlSelfRef.main_cpu__DOT__s3 
                                                   >> 2U)))
                                             ? 0U : 
                                            ((0x0130U 
                                              >= (0x000001ffU 
                                                  & (vlSelfRef.main_cpu__DOT__s3 
                                                     >> 2U)))
                                              ? vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom
                                             [(0x000001ffU 
                                               & (vlSelfRef.main_cpu__DOT__s3 
                                                  >> 2U))]
                                              : 0U))
                                         : (((vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory
                                              [(0x0000ffffU 
                                                & (vlSelfRef.main_cpu__DOT__s3 
                                                   >> 2U))] 
                                              << 0x00000018U) 
                                             | (vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory
                                                [(0x0000ffffU 
                                                  & (vlSelfRef.main_cpu__DOT__s3 
                                                     >> 2U))] 
                                                << 0x00000010U)) 
                                            | ((vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory
                                                [(0x0000ffffU 
                                                  & (vlSelfRef.main_cpu__DOT__s3 
                                                     >> 2U))] 
                                                << 8U) 
                                               | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory
                                               [(0x0000ffffU 
                                                 & (vlSelfRef.main_cpu__DOT__s3 
                                                    >> 2U))])))
                                     : vlSelfRef.DrIO);
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s30 
        = (1U & (~ ((IData)(vlSelfRef.CLK) | (IData)(vlSelfRef.main_cpu__DOT__s5))));
    vlSelfRef.main_cpu__DOT__s6 = ((0x00000010U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                    ? ((8U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                        ? 0U : ((4U 
                                                 & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                                 ? 0U
                                                 : vlSelfRef.main_cpu__DOT__s22))
                                    : ((8U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                        ? ((4U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                            ? vlSelfRef.main_cpu__DOT__s21
                                            : ((IData)(4U) 
                                               + vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state))
                                        : ((4U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                            ? ((IData)(vlSelfRef.main_cpu__DOT__DataController_i1__DOT__s24)
                                                ? (
                                                   (2U 
                                                    & vlSelfRef.main_cpu__DOT__s3)
                                                    ? 
                                                   ((1U 
                                                     & vlSelfRef.main_cpu__DOT__s3)
                                                     ? 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                      ? 0U
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                       ? 
                                                      VL_SHIFTR_III(32,32,32, vlSelfRef.main_cpu__DOT__s12, 0x00000018U)
                                                       : 
                                                      (((- (IData)(
                                                                   (vlSelfRef.main_cpu__DOT__s12 
                                                                    >> 0x0000001fU))) 
                                                        << 8U) 
                                                       | (vlSelfRef.main_cpu__DOT__s12 
                                                          >> 0x00000018U))))
                                                     : 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                       ? 
                                                      VL_SHIFTR_III(32,32,32, vlSelfRef.main_cpu__DOT__s12, 0x00000010U)
                                                       : 
                                                      (((- (IData)(
                                                                   (vlSelfRef.main_cpu__DOT__s12 
                                                                    >> 0x0000001fU))) 
                                                        << 0x00000010U) 
                                                       | (vlSelfRef.main_cpu__DOT__s12 
                                                          >> 0x00000010U)))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                       ? 
                                                      (0x000000ffU 
                                                       & (vlSelfRef.main_cpu__DOT__s12 
                                                          >> 0x00000010U))
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (vlSelfRef.main_cpu__DOT__s12 
                                                                       >> 0x00000017U)))) 
                                                        << 8U) 
                                                       | (0x000000ffU 
                                                          & (vlSelfRef.main_cpu__DOT__s12 
                                                             >> 0x00000010U))))))
                                                    : 
                                                   ((1U 
                                                     & vlSelfRef.main_cpu__DOT__s3)
                                                     ? 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                       ? 
                                                      (0x0000ffffU 
                                                       & (vlSelfRef.main_cpu__DOT__s12 
                                                          >> 8U))
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (vlSelfRef.main_cpu__DOT__s12 
                                                                       >> 0x00000017U)))) 
                                                        << 0x00000010U) 
                                                       | (0x0000ffffU 
                                                          & (vlSelfRef.main_cpu__DOT__s12 
                                                             >> 8U))))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                       ? 
                                                      (0x000000ffU 
                                                       & (vlSelfRef.main_cpu__DOT__s12 
                                                          >> 8U))
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (vlSelfRef.main_cpu__DOT__s12 
                                                                       >> 0x0000000fU)))) 
                                                        << 8U) 
                                                       | (0x000000ffU 
                                                          & (vlSelfRef.main_cpu__DOT__s12 
                                                             >> 8U)))))
                                                     : 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                       ? 
                                                      (0x0000ffffU 
                                                       & vlSelfRef.main_cpu__DOT__s12)
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (vlSelfRef.main_cpu__DOT__s12 
                                                                       >> 0x0000000fU)))) 
                                                        << 0x00000010U) 
                                                       | (0x0000ffffU 
                                                          & vlSelfRef.main_cpu__DOT__s12)))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                       ? 
                                                      (0x000000ffU 
                                                       & vlSelfRef.main_cpu__DOT__s12)
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (vlSelfRef.main_cpu__DOT__s12 
                                                                       >> 7U)))) 
                                                        << 8U) 
                                                       | (0x000000ffU 
                                                          & vlSelfRef.main_cpu__DOT__s12))))))
                                                : vlSelfRef.main_cpu__DOT__s12)
                                            : vlSelfRef.main_cpu__DOT__s3)));
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp 
        = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s30) 
                    | (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__nq_temp))));
    vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp 
        = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s30) 
                    | (IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__nq_temp))));
    vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp 
        = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s30) 
                    | (IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__nq_temp))));
    vlSelfRef.CLKIO = ((~ (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp)) 
                       & (IData)(vlSelfRef.CLK));
    vlSelfRef.main_cpu__DOT__Registers_i5__DOT__s1 
        = ((~ (IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp)) 
           & (IData)(vlSelfRef.CLK));
    vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__s1 
        = ((~ (IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp)) 
           & (IData)(vlSelfRef.CLK));
}

void Vmain_cpu___024root___eval_ico(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_ico\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vmain_cpu___024root___ico_sequent__TOP__0(vlSelf);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmain_cpu___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vmain_cpu___024root___eval_phase__ico(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_phase__ico\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vmain_cpu___024root___eval_triggers_vec__ico(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vmain_cpu___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = Vmain_cpu___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vmain_cpu___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vmain_cpu___024root___eval_triggers_vec__act(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_triggers_vec__act\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    (((((IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__s1) 
                                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__ProgramCounter_i10__DOT__s1__0))) 
                                                       << 6U) 
                                                      | ((((IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__s1) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__Registers_i5__DOT__s1__0))) 
                                                          << 5U) 
                                                         | (((IData)(vlSelfRef.CLK) 
                                                             & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__CLK__0))) 
                                                            << 4U))) 
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
    vlSelfRef.__Vtrigprevexpr___TOP__CLK__0 = vlSelfRef.CLK;
    vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__Registers_i5__DOT__s1__0 
        = vlSelfRef.main_cpu__DOT__Registers_i5__DOT__s1;
    vlSelfRef.__Vtrigprevexpr___TOP__main_cpu__DOT__ProgramCounter_i10__DOT__s1__0 
        = vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__s1;
    if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.__VactDidInit)))))) {
        vlSelfRef.__VactDidInit = 1U;
        vlSelfRef.__VactTriggered[0U] = (1ULL | vlSelfRef.__VactTriggered[0U]);
        vlSelfRef.__VactTriggered[0U] = (2ULL | vlSelfRef.__VactTriggered[0U]);
        vlSelfRef.__VactTriggered[0U] = (4ULL | vlSelfRef.__VactTriggered[0U]);
    }
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

void Vmain_cpu___024root___act_sequent__TOP__0(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___act_sequent__TOP__0\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__nq_temp 
        = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp) 
                    | (IData)(vlSelfRef.main_cpu__DOT__s5))));
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp 
        = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s30) 
                    | (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__nq_temp))));
    vlSelfRef.CLKIO = ((~ (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp)) 
                       & (IData)(vlSelfRef.CLK));
}

void Vmain_cpu___024root___act_sequent__TOP__1(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___act_sequent__TOP__1\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__nq_temp 
        = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp) 
                    | (IData)(vlSelfRef.main_cpu__DOT__s5))));
    vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp 
        = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s30) 
                    | (IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__nq_temp))));
    vlSelfRef.main_cpu__DOT__Registers_i5__DOT__s1 
        = ((~ (IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp)) 
           & (IData)(vlSelfRef.CLK));
}

void Vmain_cpu___024root___act_sequent__TOP__2(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___act_sequent__TOP__2\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__nq_temp 
        = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp) 
                    | (IData)(vlSelfRef.main_cpu__DOT__s5))));
    vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp 
        = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s30) 
                    | (IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__nq_temp))));
    vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__s1 
        = ((~ (IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp)) 
           & (IData)(vlSelfRef.CLK));
}

void Vmain_cpu___024root___eval_act(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_act\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__nq_temp 
            = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp) 
                        | (IData)(vlSelfRef.main_cpu__DOT__s5))));
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp 
            = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s30) 
                        | (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__nq_temp))));
        vlSelfRef.CLKIO = ((~ (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp)) 
                           & (IData)(vlSelfRef.CLK));
    }
    if ((2ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__nq_temp 
            = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp) 
                        | (IData)(vlSelfRef.main_cpu__DOT__s5))));
        vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp 
            = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s30) 
                        | (IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__nq_temp))));
        vlSelfRef.main_cpu__DOT__Registers_i5__DOT__s1 
            = ((~ (IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp)) 
               & (IData)(vlSelfRef.CLK));
    }
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__nq_temp 
            = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp) 
                        | (IData)(vlSelfRef.main_cpu__DOT__s5))));
        vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp 
            = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s30) 
                        | (IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__nq_temp))));
        vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__s1 
            = ((~ (IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp)) 
               & (IData)(vlSelfRef.CLK));
    }
}

void Vmain_cpu___024root___nba_sequent__TOP__0(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_sequent__TOP__0\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s31) {
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Counter_Nbit_i0__DOT__count 
            = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Counter_Nbit_i0__DOT__count)));
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Register_BUS_i5__DOT__state 
            = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__s7;
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Register_BUS_i4__DOT__state 
            = ((IData)(vlSelfRef.main_cpu__DOT__s5)
                ? vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__rem_temp
                : 0U);
    }
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
    if ((IData)((((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0) 
                  >> 1U) & (0U != (0x00000f80U & vlSelfRef.main_cpu__DOT__s27))))) {
        __VdlyVal__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0 
            = vlSelfRef.main_cpu__DOT__s6;
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

void Vmain_cpu___024root___nba_sequent__TOP__2(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_sequent__TOP__2\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0;
    __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 0;
    SData/*15:0*/ __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0;
    __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 0;
    CData/*7:0*/ __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0;
    __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 0;
    SData/*15:0*/ __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0;
    __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 0;
    CData/*7:0*/ __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0;
    __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 0;
    SData/*15:0*/ __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0;
    __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 0;
    CData/*7:0*/ __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0;
    __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 0;
    SData/*15:0*/ __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0;
    __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 0;
    // Body
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 0U;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 0U;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 0U;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 0U;
    if ((1U & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s0))) {
        __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 
            = (0x000000ffU & vlSelfRef.DwIO);
        __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 
            = (0x0000ffffU & (vlSelfRef.main_cpu__DOT__s3 
                              >> 2U));
        __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 1U;
    }
    if ((2U & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s0))) {
        __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 
            = (0x000000ffU & (vlSelfRef.DwIO >> 8U));
        __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 
            = (0x0000ffffU & (vlSelfRef.main_cpu__DOT__s3 
                              >> 2U));
        __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 1U;
    }
    if ((4U & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s0))) {
        __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 
            = (0x000000ffU & (vlSelfRef.DwIO >> 0x00000010U));
        __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 
            = (0x0000ffffU & (vlSelfRef.main_cpu__DOT__s3 
                              >> 2U));
        __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 1U;
    }
    if ((8U & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s0))) {
        __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 
            = (vlSelfRef.DwIO >> 0x00000018U);
        __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 
            = (0x0000ffffU & (vlSelfRef.main_cpu__DOT__s3 
                              >> 2U));
        __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 1U;
    }
    if (__VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory[__VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0] 
            = __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0;
    }
    if (__VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory[__VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0] 
            = __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0;
    }
    if (__VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory[__VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0] 
            = __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0;
    }
    if (__VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory[__VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0] 
            = __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0;
    }
}

void Vmain_cpu___024root___nba_sequent__TOP__3(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_sequent__TOP__3\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state 
        = vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__s0;
}

extern const VlUnpacked<CData/*0:0*/, 32> Vmain_cpu__ConstPool__TABLE_he6af935d_0;

void Vmain_cpu___024root___nba_comb__TOP__0(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_comb__TOP__0\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*5:0*/ main_cpu__DOT__ControlLogic_i3__DOT__s8;
    main_cpu__DOT__ControlLogic_i3__DOT__s8 = 0;
    CData/*4:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    vlSelfRef.main_cpu__DOT__s27 = ((IData)((0x00040000U 
                                             != (0xfffc0000U 
                                                 & vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state)))
                                     ? ((0x0130U < 
                                         (0x000007ffU 
                                          & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state 
                                             >> 2U)))
                                         ? 0U : ((0x0130U 
                                                  >= 
                                                  (0x000001ffU 
                                                   & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state 
                                                      >> 2U)))
                                                  ? vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom
                                                 [(0x000001ffU 
                                                   & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state 
                                                      >> 2U))]
                                                  : 0U))
                                     : (((vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory
                                          [(0x0000ffffU 
                                            & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state 
                                               >> 2U))] 
                                          << 0x00000018U) 
                                         | (vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory
                                            [(0x0000ffffU 
                                              & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state 
                                                 >> 2U))] 
                                            << 0x00000010U)) 
                                        | ((vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory
                                            [(0x0000ffffU 
                                              & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state 
                                                 >> 2U))] 
                                            << 8U) 
                                           | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory
                                           [(0x0000ffffU 
                                             & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state 
                                                >> 2U))])));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2 = (3U 
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
        = ((1U == (3U & (vlSelfRef.main_cpu__DOT__s27 
                         >> 0x0000000cU))) | (0U == 
                                              (3U & 
                                               (vlSelfRef.main_cpu__DOT__s27 
                                                >> 0x0000000cU))));
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0 
        = ((0x1bU < (0x0000001fU & (vlSelfRef.main_cpu__DOT__s27 
                                    >> 2U))) ? 0U : 
           ((0x1bU >= (0x0000001fU & (vlSelfRef.main_cpu__DOT__s27 
                                      >> 2U))) ? vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom
            [(0x0000001fU & (vlSelfRef.main_cpu__DOT__s27 
                             >> 2U))] : 0U));
    vlSelfRef.main_cpu__DOT__s21 = ((0x00000400U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                     ? ((0x00000200U 
                                         & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                         ? 0U : ((0x00000100U 
                                                  & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                                  ? 0U
                                                  : 
                                                 ((((0x00000ffeU 
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
                                                           >> 0x00000014U))))))
                                     : ((0x00000200U 
                                         & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                         ? ((0x00000100U 
                                             & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                             ? (0xfffff000U 
                                                & vlSelfRef.main_cpu__DOT__s27)
                                             : (((- (IData)(
                                                            (vlSelfRef.main_cpu__DOT__s27 
                                                             >> 0x0000001fU))) 
                                                 << 0x0000000dU) 
                                                | ((((2U 
                                                      & (vlSelfRef.main_cpu__DOT__s27 
                                                         >> 0x0000001eU)) 
                                                     | (1U 
                                                        & (vlSelfRef.main_cpu__DOT__s27 
                                                           >> 7U))) 
                                                    << 0x0000000bU) 
                                                   | ((0x000007e0U 
                                                       & (vlSelfRef.main_cpu__DOT__s27 
                                                          >> 0x00000014U)) 
                                                      | (0x0000001eU 
                                                         & (vlSelfRef.main_cpu__DOT__s27 
                                                            >> 7U))))))
                                         : ((0x00000100U 
                                             & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                             ? (((- (IData)(
                                                            (vlSelfRef.main_cpu__DOT__s27 
                                                             >> 0x0000001fU))) 
                                                 << 0x0000000cU) 
                                                | ((0x00000fe0U 
                                                    & (vlSelfRef.main_cpu__DOT__s27 
                                                       >> 0x00000014U)) 
                                                   | (0x0000001fU 
                                                      & (vlSelfRef.main_cpu__DOT__s27 
                                                         >> 7U))))
                                             : (((- (IData)(
                                                            (vlSelfRef.main_cpu__DOT__s27 
                                                             >> 0x0000001fU))) 
                                                 << 0x0000000cU) 
                                                | (vlSelfRef.main_cpu__DOT__s27 
                                                   >> 0x00000014U)))));
    main_cpu__DOT__ControlLogic_i3__DOT__s8 = (((1U 
                                                 == 
                                                 (3U 
                                                  & ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0) 
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
    vlSelfRef.main_cpu__DOT__s22 = (vlSelfRef.main_cpu__DOT__s21 
                                    + vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state);
    vlSelfRef.main_cpu__DOT__s0 = ((0x00001000U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                    ? ((0x00000800U 
                                        & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                        ? ((0x00002000U 
                                            & vlSelfRef.main_cpu__DOT__s27)
                                            ? 5U : 6U)
                                        : 0U) : ((0x3dU 
                                                  < (IData)(main_cpu__DOT__ControlLogic_i3__DOT__s8))
                                                  ? 0U
                                                  : 
                                                 ((0x3dU 
                                                   >= (IData)(main_cpu__DOT__ControlLogic_i3__DOT__s8))
                                                   ? vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom
                                                  [main_cpu__DOT__ControlLogic_i3__DOT__s8]
                                                   : 0U)));
    __Vtableidx1 = vlSelfRef.main_cpu__DOT__s0;
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s26 = Vmain_cpu__ConstPool__TABLE_he6af935d_0
        [__Vtableidx1];
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s29 = ((0x10U 
                                                  == (IData)(vlSelfRef.main_cpu__DOT__s0)) 
                                                 | (0x11U 
                                                    == (IData)(vlSelfRef.main_cpu__DOT__s0)));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s30 = ((0x0eU 
                                                  == (IData)(vlSelfRef.main_cpu__DOT__s0)) 
                                                 | (0x10U 
                                                    == (IData)(vlSelfRef.main_cpu__DOT__s0)));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s1 = ((1U 
                                                 == (IData)(vlSelfRef.main_cpu__DOT__s0)) 
                                                | ((6U 
                                                    == (IData)(vlSelfRef.main_cpu__DOT__s0)) 
                                                   | (5U 
                                                      == (IData)(vlSelfRef.main_cpu__DOT__s0))));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s31 = ((0x0eU 
                                                  == (IData)(vlSelfRef.main_cpu__DOT__s0)) 
                                                 | ((0x0fU 
                                                     == (IData)(vlSelfRef.main_cpu__DOT__s0)) 
                                                    | (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s29)));
}

void Vmain_cpu___024root___nba_comb__TOP__1(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_comb__TOP__1\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ main_cpu__DOT__s11;
    main_cpu__DOT__s11 = 0;
    CData/*7:0*/ main_cpu__DOT__MemoryMapperExp_i0__DOT__s20;
    main_cpu__DOT__MemoryMapperExp_i0__DOT__s20 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s6;
    main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s6 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s8;
    main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s8 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s10;
    main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s10 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s6;
    main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s6 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s8;
    main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s8 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s6;
    main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s6 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s9;
    main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s9 = 0;
    // Body
    main_cpu__DOT__s11 = ((IData)((0U != (0x01f00000U 
                                          & vlSelfRef.main_cpu__DOT__s27)))
                           ? vlSelfRef.main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory
                          [(0x0000001fU & (vlSelfRef.main_cpu__DOT__s27 
                                           >> 0x00000014U))]
                           : 0U);
    vlSelfRef.main_cpu__DOT__s2 = ((IData)((0U != (0x000f8000U 
                                                   & vlSelfRef.main_cpu__DOT__s27)))
                                    ? vlSelfRef.main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory
                                   [(0x0000001fU & 
                                     (vlSelfRef.main_cpu__DOT__s27 
                                      >> 0x0000000fU))]
                                    : 0U);
    main_cpu__DOT__MemoryMapperExp_i0__DOT__s20 = (0x000000ffU 
                                                   & ((0U 
                                                       == 
                                                       (3U 
                                                        & (vlSelfRef.main_cpu__DOT__s27 
                                                           >> 0x0000000cU)))
                                                       ? main_cpu__DOT__s11
                                                       : 
                                                      (main_cpu__DOT__s11 
                                                       >> 8U)));
    vlSelfRef.main_cpu__DOT__s1 = ((0x00000020U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                    ? vlSelfRef.main_cpu__DOT__s21
                                    : main_cpu__DOT__s11);
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__s0 
        = ((vlSelfRef.main_cpu__DOT__s2 >> 0x0000001fU) 
           & (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s30));
    vlSelfRef.DwIO = ((((0x0000ff00U & (((1U == (3U 
                                                 & (vlSelfRef.main_cpu__DOT__s27 
                                                    >> 0x0000000cU)))
                                          ? (IData)(main_cpu__DOT__MemoryMapperExp_i0__DOT__s20)
                                          : ((0U == 
                                              (3U & 
                                               (vlSelfRef.main_cpu__DOT__s27 
                                                >> 0x0000000cU)))
                                              ? main_cpu__DOT__s11
                                              : (main_cpu__DOT__s11 
                                                 >> 0x00000018U))) 
                                        << 8U)) | (0x000000ffU 
                                                   & ((1U 
                                                       == 
                                                       (3U 
                                                        & (vlSelfRef.main_cpu__DOT__s27 
                                                           >> 0x0000000cU)))
                                                       ? main_cpu__DOT__s11
                                                       : 
                                                      ((0U 
                                                        == 
                                                        (3U 
                                                         & (vlSelfRef.main_cpu__DOT__s27 
                                                            >> 0x0000000cU)))
                                                        ? main_cpu__DOT__s11
                                                        : 
                                                       (main_cpu__DOT__s11 
                                                        >> 0x00000010U))))) 
                       << 0x00000010U) | (((IData)(main_cpu__DOT__MemoryMapperExp_i0__DOT__s20) 
                                           << 8U) | 
                                          (0x000000ffU 
                                           & main_cpu__DOT__s11)));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0 = ((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s1)
                                                 ? 
                                                (~ vlSelfRef.main_cpu__DOT__s1)
                                                 : vlSelfRef.main_cpu__DOT__s1);
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s6 
        = ((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__s0)
            ? (- vlSelfRef.main_cpu__DOT__s2) : vlSelfRef.main_cpu__DOT__s2);
    if ((1U & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)) {
        main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s6 
            = VL_SHIFTL_III(32,32,32, vlSelfRef.main_cpu__DOT__s2, 1U);
        main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s6 
            = VL_SHIFTR_III(32,32,32, vlSelfRef.main_cpu__DOT__s2, 1U);
        main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s6 
            = ((0x80000000U & vlSelfRef.main_cpu__DOT__s2) 
               | (vlSelfRef.main_cpu__DOT__s2 >> 1U));
    } else {
        main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s6 
            = vlSelfRef.main_cpu__DOT__s2;
        main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s6 
            = vlSelfRef.main_cpu__DOT__s2;
        main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s6 
            = vlSelfRef.main_cpu__DOT__s2;
    }
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__mul_i3__DOT__s0 
        = ((QData)((IData)(vlSelfRef.main_cpu__DOT__s2)) 
           * (QData)((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
        = (0x00000001ffffffffULL & ((QData)((IData)(vlSelfRef.main_cpu__DOT__s2)) 
                                    + ((QData)((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)) 
                                       + (QData)((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s1)))));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__s1 
        = ((vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0 
            >> 0x0000001fU) & (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s30));
    if ((2U & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)) {
        main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s8 
            = VL_SHIFTL_III(32,32,32, main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s6, 2U);
        main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s8 
            = VL_SHIFTR_III(32,32,32, main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s6, 2U);
        main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s9 
            = (((- (IData)((vlSelfRef.main_cpu__DOT__s2 
                            >> 0x0000001fU))) << 0x0000001eU) 
               | (main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s6 
                  >> 2U));
    } else {
        main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s8 
            = main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s6;
        main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s8 
            = main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s6;
        main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s9 
            = main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s6;
    }
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s23 = (((IData)(
                                                          (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__mul_i3__DOT__s0 
                                                           >> 0x00000020U)) 
                                                  - 
                                                  (((vlSelfRef.main_cpu__DOT__s2 
                                                     >> 0x0000001fU) 
                                                    & ((0x0bU 
                                                        == (IData)(vlSelfRef.main_cpu__DOT__s0)) 
                                                       | (0x0dU 
                                                          == (IData)(vlSelfRef.main_cpu__DOT__s0))))
                                                    ? vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0
                                                    : 0U)) 
                                                 - 
                                                 (((vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0 
                                                    >> 0x0000001fU) 
                                                   & (0x0bU 
                                                      == (IData)(vlSelfRef.main_cpu__DOT__s0)))
                                                   ? vlSelfRef.main_cpu__DOT__s2
                                                   : 0U));
    vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s3 
        = (IData)((0ULL != (0x00000000ffffffffULL & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp)));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s12 = (1U 
                                                 & ((((~ 
                                                       (vlSelfRef.main_cpu__DOT__s2 
                                                        >> 0x0000001fU)) 
                                                      & ((vlSelfRef.main_cpu__DOT__s1 
                                                          >> 0x0000001fU) 
                                                         & (IData)(
                                                                   (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                                                    >> 0x0000001fU)))) 
                                                     | ((~ 
                                                         ((vlSelfRef.main_cpu__DOT__s1 
                                                           >> 0x0000001fU) 
                                                          | (IData)(
                                                                    (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                                                     >> 0x0000001fU)))) 
                                                        & (vlSelfRef.main_cpu__DOT__s2 
                                                           >> 0x0000001fU))) 
                                                    ^ (IData)(
                                                              (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                                               >> 0x0000001fU))));
    vlSelfRef.__VdfgRegularize_he50b618e_0_4 = (QData)((IData)(
                                                               ((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__s1)
                                                                 ? 
                                                                (- vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)
                                                                 : vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)));
    if ((4U & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)) {
        main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s10 
            = VL_SHIFTL_III(32,32,32, main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s8, 4U);
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s10 
            = VL_SHIFTR_III(32,32,32, main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s8, 4U);
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s11 
            = (((- (IData)((vlSelfRef.main_cpu__DOT__s2 
                            >> 0x0000001fU))) << 0x0000001cU) 
               | (main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s9 
                  >> 4U));
    } else {
        main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s10 
            = main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s8;
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s10 
            = main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s8;
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s11 
            = main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s9;
    }
    vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s4 
        = (1U & ((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s26)
                  ? vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s12
                  : (1U & (~ (IData)((vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                      >> 0x00000020U))))));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s12 
        = ((8U & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)
            ? VL_SHIFTL_III(32,32,32, main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s10, 8U)
            : main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s10);
}

void Vmain_cpu___024root___nba_comb__TOP__2(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_comb__TOP__2\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((8U & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)) {
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s12 
            = VL_SHIFTR_III(32,32,32, vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s10, 8U);
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s13 
            = (((- (IData)((vlSelfRef.main_cpu__DOT__s2 
                            >> 0x0000001fU))) << 0x00000018U) 
               | (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s11 
                  >> 8U));
    } else {
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s12 
            = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s10;
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s13 
            = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s11;
    }
}

void Vmain_cpu___024root___nba_comb__TOP__3(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_comb__TOP__3\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.main_cpu__DOT__s5 = ((~ (IData)((0x0fU 
                                               == (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Counter_Nbit_i0__DOT__count)))) 
                                   & (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s31));
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s30 
        = (1U & (~ ((IData)(vlSelfRef.CLK) | (IData)(vlSelfRef.main_cpu__DOT__s5))));
}

void Vmain_cpu___024root___nba_comb__TOP__4(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_comb__TOP__4\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*3:0*/ main_cpu__DOT__DataController_i1__DOT__s26;
    main_cpu__DOT__DataController_i1__DOT__s26 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__s8;
    main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__s8 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s8;
    main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s8 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s10;
    main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s10 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s12;
    main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s12 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i2__DOT__s0;
    main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i2__DOT__s0 = 0;
    QData/*32:0*/ main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i2__DOT__DIG_Sub_i0__DOT__temp;
    main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i2__DOT__DIG_Sub_i0__DOT__temp = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i3__DOT__s0;
    main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i3__DOT__s0 = 0;
    QData/*32:0*/ main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i3__DOT__DIG_Sub_i0__DOT__temp;
    main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i3__DOT__DIG_Sub_i0__DOT__temp = 0;
    CData/*0:0*/ __VdfgRegularize_he50b618e_0_3;
    __VdfgRegularize_he50b618e_0_3 = 0;
    // Body
    main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s8 
        = ((1U & (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Counter_Nbit_i0__DOT__count))
            ? VL_SHIFTL_III(32,32,32, vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s6, 2U)
            : vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s6);
    main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s10 
        = ((2U & (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Counter_Nbit_i0__DOT__count))
            ? VL_SHIFTL_III(32,32,32, main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s8, 4U)
            : main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s8);
    main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s12 
        = ((4U & (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Counter_Nbit_i0__DOT__count))
            ? VL_SHIFTL_III(32,32,32, main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s10, 8U)
            : main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s10);
    main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__s8 
        = ((8U & (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Counter_Nbit_i0__DOT__count))
            ? VL_SHIFTL_III(32,32,32, main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s12, 0x00000010U)
            : main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__SLL_i1__DOT__s12);
    main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i3__DOT__s0 
        = ((vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Register_BUS_i4__DOT__state 
            << 1U) | (main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__s8 
                      >> 0x0000001fU));
    main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i3__DOT__DIG_Sub_i0__DOT__temp 
        = (0x00000001ffffffffULL & ((QData)((IData)(main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i3__DOT__s0)) 
                                    - vlSelfRef.__VdfgRegularize_he50b618e_0_4));
    main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i2__DOT__s0 
        = ((((1U & (IData)((main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i3__DOT__DIG_Sub_i0__DOT__temp 
                            >> 0x00000020U))) ? main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i3__DOT__s0
              : (IData)(main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i3__DOT__DIG_Sub_i0__DOT__temp)) 
            << 1U) | (1U & (main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__s8 
                            >> 0x0000001eU)));
    main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i2__DOT__DIG_Sub_i0__DOT__temp 
        = (0x00000001ffffffffULL & ((QData)((IData)(main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i2__DOT__s0)) 
                                    - vlSelfRef.__VdfgRegularize_he50b618e_0_4));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__rem_temp 
        = ((1U & (IData)((main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i2__DOT__DIG_Sub_i0__DOT__temp 
                          >> 0x00000020U))) ? main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i2__DOT__s0
            : (IData)(main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i2__DOT__DIG_Sub_i0__DOT__temp));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__s7 
        = ((vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Register_BUS_i5__DOT__state 
            << 2U) | ((2U & ((~ (IData)((main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i3__DOT__DIG_Sub_i0__DOT__temp 
                                         >> 0x00000020U))) 
                             << 1U)) | (1U & (~ (IData)(
                                                        (main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__divstage_i2__DOT__DIG_Sub_i0__DOT__temp 
                                                         >> 0x00000020U))))));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s24 = ((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s29)
                                                  ? 
                                                 ((0U 
                                                   == vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)
                                                   ? vlSelfRef.main_cpu__DOT__s2
                                                   : 
                                                  ((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__s0)
                                                    ? 
                                                   (- vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__rem_temp)
                                                    : vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__rem_temp))
                                                  : 
                                                 ((0U 
                                                   == vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)
                                                   ? 0xffffffffU
                                                   : 
                                                  (((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__s0) 
                                                    ^ (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__s1))
                                                    ? 
                                                   (- vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__s7)
                                                    : vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__s7)));
    vlSelfRef.main_cpu__DOT__s3 = ((0x00000010U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                    ? ((8U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                        ? 0U : ((4U 
                                                 & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                 ? 0U
                                                 : 
                                                ((2U 
                                                  & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                  ? 0U
                                                  : vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s24)))
                                    : ((8U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                        ? ((4U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                            ? ((2U 
                                                & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                ? vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s24
                                                : vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s23)
                                            : ((2U 
                                                & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                ? (
                                                   (1U 
                                                    & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                    ? vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s23
                                                    : (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__mul_i3__DOT__s0))
                                                : (
                                                   (1U 
                                                    & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                    ? 
                                                   ((0x00000010U 
                                                     & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)
                                                     ? 
                                                    (((- (IData)(
                                                                 (vlSelfRef.main_cpu__DOT__s2 
                                                                  >> 0x0000001fU))) 
                                                      << 0x00000010U) 
                                                     | (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s13 
                                                        >> 0x00000010U))
                                                     : vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s13)
                                                    : 
                                                   ((0x00000010U 
                                                     & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)
                                                     ? 
                                                    VL_SHIFTR_III(32,32,32, vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s12, 0x00000010U)
                                                     : vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s12))))
                                        : ((4U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                            ? ((2U 
                                                & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                ? (
                                                   (1U 
                                                    & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                    ? 
                                                   ((0x00000010U 
                                                     & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)
                                                     ? 
                                                    VL_SHIFTL_III(32,32,32, vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s12, 0x00000010U)
                                                     : vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SLL_i5__DOT__s12)
                                                    : vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s12)
                                                : (
                                                   (1U 
                                                    & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                    ? 
                                                   (1U 
                                                    & (~ (IData)(
                                                                 (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                                                  >> 0x00000020U))))
                                                    : 
                                                   (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0 
                                                    ^ vlSelfRef.main_cpu__DOT__s2)))
                                            : ((2U 
                                                & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                ? (
                                                   (1U 
                                                    & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                    ? 
                                                   (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0 
                                                    | vlSelfRef.main_cpu__DOT__s2)
                                                    : 
                                                   (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0 
                                                    & vlSelfRef.main_cpu__DOT__s2))
                                                : (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp)))));
    vlSelfRef.AddIO = vlSelfRef.main_cpu__DOT__s3;
    vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__s0 
        = (0xfffffffeU & ((0x00000080U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                           ? ((0x00000040U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                               ? ((1U & ((0x00004000U 
                                          & vlSelfRef.main_cpu__DOT__s27)
                                          ? ((0x00001000U 
                                              & vlSelfRef.main_cpu__DOT__s27)
                                              ? (~ (IData)(vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s4))
                                              : (IData)(vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s4))
                                          : ((0x00001000U 
                                              & vlSelfRef.main_cpu__DOT__s27)
                                              ? (IData)(vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s3)
                                              : (~ (IData)(vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s3)))))
                                   ? vlSelfRef.main_cpu__DOT__s22
                                   : ((IData)(4U) + vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state))
                               : vlSelfRef.main_cpu__DOT__s3)
                           : ((0x00000040U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                               ? vlSelfRef.main_cpu__DOT__s22
                               : ((IData)(4U) + vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state))));
    main_cpu__DOT__DataController_i1__DOT__s26 = ((IData)(vlSelfRef.main_cpu__DOT__DataController_i1__DOT__s24)
                                                   ? 
                                                  (((((IData)(
                                                              ((0x00001000U 
                                                                == 
                                                                (0x00003000U 
                                                                 & vlSelfRef.main_cpu__DOT__s27)) 
                                                               & (2U 
                                                                  == 
                                                                  (3U 
                                                                   & vlSelfRef.main_cpu__DOT__s3)))) 
                                                      | (3U 
                                                         == 
                                                         (3U 
                                                          & vlSelfRef.main_cpu__DOT__s3))) 
                                                     << 3U) 
                                                    | (((IData)(
                                                                ((0x00001000U 
                                                                  == 
                                                                  (0x00003000U 
                                                                   & vlSelfRef.main_cpu__DOT__s27)) 
                                                                 & (1U 
                                                                    == 
                                                                    (3U 
                                                                     & vlSelfRef.main_cpu__DOT__s3)))) 
                                                        | (2U 
                                                           == 
                                                           (3U 
                                                            & vlSelfRef.main_cpu__DOT__s3))) 
                                                       << 2U)) 
                                                   | ((((IData)(
                                                                ((0x00001000U 
                                                                  == 
                                                                  (0x00003000U 
                                                                   & vlSelfRef.main_cpu__DOT__s27)) 
                                                                 & (0U 
                                                                    == 
                                                                    (3U 
                                                                     & vlSelfRef.main_cpu__DOT__s3)))) 
                                                        | (1U 
                                                           == 
                                                           (3U 
                                                            & vlSelfRef.main_cpu__DOT__s3))) 
                                                       << 1U) 
                                                      | (0U 
                                                         == 
                                                         (3U 
                                                          & vlSelfRef.main_cpu__DOT__s3))))
                                                   : 0x0fU);
    __VdfgRegularize_he50b618e_0_3 = (IData)((0U != 
                                              (0xfff80000U 
                                               & vlSelfRef.main_cpu__DOT__s3)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0 = (1U 
                                                & ((~ 
                                                    (vlSelfRef.main_cpu__DOT__s3 
                                                     >> 0x00000012U)) 
                                                   | (IData)(__VdfgRegularize_he50b618e_0_3)));
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s0 
        = ((- (IData)((1U & ((~ (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0)) 
                             & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))))) 
           & (IData)(main_cpu__DOT__DataController_i1__DOT__s26));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_1 = (1U 
                                                & ((~ 
                                                    ((vlSelfRef.main_cpu__DOT__s3 
                                                      >> 0x00000012U) 
                                                     | (IData)(__VdfgRegularize_he50b618e_0_3))) 
                                                   | (~ (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))));
    vlSelfRef.ReIO = ((~ (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_1)) 
                      & (4U == (0x001cU & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))));
    vlSelfRef.WeIO = ((- (IData)((1U & ((~ (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_1)) 
                                        & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))))) 
                      & (IData)(main_cpu__DOT__DataController_i1__DOT__s26));
    vlSelfRef.main_cpu__DOT__s12 = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_1)
                                     ? ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0)
                                         ? ((0x0130U 
                                             < (0x000007ffU 
                                                & (vlSelfRef.main_cpu__DOT__s3 
                                                   >> 2U)))
                                             ? 0U : 
                                            ((0x0130U 
                                              >= (0x000001ffU 
                                                  & (vlSelfRef.main_cpu__DOT__s3 
                                                     >> 2U)))
                                              ? vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom
                                             [(0x000001ffU 
                                               & (vlSelfRef.main_cpu__DOT__s3 
                                                  >> 2U))]
                                              : 0U))
                                         : (((vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory
                                              [(0x0000ffffU 
                                                & (vlSelfRef.main_cpu__DOT__s3 
                                                   >> 2U))] 
                                              << 0x00000018U) 
                                             | (vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory
                                                [(0x0000ffffU 
                                                  & (vlSelfRef.main_cpu__DOT__s3 
                                                     >> 2U))] 
                                                << 0x00000010U)) 
                                            | ((vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory
                                                [(0x0000ffffU 
                                                  & (vlSelfRef.main_cpu__DOT__s3 
                                                     >> 2U))] 
                                                << 8U) 
                                               | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory
                                               [(0x0000ffffU 
                                                 & (vlSelfRef.main_cpu__DOT__s3 
                                                    >> 2U))])))
                                     : vlSelfRef.DrIO);
}

void Vmain_cpu___024root___nba_comb__TOP__5(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_comb__TOP__5\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.main_cpu__DOT__s6 = ((0x00000010U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                    ? ((8U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                        ? 0U : ((4U 
                                                 & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                                 ? 0U
                                                 : vlSelfRef.main_cpu__DOT__s22))
                                    : ((8U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                        ? ((4U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                            ? vlSelfRef.main_cpu__DOT__s21
                                            : ((IData)(4U) 
                                               + vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state))
                                        : ((4U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0))
                                            ? ((IData)(vlSelfRef.main_cpu__DOT__DataController_i1__DOT__s24)
                                                ? (
                                                   (2U 
                                                    & vlSelfRef.main_cpu__DOT__s3)
                                                    ? 
                                                   ((1U 
                                                     & vlSelfRef.main_cpu__DOT__s3)
                                                     ? 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                      ? 0U
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                       ? 
                                                      VL_SHIFTR_III(32,32,32, vlSelfRef.main_cpu__DOT__s12, 0x00000018U)
                                                       : 
                                                      (((- (IData)(
                                                                   (vlSelfRef.main_cpu__DOT__s12 
                                                                    >> 0x0000001fU))) 
                                                        << 8U) 
                                                       | (vlSelfRef.main_cpu__DOT__s12 
                                                          >> 0x00000018U))))
                                                     : 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                       ? 
                                                      VL_SHIFTR_III(32,32,32, vlSelfRef.main_cpu__DOT__s12, 0x00000010U)
                                                       : 
                                                      (((- (IData)(
                                                                   (vlSelfRef.main_cpu__DOT__s12 
                                                                    >> 0x0000001fU))) 
                                                        << 0x00000010U) 
                                                       | (vlSelfRef.main_cpu__DOT__s12 
                                                          >> 0x00000010U)))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                       ? 
                                                      (0x000000ffU 
                                                       & (vlSelfRef.main_cpu__DOT__s12 
                                                          >> 0x00000010U))
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (vlSelfRef.main_cpu__DOT__s12 
                                                                       >> 0x00000017U)))) 
                                                        << 8U) 
                                                       | (0x000000ffU 
                                                          & (vlSelfRef.main_cpu__DOT__s12 
                                                             >> 0x00000010U))))))
                                                    : 
                                                   ((1U 
                                                     & vlSelfRef.main_cpu__DOT__s3)
                                                     ? 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                       ? 
                                                      (0x0000ffffU 
                                                       & (vlSelfRef.main_cpu__DOT__s12 
                                                          >> 8U))
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (vlSelfRef.main_cpu__DOT__s12 
                                                                       >> 0x00000017U)))) 
                                                        << 0x00000010U) 
                                                       | (0x0000ffffU 
                                                          & (vlSelfRef.main_cpu__DOT__s12 
                                                             >> 8U))))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                       ? 
                                                      (0x000000ffU 
                                                       & (vlSelfRef.main_cpu__DOT__s12 
                                                          >> 8U))
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (vlSelfRef.main_cpu__DOT__s12 
                                                                       >> 0x0000000fU)))) 
                                                        << 8U) 
                                                       | (0x000000ffU 
                                                          & (vlSelfRef.main_cpu__DOT__s12 
                                                             >> 8U)))))
                                                     : 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                       ? 
                                                      (0x0000ffffU 
                                                       & vlSelfRef.main_cpu__DOT__s12)
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (vlSelfRef.main_cpu__DOT__s12 
                                                                       >> 0x0000000fU)))) 
                                                        << 0x00000010U) 
                                                       | (0x0000ffffU 
                                                          & vlSelfRef.main_cpu__DOT__s12)))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_2))
                                                       ? 
                                                      (0x000000ffU 
                                                       & vlSelfRef.main_cpu__DOT__s12)
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (vlSelfRef.main_cpu__DOT__s12 
                                                                       >> 7U)))) 
                                                        << 8U) 
                                                       | (0x000000ffU 
                                                          & vlSelfRef.main_cpu__DOT__s12))))))
                                                : vlSelfRef.main_cpu__DOT__s12)
                                            : vlSelfRef.main_cpu__DOT__s3)));
}

void Vmain_cpu___024root___eval_nba(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_nba\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vinline__nba_sequent__TOP__1___VdlyVal__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0;
    __Vinline__nba_sequent__TOP__1___VdlyVal__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0 = 0;
    CData/*4:0*/ __Vinline__nba_sequent__TOP__1___VdlyDim0__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0;
    __Vinline__nba_sequent__TOP__1___VdlyDim0__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0 = 0;
    CData/*0:0*/ __Vinline__nba_sequent__TOP__1___VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0;
    __Vinline__nba_sequent__TOP__1___VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0 = 0;
    CData/*7:0*/ __Vinline__nba_sequent__TOP__2___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0;
    __Vinline__nba_sequent__TOP__2___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 0;
    SData/*15:0*/ __Vinline__nba_sequent__TOP__2___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0;
    __Vinline__nba_sequent__TOP__2___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 0;
    CData/*0:0*/ __Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0;
    __Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 0;
    CData/*7:0*/ __Vinline__nba_sequent__TOP__2___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0;
    __Vinline__nba_sequent__TOP__2___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 0;
    SData/*15:0*/ __Vinline__nba_sequent__TOP__2___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0;
    __Vinline__nba_sequent__TOP__2___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 0;
    CData/*0:0*/ __Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0;
    __Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 0;
    CData/*7:0*/ __Vinline__nba_sequent__TOP__2___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0;
    __Vinline__nba_sequent__TOP__2___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 0;
    SData/*15:0*/ __Vinline__nba_sequent__TOP__2___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0;
    __Vinline__nba_sequent__TOP__2___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 0;
    CData/*0:0*/ __Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0;
    __Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 0;
    CData/*7:0*/ __Vinline__nba_sequent__TOP__2___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0;
    __Vinline__nba_sequent__TOP__2___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 0;
    SData/*15:0*/ __Vinline__nba_sequent__TOP__2___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0;
    __Vinline__nba_sequent__TOP__2___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 0;
    CData/*0:0*/ __Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0;
    __Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 0;
    // Body
    if ((0x0000000000000010ULL & vlSelfRef.__VnbaTriggered[0U])) {
        if (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s31) {
            vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Counter_Nbit_i0__DOT__count 
                = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Counter_Nbit_i0__DOT__count)));
            vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Register_BUS_i5__DOT__state 
                = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__s7;
            vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Register_BUS_i4__DOT__state 
                = ((IData)(vlSelfRef.main_cpu__DOT__s5)
                    ? vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__rem_temp
                    : 0U);
        }
    }
    if ((0x0000000000000020ULL & vlSelfRef.__VnbaTriggered[0U])) {
        __Vinline__nba_sequent__TOP__1___VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0 = 0U;
        if ((IData)((((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__D__out__strong__out0) 
                      >> 1U) & (0U != (0x00000f80U 
                                       & vlSelfRef.main_cpu__DOT__s27))))) {
            __Vinline__nba_sequent__TOP__1___VdlyVal__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0 
                = vlSelfRef.main_cpu__DOT__s6;
            __Vinline__nba_sequent__TOP__1___VdlyDim0__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0 
                = (0x0000001fU & (vlSelfRef.main_cpu__DOT__s27 
                                  >> 7U));
            __Vinline__nba_sequent__TOP__1___VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0 = 1U;
        }
        if (__Vinline__nba_sequent__TOP__1___VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0) {
            vlSelfRef.main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory[__Vinline__nba_sequent__TOP__1___VdlyDim0__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0] 
                = __Vinline__nba_sequent__TOP__1___VdlyVal__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i1__DOT__memory__v0;
        }
    }
    if ((8ULL & vlSelfRef.__VnbaTriggered[0U])) {
        __Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 0U;
        __Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 0U;
        __Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 0U;
        __Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 0U;
        if ((1U & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s0))) {
            __Vinline__nba_sequent__TOP__2___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 
                = (0x000000ffU & vlSelfRef.DwIO);
            __Vinline__nba_sequent__TOP__2___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 
                = (0x0000ffffU & (vlSelfRef.main_cpu__DOT__s3 
                                  >> 2U));
            __Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 1U;
        }
        if ((2U & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s0))) {
            __Vinline__nba_sequent__TOP__2___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 
                = (0x000000ffU & (vlSelfRef.DwIO >> 8U));
            __Vinline__nba_sequent__TOP__2___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 
                = (0x0000ffffU & (vlSelfRef.main_cpu__DOT__s3 
                                  >> 2U));
            __Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 1U;
        }
        if ((4U & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s0))) {
            __Vinline__nba_sequent__TOP__2___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 
                = (0x000000ffU & (vlSelfRef.DwIO >> 0x00000010U));
            __Vinline__nba_sequent__TOP__2___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 
                = (0x0000ffffU & (vlSelfRef.main_cpu__DOT__s3 
                                  >> 2U));
            __Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 1U;
        }
        if ((8U & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__s0))) {
            __Vinline__nba_sequent__TOP__2___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 
                = (vlSelfRef.DwIO >> 0x00000018U);
            __Vinline__nba_sequent__TOP__2___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 
                = (0x0000ffffU & (vlSelfRef.main_cpu__DOT__s3 
                                  >> 2U));
            __Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 1U;
        }
        if (__Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0) {
            vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory[__Vinline__nba_sequent__TOP__2___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0] 
                = __Vinline__nba_sequent__TOP__2___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0;
        }
        if (__Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0) {
            vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory[__Vinline__nba_sequent__TOP__2___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0] 
                = __Vinline__nba_sequent__TOP__2___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0;
        }
        if (__Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0) {
            vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory[__Vinline__nba_sequent__TOP__2___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0] 
                = __Vinline__nba_sequent__TOP__2___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0;
        }
        if (__Vinline__nba_sequent__TOP__2___VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0) {
            vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory[__Vinline__nba_sequent__TOP__2___VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0] 
                = __Vinline__nba_sequent__TOP__2___VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i12__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0;
        }
    }
    if ((0x0000000000000040ULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i1__DOT__state 
            = vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__s0;
    }
    if ((0x0000000000000048ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vmain_cpu___024root___nba_comb__TOP__0(vlSelf);
    }
    if ((0x0000000000000068ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vmain_cpu___024root___nba_comb__TOP__1(vlSelf);
        if ((8U & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)) {
            vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s12 
                = VL_SHIFTR_III(32,32,32, vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s10, 8U);
            vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s13 
                = (((- (IData)((vlSelfRef.main_cpu__DOT__s2 
                                >> 0x0000001fU))) << 0x00000018U) 
                   | (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s11 
                      >> 8U));
        } else {
            vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s12 
                = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRL_i6__DOT__s10;
            vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s13 
                = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRA_i7__DOT__s11;
        }
    }
    if ((0x0000000000000058ULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.main_cpu__DOT__s5 = ((~ (IData)((0x0fU 
                                                   == (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__full_div_i4__DOT__seq_div_i5__DOT__DIG_Counter_Nbit_i0__DOT__count)))) 
                                       & (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s31));
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s30 
            = (1U & (~ ((IData)(vlSelfRef.CLK) | (IData)(vlSelfRef.main_cpu__DOT__s5))));
    }
    if ((0x0000000000000078ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vmain_cpu___024root___nba_comb__TOP__4(vlSelf);
        Vmain_cpu___024root___nba_comb__TOP__5(vlSelf);
    }
    if ((0x0000000000000059ULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__nq_temp 
            = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp) 
                        | (IData)(vlSelfRef.main_cpu__DOT__s5))));
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp 
            = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s30) 
                        | (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__nq_temp))));
        vlSelfRef.CLKIO = ((~ (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__rs_i8__DOT__q_temp)) 
                           & (IData)(vlSelfRef.CLK));
    }
    if ((0x000000000000005aULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__nq_temp 
            = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp) 
                        | (IData)(vlSelfRef.main_cpu__DOT__s5))));
        vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp 
            = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s30) 
                        | (IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__nq_temp))));
        vlSelfRef.main_cpu__DOT__Registers_i5__DOT__s1 
            = ((~ (IData)(vlSelfRef.main_cpu__DOT__Registers_i5__DOT__rs_i0__DOT__q_temp)) 
               & (IData)(vlSelfRef.CLK));
    }
    if ((0x000000000000005cULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__nq_temp 
            = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp) 
                        | (IData)(vlSelfRef.main_cpu__DOT__s5))));
        vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp 
            = (1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s30) 
                        | (IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__nq_temp))));
        vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__s1 
            = ((~ (IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__rs_i0__DOT__q_temp)) 
               & (IData)(vlSelfRef.CLK));
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
    Vmain_cpu___024root___eval_triggers_vec__act(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vmain_cpu___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vmain_cpu___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vmain_cpu___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        Vmain_cpu___024root___eval_act(vlSelf);
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
    vlSelfRef.__VicoFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vmain_cpu___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("main_cpu.v", 2998, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 100 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        vlSelfRef.__VicoPhaseResult = Vmain_cpu___024root___eval_phase__ico(vlSelf);
        vlSelfRef.__VicoFirstIteration = 0U;
    } while (vlSelfRef.__VicoPhaseResult);
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vmain_cpu___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("main_cpu.v", 2998, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vmain_cpu___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("main_cpu.v", 2998, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
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
