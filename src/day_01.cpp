// Copyright (c) 2020 Emmanuel Arias
#include "day_01.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "string_utils.h"

int checkIfSumIs2020(const std::vector<int>& input, size_t indexToSearch,
                     size_t start, size_t end) {
    size_t center = static_cast<size_t>((end + start) / 2);

    int result = input[indexToSearch] + input[center];

    if (result > 2020) {
        // go left
        if ((end - start) <= 1) {
            // not found
            return -1;
        }
        // calculate next call
        return checkIfSumIs2020(input, indexToSearch, start, center);

    } else if (result < 2020) {
        // go right
        if ((end - start) <= 1) {
            // not found
            return -1;
        }
        // calculate next call
        return checkIfSumIs2020(input, indexToSearch, center, end);
    } else {
        // found it
        return input[indexToSearch] * input[center];
    }
}

std::string day_01_01(const std::string& input) {
    std::vector<int> inputNumbers;

    // Read all numbers
    doForEachSubstring(input, [&](std::string input) {
        int number = std::stoi(input);
        inputNumbers.push_back(number);
    });

    // Sort them in ascending order
    std::sort(inputNumbers.begin(), inputNumbers.end(), std::less<int>());

    // Do a binary search from the end to the top
    size_t aux = inputNumbers.size() - 1;
    int result = -1;
    while (aux > 0) {
        result = checkIfSumIs2020(inputNumbers, aux, 0, aux - 1);
        if (result != -1) break;
        --aux;
    }

    return std::to_string(result);
}

int checkIfDoubleSumIs2020(const std::vector<int>& input,
                           size_t indexToSearch) {
    int indexToSearchValue = input[indexToSearch];
    size_t firstPossibleEndIndex = indexToSearch - 1;
    while (firstPossibleEndIndex > 0 &&
           indexToSearchValue + input[firstPossibleEndIndex] >= 2020) {
        --firstPossibleEndIndex;
    }

    // Try all possible second values
    for (size_t endIndex = firstPossibleEndIndex; endIndex > 0; --endIndex) {
        int endIndexValue = input[endIndex];
        // Iterate from the beggining finding a pair
        for (int startIndex = 0; startIndex < endIndex; ++startIndex) {
            int doubleSum =
                indexToSearchValue + endIndexValue + input[startIndex];
            if (doubleSum == 2020) {
                return static_cast<int>(indexToSearchValue * endIndexValue *
                                        input[startIndex]);
            }
        }
    }
    return -1;
}

std::string day_01_02(const std::string& input) {
    std::vector<int> inputNumbers;

    // Read all numbers
    doForEachSubstring(input, [&](std::string input) {
        int number = std::stoi(input);
        inputNumbers.push_back(number);
    });

    // Sort them in ascending order
    std::sort(inputNumbers.begin(), inputNumbers.end(), std::less<int>());

    // Try to find the three indexes starting from the last one, why? no particular
    // reason. Maybe it would be nice to have some kind of heuristics here to decide
    // This algorithm is iterative and very dumb
    int result = -1;
    for (size_t i = inputNumbers.size() - 1; result == -1 && i >= 2; --i) {
        result = checkIfDoubleSumIs2020(inputNumbers, i);
    }

    return std::to_string(result);
}
