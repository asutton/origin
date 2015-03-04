// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_CORE_CONCEPTS_HPP
#define ORIGIN_CORE_CONCEPTS_HPP

#include <type_traits>
#include <iosfwd>
#include <utility>

#include "traits.hpp"

namespace origin {

// A type `T` is the same as a type `U` if 
template<typename T, typename U>
  concept bool 
  Same() { return __is_same_as(T, U); }


// Is true if and only if T is derived from U or is the same as U.
template<typename T, typename U>
  concept bool 
  Derived() { return __is_base_of(U, T); }


// A type `T` is convertible to another type `U` if an object
// `t` of type `T` can be returned from a function whose return 
// type is `U`. 
template<typename T, typename U>
  concept bool 
  Convertible() { return std::is_convertible<T, U>::value; }


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
      typename Common_type<Ts...>; // FIXME: This better be a type requirement.
    }; 
  }


// True if and only if an expression of type T can be contextually 
// converted to bool.
template<typename T>
  concept bool 
  Conditional() { return requires (T p) { p ? true : false; }; }


// -------------------------------------------------------------------------- //
// Relational concepts                                           [concepts.comp]
//
// The relational concepts define requirements on types that can be
// compared using the C++ relational operators.


// A type T is equality comparable if its values can be compared using
// oerators `==` and `!=`.
//
// Types modeling this concept must ensure that the `==` operator
// returns true only when the arguments have the same value and that
// `!=` is the logical inverse of `==`.
template<typename T>
  concept bool 
  Equality_comparable() {
    return requires (T a, T b) {
             { a == b } -> bool;
             { a != b } -> bool;
           };
  }

// A pair of types T and U are (cross-type) equality comparable 
// only when ...
template<typename T, typename U>
  concept bool 
  Equality_comparable() {
    return Equality_comparable<T>() 
        && Equality_comparable<U>() 
        && Common<T, U>() 
        && requires (T t, T u) {
             { t == u } -> bool;
             { u == t } -> bool;
             { t != u } -> bool;
             { u != t } -> bool;
          };
  }

// A type T is weakly ordered when it can be compared using the
// operators `<`, `>`, `<=`, and `>=`.
//
// TODO: Document semantics.
//
// Note that in a weakly ordered type, for all objects `a` and `b`
// of type `T`, when `a <= b` and `b <= a`, `a` and `b` are
// equivalent, but they are not known to be equal.
template<typename T>
  concept bool 
  Weakly_ordered()
  {
    return requires (T a, T b) {
             { a < b } -> bool;
             { a > b } -> bool;
             { a <= b } -> bool;
             { a >= b } -> bool;
           };
  }

// TODO: Document me.
template<typename T, typename U>
  concept bool Weakly_ordered()
  {
    return Weakly_ordered<T>() 
        && Weakly_ordered<U>() 
        && Common<T, U>() 
        && requires (T t, T u) {
             { t < u } -> bool;
             { u < t } -> bool;
             { t > u } -> bool;
             { u > t } -> bool;
             { t <= u } -> bool;
             { u <= t } -> bool;
             { t >= u } -> bool;
             { u <= t } -> bool;
      };
  }

// A type `T` is totally ordered when it is both equality comparable
// and weakly ordered.
//
// Types modeling this concept must guarantee that, for all `a` and
// `b` of type `T`, when `a <= b` and `b <= a`, `a == b`.
template<typename T>
  concept bool Totally_ordered()
  {
    return Equality_comparable<T>() && Weakly_ordered<T>();
  }

// TODO: Document me.
template<typename T, typename U>
  concept bool Totally_ordered()
  {
    return Totally_ordered<T>() 
        && Totally_ordered<U>()
        && Equality_comparable<T, U>()
        && Weakly_ordered<T, U>();
  }


// -------------------------------------------------------------------------- //
// Regular types                                                 [concepts.type]
//
// There are a number of concepts that contributed (piecewise) to the
// definition of regular types.

// Is true if a variable of type T can be destroyed.
template<typename T>
  concept bool 
  Destructible() { return std::is_destructible<T>::value; }

// Is true if and only if an object of type T can be constructed with
// the types of arguments in Args.
template<typename T, typename... Args>
  concept bool 
  Constructible() {
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


// A type is a semiregular type if it is default constructible and
// copyable. Alternatively, a semiregular type is a regular type that
// is not equality comparable.
//
// The semiregular type represents types like C structures, which can
// be default constructed and copied, but have no default definition
// of equality.
template<typename T>
  concept bool 
  Semiregular() {
    return Default_constructible<T>() && Copyable<T>();
  }


// A type `T` is regular when it is semiregular and equality comparable.
// Regular types can be used like most scalar types, although they
// are not guaranteed to be ordered (comparble with `<`).
template<typename T>
  concept bool 
  Regular() {
    return Semiregular<T>() && Equality_comparable<T>();
  }


// A type is ordered if it is a regular type that is also totally ordered.
template<typename T>
  concept bool 
  Ordered() {
    return Regular<T>() && Totally_ordered<T>();
  }


// -------------------------------------------------------------------------- //
// Function concepts                                               [concepts.fn]
//
// The function concepts describe requirements on types that can be
// called as functions using the syntax 'f(args...)', where 'f' is
// the function-like type and 'args' is a (possibly empty) sequence
// of arguments.


// Function
template<typename F, typename... Args>
  concept bool 
  Function() {
    return Copy_constructible<F>()
       and requires (F f, Args... args) { f(args...); };
  }

// Predicate
template<typename P, typename... Args>
  concept bool 
  Predicate() {
    return requires (P pred, Args... args) { {pred(args...)} -> bool; };
  }

// Relation
template<typename R, typename T>
  concept bool 
  Relation() {
    return Predicate<R, T, T>();
  }

// Relation (cross-type)
template<typename R, typename T, typename U>
  concept bool 
  Relation() {
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
  Unary_operation() {
    return requires (F f, T a) {
             {f(a)} -> T;
           };
  }

// Binary_operation
template<typename F, typename T>
  concept bool 
  Binary_operation() {
    return requires (F f, T a, T b) {
             {f(a, b)} -> T;
           };
  }

// Binary_operation (cross-type)
template<typename F, typename T, typename U>
  concept bool 
  Binary_operation() {
    return Binary_operation<F, T>()
        && Binary_operation<F, U>()
        && Common<T, U>()
        && requires (F f, T t, U u) {
             {f(t, u)} -> Common_type<T, U>;
             {f(u, t)} -> Common_type<T, U>;
           };
  }


// -------------------------------------------------------------------------- //
// Streaming concepts                                       [concepts.stream] //
//
// The I/O streaming concepts relate types the std::istream and
// std::ostream streaming facilities. 


// A type is input streamable if it can be extracted from a formatted
// input stream derived from std::istream.
template<typename T>
  concept bool
  Input_streamable() {
    return requires(std::istream& s, T x) {
      s >> x;
    };
  }

// A type is output streamable if it can be extracted from a formatted
// output stream dervied from std::ostream.
template<typename T>
  concept bool
  Output_streamable() {
    return requires(std::ostream& s, T x) {
      s << x;
    };
  }

// A type is streamable if it is both input and output streamable.
template<typename T>
  concept bool
  Streamable() {
    return Input_streamable<T>() and Output_streamable<T>();
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

// Make iostreams have a value type.
template<typename T>
  requires Derived<T, std::ios_base>()
    struct get_value_type<T> { using type = typename T::char_type; };

template<typename T>
  using value_type = typename get_value_type<Strip<T>>::type;

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
  using difference_type = typename get_difference_type<Strip<T>>::type;

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
  using size_type = typename get_size_type<Strip<T>>::type;

} // namespace core_impl

// Size_type
template<typename T>
  using Size_type = core_impl::size_type<T>;

} // namespace origin

#endif
