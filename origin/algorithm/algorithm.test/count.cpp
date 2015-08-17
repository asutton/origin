// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/algorithm.hpp>

#include <cassert>
#include <vector>


int main() 
{
  int a[3] { 1, 2, 3 };
  assert(origin::count(a, 1) == 1);

  std::vector<int> v { 1, 2, 3 };
  assert(origin::count(v, 1) == 1);

  const std::vector<int>& cv = v;
  assert(origin::count(cv, 1) == 1);
}
