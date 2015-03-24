
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

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
