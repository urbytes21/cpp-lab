#include <algorithm>
#include <iostream>
#include <vector>

namespace {

int increase(int a, int b) {
  return static_cast<int>(a > b);
}

int decrease(int a, int b) {
  return static_cast<int>(a < b);
}

// // Function
// // Declaring
// return_type (*FuncPtr) (parameter type, ....);
// typedef int (*SortFcn)(int a, int b);
using SortFcn = int (*)(int, int);

void run() {
  std::vector<int> vect{1, 6, 4, 22, 0, 6, 33, 39, -5};

  auto f_print = [](const std::vector<int>& vec) {
    for (const auto& e : vec) {
      std::cout << e << " ";
    }
    std::cout << "\n";
  };

  std::cout << "Before sorting : \n";
  f_print(vect);

  std::cout << "Sorting in descending " << "order \n";

  // Use auto
  auto sort_type_auto = increase;
  std::sort(vect.begin(), vect.end(), sort_type_auto);

  // Use pointer
  SortFcn sort_type_ptr = decrease;
  f_print(vect);

  std::cout << "Sorting with absolute " << "value as parameter\n ";
  std::sort(vect.begin(), vect.end(), sort_type_ptr);

  for (auto i : vect)
    std::cout << i << " ";
  std::cout << "\n";
}
}  // namespace

#include "ExampleRegistry.h"

class FunctionPointer : public IExample {
 public:
  std::string group() const override { return "core/expression"; }
  std::string name() const override { return "FunctionPointer"; }
  std::string description() const override {
    return "Function Pointer Example";
  }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(FunctionPointer);
