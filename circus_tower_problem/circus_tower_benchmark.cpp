#include <benchmark/benchmark.h>

#include <random>

#include "circus_tower.h"

// Function to populate a random group of n people with integer heights and
// weights
void PopulateRandomIntDims(std::vector<PersonDimensions> &dims, int n) {
  std::random_device rd;
  std::mt19937 prng(rd());  // Initializing PRNG
  std::uniform_int_distribution<int> distribution(0, 4000);

  for (int i = 0; i < n; i++) {
    int ht = distribution(prng);
    int wt = distribution(prng);
    dims.push_back({ht, wt});
  }
}

// Benchmark function
static void BM_LongestTower(benchmark::State &state) {
  std::vector<PersonDimensions> dims;
  dims.reserve(state.range(0));

  PopulateRandomIntDims(dims, state.range(0));

  for (auto _ : state) {
    std::vector<PersonDimensions> longest_tower = LongestTower(dims);
  }
}

// Benchmarking on different values of n
BENCHMARK(BM_LongestTower)->DenseRange(2, 20, 2);
// BENCHMARK(BM_LongestTower)->Args({1000000});

BENCHMARK_MAIN();