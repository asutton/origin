// Copyright (c) 2008-2010 Kent State University
// Copyright (c) 2011-2012 Texas A&M University
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_GRAPH_IO_HPP
#define ORIGIN_GRAPH_IO_HPP

#include <iosfwd>

#include <origin/graph/graph.hpp>

namespace origin
{
  namespace io
  {
    // ---------------------------------------------------------------------- //
    //                                                                [graph.io]
    //                              Graph I/O
    //
    // Support for various forms of graph I/O.
    //
    // TODO: Rewrite the operations used by this module in terms of the generic
    // graph interface.
    //
    // TODO: Develop type constraints for these operations. Also, what should
    // we print when no value types have been given.


    // Support the printing of vertex lists.
    template<typename G>
      struct vertex_list_printer
      {
        vertex_list_printer(const G& g) : g(g) { }
        const G& g;
      };

    // Returns a vertex list.
    template<typename G>
      inline vertex_list_printer<G> 
      vertex_list(const G& g) { return vertex_list_printer<G>(g); }


    // Support the printing of edge lists.
    template<typename G>
      struct edge_list_printer
      {
        edge_list_printer(const G& g) : g(g) { }
        const G& g;
      };

    // Return an edge list printer.
    template<typename G>
      inline edge_list_printer<G> 
      edge_list(const G& g) { return edge_list_printer<G>(g); }


    // Supports the printing of edge tuples.
    template<typename G>
      struct edge_printer
      {
        edge_printer(const G& g, Edge<G> e) : g(g), e(e) { }
        const G& g;
        Edge<G> e;
      };

    // Returns an edge printer.
    template<typename G>
      inline edge_printer<G>
      edge(const G& g, Edge<G> e) { return edge_printer<G>(g, e); }


    // Print the vertex list of a graph. Each vertex is printed on a
    // separate line.
    template<typename C, typename T, typename G>
      inline std::basic_ostream<C, T>&
      operator<<(std::basic_ostream<C, T>& os, vertex_list_printer<G> p)
      {
        const G& g = p.g;
        for (auto v : g.vertices())
          os << g(v) << '\n';
        return os;
      }

    // Print the edge list of a graph.
    template<typename C, typename T, typename G>
      inline std::basic_ostream<C, T>&
      operator<<(std::basic_ostream<C, T>& os, edge_list_printer<G> p)
      {
        const G& g = p.g;
        for (auto e : g.edges())
          os << edge(g, e) << '\n';
        return os;
      }

    template<typename C, typename T, typename G>
      inline std::basic_ostream<C, T>&
      operator<<(std::basic_ostream<C, T>& os, edge_printer<G> p)
      {
        const G& g = p.g;
        Edge<G> e = p.e;
        Vertex<G> u = g.source(e);
        Vertex<G> v = g.target(e);
        return os << g(u) << ' ' << g(v) << ' ' << g(e);
      }

  } // namespace io
} // namespace origin

#endif