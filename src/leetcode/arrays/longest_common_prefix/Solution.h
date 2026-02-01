//cppcheck-suppress-file [functionStatic,ctuOneDefinitionRuleViolation]

// 14 - E
// Write a function to find the longest common prefix string amongst an array of strings.
// If there is no common prefix, return an empty string "".
// Example 1:

// Input: strs = ["flower","flow","flight"]
// Output: "fl"
// Example 2:

// Input: strs = ["dog","racecar","car"]
// Output: ""
// Explanation: There is no common prefix among the input strings.

// Constraints:

// 1 <= strs.length <= 200
// 0 <= strs[i].length <= 200
// strs[i] consists of only lowercase English letters if it is non-empty.

// Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity ?

#pragma once

#include <string>
#include <vector>

class Solution {
 public:
  std::string longestCommonPrefix(const std::vector<std::string>& strs);
};
