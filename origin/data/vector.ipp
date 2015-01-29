// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

namespace origin {

namespace vector_impl {

template<Object_type T>
  inline
  vector_base<T>::vector_base(allocator* a)
    : alloc(a), first(), last(), limit()
  { }

template<Object_type T>
  inline
  vector_base<T>::vector_base()
    : vector_base(&default_allocator())
  { }

// TODO: Replace the calls to std::exchange with origin::exchange.
template<Object_type T>
  inline
  vector_base<T>::vector_base(vector_base&& x)
    : alloc(default_allocator)
    , first(std::exchange(x.first, nullptr))
    , last(std::exchange(x.last, nullptr))
    , limit(std::exchange(x.limit, nullptr))
  { }

template<Object_type T>
  inline
  vector_base<T>::vector_base(std::size_t n, allocator* a) 
    : alloc(a), first(allocate(n)), last(first + n), limit(last)
  { }

template<Object_type T>
  inline
  vector_base<T>::vector_base(std::size_t n)
    : vector_base(n, &default_allocator())
  { }

template<Object_type T>
  inline
  vector_base<T>::~vector_base() {
    deallocate(first);
  }

template<Object_type T>
  inline T*
  vector_base<T>::allocate(std::size_t n) { return alloc->allocate(n); }

template<Object_type T>
  inline void
  vector_base<T>::deallocate(T* p) { alloc->deallocate(p); }

} // namespace vector_impl


template<Object_type T>
  inline
  vector<T>::vector()
    : vector_impl::vector_base<T>()
  { }

template<Object_type T>
  inline 
  vector<T>::vector(const vector& v) requires Copy_constructible<T>()
    : vector_impl::vector_base<T>(v.size())
  { uninitialized_copy(v, *this); }

// Note that T is not required to be Move_constructible. The
// move constructor only exchanges pointers; it does not exchange
// the values of elements.
template<Object_type T>
  inline
  vector<T>::vector(vector&& v)
    : vector_impl::vector_base<T>(std::move(v))
  { }

template<Object_type T>
  inline T*
  vector<T>::begin() { return this->first; }

template<Object_type T>
  inline T*
  vector<T>::end() { return this->last; }

template<Object_type T>
  inline const T*
  vector<T>::begin() const { return this->first; }

template<Object_type T>
  inline const T*
  vector<T>::end() const { return this->last; }


} // namespace origin
