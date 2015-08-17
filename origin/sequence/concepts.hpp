// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_SEQUENCE_CONCEPTS_HPP
#define ORIGIN_SEQUENCE_CONCEPTS_HPP

#include <origin/concepts>

#include <iterator>


namespace origin {

namespace sequence_impl {


template<typename T>
struct get_iterator_category;


template<typename T>
struct get_iterator_category<T*> 
{ 
  using type = std::random_access_iterator_tag; 
};


template<typename T>
  requires requires () { typename T::iterator_category; }
struct get_iterator_category<T> 
{ 
  using type = typename T::iterator_category; 
};


} // namespace sequence_impl


// The Iterator_category alias yields the category of a type satisfying the
// Iterator concept.
template<typename I>
using Iterator_category = typename sequence_impl::get_iterator_category<I>::type;


// -------------------------------------------------------------------------- //
// Iterator Concepts                                              [iter.concept]

// A type I is Readable if and only if it has an associated value type
// that is accessible using unary * operator.
template<typename I>
concept bool Readable()
{
  return requires (I i) { {*i} -> const Value_type<I>&; };
}


// A type I is Writable if and only if the a value of type T can be
// assigned through the unary * operator.
template<typename I, typename T>
concept bool Writable() 
{
  return requires (I i, T x) { *i = std::forward<T>(x); };
}


// A type I is Permutable if and only if its associated value can be
// replaced by moving.
template<typename I>
concept bool Permutable() 
{
  return Readable<I>() && Writable<I, Value_type<I>&&>();
}


// A type I is mutable if and only if its associated value can be
// replaced by moving.
template<typename I>
concept bool Mutable() 
{
  return Permutable<I>() && Writable<I, const Value_type<I>&>();
}


// Advanceable
template<typename I>
concept bool Advanceable() 
{
  return requires (I i) { { ++i } -> I&; };
}


// Incrementable
template<typename I>
concept bool Incrementable() 
{
  return requires (I i) 
  {
    typename Difference_type<I>;
    {++i} -> I&;
    {i++} -> I;
  };
}


// Iterator
template<typename I>
concept bool Iterator() 
{
  return Equality_comparable<I>() && requires(I i) 
  {
     {++i} -> I&;
     {*i};
   };
}


// Input iterator
template<typename I>
concept bool Input_iterator() 
{ 
  return Readable<I>() && Advanceable<I>(); 
}


// Output iterator
template<typename I, typename T>
concept bool Output_iterator() 
{ 
  return Writable<I, T>() && Advanceable<I>(); 
}


// Forward iterator
template<typename I>
concept bool Forward_iterator() 
{
  return Readable<I>() && Incrementable<I>()
      && Derived<Iterator_category<I>, std::forward_iterator_tag>();
}


// Bidirectional iterator
template<typename I>
concept bool Bidirectional_iterator() 
{
  return Forward_iterator<I>() && requires (I i)
  {
   {--i} -> I&;
   {i--} -> I;
  };
}


// Random access iterator
template<typename I>
concept bool Random_access_iterator() {
  return Bidirectional_iterator<I>()
      && requires (I i, I j, Difference_type<I> n) 
  {
    {i += n} -> I&;
    {i + n} -> I;
    {n + i} -> I;
    {i -= n} -> I&;
    {i - n} -> I;
    {i - j} -> Difference_type<I>;
    {i[n]} -> decltype(*i);
  };
}


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