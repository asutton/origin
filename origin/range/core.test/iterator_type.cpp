// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/range.hpp>

#include <iostream>
#include <forward_list>
#include <list>
#include <vector>


// True when the range R has iterator type T.
template<typename R, typename T>
constexpr bool Has_iterator_type() 
{
  return origin::Same<origin::Iterator_type<R>, T>();
}

using Fwd = std::forward_list<int>;
using List = std::list<int>;
using Vec = std::vector<int>;

static_assert(Has_iterator_type<int[1], int*>(), "");
static_assert(Has_iterator_type<const int[1], const int*>(), "");
static_assert(Has_iterator_type<Fwd, Fwd::iterator>(), "");
static_assert(Has_iterator_type<const Fwd, Fwd::const_iterator>(), "");
static_assert(Has_iterator_type<List, List::iterator>(), "");
static_assert(Has_iterator_type<const List, List::const_iterator>(), "");
static_assert(Has_iterator_type<Vec, Vec::iterator>(), "");
static_assert(Has_iterator_type<const Vec, Vec::const_iterator>(), "");

int main() { }
