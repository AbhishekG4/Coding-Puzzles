#include "circus_tower.h"

#include <gtest/gtest.h>

#include <iostream>

TEST(LongestTower, QuestionExample) {
  std::vector<PersonDimensions> longest_tower_calculated = LongestTower({{65, 100}, {70, 150}, {56, 90},{75, 190}, {60, 95},  {68, 110}});
  int tower_length_calculated = (int)longest_tower_calculated.size();
  // Logging tower found
  std::cout<<"Tower: ";
  for(auto person : longest_tower_calculated) std::cout<<person.height<<','<<person.weight<<" | ";
  std::cout<<std::endl;

  // Checking validity of tower found
  for(size_t i=0; i<longest_tower_calculated.size()-1; i++){
    EXPECT_LT(longest_tower_calculated[i].height, longest_tower_calculated[i+1].height) << "Height sequence invalid at index: "<<i;
    EXPECT_LT(longest_tower_calculated[i].weight, longest_tower_calculated[i+1].weight) << "Weight sequence invalid at index: "<<i;
  }
  // Checking tower length
  EXPECT_EQ(tower_length_calculated, 6);
}

TEST(LongestTower, CustomExample) {
  std::vector<PersonDimensions> longest_tower_calculated = LongestTower({{52, 85}, {100, 90}, {85, 91}, {30, 51}, {46, 67}, {116, 72}, {110, 89}});
  int tower_length_calculated = (int)longest_tower_calculated.size();
  // Logging tower found
  std::cout<<"Tower: ";
  for(auto person : longest_tower_calculated) std::cout<<person.height<<','<<person.weight<<" | ";
  std::cout<<std::endl;

  // Checking validity of tower found
  for(size_t i=0; i<longest_tower_calculated.size()-1; i++){
    EXPECT_LT(longest_tower_calculated[i].height, longest_tower_calculated[i+1].height) << "Height sequence invalid at index: "<<i;
    EXPECT_LT(longest_tower_calculated[i].weight, longest_tower_calculated[i+1].weight) << "Weight sequence invalid at index: "<<i;
  }
  // Checking tower length
  EXPECT_EQ(tower_length_calculated, 4);
}