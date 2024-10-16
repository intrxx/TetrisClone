#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 800;
    const char *windowTitle = "Tetris Clone";
    const char *message = "Hello world!";
    const int fontSize = 40;
    const float msgSpacing = 1.0f;

    const Color darkGrey = {64, 64, 64, 255};

    InitWindow(screenWidth, screenHeight, windowTitle);

    const Font font = GetFontDefault();
    const Vector2 msgSize = MeasureTextEx(font, message, fontSize, msgSpacing);
    const Vector2 msgPos = Vector2{(screenWidth - msgSize.x) / 2, (screenHeight - msgSize.y) / 2};

    SetTargetFPS(60);

    // Main loop
    while(!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(darkGrey);
        DrawTextEx(font, message, msgPos, fontSize, msgSpacing, RED);
        EndDrawing();
    }

    CloseWindow();
}
