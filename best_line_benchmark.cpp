#include <benchmark/benchmark.h>

#include <ctime>

#include "best_line.h"

// Function to populate a random graph of rational numbers with n points
std::vector<Point> PopulateRandomGraph(std::vector<Point> &graph, int n) {
  double lower_bound = -20000;
  double upper_bound = 2000;

  std::srand(std::time(NULL));
  for (int i = 0; i < n; i++) {
    double x =
        lower_bound + (upper_bound - lower_bound) * (std::rand() / RAND_MAX);
    double y =
        lower_bound + (upper_bound - lower_bound) * (std::rand() / RAND_MAX);

    graph.push_back({x, y});
  }

  return graph;
}

// Function to populate a random graph of integers with n points
std::vector<Point> PopulateRandomIntGraph(std::vector<Point> &graph, int n) {
  int lower_bound = -20;
  int upper_bound = 20;

  std::srand(std::time(NULL));
  for (int i = 0; i < n; i++) {
    int x = lower_bound + std::rand() % (upper_bound - lower_bound);
    int y = lower_bound + std::rand() % (upper_bound - lower_bound);

    graph.push_back({(double)x, (double)y});
  }

  return graph;
}

// Benchmark function
static void BM_GetBestLine(benchmark::State &state) {
  std::vector<Point> graph;
  graph.reserve(state.range(0));

  PopulateRandomIntGraph(
      graph,
      state.range(0));  // Graph being passed by reference to avoid copying

  for (auto _ : state) {
    Line bestLine = GetBestLine(graph);
  }
}

// Benchmarking on different values of n
BENCHMARK(BM_GetBestLine)->DenseRange(1, 56, 3);

BENCHMARK_MAIN();