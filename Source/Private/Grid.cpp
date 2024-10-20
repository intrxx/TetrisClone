#include "../Public/Grid.h"
#include <iostream>

Grid::Grid()
{

}

void Grid::Draw()
{
   const int margin = tetrisStatics::cellMargin;
   const int cellSize = tetrisStatics::cellSize;

    for(int row = 0; row < numberOfRows; row++)
    {
        for(int col = 0; col < numberOfColumns; col++)
        {
           int cellValue = grid[row][col];
           DrawRectangle(col * cellSize + margin, row * cellSize + margin, cellSize - margin,
                         cellSize - margin, tetrisStatics::tetrisColors[cellValue]);
        }
    }
}

bool Grid::IsCellOutOfBounds(int row, int col)
{
    if(row < 0 || col < 0 || row > numberOfRows - 1 || col > numberOfColumns - 1)
    {
        return true;
    }
    return false;
}

ERotationError Grid::IsCellOutOfRotatingBound(int row, int col)
{
    if(col < 0)
    {
        return ERotationError::RE_LeftSide;
    }
    if(col > numberOfColumns - 1)
    {
        return ERotationError::RE_RightSide;
    }
    if(row > numberOfRows - 1)
    {
        return ERotationError::RE_Down;
    }

    return ERotationError::RE_NoError;
}

void Grid::Debug_PrintGridNumbers()
{
    for(auto& row: grid)
    {
        for(int col : row)
        {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
}


