// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

struct S0 { };

struct S1 
{
  bool operator==(S1) const;
};

struct S2
{
  bool operator==(S2) const;
  bool operator!=(S2) const;
};

static_assert(origin::Equality_comparable<int>(), "");
static_assert(origin::Equality_comparable<float>(), "");
static_assert(not origin::Equality_comparable<S0>(), "");
static_assert(not origin::Equality_comparable<S1>(), "");
static_assert(origin::Equality_comparable<S2>(), "");

static_assert(origin::Equality_comparable<int, long>(), "");
static_assert(not origin::Equality_comparable<int, S0>(), "");

int main() { return 0; }
