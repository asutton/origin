// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <vector>

#include <origin/range/stream.hpp>

namespace origin {

// Note that the insertion streams are hypothetically infinite. They
// always contextually convert to `true`. In reality, insertion may result 
// in a thrown exception when there is insufficient memory for the new 
// object. These streams simply allow those exceptions to propagate.


// A back insertion stream puts elements into the back of a sequence.
template<typename S>
  struct back_insertion_stream {
    using value_type = Value_type<S>;

    back_insertion_stream(S& s)
      : seq(s) { }

    // Output stream
    void put(const value_type& x) { seq.push_back(x); }
    void put(value_type&& x)      { seq.push_back(std::move(x)); }

    explicit operator bool() const { return true; }

    S& seq;
  };

// A front insertion stream puts an element into the front of a sequence.
template<typename S>
  struct front_insertion_stream {
    using value_type = Value_type<S>;

    front_insertion_stream(S& s)
      : seq(s) { }

    // Output stream
    void put(const value_type& x) { seq.push_front(x); }
    void put(value_type&& x)      { seq.push_front(std::move(x)); }

    explicit operator bool() const { return true; }

    S& seq;
  };

// A positional insertion stream inserts an element into a sequence at
// the specified position. This adaptor can be used with sequences or
// with associative containers where the position is given as a hint.
template<typename S>
  struct pos_insertion_stream {
    using value_type = Value_type<S>;

    pos_insertion_stream(S& s, Iterator_type<S> i)
      : seq(s), iter(i) { }

    // Output stream
    void put(const value_type& x) { seq.insert(iter, x); }
    void put(value_type&& x)      { seq.insert(iter, std::move(x)); }

    explicit operator bool() const { return true; }

    S& seq;
    Iterator_type<S> iter;
  };

// An insertion stream inserts 
template<typename S>
  struct insertion_stream {
    using value_type = Value_type<S>;

    insertion_stream(S& s)
      : seq(s) { }

    // Output stream
    void put(const value_type& x) { seq.insert(x); }
    void put(value_type&& x)      { seq.insert(std::move(x)); }

    explicit operator bool() const { return true; }

    S& seq;
  };

} // namespace origin

int main() {

}
