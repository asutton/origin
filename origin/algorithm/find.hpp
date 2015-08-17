// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_ALGORITHM_FIND_HPP
#define ORIGIN_ALGORITHM_FIND_HPP

#include <origin/algorithm/concepts.hpp>

#include <algorithm>


namespace origin 
{

// -------------------------------------------------------------------------- //
// Find If                                                     [algo.find_if] //
//
//    find_if(first, last, pred)
//    find_if(range, pred)

template<Input_iterator I, typename S, typename P>
  requires Sentinel<S, I>() && Invokable_predicate<P, Value_type<I>>()
inline I
find_if(I first, S last, P pred) 
{
  auto&& p = make_invokable(pred);
  while (first != last && !p(*first))
    ++first;
  return first;
}


template<Input_range R, typename P>
requires Invokable_predicate<P, Value_type<R>>()
inline Iterator_type<R> 
find_if(R&& range, P pred) 
{
  return origin::find_if(std::begin(range), std::end(range), pred);
}


template<typename T, typename P>
  requires Invokable_predicate<P, T>()
inline const T*
find_if(std::initializer_list<T> list, P pred) 
{
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
  auto&& p = make_invokable(pred);
  while (first != last and p(*first))
    ++first;
  return first;
}


template<Input_range R, typename P>
  requires Invokable_predicate<P, Value_type<R>>()
inline Iterator_type<R> 
find_if_not(R&& range, P pred) 
{
  return std::find_if_not(begin(range), end(range), pred);
}


template<typename T, typename P>
  requires Invokable_predicate<P, T>()
inline const T*
find_if_not(std::initializer_list<T> list, P pred) 
{
  return origin::find_if(list.begin(), list.end(), pred);
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
find(I first, S last, const T& value) 
{
  while (first != last and *first != value)
    ++first;
  return first;
}

template<Input_range R, typename T>
  requires Equality_comparable<T, Value_type<R>>()
inline Iterator_type<R> 
find(R&& range, const T& value) 
{
  return origin::find(std::begin(range), std::end(range), value);
}


// -------------------------------------------------------------------------- //
// Adjacent Find                                              [algo.adj_find] //
//

template<Forward_iterator I, typename S, typename C>
  requires Sentinel<S, I>() and Equality_comparable<Value_type<I>>()
inline I
find_adjacent(I first, S last, C comp) 
{
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
find_adjacent(I first, S last) 
{
  return origin::find_adjacent(first, last, eq());
}


template<Forward_range R>
  requires Equality_comparable<Value_type<R>>()
inline Iterator_type<R> 
find_adjacent(R&& range) 
{
  return origin::find_adjacent(std::begin(range), std::end(range), eq());
}


template<Forward_range R, typename C>
  requires Relation<C, Value_type<R>>()
inline Iterator_type<R> 
find_adjacent(R&& range, C comp) 
{
  return origin::find_adjacent(std::begin(range), std::end(range), comp);
}


template<Equality_comparable T>
  inline const T*
find_adjacent(std::initializer_list<T> list) 
{
  return origin::find_adjacent(list.begin(), list.end(), eq());
}


template<typename T, typename C>
  requires Relation<C, T>()
inline const T*
find_adjacent(std::initializer_list<T> list, C comp) 
{
  return origin::find_adjacent(list.begin(), list.end(), comp);
}


// -------------------------------------------------------------------------- //
// Mismatch                                                   [algo.mismatch] //

template<Input_iterator I1, Input_iterator I2, typename C>
  requires Relation<Value_type<I1>, Value_type<I2>>()
inline std::pair<I1, I2>
find_mismatch(I1 first1, I1 last1, I2 first2, C comp) 
{
  while (first1 != last1 and comp(*first1, *first2)) {
    ++first1;
    ++first2;
  }
  return {first1, first2};
}


template<Input_iterator I1, Input_iterator I2>
  requires Equality_comparable<Value_type<I1>, Value_type<I2>>()
inline std::pair<I1, I2>
find_mismatch(I1 first1, I1 last1, I2 first2) 
{
  return origin::find_mismatch(first1, last1, first2, eq());
}


template<Input_range R1, Input_range R2, typename C>
  requires Relation<C, Value_type<R1>, Value_type<R2>>()
inline std::pair<Iterator_type<R1>, Iterator_type<R2>>
find_mismatch(R1&& range1, R2&& range2, C comp) 
{
  using std::begin;
  using std::end;
  return origin::find_mismatch(begin(range1), end(range1), 
                               begin(range2), comp);
}


template<Input_range R1, Input_range R2>
  requires Equality_comparable<Value_type<R1>, Value_type<R2>>()
inline std::pair<Iterator_type<R1>, Iterator_type<R2>>
find_mismatch(R1&& range1, R2&& range2) 
{
  using std::begin;
  using std::end;
  return origin::find_mismatch(begin(range1), end(range1), 
                               begin(range2), eq());
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
