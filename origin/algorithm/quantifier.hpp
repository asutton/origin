// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_ALGORITHM_QUANTIFIER_HPP
#define ORIGIN_ALGORITHM_QUANTIFIER_HPP

#include <origin/algorithm/find.hpp>

namespace origin 
{


// -------------------------------------------------------------------------- //
// All Of                                                       [algo.all_of] //
//
//      all_of(first, last, fn)
//      all_of(range, fn)

template<Input_iterator I, typename S, typename P>
  requires Sentinel<S, I>() and Invokable_predicate<P, Value_type<I>>()
inline bool
all_of(I first, S last, P pred) 
{
  return origin::find_if_not(first, last, pred) == last;
}


template<Input_range R, typename P>
  requires Invokable_predicate<P, Value_type<R>>()
inline bool
all_of(R&& range, P pred) 
{
  using std::begin;
  using std::end;
  return origin::all_of(begin(range), end(range), pred);
}


// all_of (initializer_list)
template<typename T, typename P>
  requires Invokable_predicate<P, T>()
inline bool 
all_of(std::initializer_list<T> list, P pred) 
{
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
any_of(I first, S last, P pred) 
{
  return origin::find_if(first, last, pred) != last;
}


template<Input_range R, typename P>
  requires Invokable_predicate<P, Value_type<R>>()
inline bool 
any_of(R&& range, P pred) 
{
  using std::begin;
  using std::end;
  return origin::any_of(begin(range), end(range), pred);
}

template<typename T, typename P>
  requires Invokable_predicate<P, T>()
inline bool 
any_of(std::initializer_list<T> list, P pred) 
{
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
none_of(I first, S last, P pred) 
{
  return origin::find_if(first, last, pred) == last;
}

template<Input_range R, typename P>
  requires Invokable_predicate<P, Value_type<R>>()
inline bool 
none_of(R&& range, P pred) 
{
  using std::begin;
  using std::end;
  return origin::none_of(begin(range), end(range), pred);
}

template<typename T, typename P>
  requires Invokable_predicate<P, T>()
inline bool
none_of(std::initializer_list<T> list, P pred) 
{
  return origin::none_of(list.begin(), list.end(), pred);
}


} // namesapce origin


#endif
