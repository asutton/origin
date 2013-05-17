// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <memory>
#include <origin/core/concepts.hpp>

// Integral types are conditional types
static_assert(origin::Conditional<bool>(), "");
static_assert(origin::Conditional<char>(), "");
static_assert(origin::Conditional<short>(), "");
static_assert(origin::Conditional<int>(), "");
static_assert(origin::Conditional<long>(), "");
static_assert(origin::Conditional<long long>(), "");

// Pointers are conditional (except weak_ptr)
static_assert(origin::Conditional<int*>(), "");
static_assert(origin::Conditional<std::unique_ptr<int>>(), "");
static_assert(origin::Conditional<std::shared_ptr<int>>(), "");
static_assert(not origin::Conditional<std::weak_ptr<int>>(), "");

int main() { return 0; }
