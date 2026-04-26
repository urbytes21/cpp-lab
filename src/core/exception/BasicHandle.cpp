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
      throw std::runtime_error(
          "[M] Middle error \n");  // use as custom exception
      //   throw;   // rethrow
    }
  } catch (std::exception& e) {
    std::cout << "[H] " << e.what();
    std::cout << "Caught an exception of type: " << typeid(e).name()
              << std::endl;
  }
}
}  // namespace

#include "ExampleRegistry.h"

class BasicHandle : public IExample {
 public:
  std::string group() const override { return "core/exception"; }
  std::string name() const override { return "BasicHandle"; }
  std::string description() const override {
    return "Basic Expception Handle Example";
  }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(BasicHandle, "core/exception", "BasicHandle");