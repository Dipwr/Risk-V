import rv32_pkg::*;

module regfile (
    input logic clk,

    input logic [4:0] rs1,
    input logic [4:0] rs2,
    input logic [4:0] rd,

    input logic we,

    input logic [31:0] dataIn,

    output logic [31:0] rs1O,
    output logic [31:0] rs2O
);
    logic [31:0] regdata [32];

    always_ff @(posedge clk) begin
		if (we && (rd != 5'd0)) begin
			regdata[rd] <= dataIn;
		end
	end

    assign rs1O = (rs1 == 5'd0) ? 32'd0 : regdata[rs1];
    assign rs2O = (rs2 == 5'd0) ? 32'd0 : regdata[rs2];
endmodule