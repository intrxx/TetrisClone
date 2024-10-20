#pragma once

#include <raylib.h>
#include <array>

#include "Blocks/Blocks.h"

namespace tetrisStatics
{
    static constexpr Color darkGrey = {26, 31, 40, 255};
    static constexpr Color green = {47, 230, 23, 255};
    static constexpr Color red = {232, 18, 18, 255};
    static constexpr Color orange = {226, 116, 17, 255};
    static constexpr Color yellow = {237, 234, 4, 255};
    static constexpr Color purple = {166, 0, 247, 255};
    static constexpr Color cyan = {21, 204, 209, 255};
    static constexpr Color blue = {13, 64, 216, 255};

    /**
     * 0 = darkGrey,
     * 1 = green,
     * 2 = red,
     * 3 = orange,
     * 4 = yellow,
     * 5 = purple,
     * 6 = cyan,
     * 7 = blue
     */
    static constexpr std::array<Color, 8> tetrisColors = {darkGrey, green, red, orange, yellow, purple, cyan, blue};

    static std::array<Block, 7> tetrisBlocks = {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};

    static constexpr int cellMargin = 1;
    static constexpr int cellSize = 30;
};