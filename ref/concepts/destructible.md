
# Destructible types

## Declaration

In `<origin/generic.hpp>`.

``` {.cpp}
template<typename T>
concept bool Destructible() {
  return requires (T t, T* p) {
    { t.~T(); } noexcept;
    { delete p; }
    { delete [] p; }
    { &t } -> Same<T*>;
  };
}
```

## Documentation

A *destructible type* is one whose objects can be destroyed, either
when they go out of scope or are explicitly deallocated. 

This concept is required by every other [value concept](value.html). In 
order be consistent with builtin types, these types must not change
the meaning of the address-of operator. The `delete` expressions are
specifically required since they can be overloaded and made private
or deleted. Such types are not generally usable as value types.

Note that reference types satisfy this concept. When a reference goes out of
scope, its object may not be destroyed, but it is no longer accessible.

## Semantics

- When an object is destroyed, either explicitly or implicitly, all of
its resources are reclaimed. References have no resources so this
is trivially satisfied for reference types.

- The expression `delete p` invokes `p->~T()`.

- The expression `delete [] p` invokes `p[i]->~T()` for each
  `p[i]` allocated by a corresponding call to `new T[n]` where
  `0 <= i <= n`.

- For all `t`, `&t` is equal to `addressof(t)`.


## Example


``` {.cpp}
template<Destructible T>
void f(T x)
{

}
```
