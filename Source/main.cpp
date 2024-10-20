#include "raylib.h"
#include "Public/Tetris.h"

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

        BeginDrawing();
        ClearBackground(darkGrey);

        tetris.GameLoop();

        EndDrawing();
    }

    CloseWindow();
}
