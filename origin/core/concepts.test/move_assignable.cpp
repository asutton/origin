// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

struct S0 {
  S0(S0&&) = default;
  S0& operator=(S0&&) = default;
};

struct S1 {
  S1& operator=(S1&&) = delete;
};

class S2 {
  S2& operator=(S2&&) = delete;
};

static_assert(origin::Move_assignable<int>(), "");
static_assert(origin::Move_assignable<S0>(), "");
static_assert(not origin::Move_assignable<S1>(), "");
static_assert(not origin::Move_assignable<S2>(), "");

int main() { return 0; }
