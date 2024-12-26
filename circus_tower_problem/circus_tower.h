// Engineer: Abhishek Gautam
// Last Updated: 12-14-2024

// Problem: A circus id designing a tower routine consisting of people standing
//          atop one another's shoulder. For practical and aesthetic reasions,
//          each prson must be both shorter and lighter than the person below
//          him or her. Given the heights and weights of each person in the
//          circus, write a method to compute the largest possinle number of
//          people in such a tower.

//          EXAMPLE
//          Input (ht, wt): (65,100) (70,150) (56,90) (75,190) (60,95) (68,110)
//          Output: The longest tower is length 6 and includes from top to down
//          (56,90) (60,95) (65,100) (68,110) (70,150) (75,190)
//          ["Circus Tower" from Cracking the Coding Interview]

// Approach:
// 1) Sort the array based on the second index of each tuple(wt) in descending
//    order. [O(nlgn)]
// 2) We will now do a patience sort on the first index of each tupple (ht) [O(nlgn)]
//    2.1) we initialize a (to be) sorted array of indices A and an array of
//         previous indices P.
//    2.2) we then iterate through the heights. If a height is less than the
//         corresponding height of the last element of A, we append its index to
//         A.
//    2.3) If not, then we replace the index of the first element in A where the
//         the corresponding height is <= search height with the index of the
//         search height, starting from the left. Insertion into A is done using
//         binary search. In other words we find the samllest i such that A[i]
//         <= search height.
//    2.4) Each time we insert index j into A, we assign the previous index in A
//         to P[j]. This keeps a connection of every height to a greater height
//         that definitely comes before it in the main array.
//    2.5) A maintains the indices of the largest heights(A[i]) that culminate
//         a LDS of length i+1 where i is the index in A given the array seen so
//         far.
// 3) The size of A at the end gives the size of the largest increasing
//    subsequence (LIS).
// 4) To find a LIS, we start from the height corresponding to the last index in
//    A, call the index l. The next element in the subsequence can be found by
//    the height at index P[l] and so on. This gives us the LIS [O(n)]
// Inadequecies:
// - Does not guarantee the problem's requirement of weight being strictly
//   decreasing. It could be modified to do so but that would make it more
//   complex.

// Approach 2 (dynamic programming) [O(n^2)]:
// 1) sort the array based on the second index of each tuple (wt) in descending
//    order, let this array be A. We want to find the Longest decreasing
//    subsequence(LDS) on height(ht) in this case. [O(nlgn)]
// 2) initialize a dp array of the same length as A with first element 1
//    2.1) dp[i] represents the length of the LDS ending at index i in A.
// 3) for each element A[i], check all previous elements A[j], j<i. [O(n^2)]
//    3.1) when comparing heights, if A[j]<A[i], then i can extend the LDS
//         ending at j.
//    3.2) If this condition is met then dp[i] = max(dp[i],dp[j]+1).
// 4) to get the length of the overall LDS we find the maximum in array dp.
// 5) to get the particular LDS we maintain a previous element array which we
//    update at step 3.2 to maintain a connection between i and j. This is the
//    same as in approach 1. We can reconstruct the LDS by getting subsequent
//    elements by looking up indexes in this array. [O(n)]

// Time Complexity (approach 1) = O(nlgn)
// Space Complexity (both) = O(n)

#ifndef CIRCUS_TOWER_H
#define CIRCUS_TOWER_H

#include <algorithm>
#include <vector>

struct PersonDimensions {
  int height;
  int weight;
};

// Finds smallest index i such that A[i] >= search element and does the
// approptiate insertion into a patience sorted array for a given element.
void BinaryInsert(size_t person, size_t i, size_t j,
                  std::vector<size_t> &longest_seq_ends,
                  std::vector<size_t> &prev,
                  const std::vector<PersonDimensions> &dimensions);

// Inserts all elements into a patience sorted array
void PatienceSort(const std::vector<PersonDimensions> &dimensions,
                  std::vector<size_t> &longest_seq_ends,
                  std::vector<size_t> &prev);

// Sorts the array and calls all functions to execute subsequent steps (main
// function)
std::vector<PersonDimensions> LongestTower(
    const std::vector<PersonDimensions> &dimensions);

// Dynamic programming approach to finding longest tower
std::vector<PersonDimensions> LongestTower2(
    const std::vector<PersonDimensions> &dimensions);

#endif