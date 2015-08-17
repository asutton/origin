// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_ALGORITHM_COUNT_HPP
#define ORIGIN_ALGORITHM_COUNT_HPP

#include <origin/algorithm/concepts.hpp>

#include <algorithm>


namespace origin 
{

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
count_if(I first, S last, P pred, J value) 
{
  auto&& p = make_invokable(pred);
  while (first != last) {
    if (p(*first)) ++value;
    ++first;
  }
  return value;
}


template<Input_iterator I, typename S, typename P>
  requires Sentinel<S, I>() and Invokable_predicate<P, Value_type<I>>()
inline Difference_type<I>
count_if(I first, S last, P pred) 
{
  using J = Difference_type<I>;
  return origin::count_if(first, last, pred, J{0});
}


template<Input_range R, typename P, Advanceable J>
  requires Invokable_predicate<P, Value_type<R>>()
inline Size_type<R> 
count_if(R&& range, P pred, J value) 
{
  return origin::count_if(std::begin(range), std::end(range), pred, value);
}


template<Input_range R, typename P>
  requires Invokable_predicate<P, Value_type<R>>()
    inline Size_type<R> 
count_if(R&& range, P pred) 
{
  using J = Size_type<R>;
  return origin::count_if(std::begin(range), std::end(range), pred, J{0});
}


template<typename T, typename P, Advanceable J>
  requires Invokable_predicate<P, T>()
    inline std::size_t
count_if(std::initializer_list<T> list, P pred, J value) 
{
  return origin::count_if(list.begin(), list.end(), pred, value);
}


template<typename T, typename P>
  requires Invokable_predicate<P, T>()
inline std::size_t
count_if(std::initializer_list<T> list, P pred) 
{
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
count_if_not(I first, S last, P pred, J value) 
{
  auto&& p = make_invokable(pred);
  while (first != last) {
    if (not p(*first)) ++value;
    ++first;
  }
  return value;
}


template<Input_iterator I, typename S, typename P>
  requires Sentinel<S, I>() and Invokable_predicate<P, Value_type<I>>()
inline Difference_type<I>
count_if_not(I first, S last, P pred) 
{
  using J = Difference_type<I>;
  return origin::count_if_not(first, last, pred, J{0});
}


template<Input_range R, typename P, Advanceable J>
  requires Invokable_predicate<P, Value_type<R>>()
inline Size_type<R> 
count_if_not(R&& range, P pred, J value) 
{
  return origin::count_if_not(std::begin(range), std::end(range), pred, value);
}

template<Input_range R, typename P>
  requires Invokable_predicate<P, Value_type<R>>()
inline Size_type<R> 
count_if_not(R&& range, P pred) 
{
  using J = Size_type<R>;
  return origin::count_if_not(std::begin(range), std::end(range), pred, J{0});
}


template<typename T, typename P, Advanceable J>
  requires Invokable_predicate<P, T>()
inline std::size_t
count_if_not(std::initializer_list<T> list, P pred, J value) 
{
  return origin::count_if_not(list.begin(), list.end(), pred, value);
}


template<typename T, typename P>
  requires Invokable_predicate<P, T>()
inline std::size_t
count_if_not(std::initializer_list<T> list, P pred) 
{
  return origin::count_if_not(list.begin(), list.end(), pred, std::size_t{0});
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
count(I first, S last, const T& value, N n) 
{
  while (first != last) {
    if (*first == value) ++n;
  }
  return n;
}


template<Input_iterator I, typename S, typename T>
  requires Sentinel<S, I>() and Equality_comparable<T, Value_type<I>>()
inline Difference_type<I>
count(I first, S last, const T& value) 
{
  Difference_type<I> n = 0;
  return origin::count(first, last, value, n);
}


template<Input_range R, typename T, Advanceable N>
  requires Equality_comparable<Value_type<R>, T>()
inline Size_type<R> 
count(R&& range, const T& value, N n) 
{
  return origin::count(std::begin(range), std::end(range), value, n);
}


template<Input_range R, typename T>
  requires Equality_comparable<Value_type<R>, T>()
inline Size_type<R> 
count(R&& range, const T& value) 
{
  Size_type<R> n = 0;
  return origin::count(std::begin(range), std::end(range), value, n);
}


template<typename T, typename U, Advanceable N>
  requires Equality_comparable<T, U>()
inline std::size_t
count(std::initializer_list<T> list, const T& value, N n) 
{
  return origin::count(list.begin(), list.end(), value, n);
}


template<typename T, typename U>
  requires Equality_comparable<T, U>()
inline std::size_t
count(std::initializer_list<T> list, const T& value) 
{
  std::size_t n = 0;
  return origin::count(list.begin(), list.end(), value);
}


} // namesapce origin


#endif
