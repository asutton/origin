// Copyright (c) 2008-2014 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <cassert>
#include <iostream>
#include <vector>

#include <origin/sequence/algorithm.hpp>

struct trip_count {
  trip_count() : n(0) { }

  template<typename T>
    void operator()(const T&) { ++n; }
  
  int n = 0;
};

struct S {
  void f() { ++x; }
  int x = 0;
};

int main() 
{
  int a[3] { 1, 2, 3 };

  // std::cout << origin::for_each(a, a + 3, trip_count{}).n << '\n';

  assert(origin::for_each(a, a + 3, trip_count{}).n == 3);
  assert(origin::for_each(a, trip_count{}).n == 3);
  assert(origin::for_each({1, 2, 3}, trip_count{}).n == 3);

  S s[3];
  origin::for_each(s, s + 3, &S::f);
  origin::for_each(s, &S::f);
  assert(s[0].x == 2 and s[1].x == 2 and s[2].x == 2);
}
