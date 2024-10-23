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

    fontinRegular = LoadFontEx("../../Assets/Font/Fontin-Regular.otf", 64, nullptr, 0);
    fontinSmallCaps = LoadFontEx("../../Assets/Font/Fontin-SmallCaps.otf", 64, nullptr, 0);
    fontinBold = LoadFontEx("../../Assets/Font/Fontin-Bold.otf", 64, nullptr, 0);

    InitAudioDevice();
    backgroundMusic = LoadMusicStream("");
    PlayMusicStream(backgroundMusic);

    rotateSound = LoadSound("");
    clearSound = LoadSound("");
}

Tetris::~Tetris()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(backgroundMusic);
    CloseAudioDevice();
}

void Tetris::GameLoop()
{
    DrawTextEx(fontinRegular, "Score", {352, 15}, 38, 2, WHITE);
    DrawTextEx(fontinRegular, "Next block", {320, 160}, 34, 2, WHITE);

    // Score Rectangle
    DrawRectangleRounded(Rectangle(320, 55, 170, 60), 0.3, 6, tetrisStatics::lightBlue);

    const char* scoreText = std::to_string(score).c_str();
    Vector2 textSize = MeasureTextEx(fontinRegular, scoreText, 34, 2);
    float textWidth = textSize.x;
    float textPosX = 320 + (170 - textWidth) / 2;

    DrawTextEx(fontinRegular, std::to_string(score).c_str(), {textPosX, 70}, 34, 2, WHITE);

    // Block Rectangle
    DrawRectangleRounded(Rectangle(320, 200, 170, 170), 0.3, 6, tetrisStatics::lightBlue);

    switch (nextBlock.GetBlockId())
    {
        case 3: // I Block
            nextBlock.Draw(244, 228);
            break;
        case 4: // O Block
            nextBlock.Draw(245, 210);
            break;
        default:
            nextBlock.Draw(258, 210);
            break;
    }

    grid.Draw();
    currBlock.Draw();

    if(bGameOver)
    {
        DrawTextEx(fontinBold, "Game Over", {50, 75}, 46, 2, WHITE);
        DrawTextEx(fontinBold, "Press R to restart", {46, 125}, 24, 2, WHITE);
    }
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
        case KEY_UP:
            RotateBlock();
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
        case KEY_SPACE:
            InstantPlacement();
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

    PlaySound(rotateSound);
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
    const SScoreStats scoreStats = grid.ClearFullRows();
    if(scoreStats.numberOfRowsCleared > 0)
    {
        PlaySound(clearSound);
        UpdateScore(scoreStats);
    }
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

    score = 0;
}

void Tetris::InstantPlacement()
{
    while(CanMoveDown(currBlock))
    {
        MoveBlockDown();
    }
}

void Tetris::UpdateScore(const SScoreStats &scoreStats)
{
    int addedScore = 0;

    switch(scoreStats.numberOfRowsCleared)
    {
        case 1:
            addedScore += 100;
            break;
        case 2:
            addedScore += 300;
            break;
        case 3:
            addedScore += 500;
            break;
    }

    addedScore += scoreStats.clearedRowNumber > 0 ? scoreStats.clearedRowNumber : 0;

    score += addedScore;
}
