#include <benchmark/benchmark.h>

#include "circus_tower.h"
#include "utils.h"

// Benchmark function
static void BM_LongestTower(benchmark::State &state) {
  std::vector<PersonDimensions> dims;
  dims.reserve(state.range(0));

  PopulateRandomIntDims(dims, state.range(0));

  for (auto _ : state) {
    std::vector<PersonDimensions> longest_tower = LongestTower2(dims);
  }
}

// Benchmarking on different values of n
BENCHMARK(BM_LongestTower)->DenseRange(2, 400, 10);
// BENCHMARK(BM_LongestTower)->Args({1000000});

BENCHMARK_MAIN();