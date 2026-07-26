// cppcheck-suppress-file [unreadVariable]

// A constexpr function is implicitly inline.
// A constexpr static data member is implicitly an inline variable (since C++17).

#include "Logger.h"

namespace {
constexpr int square(int x) {
  return x * x;
}

consteval int cube(int x) {
  return x * x * x;
}

void run() {
  // 1. Named constants
  const double const_var_g{9.8};

#define NAME "Phong"

  // 2. Literal constants
  bool my_name_is_alex{true};  ///< true is a boolean literal -> type: bool
  double d{3.4};  ///< 3.4 is a floating-point literal -> type: double

  // "Hello, world!" is a string literal -> type: const char[14]
  LOG("Hello, world!");

  // 3. constexpr variables
  constexpr double kConstexprVarG{9.8};  // compile-time constant

  // 4. Constant expressions
  constexpr double kSomething{kConstexprVarG};

  // Error:
  // constexpr double something2{const_var_g};
  // const_var_g is const, but not guaranteed to be a constant expression

  if constexpr (kConstexprVarG != 9.8) {
    LOG("kConstexprVarG != 9.8");
  } else {
    LOG("kConstexprVarG == 9.8");
  }

  // 5. Const expression function

  constexpr int a = square(5);  // compile-time
  int b = square(5);            // runtime allowed

  constexpr int c = cube(5);  // OK
  // int d = cube(5);          // Error if not compile-time
}

}  // namespace

#include "ExampleRegistry.h"

class TypeQualifier : public IExample {
 public:
  std::string group() const override { return "core/basics"; }
  std::string name() const override { return "TypeQualifier"; }
  std::string description() const override { return "TypeQualifier"; }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(TypeQualifier);