// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/ranges>

#include <forward_list>
#include <list>
#include <vector>


// True when the range R has size type T.
template<typename R, typename T>
constexpr bool Has_value_type() 
{
  return origin::Same<origin::Value_type<R>, T>();
}

using Fwd = std::forward_list<int>;
using List = std::list<int>;
using Vec = std::vector<int>;

static_assert(Has_value_type<int[1], int>(), "");
static_assert(Has_value_type<Fwd, int>(), "");
static_assert(Has_value_type<List, int>(), "");
static_assert(Has_value_type<Vec, int>(), "");

int main() { }
