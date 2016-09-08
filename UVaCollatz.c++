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
bool collatz_read (istream& r, int& i, int& j);

// ------------
// collatz_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length of the range [i, j]
 */
int collatz_eval (int i, int j);

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
void collatz_print (ostream& w, int i, int j, int v);

// -------------
// collatz_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void collatz_solve (istream& r, ostream& w);

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
    // Cache hit
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

int main () {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;}
