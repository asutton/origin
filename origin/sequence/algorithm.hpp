// Copyright (c) 2008-2014 Andrew Sutton
//
// This file is distributed under the MIT License. See
// http://www.opensource.org/licenses/mit-license.php
// for terms and conditions.

#ifndef ORIGIN_SEQUENCE_ALGORITHM_HPP
#define ORIGIN_SEQUENCE_ALGORITHM_HPP

#include <algorithm>

#include <origin/core/type.hpp>
#include <origin/core/function.hpp>
#include <origin/sequence/concepts.hpp>

namespace origin {

// -------------------------------------------------------------------------- //
// Algorithm Concepts                                         [algo.concepts] //

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
template<typename I, typename P>
  concept bool 
  Iterator_query() {
    return Input_iterator<I>() && Predicate<P, Value_type<I>>();
  }

// Range_query
template<typename R, typename P>
  concept bool 
  Range_query() {
    return Range<R>() && Iterator_query<Iterator_type<R>, P>();
  }

// Iter_search
template<typename I, typename T>
  concept bool Iterator_search() {
    return Input_iterator<I>() && Equality_comparable<Value_type<I>, T>();
  }

// Range_search
template<typename R, typename T>
  concept bool Range_search() {
    return Range<R>() && Iterator_search<Iterator_type<R>, T>();
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

// Non-modifiying algorithms

// -------------------------------------------------------------------------- //
// For Each                                                   [algo.for_each] //
//
//      for_each(first, last, fn)
//      for_each(range, fn)

template<Input_iterator I, typename S, typename F>
  requires Sentinel<S, I>() and Invokable<F, Value_type<I>>()
    inline F
    for_each(I first, S last, F fn) {
      auto&& f = Invokable(fn);
      while (first != last) {
        f(*first);
        ++first;
      }
      return fn;
    }

template<Input_range R, typename F>
  requires Invokable<F, Value_type<R>>()
    inline F 
    for_each(R&& range, F fn) {
      return origin::for_each(std::begin(range), std::end(range), fn);
    }

template<typename T, typename F>
  requires Invokable<F, T>()
    inline F
    for_each(std::initializer_list<T> list, F fn) {
      return origin::for_each(list.begin(), list.end(), fn);
    }

// -------------------------------------------------------------------------- //
// Find If                                                     [algo.find_if] //
//
//    find_if(first, last, pred)
//    find_if(range, pred)

template<Input_iterator I, typename S, typename P>
  requires Sentinel<S, I>() and Invokable_predicate<P, Value_type<I>>()
    inline I
    find_if(I first, S last, P pred) {
      auto&& p = Invokable(pred);
      while (first != last and not p(*first))
        ++first;
      return first;
    }

template<Input_range R, typename P>
  requires Invokable_predicate<P, Value_type<R>>()
    inline Iterator_type<R> 
    find_if(R&& range, P pred) {
      return origin::find_if(std::begin(range), std::end(range), pred);
    }

template<typename T, typename P>
  requires Invokable_predicate<P, T>()
    inline const T*
    find_if(std::initializer_list<T> list, P pred) {
      return origin::find_if(list.begin(), list.end(), pred);
    }

// -------------------------------------------------------------------------- //
// Find If Not                                             [algo.find_if_not] //
//
//    find_if_not(first, last, pred)
//    find_if_not(range, pred)

template<Input_iterator I, typename S, typename P>
  requires Sentinel<S, I>() and Invokable_predicate<P, Value_type<I>>()
    inline I
    find_if_not(I first, S last, P pred) {
      auto&& p = Invokable(pred);
      while (first != last and p(*first))
        ++first;
      return first;
    }

template<Input_range R, typename P>
  requires Invokable_predicate<P, Value_type<R>>()
    inline Iterator_type<R> 
    find_if_not(R&& range, P pred) {
      return std::find_if_not(begin(range), end(range), pred);
    }

template<typename T, typename P>
  requires Invokable_predicate<P, T>()
    inline const T*
    find_if_not(std::initializer_list<T> list, P pred) {
      return origin::find_if(list.begin(), list.end(), pred);
    }

// -------------------------------------------------------------------------- //
// All Of                                                       [algo.all_of] //
//
//      all_of(first, last, fn)
//      all_of(range, fn)

template<Input_iterator I, typename S, typename P>
  requires Sentinel<S, I>() and Invokable_predicate<P, Value_type<I>>()
    inline bool
    all_of(I first, S last, P pred) {
      return origin::find_if_not(first, last, pred) == last;
    }

template<Input_range R, typename P>
  requires Invokable_predicate<P, Value_type<R>>()
    inline bool
    all_of(R&& range, P pred) {
      return origin::all_of(std::begin(range), std::end(range), pred);
    }

// all_of (initializer_list)
template<typename T, typename P>
  requires Invokable_predicate<P, T>()
    inline bool 
    all_of(std::initializer_list<T> list, P pred) {
      return origin::all_of(list.begin(), list.end(), pred);
    }

// -------------------------------------------------------------------------- //
// Any Of                                                       [algo.any_of] //
//
//      any_of(first, last, fn)
//      any_of(range, fn)

template<Input_iterator I, typename S, typename P>
  requires Sentinel<S, I>() and Invokable_predicate<P, Value_type<I>>()
    inline bool
    any_of(I first, S last, P pred) {
      return origin::find_if(first, last, pred) != last;
    }

template<Input_range R, typename P>
  requires Invokable_predicate<P, Value_type<R>>()
    inline bool any_of(R&& range, P pred) {
      return origin::any_of(std::begin(range), std::end(range), pred);
    }

template<typename T, typename P>
  requires Invokable_predicate<P, T>()
    inline bool 
    any_of(std::initializer_list<T> list, P pred) {
      return origin::any_of(list.begin(), list.end(), pred);
    }

// -------------------------------------------------------------------------- //
// None Of                                                     [algo.none_of] //
//
//      none_of(first, last, fn)
//      none_of(range, fn)

template<Input_iterator I, typename S, typename P>
  requires Sentinel<S, I>() and Invokable_predicate<P, Value_type<I>>()
    inline bool
    none_of(I first, S last, P pred) {
      return origin::find_if(first, last, pred) == last;
    }

template<Input_range R, typename P>
  requires Invokable_predicate<P, Value_type<R>>()
    inline bool 
    none_of(R&& range, P pred) {
      return origin::none_of(std::begin(range), std::end(range), pred);
    }

template<typename T, typename P>
  requires Invokable_predicate<P, T>()
    inline bool
    none_of(std::initializer_list<T> list, P pred) {
      return origin::none_of(list.begin(), list.end(), pred);
    }

// -------------------------------------------------------------------------- //
// Count If                                                   [algo.count_if] //
//
//    count_if(first, last, pred, init)
//    count_if(first, last, pred)
//    count_if(range, pred, init)
//    count_if(range, pred)
//
// NOTE: The set of operations is extnded from those in the standard by
// allowing an initial value (required only to be Advanceable) to be 
// provided. When not provided, the count starts from 0.

template<Input_iterator I, typename S, typename P, Advanceable J>
  requires Sentinel<S, I>() and Invokable_predicate<P, Value_type<I>>()
    inline Difference_type<I>
    count_if(I first, S last, P pred, J value) {
      auto&& p = Invokable(pred);
      while (first != last) {
        if (p(*first)) ++value;
        ++first;
      }
      return value;
    }

template<Input_iterator I, typename S, typename P>
  requires Sentinel<S, I>() and Invokable_predicate<P, Value_type<I>>()
    inline Difference_type<I>
    count_if(I first, S last, P pred) {
      using J = Difference_type<I>;
      return origin::count_if(first, last, pred, J{0});
    }

template<Input_range R, typename P, Advanceable J>
  requires Invokable_predicate<P, Value_type<R>>()
    inline Size_type<R> 
    count_if(R&& range, P pred, J value) {
      return origin::count_if(std::begin(range), std::end(range), pred, value);
    }

template<Input_range R, typename P>
  requires Invokable_predicate<P, Value_type<R>>()
    inline Size_type<R> 
    count_if(R&& range, P pred) {
      using J = Size_type<R>;
      return origin::count_if(std::begin(range), std::end(range), pred, J{0});
    }

template<typename T, typename P, Advanceable J>
  requires Invokable_predicate<P, T>()
    inline std::size_t
    count_if(std::initializer_list<T> list, P pred, J value) {
      return origin::count_if(list.begin(), list.end(), pred, value);
    }

template<typename T, typename P>
  requires Invokable_predicate<P, T>()
    inline std::size_t
    count_if(std::initializer_list<T> list, P pred) {
      return origin::count_if(list.begin(), list.end(), pred, std::size_t{0});
    }

// -------------------------------------------------------------------------- //
// Count If Not                                           [algo.count_if_not] //
//
//    count_if_not(first, last, pred, init)
//    count_if_not(first, last, pred)
//    count_if_not(range, pred, init)
//    count_if_not(range, pred)


template<Input_iterator I, typename S, typename P, Advanceable J>
  requires Sentinel<S, I>() and Invokable_predicate<P, Value_type<I>>()
    inline Difference_type<I>
    count_if_not(I first, S last, P pred, J value) {
      auto&& p = Invokable(pred);
      while (first != last) {
        if (not p(*first)) ++value;
        ++first;
      }
      return value;
    }

template<Input_iterator I, typename S, typename P>
  requires Sentinel<S, I>() and Invokable_predicate<P, Value_type<I>>()
    inline Difference_type<I>
    count_if_not(I first, S last, P pred) {
      using J = Difference_type<I>;
      return origin::count_if_not(first, last, pred, J{0});
    }

template<Input_range R, typename P, Advanceable J>
  requires Invokable_predicate<P, Value_type<R>>()
    inline Size_type<R> 
    count_if_not(R&& range, P pred, J value) {
      return origin::count_if_not(std::begin(range), std::end(range), pred, value);
    }

template<Input_range R, typename P>
  requires Invokable_predicate<P, Value_type<R>>()
    inline Size_type<R> 
    count_if_not(R&& range, P pred) {
      using J = Size_type<R>;
      return origin::count_if_not(std::begin(range), std::end(range), pred, J{0});
    }

template<typename T, typename P, Advanceable J>
  requires Invokable_predicate<P, T>()
    inline std::size_t
    count_if_not(std::initializer_list<T> list, P pred, J value) {
      return origin::count_if_not(list.begin(), list.end(), pred, value);
    }

template<typename T, typename P>
  requires Invokable_predicate<P, T>()
    inline std::size_t
    count_if_not(std::initializer_list<T> list, P pred) {
      return origin::count_if_not(list.begin(), list.end(), pred, std::size_t{0});
    }

// -------------------------------------------------------------------------- //
// Find                                                           [algo.find] //
//
//      find(first, last, value)
//      find(range, value)
//
// TODO: Consider adding overloads that accept a binary relation.

template<Input_iterator I, typename S, typename T>
  requires Sentinel<I, T>() and Equality_comparable<T, Value_type<I>>()
    inline I
    find(I first, S last, const T& value) {
      while (first != last and *first != value)
        ++first;
      return first;
    }

template<Input_range R, typename T>
  requires Equality_comparable<T, Value_type<R>>()
    inline Iterator_type<R> 
    find(R&& range, const T& value) {
      return origin::find(std::begin(range), std::end(range), value);
    }

// -------------------------------------------------------------------------- //
// Count                                                         [algo.count] //
//
//      count(first, last, value, n)
//      count(first, last, value)
//      count(range, value, n)
//      count(range, value)
//
// TODO: Consider adding overloads that accept a binary relation.

template<Input_iterator I, typename S, typename T, Advanceable N>
  requires Sentinel<S, I>() and Equality_comparable<T, Value_type<I>>()
    inline N
    count(I first, S last, const T& value, N n) {
      while (first != last) {
        if (*first == value) ++n;
      }
      return n;
    }

template<Input_iterator I, typename S, typename T>
  requires Sentinel<S, I>() and Equality_comparable<T, Value_type<I>>()
    inline Difference_type<I>
    count(I first, S last, const T& value) {
      Difference_type<I> n = 0;
      return origin::count(first, last, value, n);
    }

template<Input_range R, typename T, Advanceable N>
  requires Equality_comparable<Value_type<R>, T>()
    inline Size_type<R> 
    count(R&& range, const T& value, N n) {
      return origin::count(std::begin(range), std::end(range), value, n);
    }

template<Input_range R, typename T>
  requires Equality_comparable<Value_type<R>, T>()
    inline Size_type<R> 
    count(R&& range, const T& value) {
      Size_type<R> n = 0;
      return origin::count(std::begin(range), std::end(range), value, n);
    }

template<typename T, typename U, Advanceable N>
  requires Equality_comparable<T, U>()
    inline std::size_t
    count(std::initializer_list<T> list, const T& value, N n) {
      return origin::count(list.begin(), list.end(), value, n);
    }

template<typename T, typename U>
  requires Equality_comparable<T, U>()
    inline std::size_t
    count(std::initializer_list<T> list, const T& value) {
      std::size_t n = 0;
      return origin::count(list.begin(), list.end(), value);
    }

// -------------------------------------------------------------------------- //
// Adjacent Find                                              [algo.adj_find] //
//

template<Forward_iterator I, typename S, typename C>
  requires Sentinel<S, I>() and Equality_comparable<Value_type<I>>()
    inline I
    adjacent_find(I first, S last, C comp) {
      if (first == last) return first;
      I prev = first;
      ++first;
      while (first != last and comp(*prev, *first)) {
        ++prev;
        ++first;
      }
      return prev;
    }

template<Forward_iterator I, typename S>
  requires Sentinel<S, I>() and Equality_comparable<Value_type<I>>()
    inline I
    adjacent_find(I first, S last) {
      return origin::adjacent_find(first, last, eq());
    }

template<Forward_range R>
  requires Equality_comparable<Value_type<R>>()
    inline Iterator_type<R> 
    adjacent_find(R&& range) {
      return origin::adjacent_find(std::begin(range), std::end(range), eq());
    }

template<Forward_range R, typename C>
  requires Relation<C, Value_type<R>>()
    inline Iterator_type<R> 
    adjacent_find(R&& range, C comp) {
      return origin::adjacent_find(std::begin(range), std::end(range), comp);
    }

template<Equality_comparable T>
  inline const T*
  adjacent_find(std::initializer_list<T> list) {
    return origin::adjacent_find(list.begin(), list.end(), eq());
  }

template<typename T, typename C>
  requires Relation<C, T>()
    inline const T*
    adjacent_find(std::initializer_list<T> list, C comp) {
      return origin::adjacent_find(list.begin(), list.end(), comp);
    }


// -------------------------------------------------------------------------- //
// Mismatch                                                   [algo.mismatch] //

template<Input_iterator I1, Input_iterator I2, typename C>
  requires Relation<Value_type<I1>, Value_type<I2>>()
    inline std::pair<I1, I2>
    mismatch(I1 first1, I1 last1, I2 first2, C comp) {
      while (first1 != last1 and comp(*first1, *first2)) {
        ++first1;
        ++first2;
      }
      return {first1, first2};
    }

template<Input_iterator I1, Input_iterator I2>
  requires Equality_comparable<Value_type<I1>, Value_type<I2>>()
    inline std::pair<I1, I2>
    mismatch(I1 first1, I1 last1, I2 first2) {
      return origin::mismatch(first1, last1, first2, eq());
    }

template<Input_range R1, Input_range R2, typename C>
  requires Relation<C, Value_type<R1>, Value_type<R2>>()
    inline std::pair<Iterator_type<R1>, Iterator_type<R2>>
    mismatch(R1&& range1, R2&& range2, C comp) {
      return std::mismatch(std::begin(range1), std::end(range1), 
                           std::begin(range2), comp);
    }

template<Input_range R1, Input_range R2>
  requires Equality_comparable<Value_type<R1>, Value_type<R2>>()
    inline std::pair<Iterator_type<R1>, Iterator_type<R2>>
    mismatch(R1&& range1, R2&& range2) {
      return origin::mismatch(std::begin(range1), std::end(range1), 
                              std::begin(range2), eq());
    }


// -------------------------------------------------------------------------- //
// Equal                                                         [algo.equal] //

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


// -------------------------------------------------------------------------- //
// Modifying algorithms

// FIXME: Indirectly copyable is specified in the wrong order.

template<Input_iterator I, Output_iterator<Value_type<I>> O>
  O copy(I first, I last, O out) {
    while (first != last) {
      *out = *first;
      ++first;
      ++out;
    }
    return out;
  }

template<Input_range R1, Output_range<Value_type<R1>> R2>
  Iterator_type<R2>
  copy(R1&& in, R2&& out) {
    using std::begin;
    using std::end;
    return copy(begin(in), end(in), begin(out));
  }

} // namesapce origin

#endif
