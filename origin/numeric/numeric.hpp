// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_NUMERIC_HPP
#define ORIGIN_NUMERIC_HPP

// This module defines the entirety of the Origin Numeric library, which
// includes numeric and algebraic concepts and their models.
//
// TODO: There are a lot of interesting things that this library could
// use: an arbitrary precision integer library, a library of statically
// bound fixed-precision integer types (e.g., Boost.Multiprecision),
// dynamically bound fixed-precision integer types, fractions and rational
// numbers, etc.

#include <origin/numeric/algebra.hpp>
#include <origin/core/concepts.hpp>

namespace origin {

// -------------------------------------------------------------------------- //
// Numbers                                                              [num] //
//
// A number is a mathematical object that represents some quantity.


// The Number concept defines the abstract notion of a number.
//
// FIXME: This does not allow
template<typename T>
  concept bool Number() { return std::is_arithmetic<T>::value; }


} // namespace origin

#endif
