#include <cstdio>
#include <cstdlib>
#include <format>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <iostream>


namespace eight_ways
{
    enum class Direction { Right, UpRight, Up, UpLeft, Left, DownLeft, Down, DownRight };
    struct Step { int i = 0; int j = 0; };
    auto go = std::unordered_map<Direction, Step> {
        { Direction::Right,     {  0,  1 } },
        { Direction::UpRight,   { -1,  1 } },
        { Direction::Up,        { -1,  0 } },
        { Direction::UpLeft,    { -1, -1 } },
        { Direction::Left,      {  0, -1 } },
        { Direction::DownLeft,  {  1, -1 } },
        { Direction::Down,      {  1,  0 } },
        { Direction::DownRight, {  1,  1 } },
    };

    std::string stringify(Direction direction)
    {
        switch (direction) {
            case Direction::Right:
                return "Right";
            case Direction::UpRight:
                return "UpRight";
            case Direction::Up:
                return "Up";
            case Direction::UpLeft:
                return "UpLeft";
            case Direction::Left:
                return "Left";
            case Direction::DownLeft:
                return "DownLeft";
            case Direction::Down:
                return "Down";
            case Direction::DownRight:
                return "DownRight";
        }

        std::unreachable();
    }

    bool out_of_bounds(const std::vector<std::string>& matrix, int i, int j)
    {
        return i < 0 || i >= matrix.size() ||
               j < 0 || j >= matrix.front().size();
    }

    int XMASes_in_eight_directions(const std::vector<std::string>& matrix, int i, int j)
    {
        auto count = 0;
        for(auto [direction, step] : go) {
            if (out_of_bounds(matrix, i + 3*step.i, j + 3*step.j))
                continue;

            if (matrix[i + 1*step.i][j + 1*step.j] != 'M') continue;
            if (matrix[i + 2*step.i][j + 2*step.j] != 'A') continue;
            if (matrix[i + 3*step.i][j + 3*step.j] != 'S') continue;

            ++count;
        }

        return count;
    }

    int find_xmasses(const auto& matrix)
    {
        auto xmases = 0;
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix.front().size(); ++j) {
                if (matrix[i][j] != 'X') continue;
                xmases += XMASes_in_eight_directions(matrix, i, j);
            }
        }

        return xmases;
    }
}

namespace crosses
{
    bool is_mas_x_shaped(const auto& matrix, int i, int j)
    {
        auto upright    = matrix[i-1][j+1];
        auto upleft     = matrix[i-1][j-1];
        auto downleft   = matrix[i+1][j-1];
        auto downright  = matrix[i+1][j+1];
        auto slash_is_ok =
            downleft == 'M' && upright == 'S' ||
            downleft == 'S' && upright == 'M';
        auto backslash_is_ok =
            upleft == 'M' && downright == 'S' ||
            upleft == 'S' && downright == 'M';

        return slash_is_ok && backslash_is_ok;
    }

    bool is_mas_plus_shaped(const auto& matrix, int i, int j)
    {
        auto right  = matrix[i][j+1];
        auto left   = matrix[i][j-1];
        auto up     = matrix[i-1][j];
        auto down   = matrix[i+1][j];
        auto vertical =
            up == 'M' && down == 'S' ||
            up == 'S' && down == 'M';
        auto horizontal =
            left == 'M' && right == 'S' ||
            left == 'S' && right == 'M';

        return horizontal && vertical;
    }

    int crossed_masses(const std::vector<std::string>& matrix, int i, int j)
    {
        return is_mas_x_shaped(matrix, i, j) ? 1 : 0;
    }

    int find_xmasses(const auto& matrix)
    {
        auto x_mases = 0;
        for (int i = 1; i < matrix.size() - 1; ++i) {
            for (int j = 1; j < matrix.front().size() - 1; ++j) {
                if (matrix[i][j] != 'A') continue;
                x_mases += crosses::crossed_masses(matrix, i, j);
            }
        }

        return x_mases;
    }
}

int main()
{
    std::fstream input("input.txt");
    if (!input.is_open()) {
        puts("Could not open input.txt");
        return 1;
    }

    std::vector<std::string> matrix;
    for (std::string line; std::getline(input, line);) {
        matrix.push_back(std::move(line));
    }

    std::cout << std::format("XMASes in matrix: {}\n", eight_ways::find_xmasses(matrix));
    std::cout << std::format("Coressed MASes in matrix: {}\n", crosses::find_xmasses(matrix));

    return 0;
}
