// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_ALGORITHM_CONCEPTS_HPP
#define ORIGIN_ALGORITHM_CONCEPTS_HPP

#include <origin/generic.hpp>
#include <origin/functional.hpp>
#include <origin/iterator.hpp>
#include <origin/range.hpp>


namespace origin 
{

// -------------------------------------------------------------------------- //
// Algorithm Concepts                                         [algo.concepts] //

// Indirectly_movable
template<typename I, typename O>
concept bool 
Indirectly_movable() 
{
  return Input_iterator<I>() && Output_iterator<O, Value_type<I>&&>();
}


// Indirectly_copyable
template<typename I, typename O>
concept bool 
Indirectly_copyable() 
{
  return Indirectly_movable<I, O>() && Output_iterator<O, Value_type<I>>();
}


// Indirectly_swappable
template<typename I1, typename I2>
concept bool 
Indirectly_swappable() 
{
  return Indirectly_movable<I1, I2>()
      && Indirectly_movable<I2, I1>()
      && Movable<Value_type<I1>>() 
      && Movable<Value_type<I2>>();
}


// Indirectly_equal
template<typename I1, typename I2>
concept bool 
Indirectly_equal() 
{
  return Input_iterator<I1>() 
      && Input_iterator<I2>()
      && Equality_comparable<Value_type<I1>, Value_type<I2>>();
}


// Indirectly_ordered
template<typename I1, typename I2>
concept bool 
Indirectly_ordered() 
{
  return Input_iterator<I1>() 
      && Input_iterator<I2>()
      && Weakly_ordered<Value_type<I1>, Value_type<I2>>();
}


// Indirectly_comparable
template<typename I1, typename I2, typename C>
concept bool 
Indirectly_comparable() 
{
  return Input_iterator<I1>() 
      && Input_iterator<I2>()
      && Relation<C, Value_type<I1>, Value_type<I2>>();
}


// Iter_query
template<typename I, typename P>
concept bool 
Iterator_query() 
{
  return Input_iterator<I>() && Predicate<P, Value_type<I>>();
}


// Range_query
template<typename R, typename P>
concept bool 
Range_query() 
{
  return Range<R>() && Iterator_query<Iterator_type<R>, P>();
}


// Iter_search
template<typename I, typename T>
concept bool 
Iterator_search() 
{
  return Input_iterator<I>() && Equality_comparable<Value_type<I>, T>();
}


// Range_search
template<typename R, typename T>
concept bool 
Range_search() 
{
  return Range<R>() && Iterator_search<Iterator_type<R>, T>();
}


// Indirectly_range_equal
template<typename R1, typename R2>
concept bool 
Indirectly_range_equal()
{
  return Range<R1>() 
      && Range<R2>() 
      && Indirectly_equal<Iterator_type<R1>, Iterator_type<R2>>();
}


// Indirectly_range_comparable
template<typename R1, typename R2, typename C>
concept bool 
Indirectly_range_comparable()
{
  return Range<R1>() 
      && Range<R2>() 
      && Indirectly_comparable<Iterator_type<R1>, Iterator_type<R2>, C>();
}


} // namespace origin


#endif
