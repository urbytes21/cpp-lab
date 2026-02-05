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

struct ThrowNoexceptRunner {
  ThrowNoexceptRunner() { run(); }
};

static ThrowNoexceptRunner autoRunner;