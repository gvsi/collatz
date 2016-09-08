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
#include <vector>
#include <stdint.h>


// --------
// optimazations
// --------

/// Uses a cache to store values
#define LAZY_CACHE_OPT

/// Skips one step in the computation of cycle_length if the number is odd
#define DOUBLE_ODD_STEP_OPT

/// Only checks half the range if the property discussed in class is satisfied
#define HALF_SPACE_CHECK


using namespace std;

#ifdef DOUBLE_ODD_STEP_OPT
/// A cache able to store values of `cycle_length` up to `cycle_length(1000000)``
vector<int> cache(1000001);
#endif

// ------------
// collatz_read
// ------------

bool collatz_read(istream &r, int &i, int &j) {
  if (!(r >> i))
    return false;
  r >> j;
  return true;
}

/**
 * calculates the cycle length of a positive integer
 * @param n a positive integer
 */

int cycle_length(int n) {
  // cout << "Calculating cycle_length of " << n << endl;
  assert(n > 0);
  int c;

#ifdef LAZY_CACHE_OPT
  bool cacheFit = n < (int) cache.size();

  if (cacheFit && cache.at(n)) {
    // Cache hit
    c = cache.at(n);
    // cout << "Hit! cycle_length of " << n << endl;
  } else {
    if ((n % 2) == 0) {
      c = 1 + cycle_length(n >> 1);
    } else {

#ifdef DOUBLE_ODD_STEP_OPT
      c = 2 + cycle_length((3 * n + 1) >> 1); // combines two steps
#else
      c = 1 + cycle_length((3 * n + 1));
#endif
    }

    // Store value in cache, if it fits
    if (cacheFit) {
      cache.at(n) = c;
    }
  }
#else
  // Standard algorithm discussed in class
  c = 1;
  while (n > 1) {
    if ((n % 2) == 0)
      n = (n / 2);
    else
      n = (3 * n) + 1;
    ++c;
  }
#endif

  assert(c > 0);
  return c;
}

/**
 * is a helper function that calculates that maximum cycle length between lower_bound and upper_bound inclusive
 * @param lower_bound a positive integer
 * @param upper_bound a positive integer
 */

int max_cycle_length(int lower_bound, int upper_bound) {
  assert(lower_bound > 0);
  assert(upper_bound > 0);
  int max_length = 1;

  // loop through the values in the range, storing the max as we go
  for (int i = lower_bound; i <= upper_bound; ++i) {
    int length = cycle_length(i);
    if (length > max_length)
      max_length = length;
  }
  assert(max_length > 0);
  return max_length;
}
// ------------
// collatz_eval
// ------------

int collatz_eval(int i, int j) {
  // Set base value of 1; i.e. cycle_length(1) == 1
  cache[1] = 1;

  // let i <= j always
  if (i > j) {
    int temp = i;
    i = j;
    j = temp;
  }

  assert(i <= j);

#ifdef HALF_SPACE_CHECK
  int m = (j / 2) + 1;
  if (i < m) {
    assert(i < m);
    return collatz_eval(m, j);
  } else {
    assert(i >= m);
    return max_cycle_length(i, j);
  }
#else
  return max_cycle_length(i, j);
#endif
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
