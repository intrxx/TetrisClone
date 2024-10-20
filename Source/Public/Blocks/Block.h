#pragma once

#include <map>
#include <array>

struct SBlockPosition
{
    SBlockPosition() = default;
    SBlockPosition(const SBlockPosition& other) = default;
    SBlockPosition(int inRow, int inCol)
        : blockRow(inRow)
        , blockCol(inCol) {}

    int blockRow = 0;
    int blockCol = 0;
};

class Block
{
public:
    Block();

    int GetBlockId() const
    {
        return id;
    }

    void Draw();
    void Move(int byRows, int byCol);
    void Move(SBlockPosition byPos);
    void Rotate();

    std::array<SBlockPosition, 4> CalculateCurrentPosition();

public:
    std::map<int, std::array<SBlockPosition, 4>> rotationStatesMap;

protected:
    int id;

private:
    int rotationState = 0;

    int currRowOffset = 0;
    int currColOffset = 0;
};