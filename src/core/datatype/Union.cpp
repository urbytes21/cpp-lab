#include <iostream>
#include <string>

// --- Union Definition ---
// All members share the same memory
union UnionDataType {
  int intValue;
  float floatValue;
  char charValue;

  void printAll() const {
    std::cout << "intValue = " << intValue << ", floatValue = " << floatValue
              << ", charValue = " << charValue << "\n";
  }
};

// --- Demonstrate unique property ---
void unionDemo() {
  std::cout << "\n--- Union Unique Behavior ---\n";

  UnionDataType u;

  u.intValue = 65;
  std::cout << "After assigning intValue = 65:\n";
  u.printAll();  // Only intValue is meaningful; others show overwritten memory

  u.floatValue = 3.14F;
  std::cout << "After assigning floatValue = 3.14:\n";
  u.printAll();  // Writing floatValue overwrites intValue

  u.charValue = 'A';
  std::cout << "After assigning charValue = 'A':\n";
  u.printAll();  // Writing charValue overwrites both intValue and floatValue

  std::cout << "Size of union = " << sizeof(UnionDataType) << " bytes\n";
  std::cout << "Notice: Only one value is valid at a time.\n";
}

// --- Auto-run struct ---
#include "ExampleRegistry.h"

class CUnion : public IExample {
 public:
  std::string group() const override { return "core/datatype"; }
  std::string name() const override { return "Union"; }
  std::string description() const override { return "Compound type: Union"; }
  void execute() override { unionDemo(); }
};

REGISTER_EXAMPLE(CUnion);