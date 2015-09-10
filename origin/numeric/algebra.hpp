// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_NUMERIC_ALGEBRA_HPP
#define ORIGIN_NUMERIC_ALGEBRA_HPP

#include <origin/core/concepts.hpp>
#include <origin/sequence/concepts.hpp>

namespace origin {

// A monoid is a set of values equipped with an associative binary
// operation and some identity element.
template<typename T, typename Op>
  concept bool Monoid() {
    return Binary_operation<Op, T>();
  }


// The left fold operation.
template<Input_iterator I, typename Op>
  requires Monoid<Value_type<I>, Op>()
    Value_type<I>
    foldl(I first, I last, Op op, const Value_type<I>& e) {
      Value_type<I> x = e;
      while (first != last) {
        x = op(x, *first);
        ++first;
      }
      return x;
    }


// The right fold operation.
template<Bidirectional_iterator I, typename Op>
  requires Monoid<Value_type<I>, Op>()
    Value_type<I>
    foldr(I first, I last, Op op) {
      using R = std::reverse_iterator<I>;
      return foldl(R{last}, R{first}, op);
    }


// -------------------------------------------------------------------------- //
// Monoid structure                                           [monoid.struct] //

// The monoid algebraic structure is used to encapsulate operators
// end their identity functions. A number of constructors are provided
// for common abstractions.
template<typename T, typename Op>
  requires Monoid<T, Op>()
    struct monoid {
      T id;
      Op op;
    };


// Left-fold with a monoid structure.
template<Input_iterator I, typename Op>
  inline Value_type<I>
  foldl(I first, I last, monoid<Value_type<I>, Op> const& m) {
    return foldl(first, last, m.op, m.id);
  }

// Right-fold with a monoid structure.
template<Input_iterator I, typename Op>
  inline Value_type<I>
  foldr(I first, I last, monoid<Value_type<I>, Op> const& m) {
    return foldr(first, last, m.op, m.id);
  }


// -------------------------------------------------------------------------- //
// Monoid constructors                                          [monoid.ctor] //
//
// The following functions are used to construct instances of
// monoids for different types.
//
// Each of the following constructs a monoid for its corresponding
// operations.
//
//
//    Sum<T>()        addition
//    Product<T>()    multiplication
//    All<T>()        intersection
//    Any<T>()        union
//
// Note that
//
// Each constructor above also accepts the identity element, when
// there is no direct association of the identity with the
// type (e.g., matrices of dynamic bound).
//
//    Sum<T>(e)
//    Product<T>(e)
//    All<T>(e)
//    Any<T>(e)
//
// These functions are capitalized to emphasize the idea that they
// construct unspecified models of a concept.
//
// NOTE: In the following declarations, the defaulted operators
// are not part of the public interface.

namespace monoid_impl {

template<Integral_type T>
  struct all_any_traits {
    using all_op = std::bit_and<T>;
    using any_op = std::bit_or<T>;
    static constexpr T all_id = -1;
    static constexpr T any_id = 0;
  };

template<>
  struct all_any_traits<bool> {
    using all_op = std::logical_and<bool>;
    using any_op = std::logical_or<bool>;
    static constexpr bool all_id = true;
    static constexpr bool any_id = false;
  };

template<typename T>
  using all_op = typename all_any_traits<T>::all_op;

template<typename T>
  using any_op = typename all_any_traits<T>::any_op;

template<typename T>
  static constexpr T all_id() { return all_any_traits<T>::all_id; }

template<typename T>
  static constexpr T any_id() { return all_any_traits<T>::any_id; }

} // namespace monoid_impl

// -------------------------------------------------------------------------- //
// Sum                                                          [monoid.sum] //
//
// The Sum constructor defines a monoid (T, +) where T is an
// arithmetic type.

template<Arithmetic_type T, typename Op = std::plus<T>>
  inline monoid<T, Op>
  Sum() { return monoid<T, Op>{T{0}, Op{}}; }

template<typename T, typename Op = std::plus<T>>
  requires Monoid<T, Op>()
    inline monoid<T, Op>
    Sum(T const& e) { return monoid<T, Op>{e, Op{}}; }


// -------------------------------------------------------------------------- //
// Product                                                   [monoid.product] //

template<Arithmetic_type T, typename Op = std::multiplies<T>>
  inline monoid<T, Op>
  Product() { return monoid<T, Op>{T{1}, Op{}}; }

template<typename T, typename Op = std::multiplies<T>>
  requires Monoid<T, Op>()
    inline monoid<T, Op>
    Product(T const& e) { return monoid<T, Op>{e, Op{}}; }


// -------------------------------------------------------------------------- //
// All                                                           [monoid.all] //
//
// The All constructor defines the algebraic structure (T, op) where
// op is defined as follows:
//
//  - if T has type bool, op is the logical and operator and the
//   identity element is true;
// - otherwise, if T is some other integral type, it is the bitwise
//    and operator and the identity element is -1.
//
// In general, the semantics of the operator in this monoid can be
// thought of as computing the intersection of sets. When used in
// a fold, the result is a set containing the common elements of
// the operand.
//
// TODO: Can we extend this for set-like data structures?

template<Integral_type T = bool, typename Op = monoid_impl::all_op<T>>
  inline monoid<T, Op>
  All() { return monoid<bool, Op>{monoid_impl::all_id<T>(), Op{}}; }

template<typename T, typename Op>
  requires Monoid<T, Op>()
    inline monoid<T, Op>
    All(T const& e) { return monoid<bool, Op>{e, Op{}}; }


// -------------------------------------------------------------------------- //
// Any                                                           [monoid.any] //
//
// The Any constructor defines the algebraic structure (T, op) where
// op is defined as follows:
//
//  - if T has type bool, op is the logical or operator and the
//   identity element is false;
// - otherwise, if T is some other integral type, it is the bitwise
//    or operator and the identity element is 0.
//
// In general, the semantics of the operator in this monoid can be
// thought of as computing the union of sets.

template<Integral_type T = bool, typename Op = monoid_impl::any_op<T>>
  inline monoid<T, Op>
  Any() { return monoid<bool, Op>{monoid_impl::any_id<T>(), Op{}}; }

template<typename T, typename Op>
  requires Monoid<T, Op>()
    inline monoid<T, Op>
    Any(T const& e) { return monoid<bool, Op>{e, Op{}}; }


} // namespace origin

#endif
