// cppcheck-suppress-file []

// operator()

#include <iostream>
#include "ExampleRegistry.h"
#include "Logger.h"

namespace {
#include <cassert>  // for assert()

struct Linear {
  double a, b;

  double operator()(double x) const {
    LOG("");
    return a * x + b;
  }
};

void run() {
  Linear f{2, 1};  // Represents function 2x + 1.
  double f_0 = f(0);
  LOG_S(f_0);
}
}  // namespace

class FunctionCallOperator : public IExample {
 public:
  std::string group() const override { return "core/overloading_operator"; }
  std::string name() const override { return "FunctionCallOperator"; }
  std::string description() const override { return ""; }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(FunctionCallOperator);