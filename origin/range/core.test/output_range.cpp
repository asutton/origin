// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/range.hpp>

#include <forward_list>
#include <list>
#include <vector>


using In = std::istream_iterator<int>;
using Fwd = std::forward_list<int>;
using List = std::list<int>;
using Vec = std::vector<int>;

static_assert(origin::Output_range<Fwd, int>(), "");
static_assert(origin::Output_range<List, int>(), "");
static_assert(origin::Output_range<Vec, int>(), "");

int main() { }
