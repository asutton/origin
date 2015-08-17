// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/generic.hpp>

using namespace origin;

template<typename T>
void
check()
{
  static_assert(Signed_integer_type<T>(), "");
  static_assert(Signed_integer_type<T const>(), "");
  static_assert(Signed_integer_type<T volatile>(), "");
  static_assert(Signed_integer_type<T const volatile>(), "");
}  

int 
main() 
{ 
  check<signed char>();
  check<short int>();
  check<int>();
  check<long int>();
  check<long long int>();

  static_assert(!Signed_integer_type<char>(), "");
  static_assert(!Signed_integer_type<bool>(), "");
  static_assert(!Signed_integer_type<unsigned int>(), "");
}
