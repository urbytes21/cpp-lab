#include "Solution.h"
#include <algorithm>
/**
 * @brief Complexity
 *  - Time: O(nlog(n) + n(n-1)) ~ O(n2)
 *  - Space: O(1)
 */
std::vector<std::vector<int>> Solution::threeSum(std::vector<int>& nums) {
  std::vector<std::vector<int>> trips{};
  const size_t size = nums.size();
  if (size < 3) {
    return trips;
  }

  std::sort(nums.begin(), nums.end());

  // after sorted, if the smallest number is greater than 0,
  // no triplet can sum to zero
  if (nums[0] > 0) {
    return {};
  }

  for (size_t i = 0; i < size - 2; ++i) {
    if (i > 0 && i < size - 2 && nums[i] == nums[i - 1]) {
      // we should not use num[i] == num[i+1] expression because we
      // may fall thorough out
      continue;  // skip duplicates for the 1st
    }

    int first = nums[i];

    // use two pointers to find the 2 remain numbers
    size_t j = i + 1;
    size_t k = size - 1;
    while (j < k) {
      int second = nums[j];
      int third = nums[k];
      int sum = first + second + third;

      if (sum == 0) {
        trips.push_back({first, second, third});

        ++j;
        --k;

        // move next
        while (nums[j] == nums[j - 1] && j < k) {
          ++j;  // skip duplicates for the 2nd
        }

        while (nums[k] == nums[k + 1] && j < k) {
          --k;  // skip duplicates for the 3rd
        }
      } else if (sum < 0) {
        // require a large sum by increasing the 2nd
        ++j;
      } else {
        // require a smaller sum by decreasing the 3rd
        --k;
      }
    }
  }

  return trips;
}
