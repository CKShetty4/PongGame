#include "raylib.h"
#include <iostream>
using namespace std;
int main() {
    cout<<"Starting the game"<<endl;
    const int screenWidth = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Pong Game");
    SetTargetFPS(60);

    while (WindowShouldClose()==false)
    {
        BeginDrawing();

        EndDrawing();
    }
    



    CloseWindow();
    return 0;
}