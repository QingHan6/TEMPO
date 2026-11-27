#include <ap_int.h>

namespace {
constexpr int hls_clog2(int value) {
    int result = 0;
    for (int current = value - 1; current > 0; current >>= 1) ++result;
    return result;
}

constexpr int hls_width(int value) {
    return value > 0 ? value : 1;
}

template<int W, typename T>
inline ap_uint<W> hls_trunc(T value) {
    return ap_uint<W>(value);
}

template<int W, typename C, typename A, typename B>
inline ap_uint<W> hls_mux(C cond, A a, B b) {
    return cond ? ap_uint<W>(a) : ap_uint<W>(b);
}

template<int N, int W>
inline ap_uint<(N > 0 ? N * W : W)> hls_replicate(ap_uint<W> value) {
    ap_uint<(N > 0 ? N * W : W)> result = 0;
    for (int i = 0; i < (N > 0 ? N : 0); ++i) {
        result.range((i + 1) * W - 1, i * W) = value;
    }
    return result;
}

template<int W>
inline ap_int<W> hls_as_signed(ap_uint<W> value) {
    return ap_int<W>(value);
}

template<int W>
inline ap_int<W> hls_as_signed(ap_int<W> value) {
    return value;
}

template<int W>
inline ap_uint<W> hls_as_unsigned(ap_uint<W> value) {
    return value;
}

template<int W>
inline ap_uint<W> hls_as_unsigned(ap_int<W> value) {
    return ap_uint<W>(value);
}
}

void counter_12(
    ap_uint<1> rst_n,
    ap_uint<1> valid_count,
    ap_uint<4> &out
) {
    #pragma HLS interface ap_ctrl_none port=return
    #pragma HLS interface ap_none port=rst_n
    #pragma HLS interface ap_none port=valid_count
    #pragma HLS interface ap_none port=out
    // IR timing contract encoded into HLS pragmas below:
    //   - one top-function invocation == one active clock cycle
    //   - multi-cycle IR pipelines are explicit static registers,
    //     not extra HLS schedule stages
    // clock_domain clk: posedge implicit ap_clk, reset=rst_n (asynchronous/active_low)
    // sequential transition.latency values present: [0, 1]
    // Lock schedule to IR cycle semantics (no tool-inserted flops).
    #pragma HLS pipeline II=1
    #pragma HLS latency min=0 max=0
    // One invocation models one active clock cycle.
    // Emit registered outputs from Q before state<=next updates.
    static ap_uint<4> __state_out = hls_trunc<4>(ap_uint<4>(0b0000));
    #pragma HLS reset variable=__state_out
    #pragma HLS dependence variable=__state_out inter false

    out = __state_out;

    if (!rst_n) {
        __state_out = hls_trunc<4>(ap_uint<4>(0b0000));
    } else {
        ap_uint<4> __next_out = __state_out;

        if (!rst_n) {
            __next_out = hls_trunc<4>(ap_uint<4>(0b0000));
        }
        else if (rst_n) {
            __next_out = hls_mux<4>(valid_count, hls_mux<4>((__state_out == ap_uint<4>(11)), hls_trunc<4>(ap_uint<4>(0b0000)), hls_trunc<4>(__state_out + ap_uint<1>(0b1))), hls_trunc<4>(__state_out));
        }

        __state_out = __next_out;
    }

}
