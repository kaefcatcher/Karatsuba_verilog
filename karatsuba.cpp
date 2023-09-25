#include <bitset>
#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;

int makeEqualLength(string &str1, string &str2) {
  int len1 = str1.size();
  int len2 = str2.size();
  if (len1 < len2) {
    for (int i = 0; i < len2 - len1; i++)
      str1 = '0' + str1;
    return len2;
  } else if (len1 > len2) {
    for (int i = 0; i < len1 - len2; i++)
      str2 = '0' + str2;
  }
  return len1;
}

string addBitStrings(string first, string second) {
  string result;

  int length = makeEqualLength(first, second);
  int carry = 0;

  for (int i = length - 1; i >= 0; i--) {
    int firstBit = first.at(i) - '0';
    int secondBit = second.at(i) - '0';

    int sum = (firstBit ^ secondBit ^ carry) + '0';

    result = (char)sum + result;

    carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry);
  }

  if (carry)
    result = '1' + result;

  return result;
}

int multiplyiSingleBit(string a, string b) {
  return (a[0] - '0') * (b[0] - '0');
}

long int multiply(string X, string Y) {

  int n = makeEqualLength(X, Y);

  if (n == 0)
    return 0;
  if (n == 1)
    return multiplyiSingleBit(X, Y);

  int fh = n / 2;
  int sh = (n - fh);

  string Xl = X.substr(0, fh);
  string Xr = X.substr(fh, sh);

  string Yl = Y.substr(0, fh);
  string Yr = Y.substr(fh, sh);

  long int P1 = multiply(Xl, Yl);
  long int P2 = multiply(Xr, Yr);
  long int P3 = multiply(addBitStrings(Xl, Xr), addBitStrings(Yl, Yr));

  return P1 * (1 << (2 * sh)) + (P3 - P1 - P2) * (1 << sh) + P2;
}

int main() {
  int n;
  cout << "Введите количество разрядов n: ";
  cin >> n;

  int a, b;
  cout << "Введите первое число (в формате двоичного числа): ";
  cin >> a;
  cout << "Введите второе число (в формате двоичного числа): ";
  cin >> b;

  // string binary_a = bitset<32>(a).to_string().substr(32 - n, n);
  // string binary_b = bitset<32>(b).to_string().substr(32 - n, n);

  // Создаем и открываем файл solution.v для записи
  ofstream verilogFile("solution.v");

  // Пишем Verilog код в файл
  verilogFile << "module solution(" << endl;
  verilogFile << "input  wire [" << n - 1 << ":0] iX," << endl;
  verilogFile << "input  wire [" << n - 1 << ":0] iY," << endl;
  verilogFile << "output  wire [" << 2 * n - 1 << ":0] oO" << endl;
  verilogFile << ");" << endl;
  verilogFile << "wire [" << n / 2 - 1 << ":0] X_hi, X_lo;\nwire [" << n / 2 - 1
              << ":0] Y_hi, Y_lo;" << endl;
  verilogFile << "assign {X_hi, X_lo} = iX;\nassign {Y_hi, Y_lo} = iY;" << endl;
  verilogFile << "wire [" << n / 2 * 2 - 1 << ":0] p;\nwire [" << n / 2 * 2 - 1
              << ":0] q;\nwire [" << n / 2 << ":0] r;\nwire [" << n / 2
              << ":0] s;" << endl;
  verilogFile << "assign p = X_hi * Y_hi;\nassign q = X_lo * Y_lo;\nassign r = "
                 "X_hi + X_lo;\nassign s = Y_hi + Y_lo;"
              << endl;
  verilogFile << "wire [" << n << ":0]   u;" << endl;
  verilogFile << "assign u = p + q;" << endl;
  verilogFile << "wire [" << n + 1 << ":0] t;\nwire r_hi, s_hi;\nwire ["
              << n / 2 - 1 << ":0] r_lo, s_lo;" << endl;
  verilogFile << "assign {r_hi, r_lo} = r;\nassign {s_hi, s_lo} = s;" << endl;
  verilogFile << "wire [" << n - 1 << ":0] t_s;" << endl;
  verilogFile << "assign t_s = r_lo * s_lo;\nassign t = ((r_hi & s_hi) << " << n
              << ") + ((r_hi * s_lo + s_hi * r_lo) << " << n / 2
              << ") + t_s;\nassign oO = (p << " << n << ") + ((t - u) << "
              << n / 2 << ") + q;" << endl;
  verilogFile << "endmodule" << endl;
  // Закрываем файл
  verilogFile.close();
  ofstream verilogTestFile("testSolution.v");
  verilogTestFile << "module testSolution;\nreg [" << n - 1
                  << ":0] A, B;\nwire [" << 2 * n - 1 << ":0] result;" << endl;
  verilogTestFile << "  solution #(" << n
                  << ") uut (\n.iX(A),\n.iY(B),\n.oO(result)\n);" << endl;
  verilogTestFile
      << "  initial begin\n    #10;\n    A = " << n << "'b" << a
      << ";\n    B = " << n << "'b" << b
      << ";\n    #1000;\n    wait(result !== 'bx);\n    $display(\"A = %b, B = "
         "%b, result = %b\", A, B, result);\n    $finish;\n  end\nendmodule"
      << endl;
  verilogTestFile.close();
  return 0;
}
