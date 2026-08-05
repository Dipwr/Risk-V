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
                        ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s12)
                          ? vlSelfRef.DrIO : ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3)
                                               ? (vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom
                                                  [
                                                  (0x000001ffU 
                                                   & (vlSelfRef.AddIO 
                                                      >> 2U))] 
                                                  & (- (IData)(
                                                               ((0x012dU 
                                                                 >= 
                                                                 (0x000001ffU 
                                                                  & (vlSelfRef.AddIO 
                                                                     >> 2U))) 
                                                                & (0x012dU 
                                                                   >= 
                                                                   (0x000007ffU 
                                                                    & (vlSelfRef.AddIO 
                                                                       >> 2U)))))))
                                               : ((
                                                   (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory
                                                             [
                                                             (0x0000ffffU 
                                                              & (vlSelfRef.AddIO 
                                                                 >> 2U))]) 
                                                     << 8U) 
                                                    | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory
                                                    [
                                                    (0x0000ffffU 
                                                     & (vlSelfRef.AddIO 
                                                        >> 2U))]) 
                                                   << 0x00000010U) 
                                                  | (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory
                                                              [
                                                              (0x0000ffffU 
                                                               & (vlSelfRef.AddIO 
                                                                  >> 2U))]) 
                                                      << 8U) 
                                                     | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory
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

void Vmain_cpu___024root___nba_sequent__TOP__0(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_sequent__TOP__0\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0;
    __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 0;
    SData/*15:0*/ __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0;
    __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 0;
    CData/*7:0*/ __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0;
    __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 0;
    SData/*15:0*/ __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0;
    __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 0;
    CData/*7:0*/ __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0;
    __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 0;
    SData/*15:0*/ __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0;
    __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 0;
    CData/*7:0*/ __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0;
    __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 0;
    SData/*15:0*/ __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0;
    __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 0;
    IData/*31:0*/ __VdlyVal__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0;
    __VdlyVal__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0 = 0;
    CData/*4:0*/ __VdlyDim0__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0;
    __VdlyDim0__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0 = 0;
    CData/*0:0*/ __VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0;
    __VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0 = 0;
    // Body
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 0U;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 0U;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 0U;
    __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 0U;
    __VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0 = 0U;
    if ((2U & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__s0))) {
        __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 
            = (0x000000ffU & (vlSelfRef.DwIO >> 8U));
        __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 
            = (0x0000ffffU & (vlSelfRef.AddIO >> 2U));
        __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0 = 1U;
    }
    if ((1U & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__s0))) {
        __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 
            = (0x000000ffU & vlSelfRef.DwIO);
        __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 
            = (0x0000ffffU & (vlSelfRef.AddIO >> 2U));
        __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0 = 1U;
    }
    if ((8U & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__s0))) {
        __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 
            = (vlSelfRef.DwIO >> 0x00000018U);
        __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 
            = (0x0000ffffU & (vlSelfRef.AddIO >> 2U));
        __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0 = 1U;
    }
    if ((4U & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__s0))) {
        __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 
            = (0x000000ffU & (vlSelfRef.DwIO >> 0x00000010U));
        __VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 
            = (0x0000ffffU & (vlSelfRef.AddIO >> 2U));
        __VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0 = 1U;
    }
    if ((((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
          >> 1U) & (0U != (0x0000001fU & (vlSelfRef.main_cpu__DOT__s26 
                                          >> 7U))))) {
        __VdlyVal__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0 
            = ((0x00000010U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                ? ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_7) 
                   & ((- (IData)((1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                           >> 3U))))) 
                      & (- (IData)((1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                             >> 2U)))))))
                : ((8U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                    ? ((4U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                        ? vlSelfRef.main_cpu__DOT__s20
                        : ((IData)(4U) + vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i0__DOT__state))
                    : ((4U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                        ? ((IData)(vlSelfRef.main_cpu__DOT__DataController_i1__DOT__s24)
                            ? ((2U & vlSelfRef.AddIO)
                                ? ((1U & vlSelfRef.AddIO)
                                    ? (((1U & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6))
                                         ? (vlSelfRef.main_cpu__DOT__s11 
                                            >> 0x00000018U)
                                         : (((- (IData)(
                                                        (vlSelfRef.main_cpu__DOT__s11 
                                                         >> 0x0000001fU))) 
                                             << 8U) 
                                            | (vlSelfRef.main_cpu__DOT__s11 
                                               >> 0x00000018U))) 
                                       & (- (IData)(
                                                    (1U 
                                                     & (~ 
                                                        ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6) 
                                                         >> 1U))))))
                                    : ((2U & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6))
                                        ? ((1U & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6))
                                            ? (vlSelfRef.main_cpu__DOT__s11 
                                               >> 0x00000010U)
                                            : (((- (IData)(
                                                           (vlSelfRef.main_cpu__DOT__s11 
                                                            >> 0x0000001fU))) 
                                                << 0x00000010U) 
                                               | (vlSelfRef.main_cpu__DOT__s11 
                                                  >> 0x00000010U)))
                                        : ((((- (IData)(
                                                        (1U 
                                                         & (vlSelfRef.main_cpu__DOT__s11 
                                                            >> 0x00000017U)))) 
                                             & (- (IData)(
                                                          (1U 
                                                           & (~ (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6)))))) 
                                            << 8U) 
                                           | (0x000000ffU 
                                              & (vlSelfRef.main_cpu__DOT__s11 
                                                 >> 0x00000010U)))))
                                : ((1U & vlSelfRef.AddIO)
                                    ? ((2U & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6))
                                        ? ((((- (IData)(
                                                        (1U 
                                                         & (vlSelfRef.main_cpu__DOT__s11 
                                                            >> 0x00000017U)))) 
                                             & (- (IData)(
                                                          (1U 
                                                           & (~ (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6)))))) 
                                            << 0x00000010U) 
                                           | (0x0000ffffU 
                                              & (vlSelfRef.main_cpu__DOT__s11 
                                                 >> 8U)))
                                        : ((((- (IData)(
                                                        (1U 
                                                         & (vlSelfRef.main_cpu__DOT__s11 
                                                            >> 0x0000000fU)))) 
                                             & (- (IData)(
                                                          (1U 
                                                           & (~ (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6)))))) 
                                            << 8U) 
                                           | (0x000000ffU 
                                              & (vlSelfRef.main_cpu__DOT__s11 
                                                 >> 8U))))
                                    : ((((2U & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6))
                                          ? ((0x00ffff00U 
                                              & (((- (IData)(
                                                             (1U 
                                                              & (vlSelfRef.main_cpu__DOT__s11 
                                                                 >> 0x0000000fU)))) 
                                                  & (- (IData)(
                                                               (1U 
                                                                & (~ (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6)))))) 
                                                 << 8U)) 
                                             | (0x000000ffU 
                                                & (vlSelfRef.main_cpu__DOT__s11 
                                                   >> 8U)))
                                          : ((- (IData)(
                                                        (1U 
                                                         & (vlSelfRef.main_cpu__DOT__s11 
                                                            >> 7U)))) 
                                             & (- (IData)(
                                                          (1U 
                                                           & (~ (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6))))))) 
                                        << 8U) | (0x000000ffU 
                                                  & vlSelfRef.main_cpu__DOT__s11))))
                            : vlSelfRef.main_cpu__DOT__s11)
                        : vlSelfRef.AddIO)));
        __VdlyDim0__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0 
            = (0x0000001fU & (vlSelfRef.main_cpu__DOT__s26 
                              >> 7U));
        __VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0 = 1U;
    }
    if (__VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory[__VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0] 
            = __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory__v0;
    }
    if (__VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory[__VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0] 
            = __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory__v0;
    }
    if (__VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory[__VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0] 
            = __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory__v0;
    }
    if (__VdlySet__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0) {
        vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory[__VdlyDim0__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0] 
            = __VdlyVal__main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory__v0;
    }
    if (__VdlySet__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0) {
        vlSelfRef.main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory[__VdlyDim0__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0] 
            = __VdlyVal__main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory__v0;
    }
    vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i0__DOT__state 
        = (((0x00000080U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
             ? ((0x00000040U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                 ? ((1U & ((0x00004000U & vlSelfRef.main_cpu__DOT__s26)
                            ? ((0x00001000U & vlSelfRef.main_cpu__DOT__s26)
                                ? (~ (IData)(vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s4))
                                : (IData)(vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s4))
                            : ((0x00001000U & vlSelfRef.main_cpu__DOT__s26)
                                ? (IData)(vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s3)
                                : (~ (IData)(vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s3)))))
                     ? (IData)((vlSelfRef.__VdfgRegularize_hebeb780c_0_7 
                                >> 1U)) : (IData)((vlSelfRef.__VdfgRegularize_hebeb780c_0_5 
                                                   >> 1U)))
                 : (vlSelfRef.AddIO >> 1U)) : ((0x00000040U 
                                                & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                                ? (IData)(
                                                          (vlSelfRef.__VdfgRegularize_hebeb780c_0_7 
                                                           >> 1U))
                                                : (IData)(
                                                          (vlSelfRef.__VdfgRegularize_hebeb780c_0_5 
                                                           >> 1U)))) 
           << 1U);
    vlSelfRef.__VdfgRegularize_hebeb780c_0_5 = (0x00000001ffffffffULL 
                                                & (4ULL 
                                                   + (QData)((IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i0__DOT__state))));
    vlSelfRef.main_cpu__DOT__s26 = ((IData)((0x00040000U 
                                             != (0xfffc0000U 
                                                 & vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i0__DOT__state)))
                                     ? (vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_INSROM_i3__DOT__my_rom
                                        [(0x000001ffU 
                                          & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i0__DOT__state 
                                             >> 2U))] 
                                        & (- (IData)(
                                                     ((0x012dU 
                                                       >= 
                                                       (0x000001ffU 
                                                        & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i0__DOT__state 
                                                           >> 2U))) 
                                                      & (0x012dU 
                                                         >= 
                                                         (0x000007ffU 
                                                          & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i0__DOT__state 
                                                             >> 2U)))))))
                                     : (((((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory
                                                   [
                                                   (0x0000ffffU 
                                                    & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i0__DOT__state 
                                                       >> 2U))]) 
                                           << 8U) | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory
                                          [(0x0000ffffU 
                                            & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i0__DOT__state 
                                               >> 2U))]) 
                                         << 0x00000010U) 
                                        | (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory
                                                    [
                                                    (0x0000ffffU 
                                                     & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i0__DOT__state 
                                                        >> 2U))]) 
                                            << 8U) 
                                           | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory
                                           [(0x0000ffffU 
                                             & (vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i0__DOT__state 
                                                >> 2U))])));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_6 = (3U 
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
        = ((0U == (3U & (vlSelfRef.main_cpu__DOT__s26 
                         >> 0x0000000cU))) | (1U == 
                                              (3U & 
                                               (vlSelfRef.main_cpu__DOT__s26 
                                                >> 0x0000000cU))));
    vlSelfRef.main_cpu__DOT__s2 = (vlSelfRef.main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory
                                   [(0x0000001fU & 
                                     (vlSelfRef.main_cpu__DOT__s26 
                                      >> 0x0000000fU))] 
                                   & (- (IData)((0U 
                                                 != 
                                                 (0x0000001fU 
                                                  & (vlSelfRef.main_cpu__DOT__s26 
                                                     >> 0x0000000fU))))));
    vlSelfRef.DwIO = (vlSelfRef.main_cpu__DOT__Registers_i5__DOT__DIG_RegisterFile_i0__DOT__memory
                      [(0x0000001fU & (vlSelfRef.main_cpu__DOT__s26 
                                       >> 0x00000014U))] 
                      & (- (IData)((0U != (0x0000001fU 
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
}

extern const VlUnpacked<CData/*3:0*/, 2048> Vmain_cpu__ConstPool__TABLE_h76366c4f_0;

void Vmain_cpu___024root___nba_sequent__TOP__1(Vmain_cpu___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmain_cpu___024root___nba_sequent__TOP__1\n"); );
    Vmain_cpu__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ main_cpu__DOT__s1;
    main_cpu__DOT__s1 = 0;
    CData/*0:0*/ main_cpu__DOT__ALU_i4__DOT__s1;
    main_cpu__DOT__ALU_i4__DOT__s1 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s6;
    main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s6 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s11;
    main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s11 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s13;
    main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s13 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s6;
    main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s6 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s8;
    main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s8 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s12;
    main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s12 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s6;
    main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s6 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s10;
    main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s10 = 0;
    IData/*31:0*/ main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s12;
    main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s12 = 0;
    // Body
    vlSelfRef.main_cpu__DOT__s20 = ((0x00000400U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                                     ? (((((0x00000ffeU 
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
    vlSelfRef.__VdfgRegularize_hebeb780c_0_7 = (0x00000001ffffffffULL 
                                                & ((QData)((IData)(vlSelfRef.main_cpu__DOT__s20)) 
                                                   + (QData)((IData)(vlSelfRef.main_cpu__DOT__ProgramCounter_i10__DOT__DIG_Register_BUS_i0__DOT__state))));
    main_cpu__DOT__s1 = ((0x00000020U & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))
                          ? vlSelfRef.main_cpu__DOT__s20
                          : vlSelfRef.DwIO);
    main_cpu__DOT__ALU_i4__DOT__s1 = ((1U == (IData)(vlSelfRef.main_cpu__DOT__s0)) 
                                      | ((5U == (IData)(vlSelfRef.main_cpu__DOT__s0)) 
                                         | (6U == (IData)(vlSelfRef.main_cpu__DOT__s0))));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0 = ((IData)(main_cpu__DOT__ALU_i4__DOT__s1)
                                                 ? 
                                                (~ main_cpu__DOT__s1)
                                                 : main_cpu__DOT__s1);
    if ((1U & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)) {
        main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s6 
            = (vlSelfRef.main_cpu__DOT__s2 >> 1U);
        main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s6 
            = (vlSelfRef.main_cpu__DOT__s2 << 1U);
    } else {
        main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s6 
            = vlSelfRef.main_cpu__DOT__s2;
        main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s6 
            = vlSelfRef.main_cpu__DOT__s2;
    }
    main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s6 = (
                                                   (0x80000000U 
                                                    & vlSelfRef.main_cpu__DOT__s2) 
                                                   | (0x7fffffffU 
                                                      & ((1U 
                                                          & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)
                                                          ? 
                                                         (vlSelfRef.main_cpu__DOT__s2 
                                                          >> 1U)
                                                          : vlSelfRef.main_cpu__DOT__s2)));
    vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
        = (0x00000001ffffffffULL & ((QData)((IData)(vlSelfRef.main_cpu__DOT__s2)) 
                                    + ((QData)((IData)(main_cpu__DOT__ALU_i4__DOT__s1)) 
                                       + (QData)((IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)))));
    if ((2U & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)) {
        main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s8 
            = (main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s6 
               >> 2U);
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s8 
            = (main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s6 
               << 2U);
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s9 
            = (((- (IData)((vlSelfRef.main_cpu__DOT__s2 
                            >> 0x0000001fU))) << 0x0000001eU) 
               | (main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s6 
                  >> 2U));
    } else {
        main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s8 
            = main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s6;
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s8 
            = main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s6;
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s9 
            = main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s6;
    }
    vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s3 
        = (0U != (3U & ((IData)((vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                 >> 0x0000001eU)) | 
                        ((IData)((vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                  >> 0x0000001cU)) 
                         | ((IData)((vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                     >> 0x0000001aU)) 
                            | ((IData)((vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                        >> 0x00000018U)) 
                               | ((IData)((vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                           >> 0x00000016U)) 
                                  | ((IData)((vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                              >> 0x00000014U)) 
                                     | ((IData)((vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                                 >> 0x00000012U)) 
                                        | ((IData)(
                                                   (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                                    >> 0x00000010U)) 
                                           | ((IData)(
                                                      (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                                       >> 0x0000000eU)) 
                                              | ((IData)(
                                                         (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                                          >> 0x0000000cU)) 
                                                 | ((IData)(
                                                            (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                                             >> 0x0000000aU)) 
                                                    | ((IData)(
                                                               (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                                                >> 8U)) 
                                                       | ((IData)(
                                                                  (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                                                   >> 6U)) 
                                                          | ((IData)(
                                                                     (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                                                      >> 4U)) 
                                                             | ((IData)(
                                                                        (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                                                         >> 2U)) 
                                                                | (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp))))))))))))))))));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_10 = (1U 
                                                 & ((((~ 
                                                       ((IData)(
                                                                (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                                                 >> 0x0000001fU)) 
                                                        | (main_cpu__DOT__s1 
                                                           >> 0x0000001fU))) 
                                                      & (vlSelfRef.main_cpu__DOT__s2 
                                                         >> 0x0000001fU)) 
                                                     | ((~ 
                                                         (vlSelfRef.main_cpu__DOT__s2 
                                                          >> 0x0000001fU)) 
                                                        & ((IData)(
                                                                   (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                                                    >> 0x0000001fU)) 
                                                           & (main_cpu__DOT__s1 
                                                              >> 0x0000001fU)))) 
                                                    ^ (IData)(
                                                              (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                                               >> 0x0000001fU))));
    if ((4U & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)) {
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s10 
            = (main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s8 
               >> 4U);
        main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s10 
            = (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s8 
               << 4U);
        main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s11 
            = (((- (IData)((vlSelfRef.main_cpu__DOT__s2 
                            >> 0x0000001fU))) << 0x0000001cU) 
               | (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s9 
                  >> 4U));
    } else {
        vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s10 
            = main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s8;
        main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s10 
            = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s8;
        main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s11 
            = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s9;
    }
    vlSelfRef.main_cpu__DOT__PcInSelector_i9__DOT__s4 
        = (1U & ((IData)(((6U == (6U & (IData)(vlSelfRef.main_cpu__DOT__s0))) 
                          & (~ (((IData)(vlSelfRef.main_cpu__DOT__s0) 
                                 >> 3U) | (IData)(vlSelfRef.main_cpu__DOT__s0)))))
                  ? (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_10)
                  : (~ (IData)((vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                >> 0x00000020U)))));
    if ((8U & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)) {
        main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s12 
            = (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s10 
               >> 8U);
        main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s12 
            = (main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s10 
               << 8U);
        main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s13 
            = (((- (IData)((vlSelfRef.main_cpu__DOT__s2 
                            >> 0x0000001fU))) << 0x00000018U) 
               | (main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s11 
                  >> 8U));
    } else {
        main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s12 
            = vlSelfRef.main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s10;
        main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s12 
            = main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s10;
        main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s13 
            = main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s11;
    }
    vlSelfRef.AddIO = ((8U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                        ? ((- (IData)((1U & (~ ((IData)(vlSelfRef.main_cpu__DOT__s0) 
                                                >> 1U))))) 
                           & (((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                ? ((0x00000010U & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)
                                    ? (((- (IData)(
                                                   (vlSelfRef.main_cpu__DOT__s2 
                                                    >> 0x0000001fU))) 
                                        << 0x00000010U) 
                                       | (main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s13 
                                          >> 0x00000010U))
                                    : main_cpu__DOT__ALU_i4__DOT__SRA_i5__DOT__s13)
                                : ((0x00000010U & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)
                                    ? (main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s12 
                                       >> 0x00000010U)
                                    : main_cpu__DOT__ALU_i4__DOT__SRL_i4__DOT__s12)) 
                              & (- (IData)((1U & (~ 
                                                  ((IData)(vlSelfRef.main_cpu__DOT__s0) 
                                                   >> 2U)))))))
                        : ((4U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                            ? ((2U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                ? ((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                    ? ((0x00000010U 
                                        & vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0)
                                        ? (main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s12 
                                           << 0x00000010U)
                                        : main_cpu__DOT__ALU_i4__DOT__SLL_i3__DOT__s12)
                                    : (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_10))
                                : ((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                    ? (1U & (~ (IData)(
                                                       (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp 
                                                        >> 0x00000020U))))
                                    : (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0 
                                       ^ vlSelfRef.main_cpu__DOT__s2)))
                            : ((2U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                ? ((1U & (IData)(vlSelfRef.main_cpu__DOT__s0))
                                    ? (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0 
                                       | vlSelfRef.main_cpu__DOT__s2)
                                    : (vlSelfRef.main_cpu__DOT__ALU_i4__DOT__s0 
                                       & vlSelfRef.main_cpu__DOT__s2))
                                : (IData)(vlSelfRef.main_cpu__DOT__ALU_i4__DOT__DIG_Add_i2__DOT__temp))));
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
                {
                    // Inlined CFunc: _nba_sequent__TOP__2
                    vlSelfRef.__VdfgRegularize_hebeb780c_0_3 
                        = (IData)((0x00040000U != (0xfffc0000U 
                                                   & vlSelfRef.AddIO)));
                    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__s0 
                        = (0x0000000fU & ((- (IData)(
                                                     (1U 
                                                      & ((~ (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3)) 
                                                         & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))))) 
                                          & ((((((IData)(
                                                         ((2U 
                                                           == 
                                                           (3U 
                                                            & vlSelfRef.AddIO)) 
                                                          & (0x00001000U 
                                                             == 
                                                             (0x00003000U 
                                                              & vlSelfRef.main_cpu__DOT__s26)))) 
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
                                                                & vlSelfRef.main_cpu__DOT__s26)))) 
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
                                                                & vlSelfRef.main_cpu__DOT__s26)))) 
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
                                                           & (~ (IData)(vlSelfRef.main_cpu__DOT__DataController_i1__DOT__s24))))))));
                    vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s12 
                        = ((0U != (vlSelfRef.AddIO 
                                   >> 0x00000012U)) 
                           & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3));
                    vlSelfRef.WeIO = ((IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1) 
                                      & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s12));
                    vlSelfRef.ReIO = (IData)(((4U == 
                                               (0x001cU 
                                                & (IData)(vlSelfRef.main_cpu__DOT__ControlLogic_i3__DOT__s1))) 
                                              & (IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s12)));
                    vlSelfRef.main_cpu__DOT__s11 = 
                        ((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__s12)
                          ? vlSelfRef.DrIO : ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3)
                                               ? (vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__DIG_ROM_2048X32_RROM_i4__DOT__my_rom
                                                  [
                                                  (0x000001ffU 
                                                   & (vlSelfRef.AddIO 
                                                      >> 2U))] 
                                                  & (- (IData)(
                                                               ((0x012dU 
                                                                 >= 
                                                                 (0x000001ffU 
                                                                  & (vlSelfRef.AddIO 
                                                                     >> 2U))) 
                                                                & (0x012dU 
                                                                   >= 
                                                                   (0x000007ffU 
                                                                    & (vlSelfRef.AddIO 
                                                                       >> 2U)))))))
                                               : ((
                                                   (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i2__DOT__memory
                                                             [
                                                             (0x0000ffffU 
                                                              & (vlSelfRef.AddIO 
                                                                 >> 2U))]) 
                                                     << 8U) 
                                                    | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i1__DOT__memory
                                                    [
                                                    (0x0000ffffU 
                                                     & (vlSelfRef.AddIO 
                                                        >> 2U))]) 
                                                   << 0x00000010U) 
                                                  | (((IData)(vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i4__DOT__memory
                                                              [
                                                              (0x0000ffffU 
                                                               & (vlSelfRef.AddIO 
                                                                  >> 2U))]) 
                                                      << 8U) 
                                                     | vlSelfRef.main_cpu__DOT__MemoryMapperExp_i0__DOT__RAM_256KB_i5__DOT__DIG_RAMDualAccess_i3__DOT__memory
                                                     [
                                                     (0x0000ffffU 
                                                      & (vlSelfRef.AddIO 
                                                         >> 2U))]))));
                }
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
            VL_FATAL_MT("main_cpu.v", 2205, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 10000 tries");
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
            VL_FATAL_MT("main_cpu.v", 2205, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vmain_cpu___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("main_cpu.v", 2205, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
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
