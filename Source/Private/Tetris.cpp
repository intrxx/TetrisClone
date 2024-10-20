#include <random>
#include <algorithm>

#include "../Public/Tetris.h"

Tetris::Tetris()
{
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
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, (int)internalBlocks.size() - 1);

    Block block = internalBlocks[dist(mt)];
    internalBlocks.erase(internalBlocks.begin() + dist(mt));

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
    if(IsBlockOutOfBounds(0, -1))
    {
        return;
    }
    currBlock.Move(0, -1);
}

void Tetris::MoveBlockRight()
{
    if(IsBlockOutOfBounds(0, 1))
    {
        return;
    }
    currBlock.Move(0, 1);
}

void Tetris::MoveBlockDown()
{
    if(IsBlockOutOfBounds(1, 0))
    {
        return;
    }
    currBlock.Move(1, 0);
}

void Tetris::RotateBlock()
{
    const ERotationError rotationError = IsRotatingToOutOfBounds();
    if((int)rotationError > 0)
    {
        if(rotationError == ERotationError::RE_LeftSide)
        {
            currBlock.Move(0, 1);
        }
        if(rotationError == ERotationError::RE_RightSide)
        {
            currBlock.Move(0, -1);
        }
        if(rotationError == ERotationError::RE_Down)
        {
            currBlock.Move(-1, 0);
        }
        RotateBlock();
        return;
    }
    currBlock.Rotate();
}

bool Tetris::IsBlockOutOfBounds(int rowOffset, int colOffset)
{
    const std::array<SBlockPosition, 4> currPosition = currBlock.CalculateCurrentPosition();

    for(const SBlockPosition& componentPos : currPosition)
    {
        if(Grid::IsCellOutOfBounds(componentPos.blockRow + rowOffset, componentPos.blockCol + colOffset))
        {
            return true;
        }
    }
    return false;
}

ERotationError Tetris::IsRotatingToOutOfBounds()
{
    Block currBlockCopy = currBlock;
    currBlockCopy.Rotate();

   const std::array<SBlockPosition, 4> currPosition = currBlockCopy.CalculateCurrentPosition();

   for(const SBlockPosition& componentPos : currPosition)
   {
       const ERotationError rotationError = Grid::IsCellOutOfRotatingBound(componentPos.blockRow, componentPos.blockCol);
       if((int)rotationError > 0)
       {
           return rotationError;
       }
   }
    return ERotationError::RE_NoError;
}
