// Copyright (c) 2008-2014 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <forward_list>
#include <list>
#include <vector>

#include <origin/sequence/concepts.hpp>

// True when the range R has size type T.
template<typename R, typename T>
  constexpr bool Has_value_type() {
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
