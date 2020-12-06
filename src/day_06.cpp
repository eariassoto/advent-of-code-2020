// Copyright (c) 2020 Emmanuel Arias
#include "day_06.h"

#include <array>

#include "string_utils.h"

std::string day_06_01(const std::string& input) {
    std::array<bool, 26> questionTable;

    auto ClearQuestionTable = [&]() -> void {
        for (auto& question : questionTable) {
            question = false;
        }
    };

    auto CountQuestionsInTable = [&]() -> size_t {
        size_t res = 0;
        for (auto& question : questionTable) {
            if (question) {
                ++res;
            }
        }
        return res;
    };
    size_t totalCount = 0;
    doForEachSubstring(
        input,
        [&](std::string input) {
            ClearQuestionTable();
            for (char question : input) {
                if (isalpha(question)) {
                    questionTable[question - 'a'] = true;
                }
            }
            totalCount += CountQuestionsInTable();
        },
        "\n\n");

    return std::to_string(totalCount);
}

std::string day_06_02(const std::string& input) {
    std::array<size_t, 26> questionTable;

    auto ClearQuestionTable = [&]() -> void {
        for (auto& question : questionTable) {
            question = 0;
        }
    };

    auto CountQuestionsAllLinesInTable = [&](size_t numLines) -> size_t {
        size_t res = 0;
        for (auto& question : questionTable) {
            if (question == numLines) {
                ++res;
            }
        }
        return res;
    };

    size_t totalCount = 0;
    doForEachSubstring(
        input,
        [&](std::string input) {
            ClearQuestionTable();
            size_t numLines = 1;
            for (char question : input) {
                if (isalpha(question)) {
                    questionTable[question - 'a'] += 1;
                } else if (isspace(question)) {
                    ++numLines;
                }
            }
            totalCount += CountQuestionsAllLinesInTable(numLines);
        },
        "\n\n");

    return std::to_string(totalCount);
}
