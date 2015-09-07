
# Integral types

## Declaration

In `<origin/generic.hpp>`.

``` {.cpp}
template<typename T>
concept bool Integral_type() ...
```

## Documentation

The following types are categorized as *integral types*: `bool`, `char`,
`char16_t`, `char32_t`, `wchar_t`, `short`, `int`, `long`, `long long`,
any implementation-defined extended integer types, all signed and
unsigned variants of these types, and all `const` or `volatile` qualified
variants of these types.


## Example


``` {.cpp}
template<typename T>
void f(T x)
{
  return 0;
}

template<origin::Integral_type T>
int f(T x)
{
  return 1;
}

int main()
{
  int x = 0;
  assert( f(x) == 1 );
  assert( f(&x) == 0 ); // A pointer is not an integral type
}
```

