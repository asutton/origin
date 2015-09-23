
# Constructible concept

## Synopsis

``` {.cpp}
#include <origin/generic.hpp>

template<typename T, typename... Args>
concept bool Destructible() {
  return requires (Args&&... args) {
    T(std::forward<Args>(args)...);
  };
}
```

## Documentation

The constructible concept is a purely syntactic construct. It requires
that an object or reference of type `T` can be initialized over a sequence
of arguments.

## Semantics

This concept has no semantic requirements.

## Example

``` {.cpp}

template<Destructible T>
class vector
{
  template<typename... Args>
    requires Constructible<T, Args...>()
  iterator emplace(Args&&...);
};

```

The `emplace()` function is valid only for types that can be
constructed over that sequence of arguments.
