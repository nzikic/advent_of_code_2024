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

int main()
{
    std::fstream input("input.txt");
    if (!input.is_open()) {
        puts("Could not open input.txt");
        return 1;
    }
    
    //std::string memory = "mul, mul(4), mul(1,2), mulia( 1 ,  3 ),asddmul(!2,4)dsdsmul(10,20)aaaaa_";
    std::string memory{std::istreambuf_iterator<char>(input), {}};


    std::cout << std::format("Sum of multiplications is: {}\n", sum_part_1(memory));

    return 0;
}
