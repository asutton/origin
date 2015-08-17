// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/algorithm.hpp>

#include <cassert>
#include <vector>


int main() 
{
  int a1[3] { 1, 1, 2 };
  assert(origin::adjacent_find(a1) == a1);

  int a2[3] { 1, 1, 2 };
  assert(origin::adjacent_find(a2, std::equal_to<int>{}) == a2);
}
