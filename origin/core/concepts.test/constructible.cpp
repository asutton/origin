// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

static_assert(origin::Constructible<int>(), "");
static_assert(origin::Constructible<int, int>(), "");

static_assert(origin::Constructible<int, int&>(), "");
static_assert(origin::Constructible<int, const int&>(), "");
static_assert(origin::Constructible<int, volatile int&>(), "");
static_assert(origin::Constructible<int, const volatile int&>(), "");

// TODO: Write more tests

int main() { return 0; }
