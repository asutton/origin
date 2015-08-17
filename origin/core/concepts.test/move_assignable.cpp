// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/generic.hpp>

struct S0
{
};

struct S1 
{
  S1& operator=(S1&&) = default;
};

struct S2 
{
  S2& operator=(S2&&) = delete;
};

class S3 
{
  S3 operator=(S3&&) { }
};

static_assert(origin::Move_assignable<int>(), "");
static_assert(origin::Move_assignable<S0>(), "");
static_assert(origin::Move_assignable<S1>(), "");
static_assert(!origin::Move_assignable<S2>(), "");

// FIXME: Move assignable with a private destructor?
static_assert(origin::Move_assignable<S3>(), "");

int main() { return 0; }
