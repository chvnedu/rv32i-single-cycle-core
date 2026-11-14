`timescale 1ps/1ps

module tb_alu ();
reg [2:0] alu_control;
reg [31:0] a;
reg [31:0] b;
wire [31:0] result;

alu test1(alu_control,a,b,result);
task check_alu;
        input [2:0] operation;
        input [31:0] operand_a;
        input [31:0] operand_b;
        input [31:0] expected;

        begin
            alu_control = operation;
            a = operand_a;
            b = operand_b;
            #1; 
            if(result !== expected) begin
                $error("Operation %b Failed, Expected %h, got %h", operation, expected, result);
            end else begin
                $display("Operation %b Passed", operation);
            end
        end
    endtask

initial begin
    check_alu(3'b000, 32'd7, 32'd9, 32'd16);
    #5 check_alu(3'b001, 32'd7, 32'd9, 32'hfffffffe);
    #5 check_alu(3'b010, 32'd7, 32'd9, 32'd1);
    #5 check_alu(3'b011, 32'd7, 32'd9, 32'd15);
    #5 check_alu(3'b100, 32'd7, 32'd9, 32'd14);

    #5 check_alu(3'b000, 32'hffffffff, 32'd1, 32'd0);
    #5 check_alu(3'b001, 32'd0, 32'd1, 32'hffffffff);
    #5 check_alu(3'b111, 32'd0, 32'd1, 32'd0);

end

initial begin
    #100 $finish;
end
endmodule