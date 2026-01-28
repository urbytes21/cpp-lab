#include <algorithm>
#include <iostream>
#include <vector>

namespace {

int increase(int a, int b) {
  return a > b;
}

int decrease(int a, int b) {
  return a < b;
}

// // Function
// // Declaring
// return_type (*FuncPtr) (parameter type, ....);
typedef int (*SortFcn)(int a, int b);

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

  std::cout << "Sorting in descending "
            << "order \n";

  // Use auto
  auto sortTypeAuto = increase;
  std::sort(vect.begin(), vect.end(), sortTypeAuto);

  // Use pointer
  SortFcn sortTypePtr = decrease;
  f_print(vect);

  std::cout << "Sorting with absolute "
            << "value as parameter\n ";
  std::sort(vect.begin(), vect.end(), sortTypePtr);

  for (auto i : vect)
    std::cout << i << " ";
  std::cout << "\n";
}
}  // namespace

struct FunctionPointer {
  FunctionPointer() {
    std::cout << "\n--- Function Pointer Example ---\n";
    run();
  }
};

static FunctionPointer autoRunner;
