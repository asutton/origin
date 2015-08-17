// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/generic.hpp>

struct S0
{
};

struct S1 
{
  S1(S1&&) = default;
};

struct S2 
{
  S2(S2&&) = delete;
};

class S3 
{
  S3(S3&&) { }
};

static_assert(origin::Move_constructible<int>(), "");
static_assert(origin::Move_constructible<S0>(), "");
static_assert(origin::Move_constructible<S1>(), "");
static_assert(!origin::Move_constructible<S2>(), "");

// FIXME: Move constructible with a private constructor?
static_assert(origin::Move_constructible<S3>(), "");

int main() { return 0; }
