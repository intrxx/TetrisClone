#include "raylib.h"
#include "Public/Tetris.h"

double lastUpdateTime = 0;
bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main() {
    const int screenWidth = 500;
    const int screenHeight = 700;
    const char *windowTitle = "Tetris Clone";

    InitWindow(screenWidth, screenHeight, windowTitle);

    SetTargetFPS(60);

    Tetris tetris = Tetris();

    // Main loop
    while(!WindowShouldClose()) {
        UpdateMusicStream(tetris.backgroundMusic);
        tetris.HandleInput();

        if(EventTriggered(0.2))
        {
            tetris.MoveBlockDown();
        }

        BeginDrawing();
        ClearBackground(tetrisStatics::lightGrey);

        tetris.GameLoop();

        EndDrawing();
    }

    CloseWindow();
}
