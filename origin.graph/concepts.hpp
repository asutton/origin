// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef GRAPH_CONCEPTS_HPP
#define GRAPH_CONCEPTS_HPP

#include <origin/type/concepts.hpp>

namespace origin
{
  // TODO: Lots and lots of traits for graphs!

  namespace graph_impl
  {
    template<typename G, typename V>
      class get_out_edges
      {
        template<typename X, typename Y>
          static auto check(const X& x, Y y) -> decltype(x.out_edges(y));

        static subst_failure check(...);
      public:
        using type = decltype(check(std::declval<G>(), std::declval<V>()));
      };

    template<typename G, typename V>
      class get_in_edges
      {
        template<typename X, typename Y>
          static auto check(const X& x, Y y) -> decltype(x.in_edges(y));

        static subst_failure check(...);
      public:
        using type = decltype(check(std::declval<G>(), std::declval<V>()));
      };

    template<typename G, typename V>
      class get_inc_edges
      {
        template<typename X, typename Y>
          static auto check(const X& x, Y y) -> decltype(x.edges(y));

        static subst_failure check(...);
      public:
        using type = decltype(check(std::declval<G>(), std::declval<V>()));
      };

  } // namsepace graph_impl


  // Returns true iff g.out_edges(v) is a valid expression.
  template<typename G, typename V>
    constexpr bool Has_out_edges()
    {
      return Subst_succeeded<typename graph_impl::get_out_edges<G, V>::type>();
    }

  // Returns true iff g.in_edges(v) is a valid expression.
  template<typename G, typename V>
    constexpr bool Has_in_edges()
    {
      return Subst_succeeded<typename graph_impl::get_in_edges<G, V>::type>();
    }

  // Returns true iff g.eges(v) is a valid expression.
  template<typename G, typename V>
    constexpr bool Has_incident_edges()
    {
      return Subst_succeeded<typename graph_impl::get_inc_edges<G, V>::type>();
    }



  // ------------------------------------------------------------------------ //
  //                                                               [graph.types]
  //                            Graph Type Functions
  //
  // TODO: These should probably be made a little more robust -- make them
  // dependent on the type of dereferncing a vertex or edge iterator.

  template<typename G>
    using Vertex = typename G::vertex;

  template<typename G>
    using Edge = typename G::edge;





  // ------------------------------------------------------------------------ //
  //                                                            [graph.concepts]
  //                            Graph Concepts
  //
  // TODO: Obviously, finish writing these.

  // Returns true if G is a directed graph.
  template<typename G>
    constexpr bool Directed_graph()
    {
      return Has_out_edges<G, Vertex<G>>() && Has_in_edges<G, Vertex<G>>();
    }

  // Returns true if G is an undirected graph.
  template<typename G>
    constexpr bool Undirected_graph()
    {
      return Has_incident_edges<G, Vertex<G>>();
    }

} // namespace origin

#endif
