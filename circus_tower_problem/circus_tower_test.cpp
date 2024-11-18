#include "circus_tower.h"

#include <gtest/gtest.h>

TEST(LongestTower, QuestionExample) {
  std::vector<PersonDimensions> dimensions = {{65, 100}, {70, 150}, {56, 90},
                                              {75, 190}, {60, 95},  {68, 110}};

  int calculated_tower_length = LongestTower(dimensions);
  EXPECT_EQ(calculated_tower_length, 6);
}

TEST(LongestTower, CustomExample) {
  std::vector<PersonDimensions> dimensions = {
      {52, 85}, {100, 90}, {85, 91}, {30, 51}, {46, 67}, {116, 72}, {110, 89}};

  int calculated_tower_length = LongestTower(dimensions);
  EXPECT_EQ(calculated_tower_length, 4);
}