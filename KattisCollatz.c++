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
#include <vector>
#include <tuple>

using namespace std;

// ------------
// collatz_read
// ------------

/**
 * read two long longs from r long longo i an j
 * @param r an istream
 * @param i an long long
 * @param j an long long
 * @return true if the read is successful, otherwise false
 */
bool collatz_read(istream &r, long long &i, long long &j);

// ------------
// collatz_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length of the range [i, j]
 */
void collatz_eval(long long i, long long j, ostream& w);

// ------------
// collatz_individual_solve
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @return the cycle length of n
 */
void collatz_individ_solve(vector<long long>& numbers, long long n);

tuple<long long, long long, long long> get_meet(vector<long long>& i_cycles, vector<long long>& j_cycles);
// -------------
// collatz_print
// -------------

/**
 * print three long longs to w
 * @param w an ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void collatz_print(ostream &w, 
                  long long i, 
                  long long j,
                  tuple<long long, long long, long long> results);

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


using namespace std;

// ------------
// collatz_read
// ------------

bool collatz_read(istream &r, long long &i, long long &j) {
  if (!(r >> i))
    return false;
  r >> j;
  return true;
}

// ------------
// collatz_eval
// ------------

void collatz_eval(long long i, long long j, ostream& w) {
  vector<long long> i_cycles;
  vector<long long> j_cycles;
  collatz_individ_solve(i_cycles, i);
  collatz_individ_solve(j_cycles, j);
  //cout << "i cycles size: " << i_cycles.size() << endl;
  //cout << "j cycles size: " << j_cycles.size() << endl;
  tuple<long long, long long, long long> result = get_meet(i_cycles, j_cycles); 

  collatz_print(w, i, j, result);
}

/*
Helper method: collatz_solve
*/

void collatz_individ_solve(vector<long long>& numbers, long long n) {
  numbers.push_back(n);
  while (n > 1) {
    // even
    if (n % 2 == 0) {
      n = n / 2;
    }
    // odd
    else {
      n = 3 * n + 1;
      //numbers.push_back(n);
      //n = n / 2; // small optimization: will automatically assume odd becomes even
    }
    numbers.push_back(n);
  }

}

//return {i steps, j steps, meet number}
tuple<long long, long long, long long> get_meet(vector<long long>& i_cycles, vector<long long>& j_cycles) {
  if(i_cycles.size() < j_cycles.size()) {
    for(long long i = 0; i < i_cycles.size(); i++) {
      for(long long j = 0; j < j_cycles.size(); j++) {
        //cout << i_cycles[i] << " " << j_cycles[j] << endl;
        //cout << "i steps: " << i << ", j steps: " << j << ", meeted at " << i_cycles[i] << " " << j_cycles[j] << endl;
        if(i_cycles[i] == j_cycles[j]) {
          return make_tuple(i, j, i_cycles[i]);
        }
      }
    }
  } else {
    // j list is smaller
    for(long long j = 0; j < j_cycles.size(); j++) {
      for(long long i = 0; i < i_cycles.size(); i++) {
        //cout << i_cycles[i] << " " << j_cycles[j] << endl;
        //cout << "i steps: " << i << ", j steps: " << j << ", meeted at " << i_cycles[i] << " " << j_cycles[j] << endl;
        if(j_cycles[j] == i_cycles[i]) {
          return make_tuple(i, j, i_cycles[i]);
        }
      }
    }
  }
}

// -------------
// collatz_print
// -------------

void collatz_print(ostream &w, 
                  long long i, 
                  long long j,
                  tuple<long long, long long, long long> results) {
  w << i << " needs " << get<0>(results) << " steps, " 
    << j << " needs " << get<1>(results) << " steps, they meet at " 
    << get<2>(results) << endl;
}

// -------------
// collatz_solve
// -------------

void collatz_solve(istream &r, ostream &w) {
  long long i;
  long long j;
  while (collatz_read(r, i, j)) {
    if(i != 0 && j != 0)
      collatz_eval(i, j, w);
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
