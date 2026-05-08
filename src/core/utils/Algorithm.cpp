#include <algorithm>
#include "ExampleRegistry.h"
#include "Logger.h"

namespace find_if_example {
void run() {
  LOG("std::find_if example");
  std::vector<int> v{1, 2, 3, 4, 5};
  auto it = std::find_if(v.begin(), v.end(), [](int i) { return i % 2 == 0; });
  if (it != v.end()) {
    LOG("First even number: " + std::to_string(*it));
  } else {
    LOG("No even number found");
  }

  LOG("std::find_if_not example");
  auto it_not =
      std::find_if_not(v.begin(), v.end(), [](int i) { return i % 2 == 0; });
  if (it_not != v.end()) {
    LOG("First odd number: " + std::to_string(*it_not));
  } else {
    LOG("No odd number found");
  }
}
}  // namespace find_if_example

class Algorithm : public IExample {
 public:
  std::string group() const override { return "core/utils"; }
  std::string name() const override { return "std::algorithm"; }
  std::string description() const override {
    return "The examples for <algorithm> header";
  }

  void execute() override { find_if_example::run(); }
};

REGISTER_EXAMPLE(Algorithm);