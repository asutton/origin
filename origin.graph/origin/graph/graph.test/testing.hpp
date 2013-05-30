// Copyright (c) 2008-2010 Kent State University
// Copyright (c) 2011-2012 Texas A&M University
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef GRAPH_TEST_TESTING_HPP
#define GRAPH_TEST_TESTING_HPP

#include <cassert>
#include <iostream>
#include <vector>

#include <origin/graph/graph.hpp>
#include <origin/graph/io.hpp>

namespace testing
{
  using namespace std;
  using namespace origin;

  // -------------------------------------------------------------------------- //
  //                              Helper Functions

  // Returns true if the vertex v has the given degree values. The order given
  // is out degree, in degree, total degree.

  template<typename G>
    origin::Requires<origin::Directed_graph<G>(), bool>
    has_degrees(const G& g, Vertex<G> v, std::array<size_t, 3> a)
    {
      return g.out_degree(v) == a[0]
          && g.in_degree(v) == a[1];
    }

  template<typename G>
    origin::Requires<origin::Undirected_graph<G>(), bool>
    has_degrees(const G& g, Vertex<G> v, std::array<size_t, 3> a)
    {
      return g.degree(v) == a[2];
    }


  // -------------------------------------------------------------------------- //
  //                              Graph Construction

  template<typename G>
    G build_n_graph(int n)
    {
      G g;
      for (int i = 0; i < n; ++i)
        g.add_vertex('a' + i);
      return g;
    }

  // Construct an n-vertex reflexive clique. Note that the resulting edges are
  // numbered 0..(n * (n + 1))/2.
  template<typename G>
    G build_reflexive_clique(int n)
    {
      G g = build_n_graph<G>(n);
      int x = 0;
      for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j)
          g.add_edge(i, j, x++);
      }
      return g;
    }

  // Construct an n-vertex reflexive bidirected clique. Note that the resulting
  // edges are labeled 0..(n * (n + 1)).
  template<typename G>
    G build_reflexive_bidi_clique(int n)
    {
      G g = build_n_graph<G>(n);
      int x = 0;
      for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
          g.add_edge(i, j, x++);
          g.add_edge(j, i, x++);
        }
      }
      return g;
    }


  // -------------------------------------------------------------------------- //
  //                              Testing Functions

  template<typename G>
    void check_default_init()
    {
      cout << "*** default init (" << typestr<G>() << ") ***\n";
      G g;
      assert(g.empty());
      assert(g.null());
    }

  template<typename G>
    void check_add_vertices()
    {
      cout << "*** add vertices (" << typestr<G>() << ") ***\n";
      G g;
      for (int i = 0; i < 3; ++i)
        g.add_vertex('a' + i);
      assert(g.order() == 3);
      assert(g.empty());

      assert(g(Vertex<G>(0)) == 'a');
      assert(g(Vertex<G>(1)) == 'b');
      assert(g(Vertex<G>(2)) == 'c');
    }

  template<typename G>
    void
    check_add_edges()
    {
      cout << "*** add edges (" << typestr<G>() << ") ***\n";
      G g;
      for (int i = 0; i < 3; ++i)
        g.add_vertex('a' + i);

      vector<Edge<G>> es;
      for (int i = 0; i < 3; ++i) {
        for (int j = i; j < 3; ++j) {
          Edge<G> e = g.add_edge(i, j, es.size());
          es.push_back(e);
        }
      }

      assert(g.size() == 6);
      assert(g(0, 0) == es[0]);
      assert(g(0, 1) == es[1]);
      assert(g(0, 2) == es[2]);
      assert(g(1, 1) == es[3]);
      assert(g(1, 2) == es[4]);
      assert(g(2, 2) == es[5]);

      // Check for symmetry in undirected graphs.
      if (Undirected_graph<G>()) {
        assert(g(1, 0) == es[1]);
        assert(g(2, 0) == es[2]);
        assert(g(2, 1) == es[4]);
      }
    }


  template<typename G>
    void
    check_remove_specific_edge()
    {
      cout << "*** remove specific edge (" << typestr<G>() << ") ***\n";
      G g = build_reflexive_clique<G>(3);
      assert(g.size() == 6);
      // cout << io::edge_list(g) << '\n';
      
      g.remove_edge(0); // Remove (0, 0)
      assert(g.size() == 5);
      assert(has_degrees(g, 0, {2, 0, 2})); // a--b, a--c | empty
      // cout << io::edge_list(g) << '\n';

      g.remove_edge(1); // Remove (0, 1)
      assert(g.size() == 4);
      assert(has_degrees(g, 0, {1, 0, 1})); // a--c | empty
      assert(has_degrees(g, 1, {2, 1, 3})); // b--b, b--c | b--b
      // cout << io::edge_list(g) << '\n';

      g.remove_edge(2); // Remove (0, 2)
      assert(g.size() == 3);
      assert(is_isolated(g, 0)); // empty | empty
      assert(has_degrees(g, 2, {1, 2, 3})); // c--c | b--c, c--c
      // cout << io::edge_list(g) << '\n';

      // Just remove the rest.
      g.remove_edge(3);
      g.remove_edge(4);
      g.remove_edge(5);
      assert(g.empty());
    }

  // Check the removal of single edges from a graph.
  template<typename G>
    void
    check_remove_first_simple_edge()
    {
      cout << "*** remove first simple edge (" << typestr<G>() << ") ***\n";
      G g = build_reflexive_clique<G>(3);
      // cout << io::edge_list(g) << '\n';

      // Remove a loop and test
      g.remove_edge(0, 0);
      // cout << io::edge_list(g) << '\n';
      assert(has_degrees(g, 0, {2, 0, 2})); // a--b, a--c | empty

      // Remove a non-loop and test
      g.remove_edge(0, 1);
      // cout << io::edge_list(g) << '\n';
      assert(has_degrees(g, 0, {1, 0, 1})); // a--c | empty
      assert(has_degrees(g, 1, {2, 1, 3})); // b--b, b--c | b--b

      g.remove_edge(0, 2);
      // cout << io::edge_list(g) << '\n';
      assert(is_isolated(g, 0)); // empty | empty
      assert(has_degrees(g, 2, {1, 2, 3})); // c--c | b--c, c--c

      // Remove the rest and test
      g.remove_edge(1, 1);
      g.remove_edge(1, 2);
      g.remove_edge(2, 2);
      assert(g.empty());
    }

  // Check the removal of the first simple edge in a multigraph. Basically
  // the same as above except that the graph is more complex.
  template<typename G>
    void
    check_remove_first_multi_edge()
    {
      cout << "*** remove first multi edge (" << typestr<G>() << ") ***\n";
      G g = build_reflexive_bidi_clique<G>(3);
      // cout << io::edge_list(g) << '\n';

      // Remove a loop and test
      g.remove_edge(0, 0);
      // cout << io::edge_list(g) << '\n';
      assert(has_degrees(g, 0, {3, 3, 6})); // a--a, a--b, a--c | a--a, b--a, c--a

      g.remove_edge(0, 0);
      // cout << io::edge_list(g) << '\n';
      assert(has_degrees(g, 0, {2, 2, 4})); // a--b, a--c | b--a, c--a
      assert(has_degrees(g, 1, {4, 4, 8})); // b--a, b--b, b--b, b--c | a--b, b--b, b--b, c--b

      // Remove a non-loop and test
      g.remove_edge(0, 1);
      // cout << io::edge_list(g) << '\n';
      assert(has_degrees(g, 0, {1, 2, 3})); // a--c | c--a, b--a
      assert(has_degrees(g, 1, {4, 3, 7})); // b--a, b--b, b--b, b--c | b--b, b--b, c--b

      g.remove_edge(1, 0);
      // cout << io::edge_list(g) << '\n';
      assert(has_degrees(g, 0, {1, 1, 2})); // a--c | c--a
      assert(has_degrees(g, 1, {3, 3, 6})); // b--b, b--b, b--c | b--b, b--b, c--b

      // // Remove the rest and test
      g.remove_edge(0, 2);
      g.remove_edge(2, 0);
      g.remove_edge(1, 1);
      g.remove_edge(1, 1);
      g.remove_edge(1, 2);
      g.remove_edge(2, 1);
      g.remove_edge(2, 2);
      g.remove_edge(2, 2);
      assert(g.empty());
    }

  template<typename G>
    void
    check_remove_multi_edge()
    {
      cout << "*** remove multi edge (" << typestr<G>() << ") ***\n";
      G g = build_reflexive_bidi_clique<G>(3);
      // cout << io::edge_list(g) << '\n';

      g.remove_edges(0, 0); // Remove a--a,a--a
      // cout << io::edge_list(g) << '\n';
      assert(has_degrees(g, 0, {2, 2, 4})); // a--b, a--c | b--a, c--a

      g.remove_edges(0, 1); // Removes a--b (and b--a if undirected)
      // cout << io::edge_list(g) << '\n';
      if (Directed_graph<G>()) {
        assert(has_degrees(g, 0, {1, 2, 3})); // a--c | b--a, c--a
        assert(has_degrees(g, 1, {4, 3, 7})); // b--a, b--b, b--b, b--c | b--b, b--b, c--b
      } else {
        assert(has_degrees(g, 0, {1, 1, 2})); // a--c | c--a
        assert(has_degrees(g, 1, {3, 3, 6})); // b--b, b--b, b--c | b--b, b--b, c--b
      }

      g.remove_edges(0, 2);
      // cout << io::edge_list(g) << '\n';
      if (Directed_graph<G>()) {
        assert(has_degrees(g, 0, {0, 2, 2})); // empty | b--a, c--a
        assert(has_degrees(g, 2, {4, 3, 7})); // c--a, c--b c--c, c--c | b--c, c--c, c--c
      } else {
        assert(has_degrees(g, 0, {0, 0, 0})); // empty | empty
        assert(has_degrees(g, 2, {3, 3, 6})); // c--b, c--c, c--c | b--c, c--c, c--c
      }

      // Remove the remaining edges
      g.remove_edges(1, 0); // No-op if undirected
      g.remove_edges(2, 0); // No-op if undirected
      g.remove_edges(1, 1);
      g.remove_edges(2, 2);
      g.remove_edges(1, 2);
      g.remove_edges(2, 1); // No-op if undirected
      assert(g.empty());
    }

  template<typename G>
    void
    check_remove_vertex_edges()
    {
      cout << "*** remove vertex edges (" << typestr<G>() << ") ***\n";
      G g = build_reflexive_clique<G>(3);
      // cout << io::edge_list(g) << '\n';

      g.remove_edges(0);
      // cout << io::edge_list(g) << '\n';
      assert(has_degrees(g, 0, {0, 0, 0})); // empty | empty
      assert(has_degrees(g, 1, {2, 1, 3})); // b--b, b--c | b--b
      assert(has_degrees(g, 2, {1, 2, 3})); // c--c | b--c, c--c

      g.remove_edges(1);
      // cout << io::edge_list(g) << '\n';
      assert(has_degrees(g, 1, {0, 0, 0})); // empty | empty
      assert(has_degrees(g, 2, {1, 1, 2})); // c--c | c--c

      g.remove_edges(2);
      assert(g.empty());
    }

  template<typename G>
    void
    check_remove_all_edges()
    {
      cout << "*** remove all edges (" << typestr<G>() << ") ***\n";
      G g = build_reflexive_clique<G>(3);
      // cout << io::edge_list(g) << '\n';

      assert(g.size() == 6);
      g.remove_edges();
      assert(g.empty());
    }

} // namespace testing

#endif
