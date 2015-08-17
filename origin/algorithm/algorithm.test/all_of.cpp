// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/algorithm.hpp>

#include <cassert>


bool pos(int n) { return n > 0; }


int main() 
{
  int a[3] { 1, 2, 3 };
  assert(origin::all_of(a, a + 3, pos));
  // assert(origin::all_of(a, pos));
  // assert(origin::all_of({1, 2, 3}, pos));
}
