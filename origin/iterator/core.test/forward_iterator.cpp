// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/iterator.hpp>

#include <forward_list>
#include <list>
#include <vector>


using In = std::istream_iterator<int>;
using Out = std::ostream_iterator<int>;
using Fwd = std::forward_list<int>;
using List = std::list<int>;
using Vec = std::vector<int>;

static_assert(origin::Forward_iterator<Fwd::iterator>(), "");
static_assert(origin::Forward_iterator<Fwd::const_iterator>(), "");
static_assert(origin::Forward_iterator<List::iterator>(), "");
static_assert(origin::Forward_iterator<List::const_iterator>(), "");
static_assert(origin::Forward_iterator<Vec::iterator>(), "");
static_assert(origin::Forward_iterator<Vec::const_iterator>(), "");
static_assert(origin::Forward_iterator<int*>(), "");
static_assert(origin::Forward_iterator<const int*>(), "");

static_assert(not origin::Forward_iterator<In>(), "");
static_assert(not origin::Forward_iterator<Out>(), "");

int main() { }
