// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

struct S0 {
  S0() = default;
};

struct S1 {
  S1() = delete;
};

class S2 {
  S2();
};

static_assert(origin::Default_constructible<int>(), "");
static_assert(origin::Default_constructible<S0>(), "");
static_assert(not origin::Default_constructible<S1>(), "");
static_assert(not origin::Default_constructible<S2>(), "");

int main() { return 0; }
