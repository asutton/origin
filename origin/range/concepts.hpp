// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_RANGE_CONCEPTS_HPP
#define ORIGIN_RANGE_CONCEPTS_HPP

#include <origin/iterator/concepts.hpp>

namespace origin {

// Range
template<typename R>
  concept bool Range()
  {
    return requires (R& range) {
      std::begin(range);
      std::end(range);
      requires Same<decltype(std::begin(range)), decltype(std::end(range))>();
    };
  }

// Iterator type
template<typename R>
  using Iterator_type = decltype(std::begin(std::declval<R&>()));

// Input_range
template<typename R>
  concept bool Input_range()
  {
    return Range<R>() && Input_iterator<Iterator_type<R>>();
  }

// Output_range
template<typename R, typename T>
  concept bool Output_range()
  {
    return Range<R>() && Output_iterator<Iterator_type<R>, T>();
  }

// Forward_range
template<typename R>
  concept bool Forward_range()
  {
    return Range<R>() && Forward_iterator<Iterator_type<R>>();
  }

// Bidirectional_range
template<typename R>
  concept bool Bidirectional_range()
  {
    return Range<R>() && Bidirectional_iterator<Iterator_type<R>>();
  }

// Random_access_range
template<typename R>
  concept bool Random_access_range()
  {
    return Range<R>() && Random_access_iterator<Iterator_type<R>>();
  }

} // namespace origin

#endif
