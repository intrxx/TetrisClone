#pragma once

#include "Block.h"

class LBlock : public Block
{
public:
    LBlock()
    {
        id = 1;

        rotationStatesMap[0] =
        {
                SBlockPosition(0, 2),
                SBlockPosition(1,0 ),
                SBlockPosition(1, 1),
                SBlockPosition(1,2)
        };
        rotationStatesMap[1] =
        {
                SBlockPosition(0, 1),
                SBlockPosition(1,1 ),
                SBlockPosition(2,1),
                SBlockPosition(2,2)
        };
        rotationStatesMap[2] =
        {
                SBlockPosition(1, 0),
                SBlockPosition(1,1 ),
                SBlockPosition(1,2),
                SBlockPosition(2,0)
        };
        rotationStatesMap[3] =
        {
                SBlockPosition(0, 0),
                SBlockPosition(0,1),
                SBlockPosition(1,1),
                SBlockPosition(2,1)
        };

        Move(1, 3);
    };
};

class JBlock : public Block
{
public:
    JBlock()
    {
        id = 2;

        rotationStatesMap[0] =
        {
                SBlockPosition(0, 0),
                SBlockPosition(1,0 ),
                SBlockPosition(1, 1),
                SBlockPosition(1,2)
        };
        rotationStatesMap[1] =
        {
                SBlockPosition(0, 1),
                SBlockPosition(0,2),
                SBlockPosition(1,1),
                SBlockPosition(2,1)
        };
        rotationStatesMap[2] =
        {
                SBlockPosition(1, 0),
                SBlockPosition(1,1 ),
                SBlockPosition(1,2),
                SBlockPosition(2,2)
        };
        rotationStatesMap[3] =
        {
                SBlockPosition(0, 1),
                SBlockPosition(1,1),
                SBlockPosition(2,0),
                SBlockPosition(2,1)
        };

        Move(1, 3);
    };
};

class IBlock : public Block
{
public:
    IBlock()
    {
        id = 3;
        maxPossibleCorrections = 2;

        rotationStatesMap[0] =
        {
                SBlockPosition(1, 0),
                SBlockPosition(1,1),
                SBlockPosition(1, 2),
                SBlockPosition(1,3)
        };
        rotationStatesMap[1] =
        {
                SBlockPosition(0, 2),
                SBlockPosition(1,2),
                SBlockPosition(2,2),
                SBlockPosition(3,2)
        };
        rotationStatesMap[2] =
        {
                SBlockPosition(2, 0),
                SBlockPosition(2,1 ),
                SBlockPosition(2,2),
                SBlockPosition(2,3)
        };
        rotationStatesMap[3] =
        {
                SBlockPosition(0, 1),
                SBlockPosition(1,1),
                SBlockPosition(2,1),
                SBlockPosition(3,1)
        };

        Move(0 ,3);
    };
};

class OBlock : public Block
{
public:
    OBlock()
    {
        id = 4;

        rotationStatesMap[0] =
        {
                SBlockPosition(0, 0),
                SBlockPosition(0,1),
                SBlockPosition(1, 0),
                SBlockPosition(1,1)
        };
        rotationStatesMap[1] =
        {
                SBlockPosition(0, 0),
                SBlockPosition(0,1),
                SBlockPosition(1, 0),
                SBlockPosition(1,1)
        };
        rotationStatesMap[2] =
        {
                SBlockPosition(0, 0),
                SBlockPosition(0,1),
                SBlockPosition(1, 0),
                SBlockPosition(1,1)
        };
        rotationStatesMap[3] =
        {
                SBlockPosition(0, 0),
                SBlockPosition(0,1),
                SBlockPosition(1, 0),
                SBlockPosition(1,1)
        };

        Move(1, 4);
    };
};

class SBlock : public Block
{
public:
    SBlock()
    {
        id = 5;

        rotationStatesMap[0] =
        {
                SBlockPosition(0, 1),
                SBlockPosition(0,2),
                SBlockPosition(1, 0),
                SBlockPosition(1,1)
        };
        rotationStatesMap[1] =
        {
                SBlockPosition(0, 1),
                SBlockPosition(1,1),
                SBlockPosition(1, 2),
                SBlockPosition(2,2)
        };
        rotationStatesMap[2] =
        {
                SBlockPosition(1, 1),
                SBlockPosition(1,2),
                SBlockPosition(2, 0),
                SBlockPosition(2,1)
        };
        rotationStatesMap[3] =
        {
                SBlockPosition(0, 0),
                SBlockPosition(1,0),
                SBlockPosition(1, 1),
                SBlockPosition(2,1)
        };

        Move(1, 3);
    };
};

class TBlock : public Block
{
public:
    TBlock()
    {
        id = 6;

        rotationStatesMap[0] =
        {
                SBlockPosition(0, 1),
                SBlockPosition(1,0),
                SBlockPosition(1, 1),
                SBlockPosition(1,2)
        };
        rotationStatesMap[1] =
        {
                SBlockPosition(0, 1),
                SBlockPosition(1,1),
                SBlockPosition(1, 2),
                SBlockPosition(2,1)
        };
        rotationStatesMap[2] =
        {
                SBlockPosition(1, 0),
                SBlockPosition(1,1),
                SBlockPosition(1, 2),
                SBlockPosition(2,1)
        };
        rotationStatesMap[3] =
        {
                SBlockPosition(0, 1),
                SBlockPosition(1,0),
                SBlockPosition(1, 1),
                SBlockPosition(2,1)
        };

        Move(1, 3);
    };
};

class ZBlock : public Block
{
public:
    ZBlock()
    {
        id = 7;

        rotationStatesMap[0] =
        {
                SBlockPosition(0, 0),
                SBlockPosition(0,1),
                SBlockPosition(1, 1),
                SBlockPosition(1,2)
        };
        rotationStatesMap[1] =
        {
                SBlockPosition(0, 2),
                SBlockPosition(1,1),
                SBlockPosition(1, 2),
                SBlockPosition(2,1)
        };
        rotationStatesMap[2] =
        {
                SBlockPosition(1, 0),
                SBlockPosition(1,1),
                SBlockPosition(2, 1),
                SBlockPosition(2,2)
        };
        rotationStatesMap[3] =
        {
                SBlockPosition(0, 1),
                SBlockPosition(1,0),
                SBlockPosition(1, 1),
                SBlockPosition(2,0)
        };

        Move(1, 3);
    };
};