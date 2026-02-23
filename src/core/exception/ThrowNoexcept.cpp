#include <iostream>
#include <stdexcept>

namespace {

void errorFnc() {
  throw std::runtime_error("errorFnc\n");
}

// void noExpectExcpt() throw() {
void noExpectExcpt() noexcept {
  try {
    errorFnc();
  } catch (std::exception& e) {
    std::cout << typeid(e).name() << " " << e.what();
  }
}

void expectExcpt() noexcept(false) {
  try {
    errorFnc();
  } catch (std::exception& e) {
    std::cout << typeid(e).name() << " " << e.what();
    throw;
  }
}

void run() {
  noExpectExcpt();

  std::set_terminate([]() { exit(-1); });

  // expectExcpt(); terminated program when got unhandle exception
}
}  // namespace

#include "ExampleRegistry.h"

class ThrowNoexcept : public IExample {
 public:
  std::string group() const override { return "core/exception"; }
  std::string name() const override { return "ThrowNoexcept"; }
  std::string description() const override {
    return "Exception throw/noexcept Example";
  }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(ThrowNoexcept, "core/exception", "ThrowNoexcept");