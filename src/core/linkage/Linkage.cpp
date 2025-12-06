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

struct LinkageAutoRunner {
  LinkageAutoRunner() {
    cout << "\n"
         << "\n"
         << "Linkage\n";
    Internal::run();
    External::run();
  }
};

static LinkageAutoRunner autoRunInstance;
