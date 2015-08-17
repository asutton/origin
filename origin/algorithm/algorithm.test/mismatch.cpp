// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/algorithm.hpp>

#include <cassert>
#include <vector>

int main() 
{
  int a1[3] { 1, 1, 2 };
  int a2[3] { 2, 1, 2 };
  std::equal_to<int> eq;
  assert(origin::mismatch(a1, a2) == std::make_pair(a1, a2));
  assert(origin::mismatch(a1, a2, eq) == std::make_pair(a1, a2));
}
