// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/algorithm.hpp>

#include <cassert>
#include <vector>
#include <iostream>


int main() 
{
  int a1[3] { 1, 1, 2 };

  std::vector<int> v1(3);
  origin::copy(a1, a1 + 3, v1.begin());
  assert(std::equal(a1, a1 + 3, v1.begin()));

  std::vector<int> v2(3);
  origin::copy(a1, v2);
  assert(std::equal(a1, a1 + 3, v2.begin()));
}
