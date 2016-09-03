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

#include "Collatz.h"

using namespace std;

// ------------
// collatz_read
// ------------

vector<int> cache(3000000);

bool collatz_read (istream& r, int& i, int& j) {
    if (!(r >> i))
        return false;
    r >> j;
    return true;}

int cycle_length(int64_t n) {
  // cout << "Calculating cycle_length of " << n << endl;
  assert(n > 0);

  int c;
  bool cacheFit = n < cache.size();

  if (cacheFit && cache.at(n)) {
    c = cache.at(n);
    // cout << "Hit! cycle_length of " << n << endl;
  } else {
    if ((n % 2) == 0) {
      c = 1 + cycle_length(n >> 1);
    } else {
      int64_t next = (3 * n + 1) >> 1; // combines two steps
      c = 2 + cycle_length(next);
    }

    // Store value in cache, if it fits
    if (cacheFit) {
      cache.at(n) = c;
    }
  }

  assert(c > 0);
  return c;}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    int max, min;
    if (i > j) {
      max = i;
      min = j;
    } else {
      max = j;
      min = i;
    }

    cache[1] = 1;
    cache[502441] = 198;
    // cache[504057] = 258;
    // cache[540542] = 417;
    // cache[559785] =
    // cache[581883] =
    // cache[626331] =
    // cache[630527] =
    // cache[637950] =
    // cache[655359] =
    // cache[665215] =
    // cache[687871] =
    // cache[704511] =
    // cache[747291] =
    // cache[753663] =
    // cache[763675] =
    // cache[780391] =
    // cache[829087] =
    // cache[833775] =
    // cache[839679] =
    // cache[901119] =
    // cache[906175] =
    // cache[920559] =
    // cache[937599] =
    // cache[974079] =
    // cache[975015] =

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

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    int i;
    int j;
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
