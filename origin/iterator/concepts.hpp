// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_ITERATOR_HPP
#define ORIGIN_ITERATOR_HPP

#include <origin/core/concepts.hpp>

namespace origin {

// Readable
template<typename I>
  concept bool Readable()
  {
    return requires (I i) {
             {*i} -> const Value_type<I>&;
           };
  }

// Writable
template<typename I, typename T>
  concept bool Writable()
  {
    return requires (I i, T x) {
             *i = std::forward<T>(x); 
           };
  }

// Permutable
template<typename I>
  concept bool Permutable()
  {
    return Readable<I>()
        && Writable<I, Value_type<I>&&>();
  }

// Mutable
template<typename I>
  concept bool Mutable()
  {
    return Permutable<I>()
        && Writable<I, const Value_type<I>&>();
  }

// Advanceable
template<typename I>
  concept bool Advanceable()
  {
    return requires (I i) {
             { ++i } -> I&;
           };
  }

// Incrementable
template<typename I>
  concept bool Incrementable()
  {
    return requires (I i) {
             Difference_type<I>;
             {++i} -> I&;
             {i++} -> I;
           };
  }

// Input iterator
template<typename I>
  concept bool Input_iterator()
  {
    return Readable<I>() && Advanceable<I>();
  }

template<typename I, typename T>
  concept bool Output_iterator()
  {
    return Writable<I, T>() && Advanceable<I>();
  }

// Forward iterator
template<typename I>
  concept bool Forward_iterator()
  {
    return Readable<I>() && Incrementable<I>();
  }

// Bidirectional iterator
template<typename I>
  concept bool Bidirectional_iterator()
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
  concept bool Random_access_iterator()
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

} // namespace origin


#endif