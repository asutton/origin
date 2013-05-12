// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <cassert>
#include <vector>

#include <origin/range/algorithm.hpp>

int main() 
{
  int a[3] { 1, 2, 3 };
  assert(origin::count(a, 1) == 1);

  std::vector<int> v { 1, 2, 3 };
  assert(origin::count(v, 1) == 1);

  const std::vector<int>& cv = v;
  assert(origin::count(cv, 1) == 1);
}
