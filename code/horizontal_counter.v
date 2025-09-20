module horizontal_counter (
    input wire clk,
    input wire reset,
    output reg [10:0] hcount
);

always @(posedge clk or posedge reset) begin
    if (reset)
        hcount <= 0;
    else if (hcount == 1047)
        hcount <= 0;
    else
        hcount <= hcount + 1;
end

endmodule
