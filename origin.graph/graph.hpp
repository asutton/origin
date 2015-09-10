// Copyright (c) 2008-2010 Kent State University
// Copyright (c) 2011-2012 Texas A&M University
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <origin.graph/concepts.hpp>

namespace origin
{
  // ------------------------------------------------------------------------ //
  //                                                             [graph.generic]
  //                          Generic Graph Interface
  //
  // The generic graph interface is a set of types and operations defined
  // commonly for various graph data structures.


  // Returns a range over the vertices of a graph.
  template<typename G>
    inline auto
    vertices(const G& g) -> decltype(g.vertices()) { return g.vertices(); }

  // Returns a range over the edges of a graph.
  template<typename G>
    inline auto
    edges(const G& g) -> decltype(g.edges()) { return g.edges(); }

  // Returns the source vertex of an edge in g.
  template<typename G>
    inline Vertex<G>
    source(const G& g, Edge<G> e) { return g.source(e); }

  // Returns the target vertex of an edge in g.
  template<typename G>
    inline Vertex<G>
    target(const G& g, Edge<G> e) { return g.target(e); }

  // Returns true if v is an isolated vertex. An isolated vertex is one that
  // has no incident edges.
  template<typename G>
    inline bool
    is_isolated(const G& g, Vertex<G> v) { return g.degree(v) == 0; }

  // Returns true iff v is the source vertex of e.
  template<typename G>
    inline bool
    is_source(const G& g, Edge<G> e, Vertex<G> v) { return source(g, e) == v; }

  // Returns true iff v is the target vertex of e.
  template<typename G>
    inline bool
    is_target(const G& g, Edge<G> e, Vertex<G> v) { return target(g, e) == v; }

  // Returns true iff v is an endpoint (source or target) of e.
  template<typename G>
    inline bool
    is_endpoint(const G& g, Edge<G> e, Vertex<G> v)
    {
      return is_source(g, e, v) || is_target(g, e, v);
    }

  template<typename G>
    inline Requires<Directed_graph<G>(), bool>
    are_endpoints(const G& g, Edge<G> e, Vertex<G> u, Vertex<G> v)
    {
      return is_source(g, e, u) && is_target(g, e, v);
    }

  template<typename G>
    inline Requires<Undirected_graph<G>(), bool>
    are_endpoints(const G& g, Edge<G> e, Vertex<G> u, Vertex<G> v)
    {
      return (is_source(g, e, u) && is_target(g, e, v))
          || (is_source(g, e, v) && is_target(g, e, u));
    }

  // Returns true if e is a self loop.
  template<typename G>
    inline bool
    is_loop(const G& g, Edge<G> e) { return source(g, e) == target(g, e); }

  // Return the opposite endpoint of the edge e in v. If v is not an endpoint
  // of e, the result is undefined.
  template<typename G>
    inline Vertex<G>
    opposite(const G& g, Edge<G> e, Vertex<G> v)
    {
      assert(is_endpoint(g, e, v));
      Vertex<G> u = source(g, e);
      return u == v ? target(g, e) : u;
    }



  // ------------------------------------------------------------------------ //
  //                                                                [graph.pred]
  //                          Common Graph Predicates
  //
  // The following function objects are useful in a number of graph operations.
  //
  //    has_target<G>
  //    has_source<G>
  //

  // Returns true when an edge is is the same as some target vertex.
  template<typename G>
    struct has_target
    {
      has_target(const G& g, Vertex<G> v)
        : g(g), v(v)
      { }

      inline bool
      operator()(Edge<G> e) const { return target(g, e) == v; }

      const G&  g;
      Vertex<G> v;
    };

  // Returns true when an edge is is the same as some source vertex.
  template<typename G>
    struct has_source
    {
      has_source(const G& g, Vertex<G> v)
        : g(g), v(v)
      { }

      inline bool
      operator()(Edge<G> e) const { return source(g, e) == v; }

      const G&  g;
      Vertex<G> v;
    };

  // Returns true if an edge has an end equal to v.
  template<typename G>
    struct has_endpoint
    {
      has_endpoint(const G& g, Vertex<G> v)
        : g(g), v(v)
      { }

      inline bool
      operator()(Edge<G> e) const
      {
        return source(g, e) == v || target(g, e) == v;
      }

      const G& g;
      Vertex<G> v;
    };

  // Returns true if an edge has endpoints equal to u and v (in that order).
  // If G is undirected, then
  template<typename G>
    struct has_endpoints
    {
      has_endpoints(const G& g, Vertex<G> u, Vertex<G> v)
        : g(g), u(u), v(v)
      { }

      inline bool
      operator()(Edge<G> e) const
      {
        return are_endpoints(g, e, u, v);
      }

      const G& g;
      Vertex<G> u;
      Vertex<G> v;
    };

  // Returns true when an edge e is a loop on vertex v.
  template<typename G>
    struct is_looped
    {
      is_looped(const G& g, Vertex<G> v)
        : g(g), v(v)
      { }

      inline bool
      operator()(Edge<G> e) const
      {
        return is_source(g, e, v) && is_target(g, e, v);
      }

      const G& g;
      Vertex<G> v;
    };

} // namespace origin

#endif
