#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <stdio.h>
#include <iostream>
#include <vector>


int main() {
  std::fstream input{"input.txt", std::ios::in};
  if (!input.is_open()) {
    puts("file couldn't be opened");
    return 1;
  }

  std::vector<int> left;
  std::vector<int> right;
  for (int l{0}, r{0}; input >> l >> r;) {
    left.push_back(l);
    right.push_back(r);
  }

  std::ranges::sort(left);
  std::ranges::sort(right);

  std::vector<int> difference(std::max(left.size(), right.size()));

  std::ranges::transform(left, right, difference.begin(), [](auto l, auto r) { return std::abs(r - l); });

  auto total_difference = std::accumulate(difference.begin(), difference.end(), 0);
  std::cout << total_difference << "\n";

  return 0;
}
