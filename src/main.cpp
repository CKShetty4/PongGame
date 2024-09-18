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

class Paddle{
    public:
    float x,y;
    int speed;
    float width, height;

    void Draw(){
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Move(){
        if (IsKeyDown(KEY_UP))
        {
            y-=speed;//To move the paddle up
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y+=speed;//To move the paddle down
        }

        if(y<=0)
        {
            y=0;
        }
        if(y+height>=GetScreenHeight())
        {
            y=GetScreenHeight()-height;
        }
    }
};


Ball ball;
Paddle player1;
Paddle player2;

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

player1.width=25;
player1.height=120;
player1.x=screenWidth-player1.width-10;
player1.y=screenHeight/2-player1.height/2;
player1.speed=6;

player2.width=25;
player2.height=120;
player2.x=10;
player2.y=screenHeight/2-player2.height/2;
player2.speed=6;


    while (WindowShouldClose()==false)
    {
        BeginDrawing();
//upating 
        ball.Move();
        player1.Move();
        player2.Move();
//Drawing
ClearBackground(BLACK);//To fill the window with black color before drawing anything.. So that the previous frame is not visible
        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);
        ball.Draw();
        player1.Draw();
        player2.Draw();
        EndDrawing();
    }
    



    CloseWindow();
    return 0;
}