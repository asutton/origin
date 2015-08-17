// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_CORE_FUNCTION_HPP
#define ORIGIN_CORE_FUNCTION_HPP

#include <origin/concepts>

#include <functional>


namespace origin {

// -------------------------------------------------------------------------- //
// Function Objects                                               [fn.object] //
//
// TODO: Finish implementing all of the function objects.

// Equal to function objects.

// A relation that compares two objects for equality.
// When the template argument `T` is `void`, the
// argument types of the relation may differ.
template<typename T = void>
struct equal_to;

template<>
struct equal_to<void>
{
  template<typename T, typename U>
    requires Equality_comparable<T, U>()
  bool operator()(T const& a, T const& b) const
  {
    return a == b;
  }
};

template<Equality_comparable T>
struct equal_to<T>
{
  bool operator()(T const& a, T const& b) const
  {
    return a == b;
  }
};


// A unary predicate that compares that determines if a
// fixed value is less than a given argument. Note that
// the argument type may differ from that of the fixed
// value.
//
// Note that the fixed value is copied upon initialization.
// However, this can be safely instantiated over a reference
// type.
//
// TODO: What is the requirement for T? It's either an
// object or a reference, but not an array.
template<typename T>
struct equal_to_value
{
  equal_to_value(T const& t)
    : t(t)
  { }

  template<typename U>
    requires Equality_comparable<T, U>()
  bool operator()(U const& u) const
  {
    return t == u;
  }

  T t; 
};


// Less than function objects.

// A relation that compares determines if one value is
// less than another.
template<typename T = void>
struct less_than;

template<>
struct less_than<void>
{
  template<typename T, typename U>
    requires Equality_comparable<T, U>()
  bool operator()(T const& a, T const& b) const
  {
    return a < b;
  }
};

template<Equality_comparable T>
struct less_than<T>
{
  bool operator()(T const& a, T const& b) const
  {
    return a < b;
  }
};


// A unary predicate that compares that determines if a
// fixed value is less than a given argument. Note that
// the argument type may differ from that of the fixed
// value.
//
// The fixed value is copied upon initialization. However, 
// this can be safely instantiated over a reference type.
//
// TODO: What is the requirement for T? It's either an
// object or a reference, but not an array.
template<typename T>
struct less_than_value
{
  less_than_value(T const& t)
    : t(t)
  { }

  template<typename U>
    requires Equality_comparable<T, U>()
  bool operator()(U const& u) const
  {
    return t == u;
  }

  T t; 
};


// -------------------------------------------------------------------------- //
// Function object constructors                                   [fn.object] //
//
// Utility functions used to construct function objects.


// Returns a relation that compares two values of potentially 
// different type for equality.
inline equal_to<>
eq() 
{ 
  return {}; 
}

// Returns a unary predicate that compares a value to `t`.
template<typename T>
inline equal_to_value<T>
eq(T const& t)
{
  return equal_to_value<T>(t);
}

// Returns a function that compares two vlaues of potentially
// different type for inequality.
inline std::not_equal_to<>  
ne() 
{ 
  return {}; 
}


// TODO: Implement me.
template<typename T>
inline void
ne(T const&) = delete;


// Returns a relation that compares two values of possibly
// different type. That relation returns true whenever the left
// operand is less than the right.
inline less_than<>
lt() 
{ 
  return {}; 
}


// Returns a unary predicate that compares arguments
// against a fixed value. The argument type and the
// type of the fixed value may differ. The predicate
// returns `true` whenever the fixed value is less than
// the argument.
template<typename T>
inline less_than_value<T>
lt(T const& t)
{
  return less_than_value<T>(t);
}


// Returns a relation that compares two values of possibly
// different type. That relation returns true whenever the left
// operand is greater than the right.
inline std::greater<>
gt() 
{ 
  return {}; 
}


// TODO: Implement me.
template<typename T>
inline void
gt(T const&) = delete;


// Returns a relation that compares two values of possibly
// different type. That relation returns true whenever the left
// operand is less than or equal to the right.
inline std::less_equal<>
le() 
{ 
  return {}; 
}

// TODO: Implement me.
template<typename T>
inline void
le(T const&) = delete;


// Returns a relation that compares two values of possibly
// different type. That relation returns true whenever the left
// operand is greater than or equal to the right.
inline std::greater_equal<> 
ge() 
{ 
  return {}; 
}


// TODO: Implement me.
template<typename T>
inline void
ge(T const&) = delete;


// -------------------------------------------------------------------------- //
// Result Type                                                    [fn.result] //

// The result type alias yields the result of applying
// a function of type `F` to a sequence of arguments
// whose types are given by the template argument pack 
// `...Args`.
template<typename F, typename... Args>
  requires Function<F, Args...>()
using Result_type = decltype(std::declval<F>()(std::declval<Args>()...));


// -------------------------------------------------------------------------- //
// Invoke                                                         [fn.invoke] //
//

// The `make_invokable()` function returns the object responsible 
// for invoking a function of type `F`. For member functions, this 
// returns a `mem_fn` object that can be used like a regular function.
//
// TODO: Adapt other kinds of types using make_invokable?
template<typename F>
inline decltype(auto)
make_invokable(F&& fn) { return fn; }


// Adaptor for member functions.
template<typename R, typename T>
inline auto
make_invokable(R T::* p) { return std::mem_fn(p); }


// A type `F` is invokable for a sequence of arguments `Args...` if
// an object f of type F can be transformed into a callable object 
// `g` such that `g(args...)` is well-formed.
//
// This is the case when make_invokable(f) is defined.
template<typename F, typename... Args>
concept bool 
Invokable() 
{
  return requires(F fn, Args... args) 
  {
    make_invokable(decay(fn))(args...);
  };
}


// A type P is an invokable predicate if it is Invokable and its result
// type is convertible to `bool`.
//
// TODO: It would be nice to write this in terms of Invokable 
// in order to guarantee refinement, but it's not obvious if
// that's required.
template<typename P, typename... Args>
concept bool 
Invokable_predicate() 
{
  return requires(P pred, Args... args) 
  {
    { make_invokable(decay(pred))(args...) } -> bool;
  };
}


} // namespace origin

#endif
