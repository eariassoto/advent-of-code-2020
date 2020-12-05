// Copyright (c) 2020 Emmanuel Arias
#include "day_05.h"

#include <algorithm>
#include <vector>

#include "string_utils.h"

std::string day_05_01(const std::string& input) {
    size_t highestId = 0;

    auto CalculateBinaryIndexes = [](std::pair<size_t, size_t>& indexes,
                                     bool isLow) {
        if (indexes.second - indexes.first == 1) {
            if (isLow) {
                indexes.second = indexes.first;
            } else {
                indexes.first = indexes.second;
            }
            return;
        }
        float center = static_cast<float>(indexes.second + indexes.first) / 2;
        if (isLow) {
            indexes.second = static_cast<size_t>(floor(center));
        } else {
            indexes.first = static_cast<size_t>(ceil(center));
        }
    };

    doForEachSubstring(input, [&](std::string input) {
        std::pair<size_t, size_t> planeRow = std::make_pair(0, 127);
        for (int i = 0; i < 7; ++i) {
            CalculateBinaryIndexes(planeRow, input[i] == 'F');
        }
        std::pair<size_t, size_t> planeSeat = std::make_pair(0, 7);
        for (int j = 7; j < 10; ++j) {
            CalculateBinaryIndexes(planeSeat, input[j] == 'L');
        }
        size_t currentId = (planeRow.first * 8) + planeSeat.first;
        if (currentId > highestId) {
            highestId = currentId;
        }
    });

    return std::to_string(highestId);
}

std::string day_05_02(const std::string& input) {
    std::vector<size_t> allIds;

    auto CalculateBinaryIndexes = [](std::pair<size_t, size_t>& indexes,
                                     bool isLow) {
        if (indexes.second - indexes.first == 1) {
            if (isLow) {
                indexes.second = indexes.first;
            } else {
                indexes.first = indexes.second;
            }
            return;
        }
        float center = static_cast<float>(indexes.second + indexes.first) / 2;
        if (isLow) {
            indexes.second = static_cast<size_t>(floor(center));
        } else {
            indexes.first = static_cast<size_t>(ceil(center));
        }
    };

    doForEachSubstring(input, [&](std::string input) {
        std::pair<size_t, size_t> planeRow = std::make_pair(0, 127);
        for (int i = 0; i < 7; ++i) {
            CalculateBinaryIndexes(planeRow, input[i] == 'F');
        }
        std::pair<size_t, size_t> planeSeat = std::make_pair(0, 7);
        for (int j = 7; j < 10; ++j) {
            CalculateBinaryIndexes(planeSeat, input[j] == 'L');
        }
        allIds.push_back((planeRow.first * 8) + planeSeat.first);
    });

    // Sort them in ascending order
    std::sort(allIds.begin(), allIds.end(), std::less<size_t>());
    size_t myId = 0;
    for (size_t i = 0; i < allIds.size(); ++i) {
        if ((allIds[i + 1] - allIds[i]) == 2) {
            myId = allIds[i] + 1;
            break;
        }
    }

    return std::to_string(myId);
}
