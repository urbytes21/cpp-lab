// cppcheck-suppress-file [unreadVariable]
#include <iostream>
using namespace std;

#include "external/constants.h"
#include "inline/constants.h"
#include "internal/constants.h"

namespace InternalWay {
void run() {
  std::cout << InternalConstants::avogadro << "\n";
}
}  // namespace InternalWay

namespace ExternalWay {
void run() {
  std::cout << ExternalConstants::avogadro << "\n";
}
}  // namespace ExternalWay

namespace InlineWay {
void run() {
  std::cout << InlineConstants::avogadro << "\n";
}
}  // namespace InlineWay

#include "ExampleRegistry.h"

class Sharing : public IExample {
 public:
  std::string group() const override { return "core"; }
  std::string name() const override { return "Sharing"; }
  std::string description() const override {
    return "SharingGlobalConstantsAcrossMultipleFiles";
  }
  void execute() override {
    InternalWay::run();  // prefer 2
    ExternalWay::run();
    InlineWay::run();  // prefer 1
  }
};

REGISTER_EXAMPLE(Sharing, "core", "Sharing");
