// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <forward_list>
#include <list>
#include <vector>

#include <origin/iterator/concepts.hpp>

using In = std::istream_iterator<int>;
using Out = std::ostream_iterator<int>;
using Fwd = std::forward_list<int>;
using List = std::list<int>;
using Vec = std::vector<int>;

static_assert(origin::Input_iterator<In>(), "");
static_assert(origin::Input_iterator<Fwd::iterator>(), "");
static_assert(origin::Input_iterator<Fwd::const_iterator>(), "");
static_assert(origin::Input_iterator<List::iterator>(), "");
static_assert(origin::Input_iterator<List::const_iterator>(), "");
static_assert(origin::Input_iterator<Vec::iterator>(), "");
static_assert(origin::Input_iterator<Vec::const_iterator>(), "");
static_assert(origin::Input_iterator<int*>(), "");
static_assert(origin::Input_iterator<const int*>(), "");

static_assert(not origin::Input_iterator<Out>(), "");

int main() { }
