// Generated deterministically from Hardware-aware Petri Net IR.
// Do not edit generated RTL; edit the IR/specification instead.
module counter_12 (
    input rst_n,
    input clk,
    input valid_count,
    output reg [3:0] out
);

reg [3:0] __pn_next_out;

always @* begin
    __pn_next_out = out;
    if (!rst_n) begin
        __pn_next_out = 4'b0000;
    end
    else if (rst_n) begin
        __pn_next_out = valid_count ? ((out == 4'd11) ? 4'b0000 : out + 1'b1) : out;
    end
end

// Sequential process: counter_ctrl
always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        out <= 4'b0000;
    end else begin
        out <= __pn_next_out;
    end
end

endmodule
