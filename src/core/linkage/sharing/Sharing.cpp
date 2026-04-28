// cppcheck-suppress-file [unreadVariable]
#include <iostream>

#include "external/constants.h"
#include "inline/constants.h"
#include "internal/constants.h"

namespace internal_way {
void run() {
  std::cout << internal_constants::kAvogadro << "\n";
}
}  // namespace internal_way

namespace external_way {
void run() {
  std::cout << external_constants::kAvogadro << "\n";
}
}  // namespace external_way

namespace inline_way {
void run() {
  std::cout << inline_constants::kAvogadro << "\n";
}
}  // namespace inline_way

#include "ExampleRegistry.h"

class Sharing : public IExample {
 public:
  std::string group() const override { return "core"; }
  std::string name() const override { return "Sharing"; }
  std::string description() const override {
    return "SharingGlobalConstantsAcrossMultipleFiles";
  }
  void execute() override {
    internal_way::run();  // prefer 2
    external_way::run();
    inline_way::run();  // prefer 1
  }
};

REGISTER_EXAMPLE(Sharing, "core", "Sharing");
