// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/core/concepts.hpp>

template<typename T, typename U> void test();

template<typename T, typename U>
  requires origin::Assignable<int&, int>()
void test() { }

int main() { 
  test<int&, int>();
  test<int&, const int>();
  test<int&, volatile int>();
  test<int&, const volatile int>();
}
