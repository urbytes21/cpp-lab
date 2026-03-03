#include <iomanip>
#include <iostream>
#include "ExampleRegistry.h"

namespace {
void run() {
  std::ios oldState(nullptr);
  oldState.copyfmt(std::cout);  // Save state

  // std::ios::boolalpha / noboolanpha
  std::cout << true << ' ' << false << '\n';  // 0
  std::cout.setf(std::ios::boolalpha);
  std::cout << false << ' ' << true << '\n';  // true false

  // std::ios::showpos / noshowpos
  std::cout << 5 << ' ' << -5 << '\n';  // 5 -5
  std::cout.setf(std::ios::boolalpha);
  std::cout << 5 << ' ' << -5 << '\n';  // +5 -5

  // std::ios::upercase / no
  std::cout << 12345678.9 << '\n';  // 1.23457e+07
  std::cout.setf(std::ios::uppercase);
  std::cout << 12345678.9 << '\n';  // 1.23457E+07

  // std::ios::basefield
  // std::ios::dec
  // std::ios::hex
  // std::ios::oct
  std::cout << 11 << '\n';  // 11
  std::cout.setf(std::ios::hex, std::ios::basefield);
  std::cout << 11 << '\n';  // B

  // std::fixed - use dec notation
  std::cout << std::fixed << '\n';
  std::cout << std::setprecision(5) << 123.456 << '\n';  // 123.45600

  // std::scientific
  std::cout << std::scientific << '\n';
  std::cout << std::setprecision(5) << 123.456 << '\n';  // 1.23456e+002

  // reset ========================================================
  std::cout.copyfmt(oldState);  // Restore state

  // std::setw() - set the filed width for input and output
  // std::left/right/internal - left/right justifies - Left-justifies the sign of the number, and right-justifies the value
  std::cout << -12345 << '\n';
  std::cout << std::setw(10) << -12345 << '\n';
  std::cout << std::setw(10) << std::internal << -12345 << '\n';

  // std::fill(char) set the fill char
  std::cout.fill('*');
  std::cout << std::setw(10) << std::internal << -12345 << '\n';

  std::cout.copyfmt(oldState);  // Restore state
}
}  // namespace

class OutputFormatting : public IExample {
 public:
  std::string group() const override { return "core/filehandle"; }
  std::string name() const override { return "OutputFormatting"; }
  std::string description() const override { return ""; }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(OutputFormatting, "core/filehandle", "OutputFormatting");