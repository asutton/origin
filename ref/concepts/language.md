
# Language concepts

The language concepts characterize types by their "shape" or by their
categorization according to the C++ standard. The "shape" of a type
is based on its spelling. For example, a pointer type has the
shape `T*`, where `T` is any other type. Similarly, an array of bound
`N` has the shape `T[N]`. 

The C++ language and standard library also define categories based on 
semantic properties of types. For example, the *object types* are all
those types that can hold a value in memory, which is everything except
`void`, function types, and reference types. A *polymorphic type* is
one that has at least one virtual function.

The language concepts closely parallel type traits with similar names.
We use the suffix `_type` to indicate that these are characterizations
and not specifications of abstract interfaces. They are:

- [`Integral_type`](integral_type.html)
- `Signed_type`
- `Unsigned_type`
- `Floating_point_type`
- `Pointer_type`
- `Lvalue_reference_type`
- `Rvalue_reference_type`
- `Array_type`
