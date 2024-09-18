#include "raylib.h"
#include <iostream>
using namespace std;

Color Green= Color{38, 185, 154, 255};//Not using Transparency so alpha is 255
Color DarkGreen= Color{20, 160, 133, 255};
Color LightGreen= Color{129, 204, 184, 255};
Color yellow= Color{243, 213, 91, 255};

int PlayerScore = 0;
int CpuScore = 0;

class Ball
{
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw()
    {
        DrawCircle(x, y, radius, yellow);
    }

    void Move()
    {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth() )//Computer wins
        {
            CpuScore++;
            speed_x *= -1;
            Reset();
        }
        if(x - radius <= 0)//PlayerWins
        {
            PlayerScore++;
            speed_x *= -1;
            Reset();
        }
    }

    void Reset()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        int speed_choices[] = {1, -1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

class Paddle
{
    protected:
    void LimitMovement()
    {
         if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }
public:
    float x, y;
    int speed;
    float width, height;

    void Draw()
    {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }

    void Move()
    {
        if (IsKeyDown(KEY_UP))
        {
            y -= speed; // To move the paddle up
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y += speed; // To move the paddle down
        }

       LimitMovement();
    }
};


class CpuPaddle : public Paddle
{
    public:
    void Move(int ball_y)
    {
        if (y + height / 2 < ball_y)
        {
            y += speed;
        }
        if (y + height / 2 > ball_y)
        {
            y -= speed;
        }

        LimitMovement();
    }

};


Ball ball;
Paddle player;
CpuPaddle cpu;

int main()
{
    cout << "Starting the game" << endl;
    const int screenWidth = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Pong Game");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25;
    player.height = 120;
    player.x = screenWidth - player.width - 15;
    player.y = screenHeight / 2 - player.height / 2;
    player.speed = 6;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 15;
    cpu.y = screenHeight / 2 - cpu.height / 2;
    cpu.speed = 6;

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        // upating
        ball.Move();
        player.Move();
        cpu.Move(ball.y);

        //Checking For Collision
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speed_x *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
        {
            ball.speed_x *= -1;
        }
        
        // Drawing
        ClearBackground(DarkGreen); // To fill the window with black color before drawing anything.. So that the previous frame is not visible
        DrawRectangle(screenWidth / 2, 0, screenWidth/2, screenHeight, Green);
        DrawCircle(screenWidth / 2, screenHeight / 2, 150, LightGreen);
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
        ball.Draw();
        cpu.Draw();
        player.Draw();

        DrawText(TextFormat("%i",CpuScore), screenWidth / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i",PlayerScore), 3*screenWidth / 4 - 20, 20, 80, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}