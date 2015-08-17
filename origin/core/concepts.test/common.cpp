// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/concepts>

static_assert(origin::Common<int, int>(), "");
static_assert(origin::Common<int, const int>(), "");
static_assert(origin::Common<int, volatile int>(), "");
static_assert(origin::Common<int, const volatile int>(), "");

static_assert(origin::Common<int, int&>(), "");
static_assert(origin::Common<int, const int&>(), "");
static_assert(origin::Common<int, volatile int&>(), "");
static_assert(origin::Common<int, const volatile int&>(), "");

static_assert(origin::Common<signed int, unsigned int>(), "");

// TODO: Write more tests.

int main() { return 0; }
