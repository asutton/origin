// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#ifndef ORIGIN_GRAPH_HANDLE_HPP
#define ORIGIN_GRAPH_HANDLE_HPP

#include <cstdint>
#include <functional>

namespace origin  {
// ------------------------------------------------------------------------ //
//                                                              [graph.handle]
//                              Handle
//
// A handle is an ordinal value type used to represent an object in a data
// structure. Handles are implicitly interoperable with unsigned intger
// (size_t) values, and have the special property that unsigned -1 indicates
// an invalid object.
//
// TODO: Disable arithmetic operations?
struct handle
{
  static constexpr std::size_t npos = -1;

  handle(std::size_t n = npos);

  // Boolean
  explicit operator bool() const;

  // Integral
  operator std::size_t() const { return value; }
  
  // Hashable
  std::size_t hash() const;
  
  std::size_t value;
};

inline
handle::handle(std::size_t n) : value(n) { }

inline 
handle::operator bool() const { return value != npos; }

inline std::size_t 
handle::hash() const { return std::hash<std::size_t>{}(value); }

// Equality
inline bool 
operator==(handle a, handle b) { return a.value == b.value; }

inline bool 
operator!=(handle a, handle b) { return !(a == b); }

// Ordering
inline bool 
operator<(handle a, handle b)
{ 
  if (!a)
    return bool(b);
  else 
    return b ? a.value < b.value : false; 
}
  
inline bool 
operator>(handle a, handle b) { return b < a; }

inline bool 
operator<=(handle a, handle b) { return !(b < a); }

inline bool 
operator>=(handle a, handle b) { return !(a < b); }


// ------------------------------------------------------------------------ //
//                                                             [graph.vhandle]
//                            Vertex Handle
//
// A vertex handle is a handle specifically for graph vertices. It is
// the same as a normal handle in every way except its type.
struct vertex_handle : handle
{
  using handle::handle;
};


// ------------------------------------------------------------------------ //
//                                                             [graph.ehandle]
//                              Edge Handle
//
// An edge hadndle is a handle specifically for graph edges that are uniquely
// identified by a single number. This is an uncommon property for graph
// data structures. More frequently, edge handles are source/target pairs
// or source/target/edge triples. See simple_edge_handle and multi_edge_handle
// for details.
struct edge_handle : handle
{
  using handle::handle;
};


// ------------------------------------------------------------------------ //
//                              Simple Edge Handle
//
// An edge handle is a source/target pair that uniquely identifies an edge.
//
// TODO: Implement edge_handle.



// ------------------------------------------------------------------------ //
//                            Multi-edge Handle
//
// A multi-edge handle is a triple, describing source and target handles,
// along with an edge handle. The source and target handles are usual
// vertex handles (i.e., indexes), but the edge component may vary based on
// the graph implementation. It is most often an index.
//
// FIXME: What is E?
template<typename E>
  struct multi_edge_handle
  {
    using handle_type = E;

    multi_edge_handle();
    multi_edge_handle(vertex_handle s, vertex_handle t, E e);

    vertex_handle source() const;
    vertex_handle target() const;
    handle_type edge() const;

    // Hashable
    std::size_t hash() const;

    std::tuple<vertex_handle, vertex_handle, E> value;
  };

template<typename E>
multi_edge_handle<E>::multi_edge_handle()
  : value(vertex_handle::npos, vertex_handle::npos, E{})
{ }

template<typename E>
multi_edge_handle<E>::multi_edge_handle(vertex_handle s, vertex_handle t, E e)
  : value(s, t, e)
{ }

template<typename E>
  auto multi_edge_handle<E>::source() const -> vertex_handle
  {
    return std::get<0>(value);
  }

template<typename E>
  auto multi_edge_handle<E>::target() const -> vertex_handle
  {
    return std::get<1>(value);
  }

template<typename E>
  auto multi_edge_handle<E>::edge() const -> handle_type
  {
    return std::get<2>(value);
  }

template<typename E>
  inline std::size_t
  multi_edge_handle<E>::hash() const
  {
    // TODO: Stop using GCC internal functions for hashing.
    return std::_Hash_bytes(&value, sizeof(value), 0);
  }

// Equality
template<typename E>
  inline bool
  operator==(const multi_edge_handle<E>& a, const multi_edge_handle<E>& b)
  {
    return a.value == b.value;
  }

template<typename E>
  inline bool
  operator!=(const multi_edge_handle<E>& a, const multi_edge_handle<E>& b)
  {
    return !(a == b);
  }

// Ordering
template<typename E>
  inline bool
  operator<(const multi_edge_handle<E>& a, const multi_edge_handle<E>& b)
  {
    return a.value < b.value;
  }

template<typename E>
  inline bool
  operator>(const multi_edge_handle<E>& a, const multi_edge_handle<E>& b)
  {
    return b < a;
  }

template<typename E>
  inline bool
  operator<=(const multi_edge_handle<E>& a, const multi_edge_handle<E>& b)
  {
    return !(b < a);
  }

template<typename E>
  inline bool
  operator>=(const multi_edge_handle<E>& a, const multi_edge_handle<E>& b)
  {
    return !(a < b);
  }

} // namespace origin


// Natively support the standard hashing protocol for vertex handles.
namespace std  {
template<>
  struct hash<origin::vertex_handle>
  {
    std::size_t 
    operator()(origin::vertex_handle x) const { return x.hash(); }
  };

template<typename E>
  struct hash<origin::multi_edge_handle<E>>
  {
    std::size_t 
    operator()(const origin::multi_edge_handle<E>& h) { return h.hash(); }
  };
} // namespace std


#endif
