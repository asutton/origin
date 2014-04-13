// Copyright (c) 2008-2014 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/sequence/concepts.hpp>

static_assert(origin::Writable<int*, int>(), "");
static_assert(origin::Writable<int*, const int&>(), "");
static_assert(origin::Writable<int*, int&&>(), "");

int main() { }
