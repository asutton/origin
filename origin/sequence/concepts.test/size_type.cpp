// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/ranges>

#include <forward_list>
#include <list>
#include <vector>


// True when the range R has size type T.
template<typename R, typename T>
constexpr bool Has_size_type() 
{
  return origin::Same<origin::Size_type<R>, T>();
}

using Fwd = std::forward_list<int>;
using List = std::list<int>;
using Vec = std::vector<int>;

static_assert(Has_size_type<int[1], std::size_t>(), "");
static_assert(Has_size_type<Fwd, std::size_t>(), "");
static_assert(Has_size_type<List, std::size_t>(), "");
static_assert(Has_size_type<Vec, std::size_t>(), "");

int main() { }
