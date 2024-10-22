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

    void HandleFullRows();

public:
    bool bGameOver = false;

private:
    void ResetInternalBlocks();

    bool IsBlockOutOfBounds(Block blockToCheck, int rowOffset = 0, int colOffset = 0);
    bool CanRotate(Block blockToCheck);
    bool IsThereSpaceForBlock(Block blockToCheck, int rowOffset = 0, int colOffset = 0);

    void MoveBlockLeft();
    void MoveBlockRight();
    void RotateBlock();
    void LockBlock();

    void SpawnNewBlock();
    void SpawnDummyBlock();

    void ResetGame();

    bool CanMoveRight(const Block& blockToMove);
    bool CanMoveLeft(const Block& blockToMove);
    bool CanMoveDown(const Block& blockToMove);

private:
    Grid grid = Grid();

    Block nextBlock;
    Block currBlock;

    std::vector<Block> internalBlocks;
};