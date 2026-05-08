#include <iomanip>
#include <iostream>
#include "ExampleRegistry.h"

namespace {
void run() {
  std::ios old_state(nullptr);
  old_state.copyfmt(std::cout);  // Save state

  // std::ios::boolalpha / noboolanpha
  std::cout << "[boolalpha]\n";
  std::cout << true << ' ' << false << '\n';  // 0
  std::cout.setf(std::ios::boolalpha);
  std::cout << false << ' ' << true << '\n';  // true false

  // std::ios::showpos / noshowpos
  std::cout << "\n[showpos]\n";
  std::cout << 5 << ' ' << -5 << '\n';  // 5 -5
  std::cout.setf(std::ios::boolalpha);
  std::cout << 5 << ' ' << -5 << '\n';  // +5 -5

  // std::ios::upercase / no
  std::cout << "\n[uppercase]\n";
  std::cout << 12345678.9 << '\n';  // 1.23457e+07
  std::cout.setf(std::ios::uppercase);
  std::cout << 12345678.9 << '\n';  // 1.23457E+07

  // std::ios::basefield
  // std::ios::dec
  // std::ios::hex
  // std::ios::oct
  std::cout << "\n[base: dec / hex / oct]\n";
  std::cout << 11 << '\n';  // 11
  std::cout.setf(std::ios::hex, std::ios::basefield);
  std::cout << 11 << '\n';  // B

  // std::fixed - use dec notation
  std::cout << "\n[fixed vs scientific]\n";
  std::cout << std::fixed << '\n';
  std::cout << std::setprecision(5) << 123.456 << '\n';  // 123.45600

  // std::scientific
  std::cout << std::scientific << '\n';
  std::cout << std::setprecision(5) << 123.456 << '\n';  // 1.23456e+002

  // reset ========================================================
  std::cout.copyfmt(old_state);  // Restore state

  // std::setw() - set the filed width for input and output
  // std::left/right/internal - left/right justifies - Left-justifies the sign of the number, and right-justifies the value
  std::cout << "\n[width & alignment]\n";
  std::cout << "|" << -12345 << "|\n";
  std::cout << "|" << std::setw(10) << -12345 << "|\n";               // right
  std::cout << "|" << std::setw(10) << std::left << -12345 << "|\n";  // left
  std::cout << "|" << std::setw(10) << std::internal << -12345 << "|\n";  // internal

  // std::fill(char) set the fill char
  std::cout << "\n[fill]\n";
  std::cout.fill('*');
  std::cout << std::setw(10) << std::internal << -12345 << '\n';

  std::cout.copyfmt(old_state);  // Restore state
}
}  // namespace

class OutputFormatting : public IExample {
 public:
  std::string group() const override { return "core/filehandle"; }
  std::string name() const override { return "OutputFormatting"; }
  std::string description() const override { return ""; }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(OutputFormatting);