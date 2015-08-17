// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/ranges>

#include <forward_list>
#include <list>
#include <vector>


using In = std::istream_iterator<int>;
using Out = std::ostream_iterator<int>;
using Fwd = std::forward_list<int>;
using List = std::list<int>;
using Vec = std::vector<int>;

static_assert(origin::Output_iterator<Out, int>(), "");
static_assert(origin::Output_iterator<Fwd::iterator, int>(), "");
static_assert(origin::Output_iterator<List::iterator, int>(), "");
static_assert(origin::Output_iterator<Vec::iterator, int>(), "");
static_assert(origin::Output_iterator<int*, int>(), "");

static_assert(not origin::Output_iterator<In, int>(), "");
static_assert(not origin::Output_iterator<Fwd::const_iterator, int>(), "");
static_assert(not origin::Output_iterator<List::const_iterator, int>(), "");
static_assert(not origin::Output_iterator<Vec::const_iterator, int>(), "");
static_assert(not origin::Output_iterator<const int*, int>(), "");

int main() { }
