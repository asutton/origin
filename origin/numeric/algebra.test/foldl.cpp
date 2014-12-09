
#include <origin/numeric/algebra.hpp>

#include <cassert>
#include <functional>

using namespace origin;

int 
main() {
  int a[] {1, 2, 3};
  assert(foldl(a, a + 3, std::plus<int>{}, 0) == 6);
  assert(foldl(a, a + 3, Sum<int>()) == 6);
  assert(foldl(a, a + 3, Product<int>()) == 6);


  bool b1[] {true, true, true};
  bool b2[] {false, false, true};
  assert(foldl(b1, b1 + 3, All<>()) == true);
  assert(foldl(b1, b1 + 3, Any<>()) == true);
}
