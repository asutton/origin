// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.


#include <origin/core/concepts.hpp>

// True when Common_type<T, U> is the same as C.
template<typename T, typename U, typename C>
constexpr bool Has_common_type() {
  return origin::Same<origin::Common_type<T, U>, C>();
}

static_assert(Has_common_type<int, int, int>(), "");
static_assert(Has_common_type<int, const int, int>(), "");
static_assert(Has_common_type<int, volatile int, int>(), "");
static_assert(Has_common_type<int, const volatile int, int>(), "");

static_assert(Has_common_type<int, int&, int>(), "");
static_assert(Has_common_type<int, const int&, int>(), "");
static_assert(Has_common_type<int, volatile int&, int>(), "");
static_assert(Has_common_type<int, const volatile int&, int>(), "");

static_assert(Has_common_type<signed int, unsigned int, unsigned int>(), "");

// TODO: Write more tests.

int main() { }
