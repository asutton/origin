
# Regular types

## Declaration

The `Regular` concept is declared in `<origin/generic.hpp>`.

``` {.cpp}
template<typename T>
concept bool Regular()
```

## Documentation

A *regular type* is one that can be used, to an extent, like an `int`.
Regular types can be default constructed, moved, copied, and compared
for equality. They are not, however, required to be [ordered](ordered.html).

The `Regular` concept does not define any new syntactic or semantic
requirements.

## Example

``` {.cpp}
template<Regular T>
void f(T x)
{

}
```
