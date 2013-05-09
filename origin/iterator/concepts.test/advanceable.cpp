// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/iterator/concepts.hpp>

#include "test_iterator.hpp"

static_assert(origin::Advanceable<int*>(), "");

int main() { }
