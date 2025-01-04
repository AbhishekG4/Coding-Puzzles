#include "shortest_superseq.h"
#include <gtest/gtest.h>


TEST(ShortestSuperseq, QuestionExample){
    std::vector<int> in1 = {1,5,9};
    std::vector<int> in2 = {7,5,9,0,2,1,3,5,7,9,1,1,5,8,8,9,7};

    SubArray test_result = ShortestSuperseq(in1,in2);

    EXPECT_EQ(test_result.start, 7);
    EXPECT_EQ(test_result.end, 10);
}

TEST(ShortestSuperseq, CustomExample){
    std::vector<int> in1 = {1,3,7};
    std::vector<int> in2 = {0,5,9,11,7,2,1,1,4,3,8,8,23,7,3,3,7,9};

    SubArray test_result = ShortestSuperseq(in1,in2);

    EXPECT_EQ(test_result.start, 4);
    EXPECT_EQ(test_result.end, 9);
}