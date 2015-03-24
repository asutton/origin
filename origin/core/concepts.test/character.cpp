
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

using namespace origin;

template<typename T>
void
check_narrow_character()
{
  static_assert(Narrow_character_type<T>(), "");
  static_assert(Narrow_character_type<T const>(), "");
  static_assert(Narrow_character_type<T volatile>(), "");
  static_assert(Narrow_character_type<T const volatile>(), "");
}

template<typename T>
void
check_wide_character()
{
  static_assert(Wide_character_type<T>(), "");
  static_assert(Wide_character_type<T const>(), "");
  static_assert(Wide_character_type<T volatile>(), "");
  static_assert(Wide_character_type<T const volatile>(), "");
}

int 
main() 
{ 
  check_narrow_character<char>();
  check_narrow_character<signed char>();
  check_narrow_character<unsigned char>();

  check_wide_character<char16_t>();
  check_wide_character<char32_t>();
  check_wide_character<wchar_t>();
}
