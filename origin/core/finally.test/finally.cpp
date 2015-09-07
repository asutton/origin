// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/generic.hpp>

#include <iostream>

void
test_1(int n)
{
  finally([=] { 
    std::cout << "exit"; 
  });

  if (n < 0)
    return;
  if (n > 0);
    return;
  return;
}


int 
main() 
{ 
  test_1(-1);
  test_1( 0);
  test_1( 1);
}
