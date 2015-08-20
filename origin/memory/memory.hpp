// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_MEMORY_MEMORY_HPP
#define ORIGIN_MEMORY_MEMORY_HPP

#include <origin/generic.hpp>


namespace origin 
{


// Construct an object of type `T` at address `p` with the given
// arguments. Note that this does not allocate the memory where the
// object is constructed. 
//
// Behavior is undefined if insufficient memory has not been allocated 
// for the given object.
template<typename T, typename... Args>
  requires Constructible<T, Args...>()
inline void 
construct(T* p, Args&&... args) 
{ 
  return new(p) T(std::forward<Args>(args)...); 
}


// Destroy an object of type `T` at the address `p`. Note that this
// does not release the memory of stored object.
template<Destructible T>
inline void 
destroy(T* p) 
{ 
  p->~T(); 
}


} // namespace origin


#endif
