#include <benchmark/benchmark.h>

#include <random>

#include "shortest_superseq.h"

// Function to populate random array with n values
void PopulateRandomArray(std::vector<int> &array, int n) {
  std::random_device rd;
  std::mt19937 prng(rd());
  std::uniform_int_distribution<int> distribution(0, 4000);

  for (int i = 0; i < n; i++) {
    array.push_back(distribution(prng));
  }
}

static void BM_ShortestSuperseq(benchmark::State &state) {
  std::vector<int> long_array, short_array;
  int long_array_size = state.range(0);
  int short_array_size = long_array_size / 4;

  long_array.reserve(long_array_size);
  short_array.reserve(short_array_size);

  PopulateRandomArray(long_array, long_array_size);
  PopulateRandomArray(short_array, short_array_size);

  for (auto _ : state) {
    SubArray result = ShortestSuperseq(short_array, long_array);
  }
}

// Benchmarking on different values of n
BENCHMARK(BM_ShortestSuperseq)->DenseRange(6, 100, 6);

BENCHMARK_MAIN();