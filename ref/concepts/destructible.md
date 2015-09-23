
# Destructible types

## Synopsis

``` {.cpp}
#include <origin/generic.hpp>

template<typename T>
concept bool Destructible() {
  return requires (T t) {
    { t.~T(); } noexcept;
  };
}
```

## Documentation

A *destructible type* is one whose objects can be destroyed, either
when they go out of scope or are explicitly deallocated.

## Semantics

When an object is destroyed, either explicitly or implicitly, it
releases all owned resources acquired during initialization. A 
destructible type may allocate or receive shared resources. These
are not required to be released upon destruction. For example, a
reference-counted string implementation is not required to release its 
allocated object if the reference count is non-zero.

## Example

``` {.cpp}
template<Destructible T>
void f()
{
  T x;
  T* p = new T;
  delete p;     // *p is destroyed here
}               // x is destroyed here
```
