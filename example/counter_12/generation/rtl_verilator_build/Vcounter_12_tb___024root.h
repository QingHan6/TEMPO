// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vcounter_12_tb.h for the primary calling header

#ifndef VERILATED_VCOUNTER_12_TB___024ROOT_H_
#define VERILATED_VCOUNTER_12_TB___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vcounter_12_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vcounter_12_tb___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ counter_12_tb__DOT__clk;
    CData/*0:0*/ counter_12_tb__DOT__rst_n;
    CData/*0:0*/ counter_12_tb__DOT__valid_count;
    CData/*3:0*/ counter_12_tb__DOT__out;
    CData/*0:0*/ __Vtrigprevexpr___TOP__counter_12_tb__DOT__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__counter_12_tb__DOT__rst_n__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    IData/*31:0*/ counter_12_tb__DOT__i;
    IData/*31:0*/ counter_12_tb__DOT__error;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlDelayScheduler __VdlySched;

    // INTERNAL VARIABLES
    Vcounter_12_tb__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vcounter_12_tb___024root(Vcounter_12_tb__Syms* symsp, const char* namep);
    ~Vcounter_12_tb___024root();
    VL_UNCOPYABLE(Vcounter_12_tb___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
