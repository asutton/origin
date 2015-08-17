// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/concepts>


struct B0
{
  explicit operator bool() const { return true; }
};


struct B1
{
  operator bool() const { return true; }
};


struct B2
{
  explicit operator bool() const { return true; }
  int operator!() const { return 0; }
};


static_assert(origin::Boolean<bool>(), "");
static_assert(origin::Boolean<int>(), "");
static_assert(origin::Boolean<B0>(), "");
static_assert(origin::Boolean<B1>(), "");
static_assert(!origin::Boolean<B2>(), "");

int main() { return 0; }
