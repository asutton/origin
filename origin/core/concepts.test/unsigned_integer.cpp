// Copyright (c) 2009-2015 Andrew Sutton
// All rights reserved

#include <origin/generic.hpp>


using namespace origin;

template<typename T>
void
check()
{
  static_assert(Unsigned_integer_type<T>(), "");
  static_assert(Unsigned_integer_type<T const>(), "");
  static_assert(Unsigned_integer_type<T volatile>(), "");
  static_assert(Unsigned_integer_type<T const volatile>(), "");
}  

int 
main() 
{ 
  check<unsigned char>();
  check<unsigned short int>();
  check<unsigned int>();
  check<unsigned long int>();
  check<unsigned long long int>();

  static_assert(!Unsigned_integer_type<char>(), "");
  static_assert(!Unsigned_integer_type<bool>(), "");
  static_assert(!Unsigned_integer_type<int>(), "");
}
