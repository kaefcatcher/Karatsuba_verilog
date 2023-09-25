#include <bitset>
#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;


int main() {
  int n;
  cout << "Введите количество разрядов n: ";
  cin >> n;

  int a, b;
  cout << "Введите первое число (в формате двоичного числа): ";
  cin >> a;
  cout << "Введите второе число (в формате двоичного числа): ";
  cin >> b;
  string fn = to_string(a);
  string sn = to_string(b);
  if (n % 2 == 1) {
	cout<<n%2;
    fn.insert(0, 1, '0');
    sn.insert(0, 1, '0');
	n++;
  }
  

  ofstream verilogFile("solution.v");

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

  verilogFile.close();
  ofstream verilogTestFile("testSolution.v");
  verilogTestFile << "module testSolution;\nreg [" << n - 1
                  << ":0] A, B;\nwire [" << 2 * n - 1 << ":0] result;" << endl;
  verilogTestFile << "  solution #(" << n
                  << ") uut (\n.iX(A),\n.iY(B),\n.oO(result)\n);" << endl;
  verilogTestFile
      << "  initial begin\n    #10;\n    A = " << n << "'b" << fn
      << ";\n    B = " << n << "'b" << sn
      << ";\n    #1000;\n    wait(result !== 'bx);\n    $display(\"A = %b, B = "
         "%b, result = %b\", A, B, result);\n    $finish;\n  end\nendmodule"
      << endl;
  verilogTestFile.close();
  return 0;
}
