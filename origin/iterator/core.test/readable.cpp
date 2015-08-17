// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/iterator.hpp>

static_assert(origin::Readable<int*>(), "");
static_assert(origin::Readable<const int*>(), "");
static_assert(origin::Readable<volatile int*>(), "");
static_assert(origin::Readable<const volatile int*>(), "");

int main() { }
