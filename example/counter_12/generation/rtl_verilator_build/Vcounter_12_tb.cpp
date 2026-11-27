// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vcounter_12_tb__pch.h"

//============================================================
// Constructors

Vcounter_12_tb::Vcounter_12_tb(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vcounter_12_tb__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vcounter_12_tb::Vcounter_12_tb(const char* _vcname__)
    : Vcounter_12_tb(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vcounter_12_tb::~Vcounter_12_tb() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vcounter_12_tb___024root___eval_debug_assertions(Vcounter_12_tb___024root* vlSelf);
#endif  // VL_DEBUG
void Vcounter_12_tb___024root___eval_static(Vcounter_12_tb___024root* vlSelf);
void Vcounter_12_tb___024root___eval_initial(Vcounter_12_tb___024root* vlSelf);
void Vcounter_12_tb___024root___eval_settle(Vcounter_12_tb___024root* vlSelf);
void Vcounter_12_tb___024root___eval(Vcounter_12_tb___024root* vlSelf);

void Vcounter_12_tb::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vcounter_12_tb::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vcounter_12_tb___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vcounter_12_tb___024root___eval_static(&(vlSymsp->TOP));
        Vcounter_12_tb___024root___eval_initial(&(vlSymsp->TOP));
        Vcounter_12_tb___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vcounter_12_tb___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vcounter_12_tb::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vcounter_12_tb::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vcounter_12_tb::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vcounter_12_tb___024root___eval_final(Vcounter_12_tb___024root* vlSelf);

VL_ATTR_COLD void Vcounter_12_tb::final() {
    contextp()->executingFinal(true);
    Vcounter_12_tb___024root___eval_final(&(vlSymsp->TOP));
    contextp()->executingFinal(false);
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vcounter_12_tb::hierName() const { return vlSymsp->name(); }
const char* Vcounter_12_tb::modelName() const { return "Vcounter_12_tb"; }
unsigned Vcounter_12_tb::threads() const { return 1; }
void Vcounter_12_tb::prepareClone() const { contextp()->prepareClone(); }
void Vcounter_12_tb::atClone() const {
    contextp()->threadPoolpOnClone();
}
