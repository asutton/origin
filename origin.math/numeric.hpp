// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_MATH_NUMERIC_HPP
#define ORIGIN_MATH_NUMERIC_HPP

#include <origin/sequence/concepts.hpp>
#include <origin/sequence/algorithms.hpp>

#include <numeric_limits>
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

// -------------------------------------------------------------------------- //
// Numeric values                                                   [num.values]

// Returns true if n is an infinite value. Note that n could be positive
// or negative infinity.
template<typename T>
  inline bool
  is_infinity(T n) { return std::isinf(n); }

template<typename T>
  inline bool
  is_positive_infinity(T n) { return n > 0 && is_infinity(n); }

template<typename T>
  inline bool
  is_negative_infinity(T n) { return n < 0 && is_infinity(n); }


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
