module test_pattern (
    input wire video_on,
    input wire [10:0] hcount,
    input wire [9:0] vcount,
    output reg [3:0] red,
    output reg [3:0] green,
    output reg [3:0] blue
);

always @(*) begin
    if (video_on) begin
        if (hcount < 267) begin
            red = 4'hF;
            green = 0;
            blue = 0;
        end else if (hcount < 534) begin
            red = 0;
            green = 4'hF;
            blue = 0;
        end else begin
            red = 0;
            green = 0;
            blue = 4'hF;
        end
    end else begin
        red = 0;
        green = 0;
        blue = 0;
    end
end

endmodule
