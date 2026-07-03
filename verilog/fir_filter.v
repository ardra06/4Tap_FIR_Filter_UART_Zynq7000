`timescale 1ns / 1ps

module fir_filter(
    input clk,
    input rst,
    input signed [15:0] sample_in,
    input sample_valid,
    output reg signed [31:0] sample_out
);

reg signed [15:0] x0,x1,x2,x3;

always @(posedge clk)
begin
    if(rst)
    begin
        x0<=0;
        x1<=0;
        x2<=0;
        x3<=0;
        sample_out<=0;
    end
    else if(sample_valid)
    begin
        x3<=x2;
        x2<=x1;
        x1<=x0;
        x0<=sample_in;

        sample_out <=
            x0 +
            (x1<<<1) +
            (x2<<<1) +
            x3;
    end
end

endmodule
