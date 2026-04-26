// cppcheck-suppress-file []

// operator()
#include <iostream>
#include "ExampleRegistry.h"

namespace {
#include <cassert>  // for assert()

class Matrix {
 private:
  double m_data_[4][4]{};

 public:
  double& operator()(int row, int col);
  double operator()(int row, int col) const;  // for const objects
};

double& Matrix::operator()(int row, int col) {
  assert(row >= 0 && row < 4);
  assert(col >= 0 && col < 4);

  return m_data_[row][col];
}

double Matrix::operator()(int row, int col) const {
  assert(row >= 0 && row < 4);
  assert(col >= 0 && col < 4);

  return m_data_[row][col];
}

void run() {
  Matrix matrix;
  matrix(1, 2) = 4.5;
  std::cout << matrix(1, 2) << '\n';
}
}  // namespace

class ParenthesisOperator : public IExample {
 public:
  std::string group() const override { return "core/overloading"; }
  std::string name() const override { return "ParenthesisOperator"; }
  std::string description() const override { return ""; }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(ParenthesisOperator, "core/overloading",
                 "ParenthesisOperator");