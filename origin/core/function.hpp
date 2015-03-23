// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_CORE_FUNCTION_HPP
#define ORIGIN_CORE_FUNCTION_HPP

#include <functional>

#include <origin/core/concepts.hpp>

namespace origin {

// -------------------------------------------------------------------------- //
// Function Objects                                                  [fn.object]
//
// TODO: Write my own function objects.

inline std::equal_to<>      eq() { return {}; }
inline std::not_equal_to<>  ne() { return {}; }
inline std::less<>          lt() { return {}; }
inline std::greater<>       gt() { return {}; }
inline std::less_equal<>    ge() { return {}; }
inline std::greater_equal<> le() { return {}; }


// -------------------------------------------------------------------------- //
// Result Type                                                       [fn.result]

template<typename F, typename... Args>
  using Result_type = decltype(std::declval<F>()(std::declval<Args>()...));


// -------------------------------------------------------------------------- //
// Invoke                                                         [fn.invoke] //


namespace core
{

// Returns the object responsible for invoking a function of
// type F. For member functions, this returns a mem_fn object
// that can be used like a regular function.
template<typename F>
inline decltype(auto)
invoker(F&& fn) { return fn; }

template<typename R, typename T>
inline auto
invoker(R T::* p) { return std::mem_fn(p); }

} // namespace core


// Given an invokable type F, this yields the type 
// resposible for invoking it as a free function.
template<typename F>
using Invokable_type = decltype(core::invoker(std::declval<F>()));


template<typename F, typename... Args>
concept bool 
Invokable() 
{
  return requires(F fn, Args... args) {
    core::invoker(fn);
  }
  && Function<Invokable_type<F>, Args...>();
}

// A type P is an invokable predicate if it is Invokable and its result
// type is convertible to bool.
//
// TODO: It would be nice to write this in terms of Invokable in orer to
// guarantee refinement, but as of 13.04.2014 there appears to be a
// bug related to pack expansion that is preventing it.
template<typename P, typename... Args>
  concept bool Invokable_predicate() {
    return requires(P pred, Args... args) {
      {Invokable(pred)(args...)} -> bool;
    };
  }

} // namespace origin

#endif
