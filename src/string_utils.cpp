// Copyright (c) 2020 Emmanuel Arias
#include "string_utils.h"

void doForEachSubstring(const std::string& inputStr, SubstringCallback callback,
                        const std::string& delimiter) {
    auto start = 0U;
    auto end = inputStr.find(delimiter);
    while (end != std::string::npos) {
        callback(inputStr.substr(start, end - start));
        start = end + delimiter.length();
        end = inputStr.find(delimiter, start);
    }
    callback(inputStr.substr(start, end));
}
