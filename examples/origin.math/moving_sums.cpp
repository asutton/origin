#include <origin.math/stats.hpp>
#include <iostream>
#include <iterator>

int main() {
  std::vector<double> values = {1, 2, 3, 4, 5, 6};
  auto f = std::begin(values);
  auto l = std::end(values);
  std::vector<int> result;
  origin::moving_sums(f, f + 2, l, std::back_inserter(result),  0.0);
  for (auto x : result) {
    std::cout << x << std::endl;
  }
  return 0; 
}
