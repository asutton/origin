// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_CORE_DATA_HPP
#define ORIGIN_CORE_DATA_HPP

#include <origin/memory.hpp>
#include <origin/iterator.hpp>
#include <origin/range.hpp>

#include <vector>


namespace origin
{

// The vector class template defines a resizeable, dynamically
// allocated sequence of elements.
//
// Elements are allocated contiguously.
template<Destructible T, Allocator A = allocator>
struct vector : private std::vector<T, std_allocator<T, A>>
{
private:
  using base_type = std::vector<T, std_allocator<T, A>>;
  using alloc_type = std_allocator<T, A>;
public:
  using value_type     = T;
  using iterator       = typename base_type::iterator;
  using const_iterator = typename base_type::const_iterator;

  vector();
  explicit vector(A&);

  vector(vector&&) requires Move_constructible<T>();
  vector(vector&&, A&) requires Move_constructible<T>();
  vector(vector const&) requires Copy_constructible<T>();
  vector(vector const&, A&) requires Copy_constructible<T>();

  template<Input_iterator I>
    requires Constructible<T, Value_type<I>>()
   vector(I, I);

  template<Input_iterator I>
    requires Constructible<T, Value_type<I>>()
   vector(I, I, A&);

  template<Input_range R>
    requires Constructible<T, Value_type<R>>()
  vector(R);

  template<Input_range R>
    requires Constructible<T, Value_type<R>>()
  vector(R, A&);

  template<typename U>
    requires Constructible<T, U>()
  vector(std::initializer_list<U>);

  template<typename U>
    requires Constructible<T, U>()
  vector(std::initializer_list<U>, A&);

  vector& operator=(vector&&) requires Movable<T>();
  vector& operator=(vector const&) requires Copyable<T>();

  // Allocator
  A& allocator();

  // Size
  bool is_empty() const;
  int size() const;
  int max_size() const;
  void resize(int) requires Default_constructible<T>();

  // Capacity
  int capacity() const;
  void reserve(int) requires Move_constructible<T>();
  void collapse() requires Move_constructible<T>();

  // Data access
  T&       operator[](int n);
  T const& operator[](int n) const;

  T&       front();
  T const& front() const;

  T&       back();
  T const& back() const;

  T*       data();
  T const* data() const;

  // Insertion
  iterator insert(const_iterator, T&&) requires Move_constructible<T>();
  iterator insert(const_iterator, T const&) requires Copy_constructible<T>();
  iterator insert(const_iterator, int n, T const&) requires Copy_constructible<T>();

  template<Input_iterator I>
    requires Constructible<T, Value_type<I>>()
  iterator insert(const_iterator, I, I);

  template<Input_range R>
    requires Constructible<T, Value_type<R>>()
  iterator insert(const_iterator, R);

  template<typename U>
    requires Constructible<T, U>()
  iterator insert(const_iterator, std::initializer_list<U>);

  template<typename... Args>
    requires Constructible<T, Args...>()
  iterator emplace(const_iterator, Args&&... args);

  // Erase
  iterator erase(const_iterator) requires Movable<T>();
  iterator erase(const_iterator, const_iterator) requires Movable<T>();
  void clear();

  // Push/pop
  void push_back(T&&) requires Move_constructible<T>();
  void push_back(T const&) requires Copy_constructible<T>();

  template<typename... Args>
    requires Constructible<T, Args...>()
  void emplace_back(Args&&...);

  void pop_back();


  // Iteators
  iterator       begin();
  const_iterator begin() const;

  iterator       end();
  const_iterator end() const;

  const_iterator cbegin() const;
  const_iterator cend() const;
};


template<Destructible T, Allocator A>
inline
vector<T, A>::vector()
  : base_type(alloc_type(default_allocator()))
{ }


template<Destructible T, Allocator A>
inline
vector<T, A>::vector(A& alloc)
  : base_type(alloc_type(alloc))
{ }


template<Destructible T, Allocator A>
inline
vector<T, A>::vector(vector&& v) requires Move_constructible<T>()
  : base_type(std::move(v))
{ }


template<Destructible T, Allocator A>
inline
vector<T, A>::vector(vector&& v, A& alloc) requires Move_constructible<T>()
  : base_type(std::move(v), alloc_type(alloc))
{ }


template<Destructible T, Allocator A>
inline
vector<T, A>::vector(vector const& v) requires Copy_constructible<T>()
  : base_type(v)
{ }


template<Destructible T, Allocator A>
inline
vector<T, A>::vector(vector const& v, A& alloc) requires Copy_constructible<T>()
  : base_type(v, alloc_type(alloc))
{ }


template<Destructible T, Allocator A>
template<Input_iterator I>
  requires Constructible<T, Value_type<I>>()
vector<T, A>::vector(I first, I last)
  : base_type(first, last)
{ }


template<Destructible T, Allocator A>
template<Input_iterator I>
  requires Constructible<T, Value_type<I>>()
vector<T, A>::vector(I first, I last, A& alloc)
  : base_type(first, last, alloc_type(alloc))
{ }


template<Destructible T, Allocator A>
template<Input_range R>
  requires Constructible<T, Value_type<R>>()
vector<T, A>::vector(R range)
  : base_type(std_begin(range), std_end(range))
{ }


template<Destructible T, Allocator A>
template<Input_range R>
  requires Constructible<T, Value_type<R>>()
vector<T, A>::vector(R range, A& alloc)
  : base_type(std_begin(range), std_end(range), alloc_type(alloc))
{ }


template<Destructible T, Allocator A>
template<typename U>
  requires Constructible<T, U>()
vector<T, A>::vector(std::initializer_list<U> list)
  : base_type(list)
{ }


template<Destructible T, Allocator A>
template<typename U>
  requires Constructible<T, U>()
vector<T, A>::vector(std::initializer_list<U> list, A& alloc)
  : base_type(list, alloc_type(alloc))
{ }


template<Destructible T, Allocator A>
inline vector<T, A>&
vector<T, A>::operator=(vector&& v) requires Movable<T>()
{
  base_type::operator=(std::move(v));
  return *this;
}


template<Destructible T, Allocator A>
inline vector<T, A>&
vector<T, A>::operator=(vector const& v) requires Copyable<T>()
{
  base_type::operator=(v);
  return *this;
}

// Size

template<Destructible T, Allocator A>
inline bool
vector<T, A>::is_empty() const
{
  return base_type::is_empty();
}


template<Destructible T, Allocator A>
inline int
vector<T, A>::size() const
{
  return base_type::size();
}


template<Destructible T, Allocator A>
inline int
vector<T, A>::max_size() const
{
  return base_type::max_size();
}


template<Destructible T, Allocator A>
inline void
vector<T, A>::resize(int n) requires Default_constructible<T>()
{
  base_type::resize(n);
}


// Capacity

template<Destructible T, Allocator A>
inline int
vector<T, A>::capacity() const
{
  return base_type::capacity();
}

template<Destructible T, Allocator A>
inline void
vector<T, A>::reserve(int n) requires Move_constructible<T>()
{
  base_type::reserve(n);
}


template<Destructible T, Allocator A>
inline void
vector<T, A>::collapse() requires Move_constructible<T>()
{
  base_type::collapse();
}

// Data access

template<Destructible T, Allocator A>
inline T&
vector<T, A>::operator[](int n)
{
  return base_type::operator[](n);
}


template<Destructible T, Allocator A>
inline T const&
vector<T, A>::operator[](int n) const
{
  return base_type::operator[](n);
}


template<Destructible T, Allocator A>
inline T&
vector<T, A>::front()
{
  return base_type::front();
}


template<Destructible T, Allocator A>
inline T const&
vector<T, A>::front() const
{
  return base_type::front();
}


template<Destructible T, Allocator A>
inline T&
vector<T, A>::back()
{
  return base_type::back();
}


template<Destructible T, Allocator A>
inline T const&
vector<T, A>::back() const
{
  return base_type::back();
}

template<Destructible T, Allocator A>
inline T*
vector<T, A>::data()
{
  return base_type::data();
}

template<Destructible T, Allocator A>
inline T const*
vector<T, A>::data() const
{
  return base_type::data();
}

// Insert

template<Destructible T, Allocator A>
inline typename vector<T, A>::iterator
vector<T, A>::insert(const_iterator pos, T&& t) requires Move_constructible<T>()
{
  return base_type::insert(pos, std::move(t));
}


template<Destructible T, Allocator A>
inline typename vector<T, A>::iterator
vector<T, A>::insert(const_iterator i, T const& t) requires Copy_constructible<T>()
{
  return base_type::insert(i, std::move(t));
}


template<Destructible T, Allocator A>
inline typename vector<T, A>::iterator
vector<T, A>::insert(const_iterator i, int n, T const& t) requires Copy_constructible<T>()
{
  return base_type::insert(i, n, t);
}


template<Destructible T, Allocator A>
template<Input_iterator I>
  requires Constructible<T, Value_type<I>>()
inline auto
vector<T, A>::insert(const_iterator pos, I first, I last) -> iterator
{
  return base_type::insert(pos, first, last);
}


template<Destructible T, Allocator A>
template<Input_range R>
  requires Constructible<T, Value_type<R>>()
inline auto
vector<T, A>::insert(const_iterator pos, R range) -> iterator
{
  return base_type::insert(std_begin(range), std_end(range));
}


template<Destructible T, Allocator A>
template<typename U>
  requires Constructible<T, U>()
inline auto
vector<T, A>::insert(const_iterator pos, std::initializer_list<U> list) -> iterator
{
  return base_type::insert(pos, list);
}


template<Destructible T, Allocator A>
template<typename... Args>
  requires Constructible<T, Args...>()
inline auto
vector<T, A>::emplace(const_iterator pos, Args&&... args) -> iterator
{
  return base_type::emplace(pos, std::forward<Args>(args)...);
}

// Erase

template<Destructible T, Allocator A>
inline typename vector<T, A>::iterator
vector<T, A>::erase(const_iterator pos) requires Movable<T>()
{
  return base_type::erase(pos);
}


template<Destructible T, Allocator A>
inline typename vector<T, A>::iterator
vector<T, A>::erase(const_iterator first, const_iterator last) requires Movable<T>()
{
  return base_type::erase(first, last);
}


template<Destructible T, Allocator A>
inline void
vector<T, A>::clear()
{
  return base_type::clear();
}

// Push/pop

template<Destructible T, Allocator A>
inline void
vector<T, A>::push_back(T&& t) requires Move_constructible<T>()
{
  base_type::push_back(std::move(t));
}


template<Destructible T, Allocator A>
inline void
vector<T, A>::push_back(T const& t) requires Copy_constructible<T>()
{
  base_type::push_back(t);
}


template<Destructible T, Allocator A>
template<typename... Args>
  requires Constructible<T, Args...>()
inline void
vector<T, A>::emplace_back(Args&&... args)
{
  base_type::emplace_back(std::forward<Args>(args)...);
}


template<Destructible T, Allocator A>
inline void
vector<T, A>::pop_back()
{
  base_type::pop_back();
}

// Iterators

template<Destructible T, Allocator A>
inline auto
vector<T, A>::begin() -> iterator
{
  return base_type::begin();
}


template<Destructible T, Allocator A>
inline auto
vector<T, A>::end() -> iterator
{
  return base_type::end();
}


template<Destructible T, Allocator A>
inline auto
vector<T, A>::begin() const -> const_iterator
{
  return base_type::begin();
}


template<Destructible T, Allocator A>
inline auto
vector<T, A>::end() const -> const_iterator
{
  return base_type::end();
}

template<Destructible T, Allocator A>
inline auto
vector<T, A>::cbegin() const -> const_iterator
{
  return base_type::cbegin();
}


template<Destructible T, Allocator A>
inline auto
vector<T, A>::cend() const -> const_iterator
{
  return base_type::cend();
}


} // namespace origin


#endif
