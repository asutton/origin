
# Concepts

A *concept* is a predicate that defines requirements on template
arguments. Concepts are used within the constraints of a template 
declaration to a) express the kinds of types that can be used
with that template and b) to enforce those requirements at compile
time.

Each concept defines its requirements in terms of syntax or use
patterns and the required behavior of those operations.

The primary groups of concepts are:

- [Language concepts](concepts/language.html) -- These concepts
  describe the kinds of types defined by the C++ Programming Language.
  These primarily characterize types by their "shape" or category rather
  than their uses.

- [Value concepts](concepts/value.html) -- Requirements for the initialization
  of objects, copying and moving, and comparison. These establish the abstract
  notion of "value" (as in value semantics) in modern C++.

- [Function concepts](concepts/function.html) -- These concepts describe 
  requirements on function arguments.

- [Iterator concepts](concepts/iterator.html) -- Requirements for
  iterators. An iterator is an abstraction of a position within a linear
  sequence.

- [Range concepts](concepts/range.html) -- Requirements for ranges. A range
  denotes the beginning and the end of a sequence.

- [Stream concepts](concepts/stream.html) -- Requirements for stream
  abstractions, including formatted I/O streams.
