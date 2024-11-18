// Engineer: Abhishek Gautam
// Last Updated: 11-17-2024

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
// 1) Sort the array based on the second index of each tupple (wt) [O(nlgn)]
// 2) For each pair in the sorted array, find all pairs with greater ht that
//    lie in front of it, thus ht and wt will be greater. Store all such
//    pairs(pair1->pair2) using a hashmap in the form of an adjacency
//    list. [O(n^3)]
// 3) These directional pairs make up a graph where each path is a valid
//    tower.
// 4) We must now find the longest path in the graph which can be done by
//    doing a DFS from each node. Thus complexity for this step will be
//    O(n^2)*O(n) = O(n^3).

// Time Complexity = O(n^3)
// Space Complexity = O(n^2)

// Possible improvements:
// 1) Mnemonization can be used in the graph search for better performance

#ifndef CIRCUS_TOWER_H
#define CIRCUS_TOWER_H

#include <algorithm>
#include <vector>

#include "absl/container/flat_hash_map.h"

struct PersonDimensions {
  int height;
  int weight;
};

// Creates adjacency list from sorted array
void FillAjacencyList(
    const std::vector<PersonDimensions> &sorted_dims,
    absl::flat_hash_map<size_t, std::vector<size_t>> &adjacency_list);

// Depth-First-Search given a starting node while keepting track of depth
int DFS(int distance, size_t node,
        absl::flat_hash_map<size_t, std::vector<size_t>> &adjacency_list);

// Iterates through all nodes and calls DFS on each one while keeping track of
// max depth
int LongestPathInGraph(
    absl::flat_hash_map<size_t, std::vector<size_t>> &adjacency_list);

// Sorts the array and calls all functions to execute subsequent steps (main
// function)
int LongestTower(const std::vector<PersonDimensions> &dimensions);

#endif