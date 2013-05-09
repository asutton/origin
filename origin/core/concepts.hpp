// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_CORE_CONCEPTS_HPP
#define ORIGIN_CORE_CONCEPTS_HPP

#include <type_traits>

namespace origin {

// Same
template<typename T, typename U>
  concept bool Same() { return __is_same_as(T, U); }

// Derived
template<typename T, typename U>
  concept bool Derived() { return __is_base_of(U, T); }

// Convertible
template<typename T, typename U>
  concept bool Convertible() { return __is_convertible_to(T, U); }

// Common
template<typename T, typename U>
  concept bool Common() 
  { 
    return requires (T t, U u) { true ? t : u; }; 
  }

// Common type
template<typename T, typename U>
  requires Common<T, U>()
    using Common_type = decltype(true ? std::declval<T>() : std::declval<U>());


// Relational Concepts

// Equality comparable
template<typename T>
  concept bool Equality_comparable()
  {
    return requires (T a, T b) {
             {a == b} -> bool;
             {a != b} -> bool;
           };
  }

// Equality comparable
template<typename T, typename U>
  concept bool Equality_comparable()
  {
    return Equality_comparable<T>() 
        && Equality_comparable<U>() 
        && Common<T, U>() 
        && requires (T t, T u) {
            {t == u} -> bool;
            {u == t} -> bool;
            {t != u} -> bool;
            {u != t} -> bool;
          };
  }

// Weakly ordered
template<typename T>
  concept bool Weakly_ordered()
  {
    return requires (T a, T b) {
             {a < b} -> bool;
             {a > b} -> bool;
             {a <= b} -> bool;
             {a >= b} -> bool;
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
            {t < u} -> bool;
            {u < t} -> bool;
            {t > u} -> bool;
            {u > t} -> bool;
            {t <= u} -> bool;
            {u <= t} -> bool;
            {t >= u} -> bool;
            {u <= t} -> bool;
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

// Destructible

template<typename T>
  concept bool Destructible() { return std::is_destructible<T>::value; }

// Constructible

template<typename T, typename... Args>
  concept bool Constructible() 
  { 
    return Destructible<T>() && std::is_constructible<T, Args...>::value; 
  }

// Default constructible

template<typename T>
  concept bool Default_constructible() { return Constructible<T>(); }

// Move constructible

template<typename T>
  concept bool Move_constructible() { return Constructible<T, T&&>(); }

// Copy constructible

template<typename T>
  concept bool Copy_constructible() 
  { 
    return Move_constructible<T>() && Constructible<T, const T&>(); 
  }

// Assignable

template<typename T, typename U>
  concept bool Assignable() { return std::is_assignable<T, U>::value; }

// Move assignable

template<typename T>
  concept bool Move_assignable() { return Assignable<T&, T&&>(); }

// Copy assignable

template<typename T>
  concept bool Copy_assignable() 
  { 
    return Move_assignable<T>() && Assignable<T&, const T&>(); 
  }

// Movable

template<typename T>
  concept bool Movable()
  {
    return Move_constructible<T>() && Move_assignable<T>();
  }

// Copyable

template<typename T>
  concept bool Copyable()
  {
    return Copy_constructible<T>() && Copy_assignable<T>();
  }

// Semiregular

template<typename T>
  concept bool Semiregular()
  {
    return Default_constructible<T>() && Copyable<T>();
  }

// Regular

template<typename T>
  concept bool Regular()
  {
    return Semiregular<T>() && Equality_comparable<T>();
  }

// Ordered

template<typename T>
  concept bool Ordered()
  {
    return Regular<T>() && Totally_ordered<T>();
  }

// Function

template<typename F, typename... Args>
  concept bool Function()
  {
    return Copy_constructible<F>()
        && requires (F f, Args... args) {
             f(args...);
           };
  }

// Predicate

template<typename P, typename... Args>
  concept bool Predicate()
  {
    return requires (P pred, Args... args) {
             {pred(args...)} -> bool;
           };
  }

// Relation

template<typename R, typename T>
  concept bool Relation()
  {
    return Predicate<R, T, T>();
  }

// Unary_operation

template<typename F, typename T>
  concept bool Unary_operation()
  {
    return requires (F f, T a) {
             {f(a)} -> T;
           };
  }

template<typename F, typename T>
  concept bool Binary_operation()
  {
    return requires (F f, T a, T b) {
             {f(a, b)} -> T;
           };
  }

template<typename F, typename T, typename U>
  concept bool Binary_operation()
  {
    return Binary_operation<F, T>()
        && Binary_operation<F, U>()
        && Common<T, U>()
        && requires (F f, T t, U u) {
             {f(t, u)} -> Common_type<T, U>;
             {f(u, t)} -> Common_type<T, U>;
           };
  }

// Main type

template<typename T>
  using Main_type = typename std::remove_cv<
                      typename std::remove_reference<T>::type
                    >::type;

// Value type

namespace core_impl
{
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
} // namespace core_impl

template<typename T>
  using Value_type = typename core_impl::get_value_type<T>::type;


// Difference_type

namespace core_impl
{
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
} // namespace core_impl

template<typename T>
  using Difference_type = typename core_impl::get_difference_type<T>::type;

} // namespace origin

#endif
