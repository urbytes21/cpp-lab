// cppcheck-suppress-file [unreadVariable]

#include <cstdint>  // for uint8_t
#include <iostream>

// A type defined in terms of other types

// *0. Define some enums
// Unscope enum
enum BasicEnum { kEnumratorA, kEnumratorB, kEnumratorC };

// Scoped enum - enumrators are inside enum's scope
enum class ScopeEnumClass { kEnumratorA, kEnumratorB, kEnumratorC };

// Scoped enum inside a namespace
namespace enum_name_space {
enum class ScopeEnumClass { kEnumratorA, kEnumratorB, kEnumratorC };
}

//  Scoped enum with explicit base type
enum class ScopeEnumClassB : uint8_t {
  kEnumratorA = 0,
  kEnumratorB = 1,
  kEnumratorC = 2
};

void enums() {
  std::cout << "\n--- Enum Type Examples ---\n";
  // *1. Using unscope enum
  BasicEnum unscope_e = kEnumratorA;

  // *2. Using scoped enum
  ScopeEnumClass scope_e_c = ScopeEnumClass::kEnumratorA;

  // *3. Using scoped enum namespace
  enum_name_space::ScopeEnumClass scope_e_c_n =
      enum_name_space::ScopeEnumClass::kEnumratorA;

  // *4. Using scoped enum with base type
  ScopeEnumClassB st = ScopeEnumClassB::kEnumratorA;
}

#include "ExampleRegistry.h"

class CEnum : public IExample {
 public:
  std::string group() const override { return "core/datatype"; }
  std::string name() const override { return "Enum"; }
  std::string description() const override { return "Compound type: Enum"; }
  void execute() override { enums(); }
};

REGISTER_EXAMPLE(CEnum);
