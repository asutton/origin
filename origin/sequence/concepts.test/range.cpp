// Copyright (c) 2008-2014 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <forward_list>
#include <list>
#include <vector>

#include <origin/sequence/concepts.hpp>

using Fwd = std::forward_list<int>;
using List = std::list<int>;
using Vec = std::vector<int>;

static_assert(origin::Range<int[1]>(), "");
static_assert(origin::Range<int(&)[1]>(), "");
static_assert(origin::Range<Fwd>(), "");
static_assert(origin::Range<Vec>(), "");
static_assert(origin::Range<List>(), "");

static_assert(origin::Range<Vec&>(), "");
static_assert(origin::Range<const Vec&>(), "");

template<origin::Range R>
  void f(R&& range) { }

int main() { 
  Vec v1;
  const Vec v2 { };
  f(v1);
  f(v2);
  f(Vec{});
}

