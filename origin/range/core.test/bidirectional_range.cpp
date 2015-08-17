// Copyright (c) 2008-2014 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/range.hpp>

#include <forward_list>
#include <list>
#include <vector>

using Fwd = std::forward_list<int>;
using List = std::list<int>;
using Vec = std::vector<int>;

static_assert(origin::Bidirectional_range<List>(), "");
static_assert(origin::Bidirectional_range<const List>(), "");
static_assert(origin::Bidirectional_range<Vec>(), "");
static_assert(origin::Bidirectional_range<const Vec>(), "");

static_assert(not origin::Bidirectional_range<Fwd>(), "");
static_assert(not origin::Bidirectional_range<const Fwd>(), "");

int main() { }
