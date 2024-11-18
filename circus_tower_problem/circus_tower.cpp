#include "circus_tower.h"

void FillAjacencyList(
    const std::vector<PersonDimensions> &sorted_dims,
    absl::flat_hash_map<size_t, std::vector<size_t>> &adjacency_list) {
  for (size_t i = 0; i < sorted_dims.size() - 1; i++) {
    for (size_t j = i + 1; j < sorted_dims.size(); j++) {
      if (sorted_dims[i].height <
          sorted_dims[j].height) {  // weights are sorted and in order, we need
                                    // to check for heights
        adjacency_list[i].push_back(j);
      }
    }
  }
}

int DFS(int distance, size_t node,
        absl::flat_hash_map<size_t, std::vector<size_t>> &adjacency_list) {
  int max_distance = ++distance;  // base case built in
  std::vector<size_t> neighbors = adjacency_list[node];

  for (size_t next_node : neighbors) {
    max_distance =
        std::max(max_distance, DFS(distance, next_node, adjacency_list));
  }

  return max_distance;
}

int LongestPathInGraph(
    absl::flat_hash_map<size_t, std::vector<size_t>> &adjacency_list) {
  int longest_path = 0;
  std::vector<size_t> keys;

  for (auto pair : adjacency_list) keys.push_back(pair.first);
  for (size_t node :
       keys) {  // going through all nodes and starting a DFS from there
    longest_path = std::max(longest_path, DFS(0, node, adjacency_list));
  }

  return longest_path;
}

int LongestTower(const std::vector<PersonDimensions> &dimensions) {
  std::vector<PersonDimensions> sorted_dimensions = dimensions;
  absl::flat_hash_map<size_t, std::vector<size_t>> adjacency_list;

  // sorting index arrays
  std::sort(sorted_dimensions.begin(), sorted_dimensions.end(),
            [](const PersonDimensions &x,
               const PersonDimensions &y) {  // sorting by weights
              return x.weight < y.weight;
            });
  // Creating adjacency list
  FillAjacencyList(sorted_dimensions, adjacency_list);

  // Find longest path in graph
  return LongestPathInGraph(adjacency_list);
}
