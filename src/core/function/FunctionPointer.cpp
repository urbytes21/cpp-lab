#include <algorithm>
#include <vector>
#include "Logger.h"

namespace {

int increase(int a, int b) {
  LOG("");
  return static_cast<int>(a > b);
}

int decrease(int a, int b) {
  LOG("");
  return static_cast<int>(a < b);
}

// // Function
// // Declaring
// return_type (*FuncPtr) (parameter type, ....);
// typedef int (*SortFcn)(int a, int b);

/// @brief Function Pointer
using sort_function_ptr = int (*)(int, int);

void run() {
  std::vector<int> vect{-1, -6, 4, 2, 0, 6, 3, 9, -5};
  auto f_print = [](const std::vector<int>& vec) {
    std::ostringstream oss;
    for (const auto& e : vec) {
      oss << e << " ";
    }
    LOG(oss.str());
  };

  LOG("Before sorting : ");
  f_print(vect);

  LOG("Sorting in descending order");
  // Use auto
  auto sort_type_auto = increase;
  std::sort(vect.begin(), vect.end(), sort_type_auto);

  // Use pointer
  sort_function_ptr sort_type_ptr = decrease;
  f_print(vect);

  LOG("Sorting with absolute value as parameter");
  std::sort(vect.begin(), vect.end(), sort_type_ptr);

  std::ostringstream oss;
  for (auto i : vect)
    oss << i << " ";
  LOG(oss.str());
}
}  // namespace

#include "ExampleRegistry.h"

class FunctionPointer : public IExample {
 public:
  std::string group() const override { return "core/function"; }
  std::string name() const override { return "FunctionPointer"; }
  std::string description() const override {
    return "Function Pointer Example";
  }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(FunctionPointer);
