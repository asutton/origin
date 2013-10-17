// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <cassert>
#include <vector>
#include <iostream>

#include <origin/core/type.hpp>
#include <origin/range/algorithm.hpp>

template<origin::Input_range R, typename P>
    inline bool 
    foo(R&& range, P pred) {
      using namespace origin;

      using I = Iterator_type<R>;
      std::cout << typestr<I>() << '\n';
      std::cout << typestr<Value_type<I>>() << '\n';
      std::cout << Range_query<R, P>() << '\n';

      return true;
    }

bool pos(int n) { return n > 0; }

int main() 
{
  int a[3] { 1, 2, 3 };
  // assert(foo(a, pos));
  assert(origin::all_of(a, pos));

  std::vector<int> v { 1, 2, 3 };
  assert(origin::all_of(v, pos));

  const std::vector<int>& cv = v;
  assert(origin::all_of(cv, pos));
}
