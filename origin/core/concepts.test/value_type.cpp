// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

// True when Value_type<T> is the same as U.
template<typename T, typename U>
constexpr bool Has_value_type()
{
  return origin::Same<origin::Value_type<T>, U>();
}

struct S
{
  using value_type = int;
};

static_assert(Has_value_type<int*, int>(), "");
static_assert(Has_value_type<const int*, int>(), "");
static_assert(Has_value_type<int[], int>(), "");
static_assert(Has_value_type<int[1], int>(), "");
static_assert(Has_value_type<S, int>(), "");

int main() { return 0; }
