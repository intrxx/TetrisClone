#include <raylib.h>

#include "../../Public/Blocks/Block.h"
#include "../../Public/TetrisTypes.h"

void Block::Draw(int offsetX, int offsetY)
{
    const int cellMargin = tetrisStatics::cellMargin;
    const int gridMargin = tetrisStatics::gridMargin;
    const int cellSize = tetrisStatics::cellSize;
    const Color blockColor = tetrisStatics::tetrisColors[id];

    std::array<SBlockPosition, 4> currentPos = CalculateCurrentPosition();
    for(const SBlockPosition& position : currentPos)
    {
        DrawRectangle(position.blockCol * cellSize + gridMargin + offsetX, position.blockRow * cellSize + gridMargin + offsetY,
                      cellSize - cellMargin, cellSize - cellMargin, blockColor);
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
    for(const SBlockPosition& position : initialPos)
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

void Block::DoCorrections()
{
    for(auto & cachedSimpleCorrection : cachedSimpleCorrections)
    {
        Move(cachedSimpleCorrection.blockRow, cachedSimpleCorrection.blockCol);
    }
    currentSimpleCorrections = 0;
}

