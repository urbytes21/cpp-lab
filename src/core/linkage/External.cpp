#include "External.h"
#include <iostream>

namespace External {  // We must define the variable inside the same namespace as its extern declaration;
                      // otherwise the linker cannot find the correct symbol.

// 1. Non-Static global variable/ function
int nonStaticVar{1};
void nonStaticFnc() {
  std::cout << "nonStaticFnc\n";
}

// 2. Extern Const/constexpr
extern const int EXTERN_CONST_VAR{200};

// 3. Namespaces
namespace Name {
int namespaceVar = 123;  // Định nghĩa
}

}  // namespace External