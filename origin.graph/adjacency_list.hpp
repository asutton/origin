// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_GRAPH_ADJACENCY_LIST_HPP
#define ORIGIN_GRAPH_ADJACENCY_LIST_HPP

#include <cassert>

#include <queue>
#include <tuple>
#include <vector>

#include <origin/core/concepts.hpp>

#include <origin.graph/handle.hpp>
#include <origin.graph/graph.hpp>
#include <origin.graph/io.hpp>

#include <origin.graph/adjacency_list.impl/pool.hpp>

namespace origin
{

  namespace adjacency_list_impl
  {
    // ---------------------------------------------------------------------- //
    //                            Handle Iterator

    // The handle accessor provides alternative accessors for the different
    // kinds of handle iterators required by the adjacency list data structure.
    template<typename C, typename H>
      struct handle_accessor;

    template<typename T, typename H>
      struct handle_accessor<pool<T>, H>
      {
        using I = Iterator_of<const pool<T>>;

        H get(I i) const { return i.index(); }
      };

    template<typename T, typename H>
      struct handle_accessor<std::vector<T>, H>
      {
        using I = Iterator_of<const std::vector<T>>;

        H get(I i) const { return *i; }
      };


    // The handle iterator wraps a constant iterator of the container type C and
    // returns handles of type H when dereferenced.
    template<typename C, typename H>
      struct handle_iterator : handle_accessor<C, H>
      {
        using handle_type = H;
        using iterator = Iterator_of<const C>;

        handle_iterator(iterator i)
          : iter(i)
        { }

        handle_type operator*() const { return this->get(iter); }

        handle_iterator& operator++();
        handle_iterator  operator++(int);

        iterator iter;
      };


    template<typename C, typename H>
      inline handle_iterator<C, H>&
      handle_iterator<C, H>::operator++()
      {
        ++iter;
        return *this;
      }

    template<typename C, typename H>
      inline handle_iterator<C, H>
      handle_iterator<C, H>::operator++(int)
      {
        handle_iterator tmp = *this;
        ++iter;
        return tmp;
      }

    // Equality
    template<typename C, typename H>
      inline bool
      operator==(const handle_iterator<C, H>& a, const handle_iterator<C, H>& b)
      {
        return a.iter == b.iter;
      }

    template<typename C, typename H>
      inline bool
      operator!=(const handle_iterator<C, H>& a, const handle_iterator<C, H>& b)
      {
        return a.iter != b.iter;
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

        std::size_t& source()       { return std::get<0>(data); }
        std::size_t  source() const { return std::get<0>(data); }

        std::size_t& target()       { return std::get<1>(data); }
        std::size_t  target() const { return std::get<1>(data); }

        E&       value()       { return std::get<2>(data); }
        const E& value() const { return std::get<2>(data); }

        std::tuple<vertex_handle, vertex_handle,  E> data;
      };

    // An (incident) edge list is a vector of indexes.
    using edge_list = std::vector<edge_handle>;

    // An alias for the edge pool.
    template<typename E>
      using edge_pool = pool<edge<E>>;

    // An alias for the vertex iterator.
    template<typename E>
      using edge_iterator = handle_iterator<edge_pool<E>, edge_handle>;

    // An alias for the edge range.
    template<typename E>
      using edge_range = bounded_range<edge_iterator<E>>;

    // An alias for the incident edge iterator.
    using incidence_iterator = handle_iterator<edge_list, edge_handle>;

    // An alias for the icident edge range.
    using incidence_range = bounded_range<incidence_iterator>;

  } // namespace adjacency_list_impl



  // ------------------------------------------------------------------------ //
  //                                                        [graph.adj_list.dir]
  //                        Directed Adjacency List
  //
  // A directed adjacency list...
  //


  namespace directed_adjacency_list_impl
  {
    // Imports
    using adjacency_list_impl::pool;
    using adjacency_list_impl::handle_iterator;
    using adjacency_list_impl::edge_list;


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

        // Out edges
        std::size_t out_degree() const { return out().size(); }

        void insert_out(edge_handle e) { insert_edge(out(), e); }
        void erase_out(edge_handle e)  { erase_edge(out(), e); }

        iterator begin_out() { return out().begin(); }
        iterator end_out()   { return out().end(); }
        const_iterator begin_out() const { return out().begin(); }
        const_iterator end_out() const   { return out().end(); }

        // In edges
        std::size_t in_degree() const { return in().size(); }

        void insert_in(edge_handle e) { insert_edge(in(), e); }
        void erase_in(edge_handle e)  { erase_edge(in(), e); }

        iterator begin_in() { return in().begin(); }
        iterator end_in()   { return in().end(); }
        const_iterator begin_in() const { return in().begin(); }
        const_iterator end_in() const   { return in().end(); }

        // Helper functions
        void insert_edge(edge_list& l, edge_handle e);
        void erase_edge(edge_list& l, edge_handle e);

      public:
        std::tuple<edge_list, edge_list, V> data;
      };

    template<typename V>
      inline void
      vertex<V>::insert_edge(edge_list& l, edge_handle e)
      {
        l.push_back(e);
      }

    template<typename V>
      inline void
      vertex<V>::erase_edge(edge_list& l, edge_handle e)
      {
        auto i = std::find(l.begin(), l.end(), e);
        if (i != l.end())
          l.erase(i);
      }

    // A vertex set is a pool of vertices.
    template<typename V>
      using vertex_pool = pool<vertex<V>>;

    // An alias for the vertex iterator.
    template<typename V>
      using vertex_iterator = handle_iterator<vertex_pool<V>, vertex_handle>;

    // An alias for the vertex range.
    template<typename V>
      using vertex_range = bounded_range<vertex_iterator<V>>;

  } // namespace directed_adjacency_list_impl


  // Implementation of a diretected adjacency list.
  template<typename V = empty_t, typename E = empty_t>
    class directed_adjacency_list
    {
      using this_type = directed_adjacency_list<V, E>;

      using vertex_node = directed_adjacency_list_impl::vertex<V>;
      using vertex_set = directed_adjacency_list_impl::vertex_pool<V>;
      using vertex_iter = directed_adjacency_list_impl::vertex_iterator<V>;

      using edge_node = adjacency_list_impl::edge<E>;
      using edge_set = adjacency_list_impl::edge_pool<E>;
      using edge_iter = adjacency_list_impl::edge_iterator<E>;

      using incidence_iter = adjacency_list_impl::incidence_iterator;
    public:
      using vertex = vertex_handle;
      using vertex_range = directed_adjacency_list_impl::vertex_range<V>;

      using edge = edge_handle;
      using edge_range = adjacency_list_impl::edge_range<E>;

      using incidence_range = adjacency_list_impl::incidence_range;


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
        vertex emplace_vertex(Args&&... args);

      void remove_vertex(vertex v);
      void remove_vertices();

      // Edge set
      edge add_edge(vertex u, vertex v);
      edge add_edge(vertex u, vertex v, E&& x);
      edge add_edge(vertex u, vertex v, const E& x);

      template<typename... Args>
        edge emplace_edge(vertex u, vertex v, Args&&... args);

      void remove_edge(edge e);
      void remove_edge(vertex u, vertex v);
      void remove_edges(vertex u, vertex v);
      void remove_edges(vertex v);
      void remove_edges();

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
      void unlink_edge(vertex u, vertex v, edge e);
      void unlink_out_edge(vertex u, vertex v);
      void unlink_in_edge(vertex u, vertex v);
      void unlink_out_edges(vertex u, vertex v);
      void unlink_in_edges(vertex u, vertex v);
      void unlink_target(edge e);
      void unlink_source(edge e);

      template<typename S, typename P>
        void unlink_first_edge(S& seq, P pred);

      template<typename S1, typename S2, typename P>
        void unlink_multi_edge(S1& seq1, S2& seq2, P pred);

    private:
      vertex_set verts_;
      edge_set   edges_;
    };


  template<typename V, typename E>
    inline auto
    directed_adjacency_list<V, E>::operator()(vertex u, vertex v) const -> edge
    {
      if (out_degree(u) <= in_degree(v))
        return find_out_edge(u, v);
      else
        return find_in_edge(u, v);
    }

  template<typename V, typename E>
    inline auto
    directed_adjacency_list<V, E>::find_out_edge(vertex u, vertex v) const -> edge
    {
      using P = has_target<this_type>;
      const vertex_node& n = node(u);
      return find_edge(n.out(), P(*this, v));
    }

  template<typename V, typename E>
    inline auto
    directed_adjacency_list<V, E>::find_in_edge(vertex u, vertex v) const -> edge
    {
      using P = has_source<this_type>;
      const vertex_node& n = node(v);
      return find_edge(n.in(), P(*this, u));
    }

  template<typename V, typename E>
    template<typename S, typename P>
      inline auto
      directed_adjacency_list<V, E>::find_edge(const S& seq, P pred) const -> edge
      {
        auto i = find_if(seq, pred);
        return i == seq.end() ? edge() : *i;
      }

  // Add a vertex to the graph, returning a handle to the new object. If
  // V is a user-supplied type, its value is default constructed.
  template<typename V, typename E>
    inline auto
    directed_adjacency_list<V, E>::add_vertex() -> vertex
    {
      return verts_.emplace();
    }

  template<typename V, typename E>
    inline auto
    directed_adjacency_list<V, E>::add_vertex(V&& x) -> vertex
    {
      return verts_.emplace(std::move(x));
    }

  template<typename V, typename E>
    inline auto
    directed_adjacency_list<V, E>::add_vertex(const V& x) -> vertex
    {
      return verts_.emplace(x);
    }

  template<typename V, typename E>
    template<typename... Args>
      inline auto
      directed_adjacency_list<V, E>::emplace_vertex(Args&&... args) -> vertex
      {
        return verts_.emplace(std::forward<Args>(args)...);
      }

  template<typename V, typename E>
    inline void
    directed_adjacency_list<V, E>::remove_vertex(vertex v)
    {
      remove_edges(v);
      verts_.erase(v);
    }

  template<typename V, typename E>
    inline void
    directed_adjacency_list<V, E>::remove_vertices()
    {
      edges_.clear();
      verts_.clear();
    }

  // Add a defaul edge from u to v.
  template<typename V, typename E>
    inline auto
    directed_adjacency_list<V, E>::add_edge(vertex u, vertex v) -> edge
    {
      return emplace_edge(u, v);
    }

  // Move x into an edge connecting u to v.
  template<typename V, typename E>
    inline auto
    directed_adjacency_list<V, E>::add_edge(vertex u, vertex v, E&& x) -> edge
    {
      return emplace_edge(u, v, std::move(x));
    }

  // Copy x into an edge connecting u to v.
  template<typename V, typename E>
    inline auto
    directed_adjacency_list<V, E>::add_edge(vertex u, vertex v, const E& x) -> edge
    {
      return emplace_edge(u, v, x);
    }

  template<typename V, typename E>
    template<typename... Args>
      inline auto
      directed_adjacency_list<V, E>::
        emplace_edge(vertex u, vertex v, Args&&... args) -> edge
      {
        edge e = edges_.emplace(u, v, std::forward<Args>(args)...);
        link_edge(u, v, e);
        return e;
      }

  template<typename V, typename E>
    inline void
    directed_adjacency_list<V, E>::link_edge(vertex u, vertex v, edge e)
    {
      vertex_node& un = node(u);
      vertex_node& vn = node(v);
      un.insert_out(e);
      vn.insert_in(e);
    }

  // Remove the specified edge from the graph.
  template<typename V, typename E>
    inline void
    directed_adjacency_list<V, E>::remove_edge(edge e)
    {
      unlink_edge(source(e), target(e), e);
    }

  // Unlink the given edge from the source and target vertices, and erase
  // it from the edge set.
  template<typename V, typename E>
    inline void
    directed_adjacency_list<V, E>::unlink_edge(vertex u, vertex v, edge e)
    {
      vertex_node& un = node(u);
      vertex_node& vn = node(v);
      un.erase_out(e);
      vn.erase_in(e);
      edges_.erase(e);
    }


  // Remove the first edge connecting u to v.
  template<typename V, typename E>
    inline void
    directed_adjacency_list<V, E>::remove_edge(vertex u, vertex v)
    {
      if (out_degree(u) <= in_degree(v))
        unlink_out_edge(u, v);
      else
        unlink_in_edge(u, v);
    }

  template<typename V, typename E>
    inline void
    directed_adjacency_list<V, E>::unlink_out_edge(vertex u, vertex v)
    {
      using P = has_target<this_type>;
      vertex_node& un = node(u);
      unlink_first_edge(un.out(), P(*this, v));
    }

  template<typename V, typename E>
    inline void
    directed_adjacency_list<V, E>::unlink_in_edge(vertex u, vertex v)
    {
      using P = has_source<this_type>;
      vertex_node& vn = node(v);
      unlink_first_edge(vn.in(), P(*this, u));
    }

  template<typename V, typename E>
    template<typename S, typename P>
      inline void
      directed_adjacency_list<V, E>::unlink_first_edge(S& seq, P pred)
      {
        auto i = find_if(seq, pred);
        if (i != seq.end());
          remove_edge(*i);
      }

  // Remove all edges connecting u to v.
  template<typename V, typename E>
    inline void
    directed_adjacency_list<V, E>::remove_edges(vertex u, vertex v)
    {
      if (out_degree(u) <= in_degree(v))
        unlink_out_edges(u, v);
      else
        unlink_in_edges(u, v);
    }

  template<typename V, typename E>
    inline void
    directed_adjacency_list<V, E>::unlink_out_edges(vertex u, vertex v)
    {
      using P = has_target<this_type>;
      vertex_node& un = node(u);
      vertex_node& vn = node(v);
      unlink_multi_edge(un.out(), vn.in(), P(*this, v));
    }

  template<typename V, typename E>
    inline void
    directed_adjacency_list<V, E>::unlink_in_edges(vertex u, vertex v)
    {
      using P = has_source<this_type>;
      vertex_node& un = node(u);
      vertex_node& vn = node(v);
      unlink_multi_edge(vn.in(), un.out(), P(*this, u));
    }

  // Remove all edges from seq1 that are connected to seq2.
  template<typename V, typename E>
    template<typename S1, typename S2, typename P>
      inline void
      directed_adjacency_list<V, E>::unlink_multi_edge(S1& seq1, S2& seq2, P pred)
      {
        // Partition the 1st sequence by the given predicate into "save" and
        // "erase" components.
        //
        // NOTE: We may want this to be a stable partition... not sure. It
        // seems like the saved edges are not reordered by the partitioning.
        auto i = partition(seq1, negate(pred));
        for (auto j = i; j != seq1.end(); ++j) {
          // Remove those edges from the in 2nd sequence.
          auto k = remove(seq2, *j);
          seq2.erase(k, seq2.end());

          // Erase the edge from the graph's edge set.
          edges_.erase(*j);
        }

        // Finally, erase those edges from the first sequence.
        seq1.erase(i, seq1.end());
      }


  // Remove all edges incident to the vertex v.
  template<typename V, typename E>
    inline void
    directed_adjacency_list<V, E>::remove_edges(vertex v)
    {
      vertex_node& vn = node(v);

      // Clear the out edges
      for (auto e : vn.out())
        unlink_target(e);
      vn.out().clear();

      // Clear the in edges
      for(auto e : vn.in())
        unlink_source(e);
      vn.in().clear();
    }

  template<typename V, typename E>
    inline void
    directed_adjacency_list<V, E>::unlink_target(edge e)
    {
      vertex_node& t = node(target(e));
      auto i = find(t.in(), e);
      t.in().erase(i);
      edges_.erase(e);
    }

  // Note that loops will not result in the double erasure of an edge. The
  // edge is initially erased in unlink_source, and the erase operation
  // here will have no effect.
  template<typename V, typename E>
    inline void
    directed_adjacency_list<V, E>::unlink_source(edge e)
    {
      vertex_node& t = node(source(e));
      auto i = find(t.out(), e);
      t.out().erase(i);
      edges_.erase(e);
    }


  // Remove all edges from a graph, making it empty.
  template<typename V, typename E>
    inline void
    directed_adjacency_list<V, E>::remove_edges()
    {
      for (vertex_node& n : verts_) {
        n.out().clear();
        n.in().clear();
      }
      edges_.clear();
    }

  // Retrun a range over the vertex set.
  template<typename V, typename E>
    inline auto
    directed_adjacency_list<V, E>::vertices() const -> vertex_range
    {
      return {vertex_iter(verts_.begin()), vertex_iter(verts_.end())};
    }

  // Return a range over the edge set.
  template<typename V, typename E>
    inline auto
    directed_adjacency_list<V, E>::edges() const -> edge_range
    {
      return {edge_iter(edges_.begin()), edge_iter(edges_.end())};
    }

  // Return a range over the out edges of the vertex v.
  template<typename V, typename E>
    inline auto
    directed_adjacency_list<V, E>::out_edges(vertex v) const -> incidence_range
    {
      const vertex_node& vn = node(v);
      return {incidence_iter(vn.begin_out()), incidence_iter(vn.end_out())};
    }

  template<typename V, typename E>
    inline auto
    directed_adjacency_list<V, E>::in_edges(vertex v) const -> incidence_range
    {
      const vertex_node& vn = node(v);
      return {incidence_iter(vn.begin_in()), incidence_iter(vn.end_in())};
    }




  // ------------------------------------------------------------------------ //
  //                                                      [graph.adj_list.undir]
  //                        Undirected Adjacency List
  //
  // A directed adjacency list...

  namespace undirected_adjacency_list_impl
  {
    using origin::adjacency_list_impl::pool;
    using origin::adjacency_list_impl::handle_iterator;
    using origin::adjacency_list_impl::edge_list;

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

        void insert(std::size_t e);
        void erase(std::size_t e);

        iterator begin() { return edges().begin(); }
        iterator end()   { return edges().end(); }
        const_iterator begin() const { return edges().begin(); }
        const_iterator end() const   { return edges().end(); }

      public:
        std::tuple<edge_list, V> data;
      };

    template<typename V>
      inline void
      vertex<V>::insert(std::size_t e)
      {
        edges().push_back(e);
      }

    template<typename V>
      inline void
      vertex<V>::erase(std::size_t e)
      {
        auto i = std::find(begin(), end(), e);
        if (i != end())
          edges().erase(i);
      }

    // A vertex set is a pool of vertices.
    template<typename V>
      using vertex_pool = pool<vertex<V>>;

    // An alias for the vertex iterator.
    template<typename V>
      using vertex_iterator = handle_iterator<vertex_pool<V>, vertex_handle>;

    // An alias for the vertex range.
    template<typename V>
      using vertex_range = bounded_range<vertex_iterator<V>>;

  } // namespace undirected_adjacency_list_impl


  // Implementation of the undirected adjacency list.
  template<typename V = empty_t, typename E = empty_t>
    class undirected_adjacency_list
    {
      using this_type = undirected_adjacency_list<V, E>;

      using vertex_node = undirected_adjacency_list_impl::vertex<V>;
      using vertex_set = undirected_adjacency_list_impl::vertex_pool<V>;
      using vertex_iter = undirected_adjacency_list_impl::vertex_iterator<V>;

      using edge_node = adjacency_list_impl::edge<E>;
      using edge_set = adjacency_list_impl::edge_pool<E>;
      using edge_iter = adjacency_list_impl::edge_iterator<E>;

      using incidence_iter = adjacency_list_impl::incidence_iterator;
    public:
      using vertex = vertex_handle;
      using vertex_range = undirected_adjacency_list_impl::vertex_range<V>;

      using edge = edge_handle;
      using edge_range = adjacency_list_impl::edge_range<E>;

      using incidence_range = adjacency_list_impl::incidence_range;


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

      void remove_vertex(vertex v);
      void remove_vertices();

      // Edge set
      edge add_edge(vertex u, vertex v);
      edge add_edge(vertex u, vertex v, E&& x);
      edge add_edge(vertex u, vertex v, const E& x);

      template<typename... Args>
        edge emplace_edge(vertex u, vertex v, Args&&... args);

      void remove_edge(edge e);
      void remove_edge(vertex u, vertex v);
      void remove_edges(vertex u, vertex v);
      void remove_edges(vertex v);
      void remove_edges();

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
      void unlink_loop(vertex v, edge e);
      void unlink_edge(vertex u, vertex v, edge e);
      void unlink_first_loop(vertex v);
      void unlink_first_edge(vertex u, vertex v);
      void unlink_multi_loop(vertex v);
      void unlink_multi_edge(vertex u, vertex v);

      template<typename S, typename I>
        void erase_loop(S& seq, I iter);

      template<typename S, typename I>
        void erase_edge(S& seq1, I iter1, S& seq2, I iter2);

    private:
      vertex_set verts_;
      edge_set   edges_;
    };

  // Returns true if the an edge {u, v} is in the graph.
  template<typename V, typename E>
    inline auto
    undirected_adjacency_list<V, E>::operator()(vertex u, vertex v) const -> edge
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
    undirected_adjacency_list<V, E>::find_edge(vertex u, vertex v) const -> edge
    {
      using P = has_endpoints<this_type>;
      const vertex_node& n = node(v);
      return find_endpoints(n.edges(), P(*this, u, v));
    }

  // Return an iterator to the the first incident edge whose end (either
  // source or target) is equal to v.
  template<typename V, typename E>
    template<typename S, typename P>
      inline auto
      undirected_adjacency_list<V, E>::
        find_endpoints(const S& seq, P pred) const -> edge
      {
        auto i = find_if(seq, pred);
        return i == seq.end() ? edge() : *i;
      }


  // Add a vertex to the graph, returning a handle to the new object. If
  // V is a user-supplied type, its value is default constructed.
  template<typename V, typename E>
    inline auto
    undirected_adjacency_list<V, E>::add_vertex() -> vertex
    {
      return verts_.emplace();
    }

  template<typename V, typename E>
    inline auto
    undirected_adjacency_list<V, E>::add_vertex(V&& x) -> vertex
    {
      return verts_.emplace(std::move(x));
    }

  template<typename V, typename E>
    inline auto
    undirected_adjacency_list<V, E>::add_vertex(const V& x) -> vertex
    {
      return verts_.emplace(x);
    }

  template<typename V, typename E>
    template<typename... Args>
      inline auto
      undirected_adjacency_list<V, E>::emplace_vertex(Args&&... args) -> vertex
      {
        return verts_.emplace(std::forward<Args>(args)...);
      }


  template<typename V, typename E>
    inline void
    undirected_adjacency_list<V, E>::remove_vertex(vertex v)
    {
      remove_edges(v);
      verts_.erase(v);
    }

  template<typename V, typename E>
    inline void
    undirected_adjacency_list<V, E>::remove_vertices()
    {
      edges_.clear();
      verts_.clear();
    }

  // Add a defaul edge from u to v.
  template<typename V, typename E>
    inline auto
    undirected_adjacency_list<V, E>::add_edge(vertex u, vertex v) -> edge
    {
      return emplace_edge(u, v);
    }

  // Move x into an edge connecting u to v.
  template<typename V, typename E>
    inline auto
    undirected_adjacency_list<V, E>::add_edge(vertex u, vertex v, E&& x) -> edge
    {
      return emplace_edge(u, v, std::move(x));
    }

  // Copy x into an edge connecting u to v.
  template<typename V, typename E>
    inline auto
    undirected_adjacency_list<V, E>::add_edge(vertex u, vertex v, const E& x) -> edge
    {
      return emplace_edge(u, v, x);
    }

  template<typename V, typename E>
    template<typename... Args>
      inline auto
      undirected_adjacency_list<V, E>::
        emplace_edge(vertex u, vertex v, Args&&... args) -> edge
      {
        edge e = edges_.emplace(u, v, std::forward<Args>(args)...);
        link_edge(u, v, e);
        return e;
      }

  template<typename V, typename E>
    inline void
    undirected_adjacency_list<V, E>::link_edge(vertex u, vertex v, edge e)
    {
      vertex_node& un = node(u);
      vertex_node& vn = node(v);
      un.insert(e);
      vn.insert(e);
    }

  // Remove the specified edge from the graph.
  template<typename V, typename E>
    inline void
    undirected_adjacency_list<V, E>::remove_edge(edge e)
    {
      vertex u = source(e);
      vertex v = target(e);
      if (u == v)
        unlink_loop(u, e);
      else
        unlink_edge(u, v, e);
    }

  // Unlink the given edge from the vertex, when the edge is looped.
  template<typename V, typename E>
    inline void
    undirected_adjacency_list<V, E>::unlink_loop(vertex v, edge e)
    {
      vertex_node& n = node(v);
      auto i = find(n.edges(), e);
      if (i != n.end())
        erase_loop(n.edges(), i);
    }

  // Erase the loop edge referred to by the edge list iterator i.
  template<typename V, typename E>
    template<typename S, typename I>
      inline void
      undirected_adjacency_list<V, E>::erase_loop(S& seq, I iter)
      {
        edges_.erase(*iter);
        seq.erase(iter, std::next(iter, 2));
      }

  // Unlink the given edge from the source and target vertices, and erase
  // it from the edge set.
  template<typename V, typename E>
    inline void
    undirected_adjacency_list<V, E>::unlink_edge(vertex u, vertex v, edge e)
    {
      vertex_node& un = node(u);
      vertex_node& vn = node(v);

      // Find the edge in the corresponding edge lists, and then erase them.
      auto i = find(un.edges(), e);
      auto j = find(vn.edges(), e);
      if (i != un.end())
        erase_edge(un.edges(), i, vn.edges(), j);
    }

  // Erase the edge e from the graph by removing the endpoints and the edge
  // object.
  template<typename V, typename E>
    template<typename S, typename I>
      inline void
      undirected_adjacency_list<V, E>::erase_edge(S& seq1, I iter1, S& seq2, I iter2)
        {
          edges_.erase(*iter1);
          seq1.erase(iter1);
          seq2.erase(iter2);
        }

  // Remove the first edge connecting u to v.
  template<typename V, typename E>
    inline void
    undirected_adjacency_list<V, E>::remove_edge(vertex u, vertex v)
    {
      if (u == v)
        unlink_first_loop(v);
      else if (degree(u) <= degree(v))
        unlink_first_edge(u, v);
      else
        unlink_first_edge(v, u);
    }

  // Find and remove the first loop connecting v to itself.
  template<typename V, typename E>
    inline void
    undirected_adjacency_list<V, E>::unlink_first_loop(vertex v)
    {
      using P = has_endpoint<this_type>;
      vertex_node& n = node(v);
      auto i = find_if(n.edges(), P(*this, v));
      if (i != n.end())
        erase_loop(n.edges(), i);
    }

  // Find and remove the first edge connecting u to v.
  template<typename V, typename E>
    inline void
    undirected_adjacency_list<V, E>::unlink_first_edge(vertex u, vertex v)
    {
      using P = has_endpoints<this_type>;
      vertex_node& un = node(u);
      vertex_node& vn = node(v);

      // Find the first edge with u and v as endpoints. If we didn't find
      // it, just return.
      auto i = find_if(un.edges(), P(*this, u, v));
      if (i == un.end())
        return;

      // Find the corresponding edge in v's list. Note that *i must exist
      // in the incidence list of vn, otherwise, the graph is ill-formed.
      auto j = find(vn.begin(), vn.end(), *i);
      assert(j != vn.end());
      erase_edge(un.edges(), i, vn.edges(), j);
    }

  // Remove all edges connecting u to v.
  template<typename V, typename E>
    inline void
    undirected_adjacency_list<V, E>::remove_edges(vertex u, vertex v)
    {
      if (u == v)
        unlink_multi_loop(u);
      else
        unlink_multi_edge(u, v);
    }

  template<typename V, typename E>
    inline void
    undirected_adjacency_list<V, E>::unlink_multi_loop(vertex v)
    {
      using P = is_looped<this_type>;
      vertex_node& n = node(v);
      auto i = partition(n, negate(P(*this, v)));
      for (auto j = i; j != n.end(); advance(j, 2))
        edges_.erase(*j);
      n.edges().erase(i, n.end());
    }

  template<typename V, typename E>
    inline void
    undirected_adjacency_list<V, E>::unlink_multi_edge(vertex u, vertex v)
    {
      using P = has_endpoints<this_type>;
      vertex_node& un = node(u);
      vertex_node& vn = node(v);

      auto i = partition(un.edges(), negate(P(*this, u, v)));
      auto j = partition(vn.edges(), negate(P(*this, v, u)));
      for (auto k = i; k != un.end(); ++k)
        edges_.erase(*k);
      un.edges().erase(i, un.end());
      vn.edges().erase(j, vn.end());
    }


  // Remove all edges incident to the vertex v.
  template<typename V, typename E>
    inline void
    undirected_adjacency_list<V, E>::remove_edges(vertex v)
    {
      vertex_node& vn = node(v);

      // Clear the incident edges by removing each edge from the incidence
      // list of its corresponding endpoint. Handle loops differenty.
      //
      // TODO: This looks a little dense. It's also a little inefficient
      // in the case of multigraphs. Ideally, we should find the set of
      // edges connecting u to v and erase those in a single block.
      auto i = vn.begin();
      while (i != vn.end()) {
        if (is_loop(*this, *i)) {
          edges_.erase(*i);
          std::advance(i, 2);
        } else {
          vertex_node& n = node(opposite(*this, *i, v));
          auto j = find(n.edges(), *i);
          if (j != n.end()) {
            n.edges().erase(j);
            edges_.erase(*i);
          }
          ++i;
        }
      }
      vn.edges().clear();
    }


  // Remove all edges from a graph, making it empty.
  template<typename V, typename E>
    inline void
    undirected_adjacency_list<V, E>::remove_edges()
    {
      for (vertex_node& n : verts_)
        n.edges().clear();
      edges_.clear();
    }

  // Retrun a range over the vertex set.
  template<typename V, typename E>
    inline auto
    undirected_adjacency_list<V, E>::vertices() const -> vertex_range
    {
      return {vertex_iter(verts_.begin()), vertex_iter(verts_.end())};
    }

  // Return a range over the edge set.
  template<typename V, typename E>
    inline auto
    undirected_adjacency_list<V, E>::edges() const -> edge_range
    {
      return {edge_iter(edges_.begin()), edge_iter(edges_.end())};
    }

  // Return a range over the out edges of the vertex v.
  template<typename V, typename E>
    inline auto
    undirected_adjacency_list<V, E>::edges(vertex v) const -> incidence_range
    {
      const vertex_node& vn = node(v);
      return {incidence_iter(vn.begin()), incidence_iter(vn.end())};
    }


} // namespace origin

#endif
