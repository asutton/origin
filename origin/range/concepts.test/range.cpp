// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <vector>
#include <list>

#include <origin/range/concepts.hpp>

using Vec = std::vector<int>;
using List = std::list<int>;

static_assert(origin::Range<Vec>(), "");
static_assert(origin::Range<List>(), "");

int main() { }
