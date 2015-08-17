// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/algorithm.hpp>

#include <cassert>


bool pos(int n) { return n > 0; }

int main() 
{
  int a[3] { 1, 2, 3 };
  assert(origin::count_if(a, a + 3, pos, 0) == 3);
  assert(origin::count_if(a, a + 3, pos) == 3);
  assert(origin::count_if(a, pos, 0) == 3);
  assert(origin::count_if(a, pos) == 3);
  assert(origin::count_if({1, 2, 3}, pos, 0) == 3);
  assert(origin::count_if({1, 2, 3}, pos) == 3);
}
