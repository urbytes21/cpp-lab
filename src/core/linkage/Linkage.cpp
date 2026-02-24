// cppcheck-suppress-file [unreadVariable]
#include <iostream>
#include "External.h"
using namespace std;

namespace Internal {

extern int g_internal;   //  ERROR: g_internal not visible outside Internal.cpp
extern int ce_internal;  //  ERROR: g_internal not visible outside Internal.cpp
extern int c_internal;   //  ERROR: g_internal not visible outside Internal.cpp
extern int ns_internal;  //  ERROR: g_internal not visible outside Internal.cpp

void func_internal();  //  ERROR: helper not visible outside Internal.cpp

void run() {
  // std::cout << g_internal;
  // std::cout << ce_internal;
  // std::cout << c_internal;
  // std::cout << ns_internal;
  // func_internal();
}
}  // namespace Internal

namespace External {
// use extern without initliaizer/forward declaration to access the external global variable/function
extern int nonStaticVar;
void nonStaticFnc();
extern const int EXTERN_CONST_VAR;

void run() {
  std::cout << nonStaticVar << "\n";
  std::cout << EXTERN_CONST_VAR << "\n";
  std::cout << INLINE_CONST_VAR << "\n";
  std::cout << CONSTEXPR_VAR << "\n";
  std::cout << Name::namespaceVar << "\n";
  nonStaticFnc();
}

}  // namespace External

#include "ExampleRegistry.h"

class Linkage : public IExample {
 public:
  std::string group() const override { return "core"; }
  std::string name() const override { return "Linkage"; }
  std::string description() const override { return "Linkage"; }
  void execute() override {
    Internal::run();
    External::run();
  }
};

REGISTER_EXAMPLE(Linkage, "core", "Linkage");
