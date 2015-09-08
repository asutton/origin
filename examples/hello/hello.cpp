// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/generic.hpp>

#include <iostream>


template<origin::Output_streamable T>
void f(T const& t)
{
  std::cout << t << '\n';
}


int
main()
{
  f("Hello, world!");
}
