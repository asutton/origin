// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <cassert>
#include <list>
#include <vector>

#include <origin/ranges>

template<typename R>
  void test(R&& range, std::size_t n) {
    assert(origin::size(range) == n);
  }

int main() {
  int a[3] = {1, 2, 3};
  test(a, 3);

  std::list<int> l;
  test(l, 0);

  std::vector<int> v;
  test(v, 0);
}
