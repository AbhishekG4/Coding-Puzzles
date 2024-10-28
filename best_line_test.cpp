#include "best_line.h"

#include <gtest/gtest.h>

TEST(GetBestLine, RegularLine) {
  vector<Point> pts = {Point(1, 3), Point(2, 1),   Point(3, -1),
                       Point(4, 3), Point(4, -3),  Point(3, 1),
                       Point(4, 1), Point(2.5, 2), Point(-21.3, -1.3),
                       Point(2, 4), Point(2, 11)};  // regular line

  Line test_line = getBestLine(pts);

  EXPECT_EQ(test_line.intercept, 5.0);
  EXPECT_EQ(test_line.slope, -2);
  EXPECT_EQ(test_line.x_intercept, 2.5);
  EXPECT_EQ(test_line.isHorizontal, 0);
  EXPECT_EQ(test_line.isVertical, 0);
}

TEST(GetBestLine, HorizontalLine) {
  vector<Point> pts = {Point(1, 3),       Point(2, 1),        Point(3, -1),
                       Point(4, -3),      Point(3, 1),        Point(4, 1),
                       Point(2.5, 2),     Point(-21.3, -1.3), Point(2, 4),
                       Point(-23.456, 1), Point(-5, 1)};  // horizontal line

  Line test_line = getBestLine(pts);

  EXPECT_EQ(test_line.intercept, 1);
  EXPECT_EQ(test_line.slope, 0);
  EXPECT_EQ(test_line.isHorizontal, 1);
  EXPECT_EQ(test_line.isVertical, 0);
}

TEST(GetBestLine, VerticalLine) {
  vector<Point> pts = {
      Point(1, 3),   Point(2, 1),        Point(3, -1),
      Point(4, -3),  Point(3, 1),        Point(4, 1),
      Point(2.5, 2), Point(-21.3, -1.3), Point(2, 4),
      Point(2, 11),  Point(2, 67.55),    Point(2, -1)};  // vertical line

  Line test_line = getBestLine(pts);

  EXPECT_EQ(test_line.x_intercept, 2);
  EXPECT_EQ(test_line.isHorizontal, 0);
  EXPECT_EQ(test_line.isVertical, 1);
}