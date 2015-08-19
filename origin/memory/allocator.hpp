// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_MEMORY_ALLOCATOR_HPP
#define ORIGIN_MEMORY_ALLOCATOR_HPP

#include <origin/generic.hpp>

#include <climits>
#include <memory>

namespace origin 
{


// ---------------------------------------------------------------------------//
// Allocator concepts                                                [mem.alloc]
//
// TODO: There is a concept of a non-deallocating allocator.
// Should that be separate, or should deallocate() just be
// a no-op.


// The allocator concept defines the required properties of
// a facility that can allocate and deallocate memory.
template<typename A>
concept bool Allocator()
{
  return requires (A a, int n, void* p)
  {
    { a.allocate(n) } -> void*;
    { a.deallocate(p) };
  };
}


// ---------------------------------------------------------------------------//
// Default allocator                                         [mem.alloc.default]

// An allocator is a resource type that is responsible for the acquisition
// and release of memory. It is an abstract base class.
//
// TODO: Write better docs.
//
// TODO: Look at recent allocator specifications to determine what
// sets of operations are actually being required.
struct allocator 
{
  virtual ~allocator() { }
  virtual void* allocate(int);
  virtual void deallocate(void*, int);
};


inline void*
allocator::allocate(int n) 
{ 
  return ::operator new(n); 
}


inline void
allocator::deallocate(void* p, int) 
{ 
  ::operator delete(p); 
}


allocator& default_allocator();


// ---------------------------------------------------------------------------//
// Adaptors                                                  [mem.alloc.default]


// The std allocator is a wrapper around an origin Allocator
// tha satisfies the requirements of a standard allocator.
template<Object_type T, Allocator A>
struct std_allocator
{
  using value_type      = T;
  using pointer         = T*;
  using const_pointer   = T const*;
  using reference       = T&;
  using const_reference = const T&;
  using size_type       = unsigned;
  using difference_type = int;
  
  using propagate_on_container_move_assignment = std::true_type;

  template<typename U>
    using rebind = std_allocator<U, A>;

  static T*       address(T&);
  static T const* address(T const&);

  T*   allocate(int, void* = nullptr);
  void deallocate(void*, int);

  static int max_size();

  template<typename... Args>
    requires Constructible<T, Args...>()
  static void construct(T*, Args&&...);

  template<Destructible U>
  static void destroy(U*);

  A* alloc_;
};


template<Object_type T, Allocator A>
inline T*
std_allocator<T, A>::address(T& t)
{ 
  return std::addressof(t); 
}


template<Object_type T, Allocator A>
inline T const* 
std_allocator<T, A>::address(T const& t)
{ 
  return std::addressof(t); 
}


template<Object_type T, Allocator A>
inline T*
std_allocator<T, A>::allocate(int n, void* hint)
{
  return reinterpret_cast<T*>(alloc_->allocate(n * sizeof(T), hint));
}


template<Object_type T, Allocator A>
inline void 
std_allocator<T, A>::deallocate(void* p, int n)
{
  alloc_->deallocate(p, n);
}


template<Object_type T, Allocator A>
inline int 
std_allocator<T, A>::max_size()
{
  return INT_MAX / sizeof(T);
}


template<Object_type T, Allocator A>
template<typename... Args>
  requires Constructible<T, Args...>()
inline void 
std_allocator<T, A>::construct(T* p, Args&&... args)
{
  ::new (p) T(std::forward<Args>(args)...);
}


template<Object_type T, Allocator A>
template<Destructible U>
inline void 
std_allocator<T, A>::destroy(U* p)
{
  p->~U();
}



} // namespace


#endif
