// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

static_assert(origin::Common<int, int>(), "");
static_assert(origin::Common<int, const int>(), "");
static_assert(origin::Common<int, volatile int>(), "");
static_assert(origin::Common<int, const volatile int>(), "");

static_assert(origin::Common<int, int&>(), "");
static_assert(origin::Common<int, const int&>(), "");
static_assert(origin::Common<int, volatile int&>(), "");
static_assert(origin::Common<int, const volatile int&>(), "");

static_assert(origin::Common<signed int, unsigned int>(), "");

// TODO: Write more tests.

int main() { return 0; }
