#include <algorithm>
#include <iostream>

#include "ExampleRegistry.h"

namespace FindIfExample {
void run() {
  std::cout << "std::find_if example\n";
  std::vector<int> v{1, 2, 3, 4, 5};
  auto it = std::find_if(v.begin(), v.end(), [](int i) { return i % 2 == 0; });
  if (it != v.end()) {
    std::cout << "First even number: " << *it << '\n';
  } else {
    std::cout << "No even number found\n";
  }

  std::cout << "std::find_if_not example\n";
  auto it_not =
      std::find_if_not(v.begin(), v.end(), [](int i) { return i % 2 == 0; });
  if (it_not != v.end()) {
    std::cout << "First odd number: " << *it_not << '\n';
  } else {
    std::cout << "No odd number found\n";
  }
}
}  // namespace FindIfExample

class StdAlgorithm : public IExample {
  std::string group() const override { return "core/utils"; }
  std::string name() const override { return "StdAlgorithm"; }
  std::string description() const override {
    return "The examples for <algorithm> header";
  }

  void execute() override { FindIfExample::run(); }
};

REGISTER_EXAMPLE(StdAlgorithm, "core/utils", "StdAlgorithm");