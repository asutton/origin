// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/concepts>

using namespace origin;

template<typename T>
void
check_void()
{
  static_assert(Void_type<T>(), "");
  static_assert(Void_type<T const>(), "");
  static_assert(Void_type<T volatile>(), "");
  static_assert(Void_type<T const volatile>(), "");
}

int 
main() 
{ 
  check_void<void>();
}
