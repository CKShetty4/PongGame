#include "raylib.h"
#include <iostream>
using namespace std;

class Ball{
    public:
    float x,y;
    int speed_x, speed_y;
    int radius;

    void Draw(){
        DrawCircle(x, y, radius, WHITE);
    }

    void Move(){
        x+=speed_x;
        y+=speed_y;

        if (y+ radius >=GetScreenHeight()||y-radius<=0)
        {
            speed_y*=-1;
        }
        if (x+ radius >=GetScreenWidth()||x-radius<=0)
        {
            speed_x*=-1;
        }

    }
};

Ball ball;

int main() {
    cout<<"Starting the game"<<endl;
    const int screenWidth = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Pong Game");
    SetTargetFPS(60);

ball.radius=20;
ball.x=screenWidth/2;
ball.y=screenHeight/2;
ball.speed_x=7;
ball.speed_y=7;


    while (WindowShouldClose()==false)
    {
        BeginDrawing();
//upating 
        ball.Move();
//Drawing
ClearBackground(BLACK);//To fill the window with black color before drawing anything.. So that the previous frame is not visible
        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);
        ball.Draw();
        DrawRectangle(10, screenHeight/2-60, 25, 120, WHITE);//left paddle 10=10(padding) 60=rectangle height
        DrawRectangle(screenWidth-35, screenHeight/2-60, 25, 120, WHITE);//right paddle 35=10(padding)+25(rectangle width)
        EndDrawing();
    }
    



    CloseWindow();
    return 0;
}