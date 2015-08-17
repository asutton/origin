// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/generic.hpp>

static_assert(origin::Convertible<int, int>(), "");
static_assert(origin::Convertible<int, const int>(), "");
static_assert(origin::Convertible<int, volatile int>(), "");
static_assert(origin::Convertible<int, const volatile int>(), "");
static_assert(origin::Convertible<const int, int>(), "");
static_assert(origin::Convertible<volatile int, int>(), "");
static_assert(origin::Convertible<const volatile int, int>(), "");

static_assert(not origin::Convertible<int, int&>(), "");
static_assert(not origin::Convertible<const int, int&>(), "");
static_assert(not origin::Convertible<volatile int, int&>(), "");
static_assert(not origin::Convertible<const volatile int, int&>(), "");

static_assert(origin::Convertible<int, const int&>(), "");
static_assert(origin::Convertible<const int, const int&>(), "");
static_assert(not origin::Convertible<volatile int, const int&>(), "");
static_assert(not origin::Convertible<const volatile int, const int&>(), "");

static_assert(origin::Convertible<int, int&&>(), "");

static_assert(origin::Convertible<int&, int>(), "");
static_assert(origin::Convertible<const int&, int>(), "");

static_assert(origin::Convertible<void, void>(), "");
static_assert(origin::Convertible<void, void const>(), "");

// TODO: Write more tests. Obviously...

int main() { return 0; }
