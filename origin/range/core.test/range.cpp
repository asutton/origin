// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/range.hpp>

#include <forward_list>
#include <list>
#include <vector>


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

