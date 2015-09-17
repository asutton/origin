// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_MATH_NUMERIC_HPP
#define ORIGIN_MATH_NUMERIC_HPP

// #include <origin/sequence/concepts.hpp>
// #include <origin/sequence/algorithms.hpp>

#include <algorithm>
#include <functional>
#include <limits>
#include <cmath>

// The numeric module provides basic algorithms for operations on numeric
// types. Note the term "numeric" generally applies to any type for which
// an algebraic structure can be defined. For example, strings are not
// generally considered numeric quantities, yet they naturally form a
// monoid under concatenation.
//
// TODO: The definition of identity elements is not easily solved for
// numeric types. In some cases, the identity element may be patterened
// on some other element in a sequence. For example, the additive idenity 
// of a vector in Rn, where n is a runtime quantity, is the vector with n 
// 0.0 values.
//
// Currently, we assume that for some numeric type T, T{0} constructs the
// additive identity and T{1} constructs the multiplicative identity.

namespace origin {

// FIXME: Do not define this:

template<typename T>
  using Value_type = typename T::value_type;


// -------------------------------------------------------------------------- //
// Numeric values                                                   [num.values]

// Returns true if the Integral value n is even.
template<typename T>
  inline bool even(T n) { return n % 2 == 0; }

// Returns true if the Integral value n is odd.
template<typename T>
  inline bool odd(T n) { return n % 2 == 1; }

// Returns true if n is an infinite value. Note that n could be positive
// or negative infinity.
//
// TODO: This is not general.
template<typename T>
  inline bool
  is_infinity(T n) { return std::isinf(n); }


// -------------------------------------------------------------------------- //
// Accumulation                                              [num.accumulate]

// Returns the accumulation of the elements in [first, last), with
// value as the initial element in the accumulation, using the
// binary operator op to combine consecutive elemens in the range.
template<typename I, typename T, typename Op>
  inline T 
  accumulate(I first, I last, T value, Op op) {
    while (first != last) {
      value = op(value, *first);
      ++first;
    }
    return value;
  }

// Returns the sum of the elements in [first, last), with value
// as the initial element in the accumulation.
template<typename I, typename T>
  inline T
  accumulate(I first, I last, T value) {
    return accumulate(first, last, value, std::plus<T>{});
  }

// Return the sum of elements in the range [first, last). 
template<typename I, typename T = Value_type<I>>
  inline T
  sum(I first, I last) {
    return accumulate(first, last, T{0}, std::plus<T>{});
  }

// Return the product of the elements in the range [first, last).
template<typename I, typename T = Value_type<I>>
  inline T
  product(I first, I last) {
    return accumulate(first, last, T{1}, std::multiplies<T>{});
  }

} // namespace origin

#endif
