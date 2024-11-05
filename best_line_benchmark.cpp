#include <benchmark/benchmark.h>

#include <ctime>
#include <random>

#include "best_line.h"

// Function to populate a random graph of rational numbers with n points
std::vector<Point> PopulateRandomGraph(std::vector<Point> &graph, int n) {
  std::mt19937 generator(static_cast<unsigned int>(std::time(NULL)));
  std::uniform_real_distribution<double> distribution(-2000, 2000);

  for (int i = 0; i < n; i++) {
    double x = distribution(generator);
    double y = distribution(generator);
    graph.push_back({x, y});
  }

  return graph;
}

// Function to populate a random graph of integers with n points
std::vector<Point> PopulateRandomIntGraph(std::vector<Point> &graph, int n) {
  std::mt19937 generator(static_cast<unsigned int>(std::time(NULL)));
  std::uniform_int_distribution<int> distribution(-20, 20);

  for (int i = 0; i < n; i++) {
    int x = distribution(generator);
    int y = distribution(generator);
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