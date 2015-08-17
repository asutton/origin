// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/algorithm.hpp>

#include <cassert>
#include <vector>


int main() 
{
  int a[3] { 1, 2, 3 };
  assert(origin::find(a, 1) == a);

  std::vector<int> v { 1, 2, 3 };
  assert(origin::find(v, 1) == v.begin());

  const std::vector<int>& cv = v;
  assert(origin::find(cv, 1) == v.begin());
}
