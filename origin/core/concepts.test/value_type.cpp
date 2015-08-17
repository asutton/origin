// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/generic.hpp>


// True when Value_type<T> is the same as U.
template<typename T, typename U>
constexpr bool 
Has_value_type()
{
  return origin::Same<origin::Value_type<T>, U>();
}

struct S
{
  using value_type = int;
};

static_assert(Has_value_type<int*, int>(), "");
static_assert(Has_value_type<const int*, int>(), "");
static_assert(Has_value_type<int[], int>(), "");
static_assert(Has_value_type<int[1], int>(), "");
static_assert(Has_value_type<S, int>(), "");

int main() { return 0; }
