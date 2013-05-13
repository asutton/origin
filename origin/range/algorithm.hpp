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
template<typename I1, typename I2, typename _Compare>
  constexpr bool Indirectly_comparable()
  {
    return Input_iterator<I1>() 
        && Input_iterator<I2>()
        && Relation<_Compare, Value_type<I1>, Value_type<I2>>();
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


#if 0

// any of

template<typename I, typename P>
  requires Query<I, P>()
    I any_of(I first, I last, P pred)
    {
      return std::any_of(first, last, pred);
    }

template<typename R, typename P>
  requires Query_range<R, P>()
    Iterator_type<R> any_of(R&& range)
    {
      return std::any_of(std::begin(range), std::end(range));
    }

// none of

template<typename I, typename P>
  requires Query<I, P>()
    I none_of(I first, I last, P pred)
    {
      return std::none_of(first, last, pred);
    }

template<typename R, typename P>
  requires Query_range<R, P>()
    Iterator_type<R> none_of(R&& range)
    {
      return std::none_of(std::begin(range), std::end(range));
    }

// for each
template<typename I, typename F>
  requires Input_iterator<I>() && Function<F, Value_type<I>>()
    F for_each(I first, I last, F fn)
    {
      return std::for_each(first, last, fn);      
    }

// find

template<typename I, typename T>
  requires Find<I, T>()
    I find(I first, I last, const T& value)
    {
      return std::find(first, last, value);
    }

template<typename R, typename T>
  requires Find_range<R, T>()
    Iterator_type<R> find(R&& range, const T& value)
    {
      return std::find(std::begin(range), std::end(range));
    }

// find if

template<typename I, typename P>
  requires Query<I, P>()
    I find_if(I first, I last, P pred)
    {
      return std::find_if(first, last, pred);
    }

template<typename R, typename P>
  requires Query_range<R, P>()
    Iterator_type<R> find_if(R&& range, P pred)
    {
      return std::find_if(std::begin(range), std::end(range));
    }

// find if not

template<typename I, typename P>
  requires Query<I, P>()
    I find_if_not (I first, I last, P pred)
    {
      return std::find_if_not(first, last, pred);
    }

template<typename R, typename P>
  requires Query_range<R, P>()
    Iterator_type<R> find_if_not(R&& range, P pred)
    {
      return std::find_if_not(std::begin(range), std::end(range), pred);
    }

// find end

// find first

template<typename I1, typename I2>
  requires Indirectly_equal<I1, I2>()
    I1 find_first(I1 first1, I1 last1, I2 first2, I2 last2)
    {
      return std::find_first(first1, last1, first2, last2);
    }

template<Input_iterator I1, Forward_iterator I2, typename R>
  requires Indirectly_comparable<I1, I2, R>()
    I1 find_first(I1 first1, I1 last1, I2 first2, I2 last2, R comp)
    {
      return std::find_first(first1, last1, first2, last2, comp);
    }

template<Input_range R1, Forward_range R2>
  requires Indirectly_equal_range<R1, R2, R>()
    Iterator_type<R1> find_first (R1&& range1, R2&& range2)
    {
      return std::find_find(std::begin(first1), std::end(last1),
                            std::begin(first2), std::end(last2));
    }

template<Input_range R1, Forward_range R2, typename R>
  requires Indirectly_comparable_range<R1, R2, R>()
    Iterator_type<R1> find_first (R1&& range1, R2&& range2, R comp)
    {
      return std::find_find(std::begin(first1), std::end(last1),
                            std::begin(first2), std::end(last2), comp);
    }

// Sorting algorithms

// Concepts
template<typename I>
  constexpr bool Sortable()
  {
    return Permutable<I>() 
        && Forward_iterator<I>()
        && Weakly_ordered<Value_type<I>>();
  }

template<typename I, typename R>
  constexpr bool Sortable()
  {
    return Forward_iterator<I>()
        && Permutable<I>()
        && Relation<R, Value_type<I>>();
  }

template<typename R>
  constexpr bool Sortable_range()
  {
    return Range<Main_type<R>>() && Sortable<Iterator_type<R>>();
  }

template<typename R, typename Ord>
  constexpr bool Sortable_range()
  {
    return Range<R>() && Sortable<Iterator_type<R>, Ord>();
  }


// Mergeable
template<typename I1, typename I2, typename O>
  constexpr bool Mergeable()
  {
    return Indirectly_ordered<I1, I2>()
        && Indirectly_copyable<I1, O>()
        && Indirectly_copyable<I2, O>();
  }

template<typename I1, typename I2, typename O, typename R>
  constexpr bool Mergeable()
  {
    return Indirectly_comparable<I1, I2, R>()
        && Indirectly_copyable<I1, O>()
        && Indirectly_copyable<I2, O>();
  }



// sort

template<Random_access_iterator I>
  requires Sortable<I>()
    void sort(I first, I last)
    {
      return std::sort(first, last);
    }

template<Random_access_iterator I, typename Ord>
  requires Sortable<I, Ord>()
    void sort(I first, I last, Ord comp)
    {
      return std::sort(first, last, comp);
    }

template<typename R>
  requires Sortable_range<R>()
    void sort(R&& range)
    {
      return std::sort(std::begin(range), std::end(range));
    }

template<typename R, typename Ord>
  requires Sortable_range<R, Ord>()
    void sort(R&& range, Ord comp)
    {
      return std::sort(std::begin(range), std::end(range), comp);
    }

#endif

} // namesapce origin

#endif