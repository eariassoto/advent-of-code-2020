// Copyright (c) 2020 Emmanuel Arias
#include "day_03.h"

#include <vector>

#include "string_utils.h"

std::string day_03_01(const std::string& input) {
    size_t treesHitted = 0;
    // flattened matrix
    std::vector<bool> map;
    int rows = 0;
    doForEachSubstring(input, [&](std::string input) {
        for (char c : input) {
            map.push_back((c == '#'));
        }
        ++rows;
    });
    int columns = map.size() / rows;

    // helper lambda function
    auto GetCoordinateFor = [&](size_t row, size_t column) -> int {
        // wrap around the column axis
        column = column % columns;
        return (row * columns) + column;
    };

    size_t auxColumn = 0;
    for (size_t i = 1; i < rows; ++i) {
        auxColumn += 3;
        if (map[GetCoordinateFor(i, auxColumn)]) {
            ++treesHitted;
        }
    }

    return std::to_string(treesHitted);
}

std::string day_03_02(const std::string& input) {
    // flattened matrix
    std::vector<bool> map;
    int rows = 0;
    doForEachSubstring(input, [&](std::string input) {
        for (char c : input) {
            map.push_back((c == '#'));
        }
        ++rows;
    });
    int columns = map.size() / rows;

    // helper lambda function
    auto GetCoordinateFor = [&](size_t row, size_t column) -> int {
        // wrap around the column axis
        column = column % columns;
        return (row * columns) + column;
    };

    auto CalculateTreesHitted = [&](size_t colMovement,
                                    size_t rowMovement) -> size_t {
        size_t treeCount = 0;
        size_t auxColumn = 0;
        for (size_t i = rowMovement; i < rows; i += rowMovement) {
            auxColumn += colMovement;
            if (map[GetCoordinateFor(i, auxColumn)]) {
                ++treeCount;
            }
        }
        return treeCount;
    };

    size_t treesHitted = 1;
    treesHitted *= CalculateTreesHitted(1, 1);
    treesHitted *= CalculateTreesHitted(3, 1);
    treesHitted *= CalculateTreesHitted(5, 1);
    treesHitted *= CalculateTreesHitted(7, 1);
    treesHitted *= CalculateTreesHitted(1, 2);

    return std::to_string(treesHitted);
}
