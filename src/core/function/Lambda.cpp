#include <algorithm>  // for std::sort
// std::sort
// default (1)
// template <class RandomAccessIterator>  void sort (RandomAccessIterator first, RandomAccessIterator last);
// custom (2)
// template <class RandomAccessIterator, class Compare>  void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);

#include <sstream>
#include <vector>
#include "Logger.h"

namespace {
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
  std::sort(vect.begin(), vect.end(), [](int a, int b) { return a > b; });

  f_print(vect);

  LOG("Sorting with absolute value as parameter");
  std::sort(vect.begin(), vect.end(), [](int a, int b) { return a < b; });

  std::ostringstream oss;
  for (auto i : vect)
    oss << i << " ";
  LOG(oss.str());
}
}  // namespace

#include "ExampleRegistry.h"

class Lambda : public IExample {
 public:
  std::string group() const override { return "core/function"; }
  std::string name() const override { return "Lambda"; }
  std::string description() const override {
    return "Lambda Expression Example";
  }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(Lambda);
