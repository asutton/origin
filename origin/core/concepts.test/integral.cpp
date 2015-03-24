// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

using namespace origin;

template<typename T>
void
check_integral()
{
  static_assert(Integral_type<T>(), "");
  static_assert(Integral_type<T const>(), "");
  static_assert(Integral_type<T volatile>(), "");
  static_assert(Integral_type<T const volatile>(), "");
}

template<Integral_type T>
  constexpr int value(T) { return 0; }

template<Narrow_character_type T>
  constexpr int value(T) { return 1; }

template<Wide_character_type T>
  constexpr int value(T) { return 2; }

template<Signed_integer_type T>
  constexpr int value(T) { return 3; }

template<Unsigned_integer_type T>
  constexpr int value(T) { return 4; }

int 
main() 
{ 
  // Bool is integral
  check_integral<bool>();

  // Character types are integral
  check_integral<char>();
  check_integral<signed char>();
  check_integral<unsigned char>();
  check_integral<char16_t>();
  check_integral<char32_t>();
  check_integral<wchar_t>();

  // Signed integers are integral
  check_integral<signed char>();
  check_integral<short int>();
  check_integral<int>();
  check_integral<long int>();
  check_integral<long long int>();

  // Unsigned integers are integral
  check_integral<unsigned char>();
  check_integral<unsigned short int>();
  check_integral<unsigned int>();
  check_integral<unsigned long int>();
  check_integral<unsigned long long int>();

  // Check ordering
  static_assert(value(true) == 0, "");
  static_assert(value('a')  == 1, "");
  static_assert(value(L'a') == 2, "");
  static_assert(value(0)    == 3, "");
  static_assert(value(0u)   == 4, "");
}
