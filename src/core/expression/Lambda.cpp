#include <algorithm>  // for std::sort
// std::sort
// default (1)
// template <class RandomAccessIterator>  void sort (RandomAccessIterator first, RandomAccessIterator last);
// custom (2)
// template <class RandomAccessIterator, class Compare>  void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);

#include <iostream>
#include <vector>

namespace {
void run() {
  std::vector<int> vect{-1, -6, 4, 2, 0, 6, 3, 9, -5};

  auto f_print = [](const std::vector<int>& vec) {
    for (const auto& e : vec) {
      std::cout << e << " ";
    }
    std::cout << "\n";
  };

  std::cout << "Before sorting : \n";
  f_print(vect);

  std::cout << "Sorting in descending " << "order \n";
  std::sort(vect.begin(), vect.end(), [](int a, int b) { return a > b; });

  f_print(vect);

  std::cout << "Sorting with absolute " << "value as parameter\n ";
  std::sort(vect.begin(), vect.end(), [](int a, int b) { return a < b; });

  for (auto i : vect)
    std::cout << i << " ";
  std::cout << "\n";
}
}  // namespace

#include "ExampleRegistry.h"
#include "IExample.h"

class Lambda : public IExample {
 public:
  std::string group() const override { return "core"; }
  std::string name() const override { return "Lambda"; }
  std::string description() const override {
    return "Lambda Expression Example";
  }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(Lambda, "core", "Lambda");
