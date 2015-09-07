// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_CORE_FINALLY_HPP
#define ORIGIN_CORE_FINALLY_HPP

#include <origin/core/concepts.hpp>


// The finally keyword allows the registration of a function
// to be executed at the end of the enclosing scope. This
// help simplify the definition of algorithms with multiple
// exit paths that are nonetheless required to release resources 
// prior to exit.
//
// Example:
//
//    void read(char const* path)
//    {
//      FILE* f = fopen(path, "rt");
//      finally([&f] { if (f) fclose(f); });
//      // do stuff.
//    }
//
// Regardless of how `read` exists, the file pointer is closed
// before returining.
#define finally(f) \
  auto guard__ ## __COUNTER__ = origin::make_finally(f)


namespace origin
{

// The final act class invokes its function when it destroyed. 
// `F` must be a nullary function. The return value is discarded.
//
// This class is almost never used directly. Instead, use the
// finally macro.
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
