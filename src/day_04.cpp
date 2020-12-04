// Copyright (c) 2020 Emmanuel Arias
#include "day_04.h"

#include <exception>
#include <functional>
#include <string>

#include "string_utils.h"

bool byrValidator(const std::string& input) {
    try {
        int year = std::stoi(input);
        return year >= 1920 && year <= 2002;
    } catch (std::exception e) {
        return false;
    }
};

bool iyrValidator(const std::string& input) {
    try {
        int year = std::stoi(input);
        return year >= 2010 && year <= 2020;
    } catch (std::exception e) {
        return false;
    }
};

bool eyrValidator(const std::string& input) {
    try {
        int year = std::stoi(input);
        return year >= 2020 && year <= 2030;
    } catch (std::exception e) {
        return false;
    }
};

bool hgtValidator(const std::string& input) {
    if (input.size() < 4) {
        return false;
    }
    std::string measure = input.substr(input.size() - 2);
    int min = 0;
    int max = 0;
    if (measure == "cm") {
        min = 150;
        max = 193;
    } else if (measure == "in") {
        min = 59;
        max = 76;
    } else {
        return false;
    }

    try {
        int height = std::stoi(input);
        return height >= min && height <= max;
    } catch (std::exception e) {
        return false;
    }
};

bool hclValidator(const std::string& input) {
    if (input.size() != 7) {
        return false;
    }
    for (size_t i = 0; i < 7; ++i) {
        if (i == 0) {
            if (input[i] != '#') return false;
        } else {
            if (!isalnum(input[i])) {
                return false;
            }
        }
    }
    return true;
}

bool eclValidator(const std::string& input) {
    bool isValidColor = input == "amb" || input == "blu" || input == "brn" ||
                        input == "gry" || input == "grn" || input == "hzl" ||
                        input == "oth";
    return isValidColor;
}

bool pidValidator(const std::string& input) {
    if (input.size() != 9) {
        return false;
    }
    for (size_t i = 0; i < 9; ++i) {
        if (!isdigit(input[i])) {
            return false;
        }
    }
    return true;
}

static constexpr const char* requiredFields[7] = {
    "byr:", "iyr:", "eyr:", "hgt:", "hcl:", "ecl:", "pid:"};

typedef bool (*ValidatorCallback)(const std::string&);

static constexpr ValidatorCallback validatorCallbacks[7] = {
    &byrValidator, &iyrValidator, &eyrValidator, &hgtValidator,
    &hclValidator, &eclValidator, pidValidator};

std::string day_04_01(const std::string& input) {
    int validPassports = 0;
    doForEachSubstring(
        input,
        [&](std::string input) {
            bool allFieldsFound = true;
            for (const char* field : requiredFields) {
                size_t found = input.find(field);
                if (found == input.npos) {
                    allFieldsFound = false;
                }
            }
            if (allFieldsFound) {
                ++validPassports;
            }
        },
        "\n\n");

    return std::to_string(validPassports);
}

std::string day_04_02(const std::string& input) {
    int validPassports = 0;
    doForEachSubstring(
        input,
        [&](std::string input) {
            bool allFieldsFoundAndValid = true;
            for (int i = 0; i < 7; ++i) {
                size_t found = input.find(requiredFields[i]);
                if (found == input.npos) {
                    allFieldsFoundAndValid = false;
                } else {
                    std::string value;
                    found += 3;
                    while (++found < input.size() && !isspace(input[found])) {
                        value += input[found];
                    }
                    bool isValid = validatorCallbacks[i](value);
                    if (!isValid) {
                        allFieldsFoundAndValid = false;
                    }
                }
            }
            if (allFieldsFoundAndValid) {
                ++validPassports;
            }
        },
        "\n\n");

    return std::to_string(validPassports);
}
