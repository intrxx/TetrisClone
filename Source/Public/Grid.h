#pragma once

#include <array>
#include <raylib.h>
#include "TetrisTypes.h"

class Grid
{
public:
    Grid();

    void Draw();

    void Debug_PrintGridNumbers();
    static bool IsCellOutOfBounds(int row, int col);
    static ERotationError IsCellOutOfRotatingBound(int row, int col);

public:
    int grid[20][10] = {0};

private:
    static constexpr int numberOfRows = 20;
    static constexpr int numberOfColumns = 10;
};