#include <functional>
#include "Logger.h"

namespace {
// Functions for simple math operations
int add(int a, int b) {
  LOG("");
  return a + b;
}
int sub(int a, int b) {
  LOG("");
  return a - b;
}
int mul(int a, int b) {
  LOG("");
  return a * b;
}
int divs(int a, int b) {
  LOG("");
  return a / b;
}

void func(int a, int b, const std::function<int(int, int)>& calc) {
  if (!calc) {
    LOG("No function provided");
    return;
  }

  int result = calc(a, b);
  LOG_S(result);
}

void run() {
  func(8, 2, add);
  func(8, 2, sub);
  func(8, 2, mul);
  func(8, 2, divs);
  func(8, 2, [](int a, int b) { return a % b; });  // 0
}
}  // namespace

#include "ExampleRegistry.h"

class Functional : public IExample {
 public:
  std::string group() const override { return "core/function"; }
  std::string name() const override { return "Functional"; }
  std::string description() const override { return "Functional Example"; }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(Functional);
