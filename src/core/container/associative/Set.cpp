
// cppcheck-suppress-file []
#include <iostream>
#include <set>
#include "ExampleRegistry.h"

namespace {
void run() {
  // 1. Init
  std::set<int> m_set{3, 4, 5, 1, 2};

  // 2. Modifiers
  m_set.insert(-1);

  m_set.insert(99);
  m_set.erase(99);

  for (const auto k : m_set) {
    std::cout << k << " ";
  }
  std::cout << std::endl;
}
}  // namespace

class Set : public IExample {
 public:
  std::string group() const override { return "core/container"; }
  std::string name() const override { return "Set"; }
  std::string description() const override { return "std::set Example"; }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(Set);