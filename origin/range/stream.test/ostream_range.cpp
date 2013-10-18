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
  std::string s;
  std::ostringstream ss(s);
  auto os = origin::make_ostream<int>(ss);
  auto r = origin::Range(os);

  // We can't copy r into a vector because our iterators are
  // a little simpler...
  //
  // TODO: Rewrite these suites once we have legit containers.
  auto i = r.begin();
  *i = 1; assert(os.stream().str() == "1");
  *i = 2; assert(os.stream().str() == "12");
  *i = 3; assert(os.stream().str() == "123");
  *i = 4; assert(os.stream().str() == "1234");
  *i = 5; assert(os.stream().str() == "12345");
  assert(i != r.end());
}
