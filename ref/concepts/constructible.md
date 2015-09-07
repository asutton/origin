
# Constructible concept

## Declaration

In `<origin/generic.hpp>`.

``` {.cpp}
template<typename T, typename... Args>
concept bool Destructible() {
  return requires (Args&&... args) {
    T(std::forward<Args>(args)...);
    new T(std::forward<Args>(args)...);
  };
}
```


## Documentation

The constructible concept defines the set of types that can be constructed
over a sequence of arguments. 


## Example


``` {.cpp}
template<Destructible T>
void f(T x)
{

}
```
