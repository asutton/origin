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
  constexpr bool Has_size_type() {
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
