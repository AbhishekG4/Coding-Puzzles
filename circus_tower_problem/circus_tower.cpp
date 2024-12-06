#include "circus_tower.h"


void BinaryInsert(size_t person, size_t i, size_t j, std::vector<size_t> &longest_seq_ends, std::vector<size_t> &prev, const std::vector<PersonDimensions> &dimensions){
  size_t mid = (j+i)/2;
  int search_height = dimensions[person].height;
  int mid_height = dimensions[longest_seq_ends[mid]].height;

  //base case
  if(longest_seq_ends.size()==1){         //edge case: only one element to compare
    if(search_height<=mid_height) longest_seq_ends[0] == person;
    else{
      longest_seq_ends.push_back(person);
      prev[person] = longest_seq_ends[0];
    }
    return;
  }
  if(mid == longest_seq_ends.size()-1){   //edge case: person has greatest height in which case we append
    longest_seq_ends.push_back(person);
    prev[person] = longest_seq_ends[mid];
    return;
  }
  if(!mid) longest_seq_ends[0] = person;  //edge case: smaller than the smallest

  if(i==j) return;

  int next_height = dimensions[longest_seq_ends[mid+1]].height;
  if(mid_height<search_height && next_height>=search_height){     //if search position found, insert by replacing
    longest_seq_ends[mid+1] = person;
    prev[person] = longest_seq_ends[mid];
    return;
  }

  //recursive case
  if(next_height<search_height) BinaryInsert(person,mid+1,j,longest_seq_ends,prev,dimensions);
  else BinaryInsert(person,i,mid,longest_seq_ends,prev,dimensions);
}

void PatienceSort(const std::vector<PersonDimensions> &dimensions, std::vector<size_t> &longest_seq_ends, std::vector<size_t> &prev){
  if(longest_seq_ends.size()==0) longest_seq_ends.push_back(0);   //initializing the patience sort array
  for(size_t i=1; i<dimensions.size(); i++){
    size_t end = longest_seq_ends.size()-1;
    BinaryInsert(i,0,end,longest_seq_ends,prev,dimensions);    
  }
}

std::vector<PersonDimensions> LongestTower(
    const std::vector<PersonDimensions> &dimensions) {
  std::vector<PersonDimensions> sorted_dimensions = dimensions;
  std::vector<PersonDimensions> longest_tower;
  std::vector<size_t> longest_seq_ends;       // this is the patience sorted array which stores the ends to LIS of all possible sizes
  std::vector<size_t> prev_person(dimensions.size(),0);

  // sorting index arrays
  std::sort(sorted_dimensions.begin(), sorted_dimensions.end(),
            [](const PersonDimensions &x,
               const PersonDimensions &y) {  // sorting by weights
              return x.weight < y.weight;
            });
  
  // Performing the patience sort
  PatienceSort(sorted_dimensions, longest_seq_ends, prev_person);
  
  //Forming tower by moving through the prev_person array
  size_t next_person = longest_seq_ends[longest_seq_ends.size()-1];
  for(size_t cnt=0;cnt<longest_seq_ends.size();cnt++){
    longest_tower.push_back(sorted_dimensions[next_person]);
    next_person = prev_person[next_person];
  }
  std::reverse(longest_tower.begin(),longest_tower.end());  // as we get result in descending order


  return longest_tower;
}
