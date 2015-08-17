// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/iterator.hpp>

static_assert(origin::Writable<int*, int>(), "");
static_assert(origin::Writable<int*, const int&>(), "");
static_assert(origin::Writable<int*, int&&>(), "");

int main() { }
