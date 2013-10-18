// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <cassert>
#include <iostream>
#include <sstream>

#include <origin/range/stream.hpp>

int main() {
  std::string s = "1 2 3 4 5";
  std::istringstream ss(s);
  auto is = origin::make_istream<int>(ss);
  auto r = origin::Range(is);

  // We can't copy r into a vector because our iterators are
  // a little simpler...
  //
  // TODO: Rewrite these suites once we have legit containers.
  auto i = r.begin();
  assert(*i == 1); ++i;
  assert(*i == 2); ++i;
  assert(*i == 3); ++i;
  assert(*i == 4); ++i;
  assert(*i == 5); ++i;
  assert(i == r.end());
}
