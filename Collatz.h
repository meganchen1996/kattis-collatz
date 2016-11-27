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
