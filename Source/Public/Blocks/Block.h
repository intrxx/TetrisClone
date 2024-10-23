#pragma once

#include <map>
#include <array>
#include <vector>

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
    Block() = default;

    int GetBlockId() const
    {
        return id;
    }

    void Draw(int offsetX = 0, int offsetY = 0);
    void Move(int byRows, int byCol);
    void Move(SBlockPosition byPos);
    void Rotate();
    void DoCorrections();

    std::array<SBlockPosition, 4> CalculateCurrentPosition();

public:
    std::map<int, std::array<SBlockPosition, 4>> rotationStatesMap;


    bool bTriedCorrecting = false;

    int currentSimpleCorrections = 0;
    int maxPossibleCorrections = 1;
    std::vector<SBlockPosition> cachedSimpleCorrections;

protected:
    int id = 0;

private:
    int rotationState = 0;

    int currRowOffset = 0;
    int currColOffset = 0;
};