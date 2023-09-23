// testbench.v
module testbench;
  reg [7:0] A, B;
  wire [15:0] result;

  // Подключите ваш модуль multiply здесь
  multiply #(8) uut (
    .A(A),
    .B(B),
    .result(result)
  );

  initial begin
    // Задержка времени для инициализации входов
    #10;

    // Инициализируйте входы A и B здесь
    A = 8'b01010101;
    B = 8'b11001100;

    // Задержка времени для выполнения умножения
    #1000; // Увеличьте задержку

    // Ожидание завершения симуляции
    wait(result !== 'bx);

    $display("A = %b, B = %b, result = %b", A, B, result);
    $finish;
  end
endmodule
