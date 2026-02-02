#include "DeleteMe.h"

#include <gtest/gtest.h>

/**
 * ASSERT_* versions generate fatal failures when they fail, and abort the current function
 * EXPECT_* are preferred, as they allow more than one failure to be reported in a test.
 */
TEST(AddTest, ValidNumbers) {
  DeleteMe calc = DeleteMe();

  ASSERT_TRUE(calc.add(1, 2));
  ASSERT_EQ(3, calc.get_last_result());

  ASSERT_TRUE(calc.add(0, 5));
  ASSERT_EQ(5, calc.get_last_result());

  ASSERT_TRUE(calc.add(5, 0));
  ASSERT_EQ(5, calc.get_last_result());

  ASSERT_TRUE(calc.add(4, -6));
  ASSERT_EQ(-2, calc.get_last_result());

  ASSERT_TRUE(calc.add(-4, 6));
  ASSERT_EQ(2, calc.get_last_result());

  ASSERT_TRUE(calc.add(-4, -6));
  ASSERT_EQ(-10, calc.get_last_result());
}

TEST(DivTest, ValidNumbers) {
  DeleteMe calc = DeleteMe();

  ASSERT_TRUE(calc.div(10, 2));
  ASSERT_EQ(5, calc.get_last_result());

  ASSERT_TRUE(calc.div(-12, 3));
  ASSERT_EQ(-4, calc.get_last_result());

  ASSERT_TRUE(calc.div(12, -3));
  ASSERT_EQ(-4, calc.get_last_result());
}

TEST(DivTest, InvalidNumbers) {
  DeleteMe calc = DeleteMe();

  ASSERT_FALSE(calc.div(7, 0));
  ASSERT_EQ(0, calc.get_last_result());
}

TEST(DivTest, FailureMessage) {
  // ASSERT_FALSE(true) << "FailureMessage: ASSERT_FALSE(true)";
}

#include <gmock/gmock.h>
#include "mock/MockTurtle.h"
#include "mock/Painter.h"
TEST(MockPainterTest, DrawSquare_CallsCorrectTurtleOperations) {
  MockTurtle turtle;
  Painter painter{turtle};

  EXPECT_CALL(turtle, PenDown()).Times(1);

  EXPECT_CALL(turtle, Forward(100)).Times(4);
  EXPECT_CALL(turtle, Turn(90)).Times(4);

  EXPECT_CALL(turtle, PenUp()).Times(1);

  painter.DrawSquare(100);
}

#include "mock/FakeTurtle.h"
TEST(FakePainterTest, DrawSquare_ProducesSquarePath) {
  FakeTurtle turtle;
  Painter painter{turtle};

  painter.DrawSquare(10);

  const auto& path = turtle.Path();

  ASSERT_EQ(path.size(), 8);  // 4 lines → 8 points (start/end)

  EXPECT_EQ(path[0], std::make_pair(0, 0));
  EXPECT_EQ(path[1], std::make_pair(0, 10));

  EXPECT_EQ(path[2], std::make_pair(0, 10));
  EXPECT_EQ(path[3], std::make_pair(10, 10));

  EXPECT_EQ(path[4], std::make_pair(10, 10));
  EXPECT_EQ(path[5], std::make_pair(10, 0));

  EXPECT_EQ(path[6], std::make_pair(10, 0));
  EXPECT_EQ(path[7], std::make_pair(0, 0));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
