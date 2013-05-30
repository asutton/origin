// Copyright (c) 2008-2010 Kent State University
// Copyright (c) 2011-2012 Texas A&M University
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <cassert>
#include <iostream>

#include <origin/graph/adjacency_vector.hpp>

#include "../graph.test/testing.hpp"

using namespace std;
using namespace origin;
using namespace testing;

int main()
{
  using G = undirected_adjacency_vector<char, int>;
  check_default_init<G>();
  check_add_vertices<G>();
  check_add_edges<G>();

  using D = directed_adjacency_vector<char, int>;
  check_default_init<D>();
  check_add_vertices<D>();
  check_add_edges<D>();
}
