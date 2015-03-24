// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

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
