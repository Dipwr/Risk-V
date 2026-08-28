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
    // Locals
    IData/*31:0*/ main_cpu__DOT__s11;
    main_cpu__DOT__s11 = 0;
    // Body
    vlSelfRef.CLKIO = vlSelfRef.CLK;
    main_cpu__DOT__s11 = ((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_0)
                           ? ((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_5)
                               ? ((0x0130U < (0x000007ffU 
                                              & (vlSelfRef.main_cpu__DOT__s3 
                                                 >> 2U)))
                                   ? 0U : ((0x0130U 
                                            >= (0x000001ffU 
                                                & (vlSelfRef.main_cpu__DOT__s3 
                                                   >> 2U)))
                                            ? vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom
                                           [(0x000001ffU 
                                             & (vlSelfRef.main_cpu__DOT__s3 
                                                >> 2U))]
                                            : 0U)) : vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s3)
                           : vlSelfRef.DrIO);
    vlSelfRef.main_cpu__DOT__s5 = ((0x00000010U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                    ? ((8U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                        ? 0U : ((4U 
                                                 & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                                 ? 0U
                                                 : vlSelfRef.main_cpu__DOT__s21))
                                    : ((8U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                        ? ((4U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                            ? vlSelfRef.main_cpu__DOT__s20
                                            : ((IData)(4U) 
                                               + vlSelfRef.main_cpu__DOT__s23))
                                        : ((4U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                            ? ((IData)(vlSelfRef.main_cpu__DOT__DataController_i1__DOT__s24)
                                                ? (
                                                   (2U 
                                                    & vlSelfRef.main_cpu__DOT__s3)
                                                    ? 
                                                   ((1U 
                                                     & vlSelfRef.main_cpu__DOT__s3)
                                                     ? 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                      ? 0U
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                       ? 
                                                      VL_SHIFTR_III(32,32,32, main_cpu__DOT__s11, 0x00000018U)
                                                       : 
                                                      (((- (IData)(
                                                                   (main_cpu__DOT__s11 
                                                                    >> 0x0000001fU))) 
                                                        << 8U) 
                                                       | (main_cpu__DOT__s11 
                                                          >> 0x00000018U))))
                                                     : 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                       ? 
                                                      VL_SHIFTR_III(32,32,32, main_cpu__DOT__s11, 0x00000010U)
                                                       : 
                                                      (((- (IData)(
                                                                   (main_cpu__DOT__s11 
                                                                    >> 0x0000001fU))) 
                                                        << 0x00000010U) 
                                                       | (main_cpu__DOT__s11 
                                                          >> 0x00000010U)))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                       ? 
                                                      (0x000000ffU 
                                                       & (main_cpu__DOT__s11 
                                                          >> 0x00000010U))
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (main_cpu__DOT__s11 
                                                                       >> 0x00000017U)))) 
                                                        << 8U) 
                                                       | (0x000000ffU 
                                                          & (main_cpu__DOT__s11 
                                                             >> 0x00000010U))))))
                                                    : 
                                                   ((1U 
                                                     & vlSelfRef.main_cpu__DOT__s3)
                                                     ? 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                       ? 
                                                      (0x0000ffffU 
                                                       & (main_cpu__DOT__s11 
                                                          >> 8U))
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (main_cpu__DOT__s11 
                                                                       >> 0x00000017U)))) 
                                                        << 0x00000010U) 
                                                       | (0x0000ffffU 
                                                          & (main_cpu__DOT__s11 
                                                             >> 8U))))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                       ? 
                                                      (0x000000ffU 
                                                       & (main_cpu__DOT__s11 
                                                          >> 8U))
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (main_cpu__DOT__s11 
                                                                       >> 0x0000000fU)))) 
                                                        << 8U) 
                                                       | (0x000000ffU 
                                                          & (main_cpu__DOT__s11 
                                                             >> 8U)))))
                                                     : 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                       ? 
                                                      (0x0000ffffU 
                                                       & main_cpu__DOT__s11)
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (main_cpu__DOT__s11 
                                                                       >> 0x0000000fU)))) 
                                                        << 0x00000010U) 
                                                       | (0x0000ffffU 
                                                          & main_cpu__DOT__s11)))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                       ? 
                                                      (0x000000ffU 
                                                       & main_cpu__DOT__s11)
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (main_cpu__DOT__s11 
                                                                       >> 7U)))) 
                                                        << 8U) 
                                                       | (0x000000ffU 
                                                          & main_cpu__DOT__s11))))))
                                                : main_cpu__DOT__s11)
                                            : vlSelfRef.main_cpu__DOT__s3)));
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
                                                    ((((IData)(vlSelfRef.CLK) 
                                                       & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__CLK__0))) 
                                                      << 1U) 
                                                     | ((~ (IData)(vlSelfRef.CLK)) 
                                                        & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__CLK__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__CLK__0 = vlSelfRef.CLK;
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

void Vmain_cpu___024root___nba_sequent__TOP__0(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_sequent__TOP__0\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem0__v0;
    __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem0__v0 = 0;
    SData/*15:0*/ __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem0__v0;
    __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem0__v0 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem0__v0;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem0__v0 = 0;
    CData/*7:0*/ __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem1__v0;
    __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem1__v0 = 0;
    SData/*15:0*/ __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem1__v0;
    __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem1__v0 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem1__v0;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem1__v0 = 0;
    CData/*7:0*/ __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem2__v0;
    __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem2__v0 = 0;
    SData/*15:0*/ __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem2__v0;
    __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem2__v0 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem2__v0;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem2__v0 = 0;
    CData/*7:0*/ __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem3__v0;
    __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem3__v0 = 0;
    SData/*15:0*/ __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem3__v0;
    __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem3__v0 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem3__v0;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem3__v0 = 0;
    // Body
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem0__v0 = 0U;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem1__v0 = 0U;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem2__v0 = 0U;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem3__v0 = 0U;
    if (vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s2) {
        if ((1U & (IData)(vlSelfRef.main_cpu__DOT__s17))) {
            __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem0__v0 
                = (0x000000ffU & vlSelfRef.DwIO);
            __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem0__v0 
                = (0x0000ffffU & (vlSelfRef.main_cpu__DOT__s3 
                                  >> 2U));
            __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem0__v0 = 1U;
        }
        if ((2U & (IData)(vlSelfRef.main_cpu__DOT__s17))) {
            __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem1__v0 
                = (0x000000ffU & (vlSelfRef.DwIO >> 8U));
            __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem1__v0 
                = (0x0000ffffU & (vlSelfRef.main_cpu__DOT__s3 
                                  >> 2U));
            __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem1__v0 = 1U;
        }
        if ((4U & (IData)(vlSelfRef.main_cpu__DOT__s17))) {
            __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem2__v0 
                = (0x000000ffU & (vlSelfRef.DwIO >> 0x10U));
            __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem2__v0 
                = (0x0000ffffU & (vlSelfRef.main_cpu__DOT__s3 
                                  >> 2U));
            __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem2__v0 = 1U;
        }
        if ((8U & (IData)(vlSelfRef.main_cpu__DOT__s17))) {
            __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem3__v0 
                = (vlSelfRef.DwIO >> 0x18U);
            __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem3__v0 
                = (0x0000ffffU & (vlSelfRef.main_cpu__DOT__s3 
                                  >> 2U));
            __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem3__v0 = 1U;
        }
    }
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s3 
        = ((0xff000000U & vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s3) 
           | ((vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem2
               [(0x0000ffffU & (vlSelfRef.main_cpu__DOT__s3 
                                >> 2U))] << 0x00000010U) 
              | ((vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem1
                  [(0x0000ffffU & (vlSelfRef.main_cpu__DOT__s3 
                                   >> 2U))] << 8U) 
                 | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem0
                 [(0x0000ffffU & (vlSelfRef.main_cpu__DOT__s3 
                                  >> 2U))])));
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s4 
        = ((0xff000000U & vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s4) 
           | ((vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem2
               [(0x0000ffffU & (vlSelfRef.main_cpu__DOT__s23 
                                >> 2U))] << 0x00000010U) 
              | ((vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem1
                  [(0x0000ffffU & (vlSelfRef.main_cpu__DOT__s23 
                                   >> 2U))] << 8U) 
                 | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem0
                 [(0x0000ffffU & (vlSelfRef.main_cpu__DOT__s23 
                                  >> 2U))])));
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s3 
        = ((0x00ffffffU & vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s3) 
           | (vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem3
              [(0x0000ffffU & (vlSelfRef.main_cpu__DOT__s3 
                               >> 2U))] << 0x00000018U));
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s4 
        = ((0x00ffffffU & vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s4) 
           | (vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem3
              [(0x0000ffffU & (vlSelfRef.main_cpu__DOT__s23 
                               >> 2U))] << 0x00000018U));
    if (__VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem2__v0) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem2[__VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem2__v0] 
            = __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem2__v0;
    }
    if (__VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem1__v0) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem1[__VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem1__v0] 
            = __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem1__v0;
    }
    if (__VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem0__v0) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem0[__VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem0__v0] 
            = __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem0__v0;
    }
    if (__VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem3__v0) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem3[__VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem3__v0] 
            = __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i11__DOT__mem3__v0;
    }
}

void Vmain_cpu___024root___nba_sequent__TOP__1(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_sequent__TOP__1\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    QData/*32:0*/ main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R_stage1;
    main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R_stage1 = 0;
    QData/*32:0*/ main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R_stage2;
    main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R_stage2 = 0;
    CData/*0:0*/ __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__busy;
    __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__busy = 0;
    CData/*4:0*/ __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__count;
    __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__count = 0;
    IData/*31:0*/ __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__Q;
    __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__Q = 0;
    IData/*31:0*/ __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R;
    __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R = 0;
    CData/*0:0*/ __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__sign_Q;
    __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__sign_Q = 0;
    CData/*0:0*/ __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__sign_R;
    __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__sign_R = 0;
    CData/*0:0*/ __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__div_by_zero;
    __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__div_by_zero = 0;
    CData/*0:0*/ __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__ready_reg;
    __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__ready_reg = 0;
    IData/*31:0*/ __VdlyVal__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0;
    __VdlyVal__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0 = 0;
    CData/*4:0*/ __VdlyDim0__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0;
    __VdlyDim0__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0;
    __VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0 = 0;
    // Body
    __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__busy 
        = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__busy;
    __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__count 
        = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__count;
    __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__sign_Q 
        = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__sign_Q;
    __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__sign_R 
        = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__sign_R;
    __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__div_by_zero 
        = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__div_by_zero;
    __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__ready_reg 
        = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__ready_reg;
    __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R 
        = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R;
    __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__Q 
        = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__Q;
    __VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0 = 0U;
    if ((((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
          >> 1U) & ((IData)(vlSelfRef.main_cpu__DOT____Vcellinp__Registers_i5__EN) 
                    & (0U != (0x0000001fU & (vlSelfRef.main_cpu__DOT__s26 
                                             >> 7U)))))) {
        __VdlyVal__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0 
            = vlSelfRef.main_cpu__DOT__s5;
        __VdlyDim0__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0 
            = (0x0000001fU & (vlSelfRef.main_cpu__DOT__s26 
                              >> 7U));
        __VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0 = 1U;
    }
    if ((((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__is_div) 
          & (~ (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__busy))) 
         & (~ (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__ready_reg)))) {
        __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__busy = 1U;
        __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__count = 0x10U;
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__B 
            = (((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT____Vcellinp__div_inst__is_signed) 
                & (vlSelfRef.main_cpu__DOT__s1 >> 0x1fU))
                ? (- vlSelfRef.main_cpu__DOT__s1) : vlSelfRef.main_cpu__DOT__s1);
        __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__Q 
            = (((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT____Vcellinp__div_inst__is_signed) 
                & (vlSelfRef.main_cpu__DOT__s2 >> 0x1fU))
                ? (- vlSelfRef.main_cpu__DOT__s2) : vlSelfRef.main_cpu__DOT__s2);
        __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R = 0U;
        __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__sign_Q 
            = ((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT____Vcellinp__div_inst__is_signed) 
               & ((vlSelfRef.main_cpu__DOT__s2 ^ vlSelfRef.main_cpu__DOT__s1) 
                  >> 0x1fU));
        __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__sign_R 
            = ((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT____Vcellinp__div_inst__is_signed) 
               & (vlSelfRef.main_cpu__DOT__s2 >> 0x1fU));
        __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__div_by_zero 
            = (0U == vlSelfRef.main_cpu__DOT__s1);
    } else if (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__busy) {
        if ((0U < (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__count))) {
            __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__Q 
                = ((vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__Q 
                    << 2U) | (((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__stage1_sub) 
                               << 1U) | (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__stage2_sub)));
            __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__count 
                = (0x0000001fU & ((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__count) 
                                  - (IData)(1U)));
            __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R 
                = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R_next2;
        } else {
            vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_out 
                = ((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__div_by_zero)
                    ? ((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT____Vcellinp__div_inst__is_rem)
                        ? vlSelfRef.main_cpu__DOT__s2
                        : 0xffffffffU) : ((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT____Vcellinp__div_inst__is_rem)
                                           ? ((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__sign_R)
                                               ? (- vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R)
                                               : vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R)
                                           : ((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__sign_Q)
                                               ? (- vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__Q)
                                               : vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__Q)));
            __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__busy = 0U;
            __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__ready_reg = 1U;
        }
    } else if (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__ready_reg) {
        __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__ready_reg = 0U;
    }
    if (vlSelfRef.main_cpu__DOT____Vcellinp__Registers_i5__EN) {
        vlSelfRef.main_cpu__DOT__s23 = (0xfffffffeU 
                                        & vlSelfRef.main_cpu__DOT__s22);
    }
    if (__VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0) {
        vlSelfRef.main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory[__VdlyDim0__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0] 
            = __VdlyVal__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0;
    }
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__busy 
        = __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__busy;
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__count 
        = __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__count;
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__sign_Q 
        = __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__sign_Q;
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__sign_R 
        = __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__sign_R;
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__div_by_zero 
        = __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__div_by_zero;
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__ready_reg 
        = __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__ready_reg;
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R 
        = __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R;
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__Q 
        = __Vdly__main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__Q;
    main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R_stage1 
        = (((QData)((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R)) 
            << 1U) | (QData)((IData)((vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__Q 
                                      >> 0x0000001fU))));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__stage1_sub 
        = (main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R_stage1 
           >= (QData)((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__B)));
    main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R_stage2 
        = (((QData)((IData)((0x00000001ffffffffULL 
                             & ((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__stage1_sub)
                                 ? (main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R_stage1 
                                    - (QData)((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__B)))
                                 : (QData)((IData)(main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R_stage1)))))) 
            << 1U) | (QData)((IData)((1U & (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__Q 
                                            >> 0x0000001eU)))));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__stage2_sub 
        = (main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R_stage2 
           >= (QData)((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__B)));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R_next2 
        = (IData)((0x00000001ffffffffULL & ((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__stage2_sub)
                                             ? (main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R_stage2 
                                                - (QData)((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__B)))
                                             : (QData)((IData)(main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__R_stage2)))));
}

void Vmain_cpu___024root___nba_comb__TOP__0(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_comb__TOP__0\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ main_cpu__DOT__s10;
    main_cpu__DOT__s10 = 0;
    CData/*7:0*/ main_cpu__DOT__MemoryMapperExp_i0__DOT__s20;
    main_cpu__DOT__MemoryMapperExp_i0__DOT__s20 = 0;
    CData/*5:0*/ main_cpu__DOT__ControlLogic_i3__DOT____Vcellinp__DIG_ROM_64X5_ALUOP_i4__A;
    main_cpu__DOT__ControlLogic_i3__DOT____Vcellinp__DIG_ROM_64X5_ALUOP_i4__A = 0;
    VlWide<3>/*95:0*/ __Vtemp_3;
    VlWide<3>/*95:0*/ __Vtemp_4;
    VlWide<3>/*95:0*/ __Vtemp_6;
    VlWide<3>/*95:0*/ __Vtemp_7;
    VlWide<3>/*95:0*/ __Vtemp_8;
    // Body
    vlSelfRef.main_cpu__DOT__s26 = ((IData)((0x00040000U 
                                             != (0xfffc0000U 
                                                 & vlSelfRef.main_cpu__DOT__s23)))
                                     ? ((0x0130U < 
                                         (0x000007ffU 
                                          & (vlSelfRef.main_cpu__DOT__s23 
                                             >> 2U)))
                                         ? 0U : ((0x0130U 
                                                  >= 
                                                  (0x000001ffU 
                                                   & (vlSelfRef.main_cpu__DOT__s23 
                                                      >> 2U)))
                                                  ? vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom
                                                 [(0x000001ffU 
                                                   & (vlSelfRef.main_cpu__DOT__s23 
                                                      >> 2U))]
                                                  : 0U))
                                     : vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s4);
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0 = (3U 
                                                & (~ 
                                                   (((0U 
                                                      == 
                                                      (3U 
                                                       & (vlSelfRef.main_cpu__DOT__s26 
                                                          >> 0x0000000cU))) 
                                                     << 1U) 
                                                    | (1U 
                                                       & (~ 
                                                          (vlSelfRef.main_cpu__DOT__s26 
                                                           >> 0x0000000eU))))));
    vlSelfRef.main_cpu__DOT__DataController_i1__DOT__s24 
        = ((1U == (3U & (vlSelfRef.main_cpu__DOT__s26 
                         >> 0x0000000cU))) | (0U == 
                                              (3U & 
                                               (vlSelfRef.main_cpu__DOT__s26 
                                                >> 0x0000000cU))));
    vlSelfRef.main_cpu__DOT__s2 = ((0U == (0x0000001fU 
                                           & (vlSelfRef.main_cpu__DOT__s26 
                                              >> 0x0000000fU)))
                                    ? 0U : vlSelfRef.main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory
                                   [(0x0000001fU & 
                                     (vlSelfRef.main_cpu__DOT__s26 
                                      >> 0x0000000fU))]);
    main_cpu__DOT__s10 = ((0U == (0x0000001fU & (vlSelfRef.main_cpu__DOT__s26 
                                                 >> 0x00000014U)))
                           ? 0U : vlSelfRef.main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory
                          [(0x0000001fU & (vlSelfRef.main_cpu__DOT__s26 
                                           >> 0x00000014U))]);
    vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1 
        = ((0x1bU < (0x0000001fU & (vlSelfRef.main_cpu__DOT__s26 
                                    >> 2U))) ? 0U : 
           ((0x1bU >= (0x0000001fU & (vlSelfRef.main_cpu__DOT__s26 
                                      >> 2U))) ? vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_32X13_INSLogic_i0__DOT__my_rom
            [(0x0000001fU & (vlSelfRef.main_cpu__DOT__s26 
                             >> 2U))] : 0U));
    main_cpu__DOT__MemoryMapperExp_i0__DOT__s20 = (0x000000ffU 
                                                   & ((0U 
                                                       == 
                                                       (3U 
                                                        & (vlSelfRef.main_cpu__DOT__s26 
                                                           >> 0x0000000cU)))
                                                       ? main_cpu__DOT__s10
                                                       : 
                                                      (main_cpu__DOT__s10 
                                                       >> 8U)));
    main_cpu__DOT__ControlLogic_i3__DOT____Vcellinp__DIG_ROM_64X5_ALUOP_i4__A 
        = (((1U == (3U & ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                          >> 0x0000000bU))) << 5U) 
           | ((0x0000001cU & (vlSelfRef.main_cpu__DOT__s26 
                              >> 0x0000000aU)) | ((2U 
                                                   & (vlSelfRef.main_cpu__DOT__s26 
                                                      >> 0x0000001dU)) 
                                                  | (1U 
                                                     & (vlSelfRef.main_cpu__DOT__s26 
                                                        >> 0x00000019U)))));
    vlSelfRef.main_cpu__DOT__s20 = ((0x00000400U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                     ? ((0x00000200U 
                                         & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                         ? 0U : ((0x00000100U 
                                                  & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                                  ? 0U
                                                  : 
                                                 ((((0x00000ffeU 
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
                                                           >> 0x00000014U))))))
                                     : ((0x00000200U 
                                         & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                         ? ((0x00000100U 
                                             & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                             ? (0xfffff000U 
                                                & vlSelfRef.main_cpu__DOT__s26)
                                             : (((- (IData)(
                                                            (vlSelfRef.main_cpu__DOT__s26 
                                                             >> 0x0000001fU))) 
                                                 << 0x0000000dU) 
                                                | ((((2U 
                                                      & (vlSelfRef.main_cpu__DOT__s26 
                                                         >> 0x0000001eU)) 
                                                     | (1U 
                                                        & (vlSelfRef.main_cpu__DOT__s26 
                                                           >> 7U))) 
                                                    << 0x0000000bU) 
                                                   | ((0x000007e0U 
                                                       & (vlSelfRef.main_cpu__DOT__s26 
                                                          >> 0x00000014U)) 
                                                      | (0x0000001eU 
                                                         & (vlSelfRef.main_cpu__DOT__s26 
                                                            >> 7U))))))
                                         : ((0x00000100U 
                                             & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                             ? (((- (IData)(
                                                            (vlSelfRef.main_cpu__DOT__s26 
                                                             >> 0x0000001fU))) 
                                                 << 0x0000000cU) 
                                                | ((0x00000fe0U 
                                                    & (vlSelfRef.main_cpu__DOT__s26 
                                                       >> 0x00000014U)) 
                                                   | (0x0000001fU 
                                                      & (vlSelfRef.main_cpu__DOT__s26 
                                                         >> 7U))))
                                             : (((- (IData)(
                                                            (vlSelfRef.main_cpu__DOT__s26 
                                                             >> 0x0000001fU))) 
                                                 << 0x0000000cU) 
                                                | (vlSelfRef.main_cpu__DOT__s26 
                                                   >> 0x00000014U)))));
    vlSelfRef.DwIO = ((((0x0000ff00U & (((1U == (3U 
                                                 & (vlSelfRef.main_cpu__DOT__s26 
                                                    >> 0x0000000cU)))
                                          ? (IData)(main_cpu__DOT__MemoryMapperExp_i0__DOT__s20)
                                          : ((0U == 
                                              (3U & 
                                               (vlSelfRef.main_cpu__DOT__s26 
                                                >> 0x0000000cU)))
                                              ? main_cpu__DOT__s10
                                              : (main_cpu__DOT__s10 
                                                 >> 0x00000018U))) 
                                        << 8U)) | (0x000000ffU 
                                                   & ((1U 
                                                       == 
                                                       (3U 
                                                        & (vlSelfRef.main_cpu__DOT__s26 
                                                           >> 0x0000000cU)))
                                                       ? main_cpu__DOT__s10
                                                       : 
                                                      ((0U 
                                                        == 
                                                        (3U 
                                                         & (vlSelfRef.main_cpu__DOT__s26 
                                                            >> 0x0000000cU)))
                                                        ? main_cpu__DOT__s10
                                                        : 
                                                       (main_cpu__DOT__s10 
                                                        >> 0x00000010U))))) 
                       << 0x00000010U) | (((IData)(main_cpu__DOT__MemoryMapperExp_i0__DOT__s20) 
                                           << 8U) | 
                                          (0x000000ffU 
                                           & main_cpu__DOT__s10)));
    vlSelfRef.main_cpu__DOT__s0 = ((0x00001000U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                    ? ((0x00000800U 
                                        & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                        ? ((0x00002000U 
                                            & vlSelfRef.main_cpu__DOT__s26)
                                            ? 5U : 6U)
                                        : 0U) : ((0x3dU 
                                                  < (IData)(main_cpu__DOT__ControlLogic_i3__DOT____Vcellinp__DIG_ROM_64X5_ALUOP_i4__A))
                                                  ? 0U
                                                  : 
                                                 ((0x3dU 
                                                   >= (IData)(main_cpu__DOT__ControlLogic_i3__DOT____Vcellinp__DIG_ROM_64X5_ALUOP_i4__A))
                                                   ? vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__DIG_ROM_64X5_ALUOP_i4__DOT__my_rom
                                                  [main_cpu__DOT__ControlLogic_i3__DOT____Vcellinp__DIG_ROM_64X5_ALUOP_i4__A]
                                                   : 0U)));
    vlSelfRef.main_cpu__DOT__s21 = (vlSelfRef.main_cpu__DOT__s20 
                                    + vlSelfRef.main_cpu__DOT__s23);
    vlSelfRef.main_cpu__DOT__s1 = ((0x00000020U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                    ? vlSelfRef.main_cpu__DOT__s20
                                    : main_cpu__DOT__s10);
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT____Vcellinp__div_inst__is_signed 
        = ((0x0eU == (IData)(vlSelfRef.main_cpu__DOT__s0)) 
           | (0x10U == (IData)(vlSelfRef.main_cpu__DOT__s0)));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT____Vcellinp__div_inst__is_rem 
        = ((0x10U == (IData)(vlSelfRef.main_cpu__DOT__s0)) 
           | (0x11U == (IData)(vlSelfRef.main_cpu__DOT__s0)));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__is_div = 
        ((0x0eU <= (IData)(vlSelfRef.main_cpu__DOT__s0)) 
         & (0x11U >= (IData)(vlSelfRef.main_cpu__DOT__s0)));
    vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s2 
        = (vlSelfRef.main_cpu__DOT__s2 == vlSelfRef.main_cpu__DOT__s1);
    VL_EXTENDS_WQ(66,33, __Vtemp_3, (((QData)((IData)(
                                                      (((0x0bU 
                                                         == (IData)(vlSelfRef.main_cpu__DOT__s0)) 
                                                        | (0x0dU 
                                                           == (IData)(vlSelfRef.main_cpu__DOT__s0))) 
                                                       & (vlSelfRef.main_cpu__DOT__s2 
                                                          >> 0x0000001fU)))) 
                                      << 0x00000020U) 
                                     | (QData)((IData)(vlSelfRef.main_cpu__DOT__s2))));
    __Vtemp_4[0U] = __Vtemp_3[0U];
    __Vtemp_4[1U] = __Vtemp_3[1U];
    __Vtemp_4[2U] = (3U & __Vtemp_3[2U]);
    VL_EXTENDS_WQ(66,33, __Vtemp_6, (((QData)((IData)(
                                                      ((0x0bU 
                                                        == (IData)(vlSelfRef.main_cpu__DOT__s0)) 
                                                       & (vlSelfRef.main_cpu__DOT__s1 
                                                          >> 0x0000001fU)))) 
                                      << 0x00000020U) 
                                     | (QData)((IData)(vlSelfRef.main_cpu__DOT__s1))));
    __Vtemp_7[0U] = __Vtemp_6[0U];
    __Vtemp_7[1U] = __Vtemp_6[1U];
    __Vtemp_7[2U] = (3U & __Vtemp_6[2U]);
    VL_MULS_WWW(66, __Vtemp_8, __Vtemp_4, __Vtemp_7);
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__prod[0U] 
        = __Vtemp_8[0U];
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__prod[1U] 
        = __Vtemp_8[1U];
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__prod[2U] 
        = (3U & __Vtemp_8[2U]);
    vlSelfRef.main_cpu__DOT____Vcellinp__Registers_i5__EN 
        = (1U & (~ ((~ (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_inst__DOT__ready_reg)) 
                    & (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__is_div))));
    vlSelfRef.main_cpu__DOT__s3 = ((0x00000010U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                    ? ((8U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                        ? 0U : ((4U 
                                                 & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                 ? 0U
                                                 : 
                                                ((2U 
                                                  & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                  ? 0U
                                                  : vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_out)))
                                    : ((8U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                        ? ((4U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                            ? ((2U 
                                                & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                ? vlSelfRef.main_cpu__DOT__ALU_i4__DOT__div_out
                                                : vlSelfRef.main_cpu__DOT__ALU_i4__DOT__prod[1U])
                                            : ((2U 
                                                & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                ? (
                                                   (1U 
                                                    & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                    ? vlSelfRef.main_cpu__DOT__ALU_i4__DOT__prod[1U]
                                                    : vlSelfRef.main_cpu__DOT__ALU_i4__DOT__prod[0U])
                                                : (
                                                   (1U 
                                                    & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                    ? 
                                                   VL_SHIFTRS_III(32,32,5, vlSelfRef.main_cpu__DOT__s2, 
                                                                  (0x0000001fU 
                                                                   & vlSelfRef.main_cpu__DOT__s1))
                                                    : 
                                                   (vlSelfRef.main_cpu__DOT__s2 
                                                    >> 
                                                    (0x0000001fU 
                                                     & vlSelfRef.main_cpu__DOT__s1)))))
                                        : ((4U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                            ? ((2U 
                                                & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                ? (
                                                   (1U 
                                                    & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                    ? 
                                                   (vlSelfRef.main_cpu__DOT__s2 
                                                    << 
                                                    (0x0000001fU 
                                                     & vlSelfRef.main_cpu__DOT__s1))
                                                    : 
                                                   VL_LTS_III(32, vlSelfRef.main_cpu__DOT__s2, vlSelfRef.main_cpu__DOT__s1))
                                                : (
                                                   (1U 
                                                    & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                    ? 
                                                   (vlSelfRef.main_cpu__DOT__s2 
                                                    < vlSelfRef.main_cpu__DOT__s1)
                                                    : 
                                                   (vlSelfRef.main_cpu__DOT__s2 
                                                    ^ vlSelfRef.main_cpu__DOT__s1)))
                                            : ((2U 
                                                & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                ? (
                                                   (1U 
                                                    & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                    ? 
                                                   (vlSelfRef.main_cpu__DOT__s2 
                                                    | vlSelfRef.main_cpu__DOT__s1)
                                                    : 
                                                   (vlSelfRef.main_cpu__DOT__s2 
                                                    & vlSelfRef.main_cpu__DOT__s1))
                                                : (
                                                   (1U 
                                                    & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                                    ? 
                                                   (vlSelfRef.main_cpu__DOT__s2 
                                                    - vlSelfRef.main_cpu__DOT__s1)
                                                    : 
                                                   (vlSelfRef.main_cpu__DOT__s2 
                                                    + vlSelfRef.main_cpu__DOT__s1))))));
}

void Vmain_cpu___024root___nba_comb__TOP__1(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_comb__TOP__1\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ main_cpu__DOT__s11;
    main_cpu__DOT__s11 = 0;
    CData/*0:0*/ main_cpu__DOT____Vcellinp__MemoryMapperExp_i0__We;
    main_cpu__DOT____Vcellinp__MemoryMapperExp_i0__We = 0;
    CData/*3:0*/ main_cpu__DOT__DataController_i1__DOT__s26;
    main_cpu__DOT__DataController_i1__DOT__s26 = 0;
    CData/*0:0*/ __VdfgRegularize_he50b618e_0_4;
    __VdfgRegularize_he50b618e_0_4 = 0;
    // Body
    main_cpu__DOT____Vcellinp__MemoryMapperExp_i0__We 
        = ((IData)(vlSelfRef.main_cpu__DOT____Vcellinp__Registers_i5__EN) 
           & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1));
    vlSelfRef.AddIO = vlSelfRef.main_cpu__DOT__s3;
    vlSelfRef.main_cpu__DOT__s22 = ((0x00000080U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                     ? ((0x00000040U 
                                         & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                         ? ((1U & (
                                                   (0x00004000U 
                                                    & vlSelfRef.main_cpu__DOT__s26)
                                                    ? 
                                                   ((0x00001000U 
                                                     & vlSelfRef.main_cpu__DOT__s26)
                                                     ? 
                                                    (~ vlSelfRef.main_cpu__DOT__s3)
                                                     : vlSelfRef.main_cpu__DOT__s3)
                                                    : 
                                                   ((0x00001000U 
                                                     & vlSelfRef.main_cpu__DOT__s26)
                                                     ? 
                                                    (~ (IData)(vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s2))
                                                     : (IData)(vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s2))))
                                             ? vlSelfRef.main_cpu__DOT__s21
                                             : ((IData)(4U) 
                                                + vlSelfRef.main_cpu__DOT__s23))
                                         : vlSelfRef.main_cpu__DOT__s3)
                                     : ((0x00000040U 
                                         & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                         ? vlSelfRef.main_cpu__DOT__s21
                                         : ((IData)(4U) 
                                            + vlSelfRef.main_cpu__DOT__s23)));
    main_cpu__DOT__DataController_i1__DOT__s26 = ((IData)(vlSelfRef.main_cpu__DOT__DataController_i1__DOT__s24)
                                                   ? 
                                                  (((((IData)(
                                                              ((0x00001000U 
                                                                == 
                                                                (0x00003000U 
                                                                 & vlSelfRef.main_cpu__DOT__s26)) 
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
                                                                   & vlSelfRef.main_cpu__DOT__s26)) 
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
                                                                   & vlSelfRef.main_cpu__DOT__s26)) 
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
    __VdfgRegularize_he50b618e_0_4 = (IData)((0U != 
                                              (0xfff80000U 
                                               & vlSelfRef.main_cpu__DOT__s3)));
    vlSelfRef.main_cpu__DOT__s17 = (((1U == (3U & (vlSelfRef.main_cpu__DOT__s26 
                                                   >> 0x0000000cU))) 
                                     << 5U) | (((0U 
                                                 == 
                                                 (3U 
                                                  & (vlSelfRef.main_cpu__DOT__s26 
                                                     >> 0x0000000cU))) 
                                                << 4U) 
                                               | (IData)(main_cpu__DOT__DataController_i1__DOT__s26)));
    vlSelfRef.__VdfgRegularize_he50b618e_0_5 = (1U 
                                                & ((~ 
                                                    (vlSelfRef.main_cpu__DOT__s3 
                                                     >> 0x00000012U)) 
                                                   | (IData)(__VdfgRegularize_he50b618e_0_4)));
    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s2 
        = ((~ (IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_5)) 
           & (IData)(main_cpu__DOT____Vcellinp__MemoryMapperExp_i0__We));
    vlSelfRef.__VdfgRegularize_he50b618e_0_0 = (1U 
                                                & ((~ 
                                                    ((vlSelfRef.main_cpu__DOT__s3 
                                                      >> 0x00000012U) 
                                                     | (IData)(__VdfgRegularize_he50b618e_0_4))) 
                                                   | (~ (IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_5))));
    vlSelfRef.ReIO = ((~ (IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_0)) 
                      & (4U == (0x001cU & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))));
    vlSelfRef.WeIO = ((- (IData)(((~ (IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_0)) 
                                  & (IData)(main_cpu__DOT____Vcellinp__MemoryMapperExp_i0__We)))) 
                      & (IData)(main_cpu__DOT__DataController_i1__DOT__s26));
    main_cpu__DOT__s11 = ((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_0)
                           ? ((IData)(vlSelfRef.__VdfgRegularize_he50b618e_0_5)
                               ? ((0x0130U < (0x000007ffU 
                                              & (vlSelfRef.main_cpu__DOT__s3 
                                                 >> 2U)))
                                   ? 0U : ((0x0130U 
                                            >= (0x000001ffU 
                                                & (vlSelfRef.main_cpu__DOT__s3 
                                                   >> 2U)))
                                            ? vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom
                                           [(0x000001ffU 
                                             & (vlSelfRef.main_cpu__DOT__s3 
                                                >> 2U))]
                                            : 0U)) : vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s3)
                           : vlSelfRef.DrIO);
    vlSelfRef.main_cpu__DOT__s5 = ((0x00000010U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                    ? ((8U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                        ? 0U : ((4U 
                                                 & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                                 ? 0U
                                                 : vlSelfRef.main_cpu__DOT__s21))
                                    : ((8U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                        ? ((4U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                            ? vlSelfRef.main_cpu__DOT__s20
                                            : ((IData)(4U) 
                                               + vlSelfRef.main_cpu__DOT__s23))
                                        : ((4U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                            ? ((IData)(vlSelfRef.main_cpu__DOT__DataController_i1__DOT__s24)
                                                ? (
                                                   (2U 
                                                    & vlSelfRef.main_cpu__DOT__s3)
                                                    ? 
                                                   ((1U 
                                                     & vlSelfRef.main_cpu__DOT__s3)
                                                     ? 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                      ? 0U
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                       ? 
                                                      VL_SHIFTR_III(32,32,32, main_cpu__DOT__s11, 0x00000018U)
                                                       : 
                                                      (((- (IData)(
                                                                   (main_cpu__DOT__s11 
                                                                    >> 0x0000001fU))) 
                                                        << 8U) 
                                                       | (main_cpu__DOT__s11 
                                                          >> 0x00000018U))))
                                                     : 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                       ? 
                                                      VL_SHIFTR_III(32,32,32, main_cpu__DOT__s11, 0x00000010U)
                                                       : 
                                                      (((- (IData)(
                                                                   (main_cpu__DOT__s11 
                                                                    >> 0x0000001fU))) 
                                                        << 0x00000010U) 
                                                       | (main_cpu__DOT__s11 
                                                          >> 0x00000010U)))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                       ? 
                                                      (0x000000ffU 
                                                       & (main_cpu__DOT__s11 
                                                          >> 0x00000010U))
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (main_cpu__DOT__s11 
                                                                       >> 0x00000017U)))) 
                                                        << 8U) 
                                                       | (0x000000ffU 
                                                          & (main_cpu__DOT__s11 
                                                             >> 0x00000010U))))))
                                                    : 
                                                   ((1U 
                                                     & vlSelfRef.main_cpu__DOT__s3)
                                                     ? 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                       ? 
                                                      (0x0000ffffU 
                                                       & (main_cpu__DOT__s11 
                                                          >> 8U))
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (main_cpu__DOT__s11 
                                                                       >> 0x00000017U)))) 
                                                        << 0x00000010U) 
                                                       | (0x0000ffffU 
                                                          & (main_cpu__DOT__s11 
                                                             >> 8U))))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                       ? 
                                                      (0x000000ffU 
                                                       & (main_cpu__DOT__s11 
                                                          >> 8U))
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (main_cpu__DOT__s11 
                                                                       >> 0x0000000fU)))) 
                                                        << 8U) 
                                                       | (0x000000ffU 
                                                          & (main_cpu__DOT__s11 
                                                             >> 8U)))))
                                                     : 
                                                    ((2U 
                                                      & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                       ? 
                                                      (0x0000ffffU 
                                                       & main_cpu__DOT__s11)
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (main_cpu__DOT__s11 
                                                                       >> 0x0000000fU)))) 
                                                        << 0x00000010U) 
                                                       | (0x0000ffffU 
                                                          & main_cpu__DOT__s11)))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0))
                                                       ? 
                                                      (0x000000ffU 
                                                       & main_cpu__DOT__s11)
                                                       : 
                                                      (((- (IData)(
                                                                   (1U 
                                                                    & (main_cpu__DOT__s11 
                                                                       >> 7U)))) 
                                                        << 8U) 
                                                       | (0x000000ffU 
                                                          & main_cpu__DOT__s11))))))
                                                : main_cpu__DOT__s11)
                                            : vlSelfRef.main_cpu__DOT__s3)));
}

void Vmain_cpu___024root___eval_nba(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___eval_nba\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vmain_cpu___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vmain_cpu___024root___nba_sequent__TOP__1(vlSelf);
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vmain_cpu___024root___nba_comb__TOP__0(vlSelf);
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
    // Body
    Vmain_cpu___024root___eval_triggers_vec__act(vlSelf);
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
            VL_FATAL_MT("main_cpu.v", 769, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 100 tries");
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
            VL_FATAL_MT("main_cpu.v", 769, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vmain_cpu___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("main_cpu.v", 769, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
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
