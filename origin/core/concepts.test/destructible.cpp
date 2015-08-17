// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/concepts>

struct S0
{
};

struct S1 
{
  S1() = default;
};

struct S2 
{
  ~S2() = delete;
};

class S3 
{
  ~S3();
};

static_assert(origin::Destructible<int>(), "");
static_assert(origin::Destructible<S0>(), "");
static_assert(origin::Destructible<S1>(), "");
static_assert(!origin::Destructible<S2>(), "");

// FIXME: GCC says that S3 is destructible despite having
// a private destructor.
static_assert(origin::Destructible<S3>(), "");

int main() { return 0; }
