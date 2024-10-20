#pragma once

#include <vector>

#include "Grid.h"
#include "Blocks/Blocks.h"

class Tetris
{
public:
    Tetris();

    Grid GetGrid() const
    {
        return grid;
    }

    Block GetRandomBlock();

    void GameLoop();
    void HandleInput();
    void MoveBlockDown();

private:
    void ResetInternalBlocks();

    bool IsBlockOutOfBounds(int rowOffset = 0, int colOffset = 0);
    ERotationError IsRotatingToOutOfBounds();

    void MoveBlockLeft();
    void MoveBlockRight();

    void RotateBlock();

private:
    Grid grid = Grid();
    Block currBlock;
    Block nextBlock;

    std::vector<Block> internalBlocks;
};