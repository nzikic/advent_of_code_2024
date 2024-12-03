#include <algorithm>
#include <cstdlib>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <ranges>
#include <string>


bool is_sorted(std::ranges::range auto report)
{
    return std::ranges::is_sorted(report, std::ranges::less{}) ||
           std::ranges::is_sorted(report, std::ranges::greater{});
}

bool are_adjascent_values_close(std::ranges::range auto report)
{
    auto abs_diff = [] (auto value) { return std::abs(std::get<0>(value) - std::get<1>(value)); };
    auto between_1_and_3 = [] (auto value) { return value >= 1 && value <=3; };

    auto differences = report | std::views::adjacent<2> | std::views::transform(abs_diff);

    return std::ranges::all_of(differences, between_1_and_3);
}

bool report_is_safe(std::ranges::range auto report)
{
    return is_sorted(report) && are_adjascent_values_close(report);
}

int main()
{
    std::fstream input("input.txt");
    if (!input.is_open()) {
        puts("Could not open input.txt");
        return 1;
    }

    std::vector<std::vector<int>> reports;

    for (std::string line; std::getline(input, line);) {
        if (line.empty())
            continue;

        std::vector<int> report;
        using std::operator""sv;
        for (const auto word : std::views::split(line, " "sv)) {
            report.push_back(std::stoi(std::ranges::to<std::string>(word)));
        }

        reports.push_back(report);
    }
    

    std::cout << std::format("Number of safe reports: {}\n", std::ranges::count_if(reports, [&](auto report) { return report_is_safe(report); }));

    return 0;
}