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

int cycle_length(int n) {
  // cout << "Calculating cycle_length of " << n << endl;
  assert(n > 0);

  if (n > cache.size()) {
    if ((n % 2) == 0) {
      return 1 + cycle_length(n / 2);
    } else {
      return 2 + cycle_length((3 * n + 1) >> 1); // combines two steps
    }
  }

  if (!cache.at(n)) {
    if ((n % 2) == 0) {
      cache.at(n) = 1 + cycle_length(n / 2);
    } else {
      cache.at(n) = 2 + cycle_length((3 * n + 1) >> 1); // combines two steps
    }
  }
  int length = cache.at(n);
  assert(length > 0);
  return length;}

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
