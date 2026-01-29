#include <gtest/gtest.h>
#include "../src/leetcode/arrays/median_two_arrays/MedianTwoSortedArrays.h"

TEST(MedianTwoSortedArrays, TC1) {
  std::vector<int> nums1{1, 2};
  std::vector<int> nums2{3};
  double expected{2.0};

  Solution s{};

  EXPECT_EQ(expected, s.findMedianSortedArrays(nums1, nums2));
}

TEST(MedianTwoSortedArrays, TC2) {
  std::vector<int> nums1{1, 2};
  std::vector<int> nums2{3, 3};
  double expected{2.5};

  Solution s{};

  EXPECT_EQ(expected, s.findMedianSortedArrays(nums1, nums2));
}