// Copyright (c) 2008-2010 Kent State University
// Copyright (c) 2011-2012 Texas A&M University
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_GRAPH_EDGE_HPP
#define ORIGIN_GRAPH_EDGE_HPP

#include <iterator>
#include <functional>

#include <origin/graph/handle.hpp>
#include <origin/graph/vertex.hpp>
#include <origin/range.hpp>
#include <origin/graph/traits.hpp>

namespace origin
{
  // Edge handle
  // The edge handle is an opaque reference to a edge object in a graph. 
  //
  // Note that we explicitly subclass the handle<T> so that we don't confuse
  // edge and vertex handles. They are incompatible types, even if they
  // represent the same set of values.
  template<typename T>
    class edge_handle
    {
    public:
      using value_type = Value_type<handle<T>>;
      
      edge_handle() : impl{} { }
      edge_handle(value_type n) : impl{n} { }

      // Equality_comparable
      bool operator==(edge_handle v) const { return impl == v.impl; }
      bool operator!=(edge_handle v) const { return impl != v.impl; }
      
      // Totally_ordered
      bool operator<(edge_handle v) const  { return impl < v.impl; }
      bool operator>(edge_handle v) const  { return impl > v.impl; }
      bool operator<=(edge_handle v) const { return impl <= v.impl; }
      bool operator>=(edge_handle v) const { return impl >= v.impl; }

      // Boolean
      explicit operator bool() const { return (bool)impl; }
      
      // Ordinal
      // Only if Ordinal<T>
      std::size_t ord() const { return impl.ord(); }
      
      // Hashable
      std::size_t hash() const { return impl.hash(); }
      
      // Returns the underlying value.
      value_type  value() const { return impl.value; }

      // The handle implementation.
      handle<T> impl;
    };

  
    
  // Edge iterator
  // The edge iterator provides an iterator over successive vertices.
  template<typename T>
    using edge_iterator = handle_iterator<edge_handle<T>>;
    
    

  // Undirected edge handle
  // The undirected edge handle is a triple containing an edge handle, and two
  // vertex handles: the source and target vertices, respectively. Note that 
  // equality and inequality comparisons are predicated on the underlying edge 
  // and do not include the end points in comparison.
  template<typename T>
    class undirected_edge_handle
    {
    public:
      // Default constructor
      undirected_edge_handle() : edge{}, source{}, target{} { }

      // Initialize the graph over a triple of values describing the current
      // edge handle, the source vertex, and the target vertex.
      undirected_edge_handle(edge_handle<T> e, vertex_handle<T> s, vertex_handle<T> t)
        : edge{e}, source{s}, target{t}
      { }

      // Equality_comparable
      bool operator==(const undirected_edge_handle& x) const { return edge == x.edge; }
      bool operator!=(const undirected_edge_handle& x) const { return edge != x.edge; }

      // Totally_ordered
      bool operator<(const undirected_edge_handle& x) const { return edge < x.edge; }
      bool operator>(const undirected_edge_handle& x) const { return edge > x.edge; }
      bool operator<=(const undirected_edge_handle& x) const { return edge <= x.edge; }
      bool operator>=(const undirected_edge_handle& x) const { return edge >= x.edge; }

      // Boolean
      explicit operator bool() const { return (bool)edge; }
      
      // Ordinal
      // Only if Ordinal<T>.
      std::size_t ord() const { return edge.ord(); }
      
      // Hashable
      std::size_t hash() const { return hash_value(edge); }

      edge_handle<T> edge;
      vertex_handle<T> source;
      vertex_handle<T> target;
    };

    
    
  // Undirected edge iterator
  // The undirected edge iterator is used to iterate over the edges in the
  // edge set of an undirected graph.
  //
  // FIXME: This is totally broken. It needs to chain the underlying out
  // and in edge iterators in a more natural fashion. We can generally
  template<typename G>
    class undirected_edge_iterator
    {
    /*
    public:
      using value_type = Edge_type<G>;
      using reference = const Edge_type<G>&;
      using pointer = const Edge_type<G>*;
      using difference_type = std::ptrdiff_t;
      using iterator_category = std::random_access_iterator_tag;

      undirected_edge_iterator()
        : graph{nullptr}, handle{}
      { }
      
      undirected_edge_iterator(G& g, const Edge_type<G>& e)
        : graph{&g}, handle{e}
      { }

      // Readable
      reference operator*() const { return edge; }
      
      // Equality_comparable
      bool operator==(const undirected_edge_iterator& x) const { return handle == x.handle; }
      bool operator!=(const undirected_edge_iterator& x) const { return handle != x.handle; }

      // Totally_ordered
      bool operator<(const undirected_edge_iterator& x) const { return handle == x.handle; }
      bool operator>(const undirected_edge_iterator& x) const { return handle != x.handle; }
      bool operator<=(const undirected_edge_iterator& x) const { return handle == x.handle; }
      bool operator>=(const undirected_edge_iterator& x) const { return handle != x.handle; }

      // Increment
      undirected_edge_iterator& operator++() { advance_edge(1); return *this; }
     
      undirected_edge_iterator operator++(int) 
      {
        undirected_edge_iterator tmp{*this}; 
        this->operator++();
        return tmp;
      }

      // Decrement
      undirected_edge_iterator& operator--() { advance_edge(-1); return *this; }

      undirected_edge_iterator operator--(int) 
      {
        undirected_edge_iterator tmp{*this}; 
        this->operator--();
        return tmp;
      }
      
      // Advance
      undirected_edge_iterator& operator+=(difference_type n) { advance_edge(n); return *this; }
      undirected_edge_iterator& operator-=(difference_type n) { advance_edge(-n); return *this; }

      friend undirected_edge_iterator operator+(undirected_edge_iterator i, difference_type n) 
      { 
        return i += n; 
      }
      
      friend undirected_edge_iterator operator+(difference_type n, undirected_edge_iterator i) 
      { 
        return i += n; 
      }


      friend undirected_edge_iterator operator-(undirected_edge_iterator i, difference_type n)
      {
        return i -= n;
      }

      // Difference
      friend difference_type 
      operator-(const undirected_edge_iterator& a, const undirected_edge_iterator& b) 
      { 
        return a.value() - b.value();
      }

    private:
      std::size_t value() const
      {
        return edge.edge.value;
      }

      void advance_edge(difference_type n)
      {
        edge = graph->get_edge(value() + 1);
      }

    private:
      G* graph;
      Edge_type<G> handle;
      */
    };

    
  
  // The undirected incident edge iterator abstracts the notion of a sequence
  // of incident edges by iterating over the chained in- and out-edge ranges
  // of an undirected graph's underlying directed implementation.
  //
  // Note that we don't cache the referenced edge, so we dereference a copy.
  // This means that you can't use -> with these iterators.
  //
  // FIXME: This is also totally broken.
  //
  // NOTE: Do not static assert that G is an undirected graph. Doing so results
  // in mutually recursive concept checks. G is an undirected graph if it has
  // this as an iterator. This a valid iterator if F is an undirected graph.
  template<typename G>
    class undirected_incident_edge_iterator
    {
    /*
    public:
      using value_type = Edge_type<G>;
      using reference = const Edge_type<G>&;
      using pointer = const Edge_type<G>*;
      using difference_type = std::ptrdiff_t;
      using iterator_category = std::random_access_iterator_tag;
      
      undirected_incident_edge_iterator()
        : graph(nullptr), source(), index()
      { }
      
      // Initialize the iterator so that it refers to the nth incident edge
      // of v where n < degree(g, v).
      undirected_incident_edge_iterator(G& g, Vertex_type<G> v, Size_type<G> n)
        : graph(&g), source(v), index(n)
      { }
      
      // Readable
      reference operator*() const { return get_edge(); }
      pointer operator->() const { return get_edge(); }
      
      // Equality_comparable
      bool operator==(const undirected_incident_edge_iterator& x) const { return index == x.index; }
      bool operator!=(const undirected_incident_edge_iterator& x) const { return index != x.index; }

      // Totally_ordered
      bool operator<(const undirected_incident_edge_iterator& x) const { return index == x.index; }
      bool operator>(const undirected_incident_edge_iterator& x) const { return index != x.index; }
      bool operator<=(const undirected_incident_edge_iterator& x) const { return index == x.index; }
      bool operator>=(const undirected_incident_edge_iterator& x) const { return index != x.index; }

      // Random_access_iterator: advance
      undirected_incident_edge_iterator& operator++() { ++index; return *this; }
      undirected_incident_edge_iterator& operator--() { --index; return *this; }
      
      undirected_incident_edge_iterator operator++(int) 
      {
        undirected_incident_edge_iterator tmp{*this}; 
        this->operator++();
        return tmp;
      }

      friend undirected_incident_edge_iterator 
      operator+(undirected_incident_edge_iterator i, difference_type n) 
      { 
        return i += n; 
      }
      
      friend undirected_incident_edge_iterator 
      operator+(difference_type n, undirected_incident_edge_iterator i) 
      { 
        return i += n; 
      }

      undirected_incident_edge_iterator operator--(int)
      {
        undirected_incident_edge_iterator tmp{*this}; 
        this->operator--();
        return tmp;
      }

      friend undirected_incident_edge_iterator 
      operator-(undirected_incident_edge_iterator i, difference_type n)
      {
        return i -= n;
      }

      // Random_access_iterator: distance
      friend difference_type 
      operator-(const undirected_incident_edge_iterator& a, 
                const undirected_incident_edge_iterator& b) 
      { 
        return a.value() - b.value();
      }

    private:
      Edge_type<G> get_edge() const
      {
        return graph->get_incident_edge(source, index);
      }

    private:
      G* graph;
      Vertex_type<G> source;
      Size_type<G> index;
      */
    };

    

  // FIXME: What are these functions for? Where are they being used? 
#if 0
  // The has_target Predicate is used to evaluate whether or not an edge
  // has a given vertex as its target.
  template<typename G>
    struct has_target_pred
    {
      has_target_pred(G& g, Vertex_type<G> v)
        : graph(g), vertex{v}
      { }
      
      bool operator()(Edge_type<G> e) const { return target(graph, e) == vertex; }
      
      G& graph;
      Vertex_type<G> vertex;
    };
    
  // Return a predicate that can be used to determine if the given graph has
  // an edge with the specified vertex.
  template<typename G>
    inline has_target_pred<G> if_has_target(G& g, Vertex<G> v)
    {
      return {g, v};
    }


    
  // The has_source Predicate is used to evaluate whether or not an edge
  // has a given vertex as its source.
  template<typename G>
    struct has_source_pred
    {
      has_source_pred(G& g, Vertex<G> v)
        : graph(g), vertex(v)
      { }
      
      bool operator()(Edge<G> e) const { return source(graph, e) == vertex; }
      
      G& graph;
      Vertex<G> vertex;
    };

  // Return a predicate that can be used to determine if the given graph has
  // an edge with the specified vertex.
  template<typename G>
    inline has_source_pred<G> if_has_source(G& g, Vertex<G> v)
    {
      return {g, v};
    }
#endif
    
} // namespace origin
    
// FIXME: When are we going to have Origin::Hashable?
// Support std::hash interoperability.
namespace std
{
  // Make edge handles hashable by the standard library.
  template<typename T>
    struct hash<origin::edge_handle<T>>
    {
      std::size_t operator()(const origin::edge_handle<T>& e) const
      { 
        return e.hash();
      }
    };
  
  // Make undirected edge handles hashable by the standard library.
  template<typename T>
    struct hash<origin::undirected_edge_handle<T>>
    {
      std::size_t operator()(const origin::undirected_edge_handle<T>& e) const
      {
        return e.hash();
      }
    };
    
} // namespace std
    
#endif
