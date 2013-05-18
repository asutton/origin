// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <memory>

#include <origin/core/concepts.hpp>

// Integral types are conditional types
static_assert(origin::Boolean<bool>(), "");
static_assert(origin::Boolean<char>(), "");
static_assert(origin::Boolean<short>(), "");
static_assert(origin::Boolean<int>(), "");
static_assert(origin::Boolean<long>(), "");
static_assert(origin::Boolean<long long>(), "");

// Pointers are conditional (except weak_ptr)
static_assert(origin::Boolean<int*>(), "");
static_assert(origin::Boolean<std::unique_ptr<int>>(), "");
static_assert(origin::Boolean<std::shared_ptr<int>>(), "");
static_assert(not origin::Boolean<std::weak_ptr<int>>(), "");

struct S0 
{
  explicit operator bool() { return true; }
};

S0 operator&&(S0, S0) { return S0 {}; }
S0 operator||(S0, S0) { return S0 {}; }
S0 operator!(S0) { return S0 {}; }

static_assert(not origin::Boolean<S0>(), "");

int main() { return 0; }
