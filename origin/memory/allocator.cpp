// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include "allocator.hpp"

namespace origin 
{

namespace 
{

// The global default allocator.
allocator alloc_;

} // namespace


// Returns the default allocator.
allocator& 
default_allocator() 
{ 
  return alloc_; 
}


} // namespace origin
