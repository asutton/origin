// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_MEMORY_ALLOCATOR_HPP
#define ORIGIN_MEMORY_ALLOCATOR_HPP

#include <origin/core/concepts.hpp>

namespace origin {

// A type `A` is an allocator when it provides the methods necessary to
// allocate and deallocate memory. Allocators are semiregular types;
// they are copyable, but are not required to be equality comparable.
template<typename A>
  concept bool Allocator() {
    return Semiregular<A>() and requires(A a, std::size_t n, void* p) {
      { a.allocate(n) } -> void*;
      { a.deallocate(p, n) } -> void;
    };
  }

namespace allocator_impl {

struct interface {
  virtual ~interface() = default;
  
  // Semiregular
  virtual interface* copy() = 0;
  
  // Allocator
  virtual void* allocate(int) = 0;
  virtual void deallocate(void*, int) = 0;
};

template<Allocator A>
  struct binder : interface {
    binder(const A& a) : alloc(a) { }

    virtual binder* 
    copy() { return new binder(alloc); }

    virtual void* 
    allocate(int n) { return alloc.allocate(n); }
    
    virtual void 
    deallocate(void* p, int n) { alloc.deallocate(p, n); }

    A alloc;
  };

} // namespace memory_impl


// The allocator class defines the runtime version of the Allocator
// concept.
//
// TODO: Document this.
//
// TODO: In full generality, the allocator should take an allocator
// since it dyanamically allocates memory.
class allocator {
public:
  template<Allocator A>
    allocator(const A&);

  allocator(const allocator&);
  ~allocator();

  void* allocate(int);
  void deallocate(void* p, int n = 0);

private:
  allocator_impl::interface* impl_;
};


template<Allocator A>
  inline
  allocator::allocator(const A& a)
    : impl_(new allocator_impl::binder<A>(a)) { }

inline
allocator::allocator(const allocator& x)
  : impl_(x.impl_->copy()) { }

inline
allocator::~allocator() { delete impl_; }

inline void*
allocator::allocate(int n) { return impl_->allocate(n); }

inline void
allocator::deallocate(void* p, int n) { return impl_->deallocate(p, n); }

} // namespace

#endif
