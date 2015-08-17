// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/generic.hpp>

struct S0
{
};

struct S1 
{
  S1() = default;
};

struct S2 
{
  S2() = delete;
};

class S3 
{
  S3();
};

static_assert(origin::Default_constructible<int>(), "");
static_assert(origin::Default_constructible<S0>(), "");
static_assert(origin::Default_constructible<S1>(), "");
static_assert(!origin::Default_constructible<S2>(), "");


// FIXME: GCC reports this as valid. A class with a private
// default constructor is apparently default constructible?
static_assert(origin::Default_constructible<S3>(), "");

int main() 
{ 
  return 0; 
}
