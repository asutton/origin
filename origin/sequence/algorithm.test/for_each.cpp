// Copyright (c) 2008-2014 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <cassert>
#include <vector>

#include <origin/sequence/algorithm.hpp>

void twice(int& x) { x *= 2; }

int main() 
{
  int a[3] { 1, 2, 3 };
  assert(origin::for_each(a, twice));
  assert(a[0] == 2);
  assert(a[1] == 4);
  assert(a[2] == 6);
}
