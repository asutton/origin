
# Semiregular types

## Declaration

In `<origin/generic.hpp>`.

``` {.cpp}
template<typename T>
concept bool Semiregular()
```

## Documentation

A *semiregular type* is one that can be used, to an extent, like an `int`.
Semiregular types can be, moved, copied. They are not, however, required to 
[default constructible](default_constructible.html) or 
[equality comparable](equality.html). 

Function objects, lambda closure types, plain C `struct` and `union` 
types (that don't overload `==`) are examples of semiregular types.

Note that a class containing reference member variables is not a semiregular
type because it is not [copyable](copyable.html). A union of non-POD types
may also not be semiregular if any of its required constructors are
deleted.


## Example


``` {.cpp}
template<Semiregular T>
void f()
{
}
```

