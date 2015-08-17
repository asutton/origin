// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_ALGORITHM_EQUAL_HPP
#define ORIGIN_ALGORITHM_EQUAL_HPP

#include <origin/algorithm/concepts.hpp>

#include <algorithm>


namespace origin 
{


// -------------------------------------------------------------------------- //
// Equal                                                         [algo.equal] //

template<Input_iterator I1, Input_iterator I2>
  requires Equality_comparable<Value_type<I1>, Value_type<I2>>()
inline bool 
equal(I1 first1, I1 last1, I2 first2)
{
  while (first1 != last1) {
    if (*first1 != *first2)
      return false;
    ++first1;
    ++first2;
  }
  return true;
}


template<Input_iterator I1, Input_iterator I2, typename C>
  requires Relation<C, Value_type<I1>, Value_type<I2>>()
inline bool 
equal(I1 first1, I1 last1, I2 first2, C cmp)
{
  while (first1 != last1) {
    if (!cmp(*first1, *first2))
      return false;
    ++first1;
    ++first2;
  }
  return true;
}


template<Input_range R1, Input_range R2>
  requires Indirectly_range_equal<R1, R2>()
inline bool
equal(R1&& range1, R2&& range2)
{
  using std::begin;
  using std::end;
  return origin::equal(begin(range1), end(range1), begin(range2));
}


template<Input_range R1, Input_range R2, typename C>
  requires Indirectly_range_comparable<R1, R2, C>()
inline bool
equal(R1&& range1, R2&& range2, C comp)
{
  using std::begin;
  using std::end;
  return origin::equal(begin(range1), end(range1), begin(range2), comp);
}


} // namesapce origin


#endif
