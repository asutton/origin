
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

## General requirements

The concepts defined in this section do not include syntactic requirements
for `new`, `delete`, and operator `&`. For any type `T` satisfying any of
these concepts, a pointer `p` whose type is `T*`, and an object `x` of
type `T`, the following are required:

- `new T <initializer>` allocates an object of type `T` and initializes
  it with the arguments specified by the initializer.

- `delete p` destroys the object pointed to by `p`, causing all of its
  resources to be released.

- `&x` returns the same value as `std::addressof(x)`.

Types may overload these operators, but they must behave in the conventional
way.

## Equality

Given two objects `a` and `b`, we say that "`a` is equal to `b`" to mean
that they have the same value. This does not mean that the objects have the 
same state or pattern of bits in their representation. The notion of "value"
transcends its representation.

The "equal to" equivalence relation is defined by the set of operations
supported by types. For example, creating a [copy](copyable.html) of an object
causes the new object to be equal to the original. When two objects compare
[equal](equality.html) using `==`, then those objects are in the "equal to"
relation. 

An expression is *equality preserving* if and only if equal operands 
would yield equal results. For example, given objects `x` and `y` of
type `int`, if `x` is equal to `y` then `x + x` is equal to `y + y`. This
expression is equality preserving. In other words, equal values can be
*substituted* in equality preserving expressions. 

In these concepts, all required expressions are required to be equality
preserving unless otherwise noted.

If `a` and `b` are equal but have different types, lexical substitution 
of one for the other may result in ill-formed programs. This can be caused 
by a failure to provide the necessary overloads for all cases where equal 
objects of different type can be used interchangeably.
