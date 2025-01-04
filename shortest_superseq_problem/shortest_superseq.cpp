#include "shortest_superseq.h"

SubArray ShortestSuperseq(const std::vector<int> &in_short, const std::vector<int> &in_long){
    absl::flat_hash_set<int> search_seq;    //search elements
    int nxt_out = 0;      //start of window
    int nxt_in = 0;        //next of end of window
    int min_start = 0;
    int min_end = (int)in_long.size();

    for(int i : in_short) search_seq.insert(i);

    absl::flat_hash_set<int> window_ele;    //hash set for search elements present in window
    while(nxt_in<(int)in_long.size()){
        if(window_ele.size()<search_seq.size()){
            if(search_seq.count(in_long[nxt_in])) window_ele.insert(in_long[nxt_in]);
            nxt_in++;            
        }
        else{
            if(min_end-min_start>nxt_in-1-nxt_out){
                min_end = nxt_in-1;
                min_start = nxt_out;
            }
            window_ele.erase(in_long[nxt_out]);
            nxt_out++;
        }
    }

    return {min_start, min_end};
}