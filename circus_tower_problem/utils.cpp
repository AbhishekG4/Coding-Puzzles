#include "utils.h"

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