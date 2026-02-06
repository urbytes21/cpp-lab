#include "Solution.h"
#include <algorithm>
#include <iostream>

/**
 * @brief Complexity
 *  - Time: O(n3)
 *  - Space: O(logn) // belong to sort
 */
std::vector<std::vector<int>> Solution::fourSum(std::vector<int>& nums,
                                                int target) {
  size_t size = nums.size();
  if (size < 4) {
    return {};
  }

  std::sort(nums.begin(), nums.end());

  std::vector<std::vector<int>> result;
  for (size_t fI = 0; fI < size - 3; ++fI) {
    if (fI > 0 && nums[fI] == nums[fI - 1]) {
      continue;
    }

    for (size_t sI = fI + 1; sI < size - 2; ++sI) {
      if (sI > fI + 1 && nums[sI] == nums[sI - 1]) {
        continue;
      }

      size_t tI = sI + 1;
      size_t frI = size - 1;
      while (tI < frI) {
        int f = nums[fI];
        int s = nums[sI];
        int t = nums[tI];
        int fr = nums[frI];
        long diff = static_cast<long>(f) + s + t + fr - target;
        if (diff == 0) {
          result.push_back({f, s, t, fr});
          // Next
          ++tI;
          --frI;

          while (tI < frI && nums[tI] == nums[tI - 1]) {
            ++tI;
          }

          while (tI < frI && nums[frI] == nums[frI + 1]) {
            --frI;
          }
        } else if (diff < 0) {
          ++tI;
        } else {
          --frI;
        }
      }
    }
  }

  return result;
}
