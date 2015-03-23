// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

struct B { };
struct D1 : B { };
class D2 : B { };

static_assert(origin::Derived<B, B>(), "");
static_assert(origin::Derived<D1, B>(), "");
static_assert(!origin::Derived<D2, B>(), "");

// TODO: write tests for virtual inheritance.

int main() { return 0; }
