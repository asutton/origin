// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/iterator.hpp>

#include "test_resource.hpp"

static_assert(origin::Mutable<int*>(), "");
static_assert(! origin::Mutable<res*>(), "");

int main() { }
