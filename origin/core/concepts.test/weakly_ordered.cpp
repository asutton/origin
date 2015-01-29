// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

struct S0 { };

struct S1 
{
  bool operator<(S1) const;
};

struct S2
{
  bool operator<(S2) const;
  bool operator>(S2) const;
  bool operator<=(S2) const;
  bool operator>=(S2) const;
};

static_assert(origin::Weakly_ordered<int>(), "");
static_assert(origin::Weakly_ordered<float>(), "");
static_assert(not origin::Weakly_ordered<S0>(), "");
static_assert(not origin::Weakly_ordered<S1>(), "");
static_assert(origin::Weakly_ordered<S2>(), "");

static_assert(origin::Weakly_ordered<int, long>(), "");
static_assert(not origin::Weakly_ordered<int, S0>(), "");

int main() { return 0; }
