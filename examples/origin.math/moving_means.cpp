#include <origin.math/stats.hpp>
#include <iostream>
int main() {
  std::vector<double> values = {1, 2, 3, 4, 5, 6};
  auto f = std::begin(values);
  auto l = std::end(values);
  for (auto x : origin::moving_means(f, f + 2, l)) {
    std::cout << x << std::endl;
  }
}
