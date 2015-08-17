// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_ALGORITHM_FOREACH_HPP
#define ORIGIN_ALGORITHM_FOREACH_HPP

#include <origin/algorithm/concepts.hpp>

#include <algorithm>


namespace origin 
{

// -------------------------------------------------------------------------- //
// For Each                                                   [algo.for_each] //
//
//      for_each(first, last, fn)
//      for_each(range, fn)

template<Input_iterator I, typename S, typename F>
  requires Sentinel<S, I>() && Invokable<F, Value_type<I>>()
inline F
for_each(I first, S last, F fn) 
{
  auto&& f = make_invokable(fn);
  while (first != last) {
    f(*first);
    ++first;
  }
  return fn;
}


template<Input_range R, typename F>
  requires Invokable<F, Value_type<R>>()
inline F 
for_each(R&& range, F fn) 
{
  return origin::for_each(std::begin(range), std::end(range), fn);
}


template<typename T, typename F>
  requires Invokable<F, T>()
inline F
for_each(std::initializer_list<T> list, F fn) 
{
  return origin::for_each(list.begin(), list.end(), fn);
}


} // namesapce origin


#endif
