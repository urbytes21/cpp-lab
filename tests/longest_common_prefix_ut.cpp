#include <gtest/gtest.h>
#include "../src/leetcode/arrays/longest_common_prefix/Solution.h"

TEST(LongestCommonPrefix, TC1) {
  std::vector<std::string> strs{"flower", "flow", "flight"};
  std::string expected{"fl"};
  Solution s{};
  EXPECT_EQ(expected, s.longestCommonPrefix(strs));
}

TEST(LongestCommonPrefix, TC2) {
  std::vector<std::string> strs{"dog","racecar","car"};
  std::string expected{""};
  Solution s{};
  EXPECT_EQ(expected, s.longestCommonPrefix(strs));
}


TEST(LongestCommonPrefix, TC3) {
  std::vector<std::string> strs{"a"};
  std::string expected{"a"};
  Solution s{};
  EXPECT_EQ(expected, s.longestCommonPrefix(strs));
}

TEST(LongestCommonPrefix, TC4) {
  std::vector<std::string> strs{"ab","a"};
  std::string expected{"a"};
  Solution s{};
  EXPECT_EQ(expected, s.longestCommonPrefix(strs));
}