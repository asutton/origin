
# Equality comparison

## Synopsis


``` {.cpp}
#include <origin/generic.hpp>

template<typename T>
concept bool Equality_comparable() {
  return requires (T a, T b) {
    { a == b } -> Optional;
    { a != b } -> Optional;
  };
}

```

## Documentation

An *equality comparable* type can be used with `==` to determine when
its objects are equal (have the same value), and can be used with 
`!=` to determine when its objects differ. 


## Semantics

- `==` shall be an equivalence relation (reflexive, symmetric, and transitive).

- If `a == b` is `true`, `a` is equal to `b`. In other words, when `a == b`
  is true, `a` and `b` can be substituted in equality preserving expressions.

- The expression `a != b` is equal to `!(a == b)`.


## Example


``` {.cpp}
// Assume that g is a regular function.
template<typename T>
int g(T);

template<Equality_comparable T>
void f(T a, T b)
{
  if (a == b) {
    // Because a and b are equal, we can use 
    // g(a) or g(b) and get the same results.
  }
}

```
