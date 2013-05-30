// Copyright (c) 2008-2010 Kent State University
// Copyright (c) 2011-2012 Texas A&M University
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.


#include <origin/graph/adjacency_list.hpp>

#include "../graph.test/testing.hpp"

using namespace std;
using namespace origin;
using namespace testing;

// A little helper class to help trace initializations and data movements.
struct X
{
  static bool trace;

  X()         { if (trace) cout << "default\n"; }
  X(X&&)      { if (trace) cout << "move\n"; }
  X(const X&) { if (trace) cout << "copy\n"; }
};

bool X::trace = false;

void 
trace_insert()
{
  using G = directed_adjacency_list<X>;
  G g;
  X x;
  
  // Each insertion should require exactly one initialization of X.
  X::trace = true;
  g.add_vertex();
  g.add_vertex(std::move(x));
  g.add_vertex(x);
  X::trace = false;
}



int main()
{
  trace_insert();

  // TODO: Write tests for adding vertices and edges. Even though those
  // features are thoroughly exercised by the remove edge tests, it might
  // be nice to include them here.

  using G = undirected_adjacency_list<char, int>;
  check_default_init<G>();
  check_add_vertices<G>();
  check_add_edges<G>();
  check_remove_specific_edge<G>();
  check_remove_first_simple_edge<G>();
  check_remove_first_multi_edge<G>();
  check_remove_multi_edge<G>();
  check_remove_vertex_edges<G>();
  check_remove_all_edges<G>();
  
  using D = directed_adjacency_list<char, int>;
  check_default_init<D>();
  check_add_vertices<D>();
  check_add_edges<D>();
  check_remove_specific_edge<D>();
  check_remove_first_simple_edge<D>();
  check_remove_first_multi_edge<D>();
  check_remove_multi_edge<D>();
  check_remove_vertex_edges<D>();
  check_remove_all_edges<G>();
}
