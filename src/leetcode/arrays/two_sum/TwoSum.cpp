#include "TwoSum.h"

/**
 * S1: Using for-loop-index
 * Time complexity: O(n2)
 * Space complexity: O(1)
 */
std::vector<int> Solution::twoSum(const std::vector<int>& nums, int target) {
  for (int i = 0; i < nums.size(); ++i) {
    int diff = target - nums.at(i);
    for (int j = i + 1; j < nums.size(); ++j) {
      if (diff == nums.at(j)) {
        return std::vector<int>{i, j};
      }
    }
  }

  // no solution
  return std::vector<int>{-1, -1};
}

// #include <unordered_map>
// /**
//  * 3 1 4
//  * =====
//  * 3 1 4
//  * -----
//  * 0 1 2
//  * =====
//  * Time complexity: O(n)
//  * Space complexity: O(n)
//  */
// std::vector<int> Solution::twoSum(const std::vector<int>& nums, int target) {
//   std::unordered_map<int, int> numMap{};
//   for (int i = 0; i < nums.size(); ++i) {
//     int xkey = nums[i];
//     int ykey = target - nums[i];
//     if (numMap.find(ykey) != nullptr) {
//       return std::vector<int>{numMap.at(ykey), i};
//     }

//     // save vector to map<key=num,value=index>
//     numMap.insert(std::pair(xkey, i));
//   }

//   // no solution
//   return std::vector<int>{-1, -1};
// }
