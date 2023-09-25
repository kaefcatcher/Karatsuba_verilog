module multiply #(parameter n = 8)(
  input  wire [n-1:0] iX,
  input  wire [n-1:0] iY,
  output wire [2*n-1:0] oO
);



wire [n/2-1:0] X_hi, X_lo;
wire [n/2-1:0] Y_hi, Y_lo;

assign {X_hi, X_lo} = iX;
assign {Y_hi, Y_lo} = iY;

wire [n/2*2-1:0] p;
wire [n/2*2-1:0] q;
wire [n/2:0]     r;
wire [n/2:0]     s;
assign p = X_hi * Y_hi;
assign q = X_lo * Y_lo;
assign r = X_hi + X_lo;
assign s = Y_hi + Y_lo;

wire [n/2*2:0]   u;
assign u = p + q;

wire [n+1:0]      t;
wire r_hi, s_hi;
wire [n/2-1:0]   r_lo, s_lo;

assign {r_hi, r_lo} = r;
assign {s_hi, s_lo} = s;

wire [n-1:0] t_s;

assign t_s = r_lo * s_lo;
assign t = ((r_hi & s_hi) << n) + ((r_hi * s_lo + s_hi * r_lo) << n/2) + t_s;

assign oO = (p << n) + ((t - u) << n/2) + q;

endmodule
