
# Value concepts

The value concepts (elsewhere referred to as "object" or "foundational"
concepts), describe requirements on type related to initialization,
copying, moving, and value comparison. These concepts establish the
semantic requirements of *value types*.

A *move-only type* is a type that satisfies many of the requirements
for a value type except that it cannot be copied. 

The value concepts are:

- `Destructible`
- `Move_constructible`
- `Copy_constructible`
- `Copyable`
- `Movable`
- `Semiregular`
- `Regular`
- `Equality_comparable`
- `Totally_ordered`
- `Ordered`
