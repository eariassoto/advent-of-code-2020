// Copyright (c) 2020 Emmanuel Arias
#include "day_02.h"

#include <algorithm>

#include "string_utils.h"

std::string day_02_01(const std::string& input) {
    size_t validPasswords = 0;
    doForEachSubstring(input, [&](std::string input) {
        std::size_t hyphenIndex = input.find('-');
        int min = std::stoi(input.substr(0, hyphenIndex));

        std::size_t firstSpaceIndex = input.find(' ', hyphenIndex);
        int max = std::stoi(input.substr(hyphenIndex + 1, firstSpaceIndex));

        char letter = input[firstSpaceIndex + 1];

        std::string password = input.substr(firstSpaceIndex + 3);

        size_t letterCount =
            std::count(password.begin(), password.end(), letter);
        if (letterCount >= min && letterCount <= max) {
            ++validPasswords;
        }
    });

    return std::to_string(validPasswords);
}
std::string day_02_02(const std::string& input) {
    size_t validPasswords = 0;
    doForEachSubstring(input, [&](std::string input) {
        std::size_t hyphenIndex = input.find('-');
        int firstPossiblePosition = std::stoi(input.substr(0, hyphenIndex)) - 1;

        std::size_t firstSpaceIndex = input.find(' ', hyphenIndex);
        int secondPossiblePosition =
            std::stoi(input.substr(hyphenIndex + 1, firstSpaceIndex)) - 1;

        char letter = input[firstSpaceIndex + 1];

        std::string password = input.substr(firstSpaceIndex + 4);

        if (password[firstPossiblePosition] == letter) {
            if (password[secondPossiblePosition] != letter) ++validPasswords;
        } else {
            if (password[secondPossiblePosition] == letter) ++validPasswords;
        }
    });

    return std::to_string(validPasswords);
}
