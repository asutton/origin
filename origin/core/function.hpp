// Copyright (c) 2008-2014 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_CORE_FUNCTION_HPP
#define ORIGIN_CORE_FUNCTION_HPP

#include <functional>

#include <origin/core/concepts.hpp>

namespace origin {

// -------------------------------------------------------------------------- //
// Result Type                                                       [fn.result]

template<typename F, typename... Args>
  using Result_type = decltype(std::declval<F>()(std::declval<Args>()...));


// -------------------------------------------------------------------------- //
// Invoke                                                            [fn.invoke]

template<typename F>
  inline F
  Invokable(F fn) { return fn; }

template<typename R, typename T>
  inline auto
  Invokable(R T::* p) { return std::mem_fun(p); }

// The type returned by Invokable(f).
template<typename F>
  using Invokable_type = decltype(Invokable(std::declval<F>()));

// A type F is Invokable with a sequence of arguments if a value of type
// F can be converted to a callable type and called with arguments of the
// specified types.
template<typename F, typename... Args>
  concept bool Invokable() {
    return requires(F fn) { Invokable(fn); }
       and Function<Invokable_type<F>, Args...>();
  }

} // namespace origin

#endif
