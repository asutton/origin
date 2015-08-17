// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_RANGE_CORE_HPP
#define ORIGIN_RANGE_CORE_HPP

#include <origin/iterator.hpp>

#include <iterator>


namespace origin
{

// -------------------------------------------------------------------------- //
// Range Sentinel                                               [range.sentinel]


// A type is a Sentinel for an Iterator if and only if it is Copyable
// and can be compared for equality with iterator.
template<typename T, typename I>
concept bool Sentinel() 
{
  return Copyable<T>() && Equality_comparable<T, I>();
}


// -------------------------------------------------------------------------- //
// Range Concepts                                                [range.concept]

// NOTE: The iterator and sentinel types are deduced against R& instead 
// of just R because of unintended decay for array types. In other words,
// these aliases will fail when they should not.


// The Iterator_type function returns the iterator type of a Range, the
// type resulting from a call to std::begin.
template<typename R>
using Iterator_type = decltype(std::begin(std::declval<R&>()));


// The Sentinel type function returns the sentinel type of a Range, the
// type resuluting from a call to std::end. Note that this is not 
// required to be the same as a Range's Iterator_type.
template<typename R>
using Sentinel_type = decltype(std::end(std::declval<R&>()));


namespace seq_impl
{

// Bring these into scope so the concept can find them
// the without qualification.
using std::begin;
using std::end;


template<typename R>
concept bool Range()
{
  return requires (R& range) 
  {
    typename Iterator_type<R>;
    typename Sentinel_type<R>;
    { begin(range) } -> Iterator_type<R>;
    { end(range) } -> Sentinel_type<R>;
  };
}

} // namespace range_impl


// A range is a sequence of elements denoted by a pair of iterators,
// accessed using using std::begin() and std::end(). 
//
// BUG: The requirements for Iterator and Sentinel should be nested
// requirements, but as of 13.04.2014, they cause an ICE.
template<typename R>
concept bool 
Range() 
{
  return seq_impl::Range<R>();
}


// Input_range
template<typename R>
concept bool 
Input_range() 
{
  return Range<R>() && Input_iterator<Iterator_type<R>>();
}


// Output_range
template<typename R, typename T>
concept bool 
Output_range() 
{
  return Range<R>() && Output_iterator<Iterator_type<R>, T>();
}


// Forward_range
template<typename R>
concept bool 
Forward_range() 
{
  return Range<R>() && Forward_iterator<Iterator_type<R>>();
}


// Bidirectional_range
template<typename R>
concept bool 
Bidirectional_range() 
{
  return Range<R>() && Bidirectional_iterator<Iterator_type<R>>();
}


// Random_access_range
template<typename R>
concept bool 
Random_access_range() 
{
  return Range<R>() && Random_access_iterator<Iterator_type<R>>();
}


} // namespace origin


#endif