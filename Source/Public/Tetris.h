#pragma once

#include <vector>

#include "Grid.h"
#include "Blocks/Blocks.h"

class Tetris
{
public:
    Tetris();
    ~Tetris();

    Grid GetGrid() const
    {
        return grid;
    }

    void GameLoop();
    void HandleInput();
    void MoveBlockDown();

    void HandleFullRows();

public:
    bool bGameOver = false;

    Font fontinRegular = Font();
    Font fontinSmallCaps = Font();
    Font fontinBold = Font();

    Music backgroundMusic;

private:
    void ResetInternalBlocks();

    bool IsBlockOutOfBounds(Block blockToCheck, int rowOffset = 0, int colOffset = 0);
    bool CanRotate(Block blockToCheck);
    bool IsThereSpaceForBlock(Block blockToCheck, int rowOffset = 0, int colOffset = 0);

    void MoveBlockLeft();
    void MoveBlockRight();
    void RotateBlock();
    void LockBlock();
    void InstantPlacement();

    void SpawnNewBlock();
    void SpawnDummyBlock();

    void ResetGame();

    bool CanMoveRight(const Block& blockToMove);
    bool CanMoveLeft(const Block& blockToMove);
    bool CanMoveDown(const Block& blockToMove);

    void UpdateScore(const SScoreStats& scoreStats);

    Block GetRandomBlock();

private:
    Grid grid = Grid();

    int score = 0;

    Block nextBlock;
    Block currBlock;

    std::vector<Block> internalBlocks;

    Sound rotateSound;
    Sound clearSound;
};