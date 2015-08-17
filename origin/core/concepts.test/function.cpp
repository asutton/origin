// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/concepts>

static_assert(origin::Function<void(*)(int), int>(), "");

int main() { return 0; }
