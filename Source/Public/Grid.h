#pragma once

#include <array>
#include <raylib.h>
#include "TetrisTypes.h"

class Grid
{
public:
    Grid() = default;

    void Draw();

    void Debug_PrintGridNumbers();

    static bool IsCellOutOfBounds(int row, int col);
    bool IsCellEmpty(int row, int col);
    ERotationError IsCellOutOfRotatingBound(int row, int col);

    int ClearFullRows();
    void ClearEntireGrid();

public:
    std::array<std::array<int, 10>, 20> gridArr{0};

private:
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDownByNumber(int row, int numRows);



private:
    static constexpr int numberOfRows = 20;
    static constexpr int numberOfColumns = 10;
};