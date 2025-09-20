module VGA (
    input wire clk,
    input wire reset,
    output wire hsync,
    output wire vsync,
    output wire [3:0] red,
    output wire [3:0] green,
    output wire [3:0] blue
);

wire video_on;
wire [10:0] hcount;
wire [9:0] vcount;

sync_generator sync_gen (
    .clk(clk),
    .reset(reset),
    .hsync(hsync),
    .vsync(vsync),
    .video_on(video_on),
    .hcount(hcount),
    .vcount(vcount)
);

test_pattern pattern_gen (
    .video_on(video_on),
    .hcount(hcount),
    .vcount(vcount),
    .red(red),
    .green(green),
    .blue(blue)
);

endmodule
