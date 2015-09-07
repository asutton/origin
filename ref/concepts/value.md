
# Value concepts

The value concepts (elsewhere referred to as "object" or "foundational"
concepts), describe requirements on type related to initialization,
copying, moving, and value comparison. These concepts establish the
semantic requirements of *value types*.

A *move-only type* is a type that satisfies many of the requirements
for a value type except that it cannot be copied. 

The value concepts are:

- [`Destructible`](destructible.html)
- `Move_constructible`
- `Copy_constructible`
- `Movable`
- `Copyable`
- [`Semiregular`](semiregular.html)
- [`Regular`](regular.html)
- [`Equality_comparable`](equality.html)
- `Totally_ordered`
- `Ordered`


Note that the easiest way to define value types is to allow the compiler
to generate as many special functions as possible. The semantics of those
functions will (generally) satisfy the requirements of these concepts.