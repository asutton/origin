// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/generic.hpp>

// True when Common_type<T, U> is the same as C.
template<typename T, typename U, typename C>
constexpr bool Has_common_type() 
{
  return origin::Same<origin::Common_type<T, U>, C>();
}

static_assert(Has_common_type<int, int, int>(), "");
static_assert(Has_common_type<int, const int, int>(), "");
static_assert(Has_common_type<int, volatile int, int>(), "");
static_assert(Has_common_type<int, const volatile int, int>(), "");

static_assert(Has_common_type<int, int&, int>(), "");
static_assert(Has_common_type<int, const int&, int>(), "");
static_assert(Has_common_type<int, volatile int&, int>(), "");
static_assert(Has_common_type<int, const volatile int&, int>(), "");

static_assert(Has_common_type<signed int, unsigned int, unsigned int>(), "");

// TODO: Write more tests.

int main() { }
