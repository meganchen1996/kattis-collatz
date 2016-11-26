// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <string>

#include "Collatz.h"

#define CACHE_SIZE 2000001
#define CACHE_OPT

int cache[2000001];
//the number, and the cycle length when it's first seen in i sequence
map<int, int> freq_dict;

using namespace std;

// ------------
// collatz_read
// ------------

bool collatz_read(istream &r, int &i, int &j) {
  if (!(r >> i))
    return false;
  r >> j;
  return true;
}

// ------------
// collatz_eval
// ------------

void collatz_eval(int i, int j, ostream& w) {
  int meet_num; 
  bool has_found_meet = false;
  vector<int> numbers {i, j}; 
  // find the cycle length for i
  // int i_cycle_length = collatz_individual_solve(i, meet_num, has_found_meet); 
  // // find the cycle length for j
  // int j_cycle_length = collatz_individual_solve(j, meet_num, has_found_meet);

  vector<int> results = collatz_solve(numbers, meet_num, has_found_meet);


  results[0] = freq_dict[meet_num];
  collatz_print(w, i, j, results, meet_num);

  // reset the hash table 
  freq_dict.clear();

/*  int lowerBound;
  int upperBound;
  if (i < j) {
    lowerBound = i;
    upperBound = j;
  } else {
    lowerBound = j;
    upperBound = i;
  }
  int maxCycleLength;
#ifdef CACHE_OPT
  maxCycleLength = optimized_collatz_eval(lowerBound, upperBound);
#else
  int maxCycleLength = unoptimized_collatz_eval(lowerBound, upperBound);
#endif*/
}

/*
Helper method: collatz_individual_solve
*/

vector<int> collatz_solve(vector<int>& numbers, int& meet_num, bool& has_found_meet) {
  vector<int> result {0, 0};
  for(int i = 0; i < 2; i++) {
    int cycleLength = 0;
    int& n = numbers[i];
    while (n != 1) {
      //if you see this number in i's sequence & have not seen it before, 
      //flip to be true and record it's cycle length
      if(i == 0 && freq_dict.find(n) == freq_dict.end()) {
        freq_dict[n] = cycleLength;
      }
      //if you're in j's sequence & you saw this number in i & you haven't found the meet # yet
      if(i == 1 && freq_dict.find(n) != freq_dict.end() && !has_found_meet) {
        has_found_meet = true;
        meet_num = n;
        result[1] = cycleLength;
      }
      // even
      if (n % 2 == 0) {
        n = n / 2;
      }
      // odd
      else {
        n = 3 * n + 1;
        //n = n / 2; // small optimization: will automatically assume odd becomes even
        //cycleLength++;
      }


      cycleLength++;
      // if (cycleLength < 0) {
      //   cout << cycleLength << endl;
      // }
    }
  }

  return result;
}


/* Optimized cache */
/*int optimized_collatz_eval(int i, int j) {
  int maxCycleLength = 0;
  while (i <= j) {
    int cycleLength = 0;

    // checks if the value is in the cache
    if (i < 2000001) {
      if (cache[i] != 0) {
        cycleLength = cache[i];
      } else {
        cycleLength = collatz_individual_solve(i);
        cache[i] = cycleLength;
      }

    } else {
      cycleLength = collatz_individual_solve(i);
    }

    if (cycleLength > maxCycleLength) {
      maxCycleLength = cycleLength;
    }
    i++;
  }
  return maxCycleLength;
}*/

/* Unoptimized cache */
/*int unoptimized_collatz_eval(int i, int j) {
  int maxCycleLength = 0;
  while (i <= j) {
    int cycleLength = collatz_individual_solve(i);
    if (cycleLength > maxCycleLength) {
      maxCycleLength = cycleLength;
    }
    i++;
  }
  return maxCycleLength;
}*/

// -------------
// collatz_print
// -------------

void collatz_print(ostream &w, 
                  int i, 
                  int j,
                  vector<int> results,
                  int meet) {
  w << i << " needs " << results[0] << " steps, " << j << " needs " << results[1] << " steps, they meet at " << meet << endl;
}

// -------------
// collatz_solve
// -------------

void collatz_solve(istream &r, ostream &w) {
  int i;
  int j;
  while (collatz_read(r, i, j)) {
    if(i != 0 && j != 0)
      collatz_eval(i, j, w);
  }
}
