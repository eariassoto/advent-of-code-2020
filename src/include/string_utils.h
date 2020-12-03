// Copyright (c) 2020 Emmanuel Arias
#pragma once
#include <functional>
#include <string>

typedef std::function<void(std::string)> SubstringCallback;

void doForEachSubstring(const std::string& inputStr, SubstringCallback callback,
                        const std::string& delimiter = "\n");