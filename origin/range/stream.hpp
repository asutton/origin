// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_STREAM_HPP
#define ORIGIN_STREAM_HPP

#include <iterator>

#include <origin/core/concepts.hpp>
#include <origin/range/concepts.hpp>

namespace origin {

// -------------------------------------------------------------------------- //
// Stream Primitives                                          [stream.primitive]

namespace stream_impl {
// The following concepts describe the syntax necessary to define the
// primitive operations on classes with std stream-like member functions.

// In the C++ Standard Library, the result type of operations returning
// streams (e.g., ignore, put, operator<<, operator>>) are references to
// the base istream class, not the derived class. Because of this, we can't
// design library that natively accommodates both std facilities and newer
// stream models /and/ defines a meaningful result for the result type.
//
// However, this may run afoul of seemingly recursive concept definitions.
//
// Another approach would be to define the primitive operations in terms
// of disjunction and then build and abstraction over that.

// For now, we make no guarantees about the result of those operations.

// A primitive stream is a class that provides two members: peek and
// get.
template<typename S>
  concept bool
  Primitive_istream() {
    return requires(S& s) {
      s.peek();
      s.get();
    };
  }

// An ignorable stream is a primitive stream that provides a third
// operation, ignore. This is only provided when the underlying stream
// can more efficiently advance by ignoring values than getting and
// discarding them.
template<typename S>
  concept bool
  Ignorable_istream() {
    return requires(S& s) {
      s.peek();
      s.get();
      s.ingore();
    };
    // return Primitive_istream<S>() 
    //    and requires(S& s) {
    //          s.ignore();
    //        };
  }

template<typename S, typename T>
  concept bool
  Primitive_ostream() {
    return requires(S& s, T t) {
             s.put(t);
           };
  }

} // namespace stream_impl

// Returns the current value in the stream. 
template<stream_impl::Primitive_istream S>
  inline decltype(auto)
  peek(S& is) { return is.peek(); }

// Returns the current value in the stream and advances to the next value.
template<stream_impl::Primitive_istream S>
  inline auto 
  get(S& is) { return is.get(); }

// Advances to the next value by getting and discarding the next value.
template<stream_impl::Primitive_istream S>
  inline void 
  advance(S& is) { get(is); }

// Advances to the next value by ignoring the current value.
template<typename S>
  requires stream_impl::Ignorable_istream<S>()
  inline void 
  advance(S& is) { is.ignore(); }

// Writes value into the stream.
template<typename S, typename T>
  requires stream_impl::Primitive_ostream<S, T>()
    void
    put(S& os, const T& value) { os.put(value); }

// Moves value into the stream.
template<typename S, typename T>
  requires stream_impl::Primitive_ostream<S, T>()
    void
    put(S& os, T&& value) { os.put(std::move(value)); }


// -------------------------------------------------------------------------- //
// Stream Concepts                                              [stream.concept]

// An input stream is represents a possibly infinite sequence of values.
template<typename S>
  concept bool 
  Input_stream() {
    return Conditional<S>() && 
           requires(S& s) {
             {peek(s)} -> const Value_type<S>&;
             {get(s)} -> Value_type<S>;
             advance(s);
           };
  }

// An output stream is represents an arbitrary target into which values
// may be written.
template<typename S>
  concept bool 
  Output_stream() {
    return Conditional<S>() && 
           requires(S& s, Value_type<S> x) {
              put(s, x);
           };
  }

// A stream, S, is formatted input stream for values of type T if
// and only if those values can be extracted from the stream using
// operator >>.
template<typename S, typename T>
  concept bool 
  Formatted_input_stream() {
    return Input_stream<S>() 
       and requires(S& s, T t) {
             s >> t;
           };
  }

// A stream, S, is formatted output stream for values of type T if 
// and only if those values can be inserted into the stream using 
// operator <<.
template<typename S, typename T>
  concept bool
  Formatted_output_stream() {
    return Output_stream<S>() 
       and requires(S& s, T t) {
             s << t;
           };
  }

// -------------------------------------------------------------------------- //
// Stream Adaptors                                                [stream.adapt]


// A typed input stream adaptor transforms a formatted input stream, S,
// into an input stream that gets only values of type T.
template<typename S, typename T>
  requires Formatted_input_stream<S, T>()
    class typed_istream {
    public:
      using value_type = T;

      typed_istream(S& is)
        : is(is) { is >> val; }

      // Stream operations
      
      const T& peek() const { return val; }

      T get() { 
        T tmp = std::move(val); 
        is >> val; 
        return tmp;
      }

      // Conditional
      explicit operator bool() const { return (bool)is; }

    private:
      S& is;
      T val;
    };

// Creates a typed istream for values of type T from a formatted input
// stream.
template<typename T, typename S>
  requires Formatted_input_stream<S, T>()
    auto make_istream(S& s) { return typed_istream<S, T>(s); }


// A typed output stream adaptor transforms a formatted output stream, S,
// into an output stream that writes only values of type T.
template<typename S, typename T>
  requires Formatted_output_stream<S, T>()
    class typed_ostream {
    public:
      using value_type = T;

      typed_ostream(S& os)
        : os(os) { }

      typed_ostream& put(const T& x) {
        os << x;
        return *this;
      }

      typed_ostream put(T&& x) {
        os << std::move(x);
        return *this;
      }

      // Conditional
      explicit operator bool() const { return (bool)os; }

    private:
      S& os;
    };

// Creates a typed ostream for values of type T from a formatted output 
// stream. 
template<typename T, typename S>
  requires Formatted_output_stream<S, T>()
    auto make_ostream(S& s) { return typed_ostream<S, T>(s); }



// The istream iterator replaces the std::istream iterator.
template<Input_stream S>
  struct istream_iterator {
    using value_type = Value_type<S>;
    using difference_type = std::ptrdiff_t;

    istream_iterator()
      : is(nullptr) { }

    istream_iterator(S& s)
      : is(&s) { }

    // Readable
    decltype(auto) operator*() const { return peek(*is); }

    // Advanceable
    istream_iterator& operator++() {
      origin::advance(*is);
      if (!*is)
        is = nullptr;
    }

    S* is;
  };

// Returns true only when the arguments refer to the same stream object.
template<Input_stream S>
  inline bool
  operator==(const istream_iterator<S>& a, const istream_iterator<S>& b) {
    return a.is == b.is;
  }

// Returns true when the arguments refer to different stream objects.
template<Input_stream S>
  inline bool
  operator!=(const istream_iterator<S>& a, const istream_iterator<S>& b) {
    return a.is != b.is;
  }

// The istream range transforms an input stream into a range of input
// iterators.
template<Input_stream S>
  struct istream_range {
    using value_type = Value_type<S>;
    using iterator = istream_iterator<S>;

    istream_range(S& s)
      : is(s) { }

    auto begin() const { return iterator(is); }
    auto end() const { return iterator(); }

    S& is;
  };

// The ostream range transforms an output stream into a range of output
// iterators.
template<Output_stream S>
  struct ostream_range {
    using value_type = Value_type<S>;
    using iterator = std::ostream_iterator<value_type>;

    ostream_range(S& s)
      : os(s) { }

    auto begin() const { return iterator(os); }
    auto end() const { return iterator(os); }

    S& os;
  };


// Range adaptors...
template<Input_stream S>
  istream_range<S> Range(S& is) { return {is}; }

template<Output_stream S>
  ostream_range<S> Range(S& os) { return {os}; }

} // namespace origin

#endif
