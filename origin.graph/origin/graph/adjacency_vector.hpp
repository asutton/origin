// Copyright (c) 2008-2010 Kent State University
// Copyright (c) 2011-2012 Texas A&M University
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_GRAPH_ADJACENCY_VECTOR_HPP
#define ORIGIN_GRAPH_ADJACENCY_VECTOR_HPP

#include <cassert>

#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

#include <origin/type/concepts.hpp>
#include <origin/type/empty.hpp>
#include <origin/type/typestr.hpp>
#include <origin/type/functional.hpp>
#include <origin/sequence/algorithm.hpp>
#include <origin/sequence/range.hpp>

#include <origin/graph/handle.hpp>
#include <origin/graph/graph.hpp>
#include <origin/graph/io.hpp>

#include <origin/graph/adjacency_list.impl/pool.hpp>

namespace origin
{

  namespace adjacency_vector_impl
  {

    // The handle iterator wraps a constant iterator of the container type C and
    // returns handles of type H when dereferenced.
    //
    // TODO: Make this a random access iterator.
    template<typename T, typename H>
      struct handle_counter
      {
        using handle_type = H;
        using counter_type = T;

        handle_counter(counter_type n)
          : count(n)
        { }

        handle_type operator*() const { H(count); }

        handle_counter& operator++();
        handle_counter  operator++(int);

        T count;
      };


    template<typename C, typename H>
      inline handle_counter<C, H>&
      handle_counter<C, H>::operator++()
      {
        ++count;
        return *this;
      }

    template<typename C, typename H>
      inline handle_counter<C, H>
      handle_counter<C, H>::operator++(int)
      {
        handle_counter tmp = *this;
        ++count;
        return tmp;
      }

    // Equality
    template<typename C, typename H>
      inline bool
      operator==(const handle_counter<C, H>& a, const handle_counter<C, H>& b)
      {
        return a.count == b.count;
      }

    template<typename C, typename H>
      inline bool
      operator!=(const handle_counter<C, H>& a, const handle_counter<C, H>& b)
      {
        return a.count != b.count;
      }


    // ---------------------------------------------------------------------- //
    //                            Edge Representation
    //
    // An edge is a triple describing the source vertex, the target vertex and
    // user data. The edge representation is the same for both directed and
    // undirected adjacency lists. 
    //
    // In an undirected adjacency list, the source and target vertices refer to
    // the vertices in the order they were specified on addition. There is no
    // other meaning attributed to them.
    template<typename E>
      struct edge
      {
        using value_type = E;

        edge()
          : data(-1, -1, E{})
        { }

        edge(vertex_handle s, vertex_handle t)
          : data(s, t, E{})
        { }

        template<typename... Args>
          edge(vertex_handle s, vertex_handle t, Args&&... args)
            : data(s, t, std::forward<Args>(args)...)
          { }

        vertex_handle& source()       { return std::get<0>(data); }
        vertex_handle  source() const { return std::get<0>(data); }

        vertex_handle& target()       { return std::get<1>(data); }
        vertex_handle  target() const { return std::get<1>(data); }

        E&       value()       { return std::get<2>(data); }
        const E& value() const { return std::get<2>(data); }

        std::tuple<vertex_handle, vertex_handle,  E> data;
      };

    // An (incident) edge list is a vector of indexes.
    using edge_list = std::vector<edge_handle>;
  
    // An alias for the edge pool.
    template<typename E>
      using edge_set = std::vector<edge<E>>;

    // An alias for the edge iterator.
    template<typename E>
      using edge_iterator = handle_counter<std::size_t, edge_handle>;

    // An alias for the edge range.
    template<typename E>
      using edge_range = bounded_range<edge_iterator<E>>;

    // An alias for the incident edge iterator.
    using incidence_iterator = typename edge_list::const_iterator;

    // An alias for the icident edge range.
    using incidence_range = bounded_range<incidence_iterator>;

  } // namespace adjacency_vector_impl



  // ------------------------------------------------------------------------ //
  //                                                         [graph.adj_vec.dir]
  //                        Directed Adjacency Vector
  //
  // A directed adjacency vector is a kind of adjacency list that supports only
  // incremental algorithms. That is, the data structure allows for the efficent
  // insertion insertion of vertices and edges, but removal is not supported.
  // Like any [Adjacency_list], the data structure also provides efficient
  // access to all vertices, all edges, and the successors and predecessors
  // of each vertex.

  namespace directed_adjacency_vector_impl
  {
    // Imports
    using adjacency_vector_impl::handle_counter;
    using adjacency_vector_impl::edge_list;


    // ---------------------------------------------------------------------- //
    //                        Vertex Representation
    
    // A vertex in adjacency list is implemented as a pair of edge lisst. An
    // edge list is simply a vector of indexes that refer to edges in a
    // separate edge container.
    //
    // Note that the class will compress the value type if it is empty.
    template<typename V>
      struct vertex
      {
        using value_type = V;
        using iterator = typename edge_list::iterator;
        using const_iterator = typename edge_list::const_iterator;
    
        vertex()
          : data()
        { }

        template<typename... Args>
          vertex(Args&&... args) 
            : data(edge_list{}, edge_list{}, std::forward<Args>(args)...)
          { }

        // Returns the out ege list
        edge_list&       out()       { return std::get<0>(data); }
        const edge_list& out() const { return std::get<0>(data); }
        
        // Returns the in edge list
        edge_list&       in()       { return std::get<1>(data); }
        const edge_list& in() const { return std::get<1>(data); }

        // Returns the user-supplied data object.
        V&       value()       { return std::get<2>(data); }
        const V& value() const { return std::get<2>(data); }

        // Edge insertion
        void insert_out(edge_handle e) { insert_edge(out(), e); }
        void insert_in(edge_handle e) { insert_edge(in(), e); }

        // Out edges
        std::size_t out_degree() const { return out().size(); }

        iterator begin_out() { return out().begin(); }
        iterator end_out()   { return out().end(); }
        const_iterator begin_out() const { return out().begin(); }
        const_iterator end_out() const   { return out().end(); }

        // In edges
        std::size_t in_degree() const { return in().size(); }
        
        iterator begin_in() { return in().begin(); }
        iterator end_in()   { return in().end(); }
        const_iterator begin_in() const { return in().begin(); }
        const_iterator end_in() const   { return in().end(); }


        // Helper functions
        void insert_edge(edge_list& l, edge_handle e);

      public:
        std::tuple<edge_list, edge_list, V> data;
      };

    template<typename V>
      inline void
      vertex<V>::insert_edge(edge_list& l, edge_handle e)
      {
        l.push_back(e);
      }

    // A vertex set simply a vector of vertices.
    template<typename V>
      using vertex_set = std::vector<vertex<V>>;

    // An alias for the vertex iterator.
    template<typename V>
      using vertex_iterator = handle_counter<std::size_t, vertex_handle>;

    // An alias for the vertex range.
    template<typename V>
      using vertex_range = bounded_range<vertex_iterator<V>>;


  } // namespace directed_adjacency_vector_impl



  // Implementation of a diretected adjacency list.
  template<typename V = empty_t, typename E = empty_t>
    class directed_adjacency_vector
    {
      using this_type = directed_adjacency_vector<V, E>;

      using vertex_node = directed_adjacency_vector_impl::vertex<V>;
      using vertex_set = directed_adjacency_vector_impl::vertex_set<V>;
      using vertex_iter = directed_adjacency_vector_impl::vertex_iterator<V>;

      using edge_node = adjacency_vector_impl::edge<E>;
      using edge_set = adjacency_vector_impl::edge_set<E>;
      using edge_iter = adjacency_vector_impl::edge_iterator<E>;

      using incidence_iter = adjacency_vector_impl::incidence_iterator;
    public:
      using vertex = vertex_handle;
      using vertex_range = directed_adjacency_vector_impl::vertex_range<V>;

      using edge = edge_handle;
      using edge_range = adjacency_vector_impl::edge_range<E>;

      using incidence_range = adjacency_vector_impl::incidence_range;


      // Observers
      bool        null() const  { return verts_.empty(); }
      std::size_t order() const { return verts_.size(); }

      bool        empty() const { return edges_.empty(); }
      std::size_t size() const  { return edges_.size(); }

      // Vertex observers
      std::size_t out_degree(vertex v) const { return node(v).out_degree(); }
      std::size_t in_degree(vertex v) const  { return node(v).in_degree(); }
      std::size_t degree(vertex v) const { return out_degree(v) + in_degree(v); }

      // Edge observers
      vertex source(edge e) const { return get_edge(e).source(); }
      vertex target(edge e) const { return get_edge(e).target(); }

      // Data access
      V&       operator()(vertex v)       { return node(v).value(); }
      const V& operator()(vertex v) const { return node(v).value(); }

      E&       operator()(edge e)       { return get_edge(e).value(); }
      const E& operator()(edge e) const { return get_edge(e).value(); }

      // Edge relation
      edge operator()(vertex u, vertex v) const;

      // Vertex set
      vertex add_vertex();
      vertex add_vertex(V&& x);
      vertex add_vertex(const V& x);

      template<typename... Args>
        vertex emplace_vertex(Args&&...);

      // Edge set
      edge add_edge(vertex u, vertex v);
      edge add_edge(vertex u, vertex v, E&& x);
      edge add_edge(vertex u, vertex v, const E& x);

      template<typename... Args>
        edge emplace_edge(vertex u, vertex v, Args&&...);

      // Iterators
      vertex_range    vertices() const;
      edge_range      edges() const;
      incidence_range out_edges(vertex v) const;
      incidence_range in_edges(vertex v) const;

    private:
      vertex_node&       node(vertex v)       { return verts_[v]; }
      const vertex_node& node(vertex v) const { return verts_[v]; }

      edge_node&       get_edge(edge e)       { return edges_[e]; }
      const edge_node& get_edge(edge e) const { return edges_[e]; }

      // Helper functions for finding, connecting, disconnecting edges.
      edge find_out_edge(vertex u, vertex v) const;
      edge find_in_edge(vertex u, vertex v) const;

      template<typename S, typename P>
        edge find_edge(const S& seq, P pred) const;

      void link_edge(vertex u, vertex v, edge e);

    private:
      vertex_set verts_;
      edge_set   edges_;
    };

  template<typename V, typename E>
    inline auto
    directed_adjacency_vector<V, E>::operator()(vertex u, vertex v) const -> edge
    {
      if (out_degree(u) <= in_degree(v))
        return find_out_edge(u, v);
      else
        return find_in_edge(u, v);
    }

  template<typename V, typename E>
    inline auto
    directed_adjacency_vector<V, E>::find_out_edge(vertex u, vertex v) const -> edge
    {
      using P = has_target<this_type>;
      const vertex_node& n = node(u);
      return find_edge(n.out(), P(*this, v));
    }

  template<typename V, typename E>
    inline auto
    directed_adjacency_vector<V, E>::find_in_edge(vertex u, vertex v) const -> edge
    {
      using P = has_source<this_type>;
      const vertex_node& n = node(v);
      return find_edge(n.in(), P(*this, u));
    }

  template<typename V, typename E>
    template<typename S, typename P>
    inline auto
    directed_adjacency_vector<V, E>::find_edge(const S& seq, P pred) const -> edge
    {
      auto i = find_if(seq, pred);
      return i == seq.end() ? edge() : *i;
    }

  // Add a vertex to the graph, returning a handle to the new object. If
  // V is a user-supplied type, its value is default constructed.
  template<typename V, typename E>
    inline auto
    directed_adjacency_vector<V, E>::add_vertex() -> vertex
    {
      return emplace_vertex();
    }

  template<typename V, typename E>
    inline auto
    directed_adjacency_vector<V, E>::add_vertex(V&& x) -> vertex
    {
      return emplace_vertex(std::move(x));
    }

  template<typename V, typename E>
    inline auto
    directed_adjacency_vector<V, E>::add_vertex(const V& x) -> vertex
    {
      return emplace_vertex(x);
    }

  template<typename V, typename E>
    template<typename... Args>
      inline auto
      directed_adjacency_vector<V, E>::emplace_vertex(Args&&... args) -> vertex
      {
        vertex n = verts_.size();
        verts_.emplace_back(std::forward<Args>(args)...);
        return n;
      }


  // Add a defaul edge from u to v.
  template<typename V, typename E>
    inline auto
    directed_adjacency_vector<V, E>::add_edge(vertex u, vertex v) -> edge
    {
      return emplace_edge(u, v);
    }

  // Move x into an edge connecting u to v.
  template<typename V, typename E>
    inline auto
    directed_adjacency_vector<V, E>::add_edge(vertex u, vertex v, E&& x) -> edge
    {
      return emplace_edge(u, v, std::move(x));
    }

  // Copy x into an edge connecting u to v.
  template<typename V, typename E>
    inline auto
    directed_adjacency_vector<V, E>::
      add_edge(vertex u, vertex v, const E& x) -> edge
    {
      return emplace_edge(u, v, x);
    }

  template<typename V, typename E>
    template<typename... Args>
      inline auto
      directed_adjacency_vector<V, E>::
        emplace_edge(vertex u, vertex v, Args&&... args) -> edge
      {
        edge e = edges_.size();
        edges_.emplace_back(u, v, std::forward<Args>(args)...);
        link_edge(u, v, e);
        return e;
      }

  template<typename V, typename E>
    inline void
    directed_adjacency_vector<V, E>::link_edge(vertex u, vertex v, edge e)
    {
      vertex_node& un = node(u);
      vertex_node& vn = node(v);
      un.insert_out(e);
      vn.insert_in(e);
    }


  // Retrun a range over the vertex set.
  template<typename V, typename E>
    inline auto
    directed_adjacency_vector<V, E>::vertices() const -> vertex_range
    {
      return {vertex_iter(verts_.begin()), vertex_iter(verts_.end())};
    }

  // Return a range over the edge set.
  template<typename V, typename E>
    inline auto
    directed_adjacency_vector<V, E>::edges() const -> edge_range
    {
      return {edge_iter(edges_.begin()), edge_iter(edges_.end())};
    }

  // Return a range over the out edges of the vertex v.
  template<typename V, typename E>
    inline auto
    directed_adjacency_vector<V, E>::out_edges(vertex v) const -> incidence_range
    {
      const vertex_node& vn = node(v);
      return {incidence_iter(vn.begin_out()), incidence_iter(vn.end_out())};
    }

  template<typename V, typename E>
    inline auto
    directed_adjacency_vector<V, E>::in_edges(vertex v) const -> incidence_range
    {
      const vertex_node& vn = node(v);
      return {incidence_iter(vn.begin_in()), incidence_iter(vn.end_in())};
    }



  // ------------------------------------------------------------------------ //
  //                                                      [graph.adj_list.undir]
  //                        Undirected Adjacency List
  //
  // A directed adjacency list...

  namespace undirected_adjacency_vector_impl
  {
    using origin::adjacency_vector_impl::handle_counter;
    using origin::adjacency_vector_impl::edge_list;

    // ---------------------------------------------------------------------- //
    //                        Vertex Representation
    
    // A vertex in an undirected adjacency list is simply a list of incident
    // edges. No distinction is made between in or out edges.
    template<typename V>
      struct vertex
      {
        using value_type = V;
        using iterator = typename edge_list::iterator;
        using const_iterator = typename edge_list::const_iterator;
    
        vertex()
          : data()
        { }

        template<typename... Args>
          vertex(Args&&... args) 
            : data(edge_list{}, std::forward<Args>(args)...)
          { }

        // Returns the out ege list
        edge_list&       edges()       { return std::get<0>(data); }
        const edge_list& edges() const { return std::get<0>(data); }
        
        // Returns the user-supplied data object.
        V&       value()       { return std::get<1>(data); }
        const V& value() const { return std::get<1>(data); }

        // Out edges
        std::size_t degree() const { return edges().size(); }

        void insert(edge_handle e);

        iterator begin() { return edges().begin(); }
        iterator end()   { return edges().end(); }
        const_iterator begin() const { return edges().begin(); }
        const_iterator end() const   { return edges().end(); }

      public:
        std::tuple<edge_list, V> data;
      };

    template<typename V>
      inline void
      vertex<V>::insert(edge_handle e)
      {
        edges().push_back(e);
      }

    // A vertex set is a vector of vertices.
    template<typename V>
      using vertex_set = std::vector<vertex<V>>;

    // An alias for the vertex iterator.
    template<typename V>
      using vertex_iterator = handle_counter<vertex_set<V>, vertex_handle>;

    // An alias for the vertex range.
    template<typename V>
      using vertex_range = bounded_range<vertex_iterator<V>>;

  } // namespace undirected_adjacency_vector_impl


  // Implementation of the undirected adjacency list.
  template<typename V = empty_t, typename E = empty_t>
    class undirected_adjacency_vector
    {
      using this_type = undirected_adjacency_vector<V, E>;

      using vertex_node = undirected_adjacency_vector_impl::vertex<V>;
      using vertex_set = undirected_adjacency_vector_impl::vertex_set<V>;
      using vertex_iter = undirected_adjacency_vector_impl::vertex_iterator<V>;

      using edge_node = adjacency_vector_impl::edge<E>;
      using edge_set = adjacency_vector_impl::edge_set<E>;
      using edge_iter = adjacency_vector_impl::edge_iterator<E>;

      using incidence_iter = adjacency_vector_impl::incidence_iterator;
    public:
      using vertex = vertex_handle;
      using vertex_range = undirected_adjacency_vector_impl::vertex_range<V>;

      using edge = edge_handle;
      using edge_range = adjacency_vector_impl::edge_range<E>;

      using incidence_range = adjacency_vector_impl::incidence_range;


      // Observers
      bool        null() const  { return verts_.empty(); }
      std::size_t order() const { return verts_.size(); }

      bool        empty() const { return edges_.empty(); }
      std::size_t size() const  { return edges_.size(); }

      // Vertex observers
      std::size_t degree(vertex v) const { return node(v).degree(); }

      // Edge observers
      
      // Returns the first and second endpoints of the edge, e. If e was added
      // using g.add_edge(u, v), u is the source and v is the target. There
      // is no special meaning attributed to the order.
      vertex source(edge e) const { return get_edge(e).source(); }
      vertex target(edge e) const { return get_edge(e).target(); }

      // Data access
      V&       operator()(vertex v)       { return node(v).value(); }
      const V& operator()(vertex v) const { return node(v).value(); }

      E&       operator()(edge e)       { return get_edge(e).value(); }
      const E& operator()(edge e) const { return get_edge(e).value(); }

      // Relation
      edge operator()(vertex u, vertex v) const;

      // Vertex set
      vertex add_vertex();
      vertex add_vertex(V&& x);
      vertex add_vertex(const V& x);

      template<typename... Args>
        vertex emplace_vertex(Args&&... args);

      // Edge set
      edge add_edge(vertex u, vertex v);
      edge add_edge(vertex u, vertex v, E&& x);
      edge add_edge(vertex u, vertex v, const E& x);

      template<typename... Args>
        edge emplace_edge(vertex u, vertex v, Args&&... args);

      // Iterators
      vertex_range    vertices() const;
      edge_range      edges() const;
      incidence_range edges(vertex v) const;

    private:
      vertex_node&       node(vertex v)       { return verts_[v]; }
      const vertex_node& node(vertex v) const { return verts_[v]; }

      edge_node&       get_edge(edge e)       { return edges_[e]; }
      const edge_node& get_edge(edge e) const { return edges_[e]; }

      // Helper functions
      edge find_edge(vertex u, vertex v) const;

      template<typename S, typename P>
        edge find_endpoints(const S& seq, P pred) const;

      void link_edge(vertex u, vertex v, edge e);
    
    private:
      vertex_set verts_;
      edge_set   edges_;
    };

  // Returns true if the an edge {u, v} is in the graph.
  template<typename V, typename E>
    inline auto
    undirected_adjacency_vector<V, E>::operator()(vertex u, vertex v) const -> edge
    {
      if (degree(u) <= degree(v))
        return find_edge(u, v);
      else
        return find_edge(v, u);
    }

  // Return an handle to the first edge connecting u to v, or an invalid handle
  // if no such edges exist.
  //
  // Note that, if u and v are connected, then the edge was added as either
  // (u, v) or (v, u). We prefer to search the vertex with the smaller degree
  // for evidence of either construction.
  template<typename V, typename E>
    inline auto
    undirected_adjacency_vector<V, E>::find_edge(vertex u, vertex v) const -> edge
    {
      using P = has_endpoints<this_type>;
      const vertex_node& n = node(v);
      return find_endpoints(n.edges(), P(*this, u, v));
    }

  // Return an edge whose endpoints satisfy the given predicate. The primary
  // function of this operation is to find endpoints with source/target pairs.
  template<typename V, typename E>
    template<typename S, typename P>
      inline auto
      undirected_adjacency_vector<V, E>::
        find_endpoints(const S& seq, P pred) const -> edge
        {
          auto i = find_if(seq, pred);
          return i == seq.end() ? edge() : *i;
        }


  // Add a vertex to the graph, returning a handle to the new object. If
  // V is a user-supplied type, its value is default constructed.
  template<typename V, typename E>
    inline auto
    undirected_adjacency_vector<V, E>::add_vertex() -> vertex
    {
      return emplace_vertex();
    }

  template<typename V, typename E>
    inline auto
    undirected_adjacency_vector<V, E>::add_vertex(V&& x) -> vertex
    {
      return emplace_vertex(std::move(x));
    }

  template<typename V, typename E>
    inline auto
    undirected_adjacency_vector<V, E>::add_vertex(const V& x) -> vertex
    {
      return emplace_vertex(x);
    }

  template<typename V, typename E>
    template<typename... Args>
      inline auto
      undirected_adjacency_vector<V, E>::emplace_vertex(Args&&... args) -> vertex
      {
        vertex v = verts_.size();
        verts_.emplace_back(std::forward<Args>(args)...);
        return v;
      }

  // Add a defaul edge from u to v.
  template<typename V, typename E>
    inline auto
    undirected_adjacency_vector<V, E>::add_edge(vertex u, vertex v) -> edge
    {
      return emplace_edge(u, v);
    }

  // Move x into an edge connecting u to v.
  template<typename V, typename E>
    inline auto
    undirected_adjacency_vector<V, E>::add_edge(vertex u, vertex v, E&& x) -> edge
    {
      return emplace_edge(u, v, std::move(x));
    }

  // Copy x into an edge connecting u to v.
  template<typename V, typename E>
    inline auto
    undirected_adjacency_vector<V, E>::add_edge(vertex u, vertex v, const E& x) -> edge
    {
      return emplace_edge(u, v, x);
    }

  template<typename V, typename E>
    template<typename... Args>
      inline auto
      undirected_adjacency_vector<V, E>::
        emplace_edge(vertex u, vertex v, Args&&... args) -> edge
      {
        edge e = edges_.size();
        edges_.emplace_back(u, v, std::forward<Args>(args)...);
        link_edge(u, v, e);
        return e;
      }

  template<typename V, typename E>
    inline void
    undirected_adjacency_vector<V, E>::link_edge(vertex u, vertex v, edge e)
    {
      vertex_node& un = node(u);
      vertex_node& vn = node(v);
      un.insert(e);
      vn.insert(e);
    }

  // Retrun a range over the vertex set.
  template<typename V, typename E>
    inline auto
    undirected_adjacency_vector<V, E>::vertices() const -> vertex_range
    {
      return {vertex_iter(verts_.begin()), vertex_iter(verts_.end())};
    }

  // Return a range over the edge set.
  template<typename V, typename E>
    inline auto
    undirected_adjacency_vector<V, E>::edges() const -> edge_range
    {
      return {edge_iter(edges_.begin()), edge_iter(edges_.end())};
    }

  // Return a range over the out edges of the vertex v.
  template<typename V, typename E>
    inline auto
    undirected_adjacency_vector<V, E>::edges(vertex v) const -> incidence_range
    {
      const vertex_node& vn = node(v);
      return {incidence_iter(vn.begin()), incidence_iter(vn.end())};
    }

} // namespace origin

#endif
