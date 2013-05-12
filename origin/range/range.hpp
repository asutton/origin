// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_RANGE_RANGE_HPP
#define ORIGIN_RANGE_RANGE_HPP

#include "concepts.hpp"

namespace origin {

// -------------------------------------------------------------------------- //
// Range size
//
// Returns the size of the range, the number of increments required
// to move from the beginning to the end.

template<typename R>
  requires Range<R>()
    inline Size_type<R> size(R&& range)
    {
      using std::begin;
      using std::end;
      return std::distance(begin(range), end(range));
    }


// -------------------------------------------------------------------------- //
// Bounded Range
//
// The bounded range class encapsulates an iterator range bounded 
// by a pair of iterators.
template <typename I>
  requires Iterator<I>()
    class bounded_range
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
