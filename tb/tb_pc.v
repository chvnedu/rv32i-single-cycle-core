`timescale 1ps/1ps
module tb_pc();
reg clk;
reg reset;
wire [31:0] pc_out;
pc test1(.clk(clk), .reset(reset), .pc_out(pc_out));

initial begin
    clk = 1'b0;
    forever begin
        #5 clk = ~clk;
    end
end

initial begin
    reset = 1'b1;
    #10 reset = 1'b0;

    wait(pc_out == 32'd16) begin
        #2 reset = 1'b1;
        #10 reset = 1'b0;
    end

end

initial begin
    #120 $finish;
end
endmodule