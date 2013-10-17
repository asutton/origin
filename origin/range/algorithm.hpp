// (C) 2013 Andrew Sutton
//
// This file is distributed under the MIT License. See
// http://www.opensource.org/licenses/mit-license.php
// for terms and conditions.

#ifndef ORIGIN_ALGORITHM_HPP
#define ORIGIN_ALGORITHM_HPP

#include <algorithm>

#include "concepts.hpp"
#include "range.hpp"
#include "stream.hpp"

namespace origin {

// Indirectly_movable
template<typename I, typename O>
  concept bool 
  Indirectly_movable() {
    return Input_iterator<I>()
        && Output_iterator<O, Value_type<I>&&>();
  }

// Indirectly_copyable
template<typename I, typename O>
  concept bool 
  Indirectly_copyable() {
    return Indirectly_movable<I, O>()
        && Output_iterator<O, Value_type<I>>();
  }

// Indirectly_swappable
template<typename I1, typename I2>
  concept bool 
  Indirectly_swappable() {
    return Indirectly_movable<I1, I2>()
        && Indirectly_movable<I2, I1>()
        && Movable<Value_type<I1>>() 
        && Movable<Value_type<I2>>();
  }

// Indirectly_equal
template<typename I1, typename I2>
  concept bool 
  Indirectly_equal() {
    return Input_iterator<I1>() 
        && Input_iterator<I2>()
        && Equality_comparable<Value_type<I1>, Value_type<I2>>();
  }

// Indirectly_ordered
template<typename I1, typename I2>
  concept bool 
  Indirectly_ordered() {
    return Input_iterator<I1>() 
        && Input_iterator<I2>()
        && Weakly_ordered<Value_type<I1>, Value_type<I2>>();
  }

// Indirectly_comparable
template<typename I1, typename I2, typename C>
  concept bool 
  Indirectly_comparable() {
    return Input_iterator<I1>() 
        && Input_iterator<I2>()
        && Relation<C, Value_type<I1>, Value_type<I2>>();
  }

// Iter_query
//
// TODO: Shouldn't this be in the algorithm library?
template<typename I, typename P>
  concept bool 
  Iter_query() {
    return Input_iterator<I>() && Predicate<P, Value_type<I>>();
  }

// Range_query
template<typename R, typename P>
  concept bool 
  Range_query() {
    return Range<R>() && Iter_query<Iterator_type<R>, P>();
  }

// Iter_search
template<typename I, typename T>
  concept bool Iter_search() {
    return Input_iterator<I>() && Equality_comparable<Value_type<I>, T>();
  }

// Range_search
template<typename R, typename T>
  concept bool Range_search() {
    return Range<R>() && Iter_search<Iterator_type<R>, T>();
  }


// Non-modifiying algorithms

// for_each (range)
template<Input_range R, typename F>
  requires Function<F, Value_type<R>>()
    inline F 
    for_each(R&& range, F fn) {
      return std::for_each(std::begin(range), std::end(range), fn);
    }

// for_each (initializer_list)
template<typename T, typename F>
  requires Function<F, T>()
    inline F
    for_each(std::initializer_list<T> list, F fn) {
      return std::for_each(list.begin(), list.end(), fn);
    }


// all_of (range)
template<Input_range R, typename P>
  requires Range_query<R, P>()
    inline bool 
    all_of(R&& range, P pred) {
      return std::all_of(std::begin(range), std::end(range), pred);
    }

// all_of (initializer_list)
template<typename T, typename P>
  requires Predicate<P, T>()
    inline bool 
    all_of(std::initializer_list<T> list, P pred) {
      return std::all_of(list.begin(), list.end(), pred);
    }

// any_of (range)
template<Input_range R, typename P>
  requires Range_query<R, P>()
    inline bool any_of(R&& range, P pred) {
      return std::any_of(std::begin(range), std::end(range), pred);
    }

// any_of (initializer_list)
template<typename T, typename P>
  requires Predicate<P, T>()
    inline bool 
    any_of(std::initializer_list<T> list, P pred) {
      return std::any_of(list.begin(), list.end(), pred);
    }


// none_of (range)
template<Input_range R, typename P>
  requires Range_query<R, P>()
    inline bool 
    none_of(R&& range, P pred) {
      return std::none_of(std::begin(range), std::end(range), pred);
    }

// none_of (initializer_list)
template<typename T, typename P>
  requires Predicate<P, T>()
    inline bool
    none_of(std::initializer_list<T> list, P pred) {
      return std::none_of(list.begin(), list.end(), pred);
    }


// find
template<Input_range R, typename T>
  requires Range_search<R, T>()
    inline Iterator_type<R> find(R&& range, const T& value)
    {
      using std::begin;
      using std::end;
      return std::find(begin(range), end(range), value);
    }

// find_if
template<Input_range R, typename P>
  requires Range_query<R, P>()
    inline Iterator_type<R> find_if(R&& range, P pred)
    {
      using std::begin;
      using std::end;
      return std::find_if(begin(range), end(range), pred);
    }

// find_if_not
template<Input_range R, typename P>
  requires Range_query<R, P>()
    inline Iterator_type<R> find_if_not(R&& range, P pred)
    {
      using std::begin;
      using std::end;
      return std::find_if_not(begin(range), end(range), pred);
    }

// count
template<Input_range R, typename T>
  requires Range_search<R, T>()
    inline Size_type<R> count(R&& range, const T& value)
    {
      using std::begin;
      using std::end;
      return std::count(begin(range), end(range), value);
    }

// count_if
template<Input_range R, typename P>
  requires Range_query<R, P>()
    inline Size_type<R> count_if(R&& range, P pred)
    {
      using std::begin;
      using std::end;
      return std::count_if(begin(range), end(range), pred);
    }

template<Forward_range R>
  requires Equality_comparable<Value_type<R>>()
    inline Iterator_type<R> adjacent_find(R&& range)
    {
      using std::begin;
      using std::end;
      return std::adjacent_find(begin(range), end(range));
    }

template<Forward_range R, typename C>
  requires Relation<C, Value_type<R>>()
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
template<Input_range R1, Input_range R2>
  requires Indirectly_range_equal<R1, R2>()
    inline std::pair<Iterator_type<R1>, Iterator_type<R2>>
    mismatch(R1&& range1, R2&& range2)
    {
      using std::begin;
      using std::end;
      return std::mismatch(begin(range1), end(range1), begin(range2));
    }

template<Input_range R1, Input_range R2, typename C>
  requires Indirectly_range_comparable<R1, R2, C>()
    inline std::pair<Iterator_type<R1>, Iterator_type<R2>>
    mismatch(R1&& range1, R2&& range2, C comp)
    {
      using std::begin;
      using std::end;
      return std::mismatch(begin(range1), end(range1), begin(range2), comp);
    }


// equal
template<Input_range R1, Input_range R2>
  requires Indirectly_range_equal<R1, R2>()
    inline bool
    equal(R1&& range1, R2&& range2)
    {
      using std::begin;
      using std::end;
      return std::equal(begin(range1), end(range1), begin(range2));
    }

template<Input_range R1, Input_range R2, typename C>
  requires Indirectly_range_comparable<R1, R2, C>()
    inline bool
    equal(R1&& range1, R2&& range2, C comp)
    {
      using std::begin;
      using std::end;
      return std::equal(begin(range1), end(range1), begin(range2), comp);
    }

// find_first_of
template<Input_range R1, Forward_range R2>
  requires Indirectly_range_equal<R1, R2>()
    inline Iterator_type<R1> 
    find_first_of(R1&& range1, R2&& range2)
    {
      using std::begin;
      using std::end;
      return std::find_first_of(begin(range1), end(range1), 
                                begin(range2), end(range2));
    }

template<Input_range R1, Forward_range R2, typename C>
  requires Indirectly_range_comparable<R1, R2, C>()
    inline Iterator_type<R1> 
    find_first_of(R1&& range1, R2&& range2, C comp)
    {
      using std::begin;
      using std::end;
      return std::find_first_of(begin(range1), end(range1), 
                                begin(range2), end(range2), comp);
    }

// find_end
template<Forward_range R1, Forward_range R2>
  requires Indirectly_range_equal<R1, R2>()
    inline Iterator_type<R1> 
    find_end(R1&& range1, R2&& range2)
    {
      using std::begin;
      using std::end;
      return std::find_end(begin(range1), end(range1), 
                           begin(range2), end(range2));
    }

template<Forward_range R1, Forward_range R2, typename C>
  requires Indirectly_range_comparable<R1, R2, C>()
    inline Iterator_type<R1> 
    find_end(R1&& range1, R2&& range2, C comp)
    {
      using std::begin;
      using std::end;
      return std::find_end(begin(range1), end(range1), 
                           begin(range2), end(range2), comp);
    }

} // namesapce origin

#endif
