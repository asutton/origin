// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/concepts>

struct B { };
struct D1 : B { };
class D2 : B { };

static_assert(origin::Derived<B, B>(), "");
static_assert(origin::Derived<D1, B>(), "");
static_assert(!origin::Derived<D2, B>(), "");

// TODO: write tests for virtual inheritance.

int 
main() { }
