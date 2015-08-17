// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/concepts>

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
