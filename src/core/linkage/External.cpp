#include "External.h"
#include <iostream>

namespace external {  // We must define the variable inside the same namespace as its extern declaration;
                      // otherwise the linker cannot find the correct symbol.

// 1. Non-Static global variable/ function
int non_static_var{1};
void nonStaticFnc() {
  std::cout << "nonStaticFnc\n";
}

// 2. Extern Const/constexpr
extern const int kExternConstVar{200};

// 3. Namespaces
namespace name {
int namespace_var = 123;
}

}  // namespace external