// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/algorithm.hpp>

#include <cassert>
#include <vector>


bool pos(int n) { return n > 0; }

int main() 
{
  int a[3] { 1, 2, 3 };
  assert(origin::find_if_not(a, pos) == a + 3);

  std::vector<int> v { 1, 2, 3 };
  assert(origin::find_if_not(v, pos) == v.end());

  const std::vector<int>& cv = v;
  assert(origin::find_if_not(cv, pos) == cv.end());
}
