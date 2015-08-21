// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_CORE_FINALLY_HPP
#define ORIGIN_CORE_FINALLY_HPP

#include <origin/core/concepts.hpp>


#define finally(f) auto guard__ ## __COUNTER__ = make_finally(f);

namespace origin
{

// The final act class invokes its function when it
// destroyed. `F` must be a nullary function. The 
// return value is discarded.
template<Function F>
struct final_act
{
  final_act(F f)
    : fn(f)
  { }

  ~final_act() { fn(); }

  F fn;
};


template<Function F>
inline final_act<F>
make_finally(F fn)
{
  return final_act<F>(fn);
}


} // namespace origin


#endif
