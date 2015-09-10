// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

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
