// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/generic.hpp>

static_assert(origin::Same<int, int>(), "");
static_assert(!origin::Same<int, const int>(), "");

// TODO: Write more tests.

int main() { return 0; }
