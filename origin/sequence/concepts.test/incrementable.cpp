// Copyright (c) 2008-2014 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/sequence/concepts.hpp>

#include "test_iterator.hpp"

static_assert(origin::Incrementable<int*>(), "");
static_assert(not origin::Incrementable<input_iter>(), "");

int main() { }
