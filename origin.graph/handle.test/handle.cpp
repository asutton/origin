// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <cassert>
#include <iostream>
#include <vector>

#include <origin.graph/handle.hpp>

using namespace std;
using namespace origin;

template<typename H>
  void check_eq()
  {
    H a;
    H b = 1;
    H c = b;
    assert(a == a);
    assert(a != b);
    assert(b == c);
  }

template<typename H>
  void check_ord()
  {
    H a;
    H b = 1;

    assert(a <= a);
    assert(a >= a);

    assert(a < b);
    assert(a <= b);

    assert(b > a);
    assert(b >= a);
  }


template<typename H>
  void check_interop()
  {
    vector<int> v {3, 2, 1};
    H h = 0;
    assert(v[h] == 3);
  }

int f(int n) { return n; }

// Check that conversion to integral types is unambigous and actually
// converts to an integer and not bool.
template<typename H>
  void check_conv()
  {
    H a = 3;
    assert(f(a) == 3);
  }

// Support for testing conversions.
void fv(vertex_handle v) { }
void fe(edge_handle e) { }

int main()
{
  check_eq<handle>();
  check_ord<handle>();
  check_interop<handle>();

  check_eq<vertex_handle>();
  check_ord<vertex_handle>();
  check_interop<vertex_handle>();


  // I don't know if this is good or not.
  handle a = 3;
  handle b = 1;
  assert(a + b == 4);

  vertex_handle v;
  fv(v); // OK
  // fe(v); // Error: cannot convert v to e

  edge_handle e;
  fe(e); // Ok
  // fv(e); // Error: cannot convert e to v

  // FIXME: This should not work.
  assert(v == e);
}
