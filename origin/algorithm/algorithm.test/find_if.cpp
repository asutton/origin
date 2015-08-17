// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/algorithm.hpp>

#include <cassert>
#include <vector>


bool pos(int n) { return n > 0; }

int main() 
{
  int a[3] { 1, 2, 3 };
  assert(origin::find_if(a, pos) == a);

  std::vector<int> v { 1, 2, 3 };
  assert(origin::find_if(v, pos) == v.begin());

  const std::vector<int>& cv = v;
  assert(origin::find_if(cv, pos) == cv.begin());
}
