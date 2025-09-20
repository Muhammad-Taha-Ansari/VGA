module sync_generator (
    input wire clk,
    input wire reset,
    output wire hsync,
    output wire vsync,
    output wire video_on,
    output wire [10:0] hcount,
    output wire [9:0] vcount
);

wire h_end;
wire v_en;

// horizontal counter
horizontal_counter h_counter (
    .clk(clk),
    .reset(reset),
    .hcount(hcount)
);

assign h_end = (hcount == 1047);

// vertical counter
vertical_counter v_counter (
    .clk(clk),
    .reset(reset),
    .enable(h_end),
    .vcount(vcount)
);

// hsync: positive polarity
assign hsync = (hcount >= 832 && hcount < 896);
// vsync: positive polarity
assign vsync = (vcount >= 601 && vcount < 604);

// Video active region
assign video_on = (hcount < 800) && (vcount < 600);

endmodule
