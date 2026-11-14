module alu (
    input [2:0] alu_control,
    input [31:0] a, 
    input [31:0] b, 
    output reg [31:0] result
);
always@(*) begin
    case (alu_control)
    3'b000: begin
        result = a + b;
    end
    3'b001: begin
        result = a - b;
    end
    3'b010: begin
        result = a & b;
    end
    3'b011: begin
        result = a | b;
    end
    3'b100: begin
        result = a ^ b;
    end
    default: result = 32'd0;
    endcase
end

endmodule