#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <ios>
#include <numeric>
#include <ranges>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <format>

int total_distance(std::ranges::range auto left,
                   std::ranges::range auto right)
{
  std::vector<int> difference(std::max(left.size(), right.size()));
  std::ranges::transform(left, right, difference.begin(), [](auto l, auto r) { return std::abs(r - l); });
  return std::accumulate(difference.begin(), difference.end(), 0);
}

int similarity_score(std::ranges::range auto left,
                     std::ranges::range auto right)
{
  std::vector<int> occurences(left.size());
  std::ranges::transform(left, occurences.begin(), [&] (auto l) { return std::ranges::count(right, l); });

  std::vector<long> score(left.size());
  std::ranges::transform(left, occurences, score.begin(), std::multiplies<int>());
  return std::accumulate(score.begin(), score.end(), 0);
}

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

  std::cout << std::format("Total difference: {}\n", total_distance(std::ranges::ref_view(left), std::ranges::ref_view(right)));
  std::cout << std::format("Similarity score: {}\n", similarity_score(std::ranges::ref_view(left), std::ranges::ref_view(right)));

  return 0;
}
