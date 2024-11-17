#include "best_line.h"

#include <gtest/gtest.h>

TEST(GetBestLine, RegularLine) {
  std::vector<Point> pts = {{1, 3},        {2, 1}, {3, -1}, {4, 3},
                            {4, -3},       {3, 1}, {4, 1},  {2.5, 2},
                            {-21.3, -1.3}, {2, 4}, {2, 11}};  // regular line

  Line test_line = GetBestLine(pts);

  EXPECT_EQ(test_line.GetIntercept(), 5.0);
  EXPECT_EQ(test_line.GetSlope(), -2);
  EXPECT_EQ(test_line.GetXIntercept(), 2.5);
  EXPECT_FALSE(test_line.GetIsHorizontal());
  EXPECT_FALSE(test_line.GetIsVertical());
}

TEST(GetBestLine, HorizontalLine) {
  std::vector<Point> pts = {{1, 3}, {2, 1},       {3, -1},  {4, -3},
                            {3, 1}, {4, 1},       {2.5, 2}, {-21.3, -1.3},
                            {2, 4}, {-23.456, 1}, {-5, 1}};  // horizontal line

  Line test_line = GetBestLine(pts);

  EXPECT_EQ(test_line.GetIntercept(), 1);
  EXPECT_EQ(test_line.GetSlope(), 0);
  EXPECT_TRUE(test_line.GetIsHorizontal());
  EXPECT_FALSE(test_line.GetIsVertical());
}

TEST(GetBestLine, VerticalLine) {
  std::vector<Point> pts = {
      {1, 3},        {2, 1}, {3, -1}, {4, -3},    {3, 1}, {4, 1}, {2.5, 2},
      {-21.3, -1.3}, {2, 4}, {2, 11}, {2, 67.55}, {2, -1}};  // vertical line

  Line test_line = GetBestLine(pts);

  EXPECT_EQ(test_line.GetXIntercept(), 2);
  EXPECT_FALSE(test_line.GetIsHorizontal());
  EXPECT_TRUE(test_line.GetIsVertical());
}