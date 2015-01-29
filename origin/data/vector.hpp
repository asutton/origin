// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_CORE_DATA_HPP
#define ORIGIN_CORE_DATA_HPP

#include <origin/core/concepts.hpp>
#include <origin/memory/memory.hpp>
#include <origin/sequence/algorithm.hpp>

namespace origin {

namespace vector_impl {

template<Object_type T>
  struct vector_base {
    vector_base();
    vector_base(vector_base&&);
    vector_base(const vector_base&) = delete;
    vector_base(allocator*);
    vector_base(std::size_t);
    vector_base(std::size_t, allocator*);
    ~vector_base();

    T* allocate(std::size_t);
    void deallocate(T*);

    allocator* alloc;
    T* first;
    T* last;
    T* limit;
  };

} // namespace vector_impl


// A vector is a container that stores a linear arrangement of
// elements.
//
// TODO: Write better documentation.
//
// TODO: Wrap iterators.
template<Object_type T>
  class vector : vector_impl::vector_base<T> {
    vector();
    vector(vector&&);
    vector(const vector&) requires Copy_constructible<T>();
    ~vector();

    vector(allocator*);

    // Observers
    std::size_t size() const;
    bool is_empty() const;

    // Iterators
    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;
  };

} // namespace origin

#include <origin/data/vector.ipp>

#endif
