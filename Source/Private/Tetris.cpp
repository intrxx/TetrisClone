#include <random>
#include <algorithm>
#include <iostream>
#include <utility>

#include "../Public/Tetris.h"

Tetris::Tetris()
{
    internalBlocks.reserve(7);
    ResetInternalBlocks();

    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}

void Tetris::GameLoop()
{
    grid.Draw();
    currBlock.Draw();
}

void Tetris::HandleInput()
{
    int keyPressed = GetKeyPressed();

    if(bGameOver && keyPressed == KEY_R)
    {
        bGameOver = false;
        ResetGame();
    }

    switch(keyPressed)
    {
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            break;
        case KEY_A:
            MoveBlockLeft();
            break;
        case KEY_D:
            MoveBlockRight();
            break;
        case KEY_S:
            MoveBlockDown();
            break;
        case KEY_W:
            RotateBlock();
            break;
        case KEY_UP:
            RotateBlock();
            break;
        default:
            break;
    }
}

Block Tetris::GetRandomBlock()
{
    if(internalBlocks.empty())
    {
        ResetInternalBlocks();
    }

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::mt19937::result_type> distBlockSize(0, (int)internalBlocks.size() - 1);

    unsigned int randomNum = distBlockSize(rng);

    Block block = internalBlocks[randomNum];
    internalBlocks.erase(internalBlocks.begin() + randomNum);

    return block;
}

void Tetris::ResetInternalBlocks()
{
    const int size = tetrisStatics::tetrisBlocks.size();

    for(int i = 0; i < size; i++)
    {
        internalBlocks.push_back(tetrisStatics::tetrisBlocks[i]);
    }
}

void Tetris::MoveBlockLeft()
{
    if(CanMoveLeft(currBlock))
    {
        currBlock.Move(0, -1);
    }
}

void Tetris::MoveBlockRight()
{
    if(CanMoveRight(currBlock))
    {
        currBlock.Move(0, 1);
    }
}

void Tetris::MoveBlockDown()
{
    if(CanMoveDown(currBlock))
    {
        currBlock.Move(1, 0);
        return;
    }
    LockBlock();
}

void Tetris::RotateBlock()
{
    Block copyCurr = currBlock;

    const bool bCanRotate = CanRotate(currBlock);

    if(!bCanRotate)
    {
        //TODO Make corrections

        for(int i = 0; i < copyCurr.maxPossibleCorrections; i++)
        {
            //if(MoveBlockRight(copyCurr) && CanRotate(copyCurr))
            //{
            //}
        }
        // Try Moving right
        // Try Moving left
        // Try Moving Down

        return;
    }

    currBlock.Rotate();
}

bool Tetris::IsBlockOutOfBounds(Block blockToCheck, int rowOffset, int colOffset)
{
    const std::array<SBlockPosition, 4> currPosition = blockToCheck.CalculateCurrentPosition();

    for(const SBlockPosition& componentPos : currPosition)
    {
        if(Grid::IsCellOutOfBounds(componentPos.blockRow + rowOffset, componentPos.blockCol + colOffset))
        {
            return true;
        }
    }
    return false;
}

bool Tetris::CanRotate(Block blockToCheck)
{
    Block currBlockCopy = std::move(blockToCheck);
    currBlockCopy.Rotate();

   const std::array<SBlockPosition, 4> currPosition = currBlockCopy.CalculateCurrentPosition();

   for(const SBlockPosition& componentPos : currPosition)
   {
       if(Grid::IsCellOutOfBounds(componentPos.blockRow, componentPos.blockCol) || !grid.IsCellEmpty(componentPos.blockRow, componentPos.blockCol))
       {
           return false;
       }
   }
    return true;
}

void Tetris::LockBlock()
{
    const std::array<SBlockPosition, 4> currPosition = currBlock.CalculateCurrentPosition();
    for(const SBlockPosition& componentPos : currPosition)
    {
        grid.gridArr[componentPos.blockRow][componentPos.blockCol] = currBlock.GetBlockId();
    }

    SpawnNewBlock();
    HandleFullRows();
}

void Tetris::SpawnNewBlock()
{
    if(!IsThereSpaceForBlock(nextBlock))
    {
        if(!bGameOver)
        {
            SpawnDummyBlock();
        }
        bGameOver = true;
        return;
    }
    currBlock = nextBlock;
    nextBlock = GetRandomBlock();
}

bool Tetris::IsThereSpaceForBlock(Block blockToCheck, int rowOffset, int colOffset)
{
    const std::array<SBlockPosition, 4> currPosition = blockToCheck.CalculateCurrentPosition();
    for(const SBlockPosition& componentPos : currPosition)
    {
        if(!grid.IsCellEmpty(componentPos.blockRow + rowOffset, componentPos.blockCol + colOffset))
        {
            return false;
        }
    }
    return true;
}

bool Tetris::CanMoveRight(const Block& blockToMove)
{
    if(IsBlockOutOfBounds(blockToMove, 0, 1) || !IsThereSpaceForBlock(blockToMove, 0, 1) || bGameOver)
    {
        return false;
    }
    return true;
}

bool Tetris::CanMoveLeft(const Block& blockToMove)
{
    if(IsBlockOutOfBounds(blockToMove, 0, -1) || !IsThereSpaceForBlock(blockToMove, 0, -1) || bGameOver)
    {
        return false;
    }
    return true;
}

bool Tetris::CanMoveDown(const Block& blockToMove)
{
    if(IsBlockOutOfBounds(blockToMove, 1, 0) || !IsThereSpaceForBlock(blockToMove, 1, 0) || bGameOver)
    {
        return false;
    }
    return true;
}

void Tetris::HandleFullRows()
{
    int score = grid.ClearFullRows();
}

void Tetris::SpawnDummyBlock()
{
    nextBlock.Draw();
    nextBlock.Move(-1, 0);
}

void Tetris::ResetGame()
{
    grid.ClearEntireGrid();

    ResetInternalBlocks();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}
