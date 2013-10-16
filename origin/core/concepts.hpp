// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_CORE_CONCEPTS_HPP
#define ORIGIN_CORE_CONCEPTS_HPP

#include <type_traits>
#include <utility>

#include "traits.hpp"

namespace origin {

// Is true if and only if T and U are the same type.
template<typename T, typename U>
  concept bool 
  Same() { return __is_same_as(T, U); }

// Is true if and only if T is derived from U or is the same as U.
template<typename T, typename U>
  concept bool 
  Derived() { return __is_base_of(U, T); }

// Is true if and only if T can be implicitly converted to U through
// a user-defined conversion sequence.
template<typename T, typename U>
  concept bool 
  Convertible() { return __is_convertible_to(T, U); }

// Represents the common type of a sequence of type arguments. More
// precisely, if there exists some type C such that each type T in Ts
// can be converted to C, then C is the common type of all T in Ts.
//
// There are two common uses of the Common_type facility: defining
// requirements on heterogeneously typed templates, and extracting a
// meaningful type for concept checking in the presence of perfect
// forwarding.
//
// Note that in cases where forwarding is used, the unary Common_type
// provides the type against which concept checking should be done.
// For example:
//
//      template<typename T>
//        requires<Object<Common_type<T>>()
//          void f(T&& x);
//
// The Common_type wil
template<typename... Ts>
  using Common_type = typename std::common_type<Ts...>::type;

// True if and only if there exists a common type of Ts.
template<typename... Ts>
  concept bool 
  Common() {
    return requires () { 
      Common_type<Ts...>; // FIXME: This better be a type requirement.
    }; 
  }

// True if and only if an expression of type T can be contextually 
// converted to bool.
template<typename T>
  concept bool 
  Conditional() { return requires (T p) { p ? true : false; }; }

namespace core_impl {
template<typename T>
  concept bool 
  User_defined_logical()
  {
    return Class_type<T>() 
        && requires (T a, T b) {
             {a && b} -> T;
             {a || b} -> T;
             {!a} -> T;
           };
  }
} // namespace core_impl

// Declarations

// Is true if and only if T is a Conditional type but not a user-defined 
// logical type. That is T must not overload the &&, ||, and ! operators. 
//
// TODO: Is there a way to determine the user has overloaded an operator?
template<typename T> 
  concept bool 
  Boolean() {
    return Conditional<T>() && not core_impl::User_defined_logical<T>();
  }

// Relational Concepts

// Is true if and only if arguments of type T can be compared using the 
// `==` and `!=` operators.
//
// Types modeling this concept must ensure that the `==` operator
// returns true only when the arguments have the same value. 
template<typename T>
  concept bool 
  Equality_comparable() {
    return requires (T a, T b) {
             a == b; requires Boolean<decltype(a == b)>();
             a != b; requires Boolean<decltype(a != b)>();
           };
  }

// Is true if and only if arguments of types T and U share a common type
// and can be compared using the == and != operators.
//
// Pairs of types modeling this concept must ensure the `==` operator
// returns true only when the arguments, when converted to their common
// type, and those converted values are the same.
template<typename T, typename U>
  concept bool 
  Equality_comparable() {
    return Equality_comparable<T>() 
        && Equality_comparable<U>() 
        && Common<T, U>() 
        && requires (T t, T u) {
             t == u; requires Boolean<decltype(t == u)>();
             u == t; requires Boolean<decltype(u == t)>();
             t != u; requires Boolean<decltype(t != u)>();
             u != t; requires Boolean<decltype(u != t)>();
          };
  }

// Is true if and only if arguments of type T can be compared using the
// inequality operators `<`, `>`, `<=`, and `>=`.
//
// Types modeling this concept must ensure that the `<` operator defines
// a strict weak order.
template<typename T>
  concept bool 
  Weakly_ordered()
  {
    return requires (T a, T b) {
             a < b;  requires Boolean<decltype(a < b)>();
             a > b;  requires Boolean<decltype(a > b)>();
             a <= b; requires Boolean<decltype(a <= b)>();
             a >= b; requires Boolean<decltype(a >= b)>();
           };
  }

// Weakly ordered
template<typename T, typename U>
  concept bool Weakly_ordered()
  {
    return Weakly_ordered<T>() 
        && Weakly_ordered<U>() 
        && Common<T, U>() 
        && requires (T t, T u) {
             t < u;  requires Boolean<decltype(t < u)>();
             u < t;  requires Boolean<decltype(u < t)>();
             t > u;  requires Boolean<decltype(t > u)>();
             u > t;  requires Boolean<decltype(u > t)>();
             t <= u; requires Boolean<decltype(t <= u)>();
             u <= t; requires Boolean<decltype(u <= t)>();
             t >= u; requires Boolean<decltype(t >= u)>();
             u <= t; requires Boolean<decltype(u >= t)>();
      };
  }

// Totally ordered
template<typename T>
  concept bool Totally_ordered()
  {
    return Equality_comparable<T>() && Weakly_ordered<T>();
  }

// Totally ordered
template<typename T, typename U>
  concept bool Totally_ordered()
  {
    return Totally_ordered<T>() 
        && Totally_ordered<U>()
        && Equality_comparable<T, U>()
        && Weakly_ordered<T, U>();
  }


// Regular types

// Is true if a variable of type T can be destroyed.
template<typename T>
  concept bool 
  Destructible() { return std::is_destructible<T>::value; }

// Is true if and only if an object of type T can be constructed with
// the types of arguments in Args.
template<typename T, typename... Args>
  concept bool Constructible() 
  { 
    return Destructible<T>() && std::is_constructible<T, Args...>::value; 
  }

// Is true if and only if an object of T can be default constructed.
//
// Note that default construction implies that an object of type T can
// also be default initialized. Types modeling this concept must ensure
// that any two default initialized objects must have the same value.
template<typename T>
  concept bool 
  Default_constructible() { return Constructible<T>(); }

// Is true if and only if an object of type T can be move constructed.
template<typename T>
  concept bool 
  Move_constructible() { return Constructible<T, T&&>(); }

// Is true if and only if an object of type T can be copy constructed.
template<typename T>
  concept bool 
  Copy_constructible() {
    return Move_constructible<T>() && Constructible<T, const T&>(); 
  }

// Is true if and only if an argument of type T can be assigned a value
// of type U.
//
// Note that T is typically expected to be an lvalue reference type.
template<typename T, typename U>
  concept bool 
  Assignable() { return std::is_assignable<T, U>::value; }

// Is true if and only if an object of type T can be move assigned.
template<typename T>
  concept bool 
  Move_assignable() { return Assignable<T&, T&&>(); }

// Is true if and only if an object of type T can be copy assigned.
template<typename T>
  concept bool 
  Copy_assignable() {
    return Move_assignable<T>() && Assignable<T&, const T&>(); 
  }


// Is true if and only if T supports move semantics. The type T must
// be move constructible and move assignable.
template<typename T>
  concept bool 
  Movable() {
    return Move_constructible<T>() && Move_assignable<T>();
  }

// Is true if and only if T supports copy semantics. The type T must 
// be copy constructible and copy assignable. 
template<typename T>
  concept bool 
  Copyable() {
    return Copy_constructible<T>() && Copy_assignable<T>();
  }

// Is true if and only if T is a semiregular type. A semiregular type
// is both default constructible and copyable.
template<typename T>
  concept bool 
  Semiregular() {
    return Default_constructible<T>() && Copyable<T>();
  }

// Is true if T is a regular type. A regular type is a semiregular type
// that is also equality comparable.
template<typename T>
  concept bool 
  Regular() {
    return Semiregular<T>() && Equality_comparable<T>();
  }

// Is true if T is an ordered type. An ordered type is a 
template<typename T>
  concept bool 
  Ordered() {
    return Regular<T>() && Totally_ordered<T>();
  }


// Functional types

// Function
template<typename F, typename... Args>
  concept bool 
  Function()
  {
    return Copy_constructible<F>()
        && requires (F f, Args... args) {
             f(args...);
           };
  }

// Predicate
template<typename P, typename... Args>
  concept bool 
  Predicate()
  {
    return requires (P pred, Args... args) {
             {pred(args...)} -> bool;
           };
  }

// Relation
template<typename R, typename T>
  concept bool 
  Relation()
  {
    return Predicate<R, T, T>();
  }

// Relation (cross-type)
template<typename R, typename T, typename U>
  concept bool 
  Relation()
  {
    return Relation<R, T>()
        && Relation<R, U>()
        && Common<T, U>()
        && requires (R r, T t, U u) {
             {r(t, u)} -> bool;
             {r(u, t)} -> bool;
           };
  }

// Unary_operation
template<typename F, typename T>
  concept bool 
  Unary_operation()
  {
    return requires (F f, T a) {
             {f(a)} -> T;
           };
  }

// Binary_operation
template<typename F, typename T>
  concept bool 
  Binary_operation()
  {
    return requires (F f, T a, T b) {
             {f(a, b)} -> T;
           };
  }

// Binary_operation (cross-type)
template<typename F, typename T, typename U>
  concept bool 
  Binary_operation()
  {
    return Binary_operation<F, T>()
        && Binary_operation<F, U>()
        && Common<T, U>()
        && requires (F f, T t, U u) {
             {f(t, u)} -> Common_type<T, U>;
             {f(u, t)} -> Common_type<T, U>;
           };
  }


// Miscellaneous associated types

namespace core_impl {
template<typename T>
  struct get_value_type;

template<typename T>
  struct get_value_type<T*> { using type = T; };

template<typename T>
  struct get_value_type<const T*> { using type = T; };

template<typename T>
  struct get_value_type<T[]> { using type = T; };

template<typename T, std::size_t N>
  struct get_value_type<T[N]> { using type = T; };

template<typename T>
  requires requires () { typename T::value_type; }
    struct get_value_type<T> { using type = typename T::value_type; };

template<typename T>
  using value_type = typename get_value_type<Common_type<T>>::type;
} // namespace core_impl

// Value type
template<typename T>
  using Value_type = core_impl::value_type<T>;


namespace core_impl {
template<typename T>
  struct get_difference_type;

template<typename T>
  struct get_difference_type<T*> { using type = std::ptrdiff_t; };

template<typename T>
  struct get_difference_type<T[]> { using type = std::ptrdiff_t; };

template<typename T, std::size_t N>
  struct get_difference_type<T[N]> { using type = std::ptrdiff_t; };

template<typename T>
  requires requires () { typename T::difference_type; }
    struct get_difference_type<T> { using type = typename T::difference_type; };

template<typename T>
  using difference_type = typename get_difference_type<Common_type<T>>::type;
} // namespace core_impl

// Difference_type
template<typename T>
  using Difference_type = core_impl::difference_type<T>;

namespace core_impl {
template<typename T>
  struct get_size_type;

template<typename T>
  struct get_size_type<T*> { using type = std::size_t; };

template<typename T>
  struct get_size_type<T[]> { using type = std::size_t; };

template<typename T, std::size_t N>
  struct get_size_type<T[N]> { using type = std::size_t; };

template<typename T>
  requires requires () { typename T::size_type; }
    struct get_size_type<T> { using type = typename T::size_type; };  

template<typename T>
  using size_type = typename get_size_type<Common_type<T>>::type;
} // namespace core_impl

// Size_type
template<typename T>
  using Size_type = core_impl::size_type<T>;

} // namespace origin

#endif
