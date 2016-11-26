// --------------------------
// projects/collatz/Collatz.h
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------

#ifndef Collatz_h
#define Collatz_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair

extern int cache[2000001];

using namespace std;

// ------------
// collatz_read
// ------------

/**
 * read two ints from r into i an j
 * @param r an istream
 * @param i an int
 * @param j an int
 * @return true if the read is successful, otherwise false
 */
bool collatz_read(istream &r, int &i, int &j);

// ------------
// collatz_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length of the range [i, j]
 */
int collatz_eval(int i, int j);

/* different collatz eval versions */

int unoptimized_collatz_eval(int i, int j);
int optimized_collatz_eval(int i, int j);

// ------------
// collatz_individual_solve
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @return the cycle length of n
 */
int collatz_individual_solve(int n);

// -------------
// collatz_print
// -------------

/**
 * print three ints to w
 * @param w an ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void collatz_print(ostream &w, int i, int j, int v);

// -------------
// collatz_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void collatz_solve(istream &r, ostream &w);

#endif // Collatz_h
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


#define CACHE_SIZE 2000001
#define CACHE_OPT

int cache[2000001];

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

int collatz_eval(int i, int j) {
  int lowerBound;
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
#endif

  return maxCycleLength;
}

/* Optimized cache */
int optimized_collatz_eval(int i, int j) {
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
}

/* Unoptimized cache */
int unoptimized_collatz_eval(int i, int j) {
  int maxCycleLength = 0;
  while (i <= j) {
    int cycleLength = collatz_individual_solve(i);
    if (cycleLength > maxCycleLength) {
      maxCycleLength = cycleLength;
    }
    i++;
  }
  return maxCycleLength;
}
/*
Helper method: collatz_individual_solve
*/

int collatz_individual_solve(int n) {
  int cycleLength = 1;
  while (n > 1) {
    // even
    if (n % 2 == 0) {
      n = n / 2;
    }
    // odd
    else {
      n = 3 * n + 1;
      n = n /
          2; // small optimization: will automatically assume odd becomes even
      cycleLength++;
    }
    cycleLength = cycleLength + 1;
    if (cycleLength < 0) {
      cout << cycleLength << endl;
    }
  }

  return cycleLength;
}

// -------------
// collatz_print
// -------------

void collatz_print(ostream &w, int i, int j, int v) {
  w << i << " " << j << " " << v << endl;
}

// -------------
// collatz_solve
// -------------

void collatz_solve(istream &r, ostream &w) {
  int i;
  int j;
  while (collatz_read(r, i, j)) {
    const int v = collatz_eval(i, j);
    collatz_print(w, i, j, v);
  }
}
// -------------------------------
// projects/collatz/RunCollatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// -------------------------------

// --------
// includes
// --------

#include <iostream> // cin, cout


// ----
// main
// ----

int main() {
  using namespace std;
  collatz_solve(cin, cout);
  return 0;
}
