// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

namespace origin 
{

inline
allocator::~allocator() 
{ }


inline void*
allocator::allocate(int n) 
{ 
  return ::operator new(n); 
}


inline void
allocator::deallocate(void* p) 
{ 
  ::operator delete(p); 
}


} // namespace
