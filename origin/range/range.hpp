// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_RANGE_RANGE_HPP
#define ORIGIN_RANGE_RANGE_HPP

#include <origin/range/core.hpp>


namespace origin 
{


// -------------------------------------------------------------------------- //
// Begin and end                                                      [range.be]
//
// In many cases (i.e., constructors), we want to invoke begin and 
// end so that ADL finds appropriate overloads. However, that cannot
// be done within a member-initializer-list, unless the enclosing
// namespace brings the names std::begin and std::end into scope.
//
// The std_begin and std_end functions can be used as a workaround.

template<typename T>
inline decltype(auto) 
std_begin(T&& t)
{
  using std::begin;
  return begin(std::forward<T>(t));
}


template<typename T>
inline decltype(auto) 
std_end(T&& t)
{
  using std::end;
  return end(std::forward<T>(t));
}



// -------------------------------------------------------------------------- //
// Range size
//
// Returns the size of the range, the number of increments required
// to move from the beginning to the end.

template<Range R>
inline Size_type<R> 
size(R&& range) 
{
  using std::begin;
  using std::end;
  return std::distance(begin(range), end(range));
}


// -------------------------------------------------------------------------- //
// Range base
//
// The range base class provides appropriate typedefs for the value and
// size type for range adaptors.
template<Iterator I>
struct range_base 
{
  using value_type = Value_type<I>;
  using size_type = Make_unsigned<Difference_type<I>>;
};



// -------------------------------------------------------------------------- //
// Bounded Range
//
// The bounded range class encapsulates an iterator range bounded 
// by a pair of iterators.
template<Iterator I>
class bounded_range : public range_base<I> 
{
public:
  using iterator = I;

  // A default-constructed range is empty.
  bounded_range() 
    : first(), last(first)
  { }

  // Initialize the range with a lower bound, f, and an upper
  // bound, l.
  bounded_range(I f, I l)
    : first(f), last(l)
  { }
  
  // Iterators
  iterator begin() const { return first; }
  iterator end() const { return last; }
  
private:
  I first;
  I last;
};


} // namespace origin


#endif
