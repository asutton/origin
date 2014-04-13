// Copyright (c) 2008-2014 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <forward_list>
#include <list>
#include <vector>

#include <origin/sequence/concepts.hpp>

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
