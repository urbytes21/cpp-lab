#include <iostream>
#include <stdexcept>

namespace {
void errorFnc() {
  throw std::runtime_error("[L] error fnc\n");
}

void run() {
  try {
    try {
      errorFnc();
    } catch (std::exception& e) {
      std::cout << e.what();
      throw std::runtime_error("[M] Middle error \n");
      //   throw;   // rethrow
    }
  } catch (std::exception& e) {
    std::cout << "[H] " << e.what();
    std::cout << "Caught an exception of type: " << typeid(e).name()
              << std::endl;
  }
}
}  // namespace

struct BasicHandleRunner {
  BasicHandleRunner() { run(); }
};

static BasicHandleRunner autoRunner;