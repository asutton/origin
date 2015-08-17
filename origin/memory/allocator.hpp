// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_MEMORY_ALLOCATOR_HPP
#define ORIGIN_MEMORY_ALLOCATOR_HPP

#include <memory>

namespace origin 
{

// ---------------------------------------------------------------------------//
// Allocator 

// An allocator is a resource type that is responsible for the acquisition
// and release of memory. It is an abstract base class.
//
// TODO: Write better docs.
//
// TODO: Look at recent allocator specifications to determine what
// sets of operations are actually being required.
struct allocator 
{
  virtual ~allocator();
  virtual void* allocate(int);
  virtual void deallocate(void*);
};

allocator& default_allocator();


} // namespace


#include <origin/memory/allocator.ipp>


#endif
