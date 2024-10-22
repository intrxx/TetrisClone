#include <iostream>

#include "../Public/Grid.h"

void Grid::Draw()
{
   const int margin = tetrisStatics::cellMargin;
   const int cellSize = tetrisStatics::cellSize;

    for(int row = 0; row < numberOfRows; row++)
    {
        for(int col = 0; col < numberOfColumns; col++)
        {
           int cellValue = gridArr[row][col];
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
    if(!IsCellEmpty(row, col))
    {
        return ERotationError::RE_CellTaken;
    }

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

bool Grid::IsCellEmpty(int row, int col)
{
    if(gridArr[row][col] == 0)
    {
        return true;
    }
    return false;
}

void Grid::Debug_PrintGridNumbers()
{
    for(auto& row: gridArr)
    {
        for(int col : row)
        {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
}

int Grid::ClearFullRows()
{
    int completed = 0;

    for(int row = numberOfRows - 1; row >= 0; row--)
    {
        if(IsRowFull(row))
        {
            completed++;
            ClearRow(row);
        }
        else if(completed > 0)
        {
            MoveRowDownByNumber(row, completed);
        }
    }

    return completed;
}

bool Grid::IsRowFull(int row)
{
    for(int col = 0; col < numberOfColumns; col++)
    {
        if(gridArr[row][col] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for(int col = 0; col < numberOfColumns; col++)
    {
        gridArr[row][col] = 0;
    }
}

void Grid::MoveRowDownByNumber(int row, int numRows)
{
    for(int col = 0; col < numberOfColumns; col++)
    {
        gridArr[row + numRows][col] = gridArr[row][col];
        gridArr[row][col] = 0;
    }
}

void Grid::ClearEntireGrid()
{
    for(int row = 0; row < numberOfRows; row++)
    {
        ClearRow(row);
    }
}



