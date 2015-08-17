// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/generic.hpp>

struct S0
{
};

struct S1 
{
  S1(const S1&) = default;
};

struct S2 
{
  S2(const S2&) = delete;
};

class S3
{
  S3(const S3&) = delete;
};

static_assert(origin::Copy_constructible<int>(), "");
static_assert(origin::Copy_constructible<S0>(), "");
static_assert(origin::Copy_constructible<S1>(), "");
static_assert(!origin::Copy_constructible<S2>(), "");
static_assert(!origin::Copy_constructible<S3>(), "");

int main() { return 0; }
