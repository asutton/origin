// (C) 2013 Andrew Sutton
//
// This file is distributed under the MIT License. See
// http://www.opensource.org/licenses/mit-license.php
// for terms and conditions.

#ifndef ORIGIN_ALGORITHM_HPP
#define ORIGIN_ALGORITHM_HPP

#include <algorithm>

#include "concepts.hpp"

namespace origin {

// Indirectly_movable
template<typename I, typename O>
  constexpr bool Indirectly_movable()
  {
    return Input_iterator<I>()
        && Output_iterator<O, Value_type<I>&&>();
  }

// Indirectly_copyable
template<typename I, typename O>
  constexpr bool Indirectly_copyable()
  {
    return Indirectly_movable<I, O>()
        && Output_iterator<O, Value_type<I>>();
  }

// Indirectly_swappable
template<typename I1, typename I2>
  constexpr bool Indirectly_swappable()
  {
    return Indirectly_movable<I1, I2>()
        && Indirectly_movable<I2, I1>()
        && Movable<Value_type<I1>>() 
        && Movable<Value_type<I2>>();
  }

// Indirectly_equal
template<typename I1, typename I2>
  constexpr bool Indirectly_equal()
  {
    return Input_iterator<I1>() 
        && Input_iterator<I2>()
        && Equality_comparable<Value_type<I1>, Value_type<I2>>();
  }

// Indirectly_ordered
template<typename I1, typename I2>
  constexpr bool Indirectly_ordered()
  {
    return Input_iterator<I1>() 
        && Input_iterator<I2>()
        && Weakly_ordered<Value_type<I1>, Value_type<I2>>();
  }

// Indirectly_comparable
template<typename I1, typename I2, typename C>
  constexpr bool Indirectly_comparable()
  {
    return Input_iterator<I1>() 
        && Input_iterator<I2>()
        && Relation<C, Value_type<I1>, Value_type<I2>>();
  }


// Non-modifiying algorithms

// for_each
template<typename R, typename F>
  requires Input_range<R>() && Function<F, Value_type<R>>()
    inline F for_each(R&& range, F fn)
    {
      using std::begin;
      using std::end;
      return std::for_each(begin(range), end(range), fn);
    }

// Iter_query
template<typename I, typename P>
  constexpr bool Iter_query()
  {
    return Input_iterator<I>() && Predicate<P, Value_type<I>>();
  }

// Range_query
template<typename R, typename P>
  constexpr bool Range_query()
  {
    return Range<Main_type<R>>() && Iter_query<Iterator_type<R>, P>();
  }


// all of
template<typename R, typename P>
  requires Range_query<R, P>()
    inline bool all_of(R&& range, P pred)
    {
      using std::begin;
      using std::end;
      return std::all_of(begin(range), end(range), pred);
    }

// any_of
template<typename R, typename P>
  requires Range_query<R, P>()
    inline bool any_of(R&& range, P pred)
    {
      using std::begin;
      using std::end;
      return std::any_of(begin(range), end(range), pred);
    }

// none_of
template<typename R, typename P>
  requires Range_query<R, P>()
    inline bool none_of(R&& range, P pred)
    {
      using std::begin;
      using std::end;
      return std::none_of(begin(range), end(range), pred);
    }

// Iter_search
template<typename I, typename T>
  constexpr bool Iter_search()
  {
    return Input_iterator<I>() && Equality_comparable<Value_type<I>, T>();
  }

// Range_search
template<typename R, typename T>
  constexpr bool Range_search()
  {
    return Range<R>() && Iter_search<Iterator_type<R>, T>();
  }

// find
template<typename R, typename T>
  requires Range_search<R, T>()
    inline Iterator_type<R> find(R&& range, const T& value)
    {
      using std::begin;
      using std::end;
      return std::find(begin(range), end(range), value);
    }

// find_if
template<typename R, typename P>
  requires Range_query<R, P>()
    inline Iterator_type<R> find_if(R&& range, P pred)
    {
      using std::begin;
      using std::end;
      return std::find_if(begin(range), end(range), pred);
    }

// find_if_not
template<typename R, typename P>
  requires Range_query<R, P>()
    inline Iterator_type<R> find_if_not(R&& range, P pred)
    {
      using std::begin;
      using std::end;
      return std::find_if_not(begin(range), end(range), pred);
    }

// count
template<typename R, typename T>
  requires Range_search<R, T>()
    inline Size_type<R> count(R&& range, const T& value)
    {
      using std::begin;
      using std::end;
      return std::count(begin(range), end(range), value);
    }

// count_if
template<typename R, typename P>
  requires Range_query<R, P>()
    inline Size_type<R> count_if(R&& range, P pred)
    {
      using std::begin;
      using std::end;
      return std::count_if(begin(range), end(range), pred);
    }

template<typename R>
  requires Forward_range<R>() && Equality_comparable<Value_type<R>>()
    inline Iterator_type<R> adjacent_find(R&& range)
    {
      using std::begin;
      using std::end;
      return std::adjacent_find(begin(range), end(range));
    }

template<typename R, typename C>
  requires Forward_range<R>() && Relation<C, Value_type<R>>()
    inline Iterator_type<R> adjacent_find(R&& range, C comp)
    {
      using std::begin;
      using std::end;
      return std::adjacent_find(begin(range), end(range), comp);
    }

// Indirectly_range_equal
template<typename R1, typename R2>
  concept bool Indirectly_range_equal()
  {
    return Range<R1>() 
        && Range<R2>() 
        && Indirectly_equal<Iterator_type<R1>, Iterator_type<R2>>();
  }

// Indirectly_range_comparable
template<typename R1, typename R2, typename C>
  concept bool Indirectly_range_comparable()
  {
    return Range<R1>() 
        && Range<R2>() 
        && Indirectly_comparable<Iterator_type<R1>, Iterator_type<R2>, C>();
  }

// mismatch
template<typename R1, typename R2>
  requires Indirectly_range_equal<R1, R2>()
    inline std::pair<Iterator_type<R1>, Iterator_type<R2>>
    mismatch(R1&& range1, R2&& range2)
    {
      using std::begin;
      using std::end;
      return std::mismatch(begin(range1), end(range1), begin(range2));
    }

template<typename R1, typename R2, typename C>
  // requires Indirectly_range_comparable<R1, R2, C>()
    inline std::pair<Iterator_type<R1>, Iterator_type<R2>>
    mismatch(R1&& range1, R2&& range2, C comp)
    {
      using std::begin;
      using std::end;
      return std::mismatch(begin(range1), end(range1), begin(range2), comp);
    }

} // namesapce origin

#endif