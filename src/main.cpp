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
        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);
        DrawCircle(screenWidth/2, screenHeight/2, 20, WHITE);
        DrawRectangle(10, screenHeight/2-60, 25, 120, WHITE);//left paddle 10=10(padding) 60=rectangle height
        DrawRectangle(screenWidth-35, screenHeight/2-60, 25, 120, WHITE);//right paddle 35=10(padding)+25(rectangle width)
        EndDrawing();
    }
    



    CloseWindow();
    return 0;
}