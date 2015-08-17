// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/concepts>

static_assert(origin::Constructible<int>(), "");
static_assert(origin::Constructible<int, int>(), "");

static_assert(origin::Constructible<int, int&>(), "");
static_assert(origin::Constructible<int, const int&>(), "");
static_assert(origin::Constructible<int, volatile int&>(), "");
static_assert(origin::Constructible<int, const volatile int&>(), "");

// TODO: Write more tests

int main() { return 0; }
