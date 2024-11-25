#include "circus_tower.h"

void FillAjacencyList(const std::vector<PersonDimensions> &sorted_dims,
                      std::vector<std::vector<size_t>> &adjacency_list) {
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

void DFS(size_t node, const std::vector<std::vector<size_t>> &adjacency_list,
         std::vector<size_t> ongoing_path, std::vector<size_t> &longest_path) {
  ongoing_path.push_back(node);
  const std::vector<size_t> &neighbors = adjacency_list[node];

  // base case
  if (!neighbors.size()) {
    if (ongoing_path.size() > longest_path.size()) longest_path = ongoing_path;
    return;
  }
  // recursive case
  for (size_t next_node : neighbors) {
    DFS(next_node, adjacency_list, ongoing_path, longest_path);
  }

  return;
}

std::vector<size_t> LongestPathInGraph(
    const std::vector<std::vector<size_t>> &adjacency_list) {
  std::vector<size_t> longest_path;

  for (size_t node = 0; node < adjacency_list.size();
       node++) {  // going through all nodes and starting a DFS from there
    std::vector<size_t> path;
    DFS(node, adjacency_list, {}, path);
    if (path.size() > longest_path.size()) longest_path = path;
  }

  return longest_path;
}

std::vector<PersonDimensions> LongestTower(
    const std::vector<PersonDimensions> &dimensions) {
  std::vector<PersonDimensions> sorted_dimensions = dimensions;
  std::vector<std::vector<size_t>> adjacency_list(dimensions.size());
  std::vector<PersonDimensions> longest_tower;

  // sorting index arrays
  std::sort(sorted_dimensions.begin(), sorted_dimensions.end(),
            [](const PersonDimensions &x,
               const PersonDimensions &y) {  // sorting by weights
              return x.weight < y.weight;
            });
  // Creating adjacency list
  FillAjacencyList(sorted_dimensions, adjacency_list);

  // Find longest path in graph
  std::vector<size_t> longest_path = LongestPathInGraph(adjacency_list);

  // Adding people to longest tower
  for (auto person_idx : longest_path)
    longest_tower.push_back(sorted_dimensions[person_idx]);

  return longest_tower;
}
