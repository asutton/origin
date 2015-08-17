// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/ranges>

#include <forward_list>
#include <list>
#include <vector>

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
