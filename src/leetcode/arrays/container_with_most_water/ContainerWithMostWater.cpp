#include "ContainerWithMostWater.h"

// /**
//  * @brief Complexity
//  *  Time: O(n^2)
//  *  Space: O(1)
//  */
// int ContainerWithMostWater::getMaxAmount(const std::vector<int>& heights) {
//   std::size_t size = heights.size();
//   int max{};
//   for (std::size_t i = 0; i < size - 1; ++i) {
//     for (std::size_t j = i + 1; j < size; ++j) {
//       int w = j - i;
//       int h = std::min(heights.at(i), heights.at(j));
//       max = std::max(max, w * h);
//     }
//   }

//   return max;
// }

/**
 * @brief Two pointers solution
 *   Complexity
 *    Time: O(n)
 *    Space: O(1)
 */
#include <iostream>
int ContainerWithMostWater::getMaxAmount(const std::vector<int>& heights) {
  std::size_t size = heights.size();
  if (size < 2) {
    return -1;
  }

  // size_t index = it - v.begin();
  auto lpos = heights.begin();
  auto rpos = heights.end() - 1;  // end point to the last one e
  int result{0};
  while (lpos < rpos) {
    int h = std::min(*lpos, *rpos);
    int w = static_cast<int>(rpos - lpos);
    int t = h * w;
    result = std::max(result, t);

    // the height of the container is determined by the shorter position
    // so it means we do not need to change the taller one.
    if (*lpos < *rpos) {
      lpos += 1;
    } else {
      rpos -= 1;
    }
  }

  return result;
}