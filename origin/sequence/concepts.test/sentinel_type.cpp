// Copyright (c) 2008-2014 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <iostream>
#include <forward_list>
#include <list>
#include <vector>

#include <origin/sequence/concepts.hpp>

// TODO: Construct some ranges whose iterator/sentinel types differ.

// True when the range R has sentinel type T.
template<typename R, typename T>
  constexpr bool Has_sentinel_type() {
    return origin::Same<origin::Sentinel_type<R>, T>();
  }

using Fwd = std::forward_list<int>;
using List = std::list<int>;
using Vec = std::vector<int>;

static_assert(Has_sentinel_type<int[1], int*>(), "");
static_assert(Has_sentinel_type<const int[1], const int*>(), "");
static_assert(Has_sentinel_type<Fwd, Fwd::iterator>(), "");
static_assert(Has_sentinel_type<const Fwd, Fwd::const_iterator>(), "");
static_assert(Has_sentinel_type<List, List::iterator>(), "");
static_assert(Has_sentinel_type<const List, List::const_iterator>(), "");
static_assert(Has_sentinel_type<Vec, Vec::iterator>(), "");
static_assert(Has_sentinel_type<const Vec, Vec::const_iterator>(), "");

int main() { }
