// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

// True when Difference_type<T> is the same as U.
template<typename T, typename U>
constexpr bool Has_difference_type()
{
  return origin::Same<origin::Difference_type<T>, U>();
}

struct S
{
  using difference_type = int;
};

static_assert(Has_difference_type<int*, std::ptrdiff_t>(), "");
static_assert(Has_difference_type<const int*, std::ptrdiff_t>(), "");
static_assert(Has_difference_type<int[], std::ptrdiff_t>(), "");
static_assert(Has_difference_type<int[1], std::ptrdiff_t>(), "");
static_assert(Has_difference_type<S, int>(), "");

int main() { return 0; }
