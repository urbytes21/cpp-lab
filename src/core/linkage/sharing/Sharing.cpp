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

struct SharingGlobalConstantsAcrossMultipleFilesngAutoRunner {
  SharingGlobalConstantsAcrossMultipleFilesngAutoRunner() {
    cout << "\n"
         << "\n"
         << "SharingGlobalConstantsAcrossMultipleFiles\n";

    InternalWay::run();  // prefer 2
    ExternalWay::run();
    InlineWay::run();  // prefer 1
  }
};

static SharingGlobalConstantsAcrossMultipleFilesngAutoRunner autoRunInstance;
