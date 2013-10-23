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

  for(int x : is) {
     std::cout << x << '\n';
  }

  static_assert(not origin::Range<decltype(is)>(), "");
}
