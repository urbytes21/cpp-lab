#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/leetcode/arrays/3sum/Solution.h"

using ::testing::ElementsAre;
using ::testing::UnorderedElementsAre;

/**
 * Test case definition
 */
struct ThreeSumCase {
  std::vector<int> input;
  std::vector<std::vector<int>> expected;
};

/**
 * Parameterized test fixture
 */
class ThreeSumTest : public ::testing::TestWithParam<ThreeSumCase> {};

/**
 * Main test
 *
 * Note:
 * - Order of triplets does NOT matter
 * - Order inside each triplet DOES matter (sorted by implementation)
 */
TEST_P(ThreeSumTest, ReturnsCorrectTriplets) {
  const auto& tc = GetParam();
  Solution s{};

  auto nums = tc.input;
  auto result = s.threeSum(nums);

  std::vector<::testing::Matcher<std::vector<int>>> matchers;
  for (const auto& triplet : tc.expected) {
    matchers.push_back(ElementsAre(triplet[0], triplet[1], triplet[2]));
  }

  EXPECT_THAT(result, UnorderedElementsAreArray(matchers));
}

/**
 * Test data
 */
INSTANTIATE_TEST_SUITE_P(
    BasicAndEdgeCases, ThreeSumTest,
    ::testing::Values(ThreeSumCase{{}, {}}, ThreeSumCase{{1}, {}},
                      ThreeSumCase{{1, 2}, {}}, ThreeSumCase{{1, 2, 3}, {}},
                      ThreeSumCase{{2, 1, 3}, {}}, ThreeSumCase{{0, 1, 1}, {}},
                      ThreeSumCase{{-5, -4, -3, -2}, {}},
                      ThreeSumCase{{1, 2, 3, 4}, {}},

                      ThreeSumCase{{-1, 0, 1, 2, -1, -4},
                                   {{-1, -1, 2}, {-1, 0, 1}}},

                      ThreeSumCase{{0, 0, 0}, {{0, 0, 0}}},

                      ThreeSumCase{{0, 0, 0, 0}, {{0, 0, 0}}},

                      ThreeSumCase{{1, 2, 0, 1, 0, 0, 0, 0}, {{0, 0, 0}}},

                      ThreeSumCase{{-2, 0, 0, 2, 2}, {{-2, 0, 2}}}));

/**
 * Extra safety test:
 * ensure no duplicate triplets are returned
 */
TEST(ThreeSumExtra, NoDuplicateTriplets) {
  std::vector<int> nums{-2, 0, 0, 2, 2};
  Solution s{};

  auto result = s.threeSum(nums);

  ASSERT_EQ(result.size(), 1);
  EXPECT_EQ(result[0], std::vector<int>({-2, 0, 2}));
}
