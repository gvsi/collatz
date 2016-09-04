// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#define LAZY_CACHE_OPT
#define DOUBLE_ODD_STEP_OPT

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <vector>
#include <stdint.h>

#include "Collatz.h"

using namespace std;

#ifdef DOUBLE_ODD_STEP_OPT
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

/*!
 * calculates the cycle length of a positive integer
 * @param n a positive integer
 */

int cycle_length(int64_t n) {
  // cout << "Calculating cycle_length of " << n << endl;
  assert(n > 0);

  int c;

#ifdef LAZY_CACHE_OPT
  bool cacheFit = n < cache.size();

  if (cacheFit && cache.at(n)) {
    // Cache hit
    c = cache.at(n);
    // cout << "Hit! cycle_length of " << n << endl;
  } else {
    if ((n % 2) == 0) {
      c = 1 + cycle_length(n >> 1);
    } else {
      int64_t next;

#ifdef DOUBLE_ODD_STEP_OPT
      next = (3 * n + 1) >> 1; // combines two steps
      c = 2 + cycle_length(next);
#else
      next = (3 * n + 1); // combines two steps
      c = 1 + cycle_length(next);
#endif
    }

    // Store value in cache, if it fits
    if (cacheFit) {
      cache.at(n) = c;
    }
  }
#else
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

// ------------
// collatz_eval
// ------------

int collatz_eval(int i, int j) {
  int max, min;
  if (i > j) {
    max = i;
    min = j;
  } else {
    max = j;
    min = i;
  }

  cache[1] = 1;

  assert(min <= max);

  int m = (max / 2) + 1;
  if (min < m) {
    return collatz_eval(m, max);
  } else {
    int max_length = 1;
    for (int n = min; n <= max; n++) {
      int length = cycle_length(n);
      if (length > max_length)
        max_length = length;
    }
    return max_length;
  }
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
