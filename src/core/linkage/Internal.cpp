#include <iostream>

namespace Internal {  // We must define the variable inside the same namespace as its extern declaration;
                      // otherwise the linker cannot find the correct symbol.

// 1. Static global variable/ function
static int g_internal{42};
static void func_internal() {
  std::cout << "func_internal\n";
}

// 2. Const/constexpr
const int c_internal{100};
constexpr int ce_internal{100};

// 3. Anonymous namepsace
namespace {
int ns_internal{100};
}

}  // namespace Internal