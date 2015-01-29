// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

struct S0 {
  S0(const S0&) = default;
};

struct S1 {
  S1(const S1&) = delete;
};

class S2 {
  S2(const S2&);
};

struct S3 {
  S3(S3&&) = delete;
  S3(const S3&) = default;
};

static_assert(origin::Copy_constructible<int>(), "");
static_assert(origin::Copy_constructible<S0>(), "");
static_assert(not origin::Copy_constructible<S1>(), "");
static_assert(not origin::Copy_constructible<S2>(), "");
static_assert(not origin::Copy_constructible<S3>(), "");

int main() { return 0; }
