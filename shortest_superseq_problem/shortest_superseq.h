// Engineer: Abhishek Gautam
// Last Updated: 01-04-2025

// Problem: You are given two arrays, one shorter (with all distinct elements)
//          and one longer. Find the shortest subarray in the longer array
//          that contains all the elements in the shorter array. The items
//          can appear in any order.
//          EXAMPLE
//          Input: {1,5,9} | {7,5,9,0,2,1,3,(5,7,9,1),1,5,8,8,9,7}
//          Output: [7,10] (the portion in braces)

// Approach:
// 1) Add all elements of the shorter array into a hashset. [O(m) where m<n]
// 2) Using a sliding window keep track of the smallest valid subarray. [O(n)]
//     2.1) We start with an empty window at the begining of the long array
//          and an empty hashset to keep track of distinct elements of the
//          shorter array present in the window.
//     2.2) Expand the window from the right if the size of its hashset is
//          less than the size of the shorter array.
//     2.3) Othrewise we update global record of the smallest window and
//          shrink window from the left.
// 3) Return the global minimum window.

// ====================================================================================

#pragma once

#include "absl/container/flat_hash_set.h"

struct SubArray {
  size_t start;
  size_t end;

  bool operator==(const SubArray &other) const {
    return start == other.start && end == other.end;
  }
};

SubArray ShortestSuperseq(const std::vector<int> &in_short,
                          const std::vector<int> &in_long);