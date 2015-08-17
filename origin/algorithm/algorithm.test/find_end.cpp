// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/algorithm.hpp>

#include <cassert>
#include <vector>


int main() 
{
  int a1[3] { 1, 1, 2 };
  int a2[2] { 1, 1 };
  origin::equal_to<int> eq;
  assert(origin::find_end(a1, a2) == a1);
  assert(origin::find_end(a1, a2, eq) == a1);
}
