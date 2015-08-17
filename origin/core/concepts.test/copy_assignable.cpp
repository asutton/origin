// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/concepts>

struct S0
{
};

struct S1
{
  S1& operator=(S1 const&) = default;
};

struct S2 
{
  S2& operator=(S2 const&) = delete;
};

class S3
{
  S3& operator=(S3 const&) = delete;
};


static_assert(origin::Copy_assignable<int>(), "");
static_assert(origin::Copy_assignable<S0>(), "");
static_assert(origin::Copy_assignable<S1>(), "");
static_assert(!origin::Copy_assignable<S2>(), "");
static_assert(!origin::Copy_assignable<S3>(), "");

int main() { return 0; }
