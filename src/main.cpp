// Copyright (c) 2020 Emmanuel Arias
#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include "day_01.h"
#include "day_02.h"
#include "day_03.h"
#include "day_04.h"
#include "day_05.h"
#include "day_06.h"

typedef std::string (*PuzzlePhaseFunc)(const std::string& input);

int main(int argc, char* argv[]) {
    constexpr std::array<PuzzlePhaseFunc, 6> phase1Puzzles{
        day_01_01, day_02_01, day_03_01, day_04_01, day_05_01, day_06_01};
    constexpr std::array<PuzzlePhaseFunc, 6> phase2Puzzles{
        day_01_02, day_02_02, day_03_02, day_04_02, day_05_02, day_06_02};

    if (argc < 4) {
        std::cout << "Day, phase, or input file path missing.\n";
        return 1;
    }

    size_t day = static_cast<size_t>(argv[1][0]) - '0';
    bool validDayPhaseInput = false;
    size_t phase = static_cast<size_t>(argv[2][0]) - '0';
    if (phase == 1) {
        validDayPhaseInput = phase1Puzzles.size() >= day;
    } else if (phase == 2) {
        validDayPhaseInput = phase2Puzzles.size() >= day;
    }
    if (!validDayPhaseInput) {
        std::cout << "Invalid phase " << phase << " for day " << day << ".\n";
        return 1;
    }

    std::ifstream inputFile(argv[3]);
    if (!inputFile.is_open()) {
        std::cout << "Input file cannot be opened.\n";
        return 1;
    }

    std::string inputStr((std::istreambuf_iterator<char>(inputFile)),
                         std::istreambuf_iterator<char>());

    std::string result;
    if (phase == 1) {
        result = phase1Puzzles[day - 1](inputStr);
    } else if (phase == 2) {
        result = phase2Puzzles[day - 1](inputStr);
    }
    std::cout << result << '\n';

    return 0;
}
