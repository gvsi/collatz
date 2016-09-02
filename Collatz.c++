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

#include "Collatz.h"

using namespace std;

// ------------
// collatz_read
// ------------

bool collatz_read (istream& r, int& i, int& j) {
    if (!(r >> i))
        return false;
    r >> j;
    return true;}

int cycle_length(int n) {
  assert(n > 0);
  int c = 1;
  while (n > 1) {
    if ((n % 2) == 0) {
      n = (n / 2);
      c += 1;
    } else {
      n = (3 * n + 1) >> 1; // combines two steps
      c += 2;
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
    assert(min <= max);
    int max_length = 1;
    for (int n = i; n <= j; n++) {
      int length = cycle_length(n);
      if (length > max_length)
        max_length = length;
    }
    return max_length;}

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
