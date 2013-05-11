// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <forward_list>
#include <list>
#include <vector>

#include <origin/range/concepts.hpp>

using Fwd = std::forward_list<int>;
using List = std::list<int>;
using Vec = std::vector<int>;

static_assert(origin::Random_access_range<Vec>(), "");
static_assert(origin::Random_access_range<const Vec>(), "");

static_assert(not origin::Random_access_range<Fwd>(), "");
static_assert(not origin::Random_access_range<const Fwd>(), "");
static_assert(not origin::Random_access_range<List>(), "");
static_assert(not origin::Random_access_range<const List>(), "");

int main() { }
