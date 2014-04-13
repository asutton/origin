// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <cassert>
#include <vector>

#include <iostream>

#include <origin/range/algorithm.hpp>

int main() 
{
  int a1[3] { 1, 1, 2 };
  int a2[2] { 1, 1 };
  std::equal_to<int> eq;
  assert(origin::find_end(a1, a2) == a1);
  assert(origin::find_end(a1, a2, eq) == a1);
}
