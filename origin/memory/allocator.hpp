// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_MEMORY_ALLOCATOR_HPP
#define ORIGIN_MEMORY_ALLOCATOR_HPP

#include <origin/core/concepts.hpp>

#include <memory>

namespace origin {

// ---------------------------------------------------------------------------//
// Allocator 

// An allocator is a resource type that is responsible for the acquisition
// and release of memory. It is an abstract base class.
//
// TODO: Write better docs.
//
// TODO: Look at recent allocator specifications to determine what
// sets of operations are actually being required.
struct allocator {
  virtual ~allocator();
  virtual void* allocate(int);
  virtual void deallocate(void*);
};

allocator& default_allocator();

} // namespace

#include <origin/memory/allocator.ipp>

#endif
