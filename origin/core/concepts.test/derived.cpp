// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

struct A { };
struct B : A { };
class C : private A { };

static_assert(origin::Derived<A, A>(), "");
static_assert(origin::Derived<B, A>(), "");

// FIXME: Should we be able to see private inheritance? As a
// concept, I'd think not!
static_assert(origin::Derived<C, A>(), "");

// TODO: write tests for virtual inheritance.

int main() { return 0; }
