#include "../../Public/Blocks/Block.h"
#include "../../Public/TetrisTypes.h"

#include "raylib.h"

Block::Block()
{

}

void Block::Draw()
{
    const int margin = tetrisStatics::cellMargin;
    const int cellSize = tetrisStatics::cellSize;
    const Color blockColor = tetrisStatics::tetrisColors[id];

    std::array<SBlockPosition, 4> currentPos = CalculateCurrentPosition();
    for(SBlockPosition position : currentPos)
    {
        DrawRectangle(position.blockCol * cellSize + margin, position.blockRow * cellSize + margin,
                      cellSize - margin, cellSize - margin, blockColor);
    }
}

void Block::Move(int byRows, int byCol)
{
    currColOffset += byCol;
    currRowOffset += byRows;
}

void Block::Move(SBlockPosition byPos)
{
    currColOffset += byPos.blockCol;
    currRowOffset += byPos.blockRow;
}

std::array<SBlockPosition, 4> Block::CalculateCurrentPosition()
{
    std::array<SBlockPosition, 4> initialPos = rotationStatesMap[rotationState];
    std::array<SBlockPosition, 4> movedPos;

    int i = 0;
    for(SBlockPosition position : initialPos)
    {
        SBlockPosition newPos = {position.blockRow + currRowOffset, position.blockCol + currColOffset};
        movedPos[i] = newPos;

        i++;
    }
    return movedPos;
}

void Block::Rotate()
{
    if(rotationState == rotationStatesMap.size() - 1)
    {
        rotationState = 0;
        return;
    }
    rotationState++;
}

