// (C) 2013 Andrew Sutton
//
// This file is distributed under the MIT License. See
// http://www.opensource.org/licenses/mit-license.php
// for terms and conditions.

#ifndef ORIGIN_ITERATOR_HPP
#define ORIGIN_ITERATOR_HPP

#include "concepts.hpp"

namespace origin {

// Iterator category

template<typename I>
  struct get_iterator_category;

template<typename T>
  struct get_iterator_category<T*>
  {
    using type = std::random_access_iterator_tag;
  };

template<typename T>
  requires requires () { typename T::get_iterator_category; }
    struct get_iterator_category<T>
    {
      using type = typename T::get_iterator_category;
    };

template<typename I>
  using Iterator_category = typename get_iterator_category<I>::type;


// Readable
template<typename I>
  constexpr bool Readable()
  {
    return requires (I i) {
             {*i} -> const Value_type<I>&;
           };
  }

// Writable
template<typename I, typename T>
  constexpr bool Writable()
  {
    return requires (I i, T x) {
             *i = std::forward<T>(x); 
           };
  }

// Permutable
template<typename I>
  constexpr bool Permutable()
  {
    return Readable<I>() 
        && Writable<I, Value_type<I>&&>();
  }

// Mutable
template<typename I>
  constexpr bool Mutable()
  {
    return Permutable<I> 
        && Writable<I, const Value_type<I>&>();
  }

// Advanceable
template<typename I>
  constexpr bool Advanceable()
  {
    return requires (I i) {
             { ++i } -> I&;
           };
  }

// Incrementable
template<typename I>
  constexpr bool Incrementable()
  {
    return requires (I i) {
             Difference_type<I>;
             {++i} -> I&;
             {i++} -> I;
           };
  }

// Input iterator
template<typename I>
  constexpr bool Input_iterator()
  {
    return Readable<I>() && Advanceable<I>();
  }

template<typename I, typename T>
  constexpr bool Output_iterator()
  {
    return Writable<I, T>() && Advanceable<I>();
  }

// Forward iterator
template<typename I>
  constexpr bool Forward_iterator()
  {
    return Readable<I>() && Incrementable<I>();
  }

// Bidirectional iterator
template<typename I>
  constexpr bool Bidirectional_iterator()
  {
    return Forward_iterator<I>()
        && requires (I i)
           {
             {--i} -> I&;
             {i--} -> I;
           };
  }

// Random access iterator
template<typename I>
  constexpr bool Random_access_iterator()
  {
    return Bidirectional_iterator<I>()
        && requires (I i, I j, Difference_type<I> n) {
             {i += n} -> I&;
             {i + n} -> I;
             {n + i} -> I;
             {i -= n} -> I&;
             {i - n} -> I;
             {i - j} -> Difference_type<I>;
             {i[n]} -> decltype(*i);
           };
  }

// Range Concepts

// Range
template<typename R>
  constexpr bool Range()
  {
    return requires (R range) {
      std::begin(range);
      std::end(range);
      requires Same<decltype(std::begin(range)), decltype(std::end(range))>();
    };
  }

// Iterator type
template<typename R>
  using Iterator_type = decltype(std::begin(std::declval<R>()));

template<typename R>
  constexpr bool Input_range()
  {
    return Range<R>() && Input_iterator<Iterator_type<R>>();
  }

template<typename R>
  constexpr bool Forward_range()
  {
    return Range<R>() && Forward_iterator<Iterator_type<R>>();
  }

template<typename R>
  constexpr bool Bidirectional_range()
  {
    return Range<R>() && Bidirectional_iterator<Iterator_type<R>>();
  }

template<typename R>
  constexpr bool Random_access_range()
  {
    return Range<R>() && Random_access_iterator<Iterator_type<R>>();
  }


} // namespace origin


#endif