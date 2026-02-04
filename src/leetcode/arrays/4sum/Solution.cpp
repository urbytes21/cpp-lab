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
  if (nums[0] > target) {
    return {};
  }

  std::vector<std::vector<int>> result;
  for (size_t fI = 0; fI < size - 3; ++fI) {
    if (fI > 0 && nums[fI] == nums[fI - 1]) {
      ++fI;
      continue;
    }

    for (size_t sI = fI + 1; sI < size - 2; ++sI) {
      if (sI > 1 && nums[sI] == nums[sI - 1]) {
        continue;
      }

      size_t tI = sI + 1;
      size_t frI = size - 1;
      while (tI < frI) {
        int f = nums[fI];
        int s = nums[sI];
        int t = nums[tI];
        int fr = nums[frI];

        int diff = f + s + t + fr - target;
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
