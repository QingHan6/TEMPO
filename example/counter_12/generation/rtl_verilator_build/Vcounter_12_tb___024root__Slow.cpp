// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcounter_12_tb.h for the primary calling header

#include "Vcounter_12_tb__pch.h"

void Vcounter_12_tb___024root___ctor_var_reset(Vcounter_12_tb___024root* vlSelf);

Vcounter_12_tb___024root::Vcounter_12_tb___024root(Vcounter_12_tb__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vcounter_12_tb___024root___ctor_var_reset(this);
}

void Vcounter_12_tb___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vcounter_12_tb___024root::~Vcounter_12_tb___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
