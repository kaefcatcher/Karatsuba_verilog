module multiply #(parameter n = 8) (
  input [n-1:0] A,
  input [n-1:0] B,
  output [2*n-1:0] result
);

  wire [2*n-1:0] product; // Создаем сигнал для хранения результата
  //assign result = 0;
  //assign product = 0; // Инициализируем product нулями

  // Генерируем сумму произведений
  genvar i;
  generate
    for (i = 0; i < n; i = i + 1) begin : mult_gen
      wire [2*n-1:0] partial_product;
      assign partial_product = (A[i] == 1'b1) ? (B << i) : 0;
      assign product = product + partial_product;
    end
  endgenerate
    // assign product = A * B;
  // Преобразование результата в соответствующую разрядность
  assign result = product;

endmodule


