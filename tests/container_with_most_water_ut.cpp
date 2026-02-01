#include <gtest/gtest.h>
#include "../src/leetcode/arrays/container_with_most_water/ContainerWithMostWater.h"

TEST(ContainerWithMostWater, TC1) {
  std::vector<int> height{1, 8, 6, 2, 5, 4, 8, 3, 7};
  int expected = 49;
  ContainerWithMostWater solution{};
  EXPECT_EQ(expected, solution.getMaxAmount(height));
}

TEST(ContainerWithMostWater, TC2) {
  std::vector<int> height{1, 1};
  int expected = 1;
  ContainerWithMostWater solution{};
  EXPECT_EQ(expected, solution.getMaxAmount(height));
}