// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/ranges>

#include <forward_list>
#include <list>
#include <vector>

using Fwd = std::forward_list<int>;
using List = std::list<int>;
using Vec = std::vector<int>;

static_assert(origin::Input_range<Fwd>(), "");
static_assert(origin::Input_range<const Fwd>(), "");
static_assert(origin::Input_range<List>(), "");
static_assert(origin::Input_range<const List>(), "");
static_assert(origin::Input_range<Vec>(), "");
static_assert(origin::Input_range<const Vec>(), "");

int main() { }
