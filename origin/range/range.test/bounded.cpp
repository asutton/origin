// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <cassert>
#include <vector>

#include <origin/range/range.hpp>

template<typename R, typename T>
  constexpr bool Has_size_type()
  {
    return origin::Same<origin::Size_type<R>, T>();
  }

template<typename R, typename T>
  constexpr bool Has_value_type()
  {
    return origin::Same<origin::Value_type<R>, T>();
  }

template<typename R, typename T>
  constexpr bool Has_iterator_type()
  {
    return origin::Same<origin::Iterator_type<R>, T>();
  }

static_assert(origin::Range<origin::bounded_range<int*>>(), "");
static_assert(Has_size_type<origin::bounded_range<int*>, std::size_t>(), "");
static_assert(Has_value_type<origin::bounded_range<int*>, int>(), "");
static_assert(Has_iterator_type<origin::bounded_range<int*>, int*>(), "");

template<typename I>
  void test_default()
  {
    origin::bounded_range<I> range;
    assert(origin::size(range) == 0);
  }

template<typename I>
  void test_init(I first, I last)
  {
    origin::bounded_range<I> range(first, last);
    auto first2 = range.begin();
    auto last2 = range.end();
    while (first2 != last2) {
      assert(first2 == first);
      ++first2;
      ++first;
    }
    assert(last2 == last);
  }

int main()
{
  using Vec = std::vector<int>;

  test_default<int*>();
  test_default<const int*>();
  test_default<Vec::iterator>();

  int a[3] = {1, 2, 3};
  test_init (a, a + 3);

  Vec v {1, 2, 3};
  test_init(v.begin(), v.end());
}
