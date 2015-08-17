// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_ITERATOR_CORE_HPP
#define ORIGIN_ITERATOR_CORE_HPP

#include <origin/concepts>

#include <iterator>


namespace origin {

namespace iter_impl {


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


} // namespace iter_impl


// The Iterator_category alias yields the category of a type 
// satisfying the Iterator concept.
template<typename I>
using Iterator_category = typename iter_impl::get_iterator_category<I>::type;


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


} // namespace origin


#endif