// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_STREAM_HPP
#define ORIGIN_STREAM_HPP

#include <iterator>

namespace origin {

// An input stream....
template<typename S>
  concept bool 
  Input_stream() {
    return Conditional<S>() && 
           requires(S& s) {
             {s.peek()} -> const Value_type<S>&;
             {s.get()} -> const Value_type<S>&;
             {s.ignore()} -> S&;
           };
  }

// An input stream....
template<typename S>
  concept bool 
  Output_stream() {
    return Conditional<S>() && 
           requires(S& s, Value_type<S> x) {
             s.put(x);
           };
  }

// A formatted input stream is a binary concept that describes in input
// stream S from which values of type T can be extracted.
template<typename S, typename T>
  concept bool 
  Formatted_input_stream() {
    return Input_stream<S>() and requires(S& s, T& t) {
      s >> t;
    };
  }

// A typed input stream reads and writes values of a specific type
// from an underlying formatted character stream.
template<typename S, typename T>
  requires Formatted_input_stream<S, T>()
    struct typed_istream {
      using value_type = Value_type<S>;

      typed_istream(S& is)
        : is(is) { is >> val; }

      const value_type& peek() { return val; }

      value_type get() { 
        value_type tmp = std::move(val); 
        is >> val; 
        return tmp;
      }

      typed_istream& ignore() {
        is >> val;
      }

      explicit operator bool() const { return (bool)is; }

      S& is;
      value_type val;
    };

// Adapts an istream into a range.
template<Input_stream S>
  struct istream_range {
    using value_type = origin::Value_type<S>;
    using iterator = std::istream_iterator<value_type>;

    auto begin() { return iterator(is); }
    auto end() { return iterator(); }

    S& is;
  };


// Range adaptors...
template<Input_stream S>
  istream_range<S> Range(S& is) { return {is}; }

} // namespace origin

#endif
