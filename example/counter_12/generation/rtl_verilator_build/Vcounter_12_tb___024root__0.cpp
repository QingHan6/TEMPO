// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcounter_12_tb.h for the primary calling header

#include "Vcounter_12_tb__pch.h"

VlCoroutine Vcounter_12_tb___024root___eval_initial__TOP__Vtiming__0(Vcounter_12_tb___024root* vlSelf);
VlCoroutine Vcounter_12_tb___024root___eval_initial__TOP__Vtiming__1(Vcounter_12_tb___024root* vlSelf);

void Vcounter_12_tb___024root___eval_initial(Vcounter_12_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter_12_tb___024root___eval_initial\n"); );
    Vcounter_12_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vcounter_12_tb___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vcounter_12_tb___024root___eval_initial__TOP__Vtiming__1(vlSelf);
}

VlCoroutine Vcounter_12_tb___024root___eval_initial__TOP__Vtiming__0(Vcounter_12_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter_12_tb___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vcounter_12_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ counter_12_tb__DOT__unnamedblk1_1__DOT____Vrepeat0;
    counter_12_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    IData/*31:0*/ counter_12_tb__DOT__unnamedblk1_2__DOT____Vrepeat1;
    counter_12_tb__DOT__unnamedblk1_2__DOT____Vrepeat1 = 0;
    IData/*31:0*/ counter_12_tb__DOT__unnamedblk1_3__DOT____Vrepeat2;
    counter_12_tb__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    // Body
    vlSelfRef.counter_12_tb__DOT__clk = 0U;
    vlSelfRef.counter_12_tb__DOT__rst_n = 0U;
    vlSelfRef.counter_12_tb__DOT__valid_count = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000004e20ULL, 
                                         nullptr, "generation/rtl_verilator_build/source_1.v", 
                                         23);
    vlSelfRef.counter_12_tb__DOT__rst_n = 1U;
    counter_12_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0x0000000fU;
    while (VL_LTS_III(32, 0U, counter_12_tb__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        vlSelfRef.counter_12_tb__DOT__error = ((0U 
                                                == (IData)(vlSelfRef.counter_12_tb__DOT__out))
                                                ? vlSelfRef.counter_12_tb__DOT__error
                                                : ((IData)(1U) 
                                                   + vlSelfRef.counter_12_tb__DOT__error));
        co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                             nullptr, 
                                             "generation/rtl_verilator_build/source_1.v", 
                                             27);
        counter_12_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (counter_12_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    co_await vlSelfRef.__VdlySched.delay(0x00000000000186a0ULL, 
                                         nullptr, "generation/rtl_verilator_build/source_1.v", 
                                         30);
    vlSelfRef.counter_12_tb__DOT__valid_count = 1U;
    counter_12_tb__DOT__unnamedblk1_2__DOT____Vrepeat1 = 0x0000000bU;
    while (VL_LTS_III(32, 0U, counter_12_tb__DOT__unnamedblk1_2__DOT____Vrepeat1)) {
        vlSelfRef.counter_12_tb__DOT__error = (((IData)(vlSelfRef.counter_12_tb__DOT__out) 
                                                == vlSelfRef.counter_12_tb__DOT__i)
                                                ? vlSelfRef.counter_12_tb__DOT__error
                                                : ((IData)(1U) 
                                                   + vlSelfRef.counter_12_tb__DOT__error));
        vlSelfRef.counter_12_tb__DOT__i = ((IData)(1U) 
                                           + vlSelfRef.counter_12_tb__DOT__i);
        co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                             nullptr, 
                                             "generation/rtl_verilator_build/source_1.v", 
                                             34);
        counter_12_tb__DOT__unnamedblk1_2__DOT____Vrepeat1 
            = (counter_12_tb__DOT__unnamedblk1_2__DOT____Vrepeat1 
               - (IData)(1U));
    }
    vlSelfRef.counter_12_tb__DOT__valid_count = 0U;
    counter_12_tb__DOT__unnamedblk1_3__DOT____Vrepeat2 = 5U;
    while (VL_LTS_III(32, 0U, counter_12_tb__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        vlSelfRef.counter_12_tb__DOT__error = ((0x0bU 
                                                == (IData)(vlSelfRef.counter_12_tb__DOT__out))
                                                ? vlSelfRef.counter_12_tb__DOT__error
                                                : ((IData)(1U) 
                                                   + vlSelfRef.counter_12_tb__DOT__error));
        co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                             nullptr, 
                                             "generation/rtl_verilator_build/source_1.v", 
                                             40);
        counter_12_tb__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (counter_12_tb__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    if ((0U == vlSelfRef.counter_12_tb__DOT__error)) {
        VL_WRITEF_NX("===========Your Design Passed===========\n",0);
    } else {
        VL_WRITEF_NX("===========Failed===========%d\n",1
                     , '~',32,vlSelfRef.counter_12_tb__DOT__error);
    }
    VL_FINISH_MT("generation/rtl_verilator_build/source_1.v", 49, "");
    co_return;
}

VlCoroutine Vcounter_12_tb___024root___eval_initial__TOP__Vtiming__1(Vcounter_12_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter_12_tb___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vcounter_12_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "generation/rtl_verilator_build/source_1.v", 
                                             15);
        vlSelfRef.counter_12_tb__DOT__clk = (1U & (~ (IData)(vlSelfRef.counter_12_tb__DOT__clk)));
    }
    co_return;
}

void Vcounter_12_tb___024root___eval_triggers_vec__act(Vcounter_12_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter_12_tb___024root___eval_triggers_vec__act\n"); );
    Vcounter_12_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                      << 2U) 
                                                     | ((((~ (IData)(vlSelfRef.counter_12_tb__DOT__rst_n)) 
                                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__counter_12_tb__DOT__rst_n__0)) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.counter_12_tb__DOT__clk) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__counter_12_tb__DOT__clk__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__counter_12_tb__DOT__clk__0 
        = vlSelfRef.counter_12_tb__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__counter_12_tb__DOT__rst_n__0 
        = vlSelfRef.counter_12_tb__DOT__rst_n;
}

bool Vcounter_12_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter_12_tb___024root___trigger_anySet__act\n"); );
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

void Vcounter_12_tb___024root___nba_sequent__TOP__0(Vcounter_12_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter_12_tb___024root___nba_sequent__TOP__0\n"); );
    Vcounter_12_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.counter_12_tb__DOT__out = ((IData)(vlSelfRef.counter_12_tb__DOT__rst_n)
                                          ? (0x0000000fU 
                                             & ((IData)(vlSelfRef.counter_12_tb__DOT__valid_count)
                                                 ? 
                                                ((0x0bU 
                                                  == (IData)(vlSelfRef.counter_12_tb__DOT__out))
                                                  ? 0U
                                                  : 
                                                 ((IData)(1U) 
                                                  + (IData)(vlSelfRef.counter_12_tb__DOT__out)))
                                                 : (IData)(vlSelfRef.counter_12_tb__DOT__out)))
                                          : 0U);
}

void Vcounter_12_tb___024root___eval_nba(Vcounter_12_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter_12_tb___024root___eval_nba\n"); );
    Vcounter_12_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.counter_12_tb__DOT__out = ((IData)(vlSelfRef.counter_12_tb__DOT__rst_n)
                                              ? (0x0000000fU 
                                                 & ((IData)(vlSelfRef.counter_12_tb__DOT__valid_count)
                                                     ? 
                                                    ((0x0bU 
                                                      == (IData)(vlSelfRef.counter_12_tb__DOT__out))
                                                      ? 0U
                                                      : 
                                                     ((IData)(1U) 
                                                      + (IData)(vlSelfRef.counter_12_tb__DOT__out)))
                                                     : (IData)(vlSelfRef.counter_12_tb__DOT__out)))
                                              : 0U);
    }
}

void Vcounter_12_tb___024root___timing_resume(Vcounter_12_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter_12_tb___024root___timing_resume\n"); );
    Vcounter_12_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vcounter_12_tb___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter_12_tb___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vcounter_12_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vcounter_12_tb___024root___eval_phase__act(Vcounter_12_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter_12_tb___024root___eval_phase__act\n"); );
    Vcounter_12_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vcounter_12_tb___024root___eval_triggers_vec__act(vlSelf);
    Vcounter_12_tb___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vcounter_12_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vcounter_12_tb___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vcounter_12_tb___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vcounter_12_tb___024root___timing_resume(vlSelf);
    }
    return (__VactExecute);
}

bool Vcounter_12_tb___024root___eval_phase__inact(Vcounter_12_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter_12_tb___024root___eval_phase__inact\n"); );
    Vcounter_12_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("generation/rtl_verilator_build/source_1.v", 2, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vcounter_12_tb___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter_12_tb___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vcounter_12_tb___024root___eval_phase__nba(Vcounter_12_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter_12_tb___024root___eval_phase__nba\n"); );
    Vcounter_12_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vcounter_12_tb___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vcounter_12_tb___024root___eval_nba(vlSelf);
        Vcounter_12_tb___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vcounter_12_tb___024root___eval(Vcounter_12_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter_12_tb___024root___eval\n"); );
    Vcounter_12_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vcounter_12_tb___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("generation/rtl_verilator_build/source_1.v", 2, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("generation/rtl_verilator_build/source_1.v", 2, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 10000 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vcounter_12_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("generation/rtl_verilator_build/source_1.v", 2, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vcounter_12_tb___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vcounter_12_tb___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vcounter_12_tb___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vcounter_12_tb___024root___eval_debug_assertions(Vcounter_12_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcounter_12_tb___024root___eval_debug_assertions\n"); );
    Vcounter_12_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
