// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/concepts>

#include <origin/core/concepts.hpp>

template<typename T, typename U> void test();

template<typename T, typename U>
  requires origin::Assignable<int&, int>()
void test() { }

int main() 
{ 
  test<int&, int>();
  test<int&, const int>();
  test<int&, volatile int>();
  test<int&, const volatile int>();
}
