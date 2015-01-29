// Copyright (c) 2008-2014 Andrew Sutton
//
// This file is distributed under the MIT License. See
// http://www.opensource.org/licenses/mit-license.php
// for terms and conditions.

#ifndef ORIGIN_SEQUENCE_UNINITIALIZED_HPP
#define ORIGIN_SEQUENCE_UNINITIALIZED_HPP

#include <origin/sequence/concepts.hpp>
#include <origin/memory/memory.hpp>

namespace origin {

// FIXME: For all of these algorithms the constraints are
// essentially input iterators that point to legitimate objects,
// that is, non-proxy iterators.


// Explicitly destroy the objects in the range [first, last).
//
// FIXME: Write constraints.
template<typename I>
  void
  destroy(I first, I last) { 
    destroy(&*first); 
  }

// Copy initialize each element in the bounded range [first2, last2)
// from the elements in the range [first1, last1) where last2 is 
// first2 + distance(first1, last1).
//
// Before this call, the memory in [first2, last) is uninitialized.
//
// FIXME: Write constraints.
template<typename I1, typename I2>
  I2
  uninitialized_copy(I1 first1, I1 last1, I2 first2) {
    I2 iter = first2;
    while (first1 != last1) {
      try {
        construct(&*iter, *first1);
      } catch (...) {
        destroy(first1, iter);
        throw;
      }
      ++first1;
      ++iter;
    }
  }


// Move initialize each element in the range [first2, last2) from the 
// elements in the range [first1, last1) where last2 is 
// first2 + distance(first1, last1).
//
// Before this call, the memory in [first2, last) is uninitialized.
//
// FIXME: Write constraints.
template<typename I1, typename I2>
  I2
  uninitialized_move(I1 first1, I1 last1, I2 first2) {
    I2 iter = first2;
    while (first1 != last1) {
      try {
        construct(&*iter, std::move(*first1));
      } catch (...) {
        destroy(first1, iter);
        throw;
      }
      ++first1;
      ++iter;
    }
  }

} // namespace origin

#endif
