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
    const int screenWidth = 400;
    const int screenHeight = 700;
    const char *windowTitle = "Tetris Clone";

    const Color darkGrey = {64, 64, 64, 255};

    InitWindow(screenWidth, screenHeight, windowTitle);

    SetTargetFPS(60);

    Tetris tetris = Tetris();

    // Main loop
    while(!WindowShouldClose()) {
        tetris.HandleInput();

        if(EventTriggered(0.18))
        {
            tetris.MoveBlockDown();
        }

        BeginDrawing();
        ClearBackground(darkGrey);

        tetris.GameLoop();

        EndDrawing();
    }

    CloseWindow();
}
