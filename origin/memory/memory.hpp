// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_MEMORY_MEMORY_HPP
#define ORIGIN_MEMORY_MEMORY_HPP

#include <origin/memory/allocator.hpp>

namespace origin {

// Construct an object of type `T` at address `p` with the given
// arguments. Note that this does not allocate the memory where the
// object is constructed. 
//
// Behavior is undefined if insufficient memory has not been allocated 
// for the given object.
template<typename T, typename... Args>
  inline void 
  construct(T* p, Args&&... args) { 
    return new(p) T(std::forward<Args>(args)...); 
  }

// Destroy an object of type `T` at the address `p`. Note that this
// does not release the memory of stored object.
template<typename T>
  inline void 
  destroy(T* p) { 
    p->~T(); 
  }

} // namespace origin

#endif
