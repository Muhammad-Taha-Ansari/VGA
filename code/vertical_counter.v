module vertical_counter (
    input wire clk,
    input wire reset,
    input wire enable,
    output reg [9:0] vcount
);

always @(posedge clk or posedge reset) begin
    if (reset)
        vcount <= 0;
    else if (enable) begin
        if (vcount == 630)
            vcount <= 0;
        else
            vcount <= vcount + 1;
    end
end

endmodule
