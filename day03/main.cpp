#include <algorithm>
#include <bits/ranges_algo.h>
#include <cstdio>
#include <cstdlib>
#include <format>
#include <fstream>
#include <iterator>
#include <ranges>
#include <regex>
#include <string>
#include <iostream>

int sum_part_1(const std::string& memory)
{
    std::regex mul_regex{ R"(mul\((\d+),(\d+)\))" };
    auto mul_begin = std::sregex_iterator(memory.begin(), memory.end(), mul_regex);
    auto mul_end = std::sregex_iterator();

    auto multiply_matches = [] (auto match) { return std::stoi(match[1]) * std::stoi(match[2]); }; 
    auto muls = std::ranges::subrange{mul_begin, mul_end} | std::views::transform(multiply_matches);
    return std::ranges::fold_left(muls, 0, std::plus<int>{});
}

int sum_part_2(const std::string& memory)
{
    std::regex conditional_mul{ R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))" };
    auto mul_begin = std::sregex_iterator(memory.begin(), memory.end(), conditional_mul);
    auto mul_end = std::sregex_iterator();

    auto matches = std::ranges::subrange(mul_begin, mul_end);
    bool enabled = true;
    auto multiply_conditionally = [&enabled] (auto match) {
        if (match.str() == "do()") {
            enabled = true;
            return 0;
        }

        if (match.str() == "don't()") {
            enabled = false;
            return 0;
        }

        return enabled
            ? std::stoi(match[1]) * std::stoi(match[2])
            : 0;
    };

    return std::ranges::fold_left(matches | std::views::transform(multiply_conditionally), 0, std::plus<int>{});
}

int main()
{
    std::fstream input("input.txt");
    if (!input.is_open()) {
        puts("Could not open input.txt");
        return 1;
    }

    std::string memory{std::istreambuf_iterator<char>(input), {}};

    std::cout << std::format("Sum of multiplications is: {}\n", sum_part_1(memory));
    std::cout << std::format("Sum of conditional mulitplications is: {}\n", sum_part_2(memory));

    return 0;
}
