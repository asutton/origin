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
  assert(origin::find(a, 1) == a);

  std::vector<int> v { 1, 2, 3 };
  assert(origin::find(v, 1) == v.begin());

  const std::vector<int>& cv = v;
  assert(origin::find(cv, 1) == v.begin());
}
