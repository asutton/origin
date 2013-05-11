// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <forward_list>
#include <list>
#include <vector>

#include <origin/range/concepts.hpp>

using In = std::istream_iterator<int>;
using Fwd = std::forward_list<int>;
using List = std::list<int>;
using Vec = std::vector<int>;

static_assert(origin::Output_range<Fwd, int>(), "");
static_assert(origin::Output_range<List, int>(), "");
static_assert(origin::Output_range<Vec, int>(), "");

int main() { }
