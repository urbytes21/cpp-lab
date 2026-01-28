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

  std::cout << "Sorting in descending "
            << "order \n";
  std::sort(vect.begin(), vect.end(), [](int a, int b) { return a > b; });

  f_print(vect);

  std::cout << "Sorting with absolute "
            << "value as parameter\n ";
  std::sort(vect.begin(), vect.end(), [](int a, int b) { return a < b; });

  for (auto i : vect)
    std::cout << i << " ";
  std::cout << "\n";
}
}  // namespace

struct LambdaRunner {
  LambdaRunner() {
    std::cout << "\n--- Lambda Expression Example ---\n";
    run();
  }
};

static LambdaRunner autoRunner;
