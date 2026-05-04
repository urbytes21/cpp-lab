#include <optional>
#include "Logger.h"

#include "ExampleRegistry.h"

namespace {
void run() {
  LOG("std::optional Example");
}
}  // namespace

class Optional : public IExample {
  std::string group() const override { return "core/utils"; }
  std::string name() const override { return "std::optional"; }
  std::string description() const override {
    return "The examples for <algorithm> header";
  }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(StdAlgorithm);