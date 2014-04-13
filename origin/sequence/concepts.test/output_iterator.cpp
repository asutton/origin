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
