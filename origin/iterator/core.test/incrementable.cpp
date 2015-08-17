// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/ranges>

#include "test_iterator.hpp"

static_assert(origin::Incrementable<int*>(), "");
static_assert(not origin::Incrementable<input_iter>(), "");

int main() { }
