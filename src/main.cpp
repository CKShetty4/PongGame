#include "raylib.h"

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "ProjectName");

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        // ...

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);
        // ...
        EndDrawing();
    }

    // De-initialization
    CloseWindow();

    return 0;
}