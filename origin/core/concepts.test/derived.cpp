// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

template<typename T, typename U>
concept bool 
My_derived() 
{
  return requires (T t) { {t} -> U& };
}

struct B { };
struct D1 : B { };
class D2 : B { };

static_assert(My_derived<B, B>(), "");
static_assert(My_derived<D1, B>(), "");
static_assert(!My_derived<D2, B>(), "");

// TODO: write tests for virtual inheritance.

int 
main() 
{
  // D2 x;
  // B& b = x;
  return 0;
}
