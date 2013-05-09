// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/iterator/concepts.hpp>

static_assert(origin::Readable<int*>(), "");
static_assert(origin::Readable<const int*>(), "");
static_assert(origin::Readable<volatile int*>(), "");
static_assert(origin::Readable<const volatile int*>(), "");

int main() { }
