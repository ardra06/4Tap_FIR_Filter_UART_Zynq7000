`timescale 1ns / 1ps

module fir_tb;

reg clk=0;
reg rst;
reg signed [15:0] sample_in;
reg sample_valid;

wire signed [31:0] sample_out;

fir_filter dut(
    .clk(clk),
    .rst(rst),
    .sample_in(sample_in),
    .sample_valid(sample_valid),
    .sample_out(sample_out)
);

always #5 clk=~clk;

initial
begin
    rst=1;
    sample_valid=0;
    sample_in=0;

    #20;

    rst=0;
    sample_valid=1;

    sample_in=10; #10;
    sample_in=20; #10;
    sample_in=30; #10;
    sample_in=40; #10;
    sample_in=50; #10;

    sample_valid=0;
    sample_in=0;

    #50;

    $finish;
end

endmodule
