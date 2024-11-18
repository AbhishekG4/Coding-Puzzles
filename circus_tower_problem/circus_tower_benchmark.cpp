#include <benchmark/benchmark.h>

#include <random>

#include "circus_tower.h"

// Function to populate a random group of n people with integer heights and
// weights
std::vector<PersonDimensions> PopulateRandomIntGraph(
    std::vector<PersonDimensions> &dims, int n) {
  std::random_device rd;
  std::uniform_int_distribution<int> distribution(0, 250);

  for (int i = 0; i < n; i++) {
    int ht = distribution(rd);
    int wt = distribution(rd);
    dims.push_back({ht, wt});
  }

  return dims;
}

// Benchmark function
static void BM_LongestTower(benchmark::State &state) {
  std::vector<PersonDimensions> dims;
  dims.reserve(state.range(0));

  PopulateRandomIntGraph(
      dims,
      state.range(0));  // Set being passed by reference to avoid copying

  for (auto _ : state) {
    int longest_tower = LongestTower(dims);
  }
}

// Benchmarking on different values of n
BENCHMARK(BM_LongestTower)->DenseRange(2, 20, 2);

BENCHMARK_MAIN();