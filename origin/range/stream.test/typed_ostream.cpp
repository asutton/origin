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

  put(os, 1);
  put(os, 2);
  put(os, 3);
  put(os, 4);
  put(os, 5);
  assert(os.stream().str() == "12345");
}
