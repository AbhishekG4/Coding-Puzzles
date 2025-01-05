#include "shortest_superseq.h"

SubArray ShortestSuperseq(const std::vector<int> &short_array,
                          const std::vector<int> &long_array) {
  absl::flat_hash_set<int> search_seq;  // search elements
  size_t nxt_out = 0;                   // start of window
  size_t nxt_in = 0;                    // next of end of window
  size_t min_start = 0;
  size_t min_end = long_array.size();

  for (int i : short_array) search_seq.insert(i);

  absl::flat_hash_set<int>
      window_ele;  // hash set for search elements present in window
  while (nxt_in < long_array.size()) {
    if (window_ele.size() <
        search_seq.size()) {  // expanding if we don't have all search elements
      if (search_seq.count(long_array[nxt_in]))
        window_ele.insert(long_array[nxt_in]);
      nxt_in++;
    } else {  // contracting if we have all search elements
      window_ele.erase(long_array[nxt_out]);
      nxt_out++;
    }

    if (window_ele.size() == search_seq.size()) {
      if (min_end - min_start >
          nxt_in - 1 - nxt_out) {  // updating golbal minimum array ends
        min_end = nxt_in - 1;
        min_start = nxt_out;
      }
    }
  }

  return {min_start, min_end};
}