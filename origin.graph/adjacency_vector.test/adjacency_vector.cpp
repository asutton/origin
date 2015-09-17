// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <cassert>
#include <iostream>

#include <origin.graph/adjacency_vector.hpp>

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
