#include <gtest/gtest.h>
#include "../src/leetcode/arrays/two_sum/TwoSum.h"

struct TestCase {
  std::vector<int> nums;
  int target;
  std::vector<int> expected;
};

TEST(TwoSum, Case1) {
  TestCase tc = {.nums{2, 7, 11, 15}, .target{9}, .expected{0, 1}};
  Solution s{};

  EXPECT_EQ(tc.expected, s.twoSum(tc.nums, tc.target));
}

TEST(TwoSum, Case2) {
  TestCase tc = {.nums{3, 2, 4}, .target{6}, .expected{1, 2}};
  Solution s{};

  EXPECT_EQ(tc.expected, s.twoSum(tc.nums, tc.target));
}

TEST(TwoSum, Case3) {
  TestCase tc = {.nums{3, 3}, .target{6}, .expected{0, 1}};
  Solution s{};

  EXPECT_EQ(tc.expected, s.twoSum(tc.nums, tc.target));
}

TEST(TwoSum, Case4) {
  TestCase tc = {.nums{3, 3}, .target{0}, .expected{-1, -1}};
  Solution s{};

  EXPECT_EQ(tc.expected, s.twoSum(tc.nums, tc.target));
}