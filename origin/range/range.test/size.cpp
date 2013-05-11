// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <cassert>
#include <list>
#include <vector>

#include <origin/range/range.hpp>

template<typename R>
  void test(R&& range, std::size_t n)
  {
    assert(origin::size(range) == n);
  }

int main()
{
  int a[3] = {1, 2, 3};
  test(a, 3);

  std::list<int> l;
  test(l, 0);

  std::vector<int> v;
  test(v, 0);
}
