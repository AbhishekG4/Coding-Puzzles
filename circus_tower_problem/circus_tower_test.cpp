// Possible inadequecies of test cases:
//  - Tests do not check if calculated elements(calculated tower) actually
//    belong to the original array or not .

#include "circus_tower.h"

#include <gtest/gtest.h>

#include <iostream>

#include "utils.h"

void GenericTest(const std::vector<PersonDimensions> &dimensions,
                 size_t length_expected) {
  std::vector<PersonDimensions> longest_tower_calculated =
      LongestTower(dimensions);
  size_t length_calculated = longest_tower_calculated.size();

  // Logging tower found
  std::cout << "Tower: ";
  for (auto person : longest_tower_calculated)
    std::cout << person.height << ',' << person.weight << " | ";
  std::cout << std::endl;

  // Checking validity of tower found
  for (size_t i = 0; i < longest_tower_calculated.size() - 1; i++) {
    EXPECT_LT(longest_tower_calculated[i].height,
              longest_tower_calculated[i + 1].height)
        << "Height sequence invalid at index: " << i;
    EXPECT_LT(longest_tower_calculated[i].weight,
              longest_tower_calculated[i + 1].weight)
        << "Weight sequence invalid at index: " << i;
  }
  // Checking tower length
  EXPECT_EQ(length_calculated, length_expected);
}

TEST(LongestTower, QuestionExample) {
  GenericTest({{65, 100}, {70, 150}, {56, 90}, {75, 190}, {60, 95}, {68, 110}},
              6);
}

TEST(LongestTower, CustomExample) {
  GenericTest(
      {{52, 85}, {100, 90}, {85, 91}, {30, 51}, {46, 67}, {116, 72}, {110, 89}},
      4);
}

TEST(LongestTower, NilExample) {  // contains case where heights are same
  GenericTest({{21, 33}, {24, 26}, {24, 29}, {18, 36}, {26, 22}, {27, 19}}, 1);
}

TEST(LongestTower, Correctness) {
  std::vector<PersonDimensions> random_group;

  PopulateRandomIntDims(random_group, 117);

  std::vector<PersonDimensions> test_sol = LongestTower(random_group);
  std::vector<PersonDimensions> base_sol = LongestTower2(random_group);

  EXPECT_EQ(test_sol.size(), base_sol.size());
  // Checking validity of tower found
  for (size_t i = 0; i < test_sol.size() - 1; i++) {
    EXPECT_LT(test_sol[i].height, test_sol[i + 1].height)
        << "Height sequence invalid at index: " << i;
    EXPECT_LT(test_sol[i].weight, test_sol[i + 1].weight)
        << "Weight sequence invalid at index: " << i;
  }
}