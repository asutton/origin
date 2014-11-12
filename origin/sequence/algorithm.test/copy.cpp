// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/sequence/algorithm.hpp>

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
