// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_ALGORITHM_COPY_HPP
#define ORIGIN_ALGORITHM_COPY_HPP

#include <origin/algorithm/concepts.hpp>

#include <algorithm>


namespace origin 
{

template<Input_iterator I, Output_iterator<Value_type<I>> O>
O 
copy(I first, I last, O out) 
{
  while (first != last) {
    *out = *first;
    ++first;
    ++out;
  }
  return out;
}


template<Input_range R1, Output_range<Value_type<R1>> R2>
Iterator_type<R2>
copy(R1&& in, R2&& out) 
{
  using std::begin;
  using std::end;
  return copy(begin(in), end(in), begin(out));
}


} // namesapce origin


#endif
