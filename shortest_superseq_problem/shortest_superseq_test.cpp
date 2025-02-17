#include "shortest_superseq.h"

#include <gtest/gtest.h>

TEST(ShortestSuperseq, QuestionExample) {
  EXPECT_EQ(ShortestSuperseq(
                {1, 5, 9}, {7, 5, 9, 0, 2, 1, 3, 5, 7, 9, 1, 1, 5, 8, 8, 9, 7}),
            (SubArray{7, 10}));
}

TEST(ShortestSuperseq, CustomExample1) {
  EXPECT_EQ(ShortestSuperseq({1, 3, 7}, {0, 5, 9, 11, 7, 2, 1, 1, 4, 3, 8, 8,
                                         23, 7, 3, 3, 7, 9}),
            (SubArray{4, 9}));
}

TEST(ShortestSuperseq, CustomExample2) {
  EXPECT_EQ(ShortestSuperseq({2, 3, 5, 13}, {2, 4, 3,  9, 7, 8, 1, 1, 4, 3,
                                             8, 8, 23, 5, 7, 3, 3, 7, 9, 13}),
            (SubArray{0, 19}));
}