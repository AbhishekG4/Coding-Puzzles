#include <benchmark/benchmark.h>
#include <random>
#include "shortest_superseq.h"

//Function to populate random array with n values
void PopulateRandomArray(std::vector<int> &array, int n){
    std::random_device rd;
    std::mt19937 prng(rd());
    std::uniform_int_distribution<int> distribution(-2000,2000);

    for(int i=0;i<n;i++){
        array.push_back(distribution(prng));
    }
}

static void BM_ShortestSuperseq(benchmark::State &state){
    std::vector<int> long_array, short_array;
    long_array.reserve(state.range(0));
    short_array.reserve(5%state.range(0));

    PopulateRandomArray(long_array, state.range(0));
    PopulateRandomArray(short_array, 5%state.range(0));

    for(auto _ : state){
        SubArray result = ShortestSuperseq(short_array, long_array);
    }
}

// Benchmarking on different values of n
BENCHMARK(BM_ShortestSuperseq)->DenseRange(4,20);

BENCHMARK_MAIN();