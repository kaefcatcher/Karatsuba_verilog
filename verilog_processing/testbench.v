module testbench;
  reg [3:0] A, B;
  wire [7:0] result;

  // Подключите ваш модуль multiply здесь
  multiply #(4) uut (
    .iX(A),
    .iY(B),
    .oO(result)
  );

  initial begin
    // Задержка времени для инициализации входов
    #10;

    // Инициализируйте входы A и B здесь
    A = 4'b0101;
    B = 4'b1100;

    // Задержка времени для выполнения умножения
    #1000; // Увеличьте задержку

    // Ожидание завершения симуляции
    wait(result !== 'bx);

    $display("A = %b, B = %b, result = %b", A, B, result);
    $finish;
  end
endmodule
