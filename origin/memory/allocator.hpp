// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_MEMORY_ALLOCATOR_HPP
#define ORIGIN_MEMORY_ALLOCATOR_HPP

#include <origin/core/concepts.hpp>

#include <memory>

namespace origin {

// ---------------------------------------------------------------------------//
// Abstract allocator 

// An allocator is a resource type that is responsible for the acquisition
// and release of memory. It is an abstract base class.
//
// TODO: Write better docs.
//
// TODO: Look at recent allocator specifications to determine what
// sets of operations are actually being required.
struct allocator {
  virtual ~allocator();
  virtual void* allocate(int) = 0;
  virtual void deallocate(void*) = 0;
};

allocator& default_allocator();


// ---------------------------------------------------------------------------//
// New allocator

// The new allocator acquires memory using the `new` operator
// and releases it using the `delete` operator.
//
// TODO: find a better name for this?
struct new_allocator : allocator {
  void* allocate(int);
  void deallocate(void*);
};

} // namespace

#include <origin/memory/allocator.ipp>

#endif
