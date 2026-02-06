#include <gtest/gtest.h>
#include "../src/leetcode/arrays/4sum/Solution.h"

// Create a struct for our tcs
struct FourSumCase {
  int target;
  std::vector<int> numsInput;
  std::vector<std::vector<int>> expected;
};

// Param Test Fixture
class FourSumTest : public ::testing::TestWithParam<FourSumCase> {};

// Test Data
INSTANTIATE_TEST_SUITE_P(
    BasicTestCases, FourSumTest,
    ::testing::Values(
        FourSumCase{0,
                    {1, 0, -1, 0, -2, 2},
                    {{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}}},
        FourSumCase{0,
                    {-2, -1, -1, 1, 1, 2, 2},
                    {{-2, -1, 1, 2}, {-1, -1, 1, 1}}},
        FourSumCase{3, {-3, -4, -5, 0, -5, -2, 5, 2, -3}, {{-4, 0, 2, 5}}},
        FourSumCase{-294967296,
                    {1000000000, 1000000000, 1000000000, 1000000000},
                    {}},
        FourSumCase{8, {2, 2, 2, 2, 2}, {{2, 2, 2, 2}}}));

TEST_P(FourSumTest, ReturnCorrectValues) {
  const auto& tc = GetParam();  // get the test case from test suit
  Solution s{};
  auto nums = tc.numsInput;
  auto target = tc.target;
  EXPECT_EQ(s.fourSum(nums, target), tc.expected);
}
